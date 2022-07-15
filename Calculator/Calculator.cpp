#include "Calculator.h"

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent), mMap(MyBtd::getMathMap()), mNum1(),
    mNum2(), mOp(), mPointFlag(false), mPercentFlag(false),
    mNegateFlag(false), mReciprocalFlag(false), mResult(0) {
    ui.setupUi(this);
    //QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    //db.setHostName("127.0.0.1");
    //db.setPort(3306);
    //db.setDatabaseName("MysqlText"); // 不是Database,记得别填错,是datasourse
    //db.setUserName("number");
    //db.setPassword("123456");
    //bool ok = db.open();
    //if (ok) {
    //    QMessageBox::information(this, "infor", "link success");
    //}
    //else {
    //    QMessageBox::information(this, "infor", "link failed");
    //    qDebug() << "error open database because" << db.lastError().text();
    //}
    
    buttonStart();
}

void ::Calculator::buttonStart() {
    using QPT = QPushButton;
    using BtnType =  MyBtd::BtnType;

    // Number
    connect(ui.btn0, &QPT::clicked, [this]() {
        clickBroadcast(BtnType::Num, "0");
        });
    connect(ui.btn1, &QPT::clicked, [this]() {
        clickBroadcast(BtnType::Num, "1");
        });
    connect(ui.btn2, &QPT::clicked, [this]() {
        clickBroadcast(BtnType::Num, "2");
        });
    connect(ui.btn3, &QPT::clicked, [this]() {
        clickBroadcast(BtnType::Num, "3");
        });
    connect(ui.btn4, &QPT::clicked, [this]() {
        clickBroadcast(BtnType::Num, "4");
        });
    connect(ui.btn5, &QPT::clicked, [this]() {
        clickBroadcast(BtnType::Num, "5");
        });
    connect(ui.btn6, &QPT::clicked, [this]() {
        clickBroadcast(BtnType::Num, "6");
        });
    connect(ui.btn7, &QPT::clicked, [this]() {
        clickBroadcast(BtnType::Num, "7");
        });
    connect(ui.btn8, &QPT::clicked, [this]() {
        clickBroadcast(BtnType::Num, "8");
        });
    connect(ui.btn9, &QPT::clicked, [this]() {
        clickBroadcast(BtnType::Num, "9");
        });

    // Operator
    connect(ui.btnPlus, &QPT::clicked, [this]() {
        clickBroadcast(BtnType::Op, "+");
        });
    connect(ui.btnMinus, &QPT::clicked, [this]() {
        clickBroadcast(BtnType::Op, "-");
        });
    connect(ui.btnMultiplies, &QPT::clicked, [this]() {
        clickBroadcast(BtnType::Op, "×");
        });
    connect(ui.btnDivides, &QPT::clicked, [this]() {
        clickBroadcast(BtnType::Op, "÷");
        });

    // Clear 
    connect(ui.btnCE, &QPT::clicked, [this]() {
        clickBroadcast(BtnType::Clear, "Clear");
        });
    connect(ui.btnC, &QPT::clicked, [this]() {
        clickBroadcast(BtnType::Clear, "Clear");
        });

    // others
    connect(ui.btnBack, &QPT::clicked, [this]() {
        clickBroadcast(BtnType::Back, "Back");
        });
    connect(ui.btnPoint, &QPT::clicked, [this]() {
        clickBroadcast(BtnType::Point, ".");
        });
    connect(ui.btnNegate, &QPT::clicked, [this]() {
        clickBroadcast(BtnType::Negate, "Negate");
        });
    connect(ui.btnResult, &QPT::clicked, [this]() {
        clickBroadcast(BtnType::Equal, "=");
        });
    connect(ui.btnReciprocal, &QPT::clicked, [this]() {
        clickBroadcast(BtnType::Reciprocal, "1/x");
        });
    connect(ui.btnPercent, &QPT::clicked, [this]() {
        clickBroadcast(BtnType::Percent, "%");
        });
}

