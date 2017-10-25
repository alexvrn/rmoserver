// Qt
#include <QCoreApplication>
#include <QSharedPointer>

// Local
#include "Server.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  Server server;
  server.connectToHost("", 1);

  return a.exec();
}
