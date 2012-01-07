#ifndef TILESET_H
#define TILESET_H

#include <QtCore/QObject>


class QPixmap;

namespace WZMapEditor
{

enum TilesetType
{
	NoTileset = 0,
	ArizonaTileset = 1, // 102
	UrbanTileset = 2, // 222
	RockiesTileset = 3 // 002
};

enum TileType
{
	GroundTile = 1,
	WaterTile = 2,
	RoadTile = 4,
	TracksTile = 8,
	CraterTile = 16,
	CliffTile = 32,
	TransitionTile = 64,
	OtherTile = 128,
	AllTiles = GroundTile | WaterTile| RoadTile | TracksTile | CraterTile | CliffTile | TransitionTile | OtherTile
};

Q_DECLARE_FLAGS(TileTypes, TileType)

struct CategoryInformation
{
	int background;
	TileType type;
	QString title;
};

struct TileInformation
{
	bool valid;
	bool visible;
	bool ignore;
	int id;
	int background;
	int category;
	int transitionNorthWest;
	int transitionNorthEast;
	int transitionSouthEast;
	int transitionSouthWest;
	TileType type;
	TilesetType tileset;
};

class Tileset : public QObject
{
	Q_OBJECT

public:
	Tileset(const QString &fileName, QObject *parent = 0);

	static void load(QObject *parent = NULL);
	static void createCache(TilesetType tileset, int size);
	static QPixmap pixmap(TileInformation tile, int size = -1);
	static QPixmap pixmap(TilesetType tileset, int tile, int size = -1);
	static Tileset* tileset(TilesetType type);
	static QStringList names();
	static TilesetType cachedTileset();
	static int cachedTextureSize();

	TilesetType type();
	QString name();
	TileInformation tile(int tile);
	QStringList categories();
	QList<TileInformation> tiles(bool includeTransitions = true, int category = 0, TileTypes types = AllTiles);

protected:
	TileType stringToType(const QString &type);

private:
	TilesetType m_type;
	QString m_name;
	QList<CategoryInformation> m_categories;
	QList<TileInformation> m_tiles;
};

}

#endif // TILESET_H
