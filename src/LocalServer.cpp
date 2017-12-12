// Local
#include "LocalServer.h"
#include <commandType.h>

// Qt
#include <QLocalServer>
#include <QLocalSocket>
#include <QSettings>
#include <QDate>
#include <QFile>
#include <QDir>
#include <QDataStream>

// CBOR
#include <cbor.h>

// structs
#include <cmd_data.h>
#include <cmd_data_packer.c>


const quint16 idMessage = 0xCAFE;

LocalServer::LocalServer(QObject *parent)
  : QObject(parent)
  , m_localServer(new QLocalServer(this))
  , m_rmoSocket(nullptr)
  , m_waitState(WaitingId)
  , m_messageType(-1)
  , m_messageLength(0)
{
  // Подключение клиента РМО
  connect(m_localServer, SIGNAL(newConnection()), SLOT(newConnection()));

  QSettings settings("SAMI DVO RAN", "rmo");
  m_sourceDataPath = settings.value("sourceDataPath",
#if defined(Q_OS_LINUX)
      "/tmp/rmoserver"
#else
      "C:\\tmp\\rmoserver"
#endif
  ).toString();

  // Создаём папку для хранения файлов
  QDir dir;
  if (!dir.mkpath(m_sourceDataPath))
    qWarning() << tr("Не удалось создать каталог для хранения файлов") << m_sourceDataPath;

  connect(&m_clearTimer, SIGNAL(timeout()), SLOT(clearTimer()));
  m_clearTimer.start(1000 * 60 * 60); // Запускаем таймер каждый час
}


