#pragma once
#include <string>
#include <vector>
#include <map>
#include <SFML/System/String.hpp>


struct Key
{
	int x,y, w,h;
	sf::String s;
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


	//  keyboard hook
	#ifdef _WIN32
	void Hook();
	void UnHook();
	#endif
};
