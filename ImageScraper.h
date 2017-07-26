#ifndef IMAGESCRAPER_H
#define IMAGESCRAPER_H

#include <vector>
#include "ImageWriter.h"
#include "Window.h"
#include "Request.h"
#include <qwidget.h>

class ImageScraper : public QWidget{
	Q_OBJECT

public:

	ImageScraper();
	~ImageScraper();
	

	void getImageUrlsHTML(std::string htmlData);
	void getImageUrlsCSS(std::string cssData);

	std::string getImageData(std::string imageURL);

	std::string getImageName(std::string imageURL);

signals:
	std::string updateWidgetList();

private slots:
	void scrapeImages(std::string pageURL);
        void downloadAll(std::string folderPath);
private:
	Request *request;
	ImageWriter *imageWriter;
	std::string pageURL;
	std::string folderPath;
	std::vector<std::string> imageURLStore;
};

#endif //IMAGESCRAPER_H
