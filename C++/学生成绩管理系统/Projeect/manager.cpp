#include "Manager.h"

Manager::Manager() {
	teacher1 = { "教师1", "男", 29, "123456", "教授" };
	keyAdministrator = "123456";

	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//文件不存在情况
	if (!ifs.is_open()){
		cout << "文件不存在！" << endl; //测试输出
		m_stuNum = 0;  //初始化人数
		m_FileIsEmpty = true; //初始化文件为空标志
		m_student = NULL; //初始化数组
		ifs.close(); //关闭文件
		return;
	}

	//文件存在，但没有记录
	char ch;
	ifs >> ch;
	if (ifs.eof()){
		cout << "文件为空!" << endl;
		m_stuNum = 0;
		m_FileIsEmpty = true;
		m_student = NULL;
		ifs.close();
		return;
	}

	int num = get_stuNum();
	m_stuNum = num;  //更新成员属性 
	m_student = new Student * [m_stuNum];//根据学生数创建数组
	initStudent();//初始化学生
}

Manager::~Manager() {
	if (m_student != NULL) {
		delete[] this->m_student;
	}
}

//统计文件内记录学生人数函数
int Manager::get_stuNum(){
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	string name;
	string sex;
	int age;
	string id;
	string college;
	string major;
	double score1;
	double score2;

	int num = 0;

	while (ifs >> name && ifs >> sex && ifs >> age && ifs >> id && ifs >> college && ifs >> major && ifs >> score1 && ifs >> score2){
		num++;//记录人数
	}
	ifs.close();

	return num;
}

//初始化学生信息函数
void Manager::initStudent(){
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	string name;
	string sex;
	int age;
	string id;
	string college;
	string major;
	double score1;
	double score2;

	int index = 0;
	while (ifs >> name && ifs >> sex && ifs >> age && ifs >> id && ifs >> college && ifs >> major && ifs >> score1 && ifs >> score2){
		Student* student = NULL;
		student = new Student(name, sex, age, id, college, major, score1, score2);//创建不同对象
		m_student[index] = student;//存放在数组中
		index++;
	}
}

//按照学号判断学生是否存在函数
int Manager::isExist(string id) {
	int index = -1;
	for (int i = 0; i < m_stuNum; i++) {
		if (m_student[i]->m_id == id) {
			index = i;
			break;
		}
	}
	return index;
}

