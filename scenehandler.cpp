#include "scenehandler.h"

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
    QJsonArray tvector = model["translation"].toArray();
    QJsonArray rvector = model["rotation"].toArray();
    QJsonArray svector = model["scale"].toArray();
    QJsonArray kvector = model["Ka,Kd,Ks"].toArray();
    out->shine = model["shine"].toDouble();

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

    if (tvector.size() != 3) {
        out->translate = QVector3D(0.0, 0.0, 0.0);
    }
    else {

        float dlist[3];

        for (int i = 0; i < tvector.size(); ++i) {
            dlist[i] = (float)tvector[i].toDouble();
        }
        out->translate = QVector3D(dlist[0], dlist[1], dlist[2]);
    }

    if (rvector.size() != 3) {
        out->rotate = QVector3D(0.0, 0.0, 0.0);
    }
    else {
        float dlist[3];

        for (int i = 0; i < rvector.size(); ++i) {
            dlist[i] = (float)rvector[i].toDouble();
        }
        out->rotate = QVector3D(dlist[0], dlist[1], dlist[2]);
    }

    if (svector.size() != 3) {
        out->scale = QVector3D(30.0, 45.0, 45.0);
    }
    else {
        float dlist[3];

        for (int i = 0; i < svector.size(); ++i) {
            dlist[i] = (float)svector[i].toDouble();
        }
        out->scale = QVector3D(dlist[0], dlist[1], dlist[2]);
    }

    if (kvector.size() != 3) {
        out->kConsts = QVector3D(1.0, 1.0, 1.0);
    }
    else {
        float dlist[3];
        for (int i = 0; i < kvector.size(); ++i) {
            dlist[i] = (float)kvector[i].toDouble();
        }
        out->kConsts = QVector3D(dlist[0], dlist[1], dlist[2]);
    }

    qDebug() << "load :" << out->name
             << " file: " << out->fileName
             << " transformed " << out->transform
             << " translate" << out->translate
             << " rotate" << out->rotate
             << " scale" << out->scale
             << " Ka, Kd, Ks: " << out->kConsts
             << " shine: " << out->shine;

    return out;
}

Node*
SceneHandler::parseNode(const QJsonObject& parentNode) {
    Node* out = new Node();
    out->type = parentNode["type"].toString();

    /// detected a model
    if(out->type == "model") {
        out->children.push_back(parseModel(parentNode));
    } else if (out->type == "light") {
      out->children.push_back(parseLight(parentNode));
    } else if(out->type == "node") {

        QJsonArray nodeArray = parentNode["children"].toArray();
        for(int i = 0; i < nodeArray.size(); ++i) {
            out->children.push_back(parseNode(nodeArray[i].toObject()));
        }
    }

    return out;
}

