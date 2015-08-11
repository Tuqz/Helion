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

/**
 * An exception type that is thrown by ObjLoader when an error is encountered 
 * while parsing.
 * @param message a description of the problem
 */
class ObjParseException : public Exception {
public:
	ObjParseException(std::string message) : Exception(message) {}
};

/**
 * A loader for meshes defined in the Obj-format.
 * 
 * The flag inlining determines whether data other than the vertex coordinates 
 * and the indices will be appended to the vertex data (false) or inserted 
 * directly after the corresponding vertex coordinates (true).
 */
class ObjLoader {
private:
	// Settings
	int textureCoordinateDimensions;
	bool inlining;
	bool loadColorData;
	// Mesh data
	std::vector<float> vertexData;
	std::vector<unsigned short> indices;
	std::vector<std::vector<float>> vertices;
	std::vector<std::vector<float>> texcoords;
	std::vector<std::vector<float>> normals;
	std::vector<unsigned short> vIndices;
	std::vector<unsigned short> tIndices;
	std::vector<unsigned short> nIndices;
	// For error handling
	std::string currentFile;
	int lineNumber;
public:
	ObjLoader(int textureCoordinateDimensions = 2, bool inlining = true, bool loadColorData = false);
	ObjLoader(const ObjLoader& orig);
	virtual ~ObjLoader();
	Mesh load(std::string filename);
	void load(std::string filename, Mesh* mesh);
	
	bool isInlining() const {
		return inlining;
	}

	void setInlining(bool inlining) {
		this->inlining = inlining;
	}

	int getTextureCoordinateDimensions() const {
		return textureCoordinateDimensions;
	}

	void setTextureCoordinateDimensions(int textureCoordinateDimensions) {
		this->textureCoordinateDimensions = textureCoordinateDimensions;
	}

	bool isLoadingColorData() const {
		return loadColorData;
	}

	void setLoadingColorData(bool loadColorData) {
		this->loadColorData = loadColorData;
	}

private:
	static std::vector<std::string> tokenize(std::string line,
			char separator = ' ', bool allowEmptyTokens = false);
	void load();
	void parseLine(std::string& line);
	void parseVEntry(int N, const std::vector<std::string>& tokens);
	void parseVTEntry(int N, const std::vector<std::string>& tokens);
	void parseVNEntry(int N, const std::vector<std::string>& tokens);
	void parseFEntry(int N, const std::vector<std::string>& tokens);
	void parseIndices(const std::string& token);
	
	void reorderVertexData();
	
	float toFloat(std::string str);
	int toInt(std::string str);
	
	ObjParseException error(std::string message);
};

#endif	/* OBJLOADER_HPP */

