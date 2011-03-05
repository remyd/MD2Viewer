#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <vector>

#include <QGLWidget>

#include "md2.h"
#include "vector3d.h"

using namespace std;

class Renderer : public QGLWidget {
	Q_OBJECT

public:
	Renderer(QWidget* parent = 0);
	~Renderer();
	void setFilenameModel(QString filenameModel);
	QSize minimumSizeHint() const;
	QSize sizeHint() const;
	GLfloat getScaleFactorModel();
	MD2* md2Model;
	QPoint lastMousePosition;

public slots:
	void openMD2Model();
	void openTextureModel();
	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);
	void leftTranslation();
	void rightTranslation();
	void upTranslation();
	void downTranslation();
	void centerScene();
	void setMouseBehavior(int behavior);
	void setTypeRenderer(int renderer);
	void updateScaleFactorModel(int scaleFactor);

signals:
	void xRotationChanged(int angle);
	void yRotationChanged(int angle);
	void zRotationChanged(int angle);
	void scaleFactorChanged(int scaleFactor);

protected:
	void initializeGL();
	void initLights();
	void paintGL();
	void resizeGL(int width, int height);
	void computeNormVectors(MD2* md2, vector<Vector3d>* normFaceVect, Vector3d* normVertexVect);
	Vector3d computeMouseWorldPosition(GLfloat x, GLfloat y, GLfloat z);
	void renderFrame(int n);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	
private:
	QString filenameModel;
	QString filenameTextureModel;
	
	int width, height;
	
	static const short TRANSLATE_BEHAVIOR = 0;
	static const short ROTATE_BEHAVIOR = 1;
	static const short SCALE_BEHAVIOR = 2;
	short mouseBehavior;
	
	static const short WIRED_RENDERER = 0;
	static const short FLAT_RENDERER = 1;
	static const short SMOOTH_RENDERER = 2;
	short typeRenderer;
	
	GLint xRotation, yRotation, zRotation;
	GLfloat initialScaleFactorModel;
	GLfloat scaleFactorModel;
	
	vector<Vector3d> normFaceModel;
	Vector3d* normVertexModel;
	Vector3d oldMouseWorldPosition;
	Vector3d modelTranslation;
	
	bool textured;
	unsigned char* pixels;
	int widthModelTexture;
	int heightModelTexture;
	GLuint modelTexture;
};

#endif