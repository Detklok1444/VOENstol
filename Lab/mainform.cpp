#include "mainform.h"

#include <QPushButton>
#include <QWidget>
#include <QMainWindow>
#include <QSqlTableModel>
#include <QHeaderView>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMenuBar>
#include <QDebug>
#include <QSqlError>
#include <QFile>
#include <QModelIndex>
#include <QDir>
#include <QTextBrowser>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>


MainForm::MainForm(QWidget *parent)
  :QMainWindow(parent) {

  this->setWindowTitle(myWindowTitle);
  this->setMinimumSize(QSize(1024, 480));
  createActions();
  createToolBars();
  createMenuBars();
  createTableView();
}

MainForm::~MainForm() {

}

/* Database structure :
        first_name,
        last_name,
        patronymic,
        birthday,
        birth_place,
        registration,
        birth_certificate,
        category.         */

void MainForm::createTableView() {
  /* Create model of table */
  model = new QSqlTableModel(this);
  model->setTable("recruits");
  model->setEditStrategy(QSqlTableModel::OnManualSubmit);
  model->setHeaderData(0, Qt::Horizontal, tr("Имя"));
  model->setHeaderData(1, Qt::Horizontal, tr("Фамилия"));
  model->setHeaderData(2, Qt::Horizontal, tr("Отчество"));
  model->setHeaderData(3, Qt::Horizontal, tr("Дата рождения"));
  model->setHeaderData(4, Qt::Horizontal, tr("Место рождения"));
  model->setHeaderData(5, Qt::Horizontal, tr("Прописка"));
  model->setHeaderData(6, Qt::Horizontal, tr("№ Свид. о рожд."));
  model->setHeaderData(7, Qt::Horizontal, tr("Категория годности"));
  if(!model->select()) {
    QMessageBox::critical(0, tr("Error"),
               tr("Cannot create a table model.\n"), QMessageBox::Cancel);
    this->close();
  }


  /* Create table view */
  QHBoxLayout *layout = new QHBoxLayout(this);
  tableView = new QTableView(this);
  tableView->setModel(model);
  tableView->setSortingEnabled(true);
  tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
  tableView->setMinimumSize(QSize(1024, 480));
  tableView->resizeColumnsToContents();
  tableView->horizontalHeader()->setStretchLastSection(true);
  tableView->setContextMenuPolicy(Qt::CustomContextMenu); // Add a custom context menu policy
  tableView->show();

  layout->addWidget(tableView);
  this->setLayout(layout);
  this->setCentralWidget(tableView);

  connect(tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuHandler(QPoint)));
  connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(editRecord()));
}

void MainForm::createToolBars() {
  fileToolBar = new QToolBar(tr("Toolbar"), this);
  fileToolBar->addAction(createAct);
  fileToolBar->addAction(editAct);
  fileToolBar->addAction(deleteAct);
  fileToolBar->addAction(printAct);
  addToolBar(fileToolBar);
}

void MainForm::createActions() {
  createAct = new QAction(QIcon(":Icons/addIcon.png"),tr("&Добавить"), this);
  createAct->setShortcuts(QKeySequence::New);
  createAct->setStatusTip(tr("Добавить новую запись"));
  connect(createAct, SIGNAL(triggered(bool)), this, SLOT(createRecord()));

  editAct = new QAction(QIcon(":Icons/editIcon.png"), tr("&Редактировать"), this);
  editAct->setShortcut(QKeySequence::Redo);
  editAct->setStatusTip(tr("Редактировать запись"));
  connect(editAct, SIGNAL(triggered(bool)), this, SLOT(editRecord()));

  deleteAct = new QAction(QIcon(":Icons/deleteIcon.png"), tr("&Удалить"), this);
  deleteAct->setShortcut(QKeySequence::Delete);
  deleteAct->setStatusTip(tr("Удалить запись"));
  connect(deleteAct, SIGNAL(triggered(bool)), this, SLOT(deleteRecord()));

  printAct = new QAction(QIcon(":Icons/printIcon"), tr("&Печать"), this);
  printAct->setShortcut(QKeySequence::Print);
  printAct->setStatusTip(tr("Печать"));
  connect(printAct, SIGNAL(triggered(bool)), this, SLOT(printRecord()));

  exitAct = new QAction(tr("&Выход"), this);
  exitAct->setShortcut(QKeySequence::Close);
  connect(exitAct, SIGNAL(triggered(bool)), this, SLOT(close()));


}

