#ifndef HTTPSERVER_H
#define HTTPSERVER_H

// Qt
#include <QObject>
#include <QTimer>

// Http server
#include <qhttpserver.h>
#include <qhttprequest.h>
#include <qhttpresponse.h>

class HTTPServer : public QObject
{
  Q_OBJECT

  public:
    explicit HTTPServer(QObject *parent = nullptr);

  signals:
    void pgasData(const QByteArray& data);

  public slots:
    bool listen(int port);

  private slots:
    void timer(); //! FAKE

    void handle(QHttpRequest* request, QHttpResponse* response);

  private:
    //! FAKE
    QTimer m_timer;

    QHttpServer* m_httpServer;
};

#endif // HTTPSERVER_H
