#ifndef COORDIN_H_
#define COORDIN_H_

struct polar{double distance , angle;};

struct rect{double x , y ;};

polar rect_to_polar(rect temp);

void show_polar(polar temp);

#endif
