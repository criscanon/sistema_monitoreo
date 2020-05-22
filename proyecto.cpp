#include "proyecto.h"
#include "ui_proyecto.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>

#define RUTA1 "/home/alse/Documents/PROYECTO_FINAL/tm.bin "
#define RUTA2 "/home/alse/Documents/PROYECTO_FINAL/datos.txt"
#define PORT " 65000"
#define ADDRESS "186.155.208.171 "
#define LONGITUD 1000
#define CANTIDAD_VARIABLES 7
#define TV 49
#define TVOLT 3
#define TT 1

using namespace std;

Proyecto::Proyecto(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Proyecto)
{
    ui->setupUi(this);
}

Proyecto::~Proyecto()
{
    delete ui;
}

void ConvAStringNum(string &parametro)
{
    int dir_1;
    unsigned long counter1;
    dir_1 = parametro.find_first_of(':')+1;
    for (counter1=0; counter1 < sizeof(parametro)-1; counter1++)
    {
        if (parametro[dir_1]=='\0' or parametro[dir_1]=='}')
        {
            parametro[counter1]='\0';
            break;
        }
        else
        {
            parametro[counter1] = parametro[dir_1];
            dir_1++;
        }
    }
    parametro.erase(parametro.begin()+parametro.find_first_of('\0'), parametro.begin()+dir_1);
}

/*int ExtValLimDeString(int pos, int can, string optime)
{
    int i=0;
    for (i=0; pos+i < can+pos; i++)
    {
        optime[i]=optime[pos+i];
    }
    optime[i]='\0';
    cout << optime;
    optime.erase(optime.begin()+optime.find_first_of('\0'), optime.begin()+sizeof (optime));
    return 6;
}*/

void Proyecto::on_BtStart_clicked()
{
    //Definicion de variables
    const char * carnet;
    string estado1, estado2, identificacion, velocidad, frecuencia, voltaje, temperatura, tiempo;
    double NumVel, NumFre, NumVol, NumTem;
    int Tv, Tvolt=2, Tt=2;
    float LIM1, LIM2, LIM3, LIM4, LIM5, LIM6, LIM7, LIM8;
    QString c;
    string direccion;
    //ASIGNACION CODIGO CARNET
    c = ui->carnetText->toPlainText();
    carnet = c.toStdString().c_str();
    direccion += RUTA1;
    direccion += ADDRESS;
    direccion += carnet;
    direccion += PORT;

    //EJECUCION PROCESO HIJO
    system(direccion.c_str());

    //ANALISIS DATOS ADQUIRIDOS
    //Usar el archivo txt para imprimir los valores en la ui

    ifstream infile(RUTA2);
    infile >> estado1 >> estado2 >> identificacion >> velocidad >> frecuencia >> voltaje >> temperatura >> tiempo;
    ConvAStringNum(velocidad);
    ConvAStringNum(frecuencia);
    ConvAStringNum(voltaje);
    ConvAStringNum(temperatura);
    ConvAStringNum(tiempo);
    ConvAStringNum(identificacion);

    NumVel = stof(velocidad);
    NumFre = stof(frecuencia);
    NumVol = stof(voltaje);
    NumTem = stof(temperatura);

    //TIMESTAMP
    //Tiempo de operacion del motor dia/hora
    ui->vel->setText(QString::fromStdString(velocidad));
    ui->frec->setText(QString::fromStdString(frecuencia));
    ui->volt->setText(QString::fromStdString(voltaje));
    ui->temp->setText(QString::fromStdString(temperatura));
    ui->ot->setText(QString::fromStdString(tiempo));

    //CONDICIONES LIMITE
    //Determinar si supera o no el limite de operacion*/

    LIM1 = 1800-TV;
    LIM2 = 1800+TV;
    LIM3 = 60-0.05*NumFre;
    LIM4 = 60+0.05*NumFre;
    LIM5 = 120-TVOLT;
    LIM6 = 120+TVOLT;
    LIM7 = 40-TT;
    LIM8 = 40+TT;

    if((LIM1<=NumVel or NumVel<=LIM2) and (LIM3<=NumFre or NumFre<=LIM4) and (LIM5<=NumVol or NumVol<=LIM6) and (LIM7<=NumTem or NumTem<=LIM8))
    {
        ui->good->setStyleSheet("QLabel {background-color:green;}");
    }
    else
    {
        ui->danger->setStyleSheet("QLabel {background-color:red;}");
    }
}
