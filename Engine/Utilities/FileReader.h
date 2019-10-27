#ifndef FILE_READER_H_
#define FILE_READER_H_

#include <string>
#include <fstream>

#include <iostream>

using namespace std;

static string readFile(string fullpath)
{
	/* Open file */
	ifstream is(fullpath.c_str(), std::ifstream::in);

	/* Read data from file */
	string content((istreambuf_iterator<char>(is)),
		istreambuf_iterator<char>());

	/* Return content */
	return content;
}

#endif
