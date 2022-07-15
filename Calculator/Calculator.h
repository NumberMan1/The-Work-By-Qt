#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Calculator.h"
#include "Logical.hpp"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QLabel>
#include <QPushButton>
#include <vector>

class Calculator : public QMainWindow
{
    Q_OBJECT
    template<typename T>
    friend void MyBtd::printToOut(QString& strEdit,
        T point, const QString& btn);

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::CalculatorClass ui;
    MyBtd::MyMath& mMap;
    QString mNum1;
    QString mNum2;
    QString mOp;
    bool mPointFlag; // .是否合法 true 合法
    bool mPercentFlag; // 是否为百分形式
    bool mNegateFlag; // 是否为相反数形式
    bool mReciprocalFlag; // 是否为倒数形式
    LD mResult;
    void buttonStart();
    void doMath();

public slots:
    void clickBroadcast(const MyBtd::BtnType& type,const QString& btn);
};
