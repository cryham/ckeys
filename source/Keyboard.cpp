#include "Keyboard.h"
#include "KeyNames.h"
#include "Settings.h"
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
	kll2scan.clear();
}

//  read layouts from file
void Keys::LoadIndex(const Settings* set)
{
	int id = set->iCombo;
	bool log = set->logOut;

	if (id >= files.size())
		return;

	//  clear last
	Destroy();

	//  load json
	string fname = files[id];
	string p = set->data;

	LoadJson(p + fname + ".json", log);

	//  load klls
	//	default map:  scan code to kll name
	LoadKll(p + "defaultMap" + fname + ".kll", 1, log);
	//	layer map:  kll name to layer key/function
	LoadKll(p + fname + "layer2.kll", 2, log);
	LoadKll(p + fname + "layer3.kll", 3, log);

//	LoadKll(p + fname + "overlay.kll", 0);  // Fn to layer num
//	U"Function2" : layerShift(2);  # hold
//	U"Function3" : layerShift(3);  # hold
}
