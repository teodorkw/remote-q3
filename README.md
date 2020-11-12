# Remote-q3

Remote-q3 is designed for sending commands to game servers remotely. The whole flow consists of web application and `send-keystroke.exe`. After set-up one can manage server from the web browser.

It is designed exclusively for Windows.

## 1. Installation

One needs a local web server which runs `index.php` from `www` folder of this repository. The `p` variable inside this file must be adjusted to point at command file, which is also used by `send-keystroke`.

`send-keystroke` can be built with Visual Studio solution or by invoking command from `build` file on Linux.

## 2. Usage

`send-keystroke <window_name> <command_file> [-a] [-c <x>,<y>] [-s <delay>]`

Parameters:

* `window_name` - name of window to which commands are sent.
* `command_file` - file from which commands are read.
* `-a` - enter is sent as WM_CHAR instead of WM_KEYDOWN and WM_KEYUP (proper way must be proven experimentally).
* `-c <x>,<y>` - coordinates of child window according to upper left corner of the main window's client area. Use if main window has distinct child window for taking commands. Program searches for the top window in that location.
* `-s <delay>` - time delay between each character in command in milliseconds. Default is 100.

## 3. Tested games

### 3.1 Quake III Arena

#### Regular dedicated server (`quake3.exe`)

`send-keystroke "Quake 3 Console" commands.txt -c 50,405`

#### ioquake3 port (`ioq3ded.x86.exe`)

`send-keystroke "ioquake3 Dedicated Server Console" commands.txt`

#### ioquake3 port (`ioquake3.x86.exe`)

Currently `send-keystroke` is not able to efficiently send commands to such window, although [Spy++](https://docs.microsoft.com/en-gb/visualstudio/debugger/introducing-spy-increment?view=vs-2019) shows that window receives sent ones.

### 3.2 Unreal Tournament

#### Dedicated server (`UnrealTournament.exe`)

`send-keystroke "Depot: DM-depot.unr (0 players)" commands.txt -a -c 50,50`

## 4. Known issues

* Program doesn't notice window's closing,

* target window must not be minimized during calling `send-keystroke`.
