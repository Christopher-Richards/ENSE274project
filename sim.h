#ifndef SIM_H
#define SIM_H
#include "bus.h"
#include <vector>
#include <stack>
#include <iostream>
#include <iomanip>

struct simulator
{
	std::vector<bus> busses;
	void tick(unsigned);//processes 1 "clock" of the system
	void start();//starts the system
	simulator(){x_i=0;}
private:
	short x_i;
	short xadd(unsigned);
	short xrem(unsigned);
};

namespace sim_out
{
	void view(simulator,std::ostream&);
}


#endif