#pragma once
#include <string>
#include <vector>
#include <map>


struct Key
{
	int x,y, w,h;
	std::string s;
	float sc = 1.f;
	bool on = false;
};


class Keys
{
public:
	Keys();

	void LoadIndex(int id);
	void LoadFromJson(std::string path);
	void Destroy();

	bool Init();
	std::string pathData = "data/";  // path to data dir
	std::vector<std::string> files;  // .json layouts

	//  keyboard layout
	std::vector<Key> keys;
	std::map<int, int> vk2key;  // vk code to keys id

	//  filled on init, from csKeyNames
	std::map<int, std::string> vk2str;
	std::map<std::string, int> str2vk;
};


//  replace in string
static bool replK(std::string& str, const std::string& what, const std::string& to)
{
	size_t p = str.find(what);
	bool rep = p != std::string::npos;
	if (rep)
		str.replace(p, what.length(), to);
	return rep;
}
