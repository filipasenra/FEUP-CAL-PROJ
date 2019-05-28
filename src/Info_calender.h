/**
 *
 *	class que guarda a informação de uma atividade
 *
 */
#ifndef _INFO_CALENDER_
#define _INFO_CALENDER_



#include "Spot.h"

class Info_calendar{
private:
	Spot info;
	int start;
	int duration;
	int end;
public:
	Info_calendar(Spot info, int hour , int minutes, int duration){
		this->info = info;
		this->start = hour * 60 + minutes;
		this->duration = duration;
		this->end = start+ duration;
	}

	Spot getSpot(){
		return this->info;
	}

	int getStart() const {
		return this->start;
	}

	int getEnd() const {
		return this->end;
	}

	int getDuration() const {
		return this->duration;
	}



	bool operator < (const Info_calendar & info){
		return (this->start < info.getStart());
	}

	bool sameTime(Info_calendar calendar){
		int time = calendar.getStart();
		for (int i = 0; i < calendar.getDuration(); i++, time++){
			if (time > this->start && time <this->end){
				return true;
			}
		}

		return false;
	}
};

#endif
