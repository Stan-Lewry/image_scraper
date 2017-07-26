#include "ImageScraper.h"

ImageScraper::ImageScraper(){
	request = new Request();
	imageWriter = new ImageWriter();
}


void ImageScraper::scrapeImages(std::string _pageURL){
	
	pageURL = _pageURL;
	

	imageURLStore.clear();

	std::string pageData = request->getPage(pageURL);

	getImageUrlsHTML(pageData);

	for(int i = 0; i < imageURLStore.size(); i++){
		std::cout << imageURLStore.at(i) << std::endl;
	}
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
				if(htmlData[i] == '\"'){
					o = i;
					foundQuote = true;
					break;
				}
			}

			if(foundQuote){
				 imageURLStore.push_back(
						htmlData.substr(
							o + 1, n - o + 3));
				htmlData.erase(htmlData.begin(), 
						htmlData.begin() + n + 3);
			}
		}
	}
}

std::string ImageScraper::getImageName(std::string imageURL){

	if(imageURL[0] == '.'){
		imageURL = imageURL.substr(std::string::size_type(1), std::string::size_type( imageURL.size() - 1));
	}

	if(imageURL[0] == '/'){
		imageURL = imageURL.substr(std::string::size_type(1),std::string::size_type(imageURL.size() - 1));
	}

	for(int i = imageURL.size(); i > 0; i--){
		if(imageURL[i] == '/'){
			return imageURL.substr(i + 1, imageURL.size() - i);
		}
	}
	return imageURL;
}

std::string ImageScraper::getImageData(std::string imageURL){
	std::string imageData = request->getPage(imageURL);
	std::cout << imageURL << std::endl;
	if(imageData.compare(std::string("ERR")) == 0){
		std::string newPath = pageURL + std::string("/") + imageURL;
		std::cout << newPath << std::endl;
		imageData = request->getPage(newPath);
	}

	return imageData;
}	


void ImageScraper::downloadAll(std::string folderPath){
	
	imageWriter->setFolderPath(folderPath);	

	for(int i = 0; i < imageURLStore.size(); i++){
		imageWriter->writeImageDataToFile(getImageName(imageURLStore.at(i)), getImageData(imageURLStore.at(i)));
	}
};

/*
std::vector<std::string> ImageScraper::getImageURLStore(){
	return imageURLStore;
}*/


