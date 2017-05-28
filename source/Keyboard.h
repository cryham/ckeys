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
	int x,y, w,h;   // position, dimensions
	sf::String s;   // caption
	float sc = 1.f;   // scale
	bool on = false;  // pressed
};


class Keys
{
public:
	Keys();

	void LoadIndex(int id);

	bool LoadFromJson(std::string path);
	void Destroy();


	bool Init();
	std::string pathData = "data/";  // path to data dir
	std::vector<std::string> files;  // .json layouts

	//  filled in ctor, from csKeyNames
	std::map<int, std::string> vk2str;
	std::map<std::string, int> str2vk;


	//  keyboard layout
	std::vector<Key> keys;

	//  vk code to keys id,  has +1,  0 if not found
	std::map<int, int> vk2key;



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
