#include <iostream>
#include <string>//�õ�string��������
using namespace std;
#define MAX 100//�곣�������ڶ����˵�����������ɸ���
//�������ڽṹ��
struct Date {
	int m_Year;//��
	int m_Month;//��
	int m_Day;//��
};
//������֧��¼�ṹ��
struct Record {
	Date m_Time;//����
	string m_Remark;//��ע
	string m_Variety;//�����֧��
	double m_InMoney;//������
	double m_OutMoney;//֧�����
	double m_Balance;//���
};
//����˻��ṹ��
struct Account {
	string m_Name;//�˻�����
	string m_Currency;//����
	double m_Balance;//�˻����
	struct Record AccountBill[MAX];//��֧��¼����
	int m_Size;//�˻���¼����
};
void initializeAccount(Account*);//��ʼ���˻�����
void showMenu();//��������ʾ����
void sortRecord(Account*);//��¼��ʱ��������
void calculateBalance(Account*);//�����㺯��
void addRecord(Account*);//��¼��֧����
void showRecord(Account*);//�鿴��ϸ����
void amendRecord(Account*);//�޸ļ�¼����
void deleteRecord(Account*);//ɾ����¼����
void countRecord(Account*);//��ѯͳ�Ƽ�¼����
void cleanRecord(Account*);//��ռ�¼����

int main() {
	Account A1;//�����˻�
	initializeAccount(&A1);//���ó�ʼ���˻�����
	A1.m_Size = 0;//��ʼ���˻��˵�����
	int select = 0;//�����û��������
	while (true) {//��whileѭ����������Ƿ�Ϸ�
		showMenu();//������������ʾ����
		sortRecord(&A1);//���ü�¼��ʱ��������
		calculateBalance(&A1);//���������㺯��
		cout << "�˻����ƣ�" << A1.m_Name << "\t";//��ʾ�˻�����
		//��ʾ�˻����
		if (A1.m_Size == 0)cout << "��ǰ�˻���" << A1.m_Balance << endl;
		else cout << "�˻���" << A1.AccountBill[A1.m_Size - 1].m_Balance << endl;
		cout << "#��ѡ������ţ�1/2/3/4/5/6/0����";
		cin >> select;//�û����빦�����
		switch (select) {
		case 1://1.��¼��֧
			addRecord(&A1);//���ü�¼��֧����
			break;
		case 2://2.�鿴��ϸ
			showRecord(&A1);//���ò鿴��ϸ����
			system("pause");//�밴���������
			system("cls");//��������
			break;
		case 3://3.�޸ļ�¼
			cout << "#�ѽ��롰�޸ļ�¼�����ܣ�" << endl;
			showRecord(&A1);//���ò鿴��ϸ����
			amendRecord(&A1);//�����޸ļ�¼����
			break;
		case 4://4.ɾ����¼
			cout << "#�ѽ��롰ɾ����¼�����ܣ�" << endl;
			showRecord(&A1);//���ò鿴��ϸ����
			deleteRecord(&A1);//����ɾ����¼����
			break;
		case 5://5.��¼ͳ��
			countRecord(&A1);//���ü�¼ͳ�ƺ���
			break;
		case 6://6.��ռ�¼
			cleanRecord(&A1);//������ռ�¼����
			break;
		case 0://0.�˳�ϵͳ
			cout << "#��ӭ�´�ʹ�ã�" << endl;
			system("pause");
			return 0;
			break;
		default:
			system("cls");//��������
			cout << "#����������" << endl;
			break;
		}
	}
	system("pause");
	return 0;
}

//��������ʾ
void showMenu() {
	cout << "************************" << endl;
	cout << "*                      *" << endl;
	cout << "*   ������֧����ϵͳ   *" << endl;
	cout << "*                      *" << endl;
	cout << "************************" << endl;
	cout << "****** 1.��¼��֧ ******" << endl;
	cout << "****** 2.�鿴��ϸ ******" << endl;
	cout << "****** 3.�޸ļ�¼ ******" << endl;
	cout << "****** 4.ɾ����¼ ******" << endl;
	cout << "****** 5.��ѯͳ�� ******" << endl;
	cout << "****** 6.��ռ�¼ ******" << endl;
	cout << "****** 0.�˳�ϵͳ ******" << endl;
	cout << "************************" << endl<< endl;
}

