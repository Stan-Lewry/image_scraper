#include "Request.h"


using namespace curlpp::options;

Request::Request(){}
Request::~Request(){}



std::string Request::getPage(std::string pageUrl){
	try{
		curlpp::Cleanup myCleanup;
		curlpp::Easy myRequest;

		myRequest.setOpt<Url>(pageUrl);

		std::ostringstream os;
		curlpp::options::WriteStream ws(&os);

		myRequest.setOpt(ws);

		myRequest.perform();

		os <<myRequest;
		//std::cout << os.str() << std::endl;
		return os.str();
	}
	catch(curlpp::RuntimeError & e){
		std::cout << e.what() << std::endl;
		std::cout << "A RUNTIME ERROR HAS BEEN CAUGHT"<< std::endl;
		return "ERR";
	}
	catch(curlpp::LogicError & e){
		std::cout << e.what() << std::endl;
		return "ERR";
	}


}
