#include<iostream>
#include<stdio.h>
#include"Tourism.h"

using namespace std;

int main() {
	char choice;
	while (1) {
		cout << "____________������Ϣ����ϵͳ____________" << endl;
		cout << "1.������������ͼ" << endl;
		cout << "2.��ѯ������Ϣ" << endl;
		cout << "3.���ξ��㵼��" << endl;
		cout << "4.�������·��" << endl;
		cout << "5.�����·�滮" << endl;
		cout << "0.�˳�" << endl;
		cout << "�������������<0~5>��" << endl;
		cin >> choice;
		switch (choice) {
		case '0':exit(0); break;
		case '1':CreateGraph(); break;
		case '2':GetSpotInfo(); break;
		case '3':TravelPath(); break;
		case '4':FindShortPath(); break;
		case '5':DesignPath(); break;
		default:
			cout << "��������������������" << endl;

		}
	}
}