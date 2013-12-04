#ifndef BUS_H
#define BUS_H

//CONSTANTS:
#define fullBus 10

struct route
{
	unsigned route_num;
	unsigned stops [10];
	/*this would be more complex but for now it will just 
	be random values that correspond to some location.
	each route thus has 10 stops*/

	route();
	route(unsigned);
	route operator=(const route&);
};


class bus
{
	unsigned stop;//index for route
	short passengers;
	route rt;

public:
	bus();
	bus(unsigned);
	bus(const bus&);
	bus operator=(const bus&);
	unsigned getStop();
	unsigned getRoute();
	void addPass(short);
	short getPass();
	short getMaxPass();
	void remPass(short);//it is the simulators job to ensure param<num passengers+1

//the following functions are for the simulator
	void incStop();

};

namespace depot
{
	short check(bus);//return value details action to be taken
	bus send(bus);

};

#endif