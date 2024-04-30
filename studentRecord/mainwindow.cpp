#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QDebug>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //    connect(ui->pushButtonAddRecord,SIGNAL(clicked),this,SLOT(on_pushButtonAddRecord_clicked()));
    //    connect(ui->pushButtonShow,SIGNAL(clicked),this,SLOT(on_pushButtonShow_clicked));

    connect(ui->pushButtonAddRecord,&QPushButton::pressed,this,&MainWindow::on_pushButtonAddRecord_clicked);
    connect(ui->pushButtonShow,&QPushButton::clicked,this,&MainWindow::on_pushButtonShow_clicked);
    connect(ui->pushButtonRead,SIGNAL(pressed),this,SLOT(on_pushButtonSave_clicked));
    connect(ui->pushButtonSave,SIGNAL(clicked),this,SLOT(on_pushButtonSave_clicked));
    connect(ui->pushButtonNext,SIGNAL(clicked),this,SLOT(on_pushButtonNext_clicked));
    connect(ui->pushButtonClear,SIGNAL(clicked),this,SLOT(on_pushButtonClear_clicked));

    connect(ui->checkBoxFemale,&QCheckBox::stateChanged,this,&MainWindow::on_checkBoxFemale);
    connect(ui->checkBoxMale,&QCheckBox::stateChanged,this,&MainWindow::on_checkBoxMale);



    QRegularExpressionValidator *validator = new QRegularExpressionValidator(QRegularExpression("[A-Za-z\\s]{40}"),this);
    ui->lineEdit_name->setValidator(validator);

    QRegularExpressionValidator *validator2 = new QRegularExpressionValidator(QRegularExpression("[0-9]{3}"),this);
    ui->lineEdit_age->setValidator(validator2);

    ui->lineEdit_rollno->setValidator(validator2);
    ui->lineEdit_Math->setValidator(validator2);
    ui->lineEdit_Science->setValidator(validator2);
    ui->lineEdit_English->setValidator(validator2);
    ui->lineEdit_Geography->setValidator(validator2);
    ui->lineEdit_History->setValidator(validator2);

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
  unsigned int i;
    for(i=0;i < StudentVec.size();i++)
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

        map<string,int>::iterator j;
        for(j =stdObj.SubjectsMap.begin(); j != stdObj.SubjectsMap.end();j++)
        {
            showData += "\n";
            showData += j->first.c_str();
            showData += " : ";
            showData += QString::number(j->second);
        }
        showData += "\n_______________________________\n";

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
            line += (","+to_string(sub.second) + ",");
        }
        line.pop_back();
        fio << line << endl;

    }

    QMessageBox::information(this,"Student Record","Student data is saved.");
}

void MainWindow::on_pushButtonRead_clicked()
{
    QFile file("StudentRecord.txt");

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Error", "Failed to open file.");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        line = in.readLine();
        data = line.split(',');

        Student student;

        student.name = data[0].toStdString();
        student.age = data[1].toInt();
        student.rno = data[2].toInt();
        student.sex = data[3].toStdString();


        for (int i = 4; i < data.size(); i += 2)
        {
            student.SubjectsMap[data[i].toStdString()] = data[i + 1].toInt();
        }

        StudentVec.push_back(student);

        qDebug() << "Contents of StudentVec:";
        for (const auto& student : StudentVec)
        {
            qDebug() << "Name: " << QString::fromStdString(student.name);
            qDebug() << "Age: " << student.age;
            qDebug() << "Roll No.: " << student.rno;

            qDebug() << "Subjects:";
            for (const auto& subject : student.SubjectsMap)
            {
                qDebug() << subject.first.c_str() << ": " << subject.second;
            }
            qDebug() << "---------------------";
        }
    }

    showData += ("Name: " + data[0] + "\nAge : " + data[1] + "\nRoll No. : " + data[2] + "\nGender : " + data[3] +
            "\nEnglish : " + data[5] + "\nMath : " + data[7] +"\nScience : " + data[9] + "\nGeography : " + data[11] + "\nHistory : " + data[13]+"\n\n");

    ui->textEditShow->setText(showData);
    ui->lineEdit_name->setText(data[0]);
    ui->lineEdit_age->setText(data[1]);
    ui->lineEdit_rollno->setText(data[2]);

    if (data[3] == "M")
    {
        ui->checkBoxMale->setChecked(true);
    }
    else if (data[3] == "F")
    {
        ui->checkBoxFemale->setChecked(true);
    }

    ui->lineEdit_English->setText(data[5]);
    ui->lineEdit_Math->setText(data[7]);
    ui->lineEdit_Science->setText(data[9]);
    ui->lineEdit_Geography->setText(data[11]);
    ui->lineEdit_History->setText(data[13]);

}



