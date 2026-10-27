#pragma once
#include <vector>
#include <string>
#include "deal.h"
void saveVectorToFile(const std::string& filename, const std::vector<Deal>& deals);
void loadVectorFromFile(const std::string& filename, std::vector<Deal>& deals);
void menuVector();