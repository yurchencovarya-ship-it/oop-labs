#pragma once
#include <string>
#include <iostream>

class Address {
private:
    std::string city;
    std::string street;
    int houseNumber;
    int apartmentNumber;

public:
    Address();
    Address(const std::string& c, const std::string& s, int h, int a);
    void display() const;
    std::string getCity() const;
    std::string getStreet() const;
    int getHouseNumber() const;
    int getApartmentNumber() const;
};