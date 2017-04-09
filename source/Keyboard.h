#pragma once
#include <string>
#include <vector>
#include <map>
#include <SFML/System/String.hpp>


//  keys for layout
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


	//  vk code to keys id,  has +1,  0 if not found
	std::map<int, int> vk2key;

	//  filled on init, from csKeyNames
	std::map<int, std::string> vk2str;
	std::map<std::string, int> str2vk;


	//  keyboard hook
	#ifdef _WIN32
	#define	vk_EXTRA 1000
	void Hook();
	void UnHook();
	#endif
};
