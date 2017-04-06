#include "RecordEditor.h"
#include <DBMData/Record.h>

RecordEditor::RecordEditor(Record* record, bool editable, QWidget* parent)
	: QDialog(parent)
	, record_(record)
{
	Q_ASSERT(record_);
}


RecordEditor::~RecordEditor(void)
{
}


void RecordEditor::InitUi()
{

}
