#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <vector>
#include "Student.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//private slots:
//    void on_pushButton_clicked();

private slots:
    void on_pushButtonAddRecord_clicked();

    void on_pushButtonShow_clicked();

    void on_pushButtonSave_clicked();

    void on_checkBoxFemale();

    void on_checkBoxMale();


private:
    Ui::MainWindow *ui;
    std::vector<Student> StudentVec;
    Student stdObj;
//    Student s;

};
#endif // MAINWINDOW_H
