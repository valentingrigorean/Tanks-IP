#include "error.h"

void fatalError(const char * msg)
{	
	std::cerr << "Error in " << __FILE__ << " line " << __LINE__ << ": " << msg << std::endl;
	std::terminate();	
}
