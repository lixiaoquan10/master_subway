#ifndef CPROCESSMODBUSTCP
#define CPROCESSMODBUSTCP

#include <QObject>
#include <QAbstractSocket>
#include <QProcess>

class QTimer;
class QTcpSocket;
class QTcpServer;
class CprocessModbusTcp : public QObject
{
    Q_OBJECT
public:
    explicit CprocessModbusTcp();
    ~CprocessModbusTcp();
    void replySendData(QByteArray data);
    void processReceiveData(QByteArray array);
public slots:
    void slot_readClientData();
    void slot_handleNewConnection();
    void slot_serverlisten();
    void slot_handleDisconnected();
    void onSocketError(QAbstractSocket::SocketError error);
    void slot_controlTxtFileSize();
private:
    QTcpServer* m_modbustcpServer;       // TCP服务器对象
    QTcpSocket* m_modbustcpSocket;  // 客户端连接列表
    QTimer* m_timer;
    QTimer *m_disconnectTimer;

    QByteArray m_receiveBuff;

    QTimer *m_controlTxtTimer;
};

#endif // CPROCESSMODBUSTCP

