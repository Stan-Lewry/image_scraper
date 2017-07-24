#ifndef REQUEST_H
#define REQUEST_H

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>

using namespace curlpp::options;
class Request{
public:
	Request();
	~Request();

	std::string getPage(std::string pageUrl);
private:
	//std::string 

};

#endif