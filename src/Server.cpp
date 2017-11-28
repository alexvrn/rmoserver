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
  for (auto server : m_pgasServers)
  {
    qDebug() << tr("Настройка сервера") << server;
    //sendCommand(server.first, Reboot, POST);

    qint32 dt = QDateTime::currentMSecsSinceEpoch() / 1000;
    qDebug() << dt;
    //QByteArray ba = QByteArray::fromRawData(reinterpret_cast<const char*>(dt), sizeof(quint64));
    //qDebug()<< ba;
    //char bytes[sizeof(qint32)];
    //memcpy(bytes, &dt, sizeof(qint32));
    //QByteArray ba(bytes, sizeof(qint32));

    QByteArray ba1;

    ba1 += CBOR::pack(20.0);
    ba1 += CBOR::pack(20.0);
    ba1 += CBOR::pack(20.0);

    for (int i = 0; i < 23; i++)
    {
      ba1 += CBOR::pack(20);
      ba1 += CBOR::pack(2.4);
    }
    ba1 += CBOR::pack(2.0);

//    QVariantList cmd_data31_t;
//    cmd_data31_t << (float)20.0;
//    cmd_data31_t << (float)20.0;
//    cmd_data31_t << (float)20.0;

//    QVariantList soundVelocity;
//    for (int i = 0; i < 23; i++)
//    {
//      QVariantList cmd_data32_t;
//      cmd_data32_t << 20;// unsigned  toHour;
//      cmd_data32_t << (float)2.4;//    float  sv;
//      soundVelocity.append(cmd_data32_t);
//    }
//    QVariantList cmd_data30_t;
//    cmd_data30_t << cmd_data31_t;
//    cmd_data30_t << soundVelocity;
//    cmd_data30_t << (float)2.0;

    auto bbb = CBOR::pack(ba1);
//    QFile ff("E:\\work\\rmoserver\\cbor-qt\\unittest\\ff.dat");
//    ff.open(QIODevice::WriteOnly);
//    ff.write(bbb);
//    ff.close();

    sendCommand(server.first, Env, PUT, bbb);
    sendCommand(server.first, Env, GET);
  }

//  QVariantMap map;

//  QVariantMap map1;
//  map1["int"] = 56;

//  map["int"] = 42;
//  map["bar"] = 3.14;
//  map["baz"] = "Hello world";
//  map["map"] = map1;

//  qDebug() << (CBOR::unpack(CBOR::pack(map)) == map);

//  QFile f("/home/alexey/project/rmoserver/data/pp_pss_000_000.dat");
//  qDebug() << f.open(QIODevice::ReadOnly);
//  QDataStream in(&f);    // read the data serialized from the file
//  int i;
//  in >> i;
//  qDebug() << i;
//  f.close();
}


Server::~Server()
{
}


void Server::exitProgramm(int sig)
{
  Q_UNUSED(sig)

  QCoreApplication::exit(0);
}


void Server::sendCommand(const QString& pgasHost, CommandType cmd,
                     RequestType requestType, const QByteArray& data)
{
  QUrl url(QString("%1%2").arg(pgasHost).arg(commantString(cmd)));
  QNetworkRequest request(url);

  QEventLoop loop;
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
  QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
  loop.exec();

  if (reply->error() == QNetworkReply::NoError)
  {
    qDebug() << "ok";
    switch (requestType)
    {
      case GET:
      {
        QByteArray resultData = reply->readAll();
        QDataStream stream(&resultData,  QIODevice::ReadOnly);
        stream.setByteOrder(QDataStream::LittleEndian);

        //qint32 dt;
        //stream >> dt;
        qDebug() << resultData;
        //qDebug() << qFromBigEndian<char*>(resultData.data());
        //

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
