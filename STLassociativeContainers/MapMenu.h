#pragma once
#include <map>
#include <string>
#include "deal.h"
void saveMapToFile(const std::string& filename, const std::map<int, Deal>& dealsMap);
void loadMapFromFile(const std::string& filename, std::map<int, Deal>& dealsMap);
void menuMap();