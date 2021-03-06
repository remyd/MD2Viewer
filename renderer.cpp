#include <iostream>

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QtOpenGl>

#include "pcx.h"
#include "renderer.h"

using namespace std;

/**
 * Public constructor
 * @param parent Parent of the widget
 */
Renderer::Renderer(QWidget* parent) : QGLWidget(parent) {
	xRotation = 0;
	yRotation = 0;
	zRotation = 0;
	mouseBehavior = ROTATE_BEHAVIOR;
	typeRenderer = FLAT_RENDERER;
	
	initialScaleFactorModel = 0;
	scaleFactorModel = 0;
	
	md2Model = NULL;
	normVertexModel = NULL;
	modelTranslation = Vector3d(0, 0, 0);
	
	textured = false;
	pixels = NULL;
}

/** Public destructor */
Renderer::~Renderer() {
}

/**
 * Setter for the model file name and load the model
 * @param filenameModel File name of the model
 */
void Renderer::openMD2Model() {
	filenameModel = QFileDialog::getOpenFileName(this, "Choose a MD2 model", QDir::currentPath());
	
	/* If the user clicked on Cancel */
	if (filenameModel.isNull()) {
		return;
	}
	
	/* Load the model */
	md2Model = new MD2();
	if (!md2Model->LoadModel(filenameModel.toUtf8())) {
		QMessageBox::critical(this, "MD2 model", "Cannot load the MD2 model");
		md2Model = NULL;
	} else {
		// initialScaleFactorModel = (float) 10 / qMax(md2Model->skin_height, md2Model->skin_width) - 0.01;
		// scaleFactorModel = initialScaleFactorModel;
		initialScaleFactorModel = 0.1;
		scaleFactorModel = 0.1;
		normVertexModel = new Vector3d[md2Model->num_frames * md2Model->num_xyz];
		computeNormVectors(md2Model, &normFaceModel, normVertexModel);
		updateGL();
	}
}

/**
 * Load the chosen model texture
 */
void Renderer::openTextureModel() {
	filenameTextureModel = QFileDialog::getOpenFileName(this, "Choose the texture for the model", QDir::currentPath());
	
	/* If the user clicked on Cancel */
	if (filenameTextureModel.isNull()) {
		return;
	}
	
	/* Free the memory */
	if (pixels != NULL) {
		delete [] pixels;
		pixels = NULL;
	}
	
	/* Load the texture */
	LoadFilePCX(filenameTextureModel.toUtf8(), &pixels, &md2Model->skin_width, &md2Model->skin_height, false);
	
	glEnable(GL_TEXTURE_2D);
	
	/* Generate the texture */
	glGenTextures(1, &modelTexture);
	
	/* Enable the texture */
	glBindTexture(GL_TEXTURE_2D, modelTexture);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	/* Load texture data */
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, md2Model->skin_width, md2Model->skin_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	
	textured = true;
	updateGL();
}

/** @return the minimum size of the widget */
QSize Renderer::minimumSizeHint() const {
	return QSize(50, 50);
}

/** @return the size of the widget */
QSize Renderer::sizeHint() const {
	return QSize(800, 800);
}

/** @return the scale factor */
GLfloat Renderer::getScaleFactorModel() {
	return scaleFactorModel;
}

/** Initialize the openGL settings */
void Renderer::initializeGL() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	
	initLights();
}
/** Initialize the light settings */
void Renderer::initLights() {
	GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0};
	GLfloat	diffuse[] = { 1.0, 1.0, 1.0, 1.0};
	GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat position[] = { 0.5, 0.5, 0, 0.0 };
	GLfloat mat_diffuse[] = {0.6, 0.6, 0.6, 1.0 };
	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_shininess[] = {50.0};
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

/** Draw the scene */
void Renderer::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/* Do nothing if no model is loaded */
	if (md2Model == NULL) {
		return;
	}
	
	glLoadIdentity();
	glBindTexture(GL_TEXTURE_2D, modelTexture);
	
	glColor3f(1.0, 1.0, 1.0);
	
	gluLookAt(0, 0, -5, 0, 0, 0, 0, 1, 0);
	
	glPushMatrix();
	
	glTranslatef(modelTranslation.x, modelTranslation.y, 0);
	glScalef(scaleFactorModel, scaleFactorModel, scaleFactorModel);
	glRotatef(xRotation, 1.0, 0.0, 0.0);
	glRotatef(yRotation, 0.0, 1.0, 0.0);
	glRotatef(zRotation, 0.0, 0.0, 1.0);
	
	/* Render the model */
	renderFrame(0);

	glPopMatrix();
}

