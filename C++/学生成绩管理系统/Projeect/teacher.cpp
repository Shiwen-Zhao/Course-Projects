#include "Teacher.h"
Teacher::Teacher() {
	m_name = "教师";
	m_sex = "未知";
	m_age = 0;
	m_id = "123456";
	m_key = "123456";
	m_title = "未知";
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
	cout << "姓名: " << m_name << "\t";
	cout << "性别: " << m_sex << "\t";
	cout << "年龄: " << m_age << "\t";
	cout << "工号: " << m_id << "\t";
	cout << "职位: " << m_title << endl;
}