#pragma once
#include <string>
#include <vector>
#include <map>
#include <list>
#include <SFML/System/String.hpp>
#include <SFML/System/Mutex.hpp>


//  keys for pressed list
struct KeyCode
{
	int vk=0, sc=0, ext=0;

	bool operator==(const KeyCode& o) const
	{	return vk == o.vk && sc == o.sc && ext == o.ext;  }

	bool operator<(const KeyCode& o) const
	{	return vk < o.vk || sc < o.sc || ext < o.ext;  }
};

//  keys for layout
struct Key
{
	//  from json
	int x,y, w,h;    // position, dimensions
	float sc = 1.f;  // scale

	sf::String s;    // caption str
	//  var, from key hook
	bool on = false;  // pressed

	//  from kll
	sf::String sk;   // name for kll
	bool inKll = false;
	bool hasL2 = false, hasL3 = false;
	sf::String s2,s3;   // caption on layer 2 and 3
};


class Keys
{
public:
	Keys();

	void LoadIndex(int id);

	bool LoadJson(std::string path);
	bool LoadKll(std::string path, int layer);
	void Destroy();


	bool Init();
	std::string pathData = "data/";  // path to data dir
	std::vector<std::string> files;  // .json layouts

	//  filled in ctor, from csKeyNames
	std::map<int, std::string> vk2str;
	std::map<std::string, int> str2vk;


	//  keyboard layout
	std::vector<Key> keys;

	//  vk code to keys id
	//  maps have +1,  0 if not found
	std::map<int, int> vk2key;

	//  str caption (1 row) to keys id
	std::map<std::string, int> str2key;

	//  layers, from kll (optional)
	std::map<std::string, int> scan2str;
	std::map<std::string, std::string> lay1str, lay2str;


	//  keyboard hook
	#ifdef _WIN32
	#define	vk_EXTRA 1000
	void Hook();
	void UnHook();
	#endif

	//  keys pressed list
	std::list<KeyCode> keyCodes;
	sf::Mutex mutex;
};
