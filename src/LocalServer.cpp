// Local
#include "LocalServer.h"

// Qt
#include <QLocalServer>
#include <QLocalSocket>

LocalServer::LocalServer(QObject *parent)
  : QObject(parent)
  , m_localServer(new QLocalServer(this))
  , m_rmoSocket(nullptr)
{
  // Подключение клиента РМО
  connect(m_localServer, SIGNAL(newConnection()), SLOT(newConnection()));

  connect(&m_timer, SIGNAL(timeout()), SLOT(runtimer()));
  m_timer.start(200);
}


bool LocalServer::connectToHost(const QString& name)
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


void LocalServer::newConnection()
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


void LocalServer::disconnected()
{
  m_rmoSocket = nullptr;
}


void LocalServer::runtimer()
{
  if (!m_rmoSocket)
    return;

  m_rmoSocket->write("block");
}
