#ifndef LOCALSERVER_H
#define LOCALSERVER_H

// Qt
#include <QObject>
#include <QTimer>
class QLocalServer;
class QLocalSocket;

class LocalServer : public QObject
{
  Q_OBJECT

  public:
    explicit LocalServer(QObject *parent = nullptr);

    bool connectToHost(const QString& name);

  signals:

  private slots:
    void runtimer();
    void newConnection();
    void disconnected();

  private:
    QLocalServer* m_localServer;
    QLocalSocket* m_rmoSocket;

    //! FAKE
    QTimer m_timer;
};

#endif // LOCALSERVER_H
