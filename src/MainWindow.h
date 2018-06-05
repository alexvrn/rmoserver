#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt
#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QMessageBox>

// Local
#include "Server.h"
#include "LocalServer.h"
#include "HTTPServer.h"

// UI
namespace Ui
{
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  protected:
    void closeEvent(QCloseEvent *e);

  private slots:
    void changeEvent(QEvent* event);
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void trayActionExecute();
    void setTrayIconActions();
    void showTrayIcon();

    void setPermission(bool permission);

    void on_startButton_clicked();

    void on_stopButton_clicked();

    void on_exitButton_clicked();

    void on_checkNameToolButton_clicked();

    void on_checkDataToolButton_clicked();

private:
    Ui::MainWindow *ui;

    HTTPServer* m_httpServer;
    LocalServer* m_localServer;

    bool m_running;

    QMenu* m_trayIconMenu;
    QAction* m_minimizeAction;
    QAction* m_restoreAction;
    QAction* m_quitAction;
    QSystemTrayIcon* m_trayIcon;
};

#endif // MAINWINDOW_H
