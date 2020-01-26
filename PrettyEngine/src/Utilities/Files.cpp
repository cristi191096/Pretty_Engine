#include "pepch.h"
#include "Files.h"

#include <errno.h>
#include <stdio.h>




namespace PrettyEngine {

	byte* FileSystem::ReadFile(const String& path)		//Actually not sure if it should return byte*/ unsigned char* instead of char*
	{
		/*Method that is able to read a binary file and return a byte(unsigned char) array.
		Should be tested properly.
		Use with caution.*/
	
		FILE* file = fopen( path.c_str(), "r");
		fseek(file, 0, SEEK_END);
		unsigned long length = ftell(file);
		byte* data = new byte[length + 1];		//Not sure about this thing
		memset(data, 0, length + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);
		fclose(file);

		return data;
	}

	String FileSystem::ReadTextFile(const String& path)
	{
		/*Method that is able to read a text file and return a string array.*/
		//String filePath = "../" + path;
		//char* name = get_current_dir_name();
#if 0

		String line;
		std::ifstream file;
		std::stringstream ss;

		file.open(path, std::ios::beg);

		if (file.is_open()) 
		{

			while (getline(file, line))
			{
				ss << line << '\n';
			}
			file.close();
			return ss.str();
		}
		else 
		{
			PE_CORE_ERROR("Unable to open file because: {0}", strerror(errno));
		}

		return "";
		//-----------------------------------------------
//Can't fix the C implementation of file reading

	#endif	


		FILE* file;
		unsigned int err = fopen_s(&file, path.c_str(), "rt");

		if (!err) 
		{

			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file);
			char* data = new char[length + 1];
			memset(data, 0, length + 1);
			fseek(file, 0, SEEK_SET);
			fread(data, 1, length, file);
			fclose(file);

			String result(data);
			delete[] data;
			return result;

		}
		else
		{	
			PE_CORE_ERROR("Unable to open file because: {0}", strerror(errno));
			return " ";
			
		}

	}
}