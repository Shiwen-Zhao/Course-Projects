#pragma once
#include <iostream>
#include <string>
#include "Person.h"
using namespace std;

class Student :public Person {
public:
	string m_college;
	string m_major;
	double m_score1;
	double m_score2;
	Student(string, string, int, string, string, string, double, double);
	virtual void showInfo();
};