//显示一级菜单函数
void Manager::showMenu() {
	system("cls");
	cout << "********************************************" << endl;
	cout << "*******  欢迎使用学生成绩管理系统！ ********" << endl;
	cout << "*************  1.学生登录  *****************" << endl;
	cout << "*************  2.教师登录  *****************" << endl;
	cout << "*************  3.管理员登录  ***************" << endl;
	cout << "*************  0.退出系统  *****************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//显示二级学生登录菜单函数
void Manager::showMenuStudent() {
	cout << "****************  学生登录  ****************" << endl;
	cout << "********************************************" << endl;
	cout << "*************  1.查看成绩  *****************" << endl;
	cout << "*************  2.修改密码  *****************" << endl;
	cout << "*************  0.返回上一级  ***************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//学生登录函数
void Manager::loginStudent() {
	system("cls");
	cout << "****************  学生登录  ****************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
	string id;
	cout << "请输入学号：";
	cin >> id;
	bool flag = false;  //查找到的标志
	for (int i = 0; i < m_stuNum; i++) {
		if (m_student[i]->m_id == id) {
			flag = true;
			string key;
			cout << "请输入密码：";
			cin >> key;
			if (m_student[i]->m_key == key) {
				system("cls");
				int select;
				while (true) {
					system("cls");
					cout << "登录成功，欢迎" << m_student[i]->m_name << "！" << endl;
					showMenuStudent();
					cout << "请输入您的选择：";
					cin >> select;
					if (select == 1) {
						m_student[i]->showInfo();
						system("pause");
						system("cls");
					}
					if (select == 2) {
						while (true) {
							string newKey1;
							cout << "请输入新密码：";
							cin >> newKey1;
							if (newKey1 == m_student[i]->m_key) {
								cout << "新密码与旧密码相同，修改密码失败！" << endl;
								system("pause");
								system("cls");
								break;
							}
							string newKey2;
							cout << "请再次确认密码：";
							cin >> newKey2;
							if (newKey1 == newKey2) {
								if (newKey1 != m_student[i]->m_key) {
									m_student[i]->m_key = newKey1;
									cout << "修改密码成功！" << endl;
									system("pause");
									system("cls");
									break;
								}
							}
							else {
								cout << "两次密码输入不同，修改密码失败！" << endl;
								system("pause");
								system("cls");
								break;
							}
						}
					}
					if (select == 0) {
						break;
					}
				}
			}
			else {
				cout << "密码错误！" << endl;
				system("pause");
			}
		}
	}
	if (flag == false) {
		cout << "账号不存在或账号输入有误！" << endl;
		system("pause");
	}
}

//显示二级教师登录菜单函数
void Manager::showMenuTeacher() {
	cout << "****************  教师登录  ****************" << endl;
	cout << "********************************************" << endl;
	cout << "*************  1.查看学生信息  *************" << endl;
	cout << "*************  2.添加学生信息  *************" << endl;
	cout << "*************  3.删除学生信息  *************" << endl;
	cout << "*************  4.修改学生信息  *************" << endl;
	cout << "*************  5.查找学生信息  *************" << endl;
	cout << "*************  6.清空学生信息  *************" << endl;
	cout << "*************  0.返回上一级  ***************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//教师登录函数
void Manager::loginTeacher() {
	system("cls");
	cout << "****************  教师登录  ****************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
	string id;
	cout << "请输入工号：";
	cin >> id;
	bool flag = false;  //查找到的标志
	if (teacher1.m_id == id) {
		flag = true;
		string key;
		cout << "请输入密码：";
		cin >> key;
		if (teacher1.m_key == key) {
			system("cls");
			int choice = 0;
			while (true) {
				system("cls");
				cout << "登录成功，欢迎" << teacher1.m_name << "！" << endl;
				showMenuTeacher();
				cout << "请输入您的选择：";
				cin >> choice;
				//返回上一级
				if (choice == 0)
					break;
				switch (choice) {
					//查看学生信息
				case 1:
					showStudent();
					break;
					//添加学生信息
				case 2:
					addStudent();
					break;
					//删除学生信息
				case 3:
					deleteStudent();
					break;
					//修改学生信息
				case 4:
					alterStudent();
					break;
					//查找学生信息
				case 5:
					findStudent();
					break;
					//清空学生信息
				case 6:
					cleanFile();
					break;
				default:
					system("cls");
					break;
				}
			}
		}
		else {
			cout << "密码错误！" << endl;
			system("pause");
		}

	}
	if (flag == false) {
		cout << "账号不存在或账号输入有误！" << endl;
		system("pause");
	}
}

//查看学生信息函数
void Manager::showStudent(){
	if (m_FileIsEmpty){
		cout << "文件不存在或记录为空！" << endl;
		system("pause");
	}
	else{
		for (int i = 0; i < m_stuNum; i++){
			m_student[i]->showInfo();//利用多态调用接口
		}
		cout << endl;
		cout << "是否选择排序查看（是--按1/否--按任意键）：";
		int choice = 0;
		cin >> choice;
		if (choice == 1) {
			sortStudent();
		}
	}
}

//添加学生信息函数
void Manager::addStudent() {
	cout << "请输入增加学生数量：" ;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0) {
		int newSize = m_stuNum + addNum;//计算新空间大小
		Student** newSpace = new Student*;//开辟新空间
		//将原空间下内容存放到新空间下
		if (m_student != NULL) {
			for (int i = 0; i < m_stuNum; i++) {
				newSpace[i] = m_student[i];
			}
		}

		//输入新数据
		for (int i = 0; i < addNum; i++) {
			string name;
			string sex;
			int age;
			string id;
			string college;
			string major;
			double score1;
			double score2;

			cout << "请输入第" << i + 1 << "个学生的姓名：";
			cin >> name;
			cout << "请输入第" << i + 1 << "个学生的性别：";
			cin >> sex;
			cout << "请输入第" << i + 1 << "个学生的年龄：";
			cin >> age;
			cout << "请输入第 " << i + 1 << " 个学生的学号：";
			cin >> id;
			cout << "请输入第 " << i + 1 << " 个学生所属学院：";
			cin >> college;
			cout << "请输入第 " << i + 1 << " 个学生所在专业：";
			cin >> major;
			cout << "请输入第 " << i + 1 << " 个学生分数1的分数：";
			cin >> score1;
			cout << "请输入第 " << i + 1 << " 个学生分数2的分数：";
			cin >> score2;

			Student* student = NULL;
			student = new Student(name, sex, age, id, college, major, score1, score2);
			newSpace[m_stuNum + i] = student;
		}


		delete[] m_student;//释放原有空间
		m_student = newSpace;//更改新空间的指向
		m_stuNum = newSize;//更新新的个数
		saveFile();//保存数据
		m_FileIsEmpty = false;//更新职工不为空标志
		cout << "成功添加" << addNum << "名同学！" << endl;//提示信息
	}
	else {
		cout << "输入有误" << endl;
	}
	system("pause");
	system("cls");
}

//删除学生信息函数
void Manager::deleteStudent() {
	if (m_FileIsEmpty){
		cout << "文件不存在或记录为空！" << endl;
	}
	else {
		//按学号删除
		cout << "请输入想要删除的学生的学号：";
		string id;
		cin >> id;

		int index = isExist(id);

		//说明index上位置数据需要删除
		if (index != -1) {
			for (int i = index; i < m_stuNum - 1; i++)
			{
				m_student[i] = m_student[i + 1];
			}
			m_stuNum--;

			saveFile(); //删除后数据同步到文件中
			cout << "删除成功！" << endl;
		}
		else
			cout << "删除失败，未找到该学生" << endl;
	}
	system("pause");
	system("cls");
}

//修改学生信息函数
void Manager::alterStudent() {
	if (m_FileIsEmpty){
		cout << "文件不存在或记录为空！" << endl;
	}
	else{
		cout << "请输入修改学生的学号：";
		string id;
		cin >> id;

		int ret = isExist(id);
		if (ret != -1){
			//查找到编号的学生
			cout << "查到" << id << "，学生：" << m_student[ret]->m_name << endl;
			delete m_student[ret];
			
			string newName = "";
			string newSex = "";
			int newAge = 0;
			string newId = "";
			string newCollege = "";
			string newMajor = "";
			double newScore1 = 0;
			double newScore2 = 0;

			cout << "请输入修改后的姓名：";
			cin >> newName;
			cout << "请输入修改后的性别：";
			cin >> newSex;
			cout << "请输入修改后的年龄：";
			cin >> newAge;
			cout << "请输入修改后的学号：";
			cin >> newId;
			cout << "请输入修改后的学院：";
			cin >> newCollege;
			cout << "请输入修改后的专业：";
			cin >> newMajor;
			cout << "请输入修改后的分数1的分数：";
			cin >> newScore1;
			cout << "请输入修改后的分数2的分数：";
			cin >> newScore2;

			Student* student = NULL;
			student = new Student(newName, newSex, newAge, newId, newCollege, newMajor, newScore1, newScore2);
			m_student[ret] = student;

			cout << "修改成功！" << endl;

			saveFile();//保存到文件中
		}
		else{
			cout << "修改失败，查无此人!" << endl;
		}
	}
	system("pause");
	system("cls");
}

//查找学生信息函数
void Manager::findStudent() {
	if (m_FileIsEmpty){
		cout << "文件不存在或记录为空！" << endl;
	}
	else{
		cout << "查找的方式：" << endl;
		cout << "1、按学号查找" << endl;
		cout << "2、按姓名查找" << endl;

		int select = 0;
		cout << "请选择：";
		cin >> select;

		//按学号查找
		if (select == 1){
			string id;
			cout << "请输入查找的学生的学号：";
			cin >> id;

			int ret = isExist(id);
			if (ret != -1){
				cout << "查找成功！该学生信息如下：" << endl;
				m_student[ret]->showInfo();
			}
			else{
				cout << "查找失败，查无此人" << endl;
			}
		}

		//按姓名查找
		else if (select == 2) {
			string name;
			cout << "请输入查找的姓名：";
			cin >> name;

			bool flag = false;  //查找到的标志
			for (int i = 0; i < m_stuNum; i++){
				if (m_student[i]->m_name == name){
					cout << "查找成功!" << endl;

					flag = true;

					m_student[i]->showInfo();
				}
			}
			if (flag == false){
				cout << "查找失败，查无此人" << endl;
			}
		}
		else{
			cout << "输入选项有误" << endl;
		}
	}
	system("pause");
	system("cls");
}

//排序学生信息函数
void Manager::sortStudent() {
	if (m_FileIsEmpty){
		cout << "文件不存在或记录为空！" << endl;
		system("pause");
		system("cls");
	}
	else{
		cout << "请选择排序方式： " << endl;
		cout << "1、按学号升序排序" << endl;
		cout << "2、按学号降序排序" << endl;
		cout << "3、按分数1升序排序" << endl;
		cout << "4、按分数1降序排序" << endl;
		cout << "5、按分数2升序排序" << endl;
		cout << "6、按分数2降序排序" << endl;
		cout << "请选择：";
		int select = 0;
		cin >> select;

		for (int i = 0; i < m_stuNum; i++){
			int MinOrMax = i;
			for (int j = i + 1; j < m_stuNum; j++){
				
				//学号降序
				if (select == 2) {
					if (m_student[MinOrMax]->m_id < m_student[j]->m_id){
						MinOrMax = j;
					}
				}
				//分数1升序
				if (select == 3) {
					if (m_student[MinOrMax]->m_score1 > m_student[j]->m_score1) {
						MinOrMax = j;
					}
				}
				//分数1降序
				if (select == 4) {
					if (m_student[MinOrMax]->m_score1 < m_student[j]->m_score1) {
						MinOrMax = j;
					}
				}
				//分数2升序
				if (select == 5) {
					if (m_student[MinOrMax]->m_score2 > m_student[j]->m_score2) {
						MinOrMax = j;
					}
				}
				//分数2降序
				if (select == 6) {
					if (m_student[MinOrMax]->m_score2 < m_student[j]->m_score2) {
						MinOrMax = j;
					}
				}
				//学号升序
				else {
					if (m_student[MinOrMax]->m_id > m_student[j]->m_id) {
						MinOrMax = j;
					}
				}
			}

			if (i != MinOrMax){
				Student* temp = m_student[i];
				m_student[i] = m_student[MinOrMax];
				m_student[MinOrMax] = temp;
			}

		}
		saveFile();
		cout << "排序成功,排序后结果为：" << endl;
		showStudent();
	}
}

//保存文件函数
void Manager::saveFile() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->m_stuNum; i++){
		ofs << m_student[i]->m_name << "\t"
			<< m_student[i]->m_sex << "\t"
			<< m_student[i]->m_age << "\t"
			<< m_student[i]->m_id << "\t"
			<< m_student[i]->m_college << "\t"
			<< m_student[i]->m_major << "\t"
			<< m_student[i]->m_score1 << "\t"
			<< m_student[i]->m_score2 << endl;
	}
	ofs.close();
}

