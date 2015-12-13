#ifndef SQLDATA_H
#define SQLDATA_H

#include <QString>

class SQLData {
public:
  SQLData(QString firstName,
          QString secondName,
          QString patronymic,
          QString birthDate,
          QString birthPlace,
          QString registration,
          QString birthCertificate,
          QString category);
private:
  QString firstName;
  QString secondName;
  QString patronymic;
  QString birthDate;
  QString birthPlace;
  QString registration;
  QString birthCertificate;
  QString category;

  QString getFirstName();
  QString getSecondName();
  QString getPatronymic();
  QString getBirthDate();
  QString getBirthPlace();
  QString getRegistration();
  QString getBirthCertificate();
  QString getCategory();
};

#endif // SQLDATA_H
