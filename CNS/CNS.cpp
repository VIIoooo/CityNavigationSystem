#if _MSC_VER >=1600
#pragma execution_character_set("utf-8")
#endif
#include "CNS.h"
#include "graph.h"
#include <QDebug>
#include <QTextStream>
#include <string>
CNS::CNS(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}


void CNS::on_SearchShortestPath_clicked()
{
	graph.Creat_Spot();
	graph.Creat_maps();
	int start, end, type;
	start = ui.pathstart->currentIndex();
	end = ui.pathend->currentIndex();
	type = ui.pathtype->currentIndex();
	string s;
	switch(type)
	{
	case 1:
		s = graph.ShortestPathTwo(start, end);
		ui.output->setText(QString::fromStdString(s));
		break;
	case 2:
		s = graph.ShortestTimePath(start, end);
		ui.output->setText(QString::fromStdString(s));
		break;
	case 3:
		s = graph.BestPersonWay(start, end);
		ui.output->setText(QString::fromStdString(s));
		break;
	case 4:
		s = graph.BestCarWay(start, end);
		ui.output->setText(QString::fromStdString(s));
		break;
	case 5:
		s = graph.BestSpots(start, end);
		ui.output->setText(QString::fromStdString(s));
		break;
	case 6:
		s = graph.Cheapest(start, end);
		ui.output->setText(QString::fromStdString(s));
		break;
	default:
		break;
	}
}

void CNS::on_SearchSpotInfo_clicked()
{
	graph.Creat_Spot();
	graph.Creat_maps();
	int index;
	index = ui.Spotname->currentIndex();
	string s = graph.Inquire_SpotInfo1(index);
	ui.output->setText(QString::fromStdString(s));
}

void CNS::on_pathplanning_clicked()
{
	graph.Creat_Spot();
	graph.Creat_maps();
	QString input = ui.Spotinput->text();
	QStringList input1 = input.split(" ");
	int visit[40];
	int num = input1[0].toInt();
	for (int i = 1; i < input1.length(); i++)
	{
		visit[i-1] = input1[i].toInt();
	}
	string r = graph.BestPath(num, visit);
	ui.output->setText(QString::fromStdString(r));
}
void CNS::on_exit_clicked()
{
	emit quit();
}
