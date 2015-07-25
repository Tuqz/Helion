/* 
 * File:   exceptions.hpp
 * Author: Ale Strooisma
 *
 * Created on July 25, 2015, 12:52 PM
 */

#ifndef EXCEPTIONS_HPP
#define	EXCEPTIONS_HPP

#include <exception>
#include <string>

class Exception : public std::exception {
private:
	std::string msg;
public:
	Exception(std::string message) : msg(message) {};
	virtual ~Exception() {};
	virtual const char* what() const noexcept {
		return msg.c_str();
	}
};

class GLFWException : public Exception {
public:
	GLFWException(std::string message) : Exception(message) {}
};

class IOException : public Exception {
public:
	IOException(std::string message) : Exception(message) {}
};

class ShaderException : public Exception {
public:
	ShaderException(std::string message) : Exception(message) {}
};

class LoaderException : public Exception {
public:
	LoaderException(std::string message) : Exception(message) {}
};

#endif	/* EXCEPTIONS_HPP */

