#pragma once

#include <windows.h>
#include <string>
#include <algorithm>
#include <vector>

class Sender
{
	std::string windowName, commandFileName;
	HWND hwnd;

	std::vector<std::string> params;

	bool sendEnterAsChar;
	bool sendToChild;
	int x, y;
public:
	Sender() : sendEnterAsChar(false)
	{}
	void parse(int argc, char **argv)
	{
		params.resize(argc - 1);
		transform(argv + 1, argv + argc, params.begin(),
			[](char *x)->std::string
		{
			return x;
		});

		sendEnterAsChar = findSwitch("-a");

		std::string coords;
		if( sendToChild = findOption("-c", coords) )
		{
			size_t comma = coords.find(',');
			if( comma == std::string::npos )		// basic control of parameter corectness
			{
				std::cerr << "Warning: -c option ignored - pass coordinates as <x>,<y>\n";
				sendToChild = false;
			}
			else
			{
				x = stoi(coords.substr(0, comma));
				y = stoi(coords.substr(comma + 1));
			}
		}

		windowName = params[ 0 ];
		commandFileName = params[ 1 ];
		
	}

	bool findSwitch(std::string s)
	{
		auto it = std::find(params.begin(), params.end(), s);
		if( it == params.end() )
			return false;
		params.erase(it);
		return true;
	}

	bool findOption(std::string o, std::string &res)
	{
		res = "";
		auto it = std::find(params.begin(), params.end(), o);
		if( it == params.end() || it == params.end() - 1 )
			return false;
		res = *( it + 1 );
		params.erase(it, it + 2);
		return true;
	}

	bool getHandle()
	{
		hwnd = FindWindowA(NULL, windowName.c_str());
		if( hwnd == 0 )
		{
			std::cerr << "Cannot get window handle\n";
			return false;
		}
		std::cout << "Main window handle: " << hwnd << std::endl;
		if( !sendToChild )		// just main window
			return true;	

		// child:
		POINT p;
		p.x = x;
		p.y = y;
		HWND oldHwnd, newHwnd;
		oldHwnd = hwnd;
		do
		{
			newHwnd = ChildWindowFromPoint(oldHwnd, p);
			//std::cout << newHwnd << std::endl;
			if( newHwnd == NULL )
				break;
			if( newHwnd == oldHwnd )
				break;
			oldHwnd = newHwnd;

			//oldHwnd = newHwnd;
			//newHwnd = ChildWindowFromPoint(oldHwnd, p);
			
			p.x = 0;		// reset
			p.y = 0;
		}
		while( 1 );
		if( hwnd == oldHwnd )
			std::cerr << "Warning: no child window detected - using main window instead\n";
		hwnd = oldHwnd;

		std::cout << "Child window handle: " << hwnd << std::endl;

		return true;
	}

	bool proceed()
	{
		std::fstream fs;
		std::string line;

		while( 1 )
		{
			fs.open(commandFileName, std::ios::in);
			if( !fs.is_open() )
			{
				std::cerr << "Cannot open " << commandFileName << "\n";
				return false;
			}
			while( getline(fs, line) )
				sendCommand(line);
			fs.close();
			fs.open(commandFileName, std::ios::out | std::ios::trunc);		// web app empties file anyway
			fs.close();

			Sleep(10);
		}
		return true;
	}

	void sendCommand(const std::string &cm)
	{
		for( int i = 0; i < cm.size(); ++i )
		{
			SendMessageA(hwnd, WM_CHAR, cm[ i ], 1);		// SendInput?
															//cout << GetLastError() << endl;					// 1400 Invalid window handle. po zamknieciu okna
			Sleep(10);
		}
		//if( !PostMessageA(hwnd, WM_KEYDOWN, VK_RETURN, 1) )		// Post..., Send
		//	cout << GetLastError() << endl;
		//if( !PostMessageA(hwnd, WM_KEYUP, VK_RETURN, 1) )
		//	cout << GetLastError() << endl;

		if(sendEnterAsChar)
			SendMessageA(hwnd, WM_CHAR, 13, 1);
		else
		{
			if( !PostMessageA(hwnd, WM_KEYDOWN, VK_RETURN, 1) )	
				std::cout << GetLastError() << std::endl;
			if( !PostMessageA(hwnd, WM_KEYUP, VK_RETURN, 1) )
				std::cout << GetLastError() << std::endl;
		}


	}
};