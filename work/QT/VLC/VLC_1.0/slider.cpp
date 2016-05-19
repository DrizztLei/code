#include "slider.h"

Slider * Slider::slider = NULL;

Slider::Slider(){}

Slider * Slider::getInstead(){
  if(Slider::slider == NULL){
      slider = new Slider();
    }
  return slider;
}
