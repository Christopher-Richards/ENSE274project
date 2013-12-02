#include "sim.h"

int main()
{
	unsigned i=0;
	simulator sim;
	sim.start();
	sim_out::view(sim,std::cout);
	while(1)
	{
		system("pause");
		sim.tick(i);
		sim_out::view(sim,std::cout);
		i++;
	}
	return 0;
}