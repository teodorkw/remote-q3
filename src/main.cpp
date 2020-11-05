
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

#include "sender.h"

using namespace std;



//void sendCommand(HWND hwnd, const std::string &cm)
//{
//	
//	for( int i = 0; i < cm.size(); ++i )
//	{
//		SendMessageA(hwnd, WM_CHAR, cm[ i ], 1);		// SendInput?
//			//cout << GetLastError() << endl;					// 1400 Invalid window handle. po zamknieciu okna
//		Sleep(10);
//	}
//	//if( !PostMessageA(hwnd, WM_KEYDOWN, VK_RETURN, 1) )		// Post..., Send
//	//	cout << GetLastError() << endl;
//	//if( !PostMessageA(hwnd, WM_KEYUP, VK_RETURN, 1) )
//	//	cout << GetLastError() << endl;
//
//	SendMessageA(hwnd, WM_CHAR, 13, 1);
//
//	
//}




	

int main(int argc, char **argv)
{
	Sender sender;
	sender.parse(argc, argv);
	if( !sender.getHandle() )
		return 1;
	sender.proceed();
	
	return 0;


	/*if( argc < 3 )
	{
		cout << "Pass name of window and file with commands\n";
		return 1;
	}

	char *name = argv[ 1 ];
	char *commandFile = argv[ 2 ];

	HWND hwnd = FindWindowA(NULL, name);
	if( hwnd == 0 )
	{
		cout << "Cannot get window handle\n";
		return 1;
	}
	cout << hwnd << endl;
	SetFocus(hwnd);
	
	if( argc > 4 )	// zeby dostac uchwyt do okna z konsola
	{
		POINT p;
		p.x = stoi(argv[3]);
		p.y = stoi(argv[4]);
		//hwnd = ChildWindowFromPoint(hwnd, p);
		HWND oldHwnd;
		do
		{
			oldHwnd = hwnd;
			hwnd = ChildWindowFromPoint(oldHwnd, p);
			cout << hwnd << endl;
			p.x = 1;		// podawane tylko wzgledem glownego okna
			p.y = 1;
		}while( hwnd && hwnd != oldHwnd );
		hwnd = oldHwnd;
	}

	if( hwnd == 0 )
	{
		cout << "Cannot get child window handle\n";
		return 1;
	}
	
	fstream fs;
	string line;

	while( 1 )
	{
		fs.open(commandFile, ios::in);
		if( !fs.is_open() )
		{
			cout << "Cannot open " << commandFile << "\n";
			system("pause");
			return 1;
		}
		while(getline(fs, line) )
			sendCommand(hwnd, line);
		fs.close();
		fs.open(commandFile, ios::out | ios::trunc);		// php czysci plik
		fs.close();

		Sleep(10);
	}
	system("pause");
	return 0;*/

}
