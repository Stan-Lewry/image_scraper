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
	echoLayout->addWidget(folderPath, 3, 0, 1, 2);
	echoLayout->addWidget(downloadNowButton, 3, 2);
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

	std::string pageUrl = "http://stanlewry.com";

	connect(confirmTextButton, SIGNAL(clicked()), this, SLOT(setPageURL()));

	//connect(lineEdit, SIGNAL(text()), m_button3, SLOT(setText(const QString)));

	//connect(m_button, SIGNAL(clicked()), this, SLOT(getPage()));
	//connect(m_button2, SIGNAL(clicked()), this, SLOT(getImage()));
	//connect(m_button3, SIGNAL(clicked()), this, SLOT(scrapeImages(std::string)));
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

void Window::getPage(){

	std::string pageData = request->getPage("http://stanlewry.com");
	std::cout << pageData << std::endl;

}

void Window::getImage(){
	std::string imageData = request->getPage("http://stanlewry.com/assets/me.png");
	std::cout << imageData << std::endl;
	std::ofstream fileOut("output.png");
	fileOut << imageData;
	fileOut.close();

}

void Window::setPageURL(){

	pageURL = lineEdit->text();

	std::cout << pageURL.toStdString();
	scrapeImages(pageURL.toStdString());
}