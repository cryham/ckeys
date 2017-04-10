## Crystal Keys (cKeys)

Program showing pressed keys and keyboard layouts.  
Currently works on Windows, for GNU/Linux it should be easy to port.  
Made as a support program for my keyboards CK3 and CK4 (more on [my website](https://cryham.tuxfamily.org/archives/portfolio/crystal-keyboard-3-and-4)).  

## Layouts

Reads custom keyboard layouts, from json files (using jsmn parser library),  
outputed from this web based editor: www.keyboard-layout-editor.com  
Supports only basic rectangular layouts, no rotation or styling.  
The default.json layout is the ANSI 104 preset (top left combo).  

## General

Uses SFML and ImGui for display and Windows Keyboard Hook to get key states.  
**Earlier versions** in [releases](https://github.com/cryham/ckeys/releases):  
0.1, 0.3 and 0.5 were just demo programs for using [SFML](https://github.com/SFML/SFML), [ImGui](https://github.com/ocornut/imgui) and [TinyXML-2](https://github.com/leethomason/tinyxml2).  
And can serve as **tutorials or starting projects** for such applications, for both GNU/Linux and Windows.  

## Compiling

Using [CMake](https://cmake.org/), it should be possible to build easily.  
I'm using Qt Creator IDE, which supports it.  

On GNU/Linux you'll need to get SFML installed. At least version 2.2.  
E.g. for Ubuntu (and Debian-based):  
`sudo apt-get install libsfml-dev`  

On Windows SFML needs the environment variable SFML_ROOT to be defined.  
After this the program should build.  

In sources there already are: [TinyXML2](https://github.com/leethomason/tinyxml2), ImGui with ImGui-SFML and [Native File Dialog](https://github.com/mlabbe/nativefiledialog).  

## Screenshot

![](https://raw.githubusercontent.com/cryham/ckeys/master/screenshot.png)
