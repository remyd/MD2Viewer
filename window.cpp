#include <QAction>
#include <QApplication>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

#include "window.h"

using namespace std;

/**
 * Public constructor
 * @param parent Parent of the widget
 */
Window::Window(QWidget* parent) : QWidget(parent) {
	/* Set the title of the window */
	setWindowTitle("MD2 viewer");
	
	/* Create the layouts */
	QVBoxLayout *sidebarLayout = new QVBoxLayout();
	QHBoxLayout *mainLayout = new QHBoxLayout();
	
	/* Add the openGL widget */
	renderer = new Renderer(this);
	mainLayout->addWidget(renderer);
	
	/* Add the mouse behavior widgets */
	QLabel* mouseLabel = new QLabel("Mouse behavior");
	mouseComboBox = new QComboBox(this);
	mouseComboBox->addItem("Translation");
	mouseComboBox->addItem("Rotation");
	mouseComboBox->addItem("Zoom");
	
	mouseComboBox->setCurrentIndex(1);
	
	sidebarLayout->addWidget(mouseLabel);
	sidebarLayout->addWidget(mouseComboBox);
	
	/* Add the renderer option widgets */
	QLabel* rendererLabel = new QLabel("Renderer");
	rendererComboBox = new QComboBox();
	rendererComboBox->addItem("Wired");
	rendererComboBox->addItem("Flat");
	rendererComboBox->addItem("Smooth");
	
	rendererComboBox->setCurrentIndex(1);
	
	sidebarLayout->addWidget(rendererLabel);
	sidebarLayout->addWidget(rendererComboBox);
	
	/* Add the scaling widgets */
	QLabel* scaleLabel = new QLabel("Zoom");
	scaleSpinBox = new QSpinBox();
	scaleSpinBox->setRange(1, 500);
	scaleSpinBox->setSingleStep(10);
	scaleSpinBox->setSuffix("%");
	scaleSpinBox->setValue(100);
	
	sidebarLayout->addWidget(scaleLabel);
	sidebarLayout->addWidget(scaleSpinBox);
	
	/* Add the widgets for the translations */
	sidebarLayout->addWidget(createGroupBoxTranslation());
	
	/* Add the widgets for the rotations */
	sidebarLayout->addWidget(createGroupBoxRotation());
	
	/* Add the side bar */
	mainLayout->addLayout(sidebarLayout);
	
	/* Create a spacer */
	QSpacerItem* spacer = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding);
	sidebarLayout->addSpacerItem(spacer);
	
	/* Create the menu bar */
	mainLayout->setMenuBar(createMenuBar());
	
	/* Connect the event of the sliders to the renderer */
	connectEvents();
	
	/* Set the main layout of the window */
	setLayout(mainLayout);
}

/** Public destructor */
Window::~Window() {
}

/**
 * Create the menu bar of the window
 * @return Menu bar
 */
QMenuBar* Window::createMenuBar() {
	QMenuBar* menuBar = new QMenuBar();
	
	/* Create the file menu */
	QMenu* fileMenu = new QMenu("&File", this);
	QAction* loadModelAction = new QAction("&Load MD2 model", this);
	fileMenu->addAction(loadModelAction);
	QAction* loadTexModelAction = new QAction("&Load model texture", this);
	fileMenu->addAction(loadTexModelAction);
	QAction* quitAction = new QAction("&Quit", this);
	fileMenu->addAction(quitAction);
	
	/* Connect the signal of the menu */
	connect(loadModelAction, SIGNAL(triggered()), renderer, SLOT(openMD2Model()));
	connect(loadTexModelAction, SIGNAL(triggered()), renderer, SLOT(openTextureModel()));
	connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
	
	/* Add the different menus to the menu bar */
	menuBar->addMenu(fileMenu);
	
	return menuBar;
}

/**
 * Create the group box for the translations
 * @return Group box containing the widgets for the translations
 */