//��ʼ���˻�
void initializeAccount(Account* A) {
	string name;//�����ֲ������˻�����
	double balance;//�����ֲ��������
	int Currency = 0;//�����ֲ��������ִ���
	cout << "��ӭʹ�ø�����֧����ϵͳ��" << endl;
	cout << "���ȳ�ʼ���˻���" << endl;
	cout << "#�������˻����ƣ�";
	cin >> name;
	A->m_Name = name;//���û�����ľֲ�������ֵ��ֵ��������ֵ
	cout << "#�������˻���";
	cin >> balance;
	A->m_Balance = balance;//���û�����ľֲ������˻���ֵ���������˻����
	cout << "!��ʾ��" << endl;
	cout << " �˱�Ĭ�ϼ�¼�����������CNY��" << endl;
	cout << " �������������1��������������0��" << endl;
	cout << "#�Ƿ���ģ�1/0)��";
	while (true) {//��whileѭ����������Ƿ�Ϸ�
		cin >> Currency;
		if (Currency == 0) {
			A->m_Currency = "CNY";//���û�����ľֲ�������ֵ��ֵ��������ֵ
			break;
		}
		else if (Currency == 1) {//�޸��˻�����
			int selectCurrency = 0;
			cout << "#ѡ�����" << endl;
			cout << " �����CNY - 0" << endl;
			cout << " ��ԪUSD ----1" << endl;
			cout << " ŷԪEUR --- 2" << endl;
			cout << " ��ԪJPY ----3" << endl;
			cout << " Ӣ��GPB ----4" << endl;
			while (true) {//��whileѭ����������Ƿ�Ϸ�
				cout << "��ѡ��0/1/2/3/4����";
				cin >> selectCurrency;
				if (selectCurrency == 0) {
					A->m_Currency = "CNY";
					break;
				}
				if (selectCurrency == 1) {
					A->m_Currency = "USD";
					break;
				}
				if (selectCurrency == 2) {
					A->m_Currency = "EUR";
					break;
				}
				if (selectCurrency == 3) {
					A->m_Currency = "JPY";
					break;
				}
				if (selectCurrency == 4) {
					A->m_Currency = "GPB";
					break;
				}
				cout << "���벻�Ϸ���";
			}
			break;
		}
		cout << "���벻�Ϸ����Ƿ���ģ�1/0)��";
	}
	cout << "#��ʼ���˻��ɹ���" << endl;
	cout << "��" << A->m_Name << "��" << "�˻���ǰ���Ϊ��" 
		<< A->m_Currency <<" "<< A->m_Balance << endl;
	system("pause");//�밴���������
	system("cls");//��������
}

//��¼��֧
void addRecord(Account* A) {
	cout << "#�ѽ��롰��¼��֧�����ܣ�" << endl;
	if (A->m_Size == MAX) {//����˻���¼�Ƿ��Ѵﵽ�������
		cout << "���˻���¼�Ѿ��ﵽ����������޷�������ӣ�" << endl;
		system("pause");
		system("cls");
	}
	else {
		//��������
		Date time;//����Date�ṹ�����;ֲ�����
		cout << "#����������" << endl;
		while (true) {//��whileѭ����������Ƿ�Ϸ�
			cout << " �꣺";
			cin >> time.m_Year;
			//������������Ƿ�Ϸ�
			if (0 < time.m_Year && time.m_Year < 9999) {
				A->AccountBill[A->m_Size].m_Time.m_Year = time.m_Year;//���û�����ľֲ�������ֵ��ֵ��������ֵ
				break;
			}
			cout << " ���벻�Ϸ���";
		}
		while (true) {//��whileѭ����������Ƿ�Ϸ�
			cout << " �£�";
			cin >> time.m_Month;
			//������������Ƿ�Ϸ�
			if (0 < time.m_Month && time.m_Month < 13) {
				A->AccountBill[A->m_Size].m_Time.m_Month = time.m_Month;//���û�����ľֲ�������ֵ��ֵ��������ֵ
				break;
			}
			cout << " ���벻�Ϸ���";
		}
		while (true) {//��whileѭ����������Ƿ�Ϸ�
			cout << " �գ�";
			cin >> time.m_Day;
			//������������Ƿ�Ϸ�
			if (0 < time.m_Day && time.m_Day < 32) {
				A->AccountBill[A->m_Size].m_Time.m_Day = time.m_Day;//���û�����ľֲ�������ֵ��ֵ��������ֵ
				break;
			}
			cout << " ���벻�Ϸ���";
		}
		//����ժҪ
		string remark;
		cout << "#������ժҪ��";
		cin >> remark;
		A->AccountBill[A->m_Size].m_Remark = remark;//���û�����ľֲ�������ֵ��ֵ��������ֵ
		//���������֧����־
		string variety;
		cout << "#ѡ���¼����(���� +/֧�� -)" << endl;
		while (true) {//��whileѭ����������Ƿ�Ϸ�

			cout << " �����루+/-����";
			cin >> variety;
			if (variety == "+" || variety == "-") {
				A->AccountBill[A->m_Size].m_Variety = variety;//���û�����ľֲ�������ֵ��ֵ��������ֵ
				break;
			}
			cout << " ���벻�Ϸ���";
		}
		//������
		double money = 0;
		cout << "#�������";
		cin >> money;
		if (A->AccountBill[A->m_Size].m_Variety == "+") {
			A->AccountBill[A->m_Size].m_InMoney = money;//���û�����ľֲ�������ֵ��ֵ��������ֵ
			A->AccountBill[A->m_Size].m_OutMoney = 0;//����ģʽ��֧��Ϊ0
		}
		else {
			A->AccountBill[A->m_Size].m_InMoney = 0;//֧��ģʽ������Ϊ0
			A->AccountBill[A->m_Size].m_OutMoney = money;//���û�����ľֲ�������ֵ��ֵ��������ֵ
		}
		//�����˵�
		A->m_Size++;
		cout << "#����˵��ɹ���" << endl;
		system("pause");//�밴���������
		system("cls");//��������
	}
}

