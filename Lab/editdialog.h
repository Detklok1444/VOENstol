#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlRecord>

class editDialog : public QDialog {
  Q_OBJECT
public:
  editDialog(QWidget *parent, int primaryKey);
private slots:
    void acceptHandler();
private:

  void createFormInterior();

  int primaryKey;
  QLabel *firstNameLabel;
  QLineEdit *firstNameLine;
  QLabel *secondNameLabel;
  QLineEdit *secondNameLine;
  QLabel *patronymicLabel;
  QLineEdit *patronymicLine;
  QLabel *birthdayLabel;
  QDateEdit *birthdayLine;
  QLabel *birthPlaceLabel;
  QLineEdit *birthPlaceLine;
  QLabel *registrationLabel;
  QLineEdit *registrationLine;
  QLabel *categoryLabel;
  QLineEdit *categoryLine;

signals:
  void acceptButton();

};

#endif // INSERTDIALOG_H
