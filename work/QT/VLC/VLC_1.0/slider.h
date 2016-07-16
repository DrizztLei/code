#ifndef SLIDER_H
#define SLIDER_H
#include <QSlider>

class Slider : public QSlider
{
public:
  Slider * getInstead();
private:
  Slider();
  static Slider * slider;
};

#endif // SLIDER_H
