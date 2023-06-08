//
// Created by Ющенко Андрей on 08.06.2023.
//

#ifndef LAB_6_TABLEWORK_H
#define LAB_6_TABLEWORK_H

#pragma once
#include <iostream>
#include <string>
#include <functional>
using namespace std;

template<typename K>
size_t MurmurHash2(const K& key) {
    size_t hash = 0;
    const char* data = reinterpret_cast<const char*>(&key);
    size_t len = sizeof(key);
    const size_t m = 0x5bd1e995;
    const int r = 24;

    while (len >= 4) {
        size_t k = *(reinterpret_cast<const size_t*>(data));
        k *= m;
        k ^= k >> r;
        k *= m;

        hash *= m;
        hash ^= k;

        data += 4;
        len -= 4;
    }

    switch (len) {
        case 3:
            hash ^= static_cast<size_t>(data[2]) << 16;
        case 2:
            hash ^= static_cast<size_t>(data[1]) << 8;
        case 1:
            hash ^= static_cast<size_t>(data[0]);
            hash *= m;
    }

    hash ^= hash >> 13;
    hash *= m;
    hash ^= hash >> 15;

    return hash;
}

template<typename K, typename V>
struct KeyValuePair {
    K key;
    V value;
    KeyValuePair<K, V>* next;

    KeyValuePair(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
};

template<typename K, typename V>
class HashTable {
private:
    KeyValuePair<K, V>** table;
    int size;

public:
    class Iterator {
    private:
        KeyValuePair<K, V>** table;
        int size;
        int currentIndex;
        KeyValuePair<K, V>* currentPair;

    public:
/* Конструктор класу який приймає вказівник на таблицю, її розмір,
   індекс поточного елементу та вказівник на поточну пару ключ-значення*/
        Iterator(KeyValuePair<K, V>** tbl, int sz, int index, KeyValuePair<K, V>* pair)
                : table(tbl), size(sz), currentIndex(index), currentPair(pair) {}
/* перегрузка оператора == для порівняння поточного індексу і вказівника на поточну пару ключ-значення
   з наступни ітератором*/
        bool operator==(const Iterator& other) const {
            return currentIndex == other.currentIndex && currentPair == other.currentPair;
        }
// перегрузка оператора != для інвертації результату оператора ==
        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
// повертає посилання та поточну пару ключ-значення
        KeyValuePair<K, V>& operator*() const {
            return *currentPair;
        }
// повертає вказівник на поточну пару ключ-значення
        KeyValuePair<K, V>* operator->() const {
            return currentPair;
        }
// перегрузка оператора префіксного ++ для переходу до наступного елементу в таблиці
// якщо всі елементи були пройдені, то покажчик поточної пари ключ-значення стає рівним nullptr.
        Iterator& operator++() {
            if (currentPair && currentPair->next) {
                currentPair = currentPair->next;
            }
            else {
                while (++currentIndex < size) {
                    if (table[currentIndex]) {
                        currentPair = table[currentIndex];
                        break;
                    }
                }
                if (currentIndex == size)
                    currentPair = nullptr;
            }
            return *this;
        }
    };
// конструктор для визначення розміру таблиці
    HashTable(int initialSize = 100) {
        size = initialSize;
        table = new KeyValuePair<K, V>* [size]();
    }
// деструктор
    ~HashTable() {
        clear();
        delete[] table;
    }
/* повертає хеш-код, вирахуваний діленням по модулю
   результату роботи алгоритму MurmurHash2 на розмір таблиці*/
    size_t hash(const K& key) const {
        return MurmurHash2(key) % size;
    }
// добавляє елемент в таблицю
    void insert(const K& key, const V& value) {
        int index = hash(key);
        KeyValuePair<K, V>* current = table[index];

        while (current) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            current = current->next;
        }

        KeyValuePair<K, V>* newPair = new KeyValuePair<K, V>(key, value);
        newPair->next = table[index];
        table[index] = newPair;
    }
// шукає елемент таблиці за його ключем
    V* search(const K& key) const {
        int index = hash(key);
        KeyValuePair<K, V>* current = table[index];

        while (current) {
            if (current->key == key) {
                return &(current->value);
            }
            current = current->next;
        }

        return nullptr;
    }
// видаляє елемент таблиці
    void remove(const K& key) {
        int index = hash(key);
        KeyValuePair<K, V>* previous = nullptr;
        KeyValuePair<K, V>* current = table[index];

        while (current) {
            if (current->key == key) {
                if (previous) {
                    previous->next = current->next;
                }
                else {
                    table[index] = current->next;
                }
                delete current;
                return;
            }
            previous = current;
            current = current->next;
        }
    }
// очищує таблицю
    void clear() {
        for (int i = 0; i < size; i++) {
            KeyValuePair<K, V>* current = table[i];
            while (current) {
                KeyValuePair<K, V>* next = current->next;
                delete current;
                current = next;
            }
            table[i] = nullptr;
        }
    }

// повертає ітератор, що вказує на перший елемент в таблиці
    Iterator begin() const {
        int index = 0;
        while (index < size && !table[index]) {
            index++;
        }
        if (index == size) {
            return Iterator(table, size, size, nullptr);
        }
        return Iterator(table, size, index, table[index]);
    }
// повертає ітератор, що вказує на останній елемент в таблиці
    Iterator end() const {
        return Iterator(table, size, size, nullptr);
    }
// функція виводу хеш-таблиці на екран
    void print() const {
        for (auto it = begin(); it != end(); ++it) {
            cout << " (" << it->key << " : " << it->value << ") " << endl;
        }
        cout << endl;
    }

    void interface() {
        int choice;
        while (true) {
            cout << endl << "1 - Insert a key" << endl;
            cout << "2 - Search a key" << endl;
            cout << "3 - Remove a key" << endl;
            cout << "4 - Print Hash table" << endl;
            cout << "5 - Clear Hash Table" << endl;
            cout << "6 - Terminate program" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1) {
                K key;
                V value;
                cout << "Enter key: ";
                cin >> key;
                cout << "Enter value: ";
                cin >> value;
                insert(key, value);
                cout << "Element inserted." << endl;
            }
            else if (choice == 2) {
                K key;
                cout << "Enter key: ";
                cin >> key;
                V* value = search(key);
                if (value) {
                    cout << "Value found: " << *value << endl;
                }
                else {
                    cout << "Value not found." << endl;
                }
            }
            else if (choice == 3) {
                K key;
                cout << "Enter key: ";
                cin >> key;
                remove(key);
                cout << "Element removed." << endl;
            }
            else if (choice == 4) {
                print();
            }
            else if (choice == 5) {
                clear();
                cout << "Table cleared." << endl;
            }
            else if (choice == 6) {
                break;
            }
            else {
                cout << "Invalid choice." << endl;
            }
        }
    }
};

#endif //LAB_6_TABLEWORK_H
