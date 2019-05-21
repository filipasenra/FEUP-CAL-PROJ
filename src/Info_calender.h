#ifndef _INFO_CALENDER_
#define _INFO_CALENDER_

#include "Spot.h"

class Info_calendar{
private:
	Spot info;
	int start;
	int duration;

public:
	Info_calendar(Spot info, int start, int duration){
		this->info = info;
		this->start = start;
		this->duration = duration;
	}

	Spot getSpot(){
		return this->info;
	}
};

#endif
