// Local
#include "Server.h"

// Qt
#include <QCoreApplication>
#include <QLocalServer>
#include <QLocalSocket>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>

Server::Server(QList< QPair<QString, int> > pgasServers, QObject *parent)
  : QObject(parent)
  , m_pgasServers(pgasServers)
  , m_localServer(new QLocalServer(this))
  , m_rmoSocket(nullptr)
{
  // Обработка аварийного закрытия программы
  // Иначе сервер остаётся открытым
#if defined(Q_OS_LINUX)
  signal(SIGINT, &Server::exitProgramm);
  signal(SIGTERM, &Server::exitProgramm);
#endif

  // Подключение клиента РМО
  connect(m_localServer, SIGNAL(newConnection()), SLOT(newConnection()));

  // Все IP для ПГАС находятся в конфиг файле
  for (auto server : m_pgasServers)
  {
    qDebug() << tr("настройка сервера") << server;

    auto manager = new QNetworkAccessManager(this);
    //network->connectToHost(server.first);
    m_networkManagers.append(manager);

    sendCommand(server.first, Reboot, POST, manager);
  }

  connect(&m_timer, SIGNAL(timeout()), SLOT(runtimer()));
  m_timer.start(200);
}


Server::~Server()
{
}


void Server::exitProgramm(int sig)
{
  Q_UNUSED(sig)

  QCoreApplication::exit(0);
}


bool Server::connectToHost(const QString& name)
{
  if (m_localServer->listen(name))
  {
    qDebug() << tr("Локальный сервер запущен: rmoserver");
  }
  else
  {
    qWarning(qPrintable(QString("Не удаётся запустить сервер: rmoserver %1").arg(m_localServer->errorString())));
    return false;
  }

  return true;
}


void Server::newConnection()
{
  if (m_rmoSocket)
  {
    qWarning() << tr("Попытка подключить ещё одно РМО!");
    return;
  }

  m_rmoSocket = m_localServer->nextPendingConnection();
  Q_ASSERT(m_rmoSocket);
  connect(m_rmoSocket, SIGNAL(disconnected()), SLOT(disconnected()));

  qDebug() << tr("Подключение к клиенту РМО.");
}


void Server::sendCommand(const QString& pgasHost, CommandType cmd,
                     RequestType requestType, QNetworkAccessManager* manager)
{
  QUrl url(QString("%1%2").arg(pgasHost).arg(commantString(cmd)));
  QNetworkRequest request(url);

  QNetworkReply* reply;
  switch (requestType)
  {
    case GET:
      reply = manager->get(request);
      break;
    case POST:
      reply = manager->post(request, QByteArray());
      break;
    default:
      qWarning() << tr("Не выбран тип запроса");
      return;
  }
  makeConnect(reply, cmd);
}


void Server::makeConnect(QNetworkReply* reply, CommandType cmd)
{
  switch (cmd)
  {
    case Reboot:
      connect(reply, SIGNAL(finished()), SLOT(rebootFinished()));
      break;
    default:
      qWarning() << tr("Неизвестная команда") << cmd;
  }
}


QString Server::commantString(CommandType command) const
{
  switch (command)
  {
    case Reboot: return QString("/control/reboot");
    case Resurface: return QString("/control/resurface");
    case SelfTest: return QString("/control/self-test");
    case FirmwareBurn: return QString("/firmware/burn");
    default:
      return QString();
  }
}


void Server::rebootFinished()
{
  auto reply = qobject_cast<QNetworkReply*>(sender());
  if (reply->error() == QNetworkReply::NoError)
  {
    qDebug() << "ok";
  }
  else
  {
    qDebug() << "error:" << qPrintable(reply->errorString());
  }

  reply->deleteLater();
}



void Server::disconnected()
{
  m_rmoSocket = nullptr;
}


void Server::runtimer()
{
  if (!m_rmoSocket)
    return;

  m_rmoSocket->write("block");
}
