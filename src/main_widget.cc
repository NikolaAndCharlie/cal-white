#include "main_widget.h"
#include <HalconCpp.h>
#include <QVBoxLayout>
#include <QString>
#include <QGroupBox>
#include <QLabel>
#include <QTextCodec>
#include <QPushButton>
#include <qgenericmatrix.h>
#include <opencv2/core.hpp>
#include <qfiledialog.h>

using namespace cv;
using namespace HalconCpp;

MainWidget::MainWidget()
{
  SetUi();
  SetConnect();
}

MainWidget::~MainWidget()
{

}

void MainWidget::SetUi()
{
  image_process_ = new ImageProcess;

  QHBoxLayout *main_layout = new QHBoxLayout;
  QVBoxLayout *right_layout = new QVBoxLayout;

  image_view_ = new ImageView;
  
  load_image_push_button_ = new QPushButton;
  load_image_push_button_->setText(tr("Load"));
  calculation_push_button_ = new QPushButton;
  calculation_push_button_->setText(tr("calculation"));
  
  result_label_ = new QLabel;
  result_label_->setAlignment(Qt::AlignHCenter);
  result_label_->setText(tr("NULL"));
  result_label_->setBackgroundRole(QPalette::Window);
 // result_label_->setStyleSheet("QLabel{background-color:rgb(255,255,255)}");


  QGroupBox *result_box = new QGroupBox;
  result_box->setTitle(tr("the ratio for white zone"));
  result_box->setMinimumSize(20,30);
  QVBoxLayout *result_layout = new QVBoxLayout;
  result_layout->addWidget(result_label_);
  result_box->setLayout(result_layout);



  right_layout->addWidget(load_image_push_button_);
  right_layout->addWidget(calculation_push_button_);
  right_layout->addStretch(1);
  right_layout->addWidget(result_box);;
  right_layout->addStretch(3);
  
  main_layout->addWidget(image_view_);
  main_layout->addLayout(right_layout);
  main_layout->setStretchFactor(image_view_,8);
  main_layout->setStretchFactor(right_layout,2);

  this->setLayout(main_layout);
  this->setMinimumSize(900,500);

}

void MainWidget::SetConnect()
{
  connect(load_image_push_button_,&QPushButton::clicked,[&]()
  {
    LoadImage();
  });
  connect(calculation_push_button_,&QPushButton::clicked,[&]()
  {
    calculation();
  });
}

void MainWidget::LoadImage()
{


  QString image_path = QFileDialog::getOpenFileName(this,tr("Get image file path"),".",
    "Images(*.png *.tif *.jpg)");

  image_path_file_ = image_path;

  QTextCodec *code = QTextCodec::codecForName("gb2312");
  std::string filename = code->fromUnicode(image_path).data();
  
  cv::Mat src = cv::imread(filename);
  

  if(src.empty() ||src.channels() == CV_8UC1)
  {
    return ;
  }
  Mat dst;
  cvtColor(src,dst,CV_RGB2GRAY);
  image_process_->CloseAll();
  image_view_->SetImage(dst.data,dst.cols,dst.rows);

}

void MainWidget::calculation()
{
  ratio_ = image_process_->CalculationRadio(image_path_file_,image_view_);
  GetResult(ratio_);
}

void MainWidget::GetResult(double r)
{
  QString s = QString::number(r*100)+"%";
  result_label_->setText(s);
}


