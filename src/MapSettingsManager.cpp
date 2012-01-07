#include "MapSettingsManager.h"
#include "Map.h"
#include "Tileset.h"

#include "ui_MapSettingsDialog.h"

#include <QtCore/QTime>
#include <QtGui/QMessageBox>


namespace WZMapEditor
{

MapSettingsManager::MapSettingsManager(Map *map, bool newMap, QObject *parent) : QObject(parent),
	m_map(map),
	m_newMap(newMap),
	m_managerUi(new Ui::MapSettingsDialog())
{
	QDialog managerDialog(QApplication::topLevelWidgets().at(0));
	m_managerUi->setupUi(&managerDialog);
	m_managerUi->nameLineEdit->setText(m_map->name());
	m_managerUi->tilesetComboBox->addItems(Tileset::names());
	m_managerUi->tilesetComboBox->setCurrentIndex(static_cast<int>(m_map->tileset()) - 1);
	m_managerUi->widthSpinBox->setValue(m_map->size().width());
	m_managerUi->heightSpinBox->setValue(m_map->size().height());
	m_managerUi->timeEdit->setTime(QTime().addSecs(m_map->time()));
	m_managerUi->minimumXSpinBox->setValue(m_map->scrollLimits().left());
	m_managerUi->maximumXSpinBox->setValue(m_map->scrollLimits().right());
	m_managerUi->minimumYSpinBox->setValue(m_map->scrollLimits().bottom());
	m_managerUi->maximumYSpinBox->setValue(m_map->scrollLimits().top());

	connect(&managerDialog, SIGNAL(finished(int)), this, SLOT(deleteLater()));
	connect(&managerDialog, SIGNAL(accepted()), this, SLOT(save()));
	connect(m_managerUi->tilesetComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeTileset(int)));

	managerDialog.exec();
}

MapSettingsManager::~MapSettingsManager()
{
	delete m_managerUi;
}

void MapSettingsManager::changeTileset(int index)
{
	if (!m_newMap && (index != (static_cast<int>(m_map->tileset()) - 1) && QMessageBox::question(QApplication::topLevelWidgets().at(0), tr("Confirm"), tr("Do you really want to change tileset?\nThis change require reset of map information!"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::No))
	{
		m_managerUi->tilesetComboBox->setCurrentIndex(static_cast<int>(m_map->tileset()) - 1);
	}
}

void MapSettingsManager::save()
{
	QRect scrollLimits;
	scrollLimits.setLeft(m_managerUi->minimumXSpinBox->value());
	scrollLimits.setRight(m_managerUi->maximumXSpinBox->value());
	scrollLimits.setTop(m_managerUi->minimumYSpinBox->value());
	scrollLimits.setBottom(m_managerUi->maximumYSpinBox->value());

	if (m_managerUi->tilesetComboBox->currentIndex() != (static_cast<int>(m_map->tileset()) - 1))
	{
		m_map->clear();
	}

	m_map->setName(m_managerUi->nameLineEdit->text());
	m_map->setSize(QSize(m_managerUi->widthSpinBox->value(), m_managerUi->heightSpinBox->value()));
	m_map->setScrollLimits(scrollLimits);
	m_map->setTileset(static_cast<TilesetType>(m_managerUi->tilesetComboBox->currentIndex() + 1));
}

}
