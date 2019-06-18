#pragma once
#include<stdio.h>

//存储图的顶点信息
struct Vex {

	int num;			//景点编号
	char name[20];		//景点名字
	char desc[1024];   //景点介绍
};
extern struct Vex m_vex;


//存储图的边的信息
struct Edge {
	int vex1, vex2;    //边的两个顶点
	int weight;        //权值
};

extern struct Edge m_edge;



//用于存储景区景点图，实现图的相关操作
struct Graph {
	int m_aAdjMatrix[20][20];//邻接矩阵，保存边的集合，
	//数组中每个元素的值即为边的权值
	Vex m_aVexs[20]; //顶点数组，保存顶点信息
	int m_nVexNum; //顶点个数
};  //Graph对象，用于存储景区景点图
extern struct Graph m_Graph;


struct Path {
	int vexs[20];//保存一条路径
	Path *next;//下一条路径
};
extern struct Path *PathList;



void Inint(void);//初始化图结构
int InsertVex(Vex sVex);//将顶点添加到顶点数组中
int InsertEdge(Edge sEdge);//将边保存到邻接矩阵中
Vex GetVex(int nVex);//查询指定顶点信息
int FindEdge(int nVex, Edge aEdge[]);//查询与指定顶点相连的边
int GetVexnum(void);//获取当前顶点数
void DFS(int nVex, bool bVistted[], int &nIndex, Path &pList);//深度优先遍历
//使用深度优先搜索算法遍历图
void DFSTraverse(int nVex, Path &pList);//调用DFS，得到深度优先搜索遍历结果
int FindShortPath(int nVecStar,int nVexEnd,Edge aPath[]);
int FindMinTree(Edge aPath[]);//通过Prim算法构建最小生成树
