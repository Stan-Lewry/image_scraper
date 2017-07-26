#include "ImageWriter.h"

ImageWriter::ImageWriter(){}
ImageWriter::~ImageWriter(){}

void ImageWriter::setFolderPath(std::string _folderPath){
	folderPath = _folderPath;
}

void ImageWriter::writeImageDataToFile(std::string imageName,
		std::string imageData){
	
	std::string filePath = folderPath + std::string("/") + imageName;

	std::ofstream outputFile(filePath.c_str());

	outputFile << imageData;

	outputFile.close();
}

