#include <iostream>
#include <fstream>
#include <vector>
#include "loaders.hpp"
#include "Mesh.hpp"

using namespace std;

vector<string> tokenize(string line, char separator = ' ', bool allowEmptyTokens = false) {
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

Mesh* loaders::loadOBJ(string filename) {
	ifstream file(filename.c_str());
	if (!file.is_open()) {
		cerr << "Unable to open file \"" << filename << "\"" << endl;
		throw 1;
	}

	int lineNumber = 0;
	string line;
	vector<string> tokens;
	vector<float> vertices;
	vector<unsigned short> indices;

	while (!file.eof()) {
		lineNumber++;
		getline(file, line);

		if (line.length() > 0) {
			tokens = tokenize(line);
			int N = tokens.size()-1;
			if (tokens.front().compare("v") == 0) {
				if (N != 3 && N != 4 && N != 6 && N != 7) {
					cerr << "Error while parsing \"" << filename << "\"" << endl;
					cerr << "    Expected three(xyz), four(xyzw), six(xyzrgb) or seven(xyzwrgb) values in line "
							<< lineNumber << ": \"" << line << "\"" << endl;
					throw 2;
				}
				// Push vertex coordinates XYZ
				int i;
				for (i = 1; i < 4; i++) {
					vertices.push_back(atof(tokens[i].c_str()));
				}
				// Push W
				if (N == 3 || N == 6) {
					vertices.push_back(1);
				} else  {
					vertices.push_back(atof(tokens[i].c_str()));
					i++;
				}
				// Push color values
//				for (; i < N+1; i++) {
//					vertices.push_back(atof(tokens[i].c_str()));
//				}
			} else if (tokens.front().compare("f") == 0) {
				if (tokens.size() != 4) {
					cerr << "Error while parsing \"" << filename << "\"" << endl;
					cerr << "    Expected three values in line "
							<< lineNumber << ": \"" << line << "\"" << endl;
					throw 2;
				}
				for (int i = 1; i < tokens.size(); i++) {
					indices.push_back(atoi(tokens[i].c_str())-1);
				}
			}
		}
	}
	
	return new Mesh(vertices, indices);

	// Close the file
	file.close();
}
