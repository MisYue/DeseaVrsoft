#pragma once
#include <QtWidgets>

class MaterialLib;
class MaterialViewDlg :
	public QDialog
{
public:
	MaterialViewDlg(const MaterialLib* material_lib, QWidget* parent=0);
	virtual ~MaterialViewDlg(void);

protected:
	const MaterialLib* material_lib_;
	
};

