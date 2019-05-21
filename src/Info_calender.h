#ifndef _INFO_CALENDER_
#define _INFO_CALENDER_

#include "Spot.h"

class Info_calendar{
private:
	Spot info;
	int start;
	int duration;

public:
	Info_calendar(Spot info, int hour , int minutes, int duration){
		this->info = info;
		this->start = hour * 60 + minutes;
		this->duration = duration;
	}

	Spot getSpot(){
		return this->info;
	}

	int getStart(){
		return this->start;
	}
};

#endif
