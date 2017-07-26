#include <qapplication.h>
#include <qpushbutton.h>
//#include "Window.h"
#include "ImageScraper.h"
#include <iostream>
#include <string>
//#include <curl/curl.h>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

std::string pageData;


using namespace curlpp::options;

int main(int argc, char **argv){
	QApplication app (argc, argv);

	ImageScraper *imageScraper = new ImageScraper();

	return app.exec();
}
