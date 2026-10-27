#pragma once
#include <list>
#include <string>
#include "agent.h"
void saveListToFile(const std::string& filename, const std::list<Agent>& agents);
void loadListFromFile(const std::string& filename, std::list<Agent>& agents);
void menuList();