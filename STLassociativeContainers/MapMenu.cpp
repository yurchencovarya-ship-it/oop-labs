#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "deal.h"
#include "MapMenu.h"

using namespace std;

void saveMapToFile(const string& filename, const map<int, Deal>& dealsMap) {
    ofstream ouf(filename, ios::out | ios::trunc);
    if (!ouf.is_open() || ouf.bad()) return;
    ouf << dealsMap.size() << endl;
    for (const auto& pair : dealsMap) {
        const auto& d = pair.second;
        ouf << d.getId() << ";" << d.getDealType() << ";"
            << d.getProperty().getType() << ";" << d.getProperty().getArea() << ";" << d.getProperty().getPrice() << ";"
            << d.getProperty().getAddress().getCity() << ";" << d.getProperty().getAddress().getStreet() << ";"
            << d.getClient().getName() << ";" << d.getClient().getPhone() << ";"
            << d.getAgent().getId() << ";" << d.getAgent().getName() << ";" << d.getAgent().getPhone() << ";" << d.getAgent().getExperienceYears() << endl;
    }
    ouf.close();
}
void loadMapFromFile(const string& filename, map<int, Deal>& dealsMap) {
    ifstream inf(filename, ios::in);
    if (!inf.is_open()) return;
    if (inf.peek() == EOF) { inf.close(); return; }
    dealsMap.clear();
    size_t size = 0;
    inf >> size;
    inf.ignore(1000, '\n');
    for (size_t i = 0; i < size; i++) {
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
        int id = stoi(idStr);
        Deal deal(
            id, dealType,
            Property(propType, stod(areaStr), stod(priceStr), Address(city, street, 1, 0)),
            Person(clientName, clientPhone),
            Agent(agentName, agentPhone, stoi(agentIdStr), stod(agentExpStr))
        );
        dealsMap.insert(make_pair(id, deal));
    }
    inf.close();
}
void menuMap() {
    map<int, Deal> dealsMap;
    string filename = "deals_map.txt";
    loadMapFromFile(filename, dealsMap);
    int choice;
    do {
        cout << "--- Меню map (Уникальные ключи - ID сделок) ---" << endl;
        cout << "1. Просмотр всех сделок (на экран и в файл)" << endl;
        cout << "2. Добавить новую сделку" << endl;
        cout << "3. Редактировать цену по ID" << endl;
        cout << "4. Удалить сделку по ID" << endl;
        cout << "5. Найти сделку по ID (метод find)" << endl;
        cout << "0. Назад в главное меню" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        switch (choice) {
        case 1:
            if (dealsMap.empty()) cout << "\nСписок пуст" << endl;
            else {
                for (const auto& pair : dealsMap) {
                    pair.second.displayTable();
                }
            }
            saveMapToFile(filename, dealsMap);
            break;
        case 2: {
            int id, house, apt;
            string type, cName, cPhone, aName, aPhone, pType, city, street;
            double area, price, comm;

            cout << "ID сделки (уникальный ключ): ";
            cin >> id;

            if (dealsMap.find(id) != dealsMap.end()) {
                cout << "Ошибка: Сделка с таким ID уже есть!" << endl;
                break;
            }

            cout << "Тип сделки (Продажа/Покупка): ";
            cin >> type;

            // Очищаем буфер после ввода типа сделки перед первым getline
            cin.ignore();

            cout << "ФИО Клиента: ";
            getline(cin, cName);

            cout << "Телефон Клиента: ";
            cin >> cPhone;

            // Очищаем буфер после ввода телефона клиента перед getline для ФИО агента
            cin.ignore();

            cout << "ФИО Агента: ";
            getline(cin, aName);

            cout << "Телефон Агента: ";
            cin >> aPhone; // <--- Исправлено на aPhone!

            cout << "Стаж агента: ";
            cin >> comm;

            // Очищаем буфер после ввода числа (стаж агента) перед getline для типа недвижимости
            cin.ignore();

            cout << "Тип недвижимости: ";
            getline(cin, pType);

            cout << "Город: ";
            getline(cin, city);

            cout << "Улица: ";
            getline(cin, street);

            cout << "Номер дома: ";
            cin >> house;

            cout << "Квартира (0 если дом): ";
            cin >> apt;

            cout << "Площадь: ";
            cin >> area;

            cout << "Стоимость ($): ";
            cin >> price;

            dealsMap.insert(make_pair(id, Deal(id, type, Property(pType, area, price, Address(city, street, house, apt)),
                Person(cName, cPhone),
                Agent(aName, aPhone, id + 100, comm))));

            saveMapToFile(filename, dealsMap);
            cout << "Сделка добавлена!" << endl;
            break;
        }
        case 3: {
            int id; double nPrice;
            cout << "Введите ID для изменения цены: "; 
            cin >> id;
            auto it = dealsMap.find(id);
            if (it != dealsMap.end()) {
                cout << "Новая цена: $"; 
                cin >> nPrice;
                it->second.setPrice(nPrice);
                saveMapToFile(filename, dealsMap);
                cout << "Цена обновлена!" << endl;
            }
            else cout << "Не найдено" << endl;
            break;
        }
        case 4: {
            int id; cout << "Введите ID для удаления: "; 
            cin >> id;
            if (dealsMap.erase(id) > 0) {
                saveMapToFile(filename, dealsMap);
                cout << "Удалено" << endl;
            }
            else cout << "Не найдено" << endl;
            break;
        }
        case 5: {
            int id; cout << "Введите ID для поиска: "; 
            cin >> id;
            auto it = dealsMap.find(id);
            if (it != dealsMap.end()) it->second.displayFull();
            else cout << "Не найдено" << endl;
            break;
        }
        case 0: break;
        default: cout << "Неверный выбор" << endl;
        }
    } while (choice != 0);
}