/**
 * Called when the widget is resized
 * @param width Current width of the widget
 * @param height Current height of the widget
 */
void Renderer::resizeGL(int width, int height) {
	this->width = width;
	this->height = height;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glViewport(0, 0, width, height);
	gluPerspective(60, (float)width / (float)height, 0.1, 10);
	
	glMatrixMode(GL_MODELVIEW);
}

/**
 * Compute the normal vector for each triangle of a MD2 model
 * @param md2 MD2 model
 * @param normVect Vector where the normal will be stored
 */
void Renderer::computeNormVectors(MD2* md2, vector<Vector3d>* normFaceVect, Vector3d* normVertexVect) {
	normFaceVect->clear();
	
	/* Compute the face normales */
	for (int i = 0; i < md2->num_tris; i++) {
		Vector3d vectA(md2->m_vertices[md2->tris[i].index_xyz[0]][0],
					   md2->m_vertices[md2->tris[i].index_xyz[0]][1],
					   md2->m_vertices[md2->tris[i].index_xyz[0]][2]);
		
		Vector3d vectB(md2->m_vertices[md2->tris[i].index_xyz[1]][0],
					   md2->m_vertices[md2->tris[i].index_xyz[1]][1],
					   md2->m_vertices[md2->tris[i].index_xyz[1]][2]);
		
		Vector3d vectC(md2->m_vertices[md2->tris[i].index_xyz[2]][0],
					   md2->m_vertices[md2->tris[i].index_xyz[2]][1],
					   md2->m_vertices[md2->tris[i].index_xyz[2]][2]);
		
		Vector3d vectCA = vectA - vectB;
		Vector3d vectCB = vectA - vectC;
		Vector3d normVector = vectCA % vectCB;
		normVector = normVector.getNormalizedVector();
		
		normFaceVect->push_back(normVector);
	}
	
	/* Compute the vertex normales */
	for (int i = 0; i < md2->num_xyz; i++) {
		int numConnection = 0;
		normVertexVect[i] = Vector3d(0, 0, 0);
		for (int j = 0; j < md2->num_tris; j++) {
			if (md2->m_vertices[i] == md2->m_vertices[md2->tris[j].index_xyz[0]] ||
					md2->m_vertices[i] == md2->m_vertices[md2->tris[j].index_xyz[1]] ||
					md2->m_vertices[i] == md2->m_vertices[md2->tris[j].index_xyz[2]]) {
				normVertexVect[i] = normVertexVect[i] + normFaceVect->at(j);
				numConnection++;
			}
		}
		normVertexVect[i] = normVertexVect[i] / numConnection;
	}
}

/**
 * Compute the mouse position in the world coordinates
 * @param x x mouse projection coordinate
 * @param y y mouse projection coordinate
 * @param z z mouse projection coordinate
 */
Vector3d Renderer::computeMouseWorldPosition(GLfloat x, GLfloat y, GLfloat z) {
	GLdouble modelView[16];
	GLdouble projection[16];
	int viewPort[4];
	GLdouble worldX, worldY, worldZ;
	
	glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewPort);
	y = viewPort[3] - y;
	
	gluUnProject(x, y, z, modelView, projection, viewPort, &worldX, &worldY, &worldZ);
	
	return Vector3d(worldX, worldY, worldZ);
}

/**
 * Render a frame of the MD2 model
 * @param n Number of the frame to render
 */
