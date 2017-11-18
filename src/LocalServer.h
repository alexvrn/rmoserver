#ifndef LOCALSERVER_H
#define LOCALSERVER_H

// Qt
#include <QObject>
class QLocalServer;
class QLocalSocket;

class LocalServer : public QObject
{
  Q_OBJECT

  public:
    explicit LocalServer(QObject *parent = nullptr);

    bool listen(const QString& name);

  signals:

  public slots:
    void pgasData(const QByteArray& data);

  private slots:
    void newConnection();
    void disconnected();

  private:
    QLocalServer* m_localServer;
    QLocalSocket* m_rmoSocket;

    QString m_sourceDataPath;
};

#endif // LOCALSERVER_H
