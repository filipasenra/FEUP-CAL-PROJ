#ifndef MAPPARSER_H
#define MAPPARSER_H

#include "Graph.h"
#include "Spot.h"

Graph parseMap(std::string X_YFile, std::string edgesFile,
		std::string Lat_LongFile, std::string busFile = "", std::string subawayFile = "");
#endif
