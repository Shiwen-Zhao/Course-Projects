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
	cout << "����: " << m_name << "\t";
	cout << "�Ա�: " << m_sex << "\t";
	cout << "����: " << m_age << "\t";
	cout << "ѧ��: " << m_id << "\t";
	cout << "ѧԺ: " << m_college << "\t";
	cout << "רҵ: " << m_major << "\t";
	cout << "����1: " << m_score1 << "\t";
	cout << "����2: " << m_score2 << endl;
}