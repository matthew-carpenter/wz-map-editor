#ifndef MAP3DVIEWWIDGET_H
#define MAP3DVIEWWIDGET_H

//#define GL_GLEXT_PROTOTYPES 1

#include <QtCore/QHash>
#include <QtWidgets/QWidget>
//#include <QtOpenGL/QGLWidget>
//#include <GL/glu.h>
//#include "GL/glext.h"

#include <vector>

#include "Tileset.h"
#include "Map.h"

namespace WZMapEditor
{

class Map;

struct Vertex
{
//	GLfloat pos[3];
//	GLfloat tex[2];
};

struct Entity
{
	//Object(Vertex v[4], GLuint t, QPoint f, float r);
	EntityType type;

	// position on wz map
	int x;
	int y;

	bool hovered;
	bool selected;

	std::vector<Vertex> vertex; // object verticles

//	GLuint texid;
	QPoint flip;
	float rotation;
};

class Map3DViewWidget : public QWidget
{
	Q_OBJECT

public:
	Map3DViewWidget(QWidget *parent = NULL);

	void setMap(Map *data);

	void _glSelect(int x, int y);
//	void _listHits(GLint hits, GLuint *names);

	Map* getMap();
	QSize minimumSizeHint() const;
	QSize sizeHint() const;
	int getZoom();

	void setVBO();

public slots:
	void setZoom(qreal getZoom);

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	void wheelEvent(QWheelEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

private:
	Map *m_map;
	bool m_moving;
	bool m_rotating;
	int m_rotationX;
	int m_rotationY;
	int m_rotationZ;
	int m_currentx;
	int m_currenty;
	int m_currentz;
	float m_offsetX;
	float m_offsetY;
	int m_zoom;

	std::vector<Entity> m_entities;

	struct used_texture
	{
		TilesetType tileset;
		int tiletexture;
//		GLuint texid;
	};
	std::vector<used_texture> m_used_textures;

	std::vector<Vertex> m_vboData;
	bool m_OGLinitialized;

signals:
	void cooridantesChanged(int x, int y, int z);
	void zoomChanged(int getZoom);
};

}

#endif
