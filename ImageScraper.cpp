#include "ImageScraper.h"

ImageScraper::ImageScraper(){
	Window window;
	
	connect(window, SIGNAL(sendPageRequest()), this, SLOT(scrapeImages(std::string)));

}


void ImageScraper::scrapeImages(std::sring pageURL){

	std::string pageData = request->getPage(pageURL);

	getImageUrlsHTML(pageData);

	for(int i = 0; i < linkStore.size(); i++){
		std::cout << linkStore.at() << std::endl;
	}
	/*
	first make a request to the request class
	constructing a list of html docs is risky - might accidentally make a full web crawler
	construct a list of html documents (the first element being the page returned by the request class)
	construct a list of css documents
	recurseively call the getImageUrlsHTML & CSS functions to construct the vector of image paths
	*/
}

void ImageScraper::getImageUrlsHTML(std::string htmlData){
	std::string imageTag1 = ".jpg";
	std::string imageTag2 = ".png";

	bool parsingPage = true;

	while(parsingPage){
		std::string::size_type n, o, jpgIter, pngIter;

		jpgIter = htmlData.find(imageTag1);
		pngIter = htmlData.find(imageTag2);

		(jpgIter < pngIter) ? n = jpgIter : n = pngIter;

		if(n == std::string::npos){
			parsingPage = false;
		}
		else{
			bool foundQuote = false;

			for(int i = n; i > 0; i--){
				if(htmlData[i] == "\""){
					o = i;
					foundQuote = true;
					break;
				}
			}

			if(foundQuote){
				linkStore.push_back(
						htmlData.substr(
							o + 1, n - 0 + 3));
				htmlData.erase(htmlData.begin(), 
						htmlData.begin() + n + 3);
			}
		}
	}
}

std::string getImageName(std::string imageURL){
	for(int i = imageURL.size(); i > 0; i--){
		if(imageURL[i] == '/'){
			return imageURL.substr(i + 1, imageURL.size() - i);
		}
	}
	return imageURL;
}

std::string getImageData(std::string imageURL){
	std::string imageData = request->getPage(imageURL);
	
	if(imageData.compare(std::string("ERR")) == 0){
		std::string newPath = pageURL + std::string("/") + imageURL;
		imageData = request->getPage(newPath);
	}

	return imageData;
}	


void downloadAll(){
	/*
	 * Set image writers path
	 * get the image data using the getImageDataFunction
	 * im not sure what else goes here
	 */
};
