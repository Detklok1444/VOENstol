#ifndef INSERTDIALOG_H
#define INSERTDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlRecord>

class insertDialog : public QDialog{
  Q_OBJECT
public:
  insertDialog(QWidget *parent);
private slots:
    void acceptHandler();
private:

  void virtual createFormInterior();

  QLabel *firstNameLabel;
  QLineEdit *firstNameLine;
  QLabel *secondNameLabel;
  QLineEdit *secondNameLine;
  QLabel *patronymicLabel;
  QLineEdit *patronymicLine;
  QLabel *birthdateLabel;
  QDateEdit *birthdateLine;
  QLabel *birthPlaceLabel;
  QLineEdit *birthPlaceLine;
  QLabel *registrationLabel;
  QLineEdit *registrationLine;
  QLabel *birthCertificateLabel;
  QLineEdit *birthCertificateLine;
  QLabel *categoryLabel;
  QLineEdit *categoryLine;

signals:
  void acceptButton();

};

#endif // INSERTDIALOG_H
