//
// Created by Ющенко Андрей on 07.06.2023.
//

#ifndef LAB_3_PCLASS_H
#define LAB_3_PCLASS_H

#endif //LAB_3_PCLASS_H

#pragma once
#include <iostream>
#include <string>
using namespace std;

class Text {

private:
    string text;

public:

    Text();

    void text_append(string str);

    int countDoubleCharOccurrences();

    void print();
};