#pragma once
#include <string>
#include <vector>
#include <map>
#include "../../Utility/Utility.hpp"
#include <windows.h> 

class Beat
{
public:
	Beat();
	~Beat();

	void setBeatDuration(const double& qdur);
	void setSpacePercent(const double& sp);

	void setupMap(INIParser& ip);

	void createBeat(std::string beatStr);

	void testBeat(const double& tempo, const double& spacePercent);

	std::vector<std::pair<double, bool>> getDurations();

private:

	void setMapValue(const std::string& nam, const double& tim, const bool& note);
	
	std::map<std::string, std::pair<double, bool>> timeMap;
	

	std::vector<std::pair<double, bool>> durations;
	
};

