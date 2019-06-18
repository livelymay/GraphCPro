#include<iostream>
#include<locale>
#include"Graph.h"



using namespace std;

struct Vex m_vex;        //重复定义问题
struct Edge m_edge;
struct Graph m_Graph;
struct Path pList;



//初始化图结构
void Inint(){
	m_Graph.m_nVexNum = 0; //初始化顶点个数
	//邻接矩阵初始化
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			//初始化顶点之间的距离为0
			m_Graph.m_aAdjMatrix[i][j] = 0;
		}
	}
}

//将顶点添加到顶点数组中
int InsertVex(Vex sVex) {
	if (m_Graph.m_nVexNum == 20) {
		return false;
	}
	m_Graph.m_aVexs[m_Graph.m_nVexNum++] = sVex;//插入顶点信息
	return true;
}

//将边保存到邻接矩阵中
int InsertEdge(Edge sEdge) {
	if (sEdge.vex1 < 0 || sEdge.vex1>20 || sEdge.vex2 < 0 || sEdge.vex2>20) {
		return false;
	}
	m_Graph.m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	m_Graph.m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
	return true;
}


//查询指定顶点信息
Vex GetVex(int nVex) {
		return m_Graph.m_aVexs[nVex];
}



//查询与指定顶点相连的边
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




//获取当前顶点数
int GetVexnum(void){

	return m_Graph.m_nVexNum;
}

// 使用深度优先搜索算法遍历图
int cnt = 0;
void DFS(int nVex, bool bVisited[], int &nIndex, Path &pList) {
	
	int n = GetVexnum();
	bVisited[nVex] = true;//已访问
	pList.vexs[nIndex++] = nVex;  //访问顶点nVex
	if(nIndex==n){        //输出路径
		cout << "路线" << ++cnt << ":";
		for (int i = 0; i < n; i++) {
		
			cout << GetVex(pList.vexs[i]).name;
			if (i<GetVexnum()-1) {
				cout <<"—>";
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

//调用DFS，得到深度优先搜索遍历结果
void DFSTraverse(int nVex, Path &pList) {
	int nIndex = 0;
	bool bVisited[20] = { false };
	DFS(nVex,bVisited,nIndex,pList);
}

//输入：起始景点编号和目的景点编号
//输出:最短路径
int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[]) {
	bool fin[20];		//已获得最短路径
	int dist[20];		//从nVexStart到当前点的最短距离
	int prev[20];		//存储上一个点
									//初始化数据
	for (int i = 0; i <m_Graph.m_nVexNum; i++)
	{
		fin[i] = false;
		if (m_Graph.m_aAdjMatrix[nVexStart][i] != 0)
			dist[i] = m_Graph.m_aAdjMatrix[nVexStart][i];
		else
			dist[i] = INT_MAX;	//将没有路径的点设权重为无穷
		if (dist[i] == INT_MAX)
			prev[i] = -1;
		else
			prev[i] = nVexStart;//已有路径设置上一个点为nVexStart
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
				v = i;			//获取未获得最短路径的最小值点
				min = dist[i];	//获取未获得最短路径的最小值
			}
		}
		fin[v] = true;
		for (int i = 0; i < m_Graph.m_nVexNum; ++i)
			if ((!fin[i]) && (dist[v] + m_Graph.m_aAdjMatrix[v][i] < dist[i]) && (m_Graph.m_aAdjMatrix[v][i] != 0))
			{
				dist[i] = dist[v] + m_Graph.m_aAdjMatrix[v][i];	//更新最短路径
				prev[i] = v;							//存储上一个点
			}
	}
	int num = 0, last = nVexEnd;
	//记录路径中的边数
	while (prev[last] != nVexStart)
	{
		num++;
		last = prev[last];
	}
	last = nVexEnd;
	//保存路径信息
	while (num >= 0)
	{
		aPath[num].vex2 = last;
		aPath[num].vex1 = prev[last];
		aPath[num].weight = m_Graph.m_aAdjMatrix[last][prev[last]];
		last = prev[last];
		num--;
	}
	return dist[nVexEnd];		//返回最短路径距离
}


int FindMinTree(Edge aPath[]) {

	int lowcost[20] = { 0 };	//最短距离
	bool addVexNew[20] = { true };//已获得最短距离的点
	int prev[20] = { 0 };		//之前点
	int length = 0;
	//初始化数组并默认起始顶点为0点
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
			//保存路径信息
			aPath[p].vex1 = prev[v];
			aPath[p].vex2 = v;
			aPath[p].weight = lowcost[v];
			addVexNew[v] = true;                                      //将v加Vnew中
			length += lowcost[v];                             //计算路径长度之和
			for (int i = 0; i<m_Graph.m_nVexNum; i++)
			{
				if ((!addVexNew[i]) && (m_Graph.m_aAdjMatrix[v][i]<lowcost[i]) && (m_Graph.m_aAdjMatrix[i][v] != 0))
				{
					lowcost[i] = m_Graph.m_aAdjMatrix[v][i];                     //此时v点加入Vnew 需要更新lowcost
					prev[i] = v;										//存储上一个点
				}
			}
		}
	}
	return length;
}