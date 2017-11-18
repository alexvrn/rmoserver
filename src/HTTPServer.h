#ifndef HTTPSERVER_H
#define HTTPSERVER_H

// Qt
#include <QObject>
#include <QTimer>

class HTTPServer : public QObject
{
  Q_OBJECT

  public:
    explicit HTTPServer(QObject *parent = nullptr);

  signals:
    void pgasData(const QByteArray& data);

  public slots:

  private slots:
    void timer();

  private:
    //! FAKE
    QTimer m_timer;
};

#endif // HTTPSERVER_H
