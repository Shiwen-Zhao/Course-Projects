#pragma once
#include <iostream>
#include <string>
#include "Person.h"
using namespace std;

class Teacher :public Person {
protected:
	string m_title;

public:
	Teacher();
	Teacher(string, string, int, string, string);
	virtual void showInfo();
};