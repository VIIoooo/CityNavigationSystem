
#ifndef GRAPH_H
#define GRAPH_H
#pragma once
#include<iostream>
#include <string>
#if _MSC_VER >=1600
#pragma execution_character_set("utf-8")
#endif
using namespace std;
struct Spot
{
	int num;//景点编号
	string name; //景点名称
	string introduction;//景点介绍
	int rank;//景点等级；
	int price;//门票价格
	int degree;//景点拥堵程度，度
};
struct Path
{
	double dis;//距离
	int pathtype;// 0为人行道，1为车行道，2为都可
	float state;//道路拥堵状况,0为正常，1为堵塞
};
struct Map
{
	int n;//顶点数
	int m;//边数
	Spot S[40]; //景点信息
	Path P[40][40]; //路径信息
};
#define MAX 100000

class Graph {
private:
	void FloydSpath(int Spath[40][40], int begin, int end);
	string Floydd(int Matrix[40][40], int begin, int end);
	void Floyd(Map G);
	void FloydPath(Map G, int start, int end);
	void swap(int *a, int index1, int index2);
	void BackTracking(int visitSpot[40], int num, int index);
public:
	Graph();
	~Graph();
	Map G;
	double dis[40][40];//两点间最短路径距离矩阵
	int middle[40][40];//两点之间的中间节点
	int path[40];//包含多点的最短路径
	int pathindex;
	int result[40];
	double dist;
	double dist1;
	//第五题
	Map BusG;//公交地图
	Map SubG;//地铁地图
	Map BikeG;
	Map TaxiG;
	void Creat_Spot();
	void Creat_maps();
	string Inquire_SpotInfo1(int x);
	string ShortestPathTwo(int start, int end);
	string BestPersonWay(int start, int end);
	string BestCarWay(int start, int end);
	string Cheapest(int start, int end);
	string BestSpots(int start, int end);
	string ShortestTimePath(int begin, int end);
	string BestPath(int num, int visit[40]);
	string result1;//存放结果字符串
};

#endif // GRAPH_H