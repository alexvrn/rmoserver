#ifndef LOCALSERVER_H
#define LOCALSERVER_H

// Qt
#include <QObject>
class QLocalServer;
class QLocalSocket;
class QTimer;

class LocalServer : public QObject
{
  Q_OBJECT

  public:
    explicit LocalServer(QObject *parent = nullptr);

    bool listen(const QString& name);

  signals:

  public slots:
    void pgasData(const QByteArray& data);

  private slots:
    void newConnection();
    void disconnected();

    void clearTimer();

  private:
    QLocalServer* m_localServer;
    QLocalSocket* m_rmoSocket;

    QString m_sourceDataPath;

    // Таймер для очистки старых данных, в зависимости от параметров, заданных в конфиге
    QTimer m_clearTimer;
};

#endif // LOCALSERVER_H
