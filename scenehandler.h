/* ****************************************************
 * SceneHandler class for processing JSON files
 *****************************************************/

#ifndef SCENEHANDLER_H
#define SCENEHANDLER_H

#include <QJsonDocument>
#include <QMatrix4x4>

struct Node {
    QString type;
    QVector<Node*> children;
};

struct Model : public Node
{
    QString name;
    QString fileName;
    QMatrix4x4 transform;

    QVector3D translate;
    QVector3D rotate;
    QVector3D scale;

};

struct Scene
{
    QString name;
    QString description;
    QVector<Node*> root;
};

class SceneHandler {

public:
    SceneHandler();
    ~SceneHandler();

    void scenedemo();
    Model* parseModel(const QJsonObject& model);
    Node* parseNode(const QJsonObject& parentNode) ;
    void scenedemoRead(const QString& filename, QVector<Scene *> &scenes);

    QJsonObject writeNode(Node* node);
    void scenedemoWrite(const QString& filename, QVector<Scene *> &scenes);

};

#endif
