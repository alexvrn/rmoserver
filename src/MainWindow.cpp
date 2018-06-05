// Local
#include "MainWindow.h"
#include "ui_mainwindow.h"

// Qt
#include <QSettings>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , m_httpServer(new HTTPServer(this))
  , m_localServer(new LocalServer(this))
  , m_running(false)
{
  ui->setupUi(this);

  ui->checkDataToolButton->setIcon(QIcon::fromTheme(QLatin1String("document-save")));

  QSettings settings("SAMI_DVO_RAN", "rmo");
  ui->nameEdit->setText(settings.value("rmoServerName", "rmoserver").toString());
  ui->dataLineEdit->setText(settings.value("sourceDataPath",
#if defined(Q_OS_LINUX)
                                           "/tmp/rmoserver"
#else
                                           "C:\\tmp\\rmoserver"
#endif
                                           ).toString());

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

  QObject::connect(m_httpServer, &HTTPServer::pgasData, m_localServer, &LocalServer::pgasData);

  Server server(pgasServers);

  setTrayIconActions();
  showTrayIcon();
}


MainWindow::~MainWindow()
{
  on_stopButton_clicked();
}


void MainWindow::setPermission(bool permission)
{
  ui->nameEdit->setEnabled(permission);
  ui->checkNameToolButton->setEnabled(permission);
  ui->dataLineEdit->setEnabled(permission);
  ui->checkDataToolButton->setEnabled(permission);

  ui->startButton->setEnabled(permission);
  ui->stopButton->setEnabled(!permission);
}


void MainWindow::showTrayIcon()
{
  // Создаём экземпляр класса и задаём его свойства...
  m_trayIcon = new QSystemTrayIcon(this);
  QIcon trayImage(":/images/abc.png");
  m_trayIcon->setIcon(trayImage);
  m_trayIcon->setContextMenu(m_trayIconMenu);

  // Подключаем обработчик клика по иконке...
  connect(m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));

  // Выводим значок...
  m_trayIcon->show();
}


void MainWindow::showMinimized()
{
  QMainWindow::showMinimized();
  hide();
}


void MainWindow::trayActionExecute()
{
  if (windowState() == Qt::WindowMinimized)
  {
    showNormal();
  }
  else
  {
    showMinimized();
  }
}


void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
  switch (reason)
  {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
      trayActionExecute();
      break;
    default:
      break;
  }
}


void MainWindow::setTrayIconActions()
{
  // Setting actions...
  m_minimizeAction = new QAction("Свернуть", this);
  m_restoreAction = new QAction("Восстановить", this);
  m_quitAction = new QAction("Выход", this);

  // Connecting actions to slots...
  connect(m_minimizeAction, SIGNAL(triggered()), this, SLOT(showMinimized()));
  connect(m_restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));
  connect(m_quitAction, SIGNAL(triggered()), this, SLOT(close()));

  // Setting system tray's icon menu...
  m_trayIconMenu = new QMenu(this);
  m_trayIconMenu->addAction(m_minimizeAction);
  m_trayIconMenu->addAction(m_restoreAction);
  m_trayIconMenu->addAction(m_quitAction);
}


void MainWindow::closeEvent(QCloseEvent *e)
{
  if (m_running)
  {
    showNormal();
    if (QMessageBox::question(this, tr(""), tr("Отключить службу?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
    {
      e->ignore();
      return;
    }
  }

  e->accept();
}


void MainWindow::changeEvent(QEvent *event)
{
  QMainWindow::changeEvent(event);
  if (event->type() == QEvent::WindowStateChange)
  {
    if (isMinimized())
    {
      hide();
      m_restoreAction->setEnabled(true);
      m_minimizeAction->setEnabled(false);
    }
    else
    {
      m_restoreAction->setEnabled(false);
      m_minimizeAction->setEnabled(true);
    }
  }
}

void MainWindow::on_startButton_clicked()
{
  if (!m_httpServer->listen(2777))
  {
    QMessageBox::warning(this, tr("Ошибка"), tr("Ошибка запуска http server-а"), QMessageBox::Ok);
    on_stopButton_clicked();
    return;
  }

  QSettings settings("SAMI_DVO_RAN", "rmo");
  if (!m_localServer->listen(settings.value("rmoServerName", "rmoserver").toString()))
  {
    QMessageBox::warning(this, tr("Ошибка"), tr("Не удаётся запустить сервер"), QMessageBox::Ok);
    on_stopButton_clicked();
    return;
  }

  setPermission(false);
  m_running = true;
}


void MainWindow::on_stopButton_clicked()
{
  m_httpServer->close();
  m_localServer->close();

  setPermission(true);
  m_running = false;
}


void MainWindow::on_exitButton_clicked()
{
  close();
}


void MainWindow::on_checkNameToolButton_clicked()
{
  QString name = ui->nameEdit->text().trimmed();
  if (name.isEmpty())
  {
    QMessageBox::information(this, tr(""), tr("Введите имя службы"), QMessageBox::Ok);
    return;
  }

  QSettings settings("SAMI_DVO_RAN", "rmo");
  settings.setValue("rmoServerName", name);
}


void MainWindow::on_checkDataToolButton_clicked()
{
  QString sourceDataPath = ui->dataLineEdit->text();
  if (sourceDataPath.isEmpty())
  {
    QMessageBox::information(this, tr(""), tr("Введите путь к папке хранения данных"), QMessageBox::Ok);
    return;
  }

  QSettings settings("SAMI_DVO_RAN", "rmo");
  settings.setValue("sourceDataPath", sourceDataPath);
}
