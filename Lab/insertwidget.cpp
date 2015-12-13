#include "insertwidget.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

insertWidget::insertWidget(QWidget *parent) : QWidget(parent) {

  this->setWindowModality(Qt::WindowModal);

  createFormInterior();
  this->hide();
}

void insertWidget::createFormInterior() {
  QVBoxLayout *layout = new QVBoxLayout(this);

  QLabel *firstNameLabel = new QLabel(tr("Имя"),this);
  QLineEdit *firstNameLine = new QLineEdit(tr("Имя"), this);

  QLabel *secondNameLabel = new QLabel(tr("Фамилия"), this);
  QLineEdit *secondNameLine = new QLineEdit(tr("Фамилия"), this);

  layout->addWidget(firstNameLabel);
  layout->addWidget(firstNameLine);

  layout->addWidget(secondNameLabel);
  layout->addWidget(secondNameLine);

  this->setLayout(layout);
}
