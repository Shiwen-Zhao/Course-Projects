#include <iostream>
#include <string>//用到string数据类型
using namespace std;
#define MAX 100//宏常量，用于定义账单最大容量，可更改
//声明日期结构体
struct Date {
	int m_Year;//年
	int m_Month;//月
	int m_Day;//日
};
//声明收支记录结构体
struct Record {
	Date m_Time;//日期
	string m_Remark;//备注
	string m_Variety;//收入或支出
	double m_InMoney;//收入金额
	double m_OutMoney;//支出金额
	double m_Balance;//余额
};
//设计账户结构体
struct Account {
	string m_Name;//账户名称
	string m_Currency;//币种
	double m_Balance;//账户余额
	struct Record AccountBill[MAX];//收支记录数组
	int m_Size;//账户记录条数
};
void initializeAccount(Account*);//初始化账户函数
void showMenu();//主界面显示函数
void sortRecord(Account*);//记录按时间排序函数
void calculateBalance(Account*);//余额计算函数
void addRecord(Account*);//记录收支函数
void showRecord(Account*);//查看明细函数
void amendRecord(Account*);//修改记录函数
void deleteRecord(Account*);//删除记录函数
void countRecord(Account*);//查询统计记录函数
void cleanRecord(Account*);//清空记录函数

int main() {
	Account A1;//创建账户
	initializeAccount(&A1);//调用初始化账户函数
	A1.m_Size = 0;//初始化账户账单个数
	int select = 0;//创建用户输入变量
	while (true) {//用while循环检测输入是否合法
		showMenu();//调用主界面显示函数
		sortRecord(&A1);//调用记录按时间排序函数
		calculateBalance(&A1);//调用余额计算函数
		cout << "账户名称：" << A1.m_Name << "\t";//显示账户名称
		//显示账户余额
		if (A1.m_Size == 0)cout << "当前账户余额：" << A1.m_Balance << endl;
		else cout << "账户余额：" << A1.AccountBill[A1.m_Size - 1].m_Balance << endl;
		cout << "#请选择功能序号（1/2/3/4/5/6/0）：";
		cin >> select;//用户输入功能序号
		switch (select) {
		case 1://1.记录收支
			addRecord(&A1);//调用记录收支函数
			break;
		case 2://2.查看明细
			showRecord(&A1);//调用查看明细函数
			system("pause");//请按任意键继续
			system("cls");//清屏操作
			break;
		case 3://3.修改记录
			cout << "#已进入“修改记录”功能！" << endl;
			showRecord(&A1);//调用查看明细函数
			amendRecord(&A1);//调用修改记录函数
			break;
		case 4://4.删除记录
			cout << "#已进入“删除记录”功能！" << endl;
			showRecord(&A1);//调用查看明细函数
			deleteRecord(&A1);//调用删除记录函数
			break;
		case 5://5.记录统计
			countRecord(&A1);//调用记录统计函数
			break;
		case 6://6.清空记录
			cleanRecord(&A1);//调用清空记录函数
			break;
		case 0://0.退出系统
			cout << "#欢迎下次使用！" << endl;
			system("pause");
			return 0;
			break;
		default:
			system("cls");//清屏操作
			cout << "#您输入有误！" << endl;
			break;
		}
	}
	system("pause");
	return 0;
}

//主界面显示
void showMenu() {
	cout << "************************" << endl;
	cout << "*                      *" << endl;
	cout << "*   个人收支管理系统   *" << endl;
	cout << "*                      *" << endl;
	cout << "************************" << endl;
	cout << "****** 1.记录收支 ******" << endl;
	cout << "****** 2.查看明细 ******" << endl;
	cout << "****** 3.修改记录 ******" << endl;
	cout << "****** 4.删除记录 ******" << endl;
	cout << "****** 5.查询统计 ******" << endl;
	cout << "****** 6.清空记录 ******" << endl;
	cout << "****** 0.退出系统 ******" << endl;
	cout << "************************" << endl<< endl;
}

