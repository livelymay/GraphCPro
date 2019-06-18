#include<iostream>
#include<stdio.h>
#include"Tourism.h"

using namespace std;

int main() {
	char choice;
	while (1) {
		cout << "____________景区信息管理系统____________" << endl;
		cout << "1.创建景区景点图" << endl;
		cout << "2.查询景点信息" << endl;
		cout << "3.旅游景点导航" << endl;
		cout << "4.搜索最短路径" << endl;
		cout << "5.铺设电路规划" << endl;
		cout << "0.退出" << endl;
		cout << "请输入操作编码<0~5>：" << endl;
		cin >> choice;
		switch (choice) {
		case '0':exit(0); break;
		case '1':CreateGraph(); break;
		case '2':GetSpotInfo(); break;
		case '3':TravelPath(); break;
		case '4':FindShortPath(); break;
		case '5':DesignPath(); break;
		default:
			cout << "输入错误，请检查后重新输入" << endl;

		}
	}
}