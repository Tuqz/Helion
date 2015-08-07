/* 
 * File:   ShaderProgram.hpp
 * Author: Ale Strooisma
 *
 * Created on June 8, 2015, 5:04 PM
 */

#ifndef SHADERPROGRAM_HPP
#define	SHADERPROGRAM_HPP

#include <vector>
#include <string>


class ShaderProgram {
private:
	GLuint program;
public:
	ShaderProgram(std::string vertexShader, std::string fragmentShader);
	ShaderProgram(std::string vertexShader, std::string fragmentShader,
			std::vector<std::string>* attributes);
	ShaderProgram(std::string vertexShader, std::string geometryShader,
			std::string fragmentShader);
	ShaderProgram(std::string vertexShader, std::string geometryShader,
			std::string fragmentShader, std::vector<std::string>* attributes);
	ShaderProgram(const ShaderProgram& orig) = delete;
	ShaderProgram(ShaderProgram&& orig) = delete;
	virtual ~ShaderProgram();
	GLuint getProgram() const;
	GLint getUniformLocation(std::string name) const;
	GLuint getUniformBlockIndex(std::string name) const;
};

#endif	/* SHADERPROGRAM_HPP */

