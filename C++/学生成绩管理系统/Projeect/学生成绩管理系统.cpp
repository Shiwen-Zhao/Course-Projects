#include <iostream>
#include "Manager.h"
using namespace std;

int main(){
    Manager m;
	int choice = 0;
	while (true){
		m.showMenu();//展示菜单
		cout << "请输入您的选择：";
		cin >> choice;
		switch (choice){
		case 0: //退出系统
			m.exitSystem();
			break;
		case 1: //学生登录
			m.loginStudent();
			break;
		case 2: //教师登录
			m.loginTeacher();
			break;
		case 3://管理员登录
			m.loginAdministrator();
			break;
		default:
			cout << "输入有误！" << endl;
			system("pause");
			break;
		}
	}
	system("pause");
	return 0;
}