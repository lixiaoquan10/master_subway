#ifndef CCOMMUNICATIONLINE_H
#define CCOMMUNICATIONLINE_H

#include <QHash>
#include "packagetemplate.h"
#include "ccandatabytearray.h"

class CSerialPort;
class CCommunicationLine
{
public:
    CCommunicationLine();
    void destroy();

public:
    CSerialPort* pSerialPort;
    QHash<int, QList<QByteArray> > sendDataTableAsType;
    PackageTemplate sendPacketTemplate;
    QByteArray reciveData;
    int recentRespondSerialNumber;
    int recentReceiveSerialNumber;
    int nPort;
};

struct Block
{
    int start;
    int end;
    void clear(){start=-1;end=-1;}
    Block():start(-1),end(-1){}
};

#endif // CCOMMUNICATIONLINE_H
