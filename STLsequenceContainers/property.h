#pragma once
#include <string>
#include <iostream>
#include "address.h"

class Property {
private:
    std::string type;
    double area;
    double price;
    Address address;

public:
    Property();
    Property(const std::string& t, double ar, double pr, const Address& addr);
    void display() const;
    std::string getType() const;
    double getArea() const;
    double getPrice() const;
    Address getAddress() const;
    void setPrice(double pr);
};