#ifndef IMAGESCRAPER_H
#define IMAGESCRAPER_H

#include <vector>
#include "ImageWrite.h"
#include "Window.h"
#include "Request.h"

class ImageScraper{
public:
	ImageScraper();
	~ImageScraper();
	

	void getImageUrlsHTML(std::string htmlData);
	void getImageUrlsCSS(std::string cssData);

	void downloadAll(std::vector<String> imageUrls);

private slots:
	void scrapeImages(std::string path);
private:
	Request request;
	ImageWriter imageWriter;
};

#endif //IMAGESCRAPER_H
