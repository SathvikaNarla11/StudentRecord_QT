#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <vector>
#include "Student.h"
#include <string>
#include <QString>
#include <iostream>
#include <fstream>
#include <QMessageBox>
#include <QCheckBox>
#include <QRegExpValidator>
#include <QTextStream>
#include <QDebug>
#include <QFile>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonAddRecord_clicked();

    void on_pushButtonShow_clicked();

    void on_pushButtonSave_clicked();

    void on_pushButtonRead_clicked();

    void on_pushButtonClear_clicked();

    void on_pushButtonNext_clicked();

    void on_checkBoxFemale();

    void on_checkBoxMale();


private:
    Ui::MainWindow *ui;
    std::vector<Student> StudentVec;
    Student stdObj;
    char str[80];
    QString showData = "";
    int currentStudentIndex = 0;
    QString line;
    QStringList data;

};
#endif // MAINWINDOW_H
