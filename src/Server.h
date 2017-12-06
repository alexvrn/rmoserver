#ifndef SERVER_H
#define SERVER_H

// Qt
#include <QObject>
#include <QTimer>
#include <QMap>
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
    FirmwareBurn, // Запись образа, содержащего ПО ПГАС/СКГП, системные таблицы адресов и др., в программируемое ПЗУ ПГАС/СКГП
    Rtc, // Запрос системного времени ПГАС/СКГП
    Env // Запрос гидрофизических параметров среды
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

    // Отправка команды
    void sendCommand(const QString& pgasHost, CommandType cmd,
                     RequestType requestType, const QByteArray& data = QByteArray());
    // Строковое представление команды для запроса
    QString commantString(CommandType command) const;
    // Создание коннекта
    //void makeConnect(QNetworkReply* reply, CommandType cmd);

    void rebootFinished();
    void rtcFinished();

  private:
    // Обработка сигналов от ОС Linux
    static void exitProgramm(int sig);

    // Отправка настройки параметров http-сервера
    void postSettingServer();

    QList< QPair<QString, int> > m_pgasServers;

    // Список подключений ПГАС
    QNetworkAccessManager* m_networkManager;
};

#endif // SERVER_H
