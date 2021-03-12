#include "logindialog.h"
#include "examdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDialog logDialog;
    int res = logDialog.exec();
    if (res == QDialog::Accepted) {
        examdialog* examDialog;
        examDialog = new examdialog;
    } else {
        return 0;
    }

    return a.exec(); //应用程序(object)进入消息循环
}
