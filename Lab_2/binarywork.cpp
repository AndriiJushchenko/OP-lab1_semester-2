#include "binarywork.h"


//Інтерфейс користувача
void interface() {
    cout << endl << "Choose what you need:" << endl;
    cout << "0 EXIT" << endl;
    cout << "1 create file" << endl;
    cout << "2 read file" << endl;
    cout << "3 add text to file" << endl;
    cout << "4 find students with minimum score in each branch" << endl;
    cout << "5 create new file with students on fourth course sorted by last name, whose average score is not lower than specified one" << endl;
    cout << "Enter your choice: " << endl;
}
//Виводить помилку
void error_massage() {
    cout << "Invalid choice, try again" << endl;
    cout << "You need to use only correct numbers 0-5" << endl;
}


// Перевіряє на помилку і відриває файл

//For ifstream
bool check_file_open_ifstream(ifstream& fin, const string& name) {
    fin.open(name, ios::binary);
    if (!fin.is_open()) {
        cout << "Error opening file " << name << endl;
        return false;
    }
    return true;
}
//For ofstream
bool check_file_open_ofstream(ofstream& fout, const string& name) {
    fout.open(name, ios::binary);
    if (!fout.is_open()) {
        cout << "Error opening file " << name << endl;
        return false;
    }
    return true;
}


//Структура stdent для запису даних в файл
struct student {
    string name;
    string birthday;
    string educationFORM;
    string branch;
    int group;
    double averagemark;
};


// Work with FILE 

//Повертає назву файлу
string name_file() {
    cout << "ENTER please name of the file(For example file.bin):" << endl;
    string nameFile;
    cin >> nameFile;
    return nameFile;
}
//Функція для читання бінарного файлу
void read_binary_file(const string& name) {

    ifstream fin;
    check_file_open_ifstream(fin, name); //Відкрити фвйл

    size_t count_strct = 0;
    fin.seekg(0, ios::end);
    count_strct = fin.tellg() / sizeof(student); //Ці рядки визначають розмір файлу в байтах і обчислюють кількість структур студента, які він містить.
    fin.seekg(0, ios::beg);
    student* std = new student[count_strct]; //Потім вони виділяють пам’ять для масиву студентських структур за допомогою оператора new.

    for (size_t i = 0; i < count_strct; ++i) {  //Цей цикл читає кожну структуру студента з файлу в масив структур студента std.
        if (!fin.read(reinterpret_cast<char*>(&std[i]), sizeof(student))) { //Якщо є помилка читання з файлу, він друкує повідомлення про помилку

            cerr << "Failed to read from " << name << endl;
            break;
        }
        cout << "Name: " << std[i].name << endl;
        cout << "Birthday: " << std[i].birthday << endl;
        cout << "Education form: " << std[i].educationFORM << endl;
        cout << "Branch: " << std[i].branch << endl;
        cout << "Group: " << std[i].group << endl;
        cout << "Average mark: " << std[i].averagemark << endl;
        cout << "--------------------------------------------------" << endl;
    }
    fin.close();

}
//Функція для додавання тексту у файл
void append_text_to_file(const string& name) {

    ofstream fout(name, ios::binary | ios::app);
    if (!fout.is_open()) {
        cout << "Error opening file " << name << endl;   //Відкрити файл у режимі додавання та перевірити наявність помилок
        return;
    }

    student std;

    int choice = 1;
    while (choice != 0) {
        cout << "ENTER student data:" << endl;
        cout << "ENTER student`s name (in format Yushchenko A.Y): " << endl;  //Output

        cin.ignore();
        getline(cin, std.name);

        cout << "ENTER student`s birthday (in format xx.xx.xxxx): " << endl;

        getline(cin, std.birthday);

        cout << "ENTER student`s education form: (in format Denna)" << endl;

        getline(cin, std.educationFORM);

        cout << "ENTER student`s branch (in format IP): " << endl;

        getline(cin, std.branch);

        cout << "ENTER student`s group (in format IP-XX): " << endl;

        cin >> std.group;

        cout << "ENTER student`s mark (in format x): " << endl;

        cin >> std.averagemark;

        cout << "PRESS 0 to FINISH or 1 to CONTINUE" << endl;

        cin >> choice;

        fout.write((char*)&std, sizeof(student));
    }
    cout << "Your file was successfully updated" << endl;
    fout.close();
}
//Функція для пошуку студентів з мінімальною оцінкою в кожному потоці
void find_min_students(const string& name) {

    ifstream fin;
    check_file_open_ifstream(fin, name);

    size_t count_strct = 0;
    fin.seekg(0, ios::end);
    count_strct = fin.tellg() / sizeof(student);
    fin.seekg(0, ios::beg);
    student* std = new student[count_strct];

    map<string, double> min_scores; // карта для збереження мінімального балу для кожного потоку
    map<string, vector<student>> students_by_branch; // карта для зберігання студентів за потоками

// читати всіх студентів і групувати їх за потоками
    for (size_t i = 0; i < count_strct; ++i) {
        if (!fin.read(reinterpret_cast<char*>(&std[i]), sizeof(student))) {
            cerr << "Failed to read from " << name << endl;
            break;
        }
        students_by_branch[std[i].branch].push_back(std[i]);

// оновити мінімальний бал для цього потоку, якщо потрібно
        if (min_scores.find(std[i].branch) == min_scores.end() || std[i].averagemark < min_scores[std[i].branch]) {
            min_scores[std[i].branch] = std[i].averagemark;
        }
    }
    fin.close();

// вивести студентів з мінімальними балами для кожного потоку
    for (auto it = students_by_branch.begin(); it != students_by_branch.end(); ++it) {
        const string& branch = it->first;
        const double min_score = min_scores[branch];

        cout << endl << "Minimum score for branch " << branch << ": " << min_score << endl;
        for (const auto& student : it->second) {
            if (student.averagemark == min_score) {
                cout << "Name: " << student.name << endl;
                cout << "Branch: " << student.branch << endl;
                cout << "Group: " << student.group << endl;
                cout << "Average mark: " << student.averagemark << endl;
                cout << "------------------------" << endl;
            }
        }
    }
    //
}
//Функція для сортування студентів у новому файлі, позначка якого вище заданої
void sort_and_save_by_name(const string& name, double min_avg) {

    ifstream fin;
    check_file_open_ifstream(fin, name);

    vector<student> students;
    student* temp = new student[100];
    int i = 0;
    while (fin.read(reinterpret_cast<char*>(&temp[i]), sizeof(student))) {
        if (temp[i].educationFORM == "Denna" && temp[i].averagemark >= min_avg && temp[i].group > 40) {
            students.push_back(temp[i]);
        }
        ++i;
    }

    sort(students.begin(), students.end(), [](const student& a, const student& b) {
        string a_last_name = a.name.substr(0, a.name.find_last_of(' '));
        string b_last_name = b.name.substr(0, b.name.find_last_of(' '));
        return a_last_name < b_last_name;
    });

    fin.close();

    string output_name = name_file();
    ofstream fout;
    check_file_open_ofstream(fout, output_name);

    for (int i = 0; i < students.size(); ++i) {
        fout.write(reinterpret_cast<const char*>(&students[i]), sizeof(student));
    }

    fout.close();

    cout << "Full-time students on fourth course sorted by name, whose average score is not less than " << min_avg << ", and saved to file " << output_name << endl;
}


