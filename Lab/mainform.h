#ifndef MAINFORM_H
#define MAINFORM_H

#include <QToolBar>
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QSqlTableModel>
#include <QPoint>
#include <QTableView>
#include "insertdialog.h"
#include "editdialog.h"

const QString myWindowTitle = "ВОЕННО-УЧЕТНЫЙ СТОЛ";

class MainForm : public QMainWindow {
  Q_OBJECT

public:
  MainForm(QWidget *parent = 0);
  ~MainForm();

private:
  QToolBar *fileToolBar;

  QAction *createAct;
  QAction *editAct;
  QAction *deleteAct;
  QAction *printAct;
  QAction *exitAct;

  QSqlTableModel *model;
  QTableView *tableView;

  void createTableView();
  void createToolBars();
  void createActions();
  void createMenuBars();

  bool createHtmlTable();

private slots:
  void createRecord();
  void editRecord();
  void deleteRecord();
  void printRecord();
  void contextMenuHandler(QPoint);
};

#endif // MAINFORM_H

