#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include "property.h"
#include "person.h"
#include "agent.h"

class Deal {
private:
    int dealId;
    std::string dealType;
    Property property;
    Person client;
    Agent agent;

public:
    Deal();
    Deal(int id, const std::string& dt, const Property& prop, const Person& cl, const Agent& ag);

    void displayTable() const;
    void displayFull() const;

    int getId() const;
    std::string getDealType() const;
    Property getProperty() const;
    Person getClient() const;
    Agent getAgent() const;

    void setDealType(const std::string& dt);
    void setPrice(double newPrice);
};