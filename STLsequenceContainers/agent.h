#pragma once
#include <string>
#include <iostream>
#include "person.h"

class Agent : public Person {
private:
    int agentId;
    int experienceYears;

public:
    Agent();
    Agent(const std::string& name, const std::string& ph, int id, int experience);
    void display() const override;
    int getId() const;
    int getExperienceYears() const;
    void setId(int id);
    void setExperienceYears(int experience);

    friend std::ostream& operator<<(std::ostream& os, const Agent& ag);
}; 