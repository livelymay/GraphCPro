#pragma once
#include<stdio.h>

//�洢ͼ�Ķ�����Ϣ
struct Vex {

	int num;			//������
	char name[20];		//��������
	char desc[1024];   //�������
};
extern struct Vex m_vex;


//�洢ͼ�ıߵ���Ϣ
struct Edge {
	int vex1, vex2;    //�ߵ���������
	int weight;        //Ȩֵ
};

extern struct Edge m_edge;



//���ڴ洢��������ͼ��ʵ��ͼ����ز���
struct Graph {
	int m_aAdjMatrix[20][20];//�ڽӾ��󣬱���ߵļ��ϣ�
	//������ÿ��Ԫ�ص�ֵ��Ϊ�ߵ�Ȩֵ
	Vex m_aVexs[20]; //�������飬���涥����Ϣ
	int m_nVexNum; //�������
};  //Graph�������ڴ洢��������ͼ
extern struct Graph m_Graph;


struct Path {
	int vexs[20];//����һ��·��
	Path *next;//��һ��·��
};
extern struct Path *PathList;



void Inint(void);//��ʼ��ͼ�ṹ
int InsertVex(Vex sVex);//��������ӵ�����������
int InsertEdge(Edge sEdge);//���߱��浽�ڽӾ�����
Vex GetVex(int nVex);//��ѯָ��������Ϣ
int FindEdge(int nVex, Edge aEdge[]);//��ѯ��ָ�����������ı�
int GetVexnum(void);//��ȡ��ǰ������
void DFS(int nVex, bool bVistted[], int &nIndex, Path &pList);//������ȱ���
//ʹ��������������㷨����ͼ
void DFSTraverse(int nVex, Path &pList);//����DFS���õ�������������������
int FindShortPath(int nVecStar,int nVexEnd,Edge aPath[]);
int FindMinTree(Edge aPath[]);//ͨ��Prim�㷨������С������
