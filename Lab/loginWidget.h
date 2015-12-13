#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "mainform.h"

class loginWidget : public QWidget {
  Q_OBJECT

public:
  loginWidget(QWidget *parent = 0);
  ~loginWidget();
private:
  MainForm *mainForm;
  QLabel *loginLabel;
  QLabel *passwordLabel;
  QLineEdit *loginField;
  QLineEdit *passwordField;
  QPushButton *loginButton;

  void createFormInterior();

private slots:
  void tryEnter();

signals:
  void authIsOk();
};

#endif // LOGINWIDGET_H
