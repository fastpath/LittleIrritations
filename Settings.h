#pragma once
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>

class Settings
{
public:
	Settings(void);
	~Settings(void);

	static std::string getString(const std::string& p_key);
	static int getInt(const std::string& p_key);
	static unsigned int getUnsignedInt(const std::string& p_key);

	static Settings* Get(void);

private:
	void initialize(void);

	static std::map<std::string, std::string> m_keyValue;
};

