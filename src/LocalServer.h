#ifndef LOCALSERVER_H
#define LOCALSERVER_H

// Qt
#include <QObject>
class QLocalServer;
class QLocalSocket;
#include <QTimer>

class LocalServer : public QObject
{
  Q_OBJECT

  public:
    enum WaitState
    {
      WaitingId,
      WaitingMessageType,
      WaitingLength,
      WaitingMessage
    };

    explicit LocalServer(QObject *parent = nullptr);

    bool listen(const QString& name);

  signals:

  public slots:
    void pgasData(const QByteArray& data);

  private slots:
    void newConnection();
    void disconnected();
    void readyRead();

    void clearTimer();

  private:
    void init();

    QLocalServer* m_localServer;
    QLocalSocket* m_rmoSocket;

    QString m_sourceDataPath;

    // Таймер для очистки старых данных, в зависимости от параметров, заданных в конфиге
    QTimer m_clearTimer;

    WaitState m_waitState;
    quint16 m_messageType;
    quint32 m_messageLength;
};

#endif // LOCALSERVER_H
