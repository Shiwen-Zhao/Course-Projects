#include "Student.h"

Student::Student(string name, string sex, int age, string id, string college, string major, double score1, double score2) {
	m_name = name;
	m_sex = sex;
	m_age = age;
	m_id = id;
	m_key = "123456";
	m_college = college;
	m_major = major;
	m_score1 = score1;
	m_score2 = score2;
}


void Student::showInfo() {
	cout << "姓名: " << m_name << "\t";
	cout << "性别: " << m_sex << "\t";
	cout << "年龄: " << m_age << "\t";
	cout << "学号: " << m_id << "\t";
	cout << "学院: " << m_college << "\t";
	cout << "专业: " << m_major << "\t";
	cout << "分数1: " << m_score1 << "\t";
	cout << "分数2: " << m_score2 << endl;
}