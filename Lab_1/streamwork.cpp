//
// Created by Ющенко Андрей on 16.03.2023.
//

#include "streamwork.h"

void filestream(){
    string name, name1, c;
    inputFile("text.txt");
    appFile("text.txt");
    cout << "\nResult:\n";
    findHex("text.txt", "text1.txt");
    reWord("text1.txt", "text2.txt");
    outputFile("text1.txt");
    cout << "\nThank you for using!\n";
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
}


bool is_hex(string word) {
    for (int i = 0; i < word.length(); i++) {
        if (!isxdigit(word[i])) {
            return false;
        }
    }
    return true;
}

void findHex(string name, string name1){
    ifstream fIn(name);
    ofstream fOut(name1);
    string str, line, s, st;
    while (!fIn.eof()) {
        getline(fIn, str);
        str+=" ";
        line = str;
        while(str != "\0") {
            size_t pos1 = str.find('.');
            size_t pos2 = str.find(',');
            size_t pos3 = str.find(' ');
            size_t pos = min(min(pos1, pos2), pos3);
            s = str.substr(0, pos);
            if(is_hex(s)){
                fOut << line << endl;
                break;
            }
            str.erase(0, pos+1);
        }
    }
    fIn.close();
    fOut.close();
}

void reWord(string name, string name1){
    ifstream fIn(name);
    ofstream fOut(name1);
    string str, line, s, st;
    size_t k;
    while (!fIn.eof()) {
        getline(fIn, str);
        line = str;
        size_t position = -1;
        while(str != "\0") {
            size_t pos1 = str.find('.');
            size_t pos2 = str.find(',');
            size_t pos3 = str.find(' ');
            size_t pos = min(min(pos1, pos2), pos3);
            position += pos+1;
            s = str.substr(0, pos);
            k = s.length();
            if(is_hex(s)){
                st = to_string(stoi(s, nullptr, 16));
                line.replace(position-k, k, st);
            }
            str.erase(0, pos+1);
        }
        fOut << line << endl;
    }
    fIn.close();
    fOut.close();
    remove(name.c_str());
    rename(name1.c_str(), name.c_str());
}
