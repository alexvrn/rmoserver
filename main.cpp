// Qt
#include <QCoreApplication>
#include <QLocale>
#include <QSettings>
#include <QDebug>

// Local
#include "Server.h"

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

  Server server(pgasServers);
  if (!server.connectToHost("", 1))
    return 0;

  return app.exec();
}
