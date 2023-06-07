#include "chesscode.h"


//Виводить помилку
int error_massage() {
    cout << "Oops, invalid choice,try again" << endl;
    cout << "You need to use only correct numbers like in instruction" << endl;
    return 1;
}
Numeral_2 EnterBinaryNumber(Numeral_2 Num, int *decimal, int *choice, string *binary){
    while (true) {
        if (*choice == 1) {
            cin >> *decimal;
            new(&Num) Numeral_2(*decimal);
            break;
        } else if (*choice == 2) {
            cin >> *binary;
            new(&Num) Numeral_2(*binary);
            break;
        } else {
            error_massage();
            cout << "Please make your choice:";
            cin >> *choice;
        }
    }
    return Num;
}

void mind() {

    int choice = 0;
    string binary1, binary2, binary3;
    int decimal1, decimal2, decimal3;

    Numeral_2 N1;
    Numeral_2 N2;
    Numeral_2 N3;

    cout << "In what form do you want to enter the first number? 1 - Decimal, 2 - Binary" << endl;
    cin >> choice;
// створює двійкове число N1
    cout << "Enter the first binary number: ";
    N1 = EnterBinaryNumber(N1, &decimal1, &choice, &binary1);

    cout << "In what form do you want to enter the number? 1 - Decimal, 2 - Binary" << endl;
    cin >> choice;
// створює двійкове число N2
    cout << "Enter the second binary number: ";
    N2 = EnterBinaryNumber(N2, &decimal2, &choice, &binary2);

    ++N1; //1

    int incrementValue; //2
    cout << "Enter the value to increment N2: ";
    cin >> incrementValue;
    Numeral_2 incrementValueNumeral(incrementValue);
    N2 += incrementValueNumeral;

    N3 = N1 + N2; //3

    int decimalN3 = N3.BinaryToDecimal(N3.getBinaryNumber());//4

    cout << "N1: " << N1.getBinaryNumber() << endl;
    cout << "N2: " << N2.getBinaryNumber() << endl;
    cout << "N3: " << N3.getBinaryNumber() << " (decimal: " << decimalN3 << ")" << endl;

}