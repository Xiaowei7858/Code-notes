#include"Date.h"

Date::Date(int year, int month, int day) {
	if (year >= 0 && month >= 0
		&& month < 13 && day > 0
		&& day < GetMonthDay(year, month)) {
		_year = year;
		_month = month;
		_day = day;
	}
	else {
		cout << "���ڷǷ�" << endl;
	}
}

void Date::Print() {
	cout << _year << "-" << _month << "-" << _day << endl;
}

int Date::GetMonthDay(int year, int month) {
	static int daysArray[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	int days = daysArray[month];
	if (month == 2 &&
		(year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
	{
		days = 29;
	}
	return days;
}

Date& Date::operator+=(int day) {
	if (day < 0) {
		return *this -= -day;
	}
	_day += day;
	//�����Ƿ�Ϸ�
	while (_day > GetMonthDay(_year, _month)) {
		_day -= GetMonthDay(_year, _month);
		_month++;
		if (_month == 13) {
			_year += 1;
			_month = 1;
		}
	}

	return *this;
}

Date Date::operator+(int day) {
	//Date ret(*this);
	//ret._day += day;
	//while (ret._day > GetMonthDay(ret._year, ret._month)) {
	//	ret._day -= GetMonthDay(ret._year, ret._month);
	//	ret._month++;
	//	if (_month == 13) {
	//		ret._year++;
	//		ret._month = 1;
	//	}
	//}

	Date ret(*this);
	ret += day;

	//���˺������ͻ����٣���˲���ʹ������
	return ret;
}

Date& Date::operator-=(int day) {
	if (day < 0) {
		return *this += -day;
	}
	_day -= day;
	//�����Ƿ�Ϸ�
	while (_day < 1) {
		_month--;
		if (_month == 0) {
			_year -= 1;
			_month = 12;
		}
		_day += GetMonthDay(_year, _month);
	}

	return *this;
}

Date Date::operator-(int day) {
	Date ret(*this);
	ret -= day;
	return ret;
}

//ǰ��++
Date& Date::operator++() {
	*this += 1;
	return *this;
}

//����++
Date Date::operator++(int) {
	Date ret(*this);
	*this += 1;

	return ret;
}

bool Date::operator==(const Date& d) {
	return _year == d._year
		&& _month == d._month
		&& _day == d._day;
}

bool Date::operator!=(const Date& d) {
	return !(*this == d);
}

bool Date::operator<(const Date& d) {
	if (_year > d._year) {
		return true;
	}
	else if(_year == d._year){
		if (_month > d._month)
			return true;
		else if (_month == d._month) {
			if (_day > d._day)
				return true;
		}
	}
	return false;
}

bool Date::operator<=(const Date& d) {
	return *this < d && *this == d;
}

bool Date::operator>(const Date& d) {
	return !(*this < d);
}

bool Date::operator>=(const Date& d) {
	return *this > d && *this == d;
}

int Date::operator-(const Date& d) {
	Date max(*this), min(d);
	int flag = 1;
	if (*this < d) {
		max = d;
		min = *this;
		flag = -1;
	}

	int n = 0;
	while (min != max) {
		++n;
		++min;
	}

	return n * flag;
}


// �������캯��
Date::Date(const Date& d) {
	_year = d._year;
	_month = d._month;
	_day = d._day;
}
// ��ֵ���������
// d2 = d3 -> d2.operator=(&d2, d3)
Date& Date::operator=(const Date& d) {
	_year = d._year;
	_month = d._month;
	_day = d._day;
	return *this;
}
// ����--
Date Date::operator--(int) {
	Date ret(*this);
	*this -= 1;
	return ret;
}
// ǰ��--
Date& Date::operator--() {
	*this -= 1;
	return *this;
}