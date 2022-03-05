#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CNS.h"
#include "graph.h"
#ifdef WIN32  
#pragma execution_character_set("utf-8")
#endif
class CNS : public QMainWindow
{
    Q_OBJECT

public:
    CNS(QWidget *parent = Q_NULLPTR);
private slots:
	void on_exit_clicked();
	void on_SearchShortestPath_clicked();
	void on_SearchSpotInfo_clicked();
	void on_pathplanning_clicked();
signals:
	void quit();

private:
    Ui::CNSClass ui;
	Graph graph;
};