void ::Calculator::clickBroadcast(const MyBtd::BtnType& type,const QString& btn) {
    using BtnType = MyBtd::BtnType;
    using MyBtd::printToOut;
    static QString strEdit("");
    mPointFlag = false;

    switch (type) {
        case BtnType::Num: {
            if (mOp.isEmpty()) {
                mNum1 += btn;
            } else {
                mNum2 += btn;
            }
            printToOut<decltype(this)>(strEdit, this, btn);
            break;
        }
        case BtnType::Op: {
            if (!mOp.isEmpty()) { // 多个运算符
                doMath();
                mNum1 = QString::number(static_cast<double>(mResult));
                mNum2.clear();
            }
            if (mOp.isEmpty()) {
                mOp += btn;
                printToOut<decltype(this)>(strEdit, this, btn);
            } else {
                if (btn[0] != strEdit.last(1)) { // 查看最后一个字符
                    mOp = btn;
                    printToOut<decltype(this)>(strEdit, this, btn);
                }
            }
            break;
        }
        case BtnType::Point: {
            if (mOp.isEmpty()) { // num1
                if (!mNum1.isEmpty() && !mNum1.contains(".")) { // 是否包含.
                    mNum1 += btn;
                    mPointFlag = true;
                    printToOut<decltype(this)>(strEdit, this, btn);
                }
            } else {
                if (!mNum2.isEmpty() && !mNum2.contains(".")) {
                    mNum2 += btn;
                    mPointFlag = true;
                    printToOut<decltype(this)>(strEdit, this, btn);
                }
            }
            break;
        }
        case BtnType::Clear: {
            mNum1.clear();
            mNum2.clear();
            mOp.clear();
            mResult = 0;
            strEdit.clear();
            this->ui.lineEdit->setText(strEdit);
            break;
        }
        case BtnType::Back: {
            if (!mNum1.isEmpty() && !mNum2.isEmpty() && !mOp.isEmpty()) {
                mNum2.chop(1); // 指定删除1个字符
                strEdit.chop(1);
            } else if (!mNum1.isEmpty() && !mOp.isEmpty()) {
                mOp.chop(1);
                QMessageBox box(this);
                box.setText("如果有多个运算符尝试退格,程序会出BUG,只能C或CE");
                box.exec();
                strEdit.chop(1);
            } else if (!mNum1.isEmpty()) {
                mNum1.chop(1);
                strEdit.chop(1);
            }
            ui.lineEdit->setText(strEdit);
            break;
        }
        case BtnType::Equal: {
            if (mNum1.isEmpty() || mNum2.isEmpty() || mOp.isEmpty()) { break; }
            if (mOp == "÷" && mNum2 == "0") {
                ui.lineEdit->setText("除数不能为0");
                break;
            }
            doMath();
            
            // 百分比
            if (mPercentFlag) {
                ui.lineEdit->setText(QString::number(
                    static_cast<double>(mResult / 100)));
                break;
            } else if (mNegateFlag) { // 相反数
                ui.lineEdit->setText(QString::number(
                    static_cast<double>(-mResult)));
                break;
            } else if (mReciprocalFlag) { // 倒数
                ui.lineEdit->setText(QString::number(
                    static_cast<double>(1 / mResult)));
                break;
            } else {
                ui.lineEdit->setText(QString::number(
                    static_cast<double>(mResult)));
                break;
            }
        }
        case BtnType::Negate: {
            if (mNegateFlag) {
                mNegateFlag = false;
                QMessageBox box(this);
                box.setText("相反数形式关闭\n多种形式只能同时使用1种\n\
优先级为百分比 > 相反数 > 倒数");
                box.exec();
            }
            else {
                mNegateFlag = true;
                QMessageBox box(this);
                box.setText("相反数形式开启\n多种形式只能同时使用1种\n\
优先级为百分比 > 相反数 > 倒数");
                box.exec();
            }
            break;
        }
        case BtnType::Reciprocal: {
            if (mReciprocalFlag) {
                mReciprocalFlag = false;
                QMessageBox box(this);
                box.setText("倒数形式关闭\n多种形式只能同时使用1种\n\
优先级为百分比 > 相反数 > 倒数");
                box.exec();
            }
            else {
                mReciprocalFlag = true;
                QMessageBox box(this);
                box.setText("倒数形式开启\n多种形式只能同时使用1种\n\
优先级为百分比 > 相反数 > 倒数");
                box.exec();
            }
            break;
        }
        case BtnType::Percent: {
            if (mPercentFlag) {
                mPercentFlag = false;
                QMessageBox box(this);
                box.setText("百分比形式关闭\n多种形式只能同时使用1种\n\
优先级为百分比 > 相反数 > 倒数");
                box.exec();
            } else {
                mPercentFlag = true;
                QMessageBox box(this);
                box.setText("百分比形式开启\n多种形式只能同时使用1种\n\
优先级为百分比 > 相反数 > 倒数");
                box.exec();
            }
            break;
        }
        default: break;
    }
    
}

void Calculator::doMath() {
    LD num1 = mNum1.toDouble();
    LD num2 = mNum2.toDouble();
    if (mOp == "÷" && mNum2 == "0") { return; }
    mResult = mMap[mOp](num1, num2);
}

Calculator::~Calculator() {}