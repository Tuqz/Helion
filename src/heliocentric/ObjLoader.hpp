/* 
 * File:   ObjLoader.hpp
 * Author: Ale Strooisma
 *
 * Created on July 26, 2015, 12:45 PM
 */

#ifndef OBJLOADER_HPP
#define	OBJLOADER_HPP

#include <string>
#include <vector>
#include "exceptions.hpp"
class Mesh;

class ObjParseException : public Exception {
public:
	ObjParseException(std::string message) : Exception(message) {}
};

class ObjLoader {
private:
	// Settings
	bool loadColorData;
	// Mesh data
	std::vector<float> vertices;
	std::vector<unsigned short> indices;
	// For error handling
	std::string currentFile;
	int lineNumber;
public:
	ObjLoader();
	ObjLoader(bool loadColorData);
	ObjLoader(const ObjLoader& orig);
	virtual ~ObjLoader();
	Mesh* load(std::string filename);
private:
	static std::vector<std::string> tokenize(std::string line,
			char separator = ' ', bool allowEmptyTokens = false);
	void parseLine(std::string& line);
	void parseVEntry(int N, const std::vector<std::string>& tokens);
	void parseVNEntry(int N, const std::vector<std::string>& tokens);
	void parseFEntry(int N, const std::vector<std::string>& tokens);
	
	float toFloat(std::string str);
	float toInt(std::string str);
	
	ObjParseException error(std::string message);
};

#endif	/* OBJLOADER_HPP */

