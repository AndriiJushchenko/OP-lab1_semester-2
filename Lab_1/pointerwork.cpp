//
// Created by Ющенко Андрей on 23.03.2023.
//

#include "pointerwork.h"


void filepointer(){
    char name[20] = "textpoint.txt", name1[20] = "textpoint1.txt", name2[20] = "textpoint2.txt";
    inputFile(name);
    char c = appFile(name);
    while (c == 'y') {
        cout << "\nChanged text:\n";
        outputFile(name);
        c = appFile(name);
    }
    findHex(name, name1);
    reWord(name1, name2);
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
    FILE *fp = fopen(name, "w");
    if(fp) {
        int i;
        for(i = 0; i < n-1; i++) {
            fputs(lines[i], fp);
            fputs("\n", fp);
            delete[] lines[i];
        }
        fputs(lines[i], fp);
        delete[] lines[i];
        delete[] lines;
        fclose(fp);
    } else {
        cout << "\nCannot open file!\n";
    }
}

void outputFile(char *name) {
    FILE *fp = fopen(name, "r");
    if (!fp) {
        cout << "\nCannot open file!\n";
        return;
    }
    char buffer[256];
    while((fgets(buffer, 256, fp))!=nullptr)
    {
        printf("%s", buffer);
    }
    fclose(fp);
}

char appFile(char *name){
    char choice;
    cout << "\nDo you want to add something?[y/n]\n";
    cin >> choice;
    if(choice == 'y') {
        FILE *fp = fopen(name, "a");
        if (fp) {
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
                fputs(lines[i], fp);
                fputs("\n", fp);
                delete[] lines[i];
            }
            fputs(lines[i], fp);
            delete[] lines;
            fclose(fp);
        }else{
            cout << "\nCannot open file!\n";
            choice = 'n';
        }
    }
    return choice;
}

int is_hex(char *str) {
    int i;
    for (i = 0; i < strlen(str); i++) {
        if (!isxdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

void findHex(char* name, char* name1) {
    FILE* input_file = fopen(name, "r");
    FILE* output_file = fopen(name1, "w");
    char line[256];
    char lock[100];

    while (fgets(line, 256, input_file) != nullptr) {
        char *str = strtok(line, "\n");
        strcpy(lock, str);
        char *word = strtok(line, ", .\n");
        while (word != nullptr) {
            if (is_hex(word)) {
                char *text;
                text = (char*)malloc(sizeof(char) * (strlen(lock) + 1));
                strcpy(text, lock);
                fprintf(output_file, "%s\n", text);
                free(text);
                break;
            }
            word = strtok(nullptr, ",. \n");
        }
    }
    fclose(input_file);
    fclose(output_file);
}

void reWord(char* name, char* name1){
    FILE* input_file = fopen(name, "r");
    FILE* output_file = fopen(name1, "w");

    char line[256], new_line[256], token[10], *word;
    while (fgets(line, 256, input_file) != nullptr) {
        strcpy(new_line, "");
        word = strtok(line, ", .\n");
        while (word != nullptr) {
            if (is_hex(word)) {
                int value = (int)strtol(word, nullptr, 16);
                snprintf(token, 10, "%d", value);
                strcat(new_line, token);
            } else {
                strcat(new_line, word);
            }
            strcat(new_line, " ");
            word = strtok(nullptr, ", .\n");
        }
        fprintf(output_file, "%s\n", new_line);
    }
    fclose(input_file);
    fclose(output_file);
    remove(name);
    rename(name1, name);

    FILE* infile = fopen(name, "r");
    printf("\nResult:\n");
    char buffer[256];
    while (fgets(buffer, 256, infile) != nullptr) {
        printf("%s", buffer);
    }
    fclose(infile);
}
