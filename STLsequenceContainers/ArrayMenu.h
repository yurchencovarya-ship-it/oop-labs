#pragma once
#include <array>
#include <string>
void saveArrayToFile(const std::string& filename, const std::array<std::string, 4>& categories);
void loadArrayFromFile(const std::string& filename, std::array<std::string, 4>& categories);
void menuArray();