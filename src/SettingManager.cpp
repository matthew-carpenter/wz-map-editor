#include "SettingManager.h"

#include <QtCore/QSettings>
#include <QtGui/QKeySequence>

namespace WZMapEditor
{

SettingManager* SettingManager::m_instance = NULL;

SettingManager::SettingManager(QObject *parent) : QObject(parent)
{
	QStringList mainToolbar;
	mainToolbar	<< "New" << "Open" << "Save" << QString() << "Fullscreen" << "3DView";

	m_defaultSettings["dataPath"] = QVariant(QString());
	m_defaultSettings["tileSize"] = QVariant(64);
	m_defaultSettings["zoomLevel"] = QVariant(100);
	m_defaultSettings["3DView"] = QVariant(true);
	m_defaultSettings["lockToolBars"] = QVariant(false);

	m_defaultSettings["toolbars/mainToolbar"] = QVariant(mainToolbar);

	m_defaultSettings["actions/New"] = QVariant(QKeySequence(QKeySequence::New).toString());
	m_defaultSettings["actions/Open"] = QVariant(QKeySequence(QKeySequence::Open).toString());
	m_defaultSettings["actions/Save"] = QVariant(QKeySequence(QKeySequence::Save).toString());
	m_defaultSettings["actions/SaveAs"] = QVariant(QKeySequence(QKeySequence::SaveAs).toString());
	m_defaultSettings["actions/Exit"] = QVariant(QKeySequence(QKeySequence::Quit).toString());
	m_defaultSettings["actions/Undo"] = QVariant(QKeySequence(QKeySequence::Undo).toString());
	m_defaultSettings["actions/Redo"] = QVariant(QKeySequence(QKeySequence::Redo).toString());
	m_defaultSettings["actions/ZoomIn"] = QVariant(QKeySequence(QKeySequence::ZoomIn).toString());
	m_defaultSettings["actions/ZoomOut"] = QVariant(QKeySequence(QKeySequence::ZoomOut).toString());
	m_defaultSettings["actions/Help"] = QVariant(QKeySequence(QKeySequence::HelpContents).toString());
	m_defaultSettings["actions/Tileset"] = QVariant(QKeySequence("Ctrl+1").toString());
	m_defaultSettings["actions/Objects"] = QVariant(QKeySequence("Ctrl+2").toString());
	m_defaultSettings["actions/Terrain"] = QVariant(QKeySequence("Ctrl+3").toString());
	m_defaultSettings["actions/Information"] = QVariant(QKeySequence("Ctrl+4").toString());
	m_defaultSettings["actions/ApplicationConfiguration"] = QVariant(QKeySequence(QKeySequence::Preferences).toString());
	m_defaultSettings["actions/Fullscreen"] = QVariant(QKeySequence("F11").toString());
}

void SettingManager::createInstance(QObject *parent)
{
	m_instance = new SettingManager(parent);
}

void SettingManager::restore(const QString &key)
{
	QSettings().setValue(key, m_instance->defaultValue(key));
}

void SettingManager::remove(const QString &key)
{
	QSettings().remove(key);
}

void SettingManager::setValue(const QString &key, const QVariant &value)
{
	QSettings().setValue(key, value);
}

QVariant SettingManager::keyValue(const QString &key)
{
	return m_defaultSettings[key];
}

QVariant SettingManager::defaultValue(const QString &key)
{
	return m_instance->keyValue(key);
}

QVariant SettingManager::value(const QString &key, const QVariant &value)
{
	const QVariant defaultKeyValue = defaultValue(key);

	return QSettings().value(key, (defaultKeyValue.isNull()?value:defaultKeyValue));
}

QStringList SettingManager::valueKeys()
{
	return m_defaultSettings.keys();
}

QStringList SettingManager::keys()
{
	return m_instance->valueKeys();
}

}
