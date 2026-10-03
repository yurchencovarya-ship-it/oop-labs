#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;
// Работник (базовый класс)
class Employee {
protected:
    string name;
    int id;
public:
    Employee();
    Employee(const string& name, int id);
    Employee(const Employee& other);
    virtual ~Employee();
    virtual void getData();
    virtual void putData() const;
    virtual void saveData(ofstream& ouf) const = 0;
    virtual void loadData(ifstream& inf) = 0;

    // Чисто виртуальный метод для получения строкового идентификатора типа
    virtual string getTypeName() const = 0;
    // Перегрузка операторов вывода/ввода через потоки
    friend ostream& operator<<(ostream& os, const Employee& emp);
    friend istream& operator>>(istream& is, Employee& emp);
    int getId() const { return id; }
    string getName() const { return name; }
};

// Пилот
class Pilot : public Employee {
private:
    int flightHours;
public:
    Pilot();
    Pilot(const string& name, int id, int flightHours);
    Pilot(const Pilot& other);
    ~Pilot() override;
    void getData() override;
    void putData() const override;
    void saveData(ofstream& ouf) const override;
    void loadData(ifstream& inf) override;
    string getTypeName() const override { return "Pilot"; }
    int getFlightHours() const { return flightHours; }
};
// Бортпроводник
class FlightAttendant : public Employee {
private:
    bool speaksEnglish;
public:
    FlightAttendant();
    FlightAttendant(const string& name, int id, bool speaksEnglish);
    FlightAttendant(const FlightAttendant& other);
    ~FlightAttendant() override;
    void getData() override;
    void putData() const override;
    void saveData(ofstream& ouf) const override;
    void loadData(ifstream& inf) override;
    string getTypeName() const override { return "FlightAttendant"; }
    bool getSpeaksEnglish() const { return speaksEnglish; }
};
// Инженер
class Engineer : public Employee {
private:
    string specialization;
public:
    Engineer();
    Engineer(const string& name, int id, const string& spec);
    Engineer(const Engineer& other);
    ~Engineer() override;
    void getData() override;
    void putData() const override;
    void saveData(ofstream& ouf) const override;
    void loadData(ifstream& inf) override;
    string getTypeName() const override { return "Engineer"; }
    string getSpecialization() const { return specialization; }
};
// Полет (экипаж)
class Flight {
private:
    static const int MAX_CREW = 10;
    string flightNumber;
    string destination;
    Employee* crew[MAX_CREW];
    int crewSize;
public:
    Flight();
    Flight(const string& flightNum, const string& dest);
    Flight(const Flight& other);
    ~Flight();
    void createFlight();
    void showFlightInfo() const;
    void saveToFile(const string& filename) const;
    void readFromFile(const string& filename);
    void appendToFile(const string& filename) const;
    void deleteFromFile(const string& filename, int empId);
    void editInFile(const string& filename, int empId);
    void viewFileRaw(const string& filename) const;
    void searchInFile(const string& filename, const string& keyword) const;
};
#pragma once
