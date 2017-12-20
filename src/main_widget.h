#ifndef _MainWidget_H_
#define _MainWidget_H_
#include "image_view.h"
#include "image_process.h"
#include <QWidget>
#include <QLabel>
#include <QObject>
#include <QPushButton>


class MainWidget:public QWidget
{
  Q_OBJECT;
public:
  MainWidget();
  ~MainWidget();

private:
  void SetUi();
  void SetConnect();
  ImageView *image_view_;
  ImageProcess *image_process_;
  QLabel *result_label_;
  QString image_path_file_;
  QPushButton *load_image_push_button_;
  QPushButton *calculation_push_button_;
  double ratio_;
  void LoadImage();
  void calculation();
  void GetResult(double r);
};




#endif
