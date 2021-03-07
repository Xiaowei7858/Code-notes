#include<iostream>
using namespace std;

class Date {
public:
	Date(int year = 1990, int month = 3, int day = 7);
	// 拷贝构造函数
	Date(const Date& d);
	// 赋值运算符重载
// d2 = d3 -> d2.operator=(&d2, d3)
	Date& operator=(const Date& d);

	int GetMonthDay(int year,int month);
	void Print();
	Date& operator+=(int day);
	Date operator+(int day);
	Date& operator-=(int day);
	Date operator-(int day);
	Date& operator++();
	Date operator++(int);
	bool operator==(const Date& d);
	int operator-(const Date& d);
	bool operator!=(const Date& d);
	bool operator<(const Date& d);
	bool operator<=(const Date& d);
	bool operator>(const Date& d);
	bool operator>=(const Date& d);
	// 后置--
	Date operator--(int);
	// 前置--
	Date& operator--();
private:
	int _year;
	int _month;
	int _day;
};