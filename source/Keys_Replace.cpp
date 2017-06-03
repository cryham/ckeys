#include "Keys.h"
#include "Util.h"
#include <string>
using namespace std;


//  shorten kll names
sf::String Keys::ReplaceKll(const string& name)
{
	string s = name;
	replK(s, "Protocol", "");  replK(s, "Lock", "");  replK(s, "()", "");
	replK(s, "MUTE", "Mute");  replK(s, "CALCULATOR", "Calc");
	replK(s, "VOLUMEUP", "Vol+");  replK(s, "VOLUMEDOWN", "Vol-");
	replK(s, "STOP", "[]");  replK(s, "PAUSEPLAY", "||");  replK(s, "PLAY", "|>");
	replK(s, "SCANPREVIOUSTRACK", "|<");  replK(s, "SCANNEXTTRACK", ">|");

	//  seq
	bool b = replK(s, "s(", "s");  if (b)  s = s.substr(0,s.length()-1);
	if (s.length() == 3 && s[0]=='\'' && s[2]=='\'')  s = s[1];  // '('

	//  mouse
	bool m = replK(s, "mouseOut(", "M");
	sf::String ws(s);
	if (m)
	{
		char x=0, y=0, b=0;
		sscanf(s.c_str(), "M%d,%d,%d", &b,&x,&y);
		if (x < 0)  ws = L"M←";  else  if (x > 0)  ws = L"M→";  else
		if (y < 0)  ws = L"M↑";  else  if (y > 0)  ws = L"M↓";  else
		if (b > 0)  ws = "M" + i2s(b);
	}
	ReplacePlayer(s,ws);
	return ws;
}

//  replace json name
sf::String Keys::ReplaceJson(string& s, string& sVK, string& sk, bool& ext, bool& has2)
{
	ext = false;
	has2 = replK(s, "\\n", "\n");  // key has 2 descr: upper, lower
	replK(s, "\\\\", "\\");
	sVK = s;  // copy for vk map

	replK(s, "Lock", "");  // rem Lock
	replK(s, "\\\"", "\"");
	replK(s, "Space", " ");
	replK(s, "Delete", "Del");
	replK(s, "L_", "");  replK(s, "R_", "");  // left, right modifiers
	if (replK(s, "N_", ""))  ext = true;  // numpad

	sf::String ws(s);  // arrow symbols
	if (found(s, "Left"))   ws = L"←";  if (found(s, "Right"))  ws = L"→";
	if (found(s, "Down"))   ws = L"↓";
	if (!found(s, "PgUp") && found(s, "Up"))  ws = L"↑";
	if (found(s, "CLEAR"))   ws = "5";
	if (s=="Display")   ws = L"❏";  //▤❏◾

	//  vk to key  ------
	if (has2)
	{	size_t p = sVK.find("\n");

		if (!found(sVK, "N_"))  // digits, symbols
			sVK = sVK.substr(p+1);  // second part
		else  // numpad
			sVK = sVK.substr(0, p);  // first part
	}
	//  str to key
	sk = sVK;
	replK(sk, "L_", "L");  replK(sk, "R_", "R");  // left, right mod
	replK(sk, "N_", "P");  // numpad
	replK(sk, "PgUp", "PageUp");  replK(sk, "PgDn", "PageDown");
	replK(sk, "Win", "Gui");  replK(sk, "Menu", "App");
	replK(sk, "PrtSc", "PrintScreen");
	replK(sk, "`", "BackTick");  //replK(sk, " Lock", "Lock");

	return ws;
}


//  set clr from name
void Key::SetClr()
{
	if (sJson=="L2")  clr = KC_Layer2;  else
	if (sJson=="L3")  clr = KC_Layer3;  else
	if (sJson=="Display")  clr = KC_Display;
	else  clr = KC_Normal;
}

//  apply player symbols
void Keys::ReplacePlayer(const string& s, sf::String& ws)
{
	if (s=="|>")  ws = L"▶";  if (s=="||")  ws = L"▮▮";  if (s=="[]")  ws = L"◼";
	if (s==">|" || s=="M Next")  ws = L"▶▮";  if (s==">>")  ws = L"▶▶";
	if (s=="|<" || s=="M Prev")  ws = L"▮◀";  if (s=="<<")  ws = L"◀◀";
}
