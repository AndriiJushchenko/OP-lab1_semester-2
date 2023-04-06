//
// Created by Ющенко Андрей on 23.03.2023.
//

#include "pointerwork.h"


void filepointer(){
    cout << "Enter file name:\n";
    char name[25], name1[25];
    cin.getline(name,25);
    strcpy(name1, name);
    strcat(name, ".txt");
    strcat(name1, "1.txt");
    inputFile(name);
    char c = appFile(name);
    while (c == 'y') {
        cout << "\nChanged text:\n";
        outputFile(name);
        c = appFile(name);
    }
    reWord(name, name1);
    cout << "\nThank you for using!\n";
}

void inputFile(char *name){
    cout << "\nEnter text:\n";
    int n=0;
    char** lines = new char*[n];
    while(true) {
        char* line = new char[256];
        cin.getline(line, 256);
        if(*line == '#') break;
        lines[n] = line;
        n++;
    }
    ofstream fOut(name);
    if(fOut.is_open()) {
        int i;
        for(i = 0; i < n-1; i++) {
            fOut << lines[i] << endl;
            delete[] lines[i];
        }
        fOut << lines[i];
        delete[] lines[i];
        delete[] lines;
        fOut.close();
    } else {
        cout << "\nCannot open file!\n";
    }
}

void outputFile(char *name) {
    ifstream fin(name,ios_base::in|ios_base::binary);
    if (!fin.good()) {
        cout << "\nCannot open file!\n";
        return;
    }
    fin.seekg(0,ios_base::end);
    size_t uSize = fin.tellg();
    fin.seekg(0);

    char* t = new char[uSize+1];
    fin.read(t,uSize);
    t[uSize] = 0;

    puts(t);

    delete[] t;
    fin.close();
}

char appFile(char *name){
    char choice;
    cout << "\nDo you want to add something?[y/n]\n";
    cin >> choice;
    if(choice == 'y') {
        fstream fio;
        fio.open(name, ios::app);
        if (fio.is_open()) {
            cout << "\nEnter text:\n";
            int n = 0;
            char **lines = new char *[n];
            while (true) {
                char *line = new char[256];
                cin.getline(line, 256);
                if (*line == '#') break;
                lines[n] = line;
                n++;
            }
            int i;
            for (i = 0; i < n-1; i++) {
                fio << lines[i] << endl;
                delete[] lines[i];
            }
            fio << lines[i];
            delete[] lines[i];
            delete[] lines;
            fio.close();
        }else{
            cout << "\nCannot open file!\n";
            choice = 'n';
        }
    }
    return choice;
}

void reWord(char *name, char *name1){
    ifstream fIn(name,ios::in|ios::binary);
    if (!fIn.good()) {
        cout << "\nCannot open file!\n";
        return;
    }
    ofstream fOut(name1);
    if (!fOut.good()) {
        cout << "\nCannot open file!\n";
        fIn.close();
        return;
    }

    char* text = nullptr;
    fIn.seekg(0,ios::end);
    long size = fIn.tellg();
    fIn.seekg(0,ios::beg);

    text = new char[size + 1];

    fIn.read(text, size);
    text[size] = '\0';

    fIn.close();

    char* pos = text;
    while (*pos != '\0') {
        if (isxdigit(*pos) && (*(pos+1) == 'x') or (*(pos+1) == 'X')) { // перевіряємо, чи поточний символ є шістнадцятковим і наступний символ - 'x' або 'X'
            char* endptr;
            long int val = strtol(pos, &endptr, 16); // перетворюємо шістнацядцяткове число на десяткове
            size_t len = endptr - pos; // вираховуємо довжину числа в символах
            char buffer[20]; // створюємо буфер для запису десяткового числа
            snprintf(buffer, 20,"%ld", val);// записуємо десяткове число в буфер
            size_t buffer_len = strlen(buffer); // вираховуємо довжину рядка в буфері
            memmove(pos+buffer_len, pos+len, strlen(pos+len)+1); // зсуваємо частину рядка, що залишилася, на buffer_len символів вправо
            memcpy(pos, buffer, buffer_len); // копіюємо десяткове число замість шістнадцяткового
            pos += buffer_len; // переходимо до наступного символу після числа
        } else {
            pos++; // переходимо до наступного символу
        }
    }

    cout << "\nResult:" << endl;
    cout << text << endl;
    fOut.write(text, size);
    delete[] text;

    fIn.close();
    fOut.close();
}
