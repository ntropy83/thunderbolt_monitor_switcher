#ifndef TB_MON_SW_H
#define TB_MON_SW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QProcess>
#include <QRect>

QT_BEGIN_NAMESPACE
namespace Ui { class tb_mon_sw; }
QT_END_NAMESPACE

class tb_mon_sw : public QMainWindow
{
    Q_OBJECT

public:
    tb_mon_sw(QWidget *parent = nullptr);
    ~tb_mon_sw();

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    void cleanup_mon();

    Ui::tb_mon_sw *ui;
    QSystemTrayIcon* trayIcon;
    QMenu* trayIconMenu;

    QMenu* createMenu();
};
#endif // TB_MON_SW_H
