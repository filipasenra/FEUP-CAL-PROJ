#ifndef _CALENDER_
#define _CALENDER_

#include "Info_calender.h"
#include <vector>

class Calender{

private:
	std::vector<Info_calender> calender;

public:
	Calender(Info_calender start, Info_calender end){
		calender.push_back(start);
		calender.push_back(end);
	}

};

#endif

