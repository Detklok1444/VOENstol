#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QtSql>
#include <QDir>
#include <QDebug>

static bool createConnection() {
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  QString pathToDB = QDir::currentPath()+QString("/Data/db.sqlite");
  db.setDatabaseName(pathToDB);
  qDebug() << pathToDB;

  QFileInfo checkFile(pathToDB);
  if(checkFile.isFile()) {
    if(!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                   qApp->tr("Unable to establish a database connection.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
               return false;
    }
  } else {
      QMessageBox::critical(0, qApp->tr("Cannot open database"),
                 qApp->tr("Database file doesnt exist.\n"), QMessageBox::Cancel);
             return false;
    }

  return true;
}

#endif // CONNECTION_H