QGroupBox* Window::createGroupBoxTranslation() {
	QGroupBox* translationGroupBox = new QGroupBox("Translations");
	
	/* Create the button */
	leftButton = new QPushButton("<");
	rightButton = new QPushButton(">");
	upButton = new QPushButton("^");
	downButton = new QPushButton("v");
	centerButton = new QPushButton("o");
	
	/* Create the layout of the group box */
	QGridLayout* gridBox = new QGridLayout();
	
	/* Add the buttons to the layout */
	gridBox->addWidget(leftButton, 1, 0);
	gridBox->addWidget(rightButton, 1, 2);
	gridBox->addWidget(upButton, 0, 1);
	gridBox->addWidget(downButton, 2, 1);
	gridBox->addWidget(centerButton, 1, 1);
	
	translationGroupBox->setLayout(gridBox);
	return translationGroupBox;
}

/**
 * Create the group box for the rotations
 * @return Group box containing the widgets for the rotations
 */
QGroupBox* Window::createGroupBoxRotation() {
	QGroupBox* rotationGroupBox = new QGroupBox("Rotations");
	
	/* Create the sliders */
	xRotSlider = new QSlider(Qt::Horizontal);
	xRotSlider->setRange(0, 360);
	yRotSlider = new QSlider(Qt::Horizontal);
	yRotSlider->setRange(0, 360);
	zRotSlider = new QSlider(Qt::Horizontal);
	zRotSlider->setRange(0, 360);
	
	/* Create the labels for the sliders */
	QLabel* xRotLabel = new QLabel("Around X");
	QLabel* yRotLabel = new QLabel("Around Y");
	QLabel* zRotLabel = new QLabel("Around Z");
	
	/* Create the layout of the group box */
	QVBoxLayout* vbox = new QVBoxLayout();
	
	/* Add the labels and the sliders to the layout */
	vbox->addWidget(xRotLabel);
	vbox->addWidget(xRotSlider);
	vbox->addWidget(yRotLabel);
	vbox->addWidget(yRotSlider);
	vbox->addWidget(zRotLabel);
	vbox->addWidget(zRotSlider);
	
	rotationGroupBox->setLayout(vbox);
	return rotationGroupBox;
}

/** Connect the different events to the slot of the appropriate widget */
void Window::connectEvents() {
	/* Mouse behavior */
	connect(mouseComboBox, SIGNAL(currentIndexChanged(int)), renderer, SLOT(setMouseBehavior(int)));
	
	/* Type of renderer */
	connect(rendererComboBox, SIGNAL(currentIndexChanged(int)), renderer, SLOT(setTypeRenderer(int)));
	
	/* Scale factor */
	connect(scaleSpinBox, SIGNAL(valueChanged(int)), renderer, SLOT(updateScaleFactorModel(int)));
	connect(renderer, SIGNAL(scaleFactorChanged(int)), scaleSpinBox, SLOT(setValue(int)));
	
	/* Translation */
	connect(leftButton, SIGNAL(clicked()), renderer, SLOT(leftTranslation()));
	connect(rightButton, SIGNAL(clicked()), renderer, SLOT(rightTranslation()));
	connect(upButton, SIGNAL(clicked()), renderer, SLOT(upTranslation()));
	connect(downButton, SIGNAL(clicked()), renderer, SLOT(downTranslation()));
	connect(centerButton, SIGNAL(clicked()), renderer, SLOT(centerScene()));
	
	/* Rotations */
	connect(xRotSlider, SIGNAL(valueChanged(int)), renderer, SLOT(setXRotation(int)));
	connect(yRotSlider, SIGNAL(valueChanged(int)), renderer, SLOT(setYRotation(int)));
	connect(zRotSlider, SIGNAL(valueChanged(int)), renderer, SLOT(setZRotation(int)));
	connect(renderer, SIGNAL(xRotationChanged(int)), xRotSlider, SLOT(setValue(int)));
	connect(renderer, SIGNAL(yRotationChanged(int)), yRotSlider, SLOT(setValue(int)));
	connect(renderer, SIGNAL(zRotationChanged(int)), zRotSlider, SLOT(setValue(int)));
}