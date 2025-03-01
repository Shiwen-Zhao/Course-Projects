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
	int m_stuNum;//��¼�ļ��е���������
	Student** m_student;//ѧ�������ָ��
	bool m_FileIsEmpty;//��־�ļ��Ƿ�Ϊ��

public:
	Manager();
	~Manager();
	int get_stuNum();//ͳ���ļ��ڼ�¼ѧ����������
	void initStudent();//��ʼ��ѧ����Ϣ����
	int isExist(string id);//����ѧ���ж�ѧ���Ƿ���ں���
	void showMenu();//��ʾһ���˵�����
	void showMenuStudent();//��ʾ����ѧ����¼�˵�����
	void loginStudent();//ѧ����¼����
	void showMenuTeacher();//��ʾ������ʦ��¼�˵�����
	void loginTeacher();//��ʦ��¼����
	void showStudent();//�鿴ѧ����Ϣ����
	void addStudent();//���ѧ����Ϣ����
	void deleteStudent();//ɾ��ѧ����Ϣ����
	void alterStudent();//�޸�ѧ����Ϣ����
	void findStudent();//����ѧ����Ϣ����
	void sortStudent();//����ѧ����Ϣ����
	void saveFile();//�����ļ�����
	void cleanFile();//����ļ�����
	void showMenuAdministrator();//��ʾ��������Ա��¼�˵�����
	void loginAdministrator();//����Ա��¼����
	void resetStudentKey();//����Ա����ѧ�����뺯��
	void resetTeacherKey();//����Ա����ѧ�����뺯��
	void exitSystem();//�˳�ϵͳ����
};