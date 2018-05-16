#ifndef LOCALSERVER_H
#define LOCALSERVER_H

// Qt
#include <QObject>
class QLocalServer;
class QLocalSocket;
#include <QTimer>
#include <QFile>
#include <QMap>
#include <QVariantMap>

// Local
#include <commandType.h>

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
    ~LocalServer();

    bool listen(const QString& name);

  signals:

  public slots:
    void pgasData(CommandType::Command cmd, const QByteArray& data);
    void responseData(CommandType::Command cmd, const QByteArray& data);

  private slots:
    void newConnection();
    void disconnected();
    void readyRead();

    void clearTimer();

    //! Открытие файла для сохранения данных с сервера
    bool openFile();

    QVariantMap parseData(CommandType::Command cmd, const QByteArray& data) const;

  private:
    void init();

    QLocalServer* m_localServer;
    QLocalSocket* m_rmoSocket;

    QString m_sourceDataPath;

    // Таймер для очистки старых данных, в зависимости от параметров, заданных в конфиге
    QTimer m_clearTimer;

    QMap<int, QFile*> m_dataPGAS;

    WaitState m_waitState;
    CommandType::Command m_command;
    quint32 m_messageLength;
};

#endif // LOCALSERVER_H
