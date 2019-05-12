#ifndef MAPPARSER_H
#define MAPPARSER_H

#include "Graph.h"
#include "Spot.h"

Graph<Spot> parseMap(std::string X_YFile, std::string edgesFile/*, std::string tagsFile*/);
#endif