void Renderer::renderFrame(int n) {
	GLfloat s, t;
	
	if (typeRenderer == WIRED_RENDERER || typeRenderer == FLAT_RENDERER) {
		for (int i = 0; i < md2Model->num_tris; i++) {
			glBegin(GL_TRIANGLES);
			{
				glNormal3f(normFaceModel[i].x, normFaceModel[i].y, normFaceModel[i].z);
				
				if (typeRenderer == FLAT_RENDERER && textured) {
					s = (GLfloat)md2Model->texs[md2Model->tris[i].index_st[0]].u / md2Model->skin_width;
					t = (GLfloat)md2Model->texs[md2Model->tris[i].index_st[0]].v / md2Model->skin_height;
					glTexCoord2f(s, 1 - t);
				}
				glVertex3f(md2Model->m_vertices[md2Model->tris[i].index_xyz[0] + n * md2Model->num_xyz][0],
						   md2Model->m_vertices[md2Model->tris[i].index_xyz[0] + n * md2Model->num_xyz][1],
						   md2Model->m_vertices[md2Model->tris[i].index_xyz[0] + n * md2Model->num_xyz][2]);
				
				if (typeRenderer == FLAT_RENDERER && textured) {
					s = (GLfloat)md2Model->texs[md2Model->tris[i].index_st[1]].u / md2Model->skin_width;
					t = (GLfloat)md2Model->texs[md2Model->tris[i].index_st[1]].v / md2Model->skin_height;
					glTexCoord2f(s, 1 - t);
				}
				glVertex3f(md2Model->m_vertices[md2Model->tris[i].index_xyz[1] + n * md2Model->num_xyz][0],
						   md2Model->m_vertices[md2Model->tris[i].index_xyz[1] + n * md2Model->num_xyz][1],
						   md2Model->m_vertices[md2Model->tris[i].index_xyz[1] + n * md2Model->num_xyz][2]);
				
				if (typeRenderer == FLAT_RENDERER && textured) {
					s = (GLfloat)md2Model->texs[md2Model->tris[i].index_st[2]].u / md2Model->skin_width;
					t = (GLfloat)md2Model->texs[md2Model->tris[i].index_st[2]].v / md2Model->skin_height;
					glTexCoord2f(s, 1 - t);
				}
				glVertex3f(md2Model->m_vertices[md2Model->tris[i].index_xyz[2] + n * md2Model->num_xyz][0],
						   md2Model->m_vertices[md2Model->tris[i].index_xyz[2] + n * md2Model->num_xyz][1],
						   md2Model->m_vertices[md2Model->tris[i].index_xyz[2] + n * md2Model->num_xyz][2]);
			}
			glEnd();
		}
	} else {
		for (int i = 0; i < md2Model->num_tris; i++) {
			glBegin(GL_TRIANGLES);
			{
				if (textured) {
					s = (GLfloat)md2Model->texs[md2Model->tris[i].index_st[0]].u / md2Model->skin_width;
					t = (GLfloat)md2Model->texs[md2Model->tris[i].index_st[0]].v / md2Model->skin_height;
					glTexCoord2f(s, 1 - t);
				}
				
				glNormal3f(normVertexModel[md2Model->tris[i].index_xyz[0]].x, 
						   normVertexModel[md2Model->tris[i].index_xyz[0]].y,
						   normVertexModel[md2Model->tris[i].index_xyz[0]].z);
				
				glVertex3f(md2Model->m_vertices[md2Model->tris[i].index_xyz[0]][0],
						   md2Model->m_vertices[md2Model->tris[i].index_xyz[0]][1],
						   md2Model->m_vertices[md2Model->tris[i].index_xyz[0]][2]);
				
				if (textured) {
					s = (GLfloat)md2Model->texs[md2Model->tris[i].index_st[1]].u / md2Model->skin_width;
					t = (GLfloat)md2Model->texs[md2Model->tris[i].index_st[1]].v / md2Model->skin_height;
					glTexCoord2f(s, 1 - t);
				}
				
				glNormal3f(normVertexModel[md2Model->tris[i].index_xyz[1]].x, 
						   normVertexModel[md2Model->tris[i].index_xyz[1]].y,
						   normVertexModel[md2Model->tris[i].index_xyz[1]].z);
				
				glVertex3f(md2Model->m_vertices[md2Model->tris[i].index_xyz[1]][0],
						   md2Model->m_vertices[md2Model->tris[i].index_xyz[1]][1],
						   md2Model->m_vertices[md2Model->tris[i].index_xyz[1]][2]);
				
				if (textured) {
					s = (GLfloat)md2Model->texs[md2Model->tris[i].index_st[2]].u / md2Model->skin_width;
					t = (GLfloat)md2Model->texs[md2Model->tris[i].index_st[2]].v / md2Model->skin_height;
					glTexCoord2f(s, 1 - t);
				}
				
				glNormal3f(normVertexModel[md2Model->tris[i].index_xyz[2]].x, 
						   normVertexModel[md2Model->tris[i].index_xyz[2]].y,
						   normVertexModel[md2Model->tris[i].index_xyz[2]].z);
				
				glVertex3f(md2Model->m_vertices[md2Model->tris[i].index_xyz[2]][0],
						   md2Model->m_vertices[md2Model->tris[i].index_xyz[2]][1],
						   md2Model->m_vertices[md2Model->tris[i].index_xyz[2]][2]);
			}
			glEnd();
		}
	}
}

