#if _MSC_VER >=1600
#pragma execution_character_set("utf-8")
#endif
#include "CNS.h"
#include <QtWidgets/QApplication>
#include <QTextStream>
#include <QDebug>
#include <QTextCodec>

int main(int argc, char *argv[])
{
	if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
		QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    CNS w;
    w.show();
	QObject::connect(&w, SIGNAL(quit()), &a, SLOT(quit()));
    return a.exec();
}



