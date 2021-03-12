#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->imgLabel->setScaledContents(true);
    resize(ui->imgLabel->width(), ui->imgLabel->height());
    setFixedSize(width(), height());
    setWindowTitle("驾校科目一考试登录");
    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginBtn_clicked()
{
    QRegExp rx("^[A-Za-z0-9]+([_\.][A-Za-z0-9]+)*@([A-Za-z0-9\-]+\.)+[A-Za-z]{2,6}$");

    bool res = rx.exactMatch(ui->accountEdit->text());
    if (!res) {
        QMessageBox::information(this, "提示", "非法的邮箱地址, 请你重新输入");
        ui->accountEdit->clear();
        ui->codeEdit->clear();
        ui->accountEdit->setFocus();
        return;
    } else {
        QString filename; //账号密码数据文件
        QString strAccInput; //用户输入的账号
        QString strCode; //用户输入的密码
        QString strLine; //每次读取一行数据
        QStringList strList; //保存分割读取的一行数据

        filename = "../account.txt";
        strAccInput = ui->accountEdit->text();
        strCode = ui->codeEdit->text();

        QFile file(filename);
        QTextStream stream(&file);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            while (!stream.atEnd()) {
                strLine = stream.readLine();
                strList = strLine.split(",");
                if (strAccInput == strList.at(0)) { //账号
                    if (strCode == strList.at(1)) { //密码
                        QMessageBox::information(this, "提示", "欢迎进入科目一考试系统!");
                        file.close();
                        done(Accepted);
                        return;
                    } else {
                        QMessageBox::information(this, "提示", "您输入的密码有误, 请重新输入!");
                        ui->codeEdit->clear();
                        ui->codeEdit->setFocus();
                        file.close();
                        return;
                    }
                }

                QMessageBox::information(this, "提示", "您输入的账号有误请重新输入!");
                ui->accountEdit->clear();
                ui->codeEdit->clear();
                ui->accountEdit->setFocus();
                file.close();
                return;
            }
        } else {
            QMessageBox::information(this, "提示", "读取账号数据文件失败!");
            return;
        }
    }
}

void LoginDialog::on_cancelBtn_clicked()
{
    done(Rejected);
}
