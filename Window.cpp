#include "Window.h" 

Window::Window(QWidget *parent) :
	QWidget(parent)
{

	pageURL = "";
		//setFixedSize(400, 100);

	confirmTextButton = new QPushButton("Go!", this);
	downloadNowButton = new QPushButton("Download All", this);

	QGraphicsScene scene;
	QGraphicsView view(&scene);
	//item = new QGraphicsPixmapItem(QPixmap("Assets/wizard/.png"));

	progressBar = new QProgressBar(this);

	QWidget *pic = new QWidget(this);
	pic->setStyleSheet("background-image: url(Assets/wizard.png); background-repeat: no-repeat;");
	//pic->setGeometry(QRect(50, 50, 128, 128));


	listWidget = new QListWidget(this);

	// new QListWidgetItem(tr("TEST"), listWidget);
	// new QListWidgetItem(tr("TEST"), listWidget);
	// new QListWidgetItem(tr("TEST"), listWidget);
	// new QListWidgetItem(tr("TEST"), listWidget);
	// new QListWidgetItem(tr("TEST"), listWidget);
	// new QListWidgetItem(tr("TEST"), listWidget);

	QGroupBox *echoGroup = new QGroupBox(tr("Echo"));
	QLabel *echolabel = new QLabel(tr("Mode:"));
	QComboBox *echoComboBox = new QComboBox;
	echoComboBox->addItem(tr("Normal:"));
	echoComboBox->addItem(tr("Password:"));
	echoComboBox->addItem(tr("PasswordEchoOnEdit"));
	echoComboBox->addItem(tr("No Echo"));

	lineEdit = new QLineEdit;
	lineEdit->setText("Enter your URL");
	lineEdit->setFocus();

	folderPath = new QLineEdit;
	folderPath->setText("Enter the path to your folder");

	QGridLayout *echoLayout = new QGridLayout;
	echoLayout->addWidget(pic, 0, 0, 1, 3);
	echoLayout->addWidget(lineEdit, 1, 0, 1, 2);
	echoLayout->addWidget(confirmTextButton, 1, 2);
	echoLayout->addWidget(listWidget, 2, 0, 1, 3);
	//echoLayout->addWidget(folderPath, 3, 0, 1, 2);
	echoLayout->addWidget(downloadNowButton, 3, 0);
	echoLayout->addWidget(progressBar, 4, 0);
	echoGroup->setLayout(echoLayout);


	setLayout(echoLayout);

	setWindowTitle(tr("Line Edits"));
	/*
	m_button = new QPushButton("Get Page", this);
	m_button->setGeometry(10, 10, 80, 30);

	m_button2 = new QPushButton("Get Image", this);
	m_button->setGeometry(10, 40, 80, 30);
	*/
	
	//m_button3 = new QPushButton("Scrape Images From Thread", this);
	request = new Request();

	//lineEdit->setGeometry(10, 40, 200, 30);

	//http = new HTTP();

	std::string pageUrl = "";

	connect(confirmTextButton, SIGNAL(clicked()), this, SLOT(setPageURL()));
	connect(downloadNowButton, SIGNAL(clicked()), this, SLOT(setFolderPath()));

}


void Window::scrapeImages(std::string pageURL){

	std::cout << "Scraping images..." << std::endl;



	
	std::string pageData = request->getPage(pageURL);

	

	
	std::cout << pageData << std::endl;

	std::string imageTag1 = ".jpg";
	std::string imageTag2 = ".png";

	bool parsingPage = true;

	while(parsingPage){
		std::string::size_type n;
		std::string::size_type o;

		std::string::size_type jpgIter;
		std::string::size_type pngIter;

		jpgIter = pageData.find(imageTag1);
		pngIter = pageData.find(imageTag2);

		//(jpgIter < pngIter) ? n = jpgIter : n = pngIter;

		n = pageData.find(imageTag2);



		if(n == std::string::npos){
			std::cout << "Nothing found..." << std::endl;
			parsingPage = false;
		}
		else{
			std::cout << "found an image" << std::endl;
			bool foundQuote = false;



			for(int i = n; i > 0; i--){
				if(pageData[i] == '\"'){
					std::cout << "Found end tag" << std::endl;
					o = i;
					//foundQuote = true;
					break;
				}
			}
			//parsingPage = foundQuote;
			
			std::string imageURL = pageData.substr( o + 1, n - o + 3);
			std::cout << imageURL << std::endl;

			linkStore.push_back(imageURL);
			pageData.erase(pageData.begin(), pageData.begin() + (n + 3));
			

			//std::string imageURL = pageData.substr(o, n)
		}
	}

	std::ofstream fileOut("linksFound.txt");

	for(int i = 0 ; i < linkStore.size(); i++){
		std::cout << "Writing links to file" << std::endl;
		QListWidgetItem *newItem = new QListWidgetItem;

		newItem->setText(QString(linkStore.at(i).c_str()));

		QString qstr = QString::fromStdString(linkStore.at(i));
		newItem->setText(qstr);
		listWidget->insertItem(listWidget->currentRow(), newItem);

		fileOut << linkStore.at(i);
		fileOut << "\n";
	}
	fileOut.close();
}


std::string Window::getFileName(std::string imageURL){
	for(int i = imageURL.size(); i > 0; i--){
		if(imageURL[i] == '/'){
			return imageURL.substr(i + 1, imageURL.size() - i);
		}
	}

	return imageURL;
}

void Window::getPage(){

	std::string pageData = request->getPage("http://stanlewry.com");
	std::cout << pageData << std::endl;

}

std::string Window::getImage(std::string imageURL){
	std::string imageData = request->getPage(imageURL);
	std::cout << "Requesting an image at: " << std::cout << imageURL << std::endl;
	if(imageData.compare(std::string("ERR")) == 0){
		std::string newPath = pageURLStr + std::string("/") + imageURL;
		std::cout << "image not found..." << std::endl;
		std::cout << "trying again at: " << newPath << std::endl;
		imageData = request->getPage(newPath);
	}

	return imageData;
}

void Window::writeToFile(std::string path, std::string imageURL, std::string imageData){
        path =  getFileName(imageURL);
	std::cout << "WRITING THE IMAGE TO: " << std::endl;
	std::cout << path << std::endl;
	std::ofstream fileOut(path.c_str());
	fileOut << imageData;
	fileOut.close();
}

void Window::saveAllImages(){
	for(int i = 0; i < linkStore.size(); i++){
		writeToFile(folderPathStr, linkStore.at(i),
				getImage(linkStore.at(i)));
	}
}

void Window::setPageURL(){
	
	//Empty list widget
	listWidget->clear();
	linkStore.clear();	
	pageURL = lineEdit->text();
	pageURLStr = pageURL.toStdString();
	std::cout << pageURL.toStdString();
	scrapeImages(pageURL.toStdString());
}

void Window::setFolderPath(){
	filePath = folderPath->text();
	folderPathStr = filePath.toStdString();
	saveAllImages();	
}
