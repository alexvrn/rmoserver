// Local
#include "HTTPServer.h"

HTTPServer::HTTPServer(QObject *parent)
  : QObject(parent)
{
  connect(&m_timer, SIGNAL(timeout()), SLOT(timer()));
  m_timer.start(1000);
}


void HTTPServer::timer()
{
  emit pgasData(QByteArray("data"));
}
