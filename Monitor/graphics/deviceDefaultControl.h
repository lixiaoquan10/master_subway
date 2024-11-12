#ifndef DEVICEDEFAULTCONTROL_H
#define DEVICEDEFAULTCONTROL_H
#include <QObject>
#include <QString>
#include <QFileInfo>
#include <QtXml/QDomDocument>
#include <QDebug>
#include <QMap>
#include <QCoreApplication>
#include <QDir>
#include <QSettings>
#include <QVector>
#include "deviceControl.h"
class CCanport;
class CDistribution;
class CLoop;
class CDevice;
class deviceDefaultControl : public QObject
{
        Q_OBJECT
public:
    deviceDefaultControl();
    bool restDeviceDefaultControl();
    bool saveDeviceDefaultControlFile();
private:
    void ParseROOT(QDomNode* node);
    void ParseBRANCH_LEVEL1(QDomNode *node);
    void SaveROOT(QDomNode* node);
    void SaveBranchLevel1(QDomElement* parentNode, CDevice* device);

private:
    cROOT m_tRoot;
    QDomElement eldRoot;
    QDomDocument m_domDocSaveConfig;
};

#endif // DEVICEDEFAULTCONTROL_H
