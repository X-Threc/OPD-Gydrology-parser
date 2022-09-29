#include "mainwindow.h"

//функция сохранения файла
void savefiledatas(vector<vector<QString>> vec,char* filesname);



MainWindow::MainWindow(QWidget *pwgt,int vis):QWidget(pwgt)
{
    resize(100,100);
    f_pars = new QPushButton();
        f_pars->setText(QString::fromLocal8Bit("Выбрать файл языка описания данных"));

    f_data= new QPushButton();
        f_data->setText(QString::fromLocal8Bit("Выбрать файл с Данными"));

    f_start= new QPushButton();
        f_start->setText(QString::fromLocal8Bit("Запуск программы"));

    f_save= new QPushButton();
        f_save->setText(QString::fromLocal8Bit("&Сохранить полученный результат"));

    QPushButton* quit = new QPushButton("&Quit");
    f_start->setDisabled(vis);//отключение кнопки start, при включении программы
    f_save->setDisabled(vis);//отключение кнопки save, при включении программы

    connect(f_pars, SIGNAL(clicked()), SLOT(Button_is_pars()) );
    connect(f_data,  SIGNAL(clicked()), SLOT(Button_is_data())  );

    connect(f_start, SIGNAL(clicked()), SLOT(Button_is_start()) );
    connect(f_save,  SIGNAL(clicked()), SLOT(Button_is_save())  );
    connect(quit,  SIGNAL(clicked()), qApp,     SLOT(quit())  );


    Label_pars = new QLabel("");
    Label_data = new QLabel("");
    QVBoxLayout* pvbxLayout1 = new QVBoxLayout;
    QVBoxLayout* pvbxLayout2 = new QVBoxLayout;
    QHBoxLayout* phbxLayout = new QHBoxLayout;
    QVBoxLayout* pvbxLayout3 = new QVBoxLayout;

    pvbxLayout1->addWidget(Label_pars);
    pvbxLayout1->addWidget(f_pars);
    pvbxLayout2->addWidget(Label_data);
    pvbxLayout2->addWidget(f_data);
    phbxLayout->addLayout(pvbxLayout1);
    phbxLayout->addLayout(pvbxLayout2);

    pvbxLayout3->addLayout(phbxLayout);
    pvbxLayout3->addWidget(f_start);
    pvbxLayout3->addWidget(f_save);
    pvbxLayout3->addWidget(quit);

    setLayout(pvbxLayout3);
}

void MainWindow::Button_is_pars()
{
    fname = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.DDL *.ddl");
    f_pars->setText(fname);
    dis1=0;

    Label_pars->setText(QString::fromLocal8Bit("файл получен"));
    if(fname=="")
    {
        dis1=1;
        f_start->setDisabled(true);
        Label_pars->setText(QString::fromLocal8Bit("файл не получен"));
        f_pars->setText(QString::fromLocal8Bit("Выбрать файл языка описания данных"));
    }

    if((dis1==0)&&(dis2==0))
    {
        str.clear();
        f_start->setDisabled(false);
        f_save->setDisabled(true);
        f_start->setText(QString::fromLocal8Bit("Запуск программы"));
    }


}

void MainWindow::Button_is_data(){

    fname1 = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.6");
    f_data->setText(fname1);
    dis2=0;

    Label_data->setText(QString::fromLocal8Bit("файл получен"));
    if(fname1=="")
    {
        dis2=1;
        f_start->setDisabled(true);
        Label_data->setText(QString::fromLocal8Bit("файл не получен"));
        f_data->setText(QString::fromLocal8Bit("Выбрать файл с Данными"));
    }

    if((dis1==0)&&(dis2==0))
    {
        str.clear();
        f_start->setDisabled(false);
        f_save->setDisabled(true);
        f_start->setText(QString::fromLocal8Bit("Запуск программы"));
    }
}





void MainWindow::Button_is_start()
{
    QByteArray ba = fname.toLocal8Bit();
    QByteArray ba1 = fname1.toLocal8Bit();
    char* p = ba.data();
    char* p1 = ba1.data();

    file.setpars(p);
    file.setdata(p1);
    file.start();
    vector<vector<string>> vec=file.getdata();
    for(int i=0;i<vec.size();i++)
    {
        vector<QString> stroks;
        for(int j=0;j<vec[i].size();j++)
        {
            string buf=vec[i][j];
            const char*cbuf=buf.c_str();
            QString stroka=QString::fromLocal8Bit(cbuf);
            stroks.push_back(stroka);


        }
        str.push_back(stroks);
    }


    f_start->setText(QString::fromLocal8Bit("Программа выполнена."));
    f_save->setDisabled(false);
    f_start->setDisabled(true);
}


void MainWindow::Button_is_save()
{
    QString fdata = QFileDialog::getSaveFileName(0,"Save Dialog","","*.txt");
    QByteArray ba = fdata.toLocal8Bit();
    char* p = ba.data();
    savefiledatas(str,p);
}





void savefiledatas(vector<vector<QString>> vec,char* filesname)
{
    QFile file(filesname);
    if (file.open(QIODevice::WriteOnly))
    {
    for(int i=0;i<vec.size();i++)
    {
        for(int j=0;j<vec[i].size();j++)
        {
            file.write(vec[i][j].toLocal8Bit());
            file.write("\n");
        }
      file.write("\n");
      file.write("--------------------------------------------------------------------------------------\n");
      file.write("\n");
    }
    }
}













