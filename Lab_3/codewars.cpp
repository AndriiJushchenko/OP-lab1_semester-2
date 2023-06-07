#include  "codewars.h"


//Вивід помилки
int error_massage() {
    cout << "Oops, invalid choice,try again" << endl;
    cout << "You need to use only correct numbers like in instruction" << endl;
    return 1;
}
// Сортує заданий масив об’єктів Text за кількістю подвоєних символів у кожному тексті
void sortByDoubledChars(Text* texts, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (texts[i].countDoubleCharOccurrences() < texts[j].countDoubleCharOccurrences()) {
                swap(texts[i], texts[j]);
            }
        }
    }
}
//Main
void code() {
    int stringnumbers;
    int choice = 0, line;

    //Number of strings input
    cout << "Enter the number of texts: ";
    cin >> stringnumbers;
    cout << endl;


    //Allocating memory for text array
    Text* texts = new Text[stringnumbers];

    // Input Text by user
    for (int i = 0; i < stringnumbers; ++i) {
        line = 0;
        if (choice != 1) {
            cin.ignore();
        }
        string userinput, additional_text;

        cout << "Enter text " << i + 1 << " in format(abrakadabra): ";

        getline(cin, userinput);

        while (true) {
            cout << "Do you want to add new string to your text? (Prees 1 - YES, 2 - NO): ";
            cin >> choice;

            if (choice == 1) {
                cout << "Enter additional text: ";
                cin.ignore();
                getline(cin, additional_text);
                userinput += "\n" + additional_text;
            } else if (choice == 2) {
                break;
            } else {
                error_massage();
            }
        }
        texts[i].text_append(userinput);
    }

    // Показує текст введений користувачем
    cout << endl << "Your input:" << endl;
    for (int i = 0; i < stringnumbers; i++) {
        cout << "Text " << i + 1 << ": \n";
        texts[i].print();
    }

    // Шукає подвоєння
    cout << endl << "Duplicate Character Occurrences:" << endl;
    for (int i = 0; i < stringnumbers; i++) {
        cout << "Text " << i + 1 << ": " << texts[i].countDoubleCharOccurrences() << endl;
    }

    // Сортує заданий масив об’єктів Text за кількістю подвоєних символів у кожному тексті
    sortByDoubledChars(texts, stringnumbers);

    // Вивести текст з найбільшою кількістю подвоєнь
    cout << endl << "Text with the most doubled characters: " << endl;
    texts[0].print();
    delete[] texts;
}