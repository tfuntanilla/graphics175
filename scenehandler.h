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
    QMatrix4x4 projection;
    QMatrix4x4 view;
    QMatrix4x4 model;

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
