#pragma once
//Tourism为景点旅游信息管理功能，用于实现系统的主要功能

void CreateGraph(void);//读取文件，创建景区景点图
void GetSpotInfo(void);//查询指定景点信息，显示到相邻景点的距离
void TravelPath(void);//通过调用DFSTraverse()函数，实现旅游景点导航功能，将查询到的景点导航路线显示在界面上。
void FindShortPath(void);//通过调用Graph的FindShortPath（）函数查询两个景点之间的最短路径和距离。
void DesignPath(void);//通过调用Graph的FindMinTree（）函数查询铺设电路规划图。