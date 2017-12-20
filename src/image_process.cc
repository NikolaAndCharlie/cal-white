#include "image_process.h"
#include <HalconCpp.h>
#include <iostream>
#include <QString>

using namespace HalconCpp;

ImageProcess::ImageProcess()
             :is_processed_(false)
{
  
}

ImageProcess::~ImageProcess()
{

}

void ImageProcess::CloseAll()
{
  if(is_processed_)
  {
    if(HDevWindowStack::IsOpen())
    {
      HDevWindowStack::CloseAll();
    }
  }
}

double ImageProcess::CalculationRadio(QString n,ImageView *v)
{
  if(n.isEmpty())
  {
    return -1.0;
  }
  is_processed_ = true;
  HTuple image_file;
  std::string image_file_string;
  image_file_string = n.toStdString();
  image_file = image_file_string.c_str();
  HObject image;
  ReadImage(&image,image_file);

  HObject image_red,image_green,image_blue;
  Decompose3(image,&image_red,&image_green,&image_blue);

  HObject region;
  Threshold(image_red,&region,150,255);
  Hlong winID = (Hlong)v->winId();
  HTuple hv_windowId;
  SetWindowAttr("background_color","black");
  OpenWindow(0,0,900,500,winID,"","",&hv_windowId);
  HDevWindowStack::Push(hv_windowId);
  SetColor(hv_windowId,"red");
 if(HDevWindowStack::IsOpen())
  {
    DispObj(region,HDevWindowStack::GetActive());
  }
  HTuple width, height;
  GetImageSize(image,&width,&height);

  HObject connected_region;
  Connection(region,&connected_region);
  
  HTuple area_vector,row_vector,col_vector;
  AreaCenter(connected_region,&area_vector,&row_vector,&col_vector);

  HTuple sum;
  TupleSum(area_vector,&sum);

  HTuple total;
  total = width*height;

  HTuple ratio;
  TupleDiv(total,1.0,&total);
  TupleDiv(sum,total,&ratio);
  return ratio.D();

}
