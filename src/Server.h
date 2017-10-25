#ifndef SERVER_H
#define SERVER_H

// Qt
#include <QObject>
#include <QTimer>
class QLocalServer;
class QLocalSocket;
class QNetworkAccessManager;

// SYSTEM
#include <csignal>

class Server : public QObject
{
  Q_OBJECT

  public:
    explicit Server(QObject *parent = nullptr);
    virtual ~Server();

    void connectToHost(const QString& host, int port);

  private slots:
    void runtimer();
    void newConnection();
    void disconnected();

  private:
    void exitProgramm(int sig);

    QNetworkAccessManager* m_networkManager;
    QLocalServer* m_localServer;
    QLocalSocket* m_rmoSocket;

    //! FAKE
    QTimer m_timer;
};

#endif // SERVER_H
