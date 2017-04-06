//***************************************
//	创建时间:	2015:11:8   17:33
//	文件名称: 	itemWidget.h
//	文件作者:	岳群磊
//	
//	功能说明:	定义输入的相关部件类
//***************************************

#pragma once
#include "ui_criterion.h"
#include <QtWidgets>

enum AvaliableRole
{
	ItemWidgetRole = Qt::UserRole,
	VisibleRole,
};
class IWSpinBox : public QSpinBox
{
	Q_OBJECT
public:
	IWSpinBox(QTreeWidgetItem* item, int column = 1, QWidget* parent=NULL) : _item(item), _column(column), QSpinBox(parent)
	{
		OnValueChanged("0");
		connect(this, SIGNAL(valueChanged (const QString&)), this, SLOT(OnValueChanged(const QString&)));
	}
	virtual void showEvent ( QShowEvent * event )
	{
		if(_item->data(_column, VisibleRole).toUInt() != 1)
			setVisible(false);	
	}
	virtual void hideEvent ( QShowEvent * event )
	{

	}
	public slots:
		void OnValueChanged ( const QString & text )
		{
			_item->setText(_column, text);
		}
private:
	QTreeWidgetItem* _item;
	int _column;
};

class IWDoubleSpinBox : public QDoubleSpinBox
{
	Q_OBJECT
public:
	IWDoubleSpinBox(QTreeWidgetItem* item, int column = 1, QWidget* parent=NULL) : _item(item), _column(column),QDoubleSpinBox(parent)
	{
		OnValueChanged("0.0");
		connect(this, SIGNAL(valueChanged (const QString&)), this, SLOT(OnValueChanged(const QString&)));
	}
	virtual void showEvent ( QShowEvent * event )
	{
		if(_item->data(_column, VisibleRole).toUInt() != 1)
			setVisible(false);	
	}
	virtual void hideEvent ( QShowEvent * event )
	{

	}
	public slots:
		void OnValueChanged ( const QString & text )
		{
			_item->setText(_column, text);
		}
private:
	QTreeWidgetItem* _item;
	int _column;
};

class IWLineText : public QLineEdit
{
	Q_OBJECT
public:
	IWLineText(QTreeWidgetItem* item, int column = 1, QWidget* parent=NULL) : _item(item), _column(column), QLineEdit(parent)
	{
		//connect(this, SIGNAL(textChanged(const QString&)), this, SLOT(OnValueChanged(const QString&)));
		connect(this, SIGNAL(editingFinished ()), this, SLOT(OnValueChanged()));

	}
	virtual void showEvent ( QShowEvent * event )
	{
		if(_item->data(_column, VisibleRole).toUInt() != 1)
			setVisible(false);	
	}
	virtual void hideEvent ( QShowEvent * event )
	{

	}
	public slots:
		void OnValueChanged ( const QString & text )
		{
			_item->setText(_column, text);
		}
		void OnValueChanged ( )
		{
			_item->setText(_column, text());
		}
private:
	QTreeWidgetItem* _item;
	int _column;
};


class IWComboBox : public QComboBox
{
	Q_OBJECT
public:
	IWComboBox(QTreeWidgetItem* item, int column = 1, QWidget* parent=NULL) :  _item(item), _column(column), QComboBox(parent)
	{
		connect(this, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(OnValueChanged(const QString&)));
	}
	virtual void showEvent ( QShowEvent * event )
	{
		if(_item->data(_column, VisibleRole).toUInt() != 1)
			setVisible(false);	
	}
	virtual void hideEvent ( QShowEvent * event )
	{

	}
	public slots:
		void OnValueChanged ( const QString & text )
		{
			_item->setText(_column, text);
		}
private:
	QTreeWidgetItem* _item;
	int _column;
};

class IWComboBoxEx : public QWidget
{
	Q_OBJECT
public:
	IWComboBoxEx(QTreeWidgetItem* item, int column = 1, QWidget* parent=NULL) : _item(item), _column(column), QWidget(parent)
	{
		_ui.setupUi(this);
		_ui.addCriterion->setEnabled(false);
		_ui.deleteCriterion->setEnabled(false);
		connect(_ui.addCriterion, SIGNAL(clicked()), this, SLOT(OnCmd()));
		connect(_ui.deleteCriterion, SIGNAL(clicked()), this, SLOT(OnCmd()));
		connect(_ui.comboBox, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(OnValueChanged(const QString&)));
	}
	void	addItems ( const QStringList & texts )
	{
		_ui.comboBox->addItems(texts);
	}
	void	setCurrentIndex ( int index )
	{
		_ui.comboBox->setCurrentIndex(index);
	}
	virtual void showEvent ( QShowEvent * event )
	{
		if(_item->data(_column, VisibleRole).toUInt() != 1)
		{
			setVisible(false);	
			_ui.addCriterion->setEnabled(false);
			_ui.deleteCriterion->setEnabled(false);
			_ui.comboBox->setCurrentIndex(-1);
		}
		else
		{
			int index = _ui.comboBox->findText(_text);
			index = std::max(index, 0);
			_ui.comboBox->setCurrentIndex(index);
		}
	}
	virtual void hideEvent ( QShowEvent * event )
	{

	}
	public slots:
		void OnValueChanged ( const QString & text )
		{
			if(text.size()==0)
				return ;
			_texts.clear();
			for(int i=0; i<_item->childCount(); ++i)
			{
				QTreeWidgetItem* item = _item->child(i);
				if(!item->isHidden())
					_texts.push_back(item->text(0));
			}
			if(_texts.contains(text))
			{
				_ui.addCriterion->setEnabled(false);
				_ui.deleteCriterion->setEnabled(true);
			}
			else
			{
				_ui.addCriterion->setEnabled(true);
				_ui.deleteCriterion->setEnabled(false);
			}
			_text = text;
		}
		void OnCmd()
		{
			QToolButton* btn = dynamic_cast<QToolButton*>(sender());
			if(btn == _ui.addCriterion)
			{
				emit addCmd(_text);
				_ui.addCriterion->setEnabled(false);
				_ui.deleteCriterion->setEnabled(true);
			}
			else if(btn == _ui.deleteCriterion)
			{
				emit deleteCmd(_text);
				_ui.addCriterion->setEnabled(true);
				_ui.deleteCriterion->setEnabled(false);
			}
		}
signals:
	void addCmd(const QString& text);
	void deleteCmd(const QString& text);
private:
	QTreeWidgetItem* _item;
	Ui::criterion _ui;
	QStringList _texts;
	QString _text;
	int _column;
};
class QtPropertyBrowserUtils
{
public:
	static QPixmap brushValuePixmap(const QBrush &b);
	static QIcon brushValueIcon(const QBrush &b);
	static QString colorValueText(const QColor &c);
	static QPixmap fontValuePixmap(const QFont &f);
	static QIcon fontValueIcon(const QFont &f);
	static QString fontValueText(const QFont &f);
};

class QtColorEditWidget : public QWidget {
	Q_OBJECT
public:
	QtColorEditWidget(QWidget *parent=NULL);
	bool eventFilter(QObject *obj, QEvent *ev);
public Q_SLOTS:
	void setValue(const QColor &value);
private Q_SLOTS:
	void buttonClicked();
Q_SIGNALS:
	void valueChanged(const QColor &value);

private:
	QColor m_color;
	QLabel *m_pixmapLabel;
	QLabel *m_label;
	QToolButton *m_button;
};
