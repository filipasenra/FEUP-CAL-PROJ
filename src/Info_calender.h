#ifndef _INFO_CALENDER_
#define _INFO_CALENDER_

#include "Spot.h"

class Info_calender{
private:
	Spot info;
	int start;
	int duration;

public:
	Info_calender(Spot info, int start, int duration){
		this->info = info;
		this->start = start;
		this->duration = duration;
	}
};

#endif
