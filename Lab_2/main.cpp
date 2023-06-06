#include "binarywork.h"

int main() {
    int choiceMethod;
    do {
        interface();
        cin >> choiceMethod;
        switch (choiceMethod) {
            case 0:
                break;
            case 1:
                choice1();
                break;
            case 2:
                choice2();
                break;
            case 3:
                choice3();
                break;
            case 4:
                choice4();
                break;
            case 5:
                choice5();
                break;
            default:
                error_massage();
        }
    } while (choiceMethod != 0);
}
