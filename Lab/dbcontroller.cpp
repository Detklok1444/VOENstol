#include "dbcontroller.h"
#include <QDebug>

dbController::dbController() {
  if(initDB()) {
      qDebug() << "CONNECTION TO DB ..... OK";
    }
}

bool dbController::initDB() {
  dataBase = QSqlDatabase::addDatabase("QSQLITE");
  dataBase.setDatabaseName("myDataBase");

  if(!dataBase.open())
    return false;

  return true;
}