Lights *SceneHandler::parseLight(const QJsonObject &light)
{
    Lights* out = new Lights();

    out->name = light["name"].toString();
    out->source = light["source"].toString();
    QJsonArray lp_vector = light["light position"].toArray();
    QJsonArray ac_vector = light["ambient color rgb"].toArray();
    QJsonArray dc_vector = light["diffuse color rgb"].toArray();
    QJsonArray sc_vector = light["specular color rgb"].toArray();
    QJsonArray il_vector = light["Ia, Id, Is"].toArray();
    QJsonArray af_vector = light["Attenuation: constant, linear, quadratic"].toArray();
    out->distance = light["light distance"].toDouble();

    if (lp_vector.size() != 4) {
        out->lightPosition = QVector4D(1.0, 1.0, 1.0, 0.0);
    }
    else {

        float dlist[4];

        for (int i = 0; i < lp_vector.size(); ++i) {
            dlist[i] = (float)lp_vector[i].toDouble();
        }
        out->lightPosition = QVector4D(dlist[0], dlist[1], dlist[2], dlist[3]);
    }

    if (ac_vector.size() != 3) {
        out->ambientColor = QVector3D(1.0, 1.0, 1.0);
    }
    else {
        float dlist[3];

        for (int i = 0; i < ac_vector.size(); ++i) {
            dlist[i] = (float)ac_vector[i].toDouble();
        }
        out->ambientColor = QVector3D(dlist[0], dlist[1], dlist[2]);
    }

    if (dc_vector.size() != 3) {
        out->diffuseColor = QVector3D(1.0, 1.0, 1.0);
    }
    else {
        float dlist[3];

        for (int i = 0; i < dc_vector.size(); ++i) {
            dlist[i] = (float)dc_vector[i].toDouble();
        }
        out->diffuseColor = QVector3D(dlist[0], dlist[1], dlist[2]);
    }

    if (sc_vector.size() != 3) {
        out->specColor = QVector3D(1.0, 1.0, 1.0);
    }
    else {
        float dlist[3];

        for (int i = 0; i < sc_vector.size(); ++i) {
            dlist[i] = (float)sc_vector[i].toDouble();
        }
        out->specColor = QVector3D(dlist[0], dlist[1], dlist[2]);
    }

    if (il_vector.size() != 3) {
        out->intensityLevel = QVector3D(1.0, 1.0, 1.0);
    }
    else {
        float dlist[3];

        for (int i = 0; i < il_vector.size(); ++i) {
            dlist[i] = (float)il_vector[i].toDouble();
        }
        out->intensityLevel = QVector3D(dlist[0], dlist[1], dlist[2]);
    }

    if (af_vector.size() != 3) {
        out->attenuationFactors = QVector3D(1.0, 1.0, 1.0);
    }
    else {
        float dlist[3];

        for (int i = 0; i < af_vector.size(); ++i) {
            dlist[i] = (float)af_vector[i].toDouble();
        }
        out->attenuationFactors = QVector3D(dlist[0], dlist[1], dlist[2]);
    }

    qDebug() << "load :" << out->name
             << " source: " << out->source
             << " light position: " << out->lightPosition
             << " ambient: " << out->ambientColor
             << " diffuse: " << out->diffuseColor
             << " specular: " << out->specColor
             << " intensity levels: " << out->intensityLevel
             << " attenuation factors: " << out->attenuationFactors
             << " distance: " << out->distance;

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
        out["shine"] = m->shine;

        QJsonArray t, r, s, k;

        t.push_back((float)m->translate.x());
        t.push_back((float)m->translate.y());
        t.push_back((float)m->translate.z());

        r.push_back((float)m->rotate.x());
        r.push_back((float)m->rotate.y());
        r.push_back((float)m->rotate.z());

        s.push_back((float)m->scale.x());
        s.push_back((float)m->scale.y());
        s.push_back((float)m->scale.z());

        k.push_back((float)m->kConsts.x());
        k.push_back((float)m->kConsts.y());
        k.push_back((float)m->kConsts.z());

        out["translation"] = t;
        out["rotation"] = r;
        out["scale"] = s;
        out["Ka,Kd,Ks"] = k;


    } else if (node->type == "light") {
        Lights* l = static_cast<Lights*>(node->children[0]);

        out["name"] = l->name;
        out["source"] = l->source;

        QJsonArray lP, aC, dC, sC, iL, aF, dist;

        lP.push_back((float)l->lightPosition.x());
        lP.push_back((float)l->lightPosition.y());
        lP.push_back((float)l->lightPosition.z());
        lP.push_back((float)l->lightPosition.w());

        aC.push_back((float)l->ambientColor.x());
        aC.push_back((float)l->ambientColor.y());
        aC.push_back((float)l->ambientColor.z());

        dC.push_back((float)l->diffuseColor.x());
        dC.push_back((float)l->diffuseColor.y());
        dC.push_back((float)l->diffuseColor.z());

        sC.push_back((float)l->specColor.x());
        sC.push_back((float)l->specColor.y());
        sC.push_back((float)l->specColor.z());

        iL.push_back((float)l->intensityLevel.x());
        iL.push_back((float)l->intensityLevel.y());
        iL.push_back((float)l->intensityLevel.z());

        aF.push_back((float)l->attenuationFactors.x());
        aF.push_back((float)l->attenuationFactors.y());
        aF.push_back((float)l->attenuationFactors.z());



        out["light position"] = lP;
        out["ambient color rgb"] = aC;
        out["diffuse color rgb"] = dC;
        out["specular color rgb"] = sC;
        out["Ia, Id, Is"] = iL;
        out["Attenuation: constant, linear, quadratic"] = aF;
        out["light distance"] = l->distance;


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
