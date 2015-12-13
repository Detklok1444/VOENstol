#include "sqldata.h"


SQLData::SQLData(QString firstName,
                 QString secondName,
                 QString patronymic,
                 QString birthDate,
                 QString birthPlace,
                 QString registration,
                 QString birthCertificate,
                 QString category)
{
  this->firstName = firstName;
  this->secondName = secondName;
  this->patronymic = patronymic;
  this->birthDate = birthDate;
  this->birthPlace = birthPlace;
  this->registration = registration;
  this->birthCertificate = birthCertificate;
  this->category = category;

}

QString SQLData::getFirstName() {
  return firstName;
}

QString SQLData::getSecondName() {
  return secondName;
}

QString SQLData::getPatronymic() {
  return patronymic;
}

QString SQLData::getBirthDate() {
  return birthDate;
}

QString SQLData::getBirthPlace() {
  return birthPlace;
}

QString SQLData::getRegistration() {
  return registration;
}

QString SQLData::getBirthCertificate() {
  return birthCertificate;
}

QString SQLData::getCategory() {
  return category;
}


