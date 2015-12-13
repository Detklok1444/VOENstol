#ifndef DBCONTROLLER
#define DBCONTROLLER

#include<QtSql/QSql>

/*This class use a Singleton pattern*/
class dbController {

private:

  QSqlDatabase dataBase;

  dbController();
  dbController(const dbController&);
  dbController& operator=(dbController&);

  bool initDB();


public:
  static dbController& getInstance() {
    static dbController _instance;
    return _instance;
  }
};

#endif // DBCONTROLLER

