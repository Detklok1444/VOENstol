

#include "loginWidget.h"

#include <QApplication>
#include <QtSql>
#include <QMessageBox>

loginWidget::loginWidget(QWidget *parent)
  : QWidget(parent) {
  createFormInterior();
}

loginWidget::~loginWidget() {

}

void loginWidget::createFormInterior() {
  QVBoxLayout *layout = new QVBoxLayout(this);

  loginLabel = new QLabel(this);
  loginLabel->setText(tr("Логин"));
  loginLabel->setAlignment(Qt::AlignCenter);
  passwordLabel = new QLabel(this);
  passwordLabel->setText(tr("Пароль"));
  passwordLabel->setAlignment(Qt::AlignCenter);
  loginField = new QLineEdit(this);
  passwordField = new QLineEdit(this);
  passwordField->setEchoMode(QLineEdit::Password);
  loginButton = new QPushButton(this);
  loginButton->setText(tr("Войти"));
  loginButton->setDefault(true);

  layout->addWidget(loginLabel);
  layout->addWidget(loginField);
  layout->addWidget(passwordLabel);
  layout->addWidget(passwordField);
  layout->addWidget(loginButton);

  connect(loginButton, SIGNAL(pressed()), this, SLOT(tryEnter()));
}

void loginWidget::tryEnter() {
  if(loginField->text() == NULL && passwordField->text() == NULL) //Check for null data
    return void();

  QSqlQuery query("SELECT * from logpass");
  QSqlRecord rec;
  rec = query.record();

  bool isLoginPass = false;
  /* Search user data in DB */
  while(query.next()) {
      if(loginField->text() == query.value(rec.indexOf("login")).toString()  &&
         passwordField->text() == query.value(rec.indexOf("password")).toString()) {
          qDebug() << "Login";
          isLoginPass = true;
          mainForm = new MainForm();
          mainForm->show();
          this->close();
        }
    }

  if(!isLoginPass) { // if doesn't login
      QMessageBox::critical(0, qApp->tr("Login error"),
                 qApp->tr("Incorrect login or password."), QMessageBox::Cancel);
    }

}
