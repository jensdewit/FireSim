/**
 * @file Util.cpp
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

//Standard
#include <iostream>
#include <algorithm>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

//Poco
#include "Poco/RegularExpression.h"
#include "Poco/Exception.h"

//FireSim
#include "Util.h"

using std::cout;
using std::endl;

int stringToInt(std::string str){
	std::stringstream ss;
	ss << str;
	int i;
	ss >> i;
	return i;
}

std::string intToString(int i){
	std::stringstream ss;
	ss << i;
	std::string result = ss.str();
	return result;
}

short decimalToHex(unsigned long decimal_value, char hex_value[8]) {
	short index, significant_digits = 0;
	unsigned long temp_value;
	for (index = 7; index >= 0; index--) {
		// temp_value=decimal_value/pow(16,index)
		temp_value = decimal_value / (1 << (index << 2));
		if (temp_value > 9) {
			hex_value[index] = (char) ('A' - 10 + temp_value);
			// decimal_value=decimal_value%pow(16,index)
			decimal_value = decimal_value % (1 << (index << 2));
			if (!significant_digits)
				significant_digits = index;
		} else if (temp_value > 0) {
			hex_value[index] = (char) ('0' + temp_value);
			// decimal_value=decimal_value%pow(16,index)
			decimal_value = decimal_value % (1 << (index << 2));
			if (!significant_digits)
				significant_digits = index;
		} else {
			hex_value[index] = '0';
		}
	}
	return significant_digits;
}

std::string itoa(int n) {
	char * s = new char[17];
	std::string u;
	if (n < 0) { //turns n positive
		n = (-1 * n);
		u = "-"; //adds '-' on result string
	}
	int i = 0; //s counter
	do {
		s[i++] = n % 10 + '0'; //conversion of each digit of n to char
		n -= n % 10; //update n value
	} while ((n /= 10) > 0);
	for (int j = i - 1; j >= 0; j--) {
		u += s[j]; //building our string number
	}
	delete[] s; //free-up the memory!
	return u;
}

void printFireSimLogo(std::iostream& stream){
	stream << std::endl << "##################################################" << std::endl;
	stream << "#  _____  ___  ____   _____  ____  ___  __  __   #" << std::endl;
	stream << "# |  ___||_ _||  _ \\ | ____|/ ___||_ _||  \\/  |  #" << std::endl;
	stream << "# | |_    | | | |_) ||  _|  \\___ \\ | | | |\\/| |  #" << std::endl;
	stream << "# |  _|   | | |  _ < | |___  ___) || | | |  | |  #" << std::endl;
	stream << "# |_|    |___||_| \\_\\|_____||____/|___||_|  |_|  #" << std::endl;
	stream << "#                    2008-2009                   #" << std::endl;
	stream << "#                                                #" << std::endl;
	stream << "# Nico.VanLooy@student.ua.ac.be                  #" << std::endl;
	stream << "# Jens.DeWit@student.ua.ac.be                    #" << std::endl;
	stream << "##################################################"<< std::endl;
}

std::vector<std::string> split(std::string base, char delim) {
	std::vector<std::string> tokens;
	int first = 0;
	int last = -1;
	while (first != last) {
		last = base.find_first_of(delim, first);
		std::string substring = base.substr(first, last - first);
		tokens.push_back(substring);
		first = base.find_first_not_of(delim, last);
	}
	return tokens;
}

void convertToLowerCase(std::string& str){
	std::transform(str.begin(),	str.end(),	str.begin(), tolower);
}

void removeWhitespace(std::string& str){
	try {
//		Poco::RegularExpression regexFront(" ");
//		regexFront.subst(str,"", Poco::RegularExpression::RE_GLOBAL);
		Poco::RegularExpression regexFront("^( )");
		regexFront.subst(str,"", Poco::RegularExpression::RE_GLOBAL);
		Poco::RegularExpression regexBack(" *$");
		regexBack.subst(str,"", Poco::RegularExpression::RE_GLOBAL);
	} catch (Poco::RegularExpressionException e) {
		std::cout << "Failure: " << e.message() << std::endl;
		exit(1);
	}
}

void removeFile(std::string file, std::string path) {
	if (remove((path + file).c_str()) == -1) {
		std::cout << "Remove of file " << file << " failed" << std::endl;
		exit(1);
	}
}

void removeFiles(std::vector<std::string> files, std::string path) {
	for (std::vector<std::string>::iterator it = files.begin(); it != files.end(); ++it) {
		if (remove((path + (*it)).c_str()) == -1) {
			std::cout << "Remove of file " << *it << " failed" << std::endl;
			exit(1);
		}
	}
}

std::vector<std::string> read_directory(const std::string& path) {
	std::vector<std::string> result;
	dirent* de;
	DIR* dp;
	errno = 0;
	dp = opendir(path.empty() ? "." : path.c_str());
	if (dp) {
		while (true) {
			errno = 0;
			de = readdir(dp);
			if (de == NULL)
				break;

			std::string fileName = std::string(de->d_name);
			if (!(fileName[0] == '.' || fileName == "Makefile")) {
				result.push_back(fileName);
			}
		}
		closedir(dp);
		std::sort(result.begin(), result.end());
	}
	return result;
}
