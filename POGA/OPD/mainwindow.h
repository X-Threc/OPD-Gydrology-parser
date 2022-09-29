#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtWidgets>
#include<QString>
#include <QFileDialog>
#include<QFile>
#include"mainf.h"
#include "head.h"

//������� ����
class MainWindow : public QWidget
{
    Q_OBJECT
private:
    QPushButton* f_pars;//������ ��������� ���
    QPushButton* f_data;//������ ��������� �������� �����
    QPushButton* f_start;//������ ������� �������� � ��������� ������
    QPushButton* f_save;//������ ���������� ����� � �������
    QLabel* Label_pars;
    QLabel* Label_data;
    mainfile file;

    QString fname;
    QString fname1;

    vector<vector<QString>> str;

    int dis1=1;
    int dis2=1;
public:
    MainWindow(QWidget* pwgt=0,int vis=1);//����������� �� ���������� �����, ���, ���
public slots:
    void Button_is_pars();
    void Button_is_data();
    void Button_is_start();
    void Button_is_save();
};


#endif // MAINWINDOW_H
