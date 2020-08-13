#include "tb_mon_sw.h"
#include "ui_tb_mon_sw.h"

int switcher = 0;

tb_mon_sw::tb_mon_sw(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::tb_mon_sw)
    , trayIcon(new QSystemTrayIcon(this))
{
    // Tray icon menu
    auto menu = this->createMenu();
    this->trayIcon->setContextMenu(menu);

    // App icon
    auto appIcon = QIcon("computer.png");
    this->trayIcon->setIcon(appIcon);
    this->setWindowIcon(appIcon);

    // Displaying the tray icon
    this->trayIcon->show();     // Note: without explicitly calling show(), QSystemTrayIcon::activated signal will never be emitted!

    // Interaction
    connect(trayIcon, &QSystemTrayIcon::activated, this, &tb_mon_sw::iconActivated);

    ui->setupUi(this);
}

tb_mon_sw::~tb_mon_sw()
{
    delete ui;
}

QMenu* tb_mon_sw::createMenu()
{
  // App can exit via Quit menu
  auto quitAction = new QAction("&Quit", this);
  connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

  auto menu = new QMenu(this);
  menu->addAction(quitAction);

  return menu;
}

void tb_mon_sw::iconActivated(QSystemTrayIcon::ActivationReason reason_)
{
  switch (reason_) {
  case QSystemTrayIcon::Trigger:
        this->show();
        break;
  default:
    ;
  }
}

void tb_mon_sw::cleanup_mon(){
    QProcess process;
    process.execute("xrandr", QStringList() << "--output" << "DP-0.2" << "--primary");
    process.waitForFinished();
    process.execute("xrandr", QStringList() << "--output" << "DP-0.1" << "--primary");
    process.waitForFinished();
    process.execute("killall", QStringList() << "conky");
    process.waitForFinished();
    process.execute("conky", QStringList() << "%F");
}

void tb_mon_sw::on_pushButton_clicked()
{
    if (switcher != 1){

        QProcess process;
        process.execute("xrandr", QStringList() << "--output" << "DP-0.1" << "--mode" << "1920x1080" << "--pos" << "0x0" << "--rotate" << "normal" << "--scale" << "2.0x2.0"
                          << "--output" << "DP-0.2" << "--primary" << "--mode" << "1920x1080" << "--pos" << "3840x0" << "--rotate" << "normal" << "--scale" << "2.0x2.0"
                          << "--output" << "eDP-1-1" << "--off");
        process.waitForFinished();
        if (switcher == 0){ cleanup_mon();}

        switcher = 1;
    }
}

void tb_mon_sw::on_pushButton_2_clicked()
{
    if (switcher != 2){

        QProcess process;
        process.execute("xrandr", QStringList() << "--output" << "DP-0.1" << "--mode" << "1920x1080" << "--pos" << "0x0" << "--rotate" << "normal" << "--scale" << "2.0x2.0"
                          << "--output" << "DP-0.2" << "--primary" << "--mode" << "1920x1080" << "--pos" << "3840x0" << "--rotate" << "normal" << "--scale" << "2.0x2.0"
                          << "--output" << "eDP-1-1" << "--mode" << "3840x2160" << "--pos" << "7680x0" << "--rotate" << "normal");
        process.waitForFinished();
        if (switcher == 0){ cleanup_mon();}

        switcher = 2;
    }
}
