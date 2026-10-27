#include <iostream>
#include <set>
#include <string>
#include <map>
#include "deal.h"
#include "SetMenu.h"

using namespace std;

void menuSet(const map<int, Deal>& dealsMap) {
    set<string> uniqueCities;
    for (const auto& pair : dealsMap) {
        uniqueCities.insert(pair.second.getProperty().getAddress().getCity());
    }
    int choice;
    do {
        cout << "--- Меню set (Уникальный справочник городов) ---" << endl;
        cout << "1. Показать список уникальных городов (отсортировано)" << endl;
        cout << "2. Проверить наличие города в множестве (метод find)" << endl;
        cout << "0. Назад" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "\nУникальные города проведения сделок (set):" << endl;
            for (const auto& city : uniqueCities) {
                cout << "- " << city << endl;
            }
            break;
        case 2: {
            string qCity;
            cout << "Введите название города для проверки: ";
            cin.clear();
            cin.ignore(); 
            getline(cin, qCity);
            if (uniqueCities.find(qCity) != uniqueCities.end()) {
                cout << "Город найден в множестве set!" << endl;
            }
            else {
                cout << "Такого города нет в списке сделок" << endl;
            }
            break;
        }
        case 0: break;
        default: cout << "Неверный выбор" << endl;
        }
    } while (choice != 0);
}