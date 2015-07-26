/* 
 * File:   ObjLoader.cpp
 * Author: Ale Strooisma
 * 
 * Created on July 26, 2015, 12:45 PM
 */

#include <fstream>
#include <stdexcept>
#include <errno.h>
#include <cstring>

#include "ObjLoader.hpp"
#include "Mesh.hpp"
#include "exceptions.hpp"

using namespace std;

ObjLoader::ObjLoader() : ObjLoader(false) {
}

ObjLoader::ObjLoader(bool loadColorData) : loadColorData(loadColorData) {
}

ObjLoader::ObjLoader(const ObjLoader& orig) : ObjLoader(orig.loadColorData) {
}

ObjLoader::~ObjLoader() {
}

vector<string> ObjLoader::tokenize(string line, char separator, bool allowEmptyTokens) {
	vector<string> tokens;
	int tokenStart = 0;
	int tokenLength = 0;

	for (int i = 0; i < line.length(); i++) {
		if (line[i] == separator) {
			if (tokenLength > 0 || allowEmptyTokens) {
				tokens.push_back(line.substr(tokenStart, tokenLength));
			}
			tokenStart = i + 1;
			tokenLength = 0;
		} else {
			tokenLength++;
		}
	}
	if (tokenLength > 0) {
		tokens.push_back(line.substr(tokenStart, tokenLength));
	}

	return tokens;
}

Mesh* ObjLoader::load(string filename) {
	currentFile = filename;
	lineNumber = 0;
	string line;

	// Open the file
	ifstream file(filename);
	if (!file.is_open()) {
		throw IOException("Cannot read file \"" + filename + "\": " + strerror(errno) + ".");
	}

	// Read and process the file line-by-line
	while (getline(file, line)) {
		lineNumber++;

		if (line.length() > 0 && line[0] != '#') {
			parseLine(line);
		}
	}
	if (file.bad()) {
		throw IOException("Error while reading file \"" + filename + "\": " + strerror(errno) + ".");
	}
	
	// Close the file
	file.close();

	return new Mesh(vertices, indices);
}

void ObjLoader::parseLine(std::string& line) {
	// Tokenize the string
	vector<string> tokens = tokenize(line);
	int N = tokens.size() - 1;
	string linetype = tokens.front();

	// Send string to the correct parser
	if (linetype.compare("v") == 0) {
		parseVEntry(N, tokens);
	} else if (linetype.compare("f") == 0) {
		parseFEntry(N, tokens);
	}
}

void ObjLoader::parseVEntry(int N, const std::vector<string>& tokens) {
	// Check number of element correctness
	if (N != 3 && N != 4 && N != 6 && N != 7) {
		throw error("Expected three (xyz), four (xyzw), six (xyzrgb) or seven (xyzwrgb) values in v-entry.");
	}

	int i;
	// Push vertex coordinates XYZ
	for (i = 1; i <= 3; i++) {
		vertices.push_back(toFloat(tokens[i]));
	}

	// Push W
	if (N == 3 || N == 6) {
		vertices.push_back(1);
	} else {
		vertices.push_back(toFloat(tokens[i]));
		i++;
	}

	// Push color values
	if (loadColorData) {
		for (; i < N + 1; i++) {
			vertices.push_back(toFloat(tokens[i]));
		}
	}
}

void ObjLoader::parseFEntry(int N, const std::vector<std::string>& tokens) {
	// Check number of element correctness
	if (N != 3) {
		throw error("Expected three values in f-entry.");
	}

	// Push vertex indices
	for (int i = 1; i <= N; i++) {
		indices.push_back(toInt(tokens[i]) - 1);
	}
}

float ObjLoader::toFloat(std::string str) {
	try {
		return stof(str);
	} catch (invalid_argument& ex) {
		throw error("Value \"" + str + "\" cannot be parsed as a floating point number.");
	} catch (out_of_range& ex) {
		throw error("Value \" " + str + "\" is out of the range that"
				+ " can be represented by a float.");
	}
}

float ObjLoader::toInt(std::string str) {
	try {
		return stoi(str);
	} catch (invalid_argument& ex) {
		throw error("Value \"" + str + "\" cannot be parsed as an integer.");
	} catch (out_of_range& ex) {
		throw error("Value \"" + str + "\" is out of the range that"
				+ " can be represented by an integer.");
	}

}

ObjParseException ObjLoader::error(std::string message) {
	return ObjParseException("Error while parsing \"" + currentFile + "\", line "
			+ to_string(lineNumber) + ": " + message);
}
