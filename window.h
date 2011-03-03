#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <QComboBox>
#include <QGroupBox>
#include <QMenu>
#include <QMenuBar>
#include <QSlider>
#include <QSpinBox>
#include <QWidget>

#include "renderer.h"

class Window : public QWidget {
	
public:
	Window(QWidget* parent = 0);
	~Window();

public slots:
	void openMD2Model();
	
private:
	Renderer* renderer;
	QComboBox* mouseComboBox;
	QSlider* xTransSlider;
	QSlider* yTransSlider;
	QSlider* xRotSlider;
	QSlider* yRotSlider;
	QSlider* zRotSlider;
	QSpinBox* scaleSpinBox;
	QComboBox* rendererComboBox;
	
	QMenuBar* createMenuBar();
	QGroupBox* createGroupBoxTranslation();
	QGroupBox* createGroupBoxRotation();
	void connectEvents();
};

#endif