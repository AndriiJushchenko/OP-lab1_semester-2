#include "mainwindow.h"
#include "solvearctan.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QMessageBox>
#include <QtWidgets>
#include <QWidget>
#include <QMainWindow>
#include <QSettings>


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Arctan Calculator");
    setFixedSize(320, 440);


    QLabel* startLabel = new QLabel("Start Interval");
    startTextBox = new QLineEdit();
    startTextBox->setFixedWidth(100);

    QLabel* endLabel = new QLabel("Finish Interval");
    endTextBox = new QLineEdit();
    endTextBox->setFixedWidth(100);

    QLabel* stepLabel = new QLabel("Step");
    stepTextBox = new QLineEdit();
    stepTextBox->setFixedWidth(100);

    calculateButton = new QPushButton("Calculate");
    connect(calculateButton, &QPushButton::clicked, this, &MainWindow::onCalculateButtonClick);

    clearButton = new QPushButton("Clear");
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::onClearButtonClick);

    resultListBox = new QListWidget();
    resultListBox->setFixedSize(200, 200);

    QVBoxLayout* layout = new QVBoxLayout();
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    buttonLayout->addWidget(calculateButton);
    buttonLayout->addWidget(clearButton);

    layout->addWidget(startLabel);
    layout->addWidget(startTextBox);
    layout->addWidget(endLabel);
    layout->addWidget(endTextBox);
    layout->addWidget(stepLabel);
    layout->addWidget(stepTextBox);
    layout->addLayout(buttonLayout);
    layout->addWidget(resultListBox);

    setLayout(layout);
}

void MainWindow::onCalculateButtonClick()
{
    if (!validateInput())
    {
        return;
    }

    double start = startTextBox->text().toDouble();
    double end = endTextBox->text().toDouble();
    double step = stepTextBox->text().toDouble();

    resultListBox->clear();

    double x = start;
    while (x <= end)
    {
        SolveArctan solver(x);
        double result = solver.Calculate();

        resultListBox->addItem(QString("x = %1, arctan(√x) = %2").arg(x).arg(result));

        x += step;
    }
}

void MainWindow::onClearButtonClick()
{
    startTextBox->clear();
    endTextBox->clear();
    stepTextBox->clear();
    resultListBox->clear();
}

bool MainWindow::validateInput()
{
    try
    {
        double start = startTextBox->text().toDouble();
        double end = endTextBox->text().toDouble();
        double step = stepTextBox->text().toDouble();

        if (start > end)
        {
            throw std::invalid_argument("Invalid interval, start can't be lower than end");
        }

        if (start > 100 || end > 100)
        {
            throw std::invalid_argument("Invalid input values. Please enter valid INTEGER numbers less than 100.");
        }

        if (step <= 0)
        {
            throw std::invalid_argument("Invalid input values. Step should be bigger than 0.");
        }

        if (step >= (end - start))
        {
            throw std::invalid_argument("Invalid input values. Step should be less than difference between end and start.");
        }

        if (start < 0 || end < 0)
        {
            throw std::invalid_argument("Invalid input values. Start and end of interval can't be lower than 0.");
        }

        return true;
    }
    catch (const std::exception& ex)
    {
        QMessageBox::critical(this, "Error", ex.what());
    }

    return false;
}