bool LocalServer::listen(const QString& name)
{
  if (m_localServer->listen(name))
  {
    qDebug() << tr("Локальный сервер запущен: rmoserver");
  }
  else
  {
    qWarning() << QString("Не удаётся запустить сервер: rmoserver %1").arg(m_localServer->errorString());
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
  connect(m_rmoSocket, SIGNAL(readyRead()), SLOT(readyRead()));

  qDebug() << tr("Подключение к клиенту РМО.");
}


void LocalServer::disconnected()
{
  m_rmoSocket = nullptr;
  qDebug() << tr("Отключение клиента РМО.");
}


void LocalServer::init()
{
  m_messageType = -1;
  m_messageLength = 0;
  m_waitState = WaitingId;
}


void LocalServer::readyRead()
{
  // TDOD: не знаю, нужна ли тут эта проверка
  if (!m_rmoSocket)
    return;

  if (m_waitState == WaitingId)
  {
    // ждем ID-сообщения
    if (m_rmoSocket->bytesAvailable() < (qint64)sizeof(quint16))
      return;

    quint16 id;
    auto data = m_rmoSocket->read(sizeof(quint16));
    QDataStream dataStream(&data, QIODevice::ReadOnly);
    //! TODO: dataStream.setByteOrder(QDataStream::LittleEndian);
    dataStream >> id;
    if (id != idMessage)
    {
      init();
      qWarning() << tr("Попытка прочесть какое-то другое сообщение");
      return;
    }

    m_waitState = WaitingMessageType;
  }

  if (m_waitState == WaitingMessageType)
  {
    // ждем тип сообщения
    if (m_rmoSocket->bytesAvailable() < (qint64)sizeof(quint16))
      return;

    auto data = m_rmoSocket->read(sizeof(quint16));
    QDataStream dataStream(&data, QIODevice::ReadOnly);
    //! TODO: dataStream.setByteOrder(QDataStream::LittleEndian);
    dataStream >> m_messageType;

    m_waitState = WaitingLength;
  }

  if (m_waitState == WaitingLength)
  {
    // ждем размер сообщения
    if (m_rmoSocket->bytesAvailable() < (qint64)sizeof(quint32))
      return;

    auto data = m_rmoSocket->read(sizeof(quint16));
    QDataStream dataStream(&data, QIODevice::ReadOnly);
    //! TODO: dataStream.setByteOrder(QDataStream::LittleEndian);
    dataStream >> m_messageLength;

    m_waitState = WaitingMessage;
  }

  if (m_waitState == WaitingMessage)
  {
    // ждем сообщениe
    if (m_rmoSocket->bytesAvailable() < (qint64)m_messageLength)
      return;

    QByteArray message = m_rmoSocket->read(m_messageLength);
    qDebug() << tr("Тип") << m_messageType << message.length();
    init();
  }
}


QVariantMap LocalServer::parseData(CommandType::Command cmd, const QByteArray& data) const
{
  QVariantMap vm;
  vm["i"] = 1;
  vm["j"] = 2;
  return vm;
  //QByteArray _d = data; //! TODO
  //size_t offset = 0;
  //cbor_stream_t cborStream = {reinterpret_cast<unsigned char*>(_d.data()), static_cast<size_t>(data.length()), 0};
//  switch (cmd)
//  {
//    case CommandType::Stream_1:
//    {
//      cmd_data86_t cmdData;
//      cmd_data86_unpack(&cborStream, &offset, &cmdData);
//      return QVariantMap();
//    }
//    case CommandType::Stream_2:
//    {
//      cmd_data89_t cmdData;
//      cmd_data89_unpack(&cborStream, &offset, &cmdData);
//      return QVariantMap();
//    }
//    case CommandType::Stream_3:
//    {
//      cmd_data92_t cmdData;
//      cmd_data92_unpack(&cborStream, &offset, &cmdData);
//      return QVariantMap();
//    }
//    case CommandType::Stream_4:
//    {
//      cmd_data86_t cmdData;
//      cmd_data86_unpack(&cborStream, &offset, &cmdData);
//      return QVariantMap();
//    }
//    case CommandType::Stream_5:
//    {
//      cmd_data89_t cmdData;
//      cmd_data89_unpack(&cborStream, &offset, &cmdData);
//      return QVariantMap();
//    }
//    case CommandType::Stream_6:
//    {
//      cmd_data92_t cmdData;
//      cmd_data92_unpack(&cborStream, &offset, &cmdData);
//      return QVariantMap();
//    }
//    case CommandType::Stream_7:
//    {
//      cmd_data86_t cmdData;
//      cmd_data86_unpack(&cborStream, &offset, &cmdData);
//      return QVariantMap();
//    }
//    case CommandType::Stream_8:
//    {
//      cmd_data89_t cmdData;
//      cmd_data89_unpack(&cborStream, &offset, &cmdData);
//      return QVariantMap();
//    }
//    case CommandType::Stream_9:
//    {
//      cmd_data92_t cmdData;
//      cmd_data92_unpack(&cborStream, &offset, &cmdData);
//     return QVariantMap();
//    }
//    case CommandType::Stream_10:
//    {
//      cmd_data86_t cmdData;
//      cmd_data86_unpack(&cborStream, &offset, &cmdData);
//      return QVariantMap();
//    }
//    case CommandType::Stream_11:
//    {
//      cmd_data89_t cmdData;
//      cmd_data89_unpack(&cborStream, &offset, &cmdData);
//      return QVariantMap();
//    }
//    case CommandType::Stream_12:
//    {
//      cmd_data92_t cmdData;
//      cmd_data92_unpack(&cborStream, &offset, &cmdData);
//      return QVariantMap();
//    }
//    case CommandType::Stream_13:
//    {
//      cmd_data86_t cmdData;
//      cmd_data86_unpack(&cborStream, &offset, &cmdData);
//      return QVariantMap();
//    }
//    case CommandType::Stream_14:
//    {
//      cmd_data89_t cmdData;
//      cmd_data89_unpack(&cborStream, &offset, &cmdData);
//      return QVariantMap();
//    }
//    case CommandType::Stream_15:
//    {
//      cmd_data92_t cmdData;
//      cmd_data92_unpack(&cborStream, &offset, &cmdData);
//      return QVariantMap();
//    }
//    case CommandType::Stream_16:
//    {
//      cmd_data86_t cmdData;
//      cmd_data86_unpack(&cborStream, &offset, &cmdData);
//      return QVariantMap();
//    }
//    case CommandType::Stream_17:
//    {
//      cmd_data89_t cmdData;
//      cmd_data89_unpack(&cborStream, &offset, &cmdData);
//     return QVariantMap();
//    }
//    case CommandType::Stream_18:
//    {
//      cmd_data92_t cmdData;
//      cmd_data92_unpack(&cborStream, &offset, &cmdData);
//      return QVariantMap();
//    }
//    case CommandType::Stream_19:
//    {
//      cmd_data86_t cmdData;
//      cmd_data86_unpack(&cborStream, &offset, &cmdData);
//      return QVariantMap();
//    }
//    case CommandType::Stream_20:
//    {
//      cmd_data89_t cmdData;
//      cmd_data89_unpack(&cborStream, &offset, &cmdData);
//      return QVariantMap();
//    }
//    case CommandType::Stream_21:
//    {
//      cmd_data92_t cmdData;
//      cmd_data92_unpack(&cborStream, &offset, &cmdData);
//      return QVariantMap();
//    }
//    case CommandType::Stream_22:
//    {
//      cmd_data92_t cmdData;
//      cmd_data92_unpack(&cborStream, &offset, &cmdData);
//      return QVariantMap();
//    }
//    default:
//    {
//      qWarning() << tr("Неизвестный номер потока") << cmd;
//      return QVariantMap();
//    }
//  }
}


void LocalServer::pgasData(CommandType::Command cmd, const QByteArray& data)
{
  bool fromPgas = cmd >= CommandType::Stream_1 && cmd <= CommandType::Stream_22;

  // Сохраняем данные в файле (название файла строится в соответствии с текущим днём ddMMyyyy)
  if (fromPgas)
  {
    QString fileName = QString("%1%2%3%4").arg(m_sourceDataPath).arg(QDir::separator()).arg(QDate::currentDate().toString("ddMMyyyy")).arg(".dat");
    QFile dat(fileName);
    if (dat.open(QIODevice::Append))
    {
      QDataStream out(&dat);
      out.setVersion(QDataStream::Qt_5_9);
      out << quint16(cmd);
      out << quint32(data.length());
      if (data.length())
        out.writeRawData(data.data(), data.length());
    }
    else
    {
      qWarning() << tr("Ошибка открытия файла") << fileName;
    }
  }

  // Посылаем данные клиенту GUI, если он подключен
  if (!m_rmoSocket)
    return;

  QByteArray package;
  QDataStream out(&package, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_5_9);
  out << quint16(idMessage);
  out << quint16(cmd);

  // Проверка на код потока
  if (fromPgas)
  {
     QVariant v;
     v.setValue(parseData(cmd, data));
     QByteArray ba = v.toByteArray();
     out << quint32(ba.length());
     if (ba.length())
       out.writeRawData(ba.data(), ba.length());
  }
  else
  {
    // подготовка данных для записи
    out << quint32(data.length());
    if (data.length())
      out.writeRawData(data.data(), data.length());
  }

  // Отправка данных
  m_rmoSocket->write(package);
  if (!m_rmoSocket->waitForBytesWritten())
    qWarning() << tr("Ошибка отправки данных!"); //! TODO: что тут делать?
}


void LocalServer::clearTimer()
{
  //
}
