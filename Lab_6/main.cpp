#include "tablework.h"

int main() {
    int choice;
    cout << "Choose the type of data: \n1 - int(int)\n2 - string(int)\n3 - double(int)\n4 - char(int)\n5 - int(string)\n6 - double(char)" << endl;
    cout << "Your choice:";
    cin >> choice;

    int size;
    cout << "Enter the size of the table : " << endl;
    cin >> size;

    if (choice == 1) {
        HashTable<int, int> ht(size);
        ht.interface();
    }
    else if (choice == 2) {
        HashTable<string, int> ht(size);
        ht.interface();
    }
    else if (choice == 3) {
        HashTable<double, int> ht(size);
        ht.interface();
    }
    else if (choice == 4) {
        HashTable<char, int> ht(size);
        ht.interface();
    }
    else if (choice == 5) {
        HashTable<int, string> ht(size);
        ht.interface();
    }
    else if (choice == 6) {
        HashTable<double, char> ht(size);
        ht.interface();
    }
    else {
        cout << "Invalid choice." << endl;
    }
    return 0;
}
