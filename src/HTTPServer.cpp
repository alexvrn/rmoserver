// Local
#include "HTTPServer.h"
#include <qhttprequest.h>
#include <qhttpresponse.h>
#include <commandType.h>

// Qt
#include <QEventLoop>
#include <QDataStream>


HTTPServer::HTTPServer(QObject *parent)
  : QObject(parent)
  , m_httpServer(new QHttpServer(this))
{
  //! FAKE
  connect(&m_timer, SIGNAL(timeout()), SLOT(timer()));
  //m_timer.start(5000);

  connect(m_httpServer, SIGNAL(newRequest(QHttpRequest*,QHttpResponse*)), this, SLOT(handle(QHttpRequest*, QHttpResponse*)));
}


void HTTPServer::timer()
{
  //emit pgasData(QByteArray("data"));

//  QUrl url("http://127.0.0.1:2777");
//  QNetworkRequest request(url);
//  request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-www-form-urlencoded"));
//  man->post(request, QByteArray("wewedata"));
}


bool HTTPServer::listen(int port)
{
  // let's go
  bool isListen = m_httpServer->listen(QHostAddress::Any, port);
  if (isListen)
    qDebug() << tr("Http-server запущен: порт %1").arg(port);
  else
    qWarning() << tr("Ошибка запуска http server-а на порту") << port;

  return isListen;
}


void HTTPServer::close()
{
  m_httpServer->close();
}


void HTTPServer::handle(QHttpRequest* request, QHttpResponse* response)
{
  // Это используется только в протоколе HTTP 1.1
  if (request->header("expect") == "100-continue")
  {
    response->writeHead(QHttpResponse::STATUS_CONTINUE);
    response->end();
    return;
  }

  bool shallWeWaitOrHandleThePOSTRequestNow = !request->body().isEmpty();
  const auto method = request->method();
  if ((method == QHttpRequest::HTTP_POST || method == QHttpRequest::HTTP_PUT) && !shallWeWaitOrHandleThePOSTRequestNow)
  {
    // Объект сам себя удаляет после получения данных
    auto requestProcess = new RequestProcess(request, response, this);
    connect(requestProcess, &RequestProcess::pgasData, this, &HTTPServer::pgasData);
    return;
  }
  else if (method == QHttpRequest::HTTP_GET)
  {
    //emit pgasData(body);
    response->writeHead(QHttpResponse::STATUS_OK);
    response->end();
  }
  else
  {
    qWarning() << tr("Необрабатываемый тип запроса") << method;
  }
}


RequestProcess::RequestProcess(QHttpRequest* request, QHttpResponse* response, QObject *parent)
  : QObject(parent)
  , m_request(request)
  , m_response(response)
{
  response->writeHead(QHttpResponse::STATUS_OK);

  connect(m_request, SIGNAL(data(const QByteArray&)), this, SLOT(accumulate(const QByteArray&)));
  connect(m_request, SIGNAL(end()), this, SLOT(reply()));
  connect(m_response, SIGNAL(done()), this, SLOT(deleteLater()));
}


void RequestProcess::accumulate(const QByteArray& data)
{
  const QString path = m_request->path();
  auto paths = path.split("-");
  if (paths.length() != 2)
  {
    qWarning() << tr("Неверный url:") << path;
    return;
  }
  // Номер потока (1-22)
  CommandType::Command streamNumber = static_cast<CommandType::Command>(paths[1].toInt());
  emit pgasData(streamNumber, data);

  // Проверка распаковки данных
//  QByteArray d = data;
//  size_t offset = 0;
//  cbor_stream_t cborStream = {reinterpret_cast<unsigned char*>(d.data()), static_cast<size_t>(data.length()), 0};
//  switch (streamNumber)
//  {
//    case CommandType::Stream_1:
//    {
//      cmd_data86_t cmdData;
//      cmd_data86_unpack(&cborStream, &offset, &cmdData);
//      break;
//    }
//    case CommandType::Stream_2:
//    {
//      cmd_data89_t cmdData;
//      cmd_data89_unpack(&cborStream, &offset, &cmdData);
//      break;
//    }
//    case CommandType::Stream_3:
//    {
//      cmd_data92_t cmdData;
//      cmd_data92_unpack(&cborStream, &offset, &cmdData);
//      break;
//    }
//    default:
//      //qWarning() << tr("Неизвестный номер потока") << streamNumber;
//      break;
//  }
}


void RequestProcess::reply()
{
  m_response->end();
}
