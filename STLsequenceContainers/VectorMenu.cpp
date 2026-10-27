#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "deal.h"
#include"VectorMenu.h"
using namespace std;
void saveVectorToFile(const string& filename, const vector<Deal>& deals) {
    ofstream ouf(filename, ios::out | ios::trunc);
    if (!ouf.is_open() || ouf.bad()) return;
    ouf << deals.size() << endl;
    for (int i = 0; i < deals.size(); i++) {
        const auto& d = deals[i];
        ouf << d.getId() << ";" << d.getDealType() << ";"
            << d.getProperty().getType() << ";" << d.getProperty().getArea() << ";" << d.getProperty().getPrice() << ";"
            << d.getProperty().getAddress().getCity() << ";" << d.getProperty().getAddress().getStreet() << ";"
            << d.getClient().getName() << ";" << d.getClient().getPhone() << ";"
            << d.getAgent().getId() << ";" << d.getAgent().getName() << ";" << d.getAgent().getPhone() << ";" << d.getAgent().getExperienceYears() << endl;
    }
    ouf.close();
}
void loadVectorFromFile(const string& filename, vector<Deal>& deals) {
    ifstream inf(filename, ios::in);
    if (!inf.is_open()) return;
    if (inf.peek() == EOF) { inf.close(); return; }
    deals.clear();
    size_t size = 0;
    inf >> size;
    inf.ignore(1000, '\n');
    for (int i = 0; i < size; i++) {
        if (inf.eof() || inf.fail()) break;
        string line;
        getline(inf, line);
        if (line.empty()) continue;
        stringstream ss(line);
        string idStr, dealType, propType, areaStr, priceStr, city, street;
        string clientName, clientPhone, agentIdStr, agentName, agentPhone, agentExpStr;
        getline(ss, idStr, ';');
        getline(ss, dealType, ';');
        getline(ss, propType, ';');
        getline(ss, areaStr, ';');
        getline(ss, priceStr, ';');
        getline(ss, city, ';');
        getline(ss, street, ';');
        getline(ss, clientName, ';');
        getline(ss, clientPhone, ';');
        getline(ss, agentIdStr, ';');
        getline(ss, agentName, ';');
        getline(ss, agentPhone, ';');
        getline(ss, agentExpStr, ';');
        deals.push_back(Deal(
            stoi(idStr), dealType,
            Property(propType, stod(areaStr), stod(priceStr), Address(city, street, 1, 0)),
            Person(clientName, clientPhone),
            Agent(agentName, agentPhone, stoi(agentIdStr), stod(agentExpStr))
        ));
    }
    inf.close();
}

void menuVector() {
    vector<Deal> deals;
    string filename = "deals.txt";
    loadVectorFromFile(filename, deals);
    int choice;
    do {
        cout << "\nМеню vector (Учет сделок) ---" << endl;
        cout << "1. Просмотр всех сделок (Таблица на экран и в файл)" << endl;
        cout << "2. Добавить новую сделку" << endl;
        cout << "3. Редактировать цену объекта по ID" << endl;
        cout << "4. Удалить сделку по ID" << endl;
        cout << "5. Найти сделку по ID" << endl;
        cout << "6. Сортировать сделки по цене" << endl;
        cout << "0. Назад в главное меню" << endl;
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
            if (deals.empty()) {
                cout << "\nСписок сделок пуст" << endl;
            }
            else {
                for (int i = 0; i < deals.size(); i++) {
                    deals[i].displayTable();
                }
                cout << "=================================================================================================\n";
                ofstream report("deals_report.txt");
                report << "====== ОТЧЕТ ПО СДЕЛКАМ С НЕДВИЖИМОСТЬЮ ======" << endl;
                for (int i = 0; i < deals.size(); i++) {
                    report << "ID: " << deals[i].getId() << " | Тип: " << deals[i].getDealType()
                        << " | Цена: $" << deals[i].getProperty().getPrice() << endl;
                }
                report.close();
                cout << ">(Таблица выгружена в файл 'deals_report.txt')" << endl;
            }
            saveVectorToFile(filename, deals);
            break;
        case 2: {
            int id, house, apt;
            string type, cName, cPhone, aName, aPhone, pType, city, street;
            double area, price, comm;
            cout << "ID сделки: "; cin >> id;
            cout << "Тип сделки (Продажа/Покупка): "; cin >> type;
            cout << "ФИО Клиента: "; cin.ignore(); getline(cin, cName);
            cout << "Телефон Клиента: "; cin >> cPhone;
            cout << "ФИО Агента: "; cin.ignore(); getline(cin, aName);
            cout << "Телефон Агента: "; cin >> aPhone;
            cout << "Стаж агента: "; cin >> comm;
            cout << "Тип недвижимости: "; cin.ignore(); getline(cin, pType);
            cout << "Город: "; getline(cin, city);
            cout << "Улица: "; getline(cin, street);
            cout << "Номер дома: "; cin >> house;
            cout << "Квартира (0 если дом): "; cin >> apt;
            cout << "Площадь: "; cin >> area;
            cout << "Стоимость ($): "; cin >> price;

            deals.push_back(Deal(id, type,
                Property(pType, area, price, Address(city, street, house, apt)),
                Person(cName, cPhone),
                Agent(aName, aPhone, id + 100, comm)));

            saveVectorToFile(filename, deals);
            cout << "Сделка добавлена!" << endl;
            break;
        }
        case 3: {
            int id;
            double nPrice;
            cout << "Введите ID сделки: ";
            cin >> id;

            bool found = false;
            for (auto& d : deals) {
                if (d.getId() == id) {
                    cout << "Текущая цена: $" << d.getProperty().getPrice() << "\nНовая цена: $";
                    cin >> nPrice;
                    d.setPrice(nPrice);
                    found = true;
                    break;
                }
            }
            if (found) {
                saveVectorToFile(filename, deals);
                cout << "Цена успешно обновлена!" << endl;
            }
            else {
                cout << "Сделка с таким ID не найдена" << endl;
            }
            break;
        }
        case 4: {
            int id; cout << "Введите ID для удаления: "; cin >> id;
            auto it = remove_if(deals.begin(), deals.end(), [id](const Deal& d) { return d.getId() == id; });
            if (it != deals.end()) {
                deals.erase(it, deals.end());
                saveVectorToFile(filename, deals);
                cout << "Сделка удалена" << endl;
            }
            else cout << "Сделка не найдена" << endl;
            break;
        }
        case 5: {
            int id; cout << "Введите ID для поиска: "; cin >> id;
            bool found = false;
            for (const auto& d : deals) {
                if (d.getId() == id) {
                    cout << "\nИнформация о сделке: " << endl;
                    d.displayFull();
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Сделка не найдена" << endl;
            break;
        }
        case 6:
            sort(deals.begin(), deals.end(), [](const Deal& a, const Deal& b) {
                return a.getProperty().getPrice() < b.getProperty().getPrice();
                });
            saveVectorToFile(filename, deals);
            cout << "Сделки отсортированы по цене!" << endl;
            break;
        case 0:
            break;
        default:
            cout << "Неверный выбор" << endl;
        }
    } while (choice != 0);
}