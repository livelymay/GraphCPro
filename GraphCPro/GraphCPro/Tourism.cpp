#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"Graph.h"
#include"Tourism.h"

using namespace std;


void CreateGraph() {
	cout << "������������������������ͼ������������" << endl;
	Inint();



	/////////////���ö�����Ϣ////////////////////

	//���ļ�
	FILE *pVex = fopen("Vex.txt", "rb");
	if (!pVex) {
		cout << "���ļ�ʧ�ܣ�" << endl;
		return;
	}
	//��ȡ������Ŀ
	int count = 0;
	//ʹ��fscanf(�ļ�ָ�룬��ʽ�ַ����������б�)
	fscanf(pVex, "%d\n", &count);
	cout << "������Ŀ:" << count << endl;

	//��ȡ������Ϣ
	cout << "���������������㡪����������" << endl;
	Vex sVex;
	while (fscanf(pVex, "%d\n%s\n%s\n", &sVex.num, sVex.name, sVex.desc)!=-1) {
	
		cout <<sVex.num << "-------" <<sVex.name <<"��"<< endl;
		if (!InsertVex(sVex))
		{
			cout << "��������ʧ��" << endl;
			continue;
		}
	}

	fclose(pVex);
	pVex = NULL;


	/////////////���ñߵ���Ϣ///////////////////////

	FILE *pEdge = fopen("Edge.txt", "rb");
	if (!pEdge) {
		cout << "���ļ�ʧ��" << endl;
		return;
	}
	int num;
	Edge sEdge;

	fscanf(pEdge, "%d\n", &num);
	cout << "����Ŀ:" << num << endl;

	cout << "�����������ߡ�����������" << endl;
	//fscanf�ļ���ʽ�Լ�����һ�£�ʹ�ö��ų���858993460
	while (fscanf(pEdge, "%d %d %d\n", &sEdge.vex1, &sEdge.vex2, &sEdge.weight) != -1) {
		cout << "<" <<sEdge.vex1 << "," <<sEdge.vex2 << ">\t\t" <<sEdge.weight <<"m"<< endl;

		if (!InsertEdge(sEdge)) {
			cout << "��ӱ�ʧ��" << endl;
			continue;
		}
	}
	fclose(pEdge);
	pEdge = NULL;
}





void GetSpotInfo() {
	int vex;
	int nVexNum = GetVexnum();
	Vex sVex;
	cout << "����������ѯ������Ϣ������������" << endl;
	for (int i = 0; i < nVexNum; i++) {
		sVex = GetVex(i);
		cout << sVex.num << "����" << sVex.name <<"��"<< endl;
	}
	cout << "��������Ҫ���ҵþ�����Ϣ:";
	cin >> vex;
	if (vex < 0 || vex>20) {
		cout << "�������" << endl;
		return;
	}

	//��ѯ������Ϣ�����������֣�����
	sVex = GetVex(vex);
	cout << sVex.name << endl;
	cout << sVex.desc << endl;

	//��ѯ�ܱ߾�����Ϣ�������ܱ߾������֣��Լ�����
	Edge aEdge[20];
	int sEdgeNum = FindEdge(vex, aEdge);
	cout << "�������������ܱ߾��㡪����������" << endl;
	////////////////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < sEdgeNum; i++) {
		Vex v1 = GetVex(aEdge[i].vex1);
		Vex v2 = GetVex(aEdge[i].vex2);
		cout << v1.name << "����>" << v2.name <<"��"<< "\t" << aEdge[i].weight<<"m" << endl;

	}
}



void TravelPath() {
	int vex;
	int nVexNum = GetVexnum();
	Path pList;
	cout << "���������������ξ��㵼������������������" << endl;
	for (int i = 0; i < nVexNum; i++) {
		Vex sVex = GetVex(i);
		cout << sVex.num << "����" << sVex.name <<"��"<< endl;
	}
	cout << "��������ʼ����:";
	cin >> vex;
	if (vex < 0 || vex>20) {
		cout << "�������" << endl;
	}
	//pList = (PathList)malloc(sizeof(Path));
	cout << "����·��Ϊ��" << endl;
	DFSTraverse(vex, pList);
}

void FindShortPath() {
	
	int nVexStart;
	int nVexEnd;
	cout << "�������������������·��������������" << endl;
	int nVexNum = GetVexnum();  //��ȡ������
	for (int i = 0; i < nVexNum; i++) {//������ж�����Ϣ
		Vex sVex = GetVex(i);
		cout << sVex.num << "����" << sVex.name <<"��"<< endl;
	}
	cout << "��������ʼ��ı��";
	cin >> nVexStart;
	cout << "�������յ�ı��";
	cin >> nVexEnd;
	Edge edge[20];
	int shortPath= FindShortPath(nVexStart, nVexEnd, edge);
	cout << "���·��Ϊ��";
	int i = 0;     //����ʡ�ԣ���while������ѭ��
	while ( i< GetVexnum()) {
		if (edge[i].vex1 != edge[i].vex2)
			cout << GetVex(edge[i].vex1).name << "��>";
		else {
			cout << GetVex(edge[i - 1].vex2).name <<endl;
			break;
		}
		i++;
	}
	cout << "��̾���Ϊ��" << shortPath<<"m"<< endl;
}


void DesignPath(void) {
	cout << "�����������������·���򡪡���������" << endl;
	cout << "��һ����������֮�������·��" << endl;
	Edge aPath[20];
	int length = FindMinTree(aPath);
	for (int i = 0; (i < GetVexnum())&&(aPath[i].vex1!=aPath[i].vex2); i++)
	{
		cout <<GetVex(aPath[i].vex1).name << " ��" << GetVex(aPath[i].vex2).name << "   " << aPath[i].weight << "m" << endl;
	}
	cout << "�����·���ܳ���Ϊ��" << length <<"m"<< endl;

}