//清空文件函数
void Manager::cleanFile() {
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1){
		//打开模式 ios::trunc 如果存在删除文件并重新创建
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		if (m_student != NULL){
			for (int i = 0; i < this->m_stuNum; i++){
				if (m_student[i] != NULL){
					delete this->m_student[i];
				}
			}
			m_stuNum = 0;
			delete[] m_student;
			m_student = NULL;
			m_FileIsEmpty = true;
		}
		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}

//显示二级管理员登录菜单函数
void Manager::showMenuAdministrator() {
	system("cls");
	cout << "***************  管理员登录  ***************" << endl;
	cout << "********************************************" << endl;
	cout << "*************  1.重置学生密码  *************" << endl;
	cout << "*************  2.重置教师密码  *************" << endl;
	cout << "*************  0.返回上一级  ***************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//管理员登录函数
void Manager::loginAdministrator() {
	system("cls");
	cout << "***************  管理员登录  ***************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
	string key;
	cout << "请输入管理员操作密码：";
	cin >> key;
	if (key == keyAdministrator) {
		int choice = 0;
		while (true) {
			showMenuAdministrator();
			cout << "请输入您的选择：";
			cin >> choice;
			//返回上一级
			if (choice == 0)
				break;
			switch (choice) {
				//重置学生密码
			case 1:
				resetStudentKey();
				break;
				//重置教师密码
			case 2:
				resetTeacherKey();
				break;
			default:
				system("cls");
				break;
			}
		}
	}
	else {
		cout << "密码错误！" << endl;
		system("pause");
	}
}

//管理员重置学生密码函数
void Manager::resetStudentKey() {
	if (m_FileIsEmpty) {
		cout << "文件不存在或记录为空！" << endl;
	}
	else {
		cout << "请输入重置密码的学生的学号：" << endl;
		string id;
		cin >> id;
		int ret = isExist(id);
		if (ret != -1) {
			//查找到编号的学生
			cout << "查到" << id << "，学生：" << m_student[ret]->m_name << endl;
			m_student[ret]->m_key = "123456";
			cout << "重置密码成功！新密码：" << m_student[ret]->m_key << endl;
		}
		else {
			cout << "重置失败，查无此人!" << endl;
		}
	}
	system("pause");
	system("cls");
}

//管理员重置学生密码函数
void Manager::resetTeacherKey() {
	if (m_FileIsEmpty) {
		cout << "文件不存在或记录为空！" << endl;
	}
	else {
		string id;
		cout << "请输入教师工号：";
		cin >> id;
		if (teacher1.m_id == id) {
			teacher1.m_key = "123456";
			cout << "重置密码成功！新密码" << teacher1.m_key << endl;
			system("pause");
		}
		else {
			cout << "重置失败，查无此人!" << endl;
			system("pause");
		}
	}
	system("cls");
}

//退出系统函数
void Manager::exitSystem() {
	cout << "欢迎下次使用!" << endl;
	system("pause");
	exit(0);
}