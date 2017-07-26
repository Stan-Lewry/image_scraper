#ifndef IMAGEWRITER_H
#define IMAGEWRITER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream> // remove later

class ImageWriter{
public:
	ImageWriter();
	~ImageWriter();

	void writeImageDataToFile(std::string imageName,
			std::string imageData);
	
	void setFolderPath(std::string folderPath);


private:
	std::string folderPath;
};


#endif //IMAGEWRITER_H
