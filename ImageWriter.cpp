#include "ImageWriter.h"

ImageWriter::ImageWriter(){}
ImageWriter::~ImageWriter(){}

void ImageWriter::setFolderPath(std::string _folderPath){
	folderPath = _folderPath;
}

void ImageWriter::writeImageDataToFile(std::string imageName,
		std::string imageData){

	ofstream outputFile(folderPath + std::string("/") + imageName);

	outputFile << imageData;

	outputFile.close();
}

