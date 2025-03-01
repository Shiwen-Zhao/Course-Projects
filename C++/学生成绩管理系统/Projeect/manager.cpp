#include "Manager.h"

Manager::Manager() {
	teacher1 = { "��ʦ1", "��", 29, "123456", "����" };
	keyAdministrator = "123456";

	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//�ļ����������
	if (!ifs.is_open()){
		cout << "�ļ������ڣ�" << endl; //�������
		m_stuNum = 0;  //��ʼ������
		m_FileIsEmpty = true; //��ʼ���ļ�Ϊ�ձ�־
		m_student = NULL; //��ʼ������
		ifs.close(); //�ر��ļ�
		return;
	}

	//�ļ����ڣ���û�м�¼
	char ch;
	ifs >> ch;
	if (ifs.eof()){
		cout << "�ļ�Ϊ��!" << endl;
		m_stuNum = 0;
		m_FileIsEmpty = true;
		m_student = NULL;
		ifs.close();
		return;
	}

	int num = get_stuNum();
	m_stuNum = num;  //���³�Ա���� 
	m_student = new Student * [m_stuNum];//����ѧ������������
	initStudent();//��ʼ��ѧ��
}

Manager::~Manager() {
	if (m_student != NULL) {
		delete[] this->m_student;
	}
}

//ͳ���ļ��ڼ�¼ѧ����������
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
		num++;//��¼����
	}
	ifs.close();

	return num;
}

//��ʼ��ѧ����Ϣ����
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
		student = new Student(name, sex, age, id, college, major, score1, score2);//������ͬ����
		m_student[index] = student;//�����������
		index++;
	}
}

//����ѧ���ж�ѧ���Ƿ���ں���
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

