// Qt
#include <QCoreApplication>
#include <QLocale>
#include <QSettings>
#include <QDebug>

// Local
#include "Server.h"
#include "LocalServer.h"

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

  LocalServer localServer;
  if (!localServer.connectToHost("rmoserver"))
    return 0;

  Server server(pgasServers);

  return app.exec();
}
