#pragma once
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "INIParser.hpp"


namespace utility
{
	typedef unsigned int uint;
	
	inline uint gcf(uint a, uint b)
	{
		uint c;
		while (b != 0)
		{
			c = a % b;
			a = b;
			b = c;
		}
		return a;
	}

	inline uint lcm(const uint& a, const uint& b)
	{
		return a * b / gcf(a, b);
	}

	inline int imax(const int& a, const int& b)
	{
		if (a < b)
		{
			return b;
		}
		return a;
	}

	inline int imin(const int& a, const int& b)
	{
		if (a > b)
		{
			return b;
		}
		return a;
	}

	inline double dmax(const double& a, const double& b)
	{
		if (a < b)
		{
			return b;
		}
		return a;
	}


	inline double dmin(const double& a, const double& b)
	{
		if (a > b)
		{
			return b;
		}
		return a;
	}


	inline bool inInterval_i(const int& a, const int& lb, const int& hb)
	{
		return ((a >= lb) && (a <= hb));
	}

	inline bool inInterval_d(const double& a, const double& lb, const double& hb)
	{
		return ((a >= lb) && (a <= hb));
	}


	inline int iclamp(const int& val, const int& lbound, const int& hbound)
	{
		if (val < lbound)
		{
			return lbound;
		}
		else if (val > hbound)
		{
			return hbound;
		}
		return val;
	}


	inline double dclamp(const double& val, const double& lbound, const double& hbound)
	{
		if (val < lbound)
		{
			return lbound;
		}
		else if (val > hbound)
		{
			return hbound;
		}
		return val;
	}

	inline bool isNearAbs(const double& a, const double& b, const double& error)
	{
		return (fabs(a - b) < error);
	}

	inline bool isNearPercent(const double& observed, const double& theoretical, const double& error)
	{
		return ((fabs(observed - theoretical) / theoretical)  < error);
	}

	inline void seedRand()
	{

		SYSTEMTIME st;
		GetSystemTime(&st);
		int seed = st.wMilliseconds;
		srand(seed);

	}

	inline int randInt()
	{
		return rand();
	}

	inline int randInt(const int& lo, const int& hi)
	{
		if (lo > hi)
		{
			return randInt(hi, lo);
		}
		if (lo == hi)
		{
			return lo;
		}
		else
		{
			return randInt() % (hi - lo + 1) + lo;
		}
	}

	inline double randUnitDouble()
	{
		return ((double)(randInt())) / ((double)(RAND_MAX));
	}

	inline double randDouble()
	{
		return (double)(randInt()) + randUnitDouble();
	}


	inline std::vector<std::string> spiltAtSubstring(const std::string& bigstr, const std::string& substr)
	{
		std::vector<std::string> retstrs;
		std::string tracker = "";
		if (substr.size())
		{
			for (uint i = 0; i < bigstr.size(); i++)
			{
				if (bigstr[i] == substr[0])
				{
					bool same = true;
					uint rk = 0;

					for (uint k = 1; (k < substr.size()) && same; k++)
					{

						if (bigstr[imin(i + k, bigstr.size() - 1)] != substr[k])
						{
							same = false;
						}
						rk = k;
					}
					if (same)
					{
						i = imin(i + rk, bigstr.size() - 1);
						retstrs.push_back(tracker);
						tracker = "";
					}
					else
					{
						tracker += bigstr[i];
					}
				}
				else
				{
					tracker += bigstr[i];
				}
			}
		}
		else
		{
			retstrs.push_back(bigstr);
		}
		if (tracker != "")
		{
			retstrs.push_back(tracker);
		}
		return retstrs;
	}

	inline void removeSubstring(std::string& bigstr, const std::string& substr)
	{
		std::vector<std::string> sstrs = spiltAtSubstring(bigstr, substr);
		bigstr = "";
		for (uint i = 0; i < sstrs.size(); i++)
		{
			bigstr += sstrs[i];
		}

	}

	inline std::vector<std::string> getSectionNames(const std::string& filename, INIParser& ip)
	{
		ip.readINI(filename);
		ip.setSection("SectionNames");

		const unsigned int elementNumber = ip.getValue<int>("size");
		const std::string prekey = ip.getValue<std::string>("keyName");

		std::vector<std::string> sectionNames;

		std::string tmpSectionName = "";

		for (unsigned int i = 0; i < elementNumber; i++)
		{
			tmpSectionName = prekey + boost::lexical_cast<std::string>(i);
			sectionNames.push_back(ip.getValue<std::string>(tmpSectionName));
		}

		return sectionNames;
	}
	

}
