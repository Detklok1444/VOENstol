#include "insertdialog.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <sqldata.h>
#include <QDebug>
#include <QSqlError>
#include <QValidator>


insertDialog::insertDialog(QWidget *parent) :
  QDialog(parent)
{
  createFormInterior();
}

void insertDialog::createFormInterior() {
  QVBoxLayout *layout = new QVBoxLayout(this);

  firstNameLabel = new QLabel(tr("Имя"),this);
  firstNameLine = new QLineEdit(this);

  secondNameLabel = new QLabel(tr("Фамилия"), this);
  secondNameLine = new QLineEdit(this);

  patronymicLabel = new QLabel(tr("Отчество"), this);
  patronymicLine = new QLineEdit(this);

  birthdateLabel = new QLabel(tr("Дата рождения"), this);
  birthdateLine = new QDateEdit(this);

  birthPlaceLabel = new QLabel(tr("Место рождения"), this);
  birthPlaceLine = new QLineEdit(this);

  registrationLabel = new QLabel(tr("Прописка"), this);
  registrationLine = new QLineEdit(this);

  birthCertificateLabel = new QLabel(tr("№ Свид. о рожд."), this);
  birthCertificateLine = new QLineEdit(this);

  categoryLabel = new QLabel(tr("Категория годности"), this);
  categoryLine = new QLineEdit(this);

  layout->addWidget(firstNameLabel);
  layout->addWidget(firstNameLine);
  layout->addWidget(secondNameLabel);
  layout->addWidget(secondNameLine);
  layout->addWidget(patronymicLabel);
  layout->addWidget(patronymicLine);
  layout->addWidget(birthdateLabel);
  layout->addWidget(birthdateLine);
  layout->addWidget(birthPlaceLabel);
  layout->addWidget(birthPlaceLine);
  layout->addWidget(registrationLabel);
  layout->addWidget(registrationLine);
  layout->addWidget(birthCertificateLabel);
  layout->addWidget(birthCertificateLine);
  layout->addWidget(categoryLabel);
  layout->addWidget(categoryLine);

  QPushButton *acceptButton = new QPushButton(tr("Изменить") ,this);
  layout->addWidget(acceptButton);

  connect(acceptButton, SIGNAL(clicked()), this, SLOT(acceptHandler()));
  this->setLayout(layout);
}

void insertDialog::acceptHandler() {
  if(firstNameLine->text() != NULL &&
     secondNameLine->text() != NULL &&
     patronymicLine->text() != NULL &&
     birthdateLine->text() != NULL &&
     birthPlaceLine->text() != NULL &&
     registrationLine->text() != NULL &&
     birthCertificateLine->text() != NULL &&
     categoryLine->text() != NULL) {
      qDebug() << "Insert button clicked";
      QSqlQuery query;
      query.prepare("INSERT INTO recruits (first_name, last_name, patronymic, birthday, birth_place, registration, birth_certificate, category)"
                      " VALUES (:first_name, :last_name, :patronymic, :birthday, :birth_place, :registration, :birth_certificate, :category)");
      query.bindValue(":first_name", firstNameLine->text());
      query.bindValue(":last_name", secondNameLine->text());
      query.bindValue(":patronymic", patronymicLine->text());
      query.bindValue(":birthday", birthdateLine->text());
      query.bindValue(":birth_place", birthPlaceLine->text());
      query.bindValue(":registration", registrationLine->text());
      query.bindValue(":birth_certificate", birthCertificateLine->text().toInt());
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


