// Local
#include "HTTPServer.h"

HTTPServer::HTTPServer(QObject *parent)
  : QObject(parent)
  , m_httpServer(new QHttpServer(this))
{
  //! FAKE
  connect(&m_timer, SIGNAL(timeout()), SLOT(timer()));
  m_timer.start(1000);

  connect(m_httpServer, SIGNAL(newRequest(QHttpRequest*, QHttpResponse*)), this, SLOT(handle(QHttpRequest*, QHttpResponse*)));
}


void HTTPServer::timer()
{
  emit pgasData(QByteArray("data"));
}


bool HTTPServer::listen(int port)
{
  // let's go
  bool isListen = m_httpServer->listen(port);
  if (isListen)
    qDebug() << tr("Http server запущен");
  else
    qWarning() << tr("Ошибка запуска http server-а");

  return isListen;
}


void HTTPServer::handle(QHttpRequest* request, QHttpResponse* response)
{
  QByteArray body = request->body();
  QHttpRequest::HttpMethod method = request->method();
  switch (method)
  {
    case QHttpRequest::HTTP_GET:
      qDebug() << "get";
      emit pgasData(body);
      break;
    case QHttpRequest::HTTP_POST:
      qDebug() << "port";
      break;
    case QHttpRequest::HTTP_PUT:
      qDebug() << "put";
      break;
    default:
      qWarning() << tr("Неизвестный тип запроса");
      break;
  }
}
