#pragma once
#include <iostream>
#include <string>
using namespace std;

class Person {
public:
	string m_name;
	string m_sex;
	int m_age;
	string m_id;
	string m_key;
	virtual void showInfo() = 0;
};