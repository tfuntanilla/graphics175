#include "SceneHandler.h"

#include <QFile>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

SceneHandler::SceneHandler() {
}


SceneHandler::~SceneHandler() {
}

Model*
SceneHandler::parseModel(const QJsonObject& model) {
    Model* out = new Model();

    out->name = model["name"].toString();
    out->fileName = model["filename"].toString();
    QJsonArray jmatrix = model["matrix"].toArray();

    if(jmatrix.size() != 16) {
        qDebug() << "name: " << out->name
                 << " file: " << out->fileName
                 << " matrix length: " << jmatrix.size()
                 << " not 16";
        out->transform.setToIdentity();
    } else {

        float dlist[16];

        for(int i = 0; i < jmatrix.size(); ++i) {
            dlist[i] = (float)jmatrix[i].toDouble();
        }
        out->transform = QMatrix4x4(dlist);
    }
    qDebug() << "load :" << out->name
             << " file: " << out->fileName
             << " transformed " << out->transform;

    return out;
}

Node*
SceneHandler::parseNode(const QJsonObject& parentNode) {
    Node* out = new Node();
    out->type = parentNode["type"].toString();

    /// detected a model
    if(out->type == "model") {
        out->children.push_back(parseModel(parentNode));
    } else if(out->type == "node") {

        QJsonArray nodeArray = parentNode["children"].toArray();
        for(int i = 0; i < nodeArray.size(); ++i) {
            out->children.push_back(parseNode(nodeArray[i].toObject()));
        }
    }

    return out;
}


void
SceneHandler::scenedemoRead(const QString &filename, QVector<Scene*>& scenes) {
    QString fileContents;

    QFile file(filename);

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    fileContents = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(fileContents.toUtf8());

    QJsonArray sceneList = doc.array();

    for(int i = 0; i < sceneList.size(); ++i) {

        Scene* scene = new Scene();

        QJsonObject object = sceneList[i].toObject();
        scene->name = object["name"].toString();
        scene->description = object["description"].toString();

        QJsonArray rootNode = object["root"].toArray();

        qDebug() << "scene: " << i << " " << scene->name << " " << scene->description;

        for(int i = 0; i < rootNode.size(); ++i) {
            scene->root.push_back(parseNode(rootNode[i].toObject()));
        }
        scenes.push_back(scene);
    }
}


QJsonObject
SceneHandler::writeNode(Node* node) {

    QJsonObject out;
    out["type"] = node->type;

    if(node->type == "model") {

        Model* m = static_cast<Model*>(node->children[0]);

        out["name"] = m->name;
        out["filename"] = m->fileName;

        qDebug() << out["name"] << " " << out["filename"];

        QJsonArray data;
        for(int i = 0; i < 16; ++i) {
            data.push_back((float)m->transform.data()[i]);
        }

        out["matrix"] = data;
    } else if(node->type == "node") {
        QJsonArray children;
        for(int i = 0; i < node->children.size(); ++i) {
            children.push_back(writeNode(node->children[i]));
        }
        out["children"] = children;
    }
    return out;
}

void
SceneHandler::scenedemoWrite(const QString &filename, QVector<Scene *> &scenes) {
    QFile file(filename);

    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QJsonDocument doc;

    QJsonArray sceneList;
    for(int i = 0; i < scenes.size(); ++i) {
        QJsonObject scene;
        scene["name"] = scenes[i]->name;
        scene["description"] = scenes[i]->description;
        qDebug() << "writing : " << scene["name"] << " " << scene["description"];
        QJsonArray rootNode;
        for(int j = 0; j < scenes[i]->root.size(); ++j) {
            QJsonValue value = writeNode(scenes[i]->root[j]);
            rootNode.push_back(value);
        }
        scene["root"] = rootNode;
        sceneList.push_back(scene);
    }

    doc.setArray(sceneList);
    file.write(doc.toJson());
    file.close();

}


void
SceneHandler::scenedemo() {
    QVector<Scene*> scenes;
    scenedemoRead(":/scene/sample", scenes);
    //scenedemoRead("out.json", scenes);
    scenedemoWrite("out2.json", scenes);
}
