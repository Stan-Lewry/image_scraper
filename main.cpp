#include <qapplication.h>
#include <qpushbutton.h>
#include "Window.h"
#include <iostream>
#include <string>
//#include <curl/curl.h>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

std::string pageData;


using namespace curlpp::options;

int main(int argc, char **argv){

	/*
	CURL* curl;

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();



	curl_easy_setopt(curl, CURLOPT_URL, "http://stanlewry.com");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);


	curl_easy_perform(curl);

	std::cout << pageData << std::endl;
	*/

	/*
	try
	{
		curlpp::Cleanup myCleanup;

		curlpp::Easy myRequest;

		myRequest.setOpt<Url>("http://stanlewry.com");

		myRequest.perform();
	}
	catch(curlpp::RuntimeError & e){
		std::cout << e.what() << std::endl;
	}
	catch(curlpp::LogicError & e){
		std::cout << e.what() << std::endl;
	}
	*/
	QApplication app (argc, argv);

	Window window;
	window.show();

	return app.exec();
}



/*
#include "HTTP.h"


HTTP::HTTP(){
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	//curl_easy_setopt(curl, CURLOPT_URL, "http://www.stanlewry.com");

	//curl::Cleanup myCleanup;


}


size_t HTTP::writeCallback(char* buf, size_t size, size_t nmemb, void* up){
	for(int i = 0; i < size*nmemb; i++){
		data.push_back(buf[i]);
	}
	return size*nmemb;
}

void HTTP::getPage(std::string pageURL){
	
	curl_easy_setopt(curl, CURLOPT_URL, "http://stanlewry.com");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);


	curl_easy_perform(curl);




}

*/