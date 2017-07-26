#ifndef IMAGESCRAPER_H
#define IMAGESCRAPER_H

#include <vector>
#include "ImageWriter.h"
#include "Request.h"
#include <qwidget.h>

class ImageScraper{

public:

	ImageScraper();
	

	void getImageUrlsHTML(std::string htmlData);
	void getImageUrlsCSS(std::string cssData);

	std::string getImageData(std::string imageURL);

	std::string getImageName(std::string imageURL);
	std::string updateWidgetList();

	void scrapeImages(std::string pageURL);
        void downloadAll(std::string folderPath);
	
	//std::vector<std::string> getImageURLStore();
	
	std::vector<std::string> imageURLStore;

private:
	std::string pageURL;
	std::string folderPath;

	Request *request;
	ImageWriter *imageWriter;
};

#endif //IMAGESCRAPER_H
