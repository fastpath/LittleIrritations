#include "Settings.h"

static Settings* g_Settings = NULL;
std::map<std::string,std::string> Settings::m_keyValue;

Settings::Settings(void)
{
	if (g_Settings)
	{
		delete g_Settings;
	}
	g_Settings = this;

	initialize();
}

void Settings::initialize(void) {
	std::string line;
	std::ifstream config("config.ini");
	if (config.is_open())
	{
		while (config.good())
		{
			std::getline(config,line);
			std::size_t find = line.find_first_of("=");
			std::string key = line.substr(0,find);
			std::string value = line.substr(find+1, line.length());
			m_keyValue[key]=value;
			std::cout << "Key: " << key << " Value: " << value << std::endl;
		}
		config.close();
	}
}

Settings::~Settings(void)
{
	delete g_Settings;
}

std::string Settings::getString(const std::string& p_key) {
	return m_keyValue[p_key];
}

int Settings::getInt(const std::string& p_key) {
	std::stringstream val_sstr;
	int val;
	val_sstr << m_keyValue[p_key];
	val_sstr >> val;
	return val;
}

unsigned int Settings::getUnsignedInt(const std::string& p_key) {
	std::stringstream val_sstr;
	unsigned int val;
	val_sstr << m_keyValue[p_key];
	val_sstr >> val;
	return val;
}

Settings* Settings::Get(void) {
	return g_Settings;
}