/* Insert event handler */
void MainForm::createRecord() {
  insertDialog insertWindow (this);
  insertWindow.setModal(true);
  if (insertWindow.exec() == QDialog::Accepted) {
      qDebug() << "insert == true";
      model->submitAll();
  }
}

void MainForm::createMenuBars() {
  QMenu *fileMenu = menuBar()->addMenu(tr("&Файл"));;
  fileMenu->addAction(createAct);
  fileMenu->addAction(editAct);
  fileMenu->addAction(deleteAct);
  fileMenu->addAction(printAct);
  fileMenu->addSeparator();
  fileMenu->addAction(exitAct);

}

/* Create HTML file document from tableView */
bool MainForm::createHtmlTable() {
  QString htmlFile;
  QTextStream out(&htmlFile);

  const int rowCount = tableView->model()->rowCount();
  const int columnCount = tableView->model()->columnCount();

  const QString refTitleName("Призывники");

  out <<  "<html>\n"
                  "<head>\n"
                  "<meta Content=\"Text/html; charset=Windows-1251\">\n"
              <<  QString("<title>%1</title>\n").arg(refTitleName)
              <<  "</head>\n"
                  "<body bgcolor=#ffffff link=#5000A0>\n"
                  "<table border=1 cellspacing=0 cellpadding=2>\n";

  //Headers
  out << "<tr bgcolor=#f0f0f0>";
  for (int column = 0; column < columnCount; column++)
       if (!tableView->isColumnHidden(column))
           out << QString("<th>%1</th>").arg(tableView->model()->headerData(column, Qt::Horizontal).toString());
   out << "</tr>\n";


   // data table
   for (int row = 0; row < rowCount; row++) {
       out << "<tr>";
       for (int column = 0; column < columnCount; column++) {
           if (!tableView->isColumnHidden(column)) {
               QString data = tableView->model()->data(tableView->model()->index(row, column)).toString().simplified();
               out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
           }
       }
       out << "</tr>\n";
   }
   out <<  "</table>\n"
       "</body>\n"
       "</html>\n";

   QTextDocument *document = new QTextDocument();
       document->setHtml(htmlFile);

       QPrinter printer;

       QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
       if (dialog->exec() == QDialog::Accepted) {
           document->print(&printer);
       }

       delete document;

   return true;

}

void MainForm::editRecord() {
     QModelIndex index = tableView->model()->index(tableView->currentIndex().row(), 6, QModelIndex()); // index of birth_certificate in current row
     int primaryKey = tableView->model()->data(index).toInt();
     editDialog editWindow(this, primaryKey);
     editWindow.setModal(true);

     if(editWindow.exec() == QDialog::Accepted) {
         model->submitAll();
       }
}

/* Delete record from DB */
void MainForm::deleteRecord() {
  qDebug() << "in delete record";

  QSqlQuery query;
  QModelIndex index = tableView->model()->index(tableView->currentIndex().row(), 6, QModelIndex()); // index of birth_certificate in current row
  query.prepare("DELETE FROM recruits "
                "WHERE birth_certificate = :birth_certificate");
  query.bindValue(":birth_certificate", tableView->model()->data(index).toInt());

  QMessageBox msgBox;
  msgBox.setWindowTitle(tr("Удалить"));
  msgBox.setText(tr("Вы действительно хотите удалить запись?"));
  msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
  msgBox.setDefaultButton(QMessageBox::No);
  int answer = msgBox.exec();
  if(answer == QMessageBox::No)
    return void();

  if(!query.exec())
    qDebug() << query.lastError().text();

  model->submitAll();
}

/* Print records from table */
void MainForm::printRecord() {
  createHtmlTable();
}

/* Context menu handler */
void MainForm::contextMenuHandler(QPoint pos) {
  QMenu *menu = new QMenu(this);

  menu->addAction(editAct);
  menu->addAction(deleteAct);

  menu->popup(tableView->viewport()->mapToGlobal(pos));
}
