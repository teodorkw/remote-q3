#include "sender.h"

using namespace std;


int main(int argc, char **argv)
{
	Sender sender;
	if( !sender.parse(argc, argv) )
		return 1;
	if( !sender.getHandle() )
		return 1;
	sender.proceed();
	
	return 0;
}
