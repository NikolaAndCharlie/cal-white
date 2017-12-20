#ifndef IMAGE_VIEW_H
#define IMAGE_VIEW_H
#include <iostream>
#include<qwidget.h>
#include<qimage.h>
#include <opencv2/opencv.hpp>
using namespace std;

class ImageView :public QWidget
{
  Q_OBJECT
public:
  ImageView(QWidget* parent = 0);
  ~ImageView();
  void GainNumberPosition(vector<cv::Vec4i>line_position);
  void SetImage(unsigned char* data, int w, int h);

protected:
  void paintEvent(QPaintEvent* event);

private:
  void UpdateCachedImage();
  int imageWidth_;
  int imageHeight_;
  int allocSize_;
  unsigned char *imageData_;
  QImage cachedImage_;
  vector<cv::Vec4i>line_start_position_;
};

#endif // !IMAGE_VIEW_H
