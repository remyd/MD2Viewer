#include <QApplication>

#include "main.h"
#include "window.h"

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	
	Window window;
	window.resize(WINDOW_WIDTH, WINDOW_HEIGHT);
	window.show();
	
	return app.exec();
}