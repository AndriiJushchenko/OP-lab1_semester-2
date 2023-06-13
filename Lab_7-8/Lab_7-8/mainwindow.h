#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <cmath>
#include <string>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QMessageBox>
#include <QApplication>
#include <QWidget>
#include <QMainWindow>


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QLineEdit* startTextBox;
    QLineEdit* endTextBox;
    QLineEdit* stepTextBox;
    QPushButton* calculateButton;
    QPushButton* clearButton;
    QListWidget* resultListBox;

private slots:
    void onCalculateButtonClick();
    void onClearButtonClick();
    bool validateInput();
};
#endif // MAINWINDOW_H
