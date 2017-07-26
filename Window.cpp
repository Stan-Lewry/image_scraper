#include "Window.h" 

Window::Window(QWidget *parent) :
	QWidget(parent)
{


	confirmTextButton = new QPushButton("Go!", this);
	downloadNowButton = new QPushButton("Download All", this);

	QGraphicsScene scene;
	QGraphicsView view(&scene);


	progressBar = new QProgressBar(this);

	QWidget *pic = new QWidget(this);
	pic->setStyleSheet("background-image: url(Assets/wizard.png); background-repeat: no-repeat;");

	listWidget = new QListWidget(this);

	lineEdit = new QLineEdit;
	lineEdit->setText("Enter your URL");
	lineEdit->setFocus();

	folderPath = new QLineEdit;
	folderPath->setText("Enter the path to your folder");
	
	
	QGroupBox* echoGroup = new QGroupBox(tr("Echo"));
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

	setWindowTitle(tr("Image Scraper Pro 3000 turbo edition directors cut straight to DVD"));

	connect(confirmTextButton, SIGNAL(clicked()), this, SLOT(setPageURL()));
	connect(downloadNowButton, SIGNAL(clicked()), this, SLOT(setFolderPath()));

}

std::string Window::sendPageRequest(){
	return lineEdit->text().toStdString();
}

std::string Window::sendDownloadAll(){
	return folderPath->text().toStdString();
}

void Window::setPageURL(){
	sendPageRequest();
}

void Window::setFolderPath(){
	sendDownloadAll();
}

