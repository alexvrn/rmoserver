// Local
#include "Server.h"

// Qt
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QtEndian>
#include <QDataStream>
#include <QFile>

// CBOR
#include <cbor.h>

// structs
//#include <cmd_data.h>
//#include <cmd_data_packer.c>

const quint16 idMessage = 0xCAFE;

Server::Server(QList< QPair<QString, int> > pgasServers, QObject *parent)
  : QObject(parent)
  , m_pgasServers(pgasServers)
  , m_networkManager(new QNetworkAccessManager(this))
{
  // Обработка аварийного закрытия программы
  // Иначе сервер остаётся открытым
#if defined(Q_OS_LINUX)
  signal(SIGINT, &Server::exitProgramm);
  signal(SIGTERM, &Server::exitProgramm);
#endif

  // Все IP для ПГАС находятся в конфиг файле
//  for (auto server : m_pgasServers)
//  {
//    qDebug() << tr("Настройка сервера") << server;
//    //sendCommand(server.first, Reboot, POST);

//    qint32 dt = QDateTime::currentMSecsSinceEpoch() / 1000;

//    cmd_data30_t cmd30;
//    cmd30.beta.b0 = 3.0;
//    cmd30.beta.b1 = 3.0;
//    cmd30.beta.b2 = 3.0;
//    for(int i=0; i<24;++i)
//    {
//      cmd30.soundVelocity[i].sv = 3;
//      cmd30.soundVelocity[i].toHour = 1;
//    }
//    cmd30.multipathTimeCoef = 20;

//    unsigned char stream_data[1024];
//    cbor_stream_t stream = {stream_data, sizeof(stream_data), 0};
//    cmd_data30_pack(&stream, &cmd30);

//    //sendCommand(server.first, Env, PUT, QByteArray(reinterpret_cast<char*>(stream.data), static_cast<size_t>(stream.size)));
//    //sendCommand(server.first, Env, GET);

//    ///////////////////////////////
//    cmd_data19_t cmd19;
//    cmd19.timestamp = dt;

//    unsigned char stream_data_rtc[1024];
//    cbor_stream_t stream_rtc = {stream_data_rtc, sizeof(stream_data_rtc), 0};
//    cmd_data19_pack(&stream_rtc, &cmd19);
//    //sendCommand(server.first, Rtc, POST, QByteArray(reinterpret_cast<char*>(stream_rtc.data), static_cast<size_t>(stream_rtc.size)));
//    //sendCommand(server.first, Rtc, GET);

//    ////////////////////////////////
//    //sendCommand(server.first, SelfTest, POST);

//    {
//      cmd_data165_t cmd165;
//      cmd165.attChannelId = 1;
//      strcpy(cmd165.baseURL, "localhost:2777");
//      cmd165.interval = 10;
//      cmd165.targetId = 1;

//      cmd_data168_t cmd;
//      cmd.stream_id[0] = cmd165;

//      unsigned char stream_data_168[1024];
//      cbor_stream_t stream_168 = {stream_data_168, sizeof(stream_data_168), 0};
//      cmd_data168_pack(&stream_168, &cmd);

//      //sendCommand(server.first, Streams, PUT, QByteArray(reinterpret_cast<char*>(stream_168.data), static_cast<size_t>(stream_168.size)));
//    }
//  }
}


Server::~Server()
{
}


void Server::exitProgramm(int sig)
{
  Q_UNUSED(sig)

  QCoreApplication::exit(0);
}


void Server::postSettingServer()
{

}


void Server::sendCommand(const QString& pgasHost, CommandType cmd,
                     RequestType requestType, const QByteArray& data)
{
  QUrl url(QString("%1%2").arg(pgasHost).arg(commantString(cmd)));
  QNetworkRequest request(url);

  QNetworkReply* reply;
  switch (requestType)
  {
    case GET:
      reply = m_networkManager->get(request);
      break;
    case POST:
      reply = m_networkManager->post(request, data);
      break;
    case PUT:
      reply = m_networkManager->put(request, data);
      break;
    default:
      qWarning() << tr("Не выбран тип запроса");
      return;
  }
  QEventLoop loop;
  QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
  loop.exec();

  if (reply->error() == QNetworkReply::NoError)
  {
    QByteArray resultData = reply->readAll();

    switch (requestType)
    {
      case GET:
      {
        QDataStream stream(&resultData, QIODevice::ReadOnly);
        stream.setByteOrder(QDataStream::LittleEndian);

        if (cmd == Env)
        {
          qDebug() << resultData;
        }
        else if (cmd == Rtc)
        {
//          qDebug() << resultData;
//          cmd_data19_t cmd19;
//          size_t offset = 0;
//          cbor_stream_t stream_rtc = {reinterpret_cast<unsigned char*>(resultData.data()), static_cast<size_t>(resultData.length()), 0};
//          cmd_data19_unpack(&stream_rtc, &offset, &cmd19);
//          qDebug() << cmd19.timestamp;

        }
        else if (cmd == Streams)
        {
          qDebug() << "stream" << resultData;
        }

        break;
      }
      case POST:
      {
        qDebug() << "post 1" << resultData;
        break;
      }
      case PUT:
      {
        qDebug() << "put 1" << resultData;
        break;
      }
      default: {}
    }
  }
  else
  {
    qDebug() << "error:" << qPrintable(reply->errorString());
  }

  reply->deleteLater();
  //makeConnect(reply, cmd);
}


//void Server::makeConnect(QNetworkReply* reply, CommandType cmd)
//{
//  switch (cmd)
//  {
//    case Reboot:
//      connect(reply, SIGNAL(finished()), SLOT(rebootFinished()));
//      break;
//    case Rtc:
//      connect(reply, SIGNAL(finished()), SLOT(rtcFinished()));
//      break;
//    default:
//      qWarning() << tr("Неизвестная команда") << cmd;
//  }
//}


QString Server::commantString(CommandType command) const
{
  switch (command)
  {
    case Reboot: return QString("/control/reboot");
    case Resurface: return QString("/control/resurface");
    case SelfTest: return QString("/control/self-test");
    case FirmwareBurn: return QStringLiteral("/firmware/burn");
    case Rtc: return QString("/rtc");
    case Env: return QString("/env-params");
    case Streams: return QString("/streams");
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


void Server::rtcFinished()
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
