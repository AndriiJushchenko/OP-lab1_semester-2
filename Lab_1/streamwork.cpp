//
// Created by Ющенко Андрей on 16.03.2023.
//

#include "streamwork.h"

void filestream(){
    string name, name1, c;
    cout << "Enter file name:\n";
    getline(cin, name);
    name1 = name;
    name += ".txt";
    name1 += "1.txt";
    inputFile(name);
    appFile(name);
    cout << "\nResult:\n";
    reWord(name, name1);
    outputFile(name1);
    cout << "Thank you for using!\n";
}

void inputFile(string name){
    ofstream fOut(name);
    if (!fOut) {
        cout << "\nCannot open file!\n";
        return;
    }
    string s;
    cout << "\nEnter text (# to stop):\n";
    getline(cin, s);
    fOut << s;
    while (true) {
        getline(cin, s);
        if (s == "#") break;
        fOut << endl << s;
    }
    fOut.close();
}

void outputFile(string name) {
    ifstream fIn(name);
    if (!fIn){
        cout << "\nCannot open file!\n";
        return;
    }
    string s;
    while (!fIn.eof()) {
        getline(fIn, s);
        cout << s << endl;
    }
    fIn.close();
}

void appFile(string name) {
    string choice;
    cout << "\nDo you want to add something?[y/n]\n";
    cin >> choice;
    if (choice == "n") {
        ofstream fOut(name, ios::app);
        if (fOut.is_open()) {
            fOut << endl;
            fOut.close();
        }
    } else {
        while (choice == "y") {
            fstream fio(name, ios::app);
            if (!fio.is_open()) {
                cout << "\nCannot open file!\n";
                return;
            }
            string s;
            cout << "\nEnter text (# to stop):\n";
            getline(cin, s);
            fio << s;
            while (true) {
                getline(cin, s);
                if (s == "#") break;
                fio << endl << s;
            }
            fio.close();
            cout << "\nChanged text:\n";
            outputFile(name);
            cout << "\nDo you want to add something?[y/n]\n";
            cin >> choice;
        }
        ofstream fOut(name, ios::app);
        if (fOut.is_open()) {
            fOut << endl;
            fOut.close();
        }
    }
}

void reWord(string name, string name1){
    string s;
    regex hex_reg(R"(0[xX][0-9a-fA-F]+)");/*створюємо регулярний вираз `hex_reg`,
                                               який шукає шістнадцяткові числа формату `0x` або `0X`
                                               і наступні після них цифри та букви від `a` до `f`*/
    smatch match; //обʼєкт `match`, у якому будуть зберігатись результати пошуку шістнадцяткових чисел в рядку `s`
    ifstream fIn(name);
    ofstream fOut(name1);
    while (!fIn.eof()){
        getline(fIn, s);
        while (regex_search(s, match, hex_reg)) { //цикл шукає всі шістнадцяткові числа в рядку `s` завдяки функції`regex_search(s, match, hex_reg)`
            string hex_str = match[0];//якщо число знайдено переносимо його у змінну hex_str
            int decimal_num = stoi(hex_str, nullptr, 16);//перетворюємо шістнадцяткове число в десяткове через функцію `stoi(hex_str, nullptr, 16)`.
            s.replace(match.position(), match.length(), to_string(decimal_num));
            /*замінюємо знайдене шістнадцяткове число в рядку `s` на його десятковий еквівалент
              за допомогою `s.replace(match.position(), match.length(), to_string(decimal_num))`*/
        }
        fOut << s;
        if (!fIn.eof()) fOut << endl;
    }
    fIn.close();
    fOut.close();
}
