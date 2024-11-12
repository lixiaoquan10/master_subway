#include "cglobal.h"
#include "deviceDefaultControl.h"

deviceDefaultControl::deviceDefaultControl()
{
    m_tRoot.m_sVersion = "1.00";
    m_tRoot.m_sTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
}
bool deviceDefaultControl::restDeviceDefaultControl()//deviceControl.xml文件并获取根节点
{
    qDebug() << "deviceDefaultControl::restDeviceDefaultControl" << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    QString deviceControlPath;

    deviceControlPath = qApp->applicationDirPath() + "/logfile/deviceDefaultControl.xml" ;//in linux

    QFile file(deviceControlPath);
    if (!file.open(QFile::ReadOnly))
    {
        return false;
    }
    QString errorStr;
    int errorLine;
    int errorColumn;
    QDomDocument qDomConfigFile;
    if (!qDomConfigFile.setContent(&file, false, &errorStr, &errorLine,&errorColumn))
    {
        return false;
    }
    QDomElement root = qDomConfigFile.documentElement();
    QDomNode child = root.firstChild();
    if (!child.isNull())
    {
        if(child.toElement().tagName() == "ROOT")
        {
            ParseROOT(&child);
        }
    }
    file.close();
    return true;
}

bool deviceDefaultControl::saveDeviceDefaultControlFile()
{
    qDebug() << "deviceDefaultControl::saveDeviceDefaultControlFile" << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    QDomElement root = m_domDocSaveConfig.documentElement();
    if(root.isNull())
    {
        root = m_domDocSaveConfig.createElement("xml");
    }
    SaveROOT(&root);
    m_domDocSaveConfig.appendChild(root);

    QString sFilePath = qApp->applicationDirPath() + "/logfile/deviceDefaultControl.xml";

    QFile file(sFilePath);
    if (!file.open(QFile::WriteOnly|QFile::Truncate | QFile::Text))//1.QFile::WriteOnly如果文件不存在，则创建；2.QFile::Truncate打开的同时清空
    {
        return false;
    }
    QTextStream stream( &file );
    stream.setCodec("utf-8");
    m_domDocSaveConfig.save(stream,4,QDomNode::EncodingFromTextStream);
    file.close();
    return true;
}

void deviceDefaultControl::ParseROOT(QDomNode *node)//解析根节点
{
    qDebug() << "deviceDefaultControl::ParseROOT" << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    m_tRoot.m_sVersion = node->toElement().attribute("version");
    m_tRoot.m_sTime = node->toElement().attribute("time");
    ParseBRANCH_LEVEL1(node);
}

void deviceDefaultControl::ParseBRANCH_LEVEL1(QDomNode *node)//解析一级分支
{
    qDebug() << "deviceControl::ParseBRANCH_LEVEL1" << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    QDomNode childnode = node->toElement().firstChild();
    while(!childnode.isNull())
    {
        if(childnode.toElement().tagName() == "DeviceDefaultControl")
        {
            int canportAddress = childnode.toElement().attribute("CanAddress").toInt();
            int distributionAddress = childnode.toElement().attribute("DistributionAddress").toInt();
            int loopAddress = childnode.toElement().attribute("LoopAddress").toInt();
            int deviceAddress = childnode.toElement().attribute("DeviceAddress").toInt();
            CCanport* canport = CGlobal::instance()->controller()->canportByAddress(canportAddress);
            if(!canport)
                return;
            CDistribution* distribution = canport->distributionByAddress(distributionAddress);
            if(distribution)
            {
                CLoop* loop = distribution->loopByAdd(loopAddress);
                if(loop)
                {
                    CDevice* device = loop->deviceByAdd(deviceAddress);
                    if(device)
                    {
                        device->setDeviceDefaultControl(false);
                        CMsgObjectStatus msgobjectstatus;
                        msgobjectstatus.nCanportAdd = device->canportAdd();
                        msgobjectstatus.nDisID = device->distributionAdd();
                        msgobjectstatus.nLoopID = device->loopAdd();
                        msgobjectstatus.nDeviceID = device->deviceAdd();
                        msgobjectstatus.nValue = 0x04;
                        int defaultDirection = device->deviceValue(DEVICE_VALUE_DEFAULTDIRECTION).toInt();
                        msgobjectstatus.nValue |= defaultDirection;
                        CGlobal::instance()->ClientBusiness()->exeCommand(NCT_DeviceDefaultDirection, &msgobjectstatus);
                   }
                }
            }
        }
        childnode = childnode.nextSibling();
    }
    saveDeviceDefaultControlFile();
}


void deviceDefaultControl::SaveROOT(QDomNode *node)  //保存根节点
{
    qDebug() << "deviceDefaultControl::SaveROOT" << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    QDomElement eldRoot = m_domDocSaveConfig.createElement("ROOT");
    eldRoot.setAttribute("version",m_tRoot.m_sVersion);
    eldRoot.setAttribute("time",m_tRoot.m_sTime);
    for(int i=3; i<=CGlobal::instance()->m_nCanNumber+2; i++)
    {
        CCanport* canport = CGlobal::instance()->controller()->canportByAddress(i);
        if(!canport)
            continue;
        QList<CDistribution*> distributions = canport->distributions();
        for(int i=0; i<distributions.count(); i++){
            CDistribution* distribution = distributions.at(i);
            if(distribution){
                QList<CLoop*> loops = distribution->loops();
                for(int i=0; i<loops.count(); i++){
                    CLoop* loop = loops.at(i);
                    if(loop){
                        QList<CDevice*> devices = loop->devices();
                        for(int m=0; m<devices.count(); m++){
                            CDevice* device = devices.at(m);
                            if(device)
                            {
                                if(device->isDeviceDefaultControl())
                                    SaveBranchLevel1(&eldRoot,device);
                            }
                        }
                        devices.clear();
                    }
                }
                loops.clear();
            }
        }
        distributions.clear();
    }
    node->appendChild(eldRoot);
}


void deviceDefaultControl::SaveBranchLevel1(QDomElement *parentNode, CDevice* device)   //保存一级分支
{
    qDebug() << "deviceDefaultControl::SaveBranchLevel1" << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    QDomElement eleBranchLV1 = m_domDocSaveConfig.createElement("DeviceDefaultControl");
    eleBranchLV1.setAttribute("CanAddress",device->canportAdd());
    eleBranchLV1.setAttribute("DistributionAddress",device->distributionAdd());
    eleBranchLV1.setAttribute("LoopAddress",device->loopAdd());
    eleBranchLV1.setAttribute("DeviceAddress",device->deviceAdd());
    parentNode->appendChild(eleBranchLV1);
}

