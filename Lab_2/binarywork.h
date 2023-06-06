#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;


void interface();
void error_massage();

bool check_file_open_ifstream(ifstream& fin, const string& name);
bool check_file_open_ofstream(ofstream& fout, const string& name);

struct student;

string name_file();
void read_binary_file(const string& name);
void append_text_to_file(const string& name);
void find_min_students(const string& name);
void sort_and_save_by_name(const string& name, double min_avg);

void choice1();
void choice2();
void choice3();
void choice4();
void choice5();


