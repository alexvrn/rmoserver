// Local
#include "LocalServer.h"

// Qt
#include <QLocalServer>
#include <QLocalSocket>
#include <QSettings>
#include <QDate>
#include <QFile>
#include <QDir>

LocalServer::LocalServer(QObject *parent)
  : QObject(parent)
  , m_localServer(new QLocalServer(this))
  , m_rmoSocket(nullptr)
{
  // Подключение клиента РМО
  connect(m_localServer, SIGNAL(newConnection()), SLOT(newConnection()));

  QSettings settings("SAMI DVO RAN", "rmo");
  m_sourceDataPath = settings.value("sourceDataPath",
#if defined(Q_OS_LINUX)
      "/tmp/rmoserver/"
#else
      "C:\tmp\rmoserver\"
#endif
      ).toString();

  QDir dir;
  dir.mkpath(m_sourceDataPath);
}


bool LocalServer::listen(const QString& name)
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


void LocalServer::pgasData(const QByteArray& data)
{
  if (!m_rmoSocket)
    return;

  m_rmoSocket->write(data);

  // Сохраняем данные в файле
  QString fileName = QString("%1%2%3").arg(m_sourceDataPath).arg(QDate::currentDate().toString("ddmmyyy")).arg(".dat");
  QFile dat(fileName);
  dat.open(QIODevice::Append);
  dat.write(data);
  dat.close();
}
