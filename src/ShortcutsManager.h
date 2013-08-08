#ifndef SHORTCUTSMANAGER_H
#define SHORTCUTSMANAGER_H

#include <QtCore/QObject>

class QAbstractButton;
class QKeySequence;

namespace Ui
{
	class ShortcutEditorDialog;
}

namespace WZMapEditor
{

class MainWindow;

class ShortcutsManager : public QObject
{
	Q_OBJECT

public:
	ShortcutsManager(MainWindow *parent = NULL);
	~ShortcutsManager();

	bool checkShortcut(const QKeySequence &shortcut, int index);

public slots:
	void filter(const QString &filter);
	void save();
	void dialogButtonCliked(QAbstractButton *button);

private:
	Ui::ShortcutEditorDialog *m_managerUi;
	MainWindow *m_mainWindow;
};

}

#endif