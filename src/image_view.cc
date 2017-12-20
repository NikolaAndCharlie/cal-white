#include "image_view.h"
#include <QtWidgets>

#pragma execution_character_set("utf-8")
ImageView::ImageView(QWidget *parent)
  : QWidget(parent)
  , imageWidth_(0)
  , imageHeight_(0)
  , allocSize_(0)
  , imageData_(nullptr)

{
}

ImageView::~ImageView()
{
  if (imageData_)
  {
    delete[]imageData_;
  }
}

void ImageView::GainNumberPosition(vector<cv::Vec4i>line_position)
{
 line_start_position_ = line_position;
}

void ImageView::SetImage(unsigned char *data, int w, int h)
{
  if (w * h > allocSize_)
  {
    if (imageData_ != nullptr)
    {
      delete[]imageData_;
    }
    imageData_ = new unsigned char[w * h];
    allocSize_ = w * h;
  }

  imageWidth_ = w;
  imageHeight_ = h;
  memcpy(imageData_, data, w * h);

  UpdateCachedImage();
}

void ImageView::UpdateCachedImage()
{
  QImage image(imageData_, imageWidth_, imageHeight_, imageWidth_, QImage::Format_Indexed8);
  for (int i = 0; i < 256; ++i)
  {
    image.setColor(i, qRgb(i, i, i));
  }
  cachedImage_ = image.scaledToHeight(484, Qt::SmoothTransformation);
  update();
}

void ImageView::paintEvent(QPaintEvent *e)
{

  QPainter g(this);
  QPen p(Qt::green);
  g.setFont(QFont("Î¢ÈíÑÅºÚ", 20));

  if (cachedImage_.isNull())
  {
    g.setBrush(Qt::white);
    g.drawRect(this->rect());
  }

  if (!cachedImage_.isNull())
  {
    g.drawImage(0, 0, cachedImage_);
  }


}
