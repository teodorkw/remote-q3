#include "sender.h"

using namespace std;


int main(int argc, char **argv)
{
	Sender sender;
	sender.parse(argc, argv);
	if( !sender.getHandle() )
		return 1;
	sender.proceed();
	
	return 0;
}
