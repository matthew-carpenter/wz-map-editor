#ifndef MAPINFORMATION_H
#define MAPINFORMATION_H

#include "Tileset.h"

#include <QtCore/QObject>
#include <QtCore/QPoint>
#include <QtCore/QSize>
#include <QVector>
#include <QRect>
#include <QVector3D>
#include <QFile>
#include <QDir>
#include <QDataStream>
#include <QFileInfo>

namespace WZMapEditor
{

enum FlipType
{
	FlipTypeNone = 0,
	FlipTypeVertical,
	FlipTypeHorizontal,
	FlipTypeDiagonal
};

struct Entity
{
	quint32	id;
	quint32	player;
	int 		type;	// "IMD" LND object type
	QString		name;	//char 		name[128]
	QString		script;	// char	script[32];
	QVector3D	position;
	quint32	direction;
};

enum MapObjectType
{
	MapObjectTypeFeature,
	MapObjectTypeStructure,
	MapObjectTypeDroid,
	MapObjectTypeObject
};

struct MapTile
{
	MapTile();
	bool gateway;
	int rotation;
	int texture;
	int height;
	FlipType flip;
	QPoint position;
static const quint8 MAX_TILE_TEXTURES = 255;
};

struct Gateway
{
	Gateway(){}
	Gateway(int x0, int y0, int x1, int y1);
	QPoint start;
	QPoint end;
};

class MapInformation : public QObject
{
	Q_OBJECT

public:
	MapInformation(QObject *parent = NULL);

	int deserialize(const QFileInfo& fileNfo);

	void setName(const QString &name);
	void setSize(const QSize &size);
	void setTilesetType(TilesetType tilesetType);
	QString name();
	QSize size();
	TilesetType tilesetType();
private:

	void mapClear();
	int deserializeMap(QDataStream& in);
	int deserializeGame(QDataStream& in);
	int deserializeTerrain(QDataStream& in);
	int deserializeStructures(QDataStream& in);
	int deserializeDroids(QDataStream& in);
	int deserializeFeats(QDataStream& in);

	/// Map data
	QSize m_size;
	QVector<QVector<MapTile> > m_tiles;
	QList<Gateway> m_gateways;

	/// Terrain data
	quint32 terrainVersion, numTerrainTypes;
	TilesetType m_tilesetType;

	/* LUT that returns the terrain type of a given tile texture */
	quint8 terrainTypes[MapTile::MAX_TILE_TEXTURES];

	/// Game data
	QRect m_scrollLimits;
	quint32 m_gameTime;
	quint32 m_gameType;
	QString m_levelName;
	quint32 m_playerPower[8/*MAX_PLAYERS?*/];

	/** Entity data:
	  * Structures, droids and features
	  *
	  */
	QList<Entity> m_droids, m_structures,m_features;

	int m_players;
	bool m_playerPresent[8/*MAX_PLAYERS?*/];
};

}

#endif // MAPINFORMATION_H
