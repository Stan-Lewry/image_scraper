#ifndef IMAGEWRITER_H
#define IMAGEWRITER_H

#include <string>
#include <vector>
#include <iostream> // remove later

class ImageWriter{
public:
	FileManager();
	~FileManager();

	void writeImageDataToFile(std::string filePath,
			std::string imageName,
			std::string imageData);
	std::string getImageData(std::string imageURL);
	void writeAllImages(std::vector<String> images, std::string filePath);


private:

};


#endif //IMAGEWRITER_H
