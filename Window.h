#ifndef WINDOW_H
#define WINDOW_H

#include <qwidget.h>
#include <qpushbutton.h>
#include <qapplication.h>
#include <qlineedit.h>
#include <qgroupbox.h>
#include <qcombobox.h>
#include <qgraphicsscene.h>
#include <qgraphicsview.h>
#include <QGraphicsPixmapItem>
#include <QListWidgetItem>
#include <QProgressBar>
#include <QString>
#include <QFileDialog>
#include <qlabel.h>
#include <qgridlayout.h>
#include "ImageScraper.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Window : public QWidget{
	Q_OBJECT
	public:
		explicit Window(QWidget *parent = 0);
		void writeToFile(std::string path, 
				std::string imageURL,
				std::string imageData);

		void sendPageRequest();
		void sendDownloadAll();

	private slots:
		void setPageURL();
		void setFolderPath();

	private:
		QPushButton *confirmTextButton;
		QPushButton *downloadNowButton;
		QPushButton *m_button2;
		QPushButton *m_button3;

		QProgressBar *progressBar;

		QListWidget* listWidget;

		QGraphicsPixmapItem item;

		QString pageURL;
		QString filePath;

		QLineEdit *lineEdit;
		QLineEdit *folderPath;
		

		ImageScraper* imageScraper;
};

#endif
