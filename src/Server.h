#ifndef SERVER_H
#define SERVER_H

// Qt
#include <QObject>
#include <QTimer>
#include <QMap>
class QLocalServer;
class QLocalSocket;
class QNetworkAccessManager;
class QNetworkReply;

// SYSTEM
#if defined(Q_OS_LINUX)
#include <csignal>
#endif

class Server : public QObject
{
  Q_OBJECT

  enum CommandType
  {
    Reboot,    // Перезагрузка программного обеспечения ПГАС/СКГП
    Resurface, // Отделение якорного устройства ПГАС/СКГП
    SelfTest,  // Проведение функционального контроля ПГАС и перезагрузка ПГАС/СКГП
    FirmwareBurn // Запись образа, содержащего ПО ПГАС/СКГП, системные таблицы адресов и др., в программируемое ПЗУ ПГАС/СКГП
  };

  enum RequestType
  {
    GET,
    PUT,
    POST
  };

  public:
    explicit Server(QList<QPair<QString, int> > pgasServers, QObject *parent = nullptr);
    virtual ~Server();

    bool connectToHost(const QString& name);

  private slots:
    void runtimer();
    void newConnection();
    void disconnected();

    // Отправка команды
    void sendCommand(const QString& pgasHost, CommandType cmd, RequestType requestType, QNetworkAccessManager* manager);
    // Строковое представление команды для запроса
    QString commantString(CommandType command) const;
    // Создание коннекта
    void makeConnect(QNetworkReply* reply, CommandType cmd);

    void rebootFinished();

  private:
    // Обработка сигналов от ОС Linux
    static void exitProgramm(int sig);

    QList< QPair<QString, int> > m_pgasServers;

    // Список подключений ПГАС
    QList<QNetworkAccessManager*> m_networkManagers;
    QLocalServer* m_localServer;
    QLocalSocket* m_rmoSocket;

    //! FAKE
    QTimer m_timer;
};

#endif // SERVER_H
