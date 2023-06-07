//
// Created by Ющенко Андрей on 07.06.2023.
//

#ifndef LAB_4_NUMERAL_2_H
#define LAB_4_NUMERAL_2_H

#endif //LAB_4_NUMERAL_2_H

#pragma once
#include <iostream>
#include <string>
#include <cmath>
using namespace std;


class Numeral_2 {

private:

    string binaryNumber;
    string DecimalToBinary(int decimalNumber);

public:

    //конструктори
    Numeral_2();
    Numeral_2(const string& binaryNumber);
    Numeral_2(int decimalNumber);

    //методи
    string getBinaryNumber();
    int BinaryToDecimal(const string& binaryNumber);

    //оператори
    Numeral_2& operator++();
    Numeral_2 operator+(Numeral_2& other);
    Numeral_2& operator+=(Numeral_2& other);
};

