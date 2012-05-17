#pragma once
#include <string>
#include <map>
#include <fstream>
#include <iostream>

class Settings
{
public:
	Settings(void);
	~Settings(void);

	static std::string getString(std::string p_key);

	static Settings* Get(void);

private:
	void initialize(void);

	static std::map<std::string, std::string> m_keyValue;
};