/**
 * Set the mouse behavior
 * @param behavior New mouse behavior
 */
void Renderer::setMouseBehavior(int behavior) {
	mouseBehavior = behavior;
}

/**
 * Set the rotation angle around X
 * @param angle New angle
 */
void Renderer::setXRotation(int angle) {
	xRotation = angle;
	emit xRotationChanged(angle);
	
	updateGL();
}

/**
 * Set the rotation angle around Y
 * @param angle New angle
 */
void Renderer::setYRotation(int angle) {
	yRotation = angle;
	emit yRotationChanged(angle);
	
	updateGL();
}

/**
 * Set the rotation angle around Z
 * @param angle New angle
 */
void Renderer::setZRotation(int angle) {
	zRotation = angle;
	emit zRotationChanged(angle);
	
	updateGL();
}

/** Translate the scene to the left side */
void Renderer::leftTranslation() {
	modelTranslation.x = modelTranslation.x - 0.1;
	updateGL();
}

/** Translate the scene to the right side */
void Renderer::rightTranslation() {
	modelTranslation.x = modelTranslation.x + 0.1;
	updateGL();
}

/** Translate the scene to the up side */
void Renderer::upTranslation() {
	modelTranslation.y = modelTranslation.y + 0.1;
	updateGL();
}

/** Translate the scene to the down side */
void Renderer::downTranslation() {
	modelTranslation.y = modelTranslation.y - 0.1;
	updateGL();
}

/** Center the scene */
void Renderer::centerScene() {
	modelTranslation = Vector3d(0, 0, 0);
	updateGL();
}

/**
 * Modify the current renderer and set-up openGL consequently
 * @param renderer New renderer
 */
void Renderer::setTypeRenderer(int renderer) {
	if (renderer == WIRED_RENDERER) {
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else if (renderer == FLAT_RENDERER) {
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glShadeModel(GL_FLAT);
	} else {
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glShadeModel(GL_SMOOTH);
	}
	typeRenderer = renderer;

	updateGL();
}

/**
 * Set the scale factor
 * @param scaleFactor New scale factor
 */
void Renderer::updateScaleFactorModel(int scaleFactor) {
	GLfloat factor = (float)scaleFactor / 100;
	scaleFactorModel = initialScaleFactorModel * factor;
	
	updateGL();
}

/**
 * Callback called when a mouse button is pressed
 * @param event Event catched
 */
void Renderer::mousePressEvent(QMouseEvent* event) {
	lastMousePosition = event->pos();
	
	if (mouseBehavior == TRANSLATE_BEHAVIOR) {
		GLfloat x = event->x();
		GLfloat y = event->y();
		GLfloat z;
		glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
		oldMouseWorldPosition = computeMouseWorldPosition(x, y, z);
	}
}

/**
 * Callback called when the mouse moved
 * @param event Event catched
 */
void Renderer::mouseMoveEvent(QMouseEvent* event) {
	int deltaX = event->x() - lastMousePosition.x();
	int deltaY = event->y() - lastMousePosition.y();
	
	if (mouseBehavior == ROTATE_BEHAVIOR) {
		if (event->buttons() & Qt::LeftButton) {
			setXRotation(xRotation + deltaY);
			setYRotation(yRotation + deltaX);
		} else {
			setXRotation(xRotation + deltaY);
			setZRotation(zRotation + deltaX);
		}
	} else if (mouseBehavior == SCALE_BEHAVIOR && event->buttons() & Qt::LeftButton && deltaX != 0) {
		if (scaleFactorModel + (float)deltaX / 1000 > 0) {
			scaleFactorModel = scaleFactorModel + (float)deltaX / 1000;
				
			emit scaleFactorChanged((float)scaleFactorModel / (float)initialScaleFactorModel * 100);			
			updateGL();
		}
	} else if (mouseBehavior == TRANSLATE_BEHAVIOR && event->buttons() & Qt::LeftButton) {
		Vector3d newMouseWorldPosition = computeMouseWorldPosition(event->x(), event->y(), oldMouseWorldPosition.z);
		modelTranslation = newMouseWorldPosition - oldMouseWorldPosition;
		updateGL();
	}
	
	lastMousePosition = event->pos();
}