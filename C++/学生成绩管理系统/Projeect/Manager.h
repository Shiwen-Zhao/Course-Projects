#pragma once
#include <iostream>
#include <fstream>
#include "Student.h"
#include "Teacher.h"
using namespace std;
#define  FILENAME "studentFile.txt"

class Manager {
private:
	Teacher teacher1;
	string keyAdministrator;
	int m_stuNum;//记录文件中的人数个数
	Student** m_student;//学生数组的指针
	bool m_FileIsEmpty;//标志文件是否为空

public:
	Manager();
	~Manager();
	int get_stuNum();//统计文件内记录学生人数函数
	void initStudent();//初始化学生信息函数
	int isExist(string id);//按照学号判断学生是否存在函数
	void showMenu();//显示一级菜单函数
	void showMenuStudent();//显示二级学生登录菜单函数
	void loginStudent();//学生登录函数
	void showMenuTeacher();//显示二级教师登录菜单函数
	void loginTeacher();//教师登录函数
	void showStudent();//查看学生信息函数
	void addStudent();//添加学生信息函数
	void deleteStudent();//删除学生信息函数
	void alterStudent();//修改学生信息函数
	void findStudent();//查找学生信息函数
	void sortStudent();//排序学生信息函数
	void saveFile();//保存文件函数
	void cleanFile();//清空文件函数
	void showMenuAdministrator();//显示二级管理员登录菜单函数
	void loginAdministrator();//管理员登录函数
	void resetStudentKey();//管理员重置学生密码函数
	void resetTeacherKey();//管理员重置学生密码函数
	void exitSystem();//退出系统函数
};