#include "Keys.h"
#include "KeyNames.h"
#include "Settings.h"
#include "Util.h"
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
bool Keys::Init(Settings* pSet)
{
	set = pSet;
	files.clear();
	vCmb.clear();

	//  get .json files from data dir, into combo
	vector<string> vf = vector<string>();

	getDir(set->data, vf);
	for (auto s : vf)
		if (endsWith(s, ".json"))
		{
			string ss = s;  replK(ss, ".json", "");
			files.push_back(ss);
		}

	for (auto f : files)
	{
		for (auto c : f)
			vCmb.push_back(c);
		vCmb.push_back(0);
	}
	vCmb.push_back(0);
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
void Keys::LoadIndex()
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
