#pragma once
#include <QtWidgets>

class MaterialDialog : public QDialog
{
public:
	enum Type { kMetal, kCharge, };
	MaterialDialog(Type type, QWidget* parent);
};