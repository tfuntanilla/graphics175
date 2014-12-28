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

    QVector3D kConsts;

    float shine;

};

struct Lights : public Node
{
    QString name;
    QString source;
    QVector4D lightPosition;

    QVector3D ambientColor;
    QVector3D diffuseColor;
    QVector3D specColor;
    QVector3D intensityLevel;

    QVector3D attenuationFactors;
    float distance;
};

struct Textures : public Node
{
    QString mapping;
    QString wrap_mode;
    QString interpolation;
    QString bump_mode;

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
    Lights* parseLight(const QJsonObject& light);
    Textures *parseTexture(const QJsonObject &texture);
    void scenedemoRead(const QString& filename, QVector<Scene *> &scenes);

    QJsonObject writeNode(Node* node);
    void scenedemoWrite(const QString& filename, QVector<Scene *> &scenes);


};

#endif