//初始化账户
void initializeAccount(Account* A) {
	string name;//创建局部变量账户名字
	double balance;//创建局部变量余额
	int Currency = 0;//创建局部变量币种代号
	cout << "欢迎使用个人收支管理系统！" << endl;
	cout << "请先初始化账户：" << endl;
	cout << "#请输入账户名称：";
	cin >> name;
	A->m_Name = name;//将用户输入的局部变量的值赋值给真正的值
	cout << "#请输入账户余额：";
	cin >> balance;
	A->m_Balance = balance;//将用户输入的局部变量账户余额赋值给真正的账户余额
	cout << "!提示：" << endl;
	cout << " 账本默认记录币种是人民币CNY！" << endl;
	cout << " 如需更改请输入1，不更改请输入0！" << endl;
	cout << "#是否更改（1/0)：";
	while (true) {//用while循环检测输入是否合法
		cin >> Currency;
		if (Currency == 0) {
			A->m_Currency = "CNY";//将用户输入的局部变量的值赋值给真正的值
			break;
		}
		else if (Currency == 1) {//修改账户币种
			int selectCurrency = 0;
			cout << "#选择币种" << endl;
			cout << " 人民币CNY - 0" << endl;
			cout << " 美元USD ----1" << endl;
			cout << " 欧元EUR --- 2" << endl;
			cout << " 日元JPY ----3" << endl;
			cout << " 英镑GPB ----4" << endl;
			while (true) {//用while循环检测输入是否合法
				cout << "请选择（0/1/2/3/4）：";
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
				cout << "输入不合法！";
			}
			break;
		}
		cout << "输入不合法！是否更改（1/0)：";
	}
	cout << "#初始化账户成功！" << endl;
	cout << "“" << A->m_Name << "”" << "账户当前余额为：" 
		<< A->m_Currency <<" "<< A->m_Balance << endl;
	system("pause");//请按任意键继续
	system("cls");//清屏操作
}

//记录收支
void addRecord(Account* A) {
	cout << "#已进入“记录收支”功能！" << endl;
	if (A->m_Size == MAX) {//检测账户记录是否已达到最大容量
		cout << "该账户记录已经达到最大容量，无法继续添加！" << endl;
		system("pause");
		system("cls");
	}
	else {
		//输入日期
		Date time;//创建Date结构体类型局部变量
		cout << "#请输入日期" << endl;
		while (true) {//用while循环检测输入是否合法
			cout << " 年：";
			cin >> time.m_Year;
			//检测日期输入是否合法
			if (0 < time.m_Year && time.m_Year < 9999) {
				A->AccountBill[A->m_Size].m_Time.m_Year = time.m_Year;//将用户输入的局部变量的值赋值给真正的值
				break;
			}
			cout << " 输入不合法！";
		}
		while (true) {//用while循环检测输入是否合法
			cout << " 月：";
			cin >> time.m_Month;
			//检测日期输入是否合法
			if (0 < time.m_Month && time.m_Month < 13) {
				A->AccountBill[A->m_Size].m_Time.m_Month = time.m_Month;//将用户输入的局部变量的值赋值给真正的值
				break;
			}
			cout << " 输入不合法！";
		}
		while (true) {//用while循环检测输入是否合法
			cout << " 日：";
			cin >> time.m_Day;
			//检测日期输入是否合法
			if (0 < time.m_Day && time.m_Day < 32) {
				A->AccountBill[A->m_Size].m_Time.m_Day = time.m_Day;//将用户输入的局部变量的值赋值给真正的值
				break;
			}
			cout << " 输入不合法！";
		}
		//输入摘要
		string remark;
		cout << "#请输入摘要：";
		cin >> remark;
		A->AccountBill[A->m_Size].m_Remark = remark;//将用户输入的局部变量的值赋值给真正的值
		//输入收入或支出标志
		string variety;
		cout << "#选择记录类型(收入 +/支出 -)" << endl;
		while (true) {//用while循环检测输入是否合法

			cout << " 请输入（+/-）：";
			cin >> variety;
			if (variety == "+" || variety == "-") {
				A->AccountBill[A->m_Size].m_Variety = variety;//将用户输入的局部变量的值赋值给真正的值
				break;
			}
			cout << " 输入不合法！";
		}
		//输入金额
		double money = 0;
		cout << "#请输入金额：";
		cin >> money;
		if (A->AccountBill[A->m_Size].m_Variety == "+") {
			A->AccountBill[A->m_Size].m_InMoney = money;//将用户输入的局部变量的值赋值给真正的值
			A->AccountBill[A->m_Size].m_OutMoney = 0;//收入模式，支出为0
		}
		else {
			A->AccountBill[A->m_Size].m_InMoney = 0;//支出模式，收入为0
			A->AccountBill[A->m_Size].m_OutMoney = money;//将用户输入的局部变量的值赋值给真正的值
		}
		//更新账单
		A->m_Size++;
		cout << "#添加账单成功！" << endl;
		system("pause");//请按任意键继续
		system("cls");//清屏操作
	}
}

