#include "loginWidget.h"
#include <QApplication>
#include "connection.h"
#include "mainform.h"


int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  if(!createConnection())
    return 0;

  loginWidget loginForm;
  loginForm.show();
  loginForm.setWindowTitle(myWindowTitle);

  return a.exec();
}

void authHandler() {
    MainForm mainForm;
    mainForm.show();
}

