#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void sendCommand(HWND hwnd, const std::string &cm)
{
	//BYTE keys[ 256 ];
	for( int i = 0; i < cm.size(); ++i )
	{
		/*if( cm[i] == '\\')
			PostMessage(hwnd, WM_KEYDOWN, VK_OEM_102, 1);
		else if( cm[ i ] == '_' )
		{
			//PostMessage(hwnd, WM_KEYDOWN, VK_LSHIFT, 1);
			
			//GetKeyboardState(keys);
			//cout << +keys[ VK_LSHIFT ] << "\n";
			//keys[ VK_LSHIFT ] =255;
			////cout << sizeof(keys[ VK_LSHIFT ]) << "\n";
			//SetKeyboardState(keys);
			//cout << +keys[ VK_LSHIFT ] << "\n";
			PostMessage(hwnd, WM_CHAR, '_', 1);		// jeszcze trzeba shifta
		}
		else
			PostMessage(hwnd, WM_KEYDOWN, toupper(cm[i]), 1);*/
		SendMessage(hwnd, WM_CHAR, cm[ i ], 1);
		Sleep(10);
	}
	PostMessage(hwnd, WM_KEYDOWN, VK_RETURN, 1);
	Sleep(10);
}

int main(int argc, char *argv[])
{
	/*DWORD dwPID;
	GetWindowThreadProcessId(hwnd, &dwPID);
	cout << "PID: " << dwPID << "\n";
	DWORD hThread = GetWindowThreadProcessId(hwnd, &dwPID);
	cout << "TID: " << hThread << "\n";*/


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

	fstream fs;
	string line;

	while( 1 )
	{
		fs.open(commandFile, ios::in);
		if( !fs.is_open() )
		{
			cout << "Cannot open " << commandFile << "\n";		// ciekawe jak bedzie z dostepem do pliku
			system("pause");
			return 1;
		}
		while(getline(fs, line) )
			sendCommand(hwnd, line);
		fs.close();
		fs.open(commandFile, ios::out | ios::trunc);
		fs.close();

		Sleep(10);
	}
	system("pause");
	return 0;

}