#include "ToolBarWidget.h"
#include "ActionsManager.h"
#include "SettingsManager.h"

#include <QtWidgets/QMenu>

namespace WZMapEditor
{

ToolBarWidget::ToolBarWidget(const QString &identifier, QMainWindow *parent) : QToolBar(parent)
{
	setObjectName(identifier);
	setMovable(!SettingsManager::getValue("Window/toolBarsLocked").toBool());
	setWindowTitle(SettingsManager::getValue("ToolBars/" + objectName() + "/title").toString());
	reload();
}

void ToolBarWidget::showEvent(QShowEvent *event)
{
	emit visibilityChanged(true);

	QToolBar::showEvent(event);
}

void ToolBarWidget::hideEvent(QHideEvent *event)
{
	emit visibilityChanged(false);

	QToolBar::hideEvent(event);
}

void ToolBarWidget::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu menu(this);
	QAction *actionShow = menu.addAction(tr("Show Toolbar: %1").arg(windowTitle()));
	actionShow->setCheckable(true);
	actionShow->setChecked(true);

	QAction *actionLock = menu.addAction(tr("Lock Toolbars"));
	actionLock->setCheckable(true);
	actionLock->setChecked(!isMovable());

	menu.addAction(QIcon(":/icons/configure-toolbars.png"), tr("Configure Toolbars..."), this, SLOT(configure()));

	connect(actionShow, SIGNAL(toggled(bool)), this, SLOT(setVisible(bool)));
	connect(actionLock, SIGNAL(toggled(bool)), this, SIGNAL(requestToolBarsLock(bool)));

	menu.exec(event->globalPos());
}

void ToolBarWidget::reload()
{
	clear();

	const QStringList actions = SettingsManager::getValue("ToolBars/" + objectName() + "/actions").toStringList();

	for (int i = 0; i < actions.count(); ++i)
	{
		if (actions.at(i).isEmpty())
		{
			addSeparator();
		}
		else
		{
			addAction(ActionsManager::getAction(actions.at(i)));
		}
	}
}

void ToolBarWidget::configure()
{
	emit requestConfigure(objectName());
}

}
