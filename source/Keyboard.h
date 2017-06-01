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

enum KClr
{	KC_Normal=0, KC_Missing,  KC_Layer2, KC_Layer3, KC_Display, KC_ALL  };


//  keys for Gui layout
struct Key
{
	//  from json  ----
	int x,y, w,h;     // position, dimensions
	float sc = 1.f;   // scale

	sf::String str;     // key name and caption, shown on Gui
	//  optional json
	sf::String name;    // custom caption on Gui, overrides str

	sf::String Caption()
	{	return name.isEmpty() ? str : name;  }

	uint16_t scan = 0;  // custom scan code

	std::string sJson;  // test name from json

	//  color set, based on name
	KClr clr = KC_Normal;

	//  from kll  ----
	sf::String sKll;     // test name for kll
	bool inKll = false;  // test kll

	sf::String strL2, strL3;   // caption on layer 2 and 3

	//  vk test  ----
	bool inVK = false;
	std::string sVK;

	//  var, from key hook
	bool on = false;    // pressed
};


class Keys
{
public:
	Keys();

	void LoadIndex(int id, bool log);

	bool LoadJson(std::string path, bool logOut = true);
	bool LoadKll(std::string path, int layer, bool logOut = true);
	void Destroy();

	//  replace
	void ReplacePlayer(const std::__cxx11::string& s, sf::String& ws);


	bool Init();
	std::string pathData = "data/";  // path to data dir
	std::vector<std::string> files;  // .json layouts

	//  filled in ctor, from csKeyNames
	std::map<int, std::string> vk2str;
	std::map<std::string, int> str2vk;


	//  keyboard layout  ----
	std::vector<Key> keys;

	//  vk code to key id,  for hook
	//  maps have +1,  0 if not found
	std::map<int, int> vk2key;


	//  str caption (1 row) to keys id, for kll layers
	std::map<std::string, int> str2key;
	//  from kll defaultMap
	std::map<std::string, std::string> kll2scan;


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
