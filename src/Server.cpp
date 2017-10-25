// Local
#include "Server.h"

// Qt
#include <QCoreApplication>
#include <QLocalServer>
#include <QLocalSocket>
#include <QNetworkAccessManager>
#include <QDebug>

static Server* serverExit;

Server::Server(QObject *parent)
  : QObject(parent)
  , m_networkManager(new QNetworkAccessManager(this))
  , m_localServer(new QLocalServer(this))
  , m_rmoSocket(nullptr)
{
  serverExit = this;
  //signal(SIGINT, &Server::exitProgramm);
  //signal(SIGTERM, &Server::exitProgramm);

  connect(m_localServer, SIGNAL(newConnection()), SLOT(newConnection()));

  connect(&m_timer, SIGNAL(timeout()), SLOT(runtimer()));
  m_timer.start(2000);
}


Server::~Server()
{
  m_localServer->close();
}


void Server::exitProgramm(int sig)
{
  Q_UNUSED(sig)

  QCoreApplication::exit(0);
}


void Server::connectToHost(const QString& host, int port)
{
  if (m_localServer->isListening())
    return;

  if (m_localServer->listen("rmoserverrrrr"))
    qDebug() << tr("Локальный сервер запущен: rmoserver");
  else
    qFatal(qPrintable(QString("Не удаётся запустить сервер: rmoserver %1").arg(m_localServer->errorString())));

  m_networkManager->connectToHost(host, port);
}


void Server::newConnection()
{
  if (m_rmoSocket)
  {
    qWarning() << tr("Попытка подключить ещё одно РМО!");
    return;
  }

  m_rmoSocket = m_localServer->nextPendingConnection();
  connect(m_rmoSocket, SIGNAL(disconnected()), SLOT(disconnected()));

  qDebug() << tr("Подключение к клиенту РМО.");
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
