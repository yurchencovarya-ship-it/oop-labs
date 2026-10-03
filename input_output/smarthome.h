#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
int readInt(const std::string& prompt);
class SmartDevice {//базовый класс умное устройство
protected:
    std::string name;
    bool isOn;
public:
    SmartDevice(std::string n, bool status);
    virtual ~SmartDevice();
    std::string getName() const;
    bool getStatus() const;
};
class ElectricalDevice : public SmartDevice {//класс электроприбор
protected:
    int id;
    double powerConsumption;//энергопотребление
public:
    ElectricalDevice(std::string n, bool status, int i, double power);
    int getId() const;
    double getPowerConsumption() const;
    void setPowerConsumption(double power);
    virtual std::string getDeviceType() const = 0;
    virtual void printRow(std::ostream& os) const = 0;
};
class SmartLight : public ElectricalDevice {//класс умная лампа
private:
    int brightness;//яркость 
public:
    SmartLight(std::string n, bool status, int i, double power, int bright);
    std::string getDeviceType() const override;
    void printRow(std::ostream& os) const override;
};
class SmartThermostat : public ElectricalDevice {//класс умный термостат
private:
    double targetTemperature;//целевая температура
public:
    SmartThermostat(std::string n, bool status, int i, double power, double temp);
    std::string getDeviceType() const override;
    void printRow(std::ostream& os) const override;
};
class SmartHome {//композиция, умный дом
private:
    std::string homeName;
    ElectricalDevice** devices;
    int count;
    int capacity;
    void resize();
public:
    SmartHome(std::string hName);
    ~SmartHome();
    std::string getHomeName() const { return homeName; }
    void addDevice(ElectricalDevice* dev);
    void removeDevice(int id);
    void editDevice(int id, double newPower);
    void sortDevices();
    void searchDevice(const std::string& searchName) const;
    void displayTable(std::ostream& os) const;
};
#pragma once
