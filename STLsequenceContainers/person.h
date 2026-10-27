#pragma once
#include <string>
#include <iostream>

class Person {
protected:
    std::string fullname;
    std::string phone;

public:
    Person();
    Person(const std::string& name, const std::string& ph);
    virtual ~Person();
    virtual void display() const;
    std::string getName() const;
    std::string getPhone() const;
    void setName(const std::string& name);
    void setPhone(const std::string& ph);
}; 