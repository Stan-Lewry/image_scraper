#ifndef WINDOW_H
#define WINDOW_H

#include <qwidget.h>
#include <qpushbutton.h>
#include <qapplication.h>
#include <qlineedit.h>
#include <qgroupbox.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <qgridlayout.h>
#include "Request.h"
#include <iostream>
#include <fstream>
#include <vector>


class Window : public QWidget{
	Q_OBJECT
	public:
		explicit Window(QWidget *parent = 0);

	private slots:
		void getPage();
		void getImage();
		void scrapeImages(std::string pageURL);
		void setPageURL();

	private:
		QPushButton *confirmTextButton;
		QPushButton *m_button2;
		QPushButton *m_button3;

		QString pageURL;

		QLineEdit *lineEdit;
		//HTTP *http;
		Request *request;
		std::vector<std::string> linkStore;
};

#endif