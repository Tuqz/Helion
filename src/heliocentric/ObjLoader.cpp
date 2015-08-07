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
#include "renderer/Mesh.hpp"
#include "exceptions.hpp"

using namespace std;

struct Index {
	unsigned short v;
	unsigned short n;
	unsigned short i;
};

ObjLoader::ObjLoader(bool inlining, bool loadColorData)
: inlining(inlining), loadColorData(loadColorData) {
}

ObjLoader::ObjLoader(const ObjLoader& orig) : ObjLoader(orig.inlining, orig.loadColorData) {
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
	// Set globals
	vertexData.clear();
	indices.clear();
	vertices.clear();
	normals.clear();
	vIndices.clear();
    //tIndices.clear();
	nIndices.clear();
	
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

	// Convert to singular indices and populate vertexData
	reorderVertexData();

	return new Mesh(vertexData, indices);
}

void ObjLoader::parseLine(std::string& line) {
	// Tokenize the string
	vector<string> tokens = tokenize(line);
	int N = tokens.size() - 1;
	string linetype = tokens.front();

	// Send string to the correct parser
	if (linetype.compare("v") == 0) {
		parseVEntry(N, tokens);
	} else if (linetype.compare("vn") == 0) {
		parseVNEntry(N, tokens);
	} else if (linetype.compare("f") == 0) {
		parseFEntry(N, tokens);
	}
}

void ObjLoader::parseVEntry(int N, const std::vector<string>& tokens) {
	// Check number of element correctness
	if (N != 3 && N != 4 && N != 6 && N != 7) {
		throw error("Expected three (xyz), four (xyzw), six (xyzrgb) or seven (xyzwrgb) values in v-entry.");
	}

	vector<float> vertex;
	int i;

	// Push vertex coordinates XYZ
	for (i = 1; i <= 3; i++) {
		vertex.push_back(toFloat(tokens[i]));
	}

	// Push W
	if (N == 3 || N == 6) {
		vertex.push_back(1);
	} else {
		vertex.push_back(toFloat(tokens[i]));
		i++;
	}

	// Push color values
	if (loadColorData) {
		for (; i < N + 1; i++) {
			vertex.push_back(toFloat(tokens[i]));
		}
	}

	// Add vertex to list of vertices
	vertices.push_back(vertex);
}

void ObjLoader::parseVNEntry(int N, const std::vector<std::string>& tokens) {
	// Check number of element correctness
	if (N != 3) {
		throw error("Expected three values in vn-entry.");
	}

	// Push normal values
	vector<float> normal;
	for (int i = 1; i <= N; i++) {
		normal.push_back(toFloat(tokens[i]));
	}

	// Add normal to list of normals
	normals.push_back(normal);
}

void ObjLoader::parseFEntry(int N, const std::vector<std::string>& tokens) {
	// Check number of element correctness
	if (N != 3) {
		throw error("Expected three values in f-entry.");
	}

	// Push vertex indices
	for (int i = 1; i <= N; i++) {
		parseIndices(tokens[i]);
	}
}

void ObjLoader::parseIndices(const std::string& token) {
	vector<string> tokens = tokenize(token, '/', true);

	if (tokens.size() == 3) {
		vIndices.push_back(toInt(tokens[0]) - 1);
		//if (tokens[1].empty()) {
		//	tIndices.push_back(toInt(tokens[0]) - 1);
		//} else {
		//	tIndices.push_back(toInt(tokens[1]) - 1);
		//}
		nIndices.push_back(toInt(tokens[2]) - 1);
	} else if (tokens.size() == 2) {
		vIndices.push_back(toInt(tokens[0]) - 1);
		//tIndices.push_back(toInt(tokens[1]) - 1);
		nIndices.push_back(toInt(tokens[0]) - 1);
	} else if (tokens.size() == 1) {
		vIndices.push_back(toInt(tokens[0]) - 1);
		//tIndices.push_back(toInt(tokens[0]) - 1);
		nIndices.push_back(toInt(tokens[0]) - 1);
	} else {
		throw error("Incorrect face specification.");
	}
}

void ObjLoader::reorderVertexData() {
	vector< vector<Index> > lookup(vertices.size());
	vector<Index> reverseLookup;
	Index entry;

	// Convert to singular indices
	entry.i = 0;
	for (int i = 0; i < vIndices.size(); i++) {
		bool found = false;

		// Look if this index pair already exists
		int j;
		for (j = 0; j < lookup[vIndices[i]].size()
				&& !(found = lookup[vIndices[i]][j].n == nIndices[i]); j++);

		// If not, add a new entry to the lookup tables
		if (!found) {
			entry.v = vIndices[i];
			entry.n = nIndices[i];

			lookup[vIndices[i]].push_back(entry);
			reverseLookup.push_back(entry);

			entry.i++;
		}

		// Finally, add the index to the index list
		indices.push_back(lookup[vIndices[i]][j].i);
	}

	// Populate vertexData
	vector<float> actualNormalData;
	vector<float>* normalData = &actualNormalData;
	if (inlining) {
		normalData = &vertexData;
	}
	for (int i = 0; i < entry.i; i++) {
		int iv = reverseLookup[i].v;
		int in = reverseLookup[i].n;
		vertexData.insert(vertexData.end(), vertices[iv].begin(), vertices[iv].end());
		normalData->insert(normalData->end(), normals[in].begin(), normals[in].end());
	}
	if (!inlining) {
		vertexData.insert(vertexData.end(), normalData->begin(), normalData->end());
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

int ObjLoader::toInt(std::string str) {
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
