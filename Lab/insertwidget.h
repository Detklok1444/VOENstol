#ifndef INSERTWIDGET_H
#define INSERTWIDGET_H

#include <QWidget>
#include <QPushButton>

class insertWidget : public QWidget
{
  Q_OBJECT
public:
  explicit insertWidget(QWidget *parent = 0);

private:
  void createFormInterior();
  void clearLines();

  QPushButton *acceptButton;

signals:

public slots:

};

#endif // INSERTWIDGET_H
