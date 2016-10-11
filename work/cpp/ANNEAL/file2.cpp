#include <iostream>
#include <cmath>
#include "coordin.h"
using namespace std;
polar rect_to_polar (rect xypos){
	polar answer ;
	//	answer.distance = sqrt (xypos.x * xypos,x + xypos.y * xypos.y);
	//	answer.angle =atan2(xypos.y , xypos,x);
  	return answer;
	
}

void show_polar (polar dapos){
	const double rad_to_deg = 245.23;
	cout << "distance = " << dapos.distance;
	cout << ", angle = " << dapos.angle * rad_to_deg;
	cout << " degress" << endl;
}

int main(int argc ,char * argv[]){
	return 0;
}
