#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"Graph.h"
#include"Tourism.h"

using namespace std;


void CreateGraph() {
	cout << "——————创建景区景点图——————" << endl;
	Inint();



	/////////////设置顶点信息////////////////////

	//打开文件
	FILE *pVex = fopen("Vex.txt", "rb");
	if (!pVex) {
		cout << "打开文件失败！" << endl;
		return;
	}
	//读取顶点数目
	int count = 0;
	//使用fscanf(文件指针，格式字符串，输入列表)
	fscanf(pVex, "%d\n", &count);
	cout << "顶点数目:" << count << endl;

	//读取顶点信息
	cout << "——————顶点——————" << endl;
	Vex sVex;
	while (fscanf(pVex, "%d\n%s\n%s\n", &sVex.num, sVex.name, sVex.desc)!=-1) {
	
		cout <<sVex.num << "-------" <<sVex.name <<"区"<< endl;
		if (!InsertVex(sVex))
		{
			cout << "新增顶点失败" << endl;
			continue;
		}
	}

	fclose(pVex);
	pVex = NULL;


	/////////////设置边的信息///////////////////////

	FILE *pEdge = fopen("Edge.txt", "rb");
	if (!pEdge) {
		cout << "打开文件失败" << endl;
		return;
	}
	int num;
	Edge sEdge;

	fscanf(pEdge, "%d\n", &num);
	cout << "边数目:" << num << endl;

	cout << "—————边——————" << endl;
	//fscanf文件格式以及输入一致，使用逗号出错858993460
	while (fscanf(pEdge, "%d %d %d\n", &sEdge.vex1, &sEdge.vex2, &sEdge.weight) != -1) {
		cout << "<" <<sEdge.vex1 << "," <<sEdge.vex2 << ">\t\t" <<sEdge.weight <<"m"<< endl;

		if (!InsertEdge(sEdge)) {
			cout << "添加边失败" << endl;
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
	cout << "————查询景点信息——————" << endl;
	for (int i = 0; i < nVexNum; i++) {
		sVex = GetVex(i);
		cout << sVex.num << "——" << sVex.name <<"区"<< endl;
	}
	cout << "请输入想要查找得景点信息:";
	cin >> vex;
	if (vex < 0 || vex>20) {
		cout << "输入错误" << endl;
		return;
	}

	//查询顶点信息，包包含名字，描述
	sVex = GetVex(vex);
	cout << sVex.name << endl;
	cout << sVex.desc << endl;

	//查询周边景点信息，包含周边景点名字，以及距离
	Edge aEdge[20];
	int sEdgeNum = FindEdge(vex, aEdge);
	cout << "——————周边景点——————" << endl;
	////////////////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < sEdgeNum; i++) {
		Vex v1 = GetVex(aEdge[i].vex1);
		Vex v2 = GetVex(aEdge[i].vex2);
		cout << v1.name << "——>" << v2.name <<"区"<< "\t" << aEdge[i].weight<<"m" << endl;

	}
}



void TravelPath() {
	int vex;
	int nVexNum = GetVexnum();
	Path pList;
	cout << "——————旅游景点导航————————" << endl;
	for (int i = 0; i < nVexNum; i++) {
		Vex sVex = GetVex(i);
		cout << sVex.num << "——" << sVex.name <<"区"<< endl;
	}
	cout << "请输入起始点编号:";
	cin >> vex;
	if (vex < 0 || vex>20) {
		cout << "输入错误！" << endl;
	}
	//pList = (PathList)malloc(sizeof(Path));
	cout << "导游路线为：" << endl;
	DFSTraverse(vex, pList);
}

void FindShortPath() {
	
	int nVexStart;
	int nVexEnd;
	cout << "——————搜索最短路径——————" << endl;
	int nVexNum = GetVexnum();  //获取顶点数
	for (int i = 0; i < nVexNum; i++) {//输出所有顶点信息
		Vex sVex = GetVex(i);
		cout << sVex.num << "——" << sVex.name <<"区"<< endl;
	}
	cout << "请输入起始点的编号";
	cin >> nVexStart;
	cout << "请输入终点的编号";
	cin >> nVexEnd;
	Edge edge[20];
	int shortPath= FindShortPath(nVexStart, nVexEnd, edge);
	cout << "最短路线为：";
	int i = 0;     //不可省略，在while里变成死循环
	while ( i< GetVexnum()) {
		if (edge[i].vex1 != edge[i].vex2)
			cout << GetVex(edge[i].vex1).name << "—>";
		else {
			cout << GetVex(edge[i - 1].vex2).name <<endl;
			break;
		}
		i++;
	}
	cout << "最短距离为：" << shortPath<<"m"<< endl;
}


void DesignPath(void) {
	cout << "——————铺设电路规则——————" << endl;
	cout << "在一下两个景点之间铺设电路：" << endl;
	Edge aPath[20];
	int length = FindMinTree(aPath);
	for (int i = 0; (i < GetVexnum())&&(aPath[i].vex1!=aPath[i].vex2); i++)
	{
		cout <<GetVex(aPath[i].vex1).name << " —" << GetVex(aPath[i].vex2).name << "   " << aPath[i].weight << "m" << endl;
	}
	cout << "铺设电路的总长度为：" << length <<"m"<< endl;

}