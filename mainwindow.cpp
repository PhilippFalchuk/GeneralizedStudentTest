#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "linalg.h"

using namespace alglib;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVector<QVector<double>> arrayL;

    QVector<QVector<double>> arrayK;

    arrayL.append({8, 60, 58});
    arrayL.append({8, 156, 68});
    arrayL.append({8, 90, 37});
    arrayL.append({6.1, 44, 27});
    arrayL.append({7.4, 207, 31});
    arrayL.append({7.4, 120, 32});
    arrayL.append({8.4, 65, 43});
    arrayL.append({8.1, 237, 45});
    arrayL.append({8.3, 57, 60});
    arrayL.append({7.0, 94, 43});
    arrayL.append({8.5, 86, 40});
    arrayL.append({8.4, 52, 48});
    arrayL.append({7.9, 146, 52});

    //qDebug() << arrayL;

    arrayK.append({6.2, 49, 30});
    arrayK.append({5.6, 31, 23});
    arrayK.append({5.8, 42, 22});
    arrayK.append({5.7, 42, 14});
    arrayK.append({6.2, 40, 23});
    arrayK.append({6.4, 49, 18});
    arrayK.append({5.8, 31, 17});
    arrayK.append({6.4, 31, 19});
    arrayK.append({5.4, 62, 26});
    arrayK.append({5.4, 42, 16});

    QVector<double> meanL(arrayL[0].size());
    QVector<double> meanK(arrayK[0].size());

    for(int i = 0; i < arrayL.size(); i++)
    {
        meanL[0] += arrayL[i][0];
        meanL[1] += arrayL[i][1];
        meanL[2] += arrayL[i][2];
    }

    for(int i = 0; i < arrayK.size(); i++)
    {
        meanK[0] += arrayK[i][0];
        meanK[1] += arrayK[i][1];
        meanK[2] += arrayK[i][2];
    }

    for(int i = 0; i < meanL.size(); i++)
    {
        meanK[i] /= arrayK.size();
        meanL[i] /= arrayL.size();
    }




//    double testCovMat = 0;

//    for(int i = 0; i < arrayL.size(); i++)
//    {
//        testCovMat += (arrayL[i][0] - meanL[0])*(arrayL[i][0] - meanL[0]);
//    }

//    qDebug() << testCovMat / (arrayL.size() -1);


    QVector<QVector<double>> covMatrL(3);
    for(int i = 0; i < covMatrL.size(); i++)
    {
        covMatrL[i].resize(3);
    }

    for(int i = 0; i < covMatrL.size(); i++)
    {
        for(int j = 0; j < covMatrL[i].size(); j++)
        {
            for(int k = 0; k < arrayL.size(); k++)
            {
                covMatrL[i][j] += (arrayL[k][i] - meanL[i])*(arrayL[k][j] - meanL[j]);
            }
        }
    }

    for(int i = 0; i < covMatrL.size(); i++)
    {
        for(int j = 0; j < covMatrL[i].size(); j++)
        {
            covMatrL[i][j] /= arrayL.size() - 1;
        }
    }



    QVector<QVector<double>> covMatrK(3);
    for(int i = 0; i < covMatrK.size(); i++)
    {
        covMatrK[i].resize(3);
    }

    for(int i = 0; i < covMatrK.size(); i++)
    {
        for(int j = 0; j < covMatrK[i].size(); j++)
        {
            for(int k = 0; k < arrayK.size(); k++)
            {
                covMatrK[i][j] += (arrayK[k][i] - meanK[i])*(arrayK[k][j] - meanK[j]);
            }
        }
    }

    for(int i = 0; i < covMatrK.size(); i++)
    {
        for(int j = 0; j < covMatrK[i].size(); j++)
        {
            covMatrK[i][j] /= arrayK.size() - 1;
        }
    }

    for(int i = 0; i < covMatrL.size(); i++)
    {
        qDebug() << covMatrL[i];
    }

    qDebug() << "  ";
    qDebug() << "  ";

    for(int i = 0; i < covMatrK.size(); i++)
    {
        qDebug() << covMatrK[i];
    }

    QVector<QVector<double>> tempSumMatrix(3);
    for(int i = 0; i < tempSumMatrix.size(); i++)
    {
        tempSumMatrix[i].resize(3);
    }

    for(int i = 0; i < tempSumMatrix.size(); i++)
    {
        for(int j = 0; j < tempSumMatrix[i].size(); j++)
        {
            tempSumMatrix[i][j] = (covMatrL[i][j]/13) + (covMatrK[i][j]/10);
        }
    }

    qDebug() << " ";
    qDebug() << " ";

    for(int i = 0; i < tempSumMatrix.size(); i++)
    {
        qDebug() << tempSumMatrix[i];
    }






}

MainWindow::~MainWindow()
{
    delete ui;
}

