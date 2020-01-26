#pragma once
#include <string>
#include <vector>
#include <algorithm>

typedef std::string String;


inline std::vector<String> SplitString(const String& string, const String& delimiters)
{
		size_t start = 0;
		size_t end = string.find_first_of(delimiters);

		std::vector<String> result;

		while (end <= String::npos)
		{
			String token = string.substr(start, end - start);
			if (!token.empty())
				result.push_back(token);

			if (end == String::npos)
				break;

			start = end + 1;
			end = string.find_first_of(delimiters, start);
		}

		return result;
}

//inline String ToLowerCase( String string)		
//{
//	std::transform(string.begin(), string.end(), string.begin(), ::tolower);
//	return string;

//	char c;
//	while (*string)				//Nah. Not worth it! 
//	{
//		c = *string;
//		*string = tolower(c);
//		string++;
//	}
//
//	return string;
//}

inline String ToLowerCase( String string)		
{
	std::transform(string.begin(), string.end(), string.begin(), ::tolower);
	return string;

}

inline std::vector<String> GetLines(const String& string) 
{
	return SplitString(string, "\n");
}