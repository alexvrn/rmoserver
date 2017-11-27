// Qt
#include <QCoreApplication>
#include <QLocale>
#include <QSettings>
#include <QDebug>

// Local
#include "Server.h"
#include "LocalServer.h"
#include "HTTPServer.h"

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);

  app.setOrganizationName("SAMI DVO RAN");
  app.setOrganizationDomain("skbsami.ru");
  app.setApplicationName("rmo");

  // Установка локали по умолчанию
  QLocale russianLocale(QLocale::Russian, QLocale::RussianFederation);
  QLocale::setDefault(russianLocale);

  QSettings settings("SAMI DVO RAN", "rmo");

  // Читаем адреса серверов ПГАС
  QList<QPair<QString, int> > pgasServers;
  int size = settings.beginReadArray("PGAS");
  for (int i = 0; i < size; ++i)
  {
    settings.setArrayIndex(i);
    pgasServers.append(qMakePair(settings.value("ip").toString(),
                                 settings.value("number").toInt()));
  }
  settings.endArray();

  if (pgasServers.isEmpty())
    pgasServers.append(qMakePair("127.0.0.1", 111));


  HTTPServer httpServer;

  LocalServer localServer;
  if (!localServer.listen("rmoserver"))
    return 0;

  QObject::connect(&httpServer, &HTTPServer::pgasData, &localServer, &LocalServer::pgasData);

  Server server(pgasServers);

  return app.exec();
}
