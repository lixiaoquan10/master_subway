#include "cglobal.h"


#define CONTROLLER_MODEL_PIXMAP "canport_model_pixmap"

CCanportModel::CCanportModel(QObject *parent) :
    CModel(parent), m_canport(0)
{
    initObject();
    setTrack(true);
}

CCanportModel::~CCanportModel()
{
    delete m_distributionCount;
}

CCanportModel::CCanportModel(CCanport *canport, bool track, QObject *parent) :
    CModel(parent), m_canport(0)
{
    initObject();
    setTrack(track);
    setCanport(canport);
}

int CCanportModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}

QVariant CCanportModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if(section == CANPORT_COLUMN_NAME)
            return "名称";
        else if(section == CANPORT_COLUMN_NUMBER)
            return "数量";
        else if(section == CANPORT_COLUMN_ONLINE)
            return "在线数量";
    }
    else if (role == Qt::FontRole && orientation == Qt::Horizontal)
    {
        QFont font;
        font.setPointSize(12);  // 设置字号为12
        return font;
    }
    return QVariant();
}

void CCanportModel::setCanport(CCanport *canport)
{
    if(m_canport != canport)
    {
        clean();
        m_canport = canport;
        if(m_canport)
        {
            connectObject(m_canport);
            m_rootObject = m_canport;
            addItem(m_canport, m_root);
            appendObject(m_distributionCount, m_canport);

            connect(m_canport, SIGNAL(onlineChanged()), this, SLOT(updateOnline()));
        }
        calcObject();
        updateOnline();
    }
}

void CCanportModel::objectChanged(CObject::ObjectType type, CObject *object)
{
    Q_UNUSED(type);
    Q_UNUSED(object);
    calcObject();
}

void CCanportModel::objectDestroy(CObject *object)
{
    if(object == m_canport)
    {
        m_canport = NULL;
        CModel::setRootObject(m_canport);
        return;
    }
    CModel::objectDestroy(object);
}

QVariant CCanportModel::data(const QModelIndex &index, int role) const
{
    CObject* data = getObject(index);
    if(!data)
        return QVariant();
    if(role == Qt::DisplayRole){
        if(index.column() == CANPORT_COLUMN_NAME)
            return data->value(OBJECT_VALUE_DISPLAY_NAME);
        else if(index.column() == CANPORT_COLUMN_NUMBER)
            return data->value("number");
        else if(index.column() == CANPORT_COLUMN_ONLINE)
            return data->value("online_number");
    }
    if(role == Qt::DecorationRole){
        if(index.column() == CANPORT_COLUMN_NAME)
            return data->value(CONTROLLER_MODEL_PIXMAP);
    }
    return QVariant();
}

void CCanportModel::initObject()
{
    m_distributionCount = new CObject();
    m_distributionCount->setValue(OBJECT_VALUE_DISPLAY_NAME, "集中电源");
    m_distributionCount->setValue("number", 0);
    m_distributionCount->setValue("online_number", 0);
    m_distributionCount->setValue(CONTROLLER_MODEL_PIXMAP, QPixmap(":/images/distribution.png"));
}

void CCanportModel::calcObject()
{
    if(m_canport)
    {
        int distributionCount = m_canport->distributionCount();
        m_distributionCount->setValue("number", distributionCount);
    }
    else
    {
        m_distributionCount->setValue("number", 0);
    }
}


void CCanportModel::updateOnline()
{
    if(m_canport)
    {
        m_distributionCount->setValue("online_number", m_canport->getOnlineDistributionCount());
    }
    else
    {
        m_distributionCount->setValue("online_number", 0);
    }
}
