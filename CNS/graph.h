
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
	int num;//������
	string name; //��������
	string introduction;//�������
	int rank;//����ȼ���
	int price;//��Ʊ�۸�
	int degree;//����ӵ�³̶ȣ���
};
struct Path
{
	double dis;//����
	int pathtype;// 0Ϊ���е���1Ϊ���е���2Ϊ����
	float state;//��·ӵ��״��,0Ϊ������1Ϊ����
};
struct Map
{
	int n;//������
	int m;//����
	Spot S[40]; //������Ϣ
	Path P[40][40]; //·����Ϣ
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
	double dis[40][40];//��������·���������
	int middle[40][40];//����֮����м�ڵ�
	int path[40];//�����������·��
	int pathindex;
	int result[40];
	double dist;
	double dist1;
	//������
	Map BusG;//������ͼ
	Map SubG;//������ͼ
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
	string result1;//��Ž���ַ���
};

#endif // GRAPH_H