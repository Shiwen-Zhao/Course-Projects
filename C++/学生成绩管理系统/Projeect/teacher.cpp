#include "Teacher.h"
Teacher::Teacher() {
	m_name = "��ʦ";
	m_sex = "δ֪";
	m_age = 0;
	m_id = "123456";
	m_key = "123456";
	m_title = "δ֪";
}

Teacher::Teacher(string name, string sex, int age, string id, string title) {
	m_name = name;
	m_sex = sex;
	m_age = age;
	m_id = id;
	m_key = "123456";
	m_title = title;
}

void Teacher::showInfo() {
	cout << "����: " << m_name << "\t";
	cout << "�Ա�: " << m_sex << "\t";
	cout << "����: " << m_age << "\t";
	cout << "����: " << m_id << "\t";
	cout << "ְλ: " << m_title << endl;
}