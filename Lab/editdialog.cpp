#include "editdialog.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QDate>
#include <QDebug>
#include <QDateTime>
#include <QSqlError>


editDialog::editDialog(QWidget *parent, int primaryKey) :
  QDialog(parent)
{
  this->primaryKey = primaryKey;
  createFormInterior();
}

void editDialog::createFormInterior() {

  QVBoxLayout *layout = new QVBoxLayout(this);

  firstNameLabel = new QLabel(tr("Имя"),this);
  firstNameLine = new QLineEdit(this);

  secondNameLabel = new QLabel(tr("Фамилия"), this);
  secondNameLine = new QLineEdit(this);

  patronymicLabel = new QLabel(tr("Отчество"), this);
  patronymicLine = new QLineEdit(this);

  birthdayLabel = new QLabel(tr("Дата рождения"), this);
  birthdayLine = new QDateEdit(this);
  birthdayLine->setCalendarPopup(true);
  QString format("yyyy-dd-MM");
  birthdayLine->setMinimumDate(QDate(1900, 0, 0));
  birthdayLine->setDisplayFormat(format);

  birthPlaceLabel = new QLabel(tr("Место рождения"), this);
  birthPlaceLine = new QLineEdit(this);

  registrationLabel = new QLabel(tr("Прописка"), this);
  registrationLine = new QLineEdit(this);

  categoryLabel = new QLabel(tr("Категория годности"), this);
  categoryLine = new QLineEdit(this);

  layout->addWidget(firstNameLabel);
  layout->addWidget(firstNameLine);
  layout->addWidget(secondNameLabel);
  layout->addWidget(secondNameLine);
  layout->addWidget(patronymicLabel);
  layout->addWidget(patronymicLine);
  layout->addWidget(birthdayLabel);
  layout->addWidget(birthdayLine);
  layout->addWidget(birthPlaceLabel);
  layout->addWidget(birthPlaceLine);
  layout->addWidget(registrationLabel);
  layout->addWidget(registrationLine);
  layout->addWidget(categoryLabel);
  layout->addWidget(categoryLine);

  /* Add text to widgets */
  QString primaryKeyStr = QString::number(this->primaryKey);
  QSqlQuery query;

  query.exec(QString("SELECT * FROM recruits WHERE birth_certificate = %1").arg(primaryKeyStr));

  while(query.next()) {
  firstNameLine->setText(query.value(0).toString());
  secondNameLine->setText(query.value(1).toString());
  patronymicLine->setText(query.value(2).toString());
  birthdayLine->setDate(query.value(3).toDate());
  birthPlaceLine->setText(query.value(4).toString());
  registrationLine->setText(query.value(5).toString());
  categoryLine->setText(query.value(7).toString());
  }
  qDebug() << "Primary key: " << this->primaryKey;
  qDebug() << query.lastError().text();
  QPushButton *acceptButton = new QPushButton(tr("Изменить") ,this);

  layout->addWidget(acceptButton);

  connect(acceptButton, SIGNAL(clicked()), this, SLOT(acceptHandler()));
  this->setLayout(layout);
}

void editDialog::acceptHandler() {
  if(firstNameLine->text() != NULL &&
     secondNameLine->text() != NULL &&
     patronymicLine->text() != NULL &&
     birthdayLine->text() != NULL &&
     birthPlaceLine->text() != NULL &&
     registrationLine->text() != NULL &&
     categoryLine->text() != NULL) {
      qDebug() << "Insert button clicked";
      QSqlQuery query;
      query.prepare("UPDATE recruits  SET first_name = :first_name, last_name = :last_name, patronymic = :patronymic, birthday = :birthday, birth_place = :birth_place, registration = :registration, category = :category"
                      " WHERE birth_certificate = :birth_certificate");
      query.bindValue(":first_name", firstNameLine->text());
      query.bindValue(":last_name", secondNameLine->text());
      query.bindValue(":patronymic", patronymicLine->text());
      query.bindValue(":birthday", birthdayLine->date());
      query.bindValue(":birth_place", birthPlaceLine->text());
      query.bindValue(":registration", registrationLine->text());
      query.bindValue(":birth_certificate", primaryKey);
      query.bindValue(":category", categoryLine->text());
      if(!query.exec())
        qDebug() << query.lastError().text();

      this->setResult(QDialog::Accepted);
      this->accept();
      this->close();
    }
  else {
      QMessageBox::critical(0, tr("Error"),
                 tr("Заполните все поля!\n"), QMessageBox::Cancel);
    }
}


