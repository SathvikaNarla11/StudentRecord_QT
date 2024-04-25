#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QString>
#include <Student.h>
#include <iostream>
#include <fstream>
#include <QMessageBox>
#include <QCheckBox>
#include <QRegExpValidator>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //    auto s = ui->lineEdit_name->text();
    //    connect(ui->lineEdit_name,SIGNAL(textChanged(QString)),ui->textEdit,SLOT(setPlainText(QString)));
    //    connect(ui->lineEdit_name,SIGNAL(textChanged(QString)),ui->pushButton,SLOT(on_some_pushButton_clicked(s)));

//      connect(ui->pushButtonAddRecord,&QPushButton::clicked,this,&MainWindow::on_pushButtonAddRecord_clicked);
//      connect(ui->pushButtonAddRecord,&QPushButton::clicked,this,&MainWindow::on_pushButtonShow_clicked);


    connect(ui->pushButtonAddRecord,SIGNAL(clicked()),this,SLOT(on_pushButtonAddRecord_clicked));

    connect(ui->pushButtonShow,SIGNAL(clicked()),this,SLOT(on_pushButtonShow_clicked()));

    connect(ui->checkBoxFemale,&QCheckBox::stateChanged,this,&MainWindow::on_checkBoxFemale);

    connect(ui->pushButtonSave,&QPushButton::clicked, this,&MainWindow::on_pushButtonSave_clicked);

    connect(ui->checkBoxMale,&QCheckBox::stateChanged,this,&MainWindow::on_checkBoxMale);

    QRegularExpressionValidator *validator = new QRegularExpressionValidator(QRegularExpression("[A-Za-z\\s]{40}"),this);
    ui->lineEdit_name->setValidator(validator);

    QRegularExpressionValidator *validator2 = new QRegularExpressionValidator(QRegularExpression("[0-9]{3}"),this);
    ui->lineEdit_age->setValidator(validator2);

    QRegularExpressionValidator *validator3 = new QRegularExpressionValidator(QRegularExpression("[0-9]{100}"),this);
    ui->lineEdit_rollno->setValidator(validator3);


}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButtonAddRecord_clicked()
{

    stdObj.name = ui->lineEdit_name->text().toStdString();
    stdObj.rno = ui->lineEdit_rollno->text().toInt();
    stdObj.age = ui->lineEdit_age->text().toInt();

    stdObj.SubjectsMap["English"] = ui->lineEdit_English->text().toInt();
    stdObj.SubjectsMap["Maths"] = ui->lineEdit_Math->text().toInt();
    stdObj.SubjectsMap["Science"] = ui->lineEdit_Science->text().toInt();
    stdObj.SubjectsMap["Geography"] = ui->lineEdit_Geography->text().toInt();
    stdObj.SubjectsMap["History"] = ui->lineEdit_History->text().toInt();

    StudentVec.push_back(stdObj);

    QMessageBox::information(this,"Student Record","Student data is added.");
}


void MainWindow::on_pushButtonShow_clicked()
{
    QString showData;
    //    for(const auto &obj : StudentVec)
    for(unsigned int i=0;i < StudentVec.size();i++)
    {
        showData += "Name : ";
        showData += StudentVec[i].name.c_str();
        showData += "\nAge : ";
        showData += QString::number(StudentVec[i].age);
        showData += "\nRoll No : ";
        showData += QString::number(StudentVec[i].rno);
        showData += "\nSex : ";
        showData += StudentVec[i].sex.c_str();

        showData += "\n";
        showData += "\nMarks of the student ";
        //        for(map<Student> sub : obj.SubjectsMap)
        //        for(int j=SubjectsMap.begin();j!=SubjectsMap.end();j++)

        map<string,int>::iterator j;

        for(j =stdObj.SubjectsMap.begin(); j != stdObj.SubjectsMap.end();j++)
        {
            showData += "\n";
            showData += j->first.c_str();
            showData += " : ";
            showData += QString::number(j->second);
        }
        showData += "\n_______________________________";
    }
    ui->textEditShow->setText(showData);
}


void MainWindow::on_pushButtonSave_clicked()
{
    string line;
    fstream fio;

    fio.open("StudentRecord.txt", ios::app | ios::out | ios::in);

    for(const auto& obj: StudentVec)
    {
        line += (obj.name + ",");
        line += (to_string(obj.age) + ",");
        line += (to_string(obj.rno) + ",");
        line += (obj.sex + ",");
        for(const auto &sub : obj.SubjectsMap)
        {
            line += (sub.first.c_str());
            line += (":"+to_string(sub.second) + ",");
        }
        line.pop_back();
        fio << line << endl;
    }
    QMessageBox::information(this,"Student Record","Student data is saved.");
}

void MainWindow::on_checkBoxMale()
{
    if(ui->checkBoxMale->isChecked())
    {
        stdObj.sex = 'M';
        ui->checkBoxFemale->setDisabled(true);
    }
    else
    {
        ui->checkBoxFemale->setDisabled(false);
    }

}

void MainWindow::on_checkBoxFemale()
{
    if(ui->checkBoxFemale->isChecked())
    {
        stdObj.sex = 'F';
        ui->checkBoxMale->setDisabled(true);
    }
    else
    {
        ui->checkBoxMale->setDisabled(false);
    }
}



