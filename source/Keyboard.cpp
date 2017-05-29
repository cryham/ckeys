#include "Keyboard.h"
#include "KeyNames.h"
using namespace std;


//  ctor
Keys::Keys()
{
	//  filled vk to str maps from csKeyNames
	for (int k=0; k < 256; ++k)
	{
		string s = csKeyNames[k];
		vk2str[k] = s;
		str2vk[s] = k;
	}
}

//  find data path
//-----------------------------------------------------------
bool Keys::Init()
{
	pathData = "data/";
	files.clear();
	files.push_back("default");  //todo read dir
	files.push_back("ck3");
	files.push_back("ck4");
	return true;
}

void Keys::Destroy()
{
	keys.clear();
	vk2key.clear();
	str2key.clear();
}

//  read layouts from file
void Keys::LoadIndex(int id)
{
	if (id >= files.size())
		return;

	//  clear last
	Destroy();

	//  load json
	string fname = files[id];
	LoadJson(pathData + fname + ".json");

	//  load klls
	//	default map:  scan code to kll name
	LoadKll(pathData + "defaultMap" + fname + ".kll", 1);
	//	layer map:  kll name to layer key/function
	LoadKll(pathData + fname + "layer2.kll", 2);
	LoadKll(pathData + fname + "layer3.kll", 3);
//	LoadKll(pathData + fname + "overlay.kll", 0);  // Fn to layer num
}