//账单按时间排序
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

//余额计算
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

//查看明细
void showRecord(Account* A) {
	if (A->m_Size == 0) {//提示记录为0
		cout << "#当前记录为空！" << endl;
	}
	else {
		for (int i = 0; i < A->m_Size; i++) {
			cout << i+1 << "\t";
			cout << A->AccountBill[i].m_Time.m_Year << "年";
			A->AccountBill[i].m_Time.m_Month > 0 && A->AccountBill[i].m_Time.m_Month < 10 ? 
				cout << "0" << A->AccountBill[i].m_Time.m_Month : cout << A->AccountBill[i].m_Time.m_Month; cout << "月";
			A->AccountBill[i].m_Time.m_Day > 0 && A->AccountBill[i].m_Time.m_Day < 10 ?
				cout << "0" << A->AccountBill[i].m_Time.m_Day : cout << A->AccountBill[i].m_Time.m_Day; cout << "日" << "\t";
			cout << " " << A->m_Currency << " ";
			A->AccountBill[i].m_Variety == "+" ?
				cout << " " << A->AccountBill[i].m_InMoney << "\t": cout << "-" << A->AccountBill[i].m_OutMoney << "\t";
			cout << "余额：" << A->m_Currency << " " << A->AccountBill[i].m_Balance << "\t";
			cout << "摘要：" << A->AccountBill[i].m_Remark << endl;
		}
	}
}

