#pragma once
#ifndef _LOGICAL_H_
#define _LOGICAL_H_

#include <map>
#include <functional>
#include <QString>

#define MYBTDBEGIN namespace MyBtd {
#define MYBTDEND }
#define LD long double

MYBTDBEGIN
enum class BtnType : std::size_t {
	Num, // 数字
	Op, // 运算符
	Point, // 点
	Clear, // C
	Back, //退格
	Equal, // =
	Negate, // 相反数
	Reciprocal, // 倒数
	Percent // 百分比
};
template<typename T>
void printToOut(QString& strEdit,T point, const QString& btn) {
	strEdit += btn;
	point->ui.lineEdit->setText(strEdit);
}
// 算法
using MyMath = std::map<const QString,
	std::function<const LD(const LD,const LD)>>;

struct Reciprocal {
	inline const LD operator()(const LD value)const;
};
struct Percent{
	inline const LD operator()(const LD value)const;
};
MyMath& getMathMap();
MYBTDEND



#endif // !_LOGICAL_H_