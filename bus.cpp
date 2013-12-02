#ifndef BUS_CPP
#define BUS_CPP
#include "bus.h"
#include <stdlib.h>

route::route()
{
	route_num=0;
	srand(0u);
	for(int i=0;i<10;i++)
		stops[i]=rand();
}

route::route(unsigned s)
{
	route_num=s;
	srand(s);
	for(int i=0;i<10;i++)
		stops[i]=rand();
}
route route::operator=(const route& a)
{
	this->route_num=a.route_num;
	for(int i=0;i<10;i++)
		this->stops[i]=a.stops[i];
	return *this;
}

bus::bus()
{
	stop=0;
	passengers=0;
	//route deafult constructor is called implicitly
}
bus::bus(unsigned seed)
{
	stop=0;
	passengers=0;
	//explicit use of route non-deafult constructor:
	route* r = new route (seed);
	rt=*r;
	r=0;
}

bus::bus(const bus& a)
{
	this->stop=a.stop;//start this bus at the stop-2
	this->passengers=a.passengers;
	this->rt=a.rt;
}

bus bus::operator=(const bus& a)
{
	this->stop=a.stop;
	this->passengers=a.passengers;
	this->rt=a.rt;
	return *this;
}

unsigned bus::getStop(){return stop;}

unsigned bus::getRoute(){return rt.route_num;}

void bus::addPass(short a){passengers+=a;}

short bus::getPass(){return passengers;}

short bus::getMaxPass(){return fullBus;}

void bus::remPass(short a){passengers-=a;}

void bus::incStop(){stop=(stop+1)%10;}

short depot::check(bus a)
{
	return (a.getPass()-a.getMaxPass())+fullBus;
	//if fullBus is returned, send another bus
	//if 0 is returned, recall this bus
	//otherwise good
}
bus depot::send(bus a)
{
	bus *b = new bus(a);
	for(int i=0;i<8;i++)
		b->incStop();
	b->addPass(1);
	return *b;
}


#endif