//Switch cases

//case1
void choice1() {

    ofstream outFile; student std; int choice = 1;
    string name = name_file();

    check_file_open_ofstream(outFile, name); //Open file

    while (choice != 0) {

        cout << "ENTER student data:" << endl;
        cout << "ENTER student`s name (in format Yushchenko A.Y.): " << endl; //Output

        cin.ignore();
        getline(cin, std.name);

        cout << "ENTER student`s birthday (in format xx.xx.xxxx): " << endl;

        getline(cin, std.birthday);

        cout << "ENTER student`s education form: (in format Denna)" << endl;

        getline(cin, std.educationFORM);

        cout << "ENTER student`s branch (in format IP): " << endl;

        getline(cin, std.branch);

        cout << "ENTER student`s group (in format IP-XX): " << endl;

        cin >> std.group;

        cout << "ENTER student`s mark (in format x): " << endl;

        cin >> std.averagemark;

        cout << "PRESS 0 to FINISH or 1 to CONTINUE" << endl;

        cin >> choice;

        outFile.write((char*)&std, sizeof(student));
    }
    cout << "Your file was successfully created" << endl;
    outFile.close();
}
//case2
void choice2() {
    string name = name_file();
    cout << endl;
    read_binary_file(name);
}
//case3
void choice3() {
    string name = name_file();
    append_text_to_file(name);
}
//case4
void choice4() {
    string name = name_file();
    find_min_students(name);
}
//case5
void choice5() {

    string name; double mark = 0;
    name = name_file();

    cout << "Enter minimal average mark:" << endl;
    cin >> mark;

    sort_and_save_by_name(name, mark);
}