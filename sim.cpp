#ifndef SIM_CPP
#define SIM_CPP
#include "sim.h"

short simulator::xadd(unsigned x)
{
	x_i++;
	srand(x_i*4369);
	if(x%4<2)
		return (rand()+rand())%8;

	return (rand()+rand())%4;
}

short simulator::xrem(unsigned x)
{
	x_i++;
	srand(x_i*4369);
	if(x%4>2)
		return (rand()+rand())%12;

	return (rand()+rand())%4;
}

void simulator::start()
{
	busses.clear();
	bus* newBus;
	for(int i=1;i<6;i++)
	{
		newBus = new bus(i);
		busses.push_back(*newBus);
		delete newBus;
	}
}
void simulator::tick(unsigned i)
{
	//there are 5 routes [1,5]
	std::stack<bus> stk;
	bus temp,temp2;
	short a,b,c;

	for(int j=1;j<6;j++)
	{
		srand(unsigned(time(0u)));
		for(int k=0;k<busses.size();k++)
		{
			if(busses[k].getRoute()==j)
			{
				stk.push(busses[k]);
				busses.erase(busses.begin()+k);
				k--;
			}
		}
		//stk now contains all busses on one route (last bus deployed, at top)
		b=stk.size();
		c=0;
		temp2=stk.top();

		while(!stk.empty())
		{

			temp=stk.top();stk.pop();
			temp.incStop();

			temp.remPass(xrem(i));

			if(depot::check(temp)<fullBus)
				temp.addPass(xadd(i));

			if(depot::check(temp)<=0)
			{
				a=temp.getPass();//correct for negative passengers
				temp.addPass(-a);
				if(b!=1)
					b--;//if there is only 1 bus left on the route, do nothing
				else
					busses.push_back(temp);
			}
			else if(depot::check(temp)>=fullBus)
			{
				c++;//hehe
				temp.remPass(5);
				busses.push_back(temp);
			}
			else
				busses.push_back(temp);
		}
		if(c==b || (c==b-1 && b>1))
			busses.push_back(depot::send(temp2));//send another bus only if all are full
	}
}	


void sim_out::view(simulator sim,std::ostream& os)
{
	//output pretty pictures
	os<<"|"<<std::setw(8)<<"Bus #"<<"|"<<std::setw(8)<<"Route"<<"|"<<std::setw(8)<<"Stop #"<<"|"<<std::setw(10)<<"# of pass"<<"|\n";
	std::stack<bus> stk;
	int i=0;
	bus temp;

	for(int j=1;j<6;j++)
	{
		
		for(unsigned k=0;k<sim.busses.size();k++)
		{
			if(sim.busses[k].getRoute()==j)
			{
				stk.push(sim.busses[k]);
			}
		}
		while(!stk.empty())
		{
			i++;
			temp=stk.top();stk.pop();
			os<<"|"<<std::setw(8)<<i<<"|";
			os<<std::setw(8)<<temp.getRoute()<<"|";
			os<<std::setw(8)<<temp.getStop()<<"|";
			os<<std::setw(10)<<temp.getPass()<<"|\n";
		}
	}
}



#endif