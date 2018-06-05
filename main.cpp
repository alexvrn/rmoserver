// Qt
#include <QLocale>
#include <QSettings>
#include <QApplication>
#include <QDebug>

// Local
#include "MainWindow.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  app.setOrganizationName("SAMI_DVO_RAN");
  app.setOrganizationDomain("skbsami.ru");
  app.setApplicationName("rmo");

  // Установка локали по умолчанию
  QLocale russianLocale(QLocale::Russian, QLocale::RussianFederation);
  QLocale::setDefault(russianLocale);

  MainWindow mainWindow;
  mainWindow.show();

  return app.exec();
}
