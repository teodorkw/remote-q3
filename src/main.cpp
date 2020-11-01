#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;



void sendCommand(HWND hwnd, const std::string &cm)
{
	
	for( int i = 0; i < cm.size(); ++i )
	{
		SendMessage(hwnd, WM_CHAR, cm[ i ], 1);
		Sleep(10);
	}
	PostMessage(hwnd, WM_KEYDOWN, VK_RETURN, 1);
	Sleep(10);
}
	

int main(int argc, char *argv[])
{
	if( argc < 3 )
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
	
	if( argc > 4 )	// zeby dostac uchwyt do okna z konsola
	{
		POINT p;
		p.x = stoi(argv[3]);
		p.y = stoi(argv[4]);
		hwnd = ChildWindowFromPoint(hwnd, p);
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
	return 0;

}
