#pragma once
#include <iostream>
#include <array>
#include <string>
#include <fstream>
#include <algorithm>
#include"ArrayMenu.h"
using namespace std;
void saveArrayToFile(const string& filename, const array<string, 4>& categories) {
    ofstream ouf(filename, ios::out | ios::trunc);
    if (!ouf.is_open() || ouf.bad()) return;
    for (int i = 0; i < 4; i++) {
        ouf << categories[i] << endl;
    }
    ouf.close();
}
void loadArrayFromFile(const string& filename, array<string, 4>& categories) {
    ifstream inf(filename, ios::in);
    if (!inf.is_open()) return;
    if (inf.peek() == EOF || inf.bad()) { inf.close(); return; }
    string line;
    int i = 0;
    while (inf.good() && !inf.eof() && getline(inf, line) && i < 4) {
        if (!line.empty()) {
            categories[i] = line;
            i++;
        }
    }
    inf.close();
}
void menuArray() {
    array<string, 4> categories = { "Жилой дом", "Квартира", "Коммерческая", "Таунхаус" };
    string filename = "categories.txt";
    loadArrayFromFile(filename, categories);
    int choice;
    do {
        cout << "--- Меню array (Категории недвижимости) ---" << endl;
        cout << "1. Просмотр категорий (на экран и в файл)" << endl;
        cout << "2. Редактировать категорию по индексу (0-3)" << endl;
        cout << "3. Найти категорию по названию" << endl;
        cout << "0. Назад в главное меню" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "\nСписок категорий: " << endl;
            for (int i = 0; i < 4; i++) {
                cout << " [" << i << "] " << categories[i] << endl;
            }
            saveArrayToFile(filename, categories);
            break;
        case 2: {
            int idx;
            cout << "Введите индекс (0-3): ";
            cin >> idx;
            if (idx >= 0 && idx < 4) {
                cout << "\nТекущее: " << categories[idx] << "\nНовое название: ";
                cin.ignore();
                getline(cin, categories[idx]);
                saveArrayToFile(filename, categories);
                cout << "Успешно изменено!" << endl;
            }
            else {
                cout << "Неверный индекс!" << endl;
            }
            break;
        }
        case 3: {
            string q;
            cout << "Искомая категория: " << endl;
            cin.ignore();
            getline(cin, q);
            auto it = find(categories.begin(), categories.end(), q);
            if (it != categories.end()) cout << "Категория найдена в array!" << endl;
            else cout << "Категория не найдена" << endl;
            break;
        }
        case 0:
            break;
        default:
            cout << "Неверный выбор" << endl;
        }
    } while (choice != 0);
}