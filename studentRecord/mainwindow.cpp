#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //    auto s = ui->lineEdit_name->text();
    //    connect(ui->lineEdit_name,SIGNAL(textChanged(QString)),ui->textEdit,SLOT(setPlainText(QString)));
    //    connect(ui->lineEdit_name,SIGNAL(textChanged(QString)),ui->pushButton,SLOT(on_some_pushButton_clicked(s)));

    connect(ui->pushButtonAddRecord,&QPushButton::pressed,this,&MainWindow::on_pushButtonAddRecord_clicked);
    connect(ui->pushButtonShow,&QPushButton::clicked,this,&MainWindow::on_pushButtonShow_clicked);


    //    connect(ui->pushButtonAddRecord,SIGNAL(clicked),this,SLOT(on_pushButtonAddRecord_clicked()));

    //    connect(ui->pushButtonShow,SIGNAL(clicked),this,SLOT(on_pushButtonShow_clicked));

    connect(ui->pushButtonSave,SIGNAL(clicked),this,SLOT(on_pushButtonAddSave_clicked()));

    connect(ui->checkBoxFemale,&QCheckBox::stateChanged,this,&MainWindow::on_checkBoxFemale);

    connect(ui->checkBoxMale,&QCheckBox::stateChanged,this,&MainWindow::on_checkBoxMale);

    connect(ui->pushButtonRead,&QPushButton::clicked,this,&MainWindow::on_pushButtonRead_clicked);

    QRegularExpressionValidator *validator = new QRegularExpressionValidator(QRegularExpression("[A-Za-z\\s]{40}"),this);
    ui->lineEdit_name->setValidator(validator);

    QRegularExpressionValidator *validator2 = new QRegularExpressionValidator(QRegularExpression("[0-9]{3}"),this);
    ui->lineEdit_age->setValidator(validator2);

    ui->lineEdit_rollno->setValidator(validator2);
    ui->lineEdit_English->setValidator(validator2);
    ui->lineEdit_Math->setValidator(validator2);
    ui->lineEdit_Science->setValidator(validator2);
    ui->lineEdit_English->setValidator(validator2);
    ui->lineEdit_Geography->setValidator(validator2);


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
    //    ifstream file("StudentRecord.txt");

    //    while (file.getline(str,80))
    //    {
    //        ui->textEditShow->setText(str);
    //    }

    on_pushButtonClear_clicked();
    QFile file("StudentRecord.txt");
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream in(&file);
        QString line = in.readLine();
        QStringList data = line.split(',');

        QString record;
        record += ("Name: " + data[0] + "\nAge : " + data[1] + "\nRoll No. : " + data[2] + "\nGender : " + data[3] +
          "\nEnglish : " + data[5] + "\nMath : " + data[7] +"\nScience : " + data[9] + "\nGeography : " + data[11] + "\nHistory : " + data[13]);
        ui->textEditShow->setText(record);

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

    file.close();

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

void MainWindow::on_pushButtonNext_clicked()
{
    QFile file("StudentRecord.txt");
    vector<QString> s;

    static int count = 0;
    count++;

    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream in(&file);

        while (!in.atEnd())
        {

            QString line = in.readLine();
            s.push_back(line);
        }
        int l = s.size();
        if(count == l)
        {
            QMessageBox::information(this,"Pop Up","End of the file.");
            return;
        }

        on_pushButtonClear_clicked();

        for(int i = count; i <= count; i++)
        {
            qDebug () << s[i];
            QStringList data = s[i].split(',');
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

            //************************************
            QString record;
            record += ("Name: " + data[0] + "\nAge : " + data[1] + "\nRoll No. : " + data[2] + "\nGender : " + data[3] +
              "\nEnglish : " + data[5] + "\nMath : " + data[7] +"\nScience : " + data[9] + "\nGeography : " + data[11] + "\nHistory : " + data[13]);
            ui->textEditShow->setText(record);
        }
    }

    file.close();

}