//��ʾһ���˵�����
void Manager::showMenu() {
	system("cls");
	cout << "********************************************" << endl;
	cout << "*******  ��ӭʹ��ѧ���ɼ�����ϵͳ�� ********" << endl;
	cout << "*************  1.ѧ����¼  *****************" << endl;
	cout << "*************  2.��ʦ��¼  *****************" << endl;
	cout << "*************  3.����Ա��¼  ***************" << endl;
	cout << "*************  0.�˳�ϵͳ  *****************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//��ʾ����ѧ����¼�˵�����
void Manager::showMenuStudent() {
	cout << "****************  ѧ����¼  ****************" << endl;
	cout << "********************************************" << endl;
	cout << "*************  1.�鿴�ɼ�  *****************" << endl;
	cout << "*************  2.�޸�����  *****************" << endl;
	cout << "*************  0.������һ��  ***************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//ѧ����¼����
void Manager::loginStudent() {
	system("cls");
	cout << "****************  ѧ����¼  ****************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
	string id;
	cout << "������ѧ�ţ�";
	cin >> id;
	bool flag = false;  //���ҵ��ı�־
	for (int i = 0; i < m_stuNum; i++) {
		if (m_student[i]->m_id == id) {
			flag = true;
			string key;
			cout << "���������룺";
			cin >> key;
			if (m_student[i]->m_key == key) {
				system("cls");
				int select;
				while (true) {
					system("cls");
					cout << "��¼�ɹ�����ӭ" << m_student[i]->m_name << "��" << endl;
					showMenuStudent();
					cout << "����������ѡ��";
					cin >> select;
					if (select == 1) {
						m_student[i]->showInfo();
						system("pause");
						system("cls");
					}
					if (select == 2) {
						while (true) {
							string newKey1;
							cout << "�����������룺";
							cin >> newKey1;
							if (newKey1 == m_student[i]->m_key) {
								cout << "���������������ͬ���޸�����ʧ�ܣ�" << endl;
								system("pause");
								system("cls");
								break;
							}
							string newKey2;
							cout << "���ٴ�ȷ�����룺";
							cin >> newKey2;
							if (newKey1 == newKey2) {
								if (newKey1 != m_student[i]->m_key) {
									m_student[i]->m_key = newKey1;
									cout << "�޸�����ɹ���" << endl;
									system("pause");
									system("cls");
									break;
								}
							}
							else {
								cout << "�����������벻ͬ���޸�����ʧ�ܣ�" << endl;
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
				cout << "�������" << endl;
				system("pause");
			}
		}
	}
	if (flag == false) {
		cout << "�˺Ų����ڻ��˺���������" << endl;
		system("pause");
	}
}

//��ʾ������ʦ��¼�˵�����
void Manager::showMenuTeacher() {
	cout << "****************  ��ʦ��¼  ****************" << endl;
	cout << "********************************************" << endl;
	cout << "*************  1.�鿴ѧ����Ϣ  *************" << endl;
	cout << "*************  2.���ѧ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ��ѧ����Ϣ  *************" << endl;
	cout << "*************  4.�޸�ѧ����Ϣ  *************" << endl;
	cout << "*************  5.����ѧ����Ϣ  *************" << endl;
	cout << "*************  6.���ѧ����Ϣ  *************" << endl;
	cout << "*************  0.������һ��  ***************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//��ʦ��¼����
void Manager::loginTeacher() {
	system("cls");
	cout << "****************  ��ʦ��¼  ****************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
	string id;
	cout << "�����빤�ţ�";
	cin >> id;
	bool flag = false;  //���ҵ��ı�־
	if (teacher1.m_id == id) {
		flag = true;
		string key;
		cout << "���������룺";
		cin >> key;
		if (teacher1.m_key == key) {
			system("cls");
			int choice = 0;
			while (true) {
				system("cls");
				cout << "��¼�ɹ�����ӭ" << teacher1.m_name << "��" << endl;
				showMenuTeacher();
				cout << "����������ѡ��";
				cin >> choice;
				//������һ��
				if (choice == 0)
					break;
				switch (choice) {
					//�鿴ѧ����Ϣ
				case 1:
					showStudent();
					break;
					//���ѧ����Ϣ
				case 2:
					addStudent();
					break;
					//ɾ��ѧ����Ϣ
				case 3:
					deleteStudent();
					break;
					//�޸�ѧ����Ϣ
				case 4:
					alterStudent();
					break;
					//����ѧ����Ϣ
				case 5:
					findStudent();
					break;
					//���ѧ����Ϣ
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
			cout << "�������" << endl;
			system("pause");
		}

	}
	if (flag == false) {
		cout << "�˺Ų����ڻ��˺���������" << endl;
		system("pause");
	}
}

//�鿴ѧ����Ϣ����
void Manager::showStudent(){
	if (m_FileIsEmpty){
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		system("pause");
	}
	else{
		for (int i = 0; i < m_stuNum; i++){
			m_student[i]->showInfo();//���ö�̬���ýӿ�
		}
		cout << endl;
		cout << "�Ƿ�ѡ������鿴����--��1/��--�����������";
		int choice = 0;
		cin >> choice;
		if (choice == 1) {
			sortStudent();
		}
	}
}

//���ѧ����Ϣ����
void Manager::addStudent() {
	cout << "����������ѧ��������" ;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0) {
		int newSize = m_stuNum + addNum;//�����¿ռ��С
		Student** newSpace = new Student*;//�����¿ռ�
		//��ԭ�ռ������ݴ�ŵ��¿ռ���
		if (m_student != NULL) {
			for (int i = 0; i < m_stuNum; i++) {
				newSpace[i] = m_student[i];
			}
		}

		//����������
		for (int i = 0; i < addNum; i++) {
			string name;
			string sex;
			int age;
			string id;
			string college;
			string major;
			double score1;
			double score2;

			cout << "�������" << i + 1 << "��ѧ����������";
			cin >> name;
			cout << "�������" << i + 1 << "��ѧ�����Ա�";
			cin >> sex;
			cout << "�������" << i + 1 << "��ѧ�������䣺";
			cin >> age;
			cout << "������� " << i + 1 << " ��ѧ����ѧ�ţ�";
			cin >> id;
			cout << "������� " << i + 1 << " ��ѧ������ѧԺ��";
			cin >> college;
			cout << "������� " << i + 1 << " ��ѧ������רҵ��";
			cin >> major;
			cout << "������� " << i + 1 << " ��ѧ������1�ķ�����";
			cin >> score1;
			cout << "������� " << i + 1 << " ��ѧ������2�ķ�����";
			cin >> score2;

			Student* student = NULL;
			student = new Student(name, sex, age, id, college, major, score1, score2);
			newSpace[m_stuNum + i] = student;
		}


		delete[] m_student;//�ͷ�ԭ�пռ�
		m_student = newSpace;//�����¿ռ��ָ��
		m_stuNum = newSize;//�����µĸ���
		saveFile();//��������
		m_FileIsEmpty = false;//����ְ����Ϊ�ձ�־
		cout << "�ɹ����" << addNum << "��ͬѧ��" << endl;//��ʾ��Ϣ
	}
	else {
		cout << "��������" << endl;
	}
	system("pause");
	system("cls");
}

//ɾ��ѧ����Ϣ����
void Manager::deleteStudent() {
	if (m_FileIsEmpty){
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else {
		//��ѧ��ɾ��
		cout << "��������Ҫɾ����ѧ����ѧ�ţ�";
		string id;
		cin >> id;

		int index = isExist(id);

		//˵��index��λ��������Ҫɾ��
		if (index != -1) {
			for (int i = index; i < m_stuNum - 1; i++)
			{
				m_student[i] = m_student[i + 1];
			}
			m_stuNum--;

			saveFile(); //ɾ��������ͬ�����ļ���
			cout << "ɾ���ɹ���" << endl;
		}
		else
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ѧ��" << endl;
	}
	system("pause");
	system("cls");
}

//�޸�ѧ����Ϣ����
void Manager::alterStudent() {
	if (m_FileIsEmpty){
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else{
		cout << "�������޸�ѧ����ѧ�ţ�";
		string id;
		cin >> id;

		int ret = isExist(id);
		if (ret != -1){
			//���ҵ���ŵ�ѧ��
			cout << "�鵽" << id << "��ѧ����" << m_student[ret]->m_name << endl;
			delete m_student[ret];
			
			string newName = "";
			string newSex = "";
			int newAge = 0;
			string newId = "";
			string newCollege = "";
			string newMajor = "";
			double newScore1 = 0;
			double newScore2 = 0;

			cout << "�������޸ĺ��������";
			cin >> newName;
			cout << "�������޸ĺ���Ա�";
			cin >> newSex;
			cout << "�������޸ĺ�����䣺";
			cin >> newAge;
			cout << "�������޸ĺ��ѧ�ţ�";
			cin >> newId;
			cout << "�������޸ĺ��ѧԺ��";
			cin >> newCollege;
			cout << "�������޸ĺ��רҵ��";
			cin >> newMajor;
			cout << "�������޸ĺ�ķ���1�ķ�����";
			cin >> newScore1;
			cout << "�������޸ĺ�ķ���2�ķ�����";
			cin >> newScore2;

			Student* student = NULL;
			student = new Student(newName, newSex, newAge, newId, newCollege, newMajor, newScore1, newScore2);
			m_student[ret] = student;

			cout << "�޸ĳɹ���" << endl;

			saveFile();//���浽�ļ���
		}
		else{
			cout << "�޸�ʧ�ܣ����޴���!" << endl;
		}
	}
	system("pause");
	system("cls");
}

//����ѧ����Ϣ����
void Manager::findStudent() {
	if (m_FileIsEmpty){
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else{
		cout << "���ҵķ�ʽ��" << endl;
		cout << "1����ѧ�Ų���" << endl;
		cout << "2������������" << endl;

		int select = 0;
		cout << "��ѡ��";
		cin >> select;

		//��ѧ�Ų���
		if (select == 1){
			string id;
			cout << "��������ҵ�ѧ����ѧ�ţ�";
			cin >> id;

			int ret = isExist(id);
			if (ret != -1){
				cout << "���ҳɹ�����ѧ����Ϣ���£�" << endl;
				m_student[ret]->showInfo();
			}
			else{
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}

		//����������
		else if (select == 2) {
			string name;
			cout << "��������ҵ�������";
			cin >> name;

			bool flag = false;  //���ҵ��ı�־
			for (int i = 0; i < m_stuNum; i++){
				if (m_student[i]->m_name == name){
					cout << "���ҳɹ�!" << endl;

					flag = true;

					m_student[i]->showInfo();
				}
			}
			if (flag == false){
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else{
			cout << "����ѡ������" << endl;
		}
	}
	system("pause");
	system("cls");
}

//����ѧ����Ϣ����
void Manager::sortStudent() {
	if (m_FileIsEmpty){
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else{
		cout << "��ѡ������ʽ�� " << endl;
		cout << "1����ѧ����������" << endl;
		cout << "2����ѧ�Ž�������" << endl;
		cout << "3��������1��������" << endl;
		cout << "4��������1��������" << endl;
		cout << "5��������2��������" << endl;
		cout << "6��������2��������" << endl;
		cout << "��ѡ��";
		int select = 0;
		cin >> select;

		for (int i = 0; i < m_stuNum; i++){
			int MinOrMax = i;
			for (int j = i + 1; j < m_stuNum; j++){
				
				//ѧ�Ž���
				if (select == 2) {
					if (m_student[MinOrMax]->m_id < m_student[j]->m_id){
						MinOrMax = j;
					}
				}
				//����1����
				if (select == 3) {
					if (m_student[MinOrMax]->m_score1 > m_student[j]->m_score1) {
						MinOrMax = j;
					}
				}
				//����1����
				if (select == 4) {
					if (m_student[MinOrMax]->m_score1 < m_student[j]->m_score1) {
						MinOrMax = j;
					}
				}
				//����2����
				if (select == 5) {
					if (m_student[MinOrMax]->m_score2 > m_student[j]->m_score2) {
						MinOrMax = j;
					}
				}
				//����2����
				if (select == 6) {
					if (m_student[MinOrMax]->m_score2 < m_student[j]->m_score2) {
						MinOrMax = j;
					}
				}
				//ѧ������
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
		cout << "����ɹ�,�������Ϊ��" << endl;
		showStudent();
	}
}

//�����ļ�����
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

//����ļ�����
void Manager::cleanFile() {
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int select = 0;
	cin >> select;

	if (select == 1){
		//��ģʽ ios::trunc �������ɾ���ļ������´���
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
		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}

//��ʾ��������Ա��¼�˵�����
void Manager::showMenuAdministrator() {
	system("cls");
	cout << "***************  ����Ա��¼  ***************" << endl;
	cout << "********************************************" << endl;
	cout << "*************  1.����ѧ������  *************" << endl;
	cout << "*************  2.���ý�ʦ����  *************" << endl;
	cout << "*************  0.������һ��  ***************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//����Ա��¼����
void Manager::loginAdministrator() {
	system("cls");
	cout << "***************  ����Ա��¼  ***************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
	string key;
	cout << "���������Ա�������룺";
	cin >> key;
	if (key == keyAdministrator) {
		int choice = 0;
		while (true) {
			showMenuAdministrator();
			cout << "����������ѡ��";
			cin >> choice;
			//������һ��
			if (choice == 0)
				break;
			switch (choice) {
				//����ѧ������
			case 1:
				resetStudentKey();
				break;
				//���ý�ʦ����
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
		cout << "�������" << endl;
		system("pause");
	}
}

//����Ա����ѧ�����뺯��
void Manager::resetStudentKey() {
	if (m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else {
		cout << "���������������ѧ����ѧ�ţ�" << endl;
		string id;
		cin >> id;
		int ret = isExist(id);
		if (ret != -1) {
			//���ҵ���ŵ�ѧ��
			cout << "�鵽" << id << "��ѧ����" << m_student[ret]->m_name << endl;
			m_student[ret]->m_key = "123456";
			cout << "��������ɹ��������룺" << m_student[ret]->m_key << endl;
		}
		else {
			cout << "����ʧ�ܣ����޴���!" << endl;
		}
	}
	system("pause");
	system("cls");
}

//����Ա����ѧ�����뺯��
void Manager::resetTeacherKey() {
	if (m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else {
		string id;
		cout << "�������ʦ���ţ�";
		cin >> id;
		if (teacher1.m_id == id) {
			teacher1.m_key = "123456";
			cout << "��������ɹ���������" << teacher1.m_key << endl;
			system("pause");
		}
		else {
			cout << "����ʧ�ܣ����޴���!" << endl;
			system("pause");
		}
	}
	system("cls");
}

//�˳�ϵͳ����
void Manager::exitSystem() {
	cout << "��ӭ�´�ʹ��!" << endl;
	system("pause");
	exit(0);
}