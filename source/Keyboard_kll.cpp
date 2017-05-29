#include "Keyboard.h"
#include <string>
#include <fstream>
#include <sstream>
#include <string.h>
#include "Util.h"
using namespace std;


// kll syntax:
//   pre"sname": pre"name";  #comment\n
//             ^mid       ^end
// examples:
//   S0x39: U"F1";  S0x78: CONS"STOP";  S0x4E: U"P+";
//   U"A": U"B";  U"1": s(1);  U";": '(';
//   U"V":SYS"SLEEP";  U"Delete": mouseOut(3, 0, 0);
//   S0x6D: U"Alt"+U"Esc";  S0x77:+ shift();


//  kll parser state variables
struct SParser
{
	bool comment, apos, scan, skip;  // flags
	int name0, apos0, scan0, mid0;  // start pos
	string name, sname, sscan, pre;

	SParser()
	{
		Reset();
	}
	void Reset()
	{
		comment = apos = scan = skip = false;
		name0 = apos0 = scan0 = mid0 = 0;
		name = sname = sscan = pre = "";
	}
	void MidReset()
	{
		comment = apos = false;
		name0 = apos0 = scan0 = 0;
		name = "";
	}
};


//  load layer, from kll file
//-----------------------------------------------------------------------------------------------------------
bool Keys::LoadKll(string path, int layer)
{
	//  open
	ifstream f;
	f.open(path);
	if (!f.is_open())
		return false;

//	#define DBG_OUT  // test
	#ifdef DBG_OUT
	ofstream of;
	of.open(path+"o", ofstream::out);
	#endif

	//  read whole file as string s
	string s;
	#define LN 512
	char ln[LN];
	int l=0;
	while (!f.eof())
	{
		f.getline(ln,LN-1);  ++l;
		//  skip first 5 lines
		if (l > 5)
		{
			s += string(ln);
			s += "\n";
		}
	}

	//  parse kll
	//----------------------------------
	int pos=0, len = s.length();
	SParser p;

	//  foreach char in string s
	while (pos++ < len)
	{
		char ch = s[pos];
		//of << ch << "\n";

		//  comment, skip until \n
		if (ch=='#')
		{
			p.comment = true;
		}
		else  //  end of line, reset
		if (ch=='\n')
		{
			p.Reset();
		}
		//  normal  -----------------
		else if (!p.comment)
		{
			//  scan code  S0x..
			if (pos>=2 && ch=='x' && s[pos-1]=='0' && s[pos-2]=='S')
			{
				p.scan0 = pos+1;  p.scan = 1;
			}
			//  outside apos
			else if (p.apos == 0)
			{
				if (ch==':')  // middle of mapping
				{
					//  skip :+
					if (pos+1 < len && s[pos+1]=='+')
						p.skip = 1;
					else
					{
						if (p.scan == 1)
						{
							p.sscan = s.substr(p.scan0, pos - p.scan0);
							//of << "--scan: " << sscan << "\n";
						}else{
							p.sname = p.name;
							//of << "--name: " << p.name << "\n";
						}
						p.mid0 = pos+1;
						//  trim front spaces
						while (s[p.mid0]==' ' && p.mid0 < len)  ++p.mid0;
						p.MidReset();
					}
				}
				else if (ch==';' && !p.skip)  // end of mapping
				{
					int id = -1;
					if (p.scan)
					{
						#ifdef DBG_OUT
						id = str2key[p.name]-1;
						of << "sc: " << p.sscan << "  n: " << p.name << "  id: " << id << "\n";
						#endif
					}else{
						if (p.name.empty())
							p.name = s.substr(p.mid0, pos - p.mid0);
						#ifdef DBG_OUT
						id = str2key[p.sname]-1;
						of << "sn: " << p.sname << "  n: " << p.name << "  id: " << id << "\n";
						#endif
					}
					if (id >= 0)
					{
						Key& k = keys[id];
						k.inKll = true;

						///****  shorten kll names
						string s = p.name;
						replK(s, "Protocol", "");  replK(s, "Lock", "");  replK(s, "()", "");
						replK(s, "MUTE", "Mute");  replK(s, "CALCULATOR", "Calc");
						replK(s, "VOLUMEUP", "V+");  replK(s, "VOLUMEDOWN", "V-");
						replK(s, "STOP", "[]");  replK(s, "PAUSEPLAY", "||");  replK(s, "PLAY", "|>");
						replK(s, "SCANPREVIOUSTRACK", "|<");  replK(s, "SCANNEXTTRACK", ">|");
						//  seq
						bool b = replK(s, "s(", "s");  if (b)  s = s.substr(0,s.length()-1);
						if (s.length() == 3 && s[0]=='\'' && s[2]=='\'')
							s = s[1];
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
						///****

						if (layer==2)
						{
							k.hasL2 = true;
							k.s2 = ws;
						}else
						if (layer==3)
						{
							k.hasL3 = true;
							k.s3 = ws;
						}
					}
					p.Reset();
				}
				else if (ch=='U')
				{
					p.name0 = pos;  p.pre = "U";
				}
			}
			//  apos "name"
			if (ch=='"')
			{
				if (p.apos == 0)  // 1st, start"
				{
					p.apos0 = pos+1;
					p.apos = 1;
				}
				else  // 2nd, end"
				{
					if (!p.name.empty())
						p.sname = p.name;

					if (!p.name.empty())
						p.name += "+";  // add, s[pos+1]=='+';
					p.name += s.substr(p.apos0, pos - p.apos0);

					//of << "name: " << name << "\n";
					p.apos = 0;  //name0 = pos;
				}
			}
		}
	}

	of.close();
	f.close();
	return true;
}