//�˵���ʱ������
void sortRecord(Account* A) {
	for (int i = 0; i < A->m_Size - 1; i++) {
		for (int j = 0; j < A->m_Size - i - 1; j++) {
			if (A->AccountBill[j].m_Time.m_Year > A->AccountBill[j + 1].m_Time.m_Year) {
				Record temp = A->AccountBill[j];
				A->AccountBill[j] = A->AccountBill[j + 1];
				A->AccountBill[j + 1] = temp;
			}
		}
	}
	for (int k = 0; k < A->m_Size - 1; k++) {
		if (A->AccountBill[k].m_Time.m_Year == A->AccountBill[k + 1].m_Time.m_Year) {
			if (A->AccountBill[k].m_Time.m_Month > A->AccountBill[k + 1].m_Time.m_Month) {
				Record temp = A->AccountBill[k];
				A->AccountBill[k] = A->AccountBill[k + 1];
				A->AccountBill[k + 1] = temp;
			}
		}
	}
	for (int m = 0; m < A->m_Size - 1; m++) {
		if (A->AccountBill[m].m_Time.m_Year == A->AccountBill[m + 1].m_Time.m_Year) {
			if (A->AccountBill[m].m_Time.m_Month == A->AccountBill[m + 1].m_Time.m_Month) {
				if (A->AccountBill[m].m_Time.m_Day > A->AccountBill[m + 1].m_Time.m_Day) {
					Record temp = A->AccountBill[m];
					A->AccountBill[m] = A->AccountBill[m + 1];
					A->AccountBill[m + 1] = temp;
				}
			}
		}
	}
}

//������
void calculateBalance(Account* A) {
	double C = 0;
	if (A->AccountBill[0].m_Variety == "+") {
		C = A->m_Balance + A->AccountBill[0].m_InMoney;
		A->AccountBill[0].m_Balance = C;
	}
	else {
		C = A->m_Balance - A->AccountBill[0].m_OutMoney;
		A->AccountBill[0].m_Balance = C;
	}
	for (int i = 1; i < A->m_Size; i++) {
		if (A->AccountBill[i].m_Variety == "+") {
			C += A->AccountBill[i].m_InMoney;
			A->AccountBill[i].m_Balance = C;
		}
		else {
			C -= A->AccountBill[i].m_OutMoney;
			A->AccountBill[i].m_Balance = C;
		}
	}
}

