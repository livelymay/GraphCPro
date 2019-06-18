#include<iostream>
#include<locale>
#include"Graph.h"



using namespace std;

struct Vex m_vex;        //�ظ���������
struct Edge m_edge;
struct Graph m_Graph;
struct Path pList;



//��ʼ��ͼ�ṹ
void Inint(){
	m_Graph.m_nVexNum = 0; //��ʼ���������
	//�ڽӾ����ʼ��
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			//��ʼ������֮��ľ���Ϊ0
			m_Graph.m_aAdjMatrix[i][j] = 0;
		}
	}
}

//��������ӵ�����������
int InsertVex(Vex sVex) {
	if (m_Graph.m_nVexNum == 20) {
		return false;
	}
	m_Graph.m_aVexs[m_Graph.m_nVexNum++] = sVex;//���붥����Ϣ
	return true;
}

//���߱��浽�ڽӾ�����
int InsertEdge(Edge sEdge) {
	if (sEdge.vex1 < 0 || sEdge.vex1>20 || sEdge.vex2 < 0 || sEdge.vex2>20) {
		return false;
	}
	m_Graph.m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	m_Graph.m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
	return true;
}


//��ѯָ��������Ϣ
Vex GetVex(int nVex) {
		return m_Graph.m_aVexs[nVex];
}



//��ѯ��ָ�����������ı�
int FindEdge(int nVex, Edge aEdge[]) {
	int k=0;
	for (int i = 0; i < m_Graph.m_nVexNum; i++) {
		if (m_Graph.m_aAdjMatrix[nVex][i]!=0) {
			aEdge[k].vex1 = nVex;
			aEdge[k].vex2 = i;
			aEdge[k].weight = m_Graph.m_aAdjMatrix[nVex][i];
			k++;
		}


	}
	return k;
}




//��ȡ��ǰ������
int GetVexnum(void){

	return m_Graph.m_nVexNum;
}

// ʹ��������������㷨����ͼ
int cnt = 0;
void DFS(int nVex, bool bVisited[], int &nIndex, Path &pList) {
	
	int n = GetVexnum();
	bVisited[nVex] = true;//�ѷ���
	pList.vexs[nIndex++] = nVex;  //���ʶ���nVex
	if(nIndex==n){        //���·��
		cout << "·��" << ++cnt << ":";
		for (int i = 0; i < n; i++) {
		
			cout << GetVex(pList.vexs[i]).name;
			if (i<GetVexnum()-1) {
				cout <<"��>";
			}
		}
		cout << endl;
	}
	else {
		for (int j = 0; j < n; j++) {
			if (m_Graph.m_aAdjMatrix[nVex][j] && (!bVisited[j])) {
				DFS(j, bVisited, nIndex, pList);
				bVisited[j] = false;
				nIndex--;
			}
		}
	}
}

//����DFS���õ�������������������
void DFSTraverse(int nVex, Path &pList) {
	int nIndex = 0;
	bool bVisited[20] = { false };
	DFS(nVex,bVisited,nIndex,pList);
}

//���룺��ʼ�����ź�Ŀ�ľ�����
//���:���·��
int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[]) {
	bool fin[20];		//�ѻ�����·��
	int dist[20];		//��nVexStart����ǰ�����̾���
	int prev[20];		//�洢��һ����
									//��ʼ������
	for (int i = 0; i <m_Graph.m_nVexNum; i++)
	{
		fin[i] = false;
		if (m_Graph.m_aAdjMatrix[nVexStart][i] != 0)
			dist[i] = m_Graph.m_aAdjMatrix[nVexStart][i];
		else
			dist[i] = INT_MAX;	//��û��·���ĵ���Ȩ��Ϊ����
		if (dist[i] == INT_MAX)
			prev[i] = -1;
		else
			prev[i] = nVexStart;//����·��������һ����ΪnVexStart
	}
	fin[nVexStart] = true;
	dist[nVexStart] = 0;
	prev[nVexStart] = nVexStart;
	for (int p = 0; p < m_Graph.m_nVexNum - 1; p++)
	{
		int v = nVexStart;
		int min = INT_MAX;
		for (int i = 0; i < m_Graph.m_nVexNum; ++i)
		{
			if ((!fin[i]) && (dist[i]<min))
			{
				v = i;			//��ȡδ������·������Сֵ��
				min = dist[i];	//��ȡδ������·������Сֵ
			}
		}
		fin[v] = true;
		for (int i = 0; i < m_Graph.m_nVexNum; ++i)
			if ((!fin[i]) && (dist[v] + m_Graph.m_aAdjMatrix[v][i] < dist[i]) && (m_Graph.m_aAdjMatrix[v][i] != 0))
			{
				dist[i] = dist[v] + m_Graph.m_aAdjMatrix[v][i];	//�������·��
				prev[i] = v;							//�洢��һ����
			}
	}
	int num = 0, last = nVexEnd;
	//��¼·���еı���
	while (prev[last] != nVexStart)
	{
		num++;
		last = prev[last];
	}
	last = nVexEnd;
	//����·����Ϣ
	while (num >= 0)
	{
		aPath[num].vex2 = last;
		aPath[num].vex1 = prev[last];
		aPath[num].weight = m_Graph.m_aAdjMatrix[last][prev[last]];
		last = prev[last];
		num--;
	}
	return dist[nVexEnd];		//�������·������
}


int FindMinTree(Edge aPath[]) {

	int lowcost[20] = { 0 };	//��̾���
	bool addVexNew[20] = { true };//�ѻ����̾���ĵ�
	int prev[20] = { 0 };		//֮ǰ��
	int length = 0;
	//��ʼ�����鲢Ĭ����ʼ����Ϊ0��
	for (int i = 1; i < m_Graph.m_nVexNum; i++)
	{
		if (m_Graph.m_aAdjMatrix[0][i] != 0)
			lowcost[i] = m_Graph.m_aAdjMatrix[0][i];
		else
			lowcost[i] = INT_MAX;
		addVexNew[i] = false;
	}
	for (int p = 0; p< m_Graph.m_nVexNum - 1; p++)
	{
		int min = INT_MAX;
		int v = 0;
		for (int i = 1; i <m_Graph.m_nVexNum; i++)
		{
			if ((!addVexNew[i]) && lowcost[i] < min)
			{
				min = lowcost[i];
				v = i;
			}
		}
		if (v != 0)
		{
			//����·����Ϣ
			aPath[p].vex1 = prev[v];
			aPath[p].vex2 = v;
			aPath[p].weight = lowcost[v];
			addVexNew[v] = true;                                      //��v��Vnew��
			length += lowcost[v];                             //����·������֮��
			for (int i = 0; i<m_Graph.m_nVexNum; i++)
			{
				if ((!addVexNew[i]) && (m_Graph.m_aAdjMatrix[v][i]<lowcost[i]) && (m_Graph.m_aAdjMatrix[i][v] != 0))
				{
					lowcost[i] = m_Graph.m_aAdjMatrix[v][i];                     //��ʱv�����Vnew ��Ҫ����lowcost
					prev[i] = v;										//�洢��һ����
				}
			}
		}
	}
	return length;
}