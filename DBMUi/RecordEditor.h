#pragma once

#include "dbmui_global.h"
#include <QtWidgets>

class Record;
class RecordEditor :
	public QDialog
{
public:
	RecordEditor(Record* record, bool editable = true, QWidget* parent=0);
	virtual ~RecordEditor(void);

	void set_editable(bool editable) { editable_ = editable; }
	bool get_editable() const { return editable_; }

protected:
	Record* record_;
	bool editable_;

	void InitUi();
};