//�鿴��ϸ
void showRecord(Account* A) {
	if (A->m_Size == 0) {//��ʾ��¼Ϊ0
		cout << "#��ǰ��¼Ϊ�գ�" << endl;
	}
	else {
		for (int i = 0; i < A->m_Size; i++) {
			cout << i+1 << "\t";
			cout << A->AccountBill[i].m_Time.m_Year << "��";
			A->AccountBill[i].m_Time.m_Month > 0 && A->AccountBill[i].m_Time.m_Month < 10 ? 
				cout << "0" << A->AccountBill[i].m_Time.m_Month : cout << A->AccountBill[i].m_Time.m_Month; cout << "��";
			A->AccountBill[i].m_Time.m_Day > 0 && A->AccountBill[i].m_Time.m_Day < 10 ?
				cout << "0" << A->AccountBill[i].m_Time.m_Day : cout << A->AccountBill[i].m_Time.m_Day; cout << "��" << "\t";
			cout << " " << A->m_Currency << " ";
			A->AccountBill[i].m_Variety == "+" ?
				cout << " " << A->AccountBill[i].m_InMoney << "\t": cout << "-" << A->AccountBill[i].m_OutMoney << "\t";
			cout << "��" << A->m_Currency << " " << A->AccountBill[i].m_Balance << "\t";
			cout << "ժҪ��" << A->AccountBill[i].m_Remark << endl;
		}
	}
}

//�޸ļ�¼
void amendRecord(Account* A) {
	if (A->m_Size == 0) {//��ʾ��¼Ϊ0
		cout << "#�޿��޸��˵���" << endl;
	}
	else {
		int amendNumber;
		while (true) {
			cout << "#������Ҫ�޸ĵļ�¼����ţ�";
			cin >> amendNumber;
			if (amendNumber > A->m_Size) {//����ѯ����Ƿ����
				cout << "#����ѯ�ļ�¼�����ڣ���ȷ�Ϻ��������룡" << endl;
			}
			else {
				Date time;
				cout << "#����������" << endl;
				while (true) {//��whileѭ����������Ƿ�Ϸ�
					cout << " �꣺";
					cin >> time.m_Year;
					if (0 < time.m_Year && time.m_Year < 9999) {
						A->AccountBill[amendNumber - 1].m_Time.m_Year = time.m_Year;
						break;
					}
					cout << " ���벻�Ϸ���";
				}
				while (true) {//��whileѭ����������Ƿ�Ϸ�
					cout << " �£�";
					cin >> time.m_Month;
					if (0 < time.m_Month && time.m_Month < 13) {
						A->AccountBill[amendNumber - 1].m_Time.m_Month = time.m_Month;
						break;
					}
					cout << " ���벻�Ϸ���";
				}
				while (true) {//��whileѭ����������Ƿ�Ϸ�
					cout << " �գ�";
					cin >> time.m_Day;
					if (0 < time.m_Day && time.m_Day < 32) {
						A->AccountBill[amendNumber - 1].m_Time.m_Day = time.m_Day;
						break;
					}
					cout << " ���벻�Ϸ���";
				}
				//����ժҪ
				string remark;
				cout << "#������ժҪ��";
				cin >> remark;
				A->AccountBill[amendNumber - 1].m_Remark = remark;
				//���������֧����־
				string variety;
				cout << "#ѡ���¼����(���� +/֧�� -)" << endl;
				while (true) {//��whileѭ����������Ƿ�Ϸ�
					cout << " �����루+/-����";
					cin >> variety;
					if (variety == "+" || variety == "-") {
						A->AccountBill[amendNumber - 1].m_Variety = variety;
						break;
					}
					cout << " ���벻�Ϸ���";
				}
				//������
				double money = 0;
				cout << "#�������";
				cin >> money;
				if (A->AccountBill[amendNumber - 1].m_Variety == "+") {
					A->AccountBill[amendNumber - 1].m_InMoney = money;
					A->AccountBill[amendNumber - 1].m_OutMoney = 0;
				}
				else {
					A->AccountBill[amendNumber - 1].m_InMoney = 0;
					A->AccountBill[amendNumber - 1].m_OutMoney = money;
				}
				break;
			}
		}
		cout << "�޸ļ�¼�ɹ���" << endl;
	}
	system("pause");//�밴���������
	system("cls");//��������
}

//ɾ����¼
void deleteRecord(Account* A) {
	if (A->m_Size == 0) {//��ʾ��¼Ϊ0
		cout << "#�޿�ɾ���˵���" << endl;
	}
	else {
		int deleteNumber;
		cout << "#������Ҫɾ���ļ�¼����ţ�";
		while (true) {//��whileѭ�������������Ƿ����
			cin >> deleteNumber;
			if (0 < deleteNumber && deleteNumber <= A->m_Size) {
				for (int i = deleteNumber - 1; i < A->m_Size; i++)
					A->AccountBill[i] = A->AccountBill[i + 1];
				A->m_Size--;
				break;
			}
			cout << " �Ҳ�����Ӧ��ţ���ȷ�ϣ�";
		}
		cout << "#ɾ����¼�ɹ���" << endl;
	}
	system("pause");//�밴���������
	system("cls");//��������
}

