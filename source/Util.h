#pragma once
#include <vector>
#include <string>
#include <algorithm>


//  format int, float to string
std::string i2s(const int v, const char width=0/*, const char fill=' '*/);
std::string f2s(const float v, const char precision=2, const char width=4);


//  split string
std::vector<std::string> split(
	const std::string& s, const std::string& reg);

//  string to lower
std::string strlower(const std::string& s);

//  found substring ss in s true
static bool found(const std::string& s, const std::string& ss)
{	return s.find(ss) != std::string::npos;  }



//  replace in key name
bool replK(std::string& str, const std::string& what, const std::string& to);

bool replK(std::wstring& str, const std::wstring& what, const std::wstring& to);

//  convert UTF-8 string to wstring
std::wstring utf8_to_wstring(const std::string& str);
