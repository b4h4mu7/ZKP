#include <QCoreApplication>
#include <QTimer>
#include <iostream>
#include "ExampleProtocol.h"

int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		std::cerr<<"Usage: "<<argv[0]<<" <number of rounds>"<<std::endl;
		return 1;
	}
	QCoreApplication a(argc,argv);
	try
	{
		const int numberOfRounds=std::atoi(argv[1]);
		if(numberOfRounds<=0)
		{
			throw std::logic_error("Number of rounds needs to be larger than 0");
		}
		ZKP::Example::Protocol*const o=new ZKP::Example::Protocol(numberOfRounds,&a);
		QObject::connect(o,SIGNAL(finished()),&a,SLOT(quit()));
		QTimer::singleShot(0,o,SLOT(run()));
		return a.exec();
	}
	catch(std::exception& e)
	{
		std::cerr<<e.what()<<std::endl;
		return 1;
	}
}