//��ѯͳ��
void countRecord(Account* A) {
	cout << "#�ѽ��롰��ѯͳ�ơ����ܣ�" << endl;
	if (A->m_Size == 0) {//��ʾ��¼Ϊ0
		cout << "#��ǰ��¼Ϊ�գ�" << endl;
		cout << "#�޿ɲ�ѯ��ͳ�Ƶ��˵���" << endl;
		system("pause");
		system("cls");
	}
	else {
		int n;
		cout << "#��ѡ����幦�ܣ�" << endl;
		cout << " ������ֹ���ڲ�ѯ�ö�ʱ�����֧��ϸ --- 1" << endl;
		cout << " ����ͳ�����������֧�� --------------- 2" << endl;
		cout << " ����ͳ�����������֧�� --------------- 3" << endl;
		cout << "#��ѡ��1/2/3����";
		while (true) {//��whileѭ����������Ƿ�����
			cin >> n;
			if (n == 1) {
				Date beginningTime, endTime;
				int b = -1, e = A->m_Size, k = 0;
				cout << "#�������ѯ��ʼ����" << endl;
				while (true) {//��whileѭ����������Ƿ�Ϸ�
					cout << " �꣺";
					cin >> beginningTime.m_Year;
					if (0 < beginningTime.m_Year && beginningTime.m_Year < 9999)
						break;
					cout << " ���벻�Ϸ���";
				}
				while (true) {//��whileѭ����������Ƿ�Ϸ�
					cout << " �£�";
					cin >> beginningTime.m_Month;
					if (0 < beginningTime.m_Month && beginningTime.m_Month < 13)
						break;
					cout << " ���벻�Ϸ���";
				}
				while (true) {//��whileѭ����������Ƿ�Ϸ�
					cout << " �գ�";
					cin >> beginningTime.m_Day;
					if (0 < beginningTime.m_Day && beginningTime.m_Day < 32)
						break;
					cout << " ���벻�Ϸ���";
				}
				cout << "#�������ѯ��������" << endl;
				while (true) {//��whileѭ����������Ƿ�Ϸ�
					cout << " �꣺";
					cin >> endTime.m_Year;
					if (0 < endTime.m_Year && endTime.m_Year < 9999)
						break;
					cout << " ���벻�Ϸ���";
				}
				while (true) {//��whileѭ����������Ƿ�Ϸ�
					cout << " �£�";
					cin >> endTime.m_Month;
					if (0 < endTime.m_Month && endTime.m_Month < 13)
						break;
					cout << " ���벻�Ϸ���";
				}
				while (true) {//��whileѭ����������Ƿ�Ϸ�
					cout << " �գ�";
					cin >> endTime.m_Day;
					if (0 < endTime.m_Day && endTime.m_Day < 32)
						break;
					cout << " ���벻�Ϸ���";
				}
				//���ڱȽ� 20030121<20030122<20030124
				int m = beginningTime.m_Year * 10000 + beginningTime.m_Month * 100 + beginningTime.m_Day,
					n = endTime.m_Year * 10000 + endTime.m_Month * 100 + endTime.m_Day;
				for (int i = 0; i < A->m_Size - 1; i++) {
					int p = A->AccountBill[i].m_Time.m_Year * 10000 + A->AccountBill[i].m_Time.m_Month * 100 + A->AccountBill[i].m_Time.m_Day,
						q = A->AccountBill[i + 1].m_Time.m_Year * 10000 + A->AccountBill[i + 1].m_Time.m_Month * 100 + A->AccountBill[i + 1].m_Time.m_Day;
					if (p < m && m <= q) {
						b = i + 1;
						break;
					}
				}
				for (int j = 0; j < A->m_Size - 1; j++) {
					int p = A->AccountBill[j].m_Time.m_Year * 10000 + A->AccountBill[j].m_Time.m_Month * 100 + A->AccountBill[j].m_Time.m_Day,
						q = A->AccountBill[j + 1].m_Time.m_Year * 10000 + A->AccountBill[j + 1].m_Time.m_Month * 100 + A->AccountBill[j + 1].m_Time.m_Day;
					if (p <= n && n < q) {
						e = j;
						break;
					}
				}
				if (b == -1) {//����Ƿ�����
					cout << "#���ִ���" << endl;
				}
				else {
					cout << "#����" << beginningTime.m_Year << "��" << beginningTime.m_Month << "��" << beginningTime.m_Day << "��"
						<< "��" << endTime.m_Year << "��" << endTime.m_Month << "��" << endTime.m_Day << "��"
						<< "����֧��ϸ���£�" << endl;
					for (int i = b; i <= e; i++) {
						cout << k + 1 << "\t";
						cout << A->AccountBill[i].m_Time.m_Year << "��";
						A->AccountBill[i].m_Time.m_Month > 0 && A->AccountBill[i].m_Time.m_Month < 10 ?
							cout << "0" << A->AccountBill[i].m_Time.m_Month : cout << A->AccountBill[i].m_Time.m_Month; cout << "��";
						A->AccountBill[i].m_Time.m_Day > 0 && A->AccountBill[i].m_Time.m_Day < 10 ?
							cout << "0" << A->AccountBill[i].m_Time.m_Day : cout << A->AccountBill[i].m_Time.m_Day; cout << "��" << "\t";
						cout << " " << A->m_Currency << " ";
						A->AccountBill[i].m_Variety == "+" ?
							cout << " " << A->AccountBill[i].m_InMoney << "\t" : cout << "-" << A->AccountBill[i].m_OutMoney << "\t";
						cout << "��" << A->m_Currency << " " << A->AccountBill[i].m_Balance << "\t";
						cout << "ժҪ��" << A->AccountBill[i].m_Remark << endl;
						k++;
					}
				}
				break;
			}
			if (n == 2) {
				int Y;
				double YsumIn = 0, YsumOut = 0;
				cout << "#��������Ҫ��ѯ����ݣ�";
				cin >> Y;
				for (int i = 0; i < A->m_Size; i++) {
					if (Y == A->AccountBill[i].m_Time.m_Year) {
						YsumIn += A->AccountBill[i].m_InMoney;
						YsumOut += A->AccountBill[i].m_OutMoney;
					}
				}
				cout << "#����" << Y << "�꣬";
				cout << "������Ϊ:" << A->m_Currency << " " << YsumIn << "\t";
				cout << "��֧��Ϊ:" << A->m_Currency << " " << YsumOut << endl;
				break;
			}
			if (n == 3) {
				int Y, M;
				double YMsumIn = 0, YMsumOut = 0;
				cout << "#��������Ҫ��ѯ����ݣ�";
				cin >> Y;
				cout << "#������" << Y << "�������ѯ���·ݣ�";
				cin >> M;
				for (int i = 0; i < A->m_Size; i++) {
					if (Y == A->AccountBill[i].m_Time.m_Year && M == A->AccountBill[i].m_Time.m_Month) {
						YMsumIn = YMsumIn + A->AccountBill[i].m_InMoney;
						YMsumOut = YMsumOut + A->AccountBill[i].m_OutMoney;
					}
				}
				cout << "#����" << Y << "��" << M << "�£�" << endl;
				cout << "������Ϊ:" << A->m_Currency << " " << YMsumIn << "\t";
				cout << "��֧��Ϊ:" << A->m_Currency << " " << YMsumOut << endl;
				break;
			}
			cout << "#����������������ѡ��1/2/3����";
		}
		system("pause");
		system("cls");
	}
}
	
//��ռ�¼
void cleanRecord(Account* A) {
	cout << "#�ѽ��롰��ռ�¼�����ܣ�" << endl;
	if (A->m_Size == 0) {//��ʾ��¼Ϊ0
		cout << "#��ǰ�˵���¼��Ϊ�գ�" << endl;
	}
	else {
		string select;
		cout << "���Ƿ�Ҫ������м�¼����-y/��-n��:" << endl;
		while (true) {//��whileѭ����������Ƿ�Ϸ�
			cin >> select;
			if (select == "y") {
				A->m_Size = 0;//�߼������
				cout << "��¼����գ�" << endl;
				break;
			}
			if (select == "n")
				break;
			cout << "����������������ѡ����-y/��-n����";
		}
		system("pause");
		system("cls");
	}
	
}