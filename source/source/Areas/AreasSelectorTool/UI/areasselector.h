#ifndef AREASSELECTOR_H
#define AREASSELECTOR_H

#include <QtGui/QMainWindow>
#include "ui_areasselector.h"

#include "AreasKit/AreasKit.h"

class AreasSelectorTool 
	: public QMainWindow
	, public mc::AgentImpl
	, public mc::ItemImpl
{
	Q_OBJECT

public:
	
	AreasSelectorTool(QWidget *parent = 0, Qt::WFlags flags = 0);
	~AreasSelectorTool();

	// ICommon section
	DECLARE_INTERFACE_MAP()	

	// IAgent section
	virtual mc::result Invoke(mc::DispId idMember = mc::AGENTID_DEFAULT, mc::DispParamsRef dispParams = NULL, mc::IVariantWrapperRef result = NULL, mc::RefIid iid = mc::IID_IAgent);

private:

	// Private tools
	mc::result UpdateProject(Areas::IAProjectRef project);

private slots:

	// Menu events
	void NewProject();

	void LoadProject();

	void SaveProject();

	void LoadImage();

	void ShowProperties();

	void Undo();

	void Redo();

private:

	Ui::AreasSelectorClass ui;

	Areas::IAProjectPtr project_;

};

#endif // AREASSELECTOR_H