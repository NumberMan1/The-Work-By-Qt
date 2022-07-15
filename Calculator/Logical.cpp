#include "Calculator.h"

MyBtd::MyMath& MyBtd::getMathMap() {
    static MyMath mathMap = {
        {QString("-"), std::minus<const LD>()},
        {QString("+"), std::plus<const LD>()},
        {QString("×"), std::multiplies<const LD>()},
        {QString("÷"), std::divides<const LD>()}
    };
    return mathMap;
}

inline const LD MyBtd::Reciprocal::operator()(const LD value)const { return 1 / value; }

inline const LD MyBtd::Percent::operator() (const LD value)const { return value / 100; }