void MainWindow::on_pushButtonNext_clicked()
{
    static int count = 0;
    qDebug() << "Next button clicked";
    int l = StudentVec.size();

    qDebug() << "Number of student records in StudentVec:" << l;
    on_pushButtonClear_clicked();
    if (count < l)
    {
        qDebug() << "Displaying student record #" << (count + 1);
        qDebug() <<"name : "<< StudentVec[count].name.c_str();
        ui->lineEdit_name->setText(StudentVec[count].name.c_str());
        ui->lineEdit_age->setText(QString::number(StudentVec[count].age));
        ui->lineEdit_rollno->setText(QString::number(StudentVec[count].rno));

        if (StudentVec[count].sex == "M")
        {
            ui->checkBoxMale->setChecked(true);
        }
        else if (StudentVec[count].sex == "F")
        {
            ui->checkBoxFemale->setChecked(true);
        }
        ui->lineEdit_English->setText(QString::number(StudentVec[count].SubjectsMap["English"]));
        ui->lineEdit_Math->setText(QString::number(StudentVec[count].SubjectsMap["Maths"]));
        ui->lineEdit_Science->setText(QString::number(StudentVec[count].SubjectsMap["Science"]));
        ui->lineEdit_Geography->setText(QString::number(StudentVec[count].SubjectsMap["Geography"]));
        ui->lineEdit_History->setText(QString::number(StudentVec[count].SubjectsMap["History"]));


        QString studentInfo;
        studentInfo += ("Name: " + QString::fromStdString(StudentVec[count].name) + "\nAge : " + QString::number(StudentVec[count].age) + "\nRoll No. : "
                        + QString::number(StudentVec[count].rno));
        if (StudentVec[count].sex == "M")
        {
            studentInfo += "\nGender: M";
        }
        else if (StudentVec[count].sex == "F")
        {
            studentInfo += "\nGender: F";
        }
        studentInfo += "\n\nMarks of the student";
        for (auto it = StudentVec[count].SubjectsMap.begin(); it != StudentVec[count].SubjectsMap.end(); ++it)
        {
            studentInfo += "\n" + QString::fromStdString(it->first) + " : " + QString::number(it->second);
        }
        ui->textEditShow->setText(studentInfo);


        count++;
    }
    else
    {
        QMessageBox::information(this,"Pop Up","End of the file.");
        count = 0;
    }

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


void MainWindow::on_pushButtonClear_clicked()
{
    ui->lineEdit_name->clear();
    ui->lineEdit_rollno->clear();
    ui->lineEdit_age->clear();
    ui->checkBoxMale->setEnabled(true);
    ui->checkBoxFemale->setEnabled(true);

    ui->checkBoxMale->setChecked(false);
    ui->checkBoxFemale->setChecked(false);

    ui->lineEdit_English->clear();
    ui->lineEdit_Math->clear();
    ui->lineEdit_Science->clear();
    ui->lineEdit_Geography->clear();
    ui->lineEdit_History->clear();
    ui->textEditShow->clear();
}
