#include"person.h"
using namespace std;
Person::Person(const string& name, const string& ph) {
    fullname = name;
    phone = ph;
}
Person::Person() {
    fullname = "Не указано";
    phone = "Не указан";
}
Person::~Person() {}
void Person::display() const {
    cout << "ФИО: " << fullname << ", Тел: " << phone;
}
string Person::getName() const { return fullname; }
string Person::getPhone() const { return phone; }
void Person::setName(const string& name) { fullname = name; }
void Person::setPhone(const string& ph) { phone = ph; }