//修改记录
void amendRecord(Account* A) {
	if (A->m_Size == 0) {//提示记录为0
		cout << "#无可修改账单！" << endl;
	}
	else {
		int amendNumber;
		while (true) {
			cout << "#请输入要修改的记录的序号：";
			cin >> amendNumber;
			if (amendNumber > A->m_Size) {//检测查询序号是否存在
				cout << "#您查询的记录不存在，请确认后重新输入！" << endl;
			}
			else {
				Date time;
				cout << "#请输入日期" << endl;
				while (true) {//用while循环检测输入是否合法
					cout << " 年：";
					cin >> time.m_Year;
					if (0 < time.m_Year && time.m_Year < 9999) {
						A->AccountBill[amendNumber - 1].m_Time.m_Year = time.m_Year;
						break;
					}
					cout << " 输入不合法！";
				}
				while (true) {//用while循环检测输入是否合法
					cout << " 月：";
					cin >> time.m_Month;
					if (0 < time.m_Month && time.m_Month < 13) {
						A->AccountBill[amendNumber - 1].m_Time.m_Month = time.m_Month;
						break;
					}
					cout << " 输入不合法！";
				}
				while (true) {//用while循环检测输入是否合法
					cout << " 日：";
					cin >> time.m_Day;
					if (0 < time.m_Day && time.m_Day < 32) {
						A->AccountBill[amendNumber - 1].m_Time.m_Day = time.m_Day;
						break;
					}
					cout << " 输入不合法！";
				}
				//输入摘要
				string remark;
				cout << "#请输入摘要：";
				cin >> remark;
				A->AccountBill[amendNumber - 1].m_Remark = remark;
				//输入收入或支出标志
				string variety;
				cout << "#选择记录类型(收入 +/支出 -)" << endl;
				while (true) {//用while循环检测输入是否合法
					cout << " 请输入（+/-）：";
					cin >> variety;
					if (variety == "+" || variety == "-") {
						A->AccountBill[amendNumber - 1].m_Variety = variety;
						break;
					}
					cout << " 输入不合法！";
				}
				//输入金额
				double money = 0;
				cout << "#请输入金额：";
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
		cout << "修改记录成功！" << endl;
	}
	system("pause");//请按任意键继续
	system("cls");//清屏操作
}

//删除记录
void deleteRecord(Account* A) {
	if (A->m_Size == 0) {//提示记录为0
		cout << "#无可删除账单！" << endl;
	}
	else {
		int deleteNumber;
		cout << "#请输入要删除的记录的序号：";
		while (true) {//用while循环检测输入序号是否存在
			cin >> deleteNumber;
			if (0 < deleteNumber && deleteNumber <= A->m_Size) {
				for (int i = deleteNumber - 1; i < A->m_Size; i++)
					A->AccountBill[i] = A->AccountBill[i + 1];
				A->m_Size--;
				break;
			}
			cout << " 找不到对应序号！请确认：";
		}
		cout << "#删除记录成功！" << endl;
	}
	system("pause");//请按任意键继续
	system("cls");//清屏操作
}

//查询统计
void countRecord(Account* A) {
	cout << "#已进入“查询统计”功能！" << endl;
	if (A->m_Size == 0) {//提示记录为0
		cout << "#当前记录为空！" << endl;
		cout << "#无可查询或统计的账单！" << endl;
		system("pause");
		system("cls");
	}
	else {
		int n;
		cout << "#请选择具体功能：" << endl;
		cout << " 输入起止日期查询该段时间的收支明细 --- 1" << endl;
		cout << " 按年统计总收入和总支出 --------------- 2" << endl;
		cout << " 按月统计总收入和总支出 --------------- 3" << endl;
		cout << "#请选择（1/2/3）：";
		while (true) {//用while循环检测输入是否有误
			cin >> n;
			if (n == 1) {
				Date beginningTime, endTime;
				int b = -1, e = A->m_Size, k = 0;
				cout << "#请输入查询开始日期" << endl;
				while (true) {//用while循环检测输入是否合法
					cout << " 年：";
					cin >> beginningTime.m_Year;
					if (0 < beginningTime.m_Year && beginningTime.m_Year < 9999)
						break;
					cout << " 输入不合法！";
				}
				while (true) {//用while循环检测输入是否合法
					cout << " 月：";
					cin >> beginningTime.m_Month;
					if (0 < beginningTime.m_Month && beginningTime.m_Month < 13)
						break;
					cout << " 输入不合法！";
				}
				while (true) {//用while循环检测输入是否合法
					cout << " 日：";
					cin >> beginningTime.m_Day;
					if (0 < beginningTime.m_Day && beginningTime.m_Day < 32)
						break;
					cout << " 输入不合法！";
				}
				cout << "#请输入查询结束日期" << endl;
				while (true) {//用while循环检测输入是否合法
					cout << " 年：";
					cin >> endTime.m_Year;
					if (0 < endTime.m_Year && endTime.m_Year < 9999)
						break;
					cout << " 输入不合法！";
				}
				while (true) {//用while循环检测输入是否合法
					cout << " 月：";
					cin >> endTime.m_Month;
					if (0 < endTime.m_Month && endTime.m_Month < 13)
						break;
					cout << " 输入不合法！";
				}
				while (true) {//用while循环检测输入是否合法
					cout << " 日：";
					cin >> endTime.m_Day;
					if (0 < endTime.m_Day && endTime.m_Day < 32)
						break;
					cout << " 输入不合法！";
				}
				//日期比较 20030121<20030122<20030124
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
				if (b == -1) {//检测是否有误
					cout << "#出现错误！" << endl;
				}
				else {
					cout << "#您从" << beginningTime.m_Year << "年" << beginningTime.m_Month << "月" << beginningTime.m_Day << "日"
						<< "到" << endTime.m_Year << "年" << endTime.m_Month << "月" << endTime.m_Day << "日"
						<< "的收支明细如下：" << endl;
					for (int i = b; i <= e; i++) {
						cout << k + 1 << "\t";
						cout << A->AccountBill[i].m_Time.m_Year << "年";
						A->AccountBill[i].m_Time.m_Month > 0 && A->AccountBill[i].m_Time.m_Month < 10 ?
							cout << "0" << A->AccountBill[i].m_Time.m_Month : cout << A->AccountBill[i].m_Time.m_Month; cout << "月";
						A->AccountBill[i].m_Time.m_Day > 0 && A->AccountBill[i].m_Time.m_Day < 10 ?
							cout << "0" << A->AccountBill[i].m_Time.m_Day : cout << A->AccountBill[i].m_Time.m_Day; cout << "日" << "\t";
						cout << " " << A->m_Currency << " ";
						A->AccountBill[i].m_Variety == "+" ?
							cout << " " << A->AccountBill[i].m_InMoney << "\t" : cout << "-" << A->AccountBill[i].m_OutMoney << "\t";
						cout << "余额：" << A->m_Currency << " " << A->AccountBill[i].m_Balance << "\t";
						cout << "摘要：" << A->AccountBill[i].m_Remark << endl;
						k++;
					}
				}
				break;
			}
			if (n == 2) {
				int Y;
				double YsumIn = 0, YsumOut = 0;
				cout << "#请输入想要查询的年份：";
				cin >> Y;
				for (int i = 0; i < A->m_Size; i++) {
					if (Y == A->AccountBill[i].m_Time.m_Year) {
						YsumIn += A->AccountBill[i].m_InMoney;
						YsumOut += A->AccountBill[i].m_OutMoney;
					}
				}
				cout << "#您在" << Y << "年，";
				cout << "总收入为:" << A->m_Currency << " " << YsumIn << "\t";
				cout << "总支出为:" << A->m_Currency << " " << YsumOut << endl;
				break;
			}
			if (n == 3) {
				int Y, M;
				double YMsumIn = 0, YMsumOut = 0;
				cout << "#请输入想要查询的年份：";
				cin >> Y;
				cout << "#请输入" << Y << "年中想查询的月份：";
				cin >> M;
				for (int i = 0; i < A->m_Size; i++) {
					if (Y == A->AccountBill[i].m_Time.m_Year && M == A->AccountBill[i].m_Time.m_Month) {
						YMsumIn = YMsumIn + A->AccountBill[i].m_InMoney;
						YMsumOut = YMsumOut + A->AccountBill[i].m_OutMoney;
					}
				}
				cout << "#您在" << Y << "年" << M << "月，" << endl;
				cout << "总收入为:" << A->m_Currency << " " << YMsumIn << "\t";
				cout << "总支出为:" << A->m_Currency << " " << YMsumOut << endl;
				break;
			}
			cout << "#您输入有误！请重新选择（1/2/3）：";
		}
		system("pause");
		system("cls");
	}
}
	
//清空记录
void cleanRecord(Account* A) {
	cout << "#已进入“清空记录”功能！" << endl;
	if (A->m_Size == 0) {//提示记录为0
		cout << "#当前账单记录已为空！" << endl;
	}
	else {
		string select;
		cout << "您是否要清空所有记录（是-y/否-n）:" << endl;
		while (true) {//用while循环检测输入是否合法
			cin >> select;
			if (select == "y") {
				A->m_Size = 0;//逻辑上清空
				cout << "记录已清空！" << endl;
				break;
			}
			if (select == "n")
				break;
			cout << "您输入有误！请重新选择（是-y/否-n）：";
		}
		system("pause");
		system("cls");
	}
	
}