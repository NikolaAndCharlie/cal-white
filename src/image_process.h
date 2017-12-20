#ifndef _IMAGEPROCESS_
#define _IMAGEPROCESS_
#include "image_view.h"

#include <HalconCpp.h>
#include <QString>
class ImageProcess
{
public:
  ImageProcess();
  ~ImageProcess();
  void CloseAll();
  double CalculationRadio(QString n,ImageView*v);
private:
  bool is_processed_;

};



#endif
