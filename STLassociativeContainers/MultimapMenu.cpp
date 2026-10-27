#include <iostream>
#include <map>
#include <string>
#include "deal.h"
#include "MultimapMenu.h"

using namespace std;
void menuMultimap(const map<int, Deal>& dealsMap) {
    multimap<string, Deal> multiDeals;
    for (const auto& pair : dealsMap) {
        multiDeals.insert(make_pair(pair.second.getProperty().getType(), pair.second));
    }
    int choice;
    do {
        cout << "--- Меню multimap (Группировка по типу недвижимости) ---" << endl;
        cout << "1. Показать все сделки, сгруппированные по типу" << endl;
        cout << "2. Найти сделки по конкретному типу (метод equal_range)" << endl;
        cout << "0. Назад" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "\nСодержимое multimap:" << endl;
            for (const auto& pair : multiDeals) {
                cout << "[Тип: " << pair.first << "] -> ";
                pair.second.displayTable();
            }
            break;
        case 2: {
            string searchType;
            cout << "Введите тип недвижимости для поиска (например, Квартира): ";
            cin.ignore();
            getline(cin, searchType);
            auto range = multiDeals.equal_range(searchType);
            cout << "\nРезультаты поиска для типа '" << searchType << "':" << endl;
            bool found = false;
            for (auto it = range.first; it != range.second; ++it) {
                it->second.displayFull();
                cout << "-----------------------------------" << endl;
                found = true;
            }
            if (!found) cout << "Сделок с таким типом не найдено." << endl;
            break;
        }
        case 0: break;
        default: cout << "Неверный выбор." << endl;
        }
    } while (choice != 0);
}