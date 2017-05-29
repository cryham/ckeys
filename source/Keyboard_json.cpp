#include "Keyboard.h"
#include "KeyNames.h"
#include <string>
#include <fstream>
#include <sstream>
#include <string.h>
#include "../libs/jsmn.h"
#include "Util.h"
using namespace std;


//  load layout, read json layout from file
//-----------------------------------------------------------------------------------------------------------
bool Keys::LoadJson(string path)
{
	//  open
	ifstream f;
	f.open(path);
	if (!f.is_open())
		return false;

	//#define DBG  // test
	#ifdef DBG
	ofstream of(path + ".log");
	#endif
	stringstream ss;  ss << f.rdbuf();
	string str = ss.str();
	const char* s = str.c_str();

	//  jsmn json vars
	int i,r;
	jsmn_parser p;
	jsmntok_t t[512];  // const max
	jsmn_init(&p);

	//  parse
	string q;  //, re;
	r = jsmn_parse(&p, s, strlen(s), t, sizeof(t)/sizeof(t[0]));
	if (r < 0)
		return false;
	//	re += "Failed to parse JSON: " + r;

	//  layout
	int x=0, y=0;
	float w=1.f, h=1.f;  string prim;

	//  params
	const float sc = 1.3f;
	const int  sx = 40 * sc, sy = sx, se = 5,  // size x,y, empty margin
			 yfnt = 14 * sc, x0 = 0, y0 = 0;  // font, start pos

	//  iterate all
	//-----------------------------------------------------------
	for (i = 1; i < r; i++)
	{
		if (t[i].type == JSMN_ARRAY)
		{   x = 0;  y += sy;  w = 1.f;  h = 1.f;  // next row
		}
		else
		if (t[i].type == JSMN_STRING)
		{
			//  key text
			string s = str.substr(t[i].start, t[i].end - t[i].start);
			if (s[0]>='a' && s[0]<='z')
				prim = s;
			else
			{
				///****  replace
				bool ext = false;
				bool has2 = replK(s, "\\n", "\n");  // key has 2 descr: upper, lower
				replK(s, "\\\\", "\\");
				string ss = s;  // copy org nameg for vk map
				replK(s, "Lock", "");  // rem Lock
				replK(s, "\\\"", "\"");
				//replK(s, "Space", " ");
				replK(s, "Delete", "Del");
				replK(s, "L_", "");  replK(s, "R_", "");  // left, right modifiers
				if (replK(s, "N_", ""))  ext = true;  // numpad

				sf::String ws(s);  // arrow symbols
				if (found(s, "Left"))   ws = L"←";  if (found(s, "Right"))  ws = L"→";
				if (found(s, "Down"))   ws = L"↓";
				if (!found(s, "PgUp") && found(s, "Up"))  ws = L"↑";
				if (found(s, "CLEAR"))   ws = "5";
				///****

				//  font scale
				float sf = w < 0.7f ? 0.6f/*ck4 mini*/ : 0.8f;
				//float sf = k2 ? 0.8f :
				//    k.length() > 1 ? 0.7f : 1.f;


				//  setup key  ----
				Key k;  k.x = x0 + x;  k.y = y0 + y;
				k.w = sx * w - se;  k.h = sy * h - se;
				k.sc = sf * yfnt;
				k.s = ws;

				x += w * sx;  // add x
				w = 1.f;  h = 1.f;  // reset


				//  vk to key  ------
				if (has2)
				{	size_t p = ss.find("\n");

					if (!found(ss, "N_"))  // digits, symbols
						ss = ss.substr(p+1);  // second part
					else  // numpad
						ss = ss.substr(0, p);  // first part
				}
				int vk = str2vk[ss];
				#ifdef DBG
				of << hex << vk << "  " << ss << endl;
				#endif
				if (vk)  // if found
				{
					int kk = keys.size()+1;
					if (ext)  kk += vk_EXTRA;  // numpad
					vk2key[vk] = kk;
				}


				///****  str to key
				string sk = ss;  // todo? cfg file..
				replK(sk, "L_", "L");  replK(sk, "R_", "R");  // left, right mod
				replK(sk, "N_", "P");  // numpad
				replK(sk, "PgUp", "PageUp");  replK(sk, "PgDn", "PageDown");
				replK(sk, "Win", "Gui");  replK(sk, "Menu", "App");
				replK(sk, "PrtSc", "PrintScreen");
				replK(sk, "`", "BackTick");  //replK(sk, " Lock", "Lock");
				///****

				str2key[sk] = keys.size()+1;
				k.sk = sk;  // test


				keys.push_back(k);  // add key
		}   }
		else
		if (t[i].type == JSMN_PRIMITIVE)
		{
			string p = str.substr(t[i].start, t[i].end - t[i].start);
			if (p[0]>='a' && p[0]<='z')
				prim = p;
			else
			{   float f = 0.f;
				sscanf(p.c_str(), "%f", &f);

				if (prim == "x")  x += f * sx;
				else
				if (prim == "y")  y += f * sy;
				else
				if (prim == "w")  w = f;
				else
				if (prim == "h")  h = f;
			}
		}
	}
	return true;
}
