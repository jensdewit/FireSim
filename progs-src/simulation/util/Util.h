/**
 * @file Util.h
 * @author Nico Van Looy (s0061909) & Jens De Wit (s0061864)
 * @brief Bachelor project of University of Antwerp - 2008-2009
 */

#ifndef FIRESIM_UTIL_H_
#define FIRESIM_UTIL_H_

//Standard
#include <string>
#include <sstream>
#include <vector>

/**
 * Conversion from std::string to integer.
 * @param string
 * @return integer
 */
int stringToInt(std::string str);

/**
 * Conversion from integer to std::string.
 * @param integer
 * @return string
 */
std::string intToString(int i);

/**
 * Conversion from decimal to hex.
 * @param decimal_value
 * @param hex_value
 * @return the number of hex digits.
 */
short decimalToHex(unsigned long decimal_value, char hex_value[8]);

/**
 * Conversion from integer to string.
 * @param integer value
 * @return the resulting string.
 */
std::string itoa(int n);

/**
 * Print the Firesim-logo as an ascii-chart on the specified stream
 */
void printFireSimLogo(std::iostream& stream);

/**
 * Split a string in substring using the given delimiter.
 * @param base string to split.
 * @param delim delimiter used to split string
 * @return vector containing the substrings
 */
std::vector<std::string> split(std::string base, char delim);

/**
 * Convert string to lower case.
 * @param str the string which will be transformed.
 */
void convertToLowerCase(std::string& str);

/**
 * Remove all whitespace in the specified string.
 * @param str the string which will be transformed.
 */
void removeWhitespace(std::string& str);

/**
 * Remove file, localized by path parameter and filename.
 */
void removeFile(std::string filename, std::string path);

/**
 * Remove all files listed in the vector parameter, localized by path parameter.
 */
void removeFiles(std::vector<std::string> files, std::string path);

/**
 * Makes a listing of all files in the folder specified by path parameter.
 */
std::vector<std::string> read_directory(const std::string& path);
#endif /* FIRESIM_UTIL_H_ */
