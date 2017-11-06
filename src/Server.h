#ifndef SERVER_H
#define SERVER_H

// Qt
#include <QObject>
#include <QTimer>
class QLocalServer;
class QLocalSocket;
class QNetworkAccessManager;

// SYSTEM
#if defined(Q_OS_LINUX)
#include <csignal>
#endif

class Server : public QObject
{
  Q_OBJECT

  public:
    explicit Server(QList<QPair<QString, int> > pgasServers, QObject *parent = nullptr);
    virtual ~Server();

    bool connectToHost(const QString& host, int port);

  private slots:
    void runtimer();
    void newConnection();
    void disconnected();

  private:
    // Обработка сигналов от ОС Linux
    static void exitProgramm(int sig);

    // Список подключений ПГАС
    QList<QNetworkAccessManager*> m_networkManagers;
    QLocalServer* m_localServer;
    QLocalSocket* m_rmoSocket;

    //! FAKE
    QTimer m_timer;
};

#endif // SERVER_H
