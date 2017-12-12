#ifndef HTTPSERVER_H
#define HTTPSERVER_H

// Qt
#include <QObject>
#include <QTimer>
//#include <QNetworkAccessManager>

// Http server
#include <qhttpserver.h>

// Local
#include <commandType.h>

class HTTPServer : public QObject
{
  Q_OBJECT

  public:
    explicit HTTPServer(QObject *parent = nullptr);

  signals:
    void pgasData(CommandType::Command cmd, const QByteArray& data);

  public slots:
    bool listen(int port);

  private slots:
    void timer(); //! FAKE
    void handle(QHttpRequest* request, QHttpResponse* response);

  private:
    //! FAKE
    QTimer m_timer;

    QHttpServer* m_httpServer;
    //QNetworkAccessManager* man;
    QList< QPair< QHttpRequest*, QHttpResponse* > > mmm;
};

class RequestProcess : public QObject
{
  Q_OBJECT

  public:
    RequestProcess(QHttpRequest* request, QHttpResponse* response, QObject *parent = nullptr);

  signals:
    void pgasData(CommandType::Command cmd, const QByteArray& data);

  private slots:
    void accumulate(const QByteArray& data);
    void reply();

  private:
    QHttpRequest* m_request;
    QHttpResponse* m_response;
};

#endif // HTTPSERVER_H
