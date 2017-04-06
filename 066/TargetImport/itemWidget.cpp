//***************************************
//	创建时间:	2015:11:8   17:33
//	文件名称: 	itemWidget.cpp
//	文件作者:	岳群磊
//	
//	功能说明:	实现输入相关部件类
//***************************************

#include "itemWidget.h"
#include <QHBoxLayout>
#include <QColorDialog>
#include <QEvent>
#include <QPainter>
#include <QApplication>
#include <QKeyEvent>

QPixmap QtPropertyBrowserUtils::brushValuePixmap(const QBrush &b)
{
	QImage img(16, 16, QImage::Format_ARGB32_Premultiplied);
	img.fill(0);

	QPainter painter(&img);
	painter.setCompositionMode(QPainter::CompositionMode_Source);
	painter.fillRect(0, 0, img.width(), img.height(), b);
	QColor color = b.color();
	if (color.alpha() != 255) { // indicate alpha by an inset
		QBrush  opaqueBrush = b;
		color.setAlpha(255);
		opaqueBrush.setColor(color);
		painter.fillRect(img.width() / 4, img.height() / 4,
			img.width() / 2, img.height() / 2, opaqueBrush);
	}
	painter.end();
	return QPixmap::fromImage(img);
}

QIcon QtPropertyBrowserUtils::brushValueIcon(const QBrush &b)
{
	return QIcon(brushValuePixmap(b));
}

QString QtPropertyBrowserUtils::colorValueText(const QColor &c)
{
	return QString("[%1, %2, %3] (%4)")
		.arg(QString::number(c.red()))
		.arg(QString::number(c.green()))
		.arg(QString::number(c.blue()))
		.arg(QString::number(c.alpha()));
}

QPixmap QtPropertyBrowserUtils::fontValuePixmap(const QFont &font)
{
	QFont f = font;
	QImage img(16, 16, QImage::Format_ARGB32_Premultiplied);
	img.fill(0);
	QPainter p(&img);
	p.setRenderHint(QPainter::TextAntialiasing, true);
	p.setRenderHint(QPainter::Antialiasing, true);
	f.setPointSize(13);
	p.setFont(f);
	QTextOption t;
	t.setAlignment(Qt::AlignCenter);
	p.drawText(QRect(0, 0, 16, 16), QString(QLatin1Char('A')), t);
	return QPixmap::fromImage(img);
}

QIcon QtPropertyBrowserUtils::fontValueIcon(const QFont &f)
{
	return QIcon(fontValuePixmap(f));
}

QString QtPropertyBrowserUtils::fontValueText(const QFont &f)
{
	return QString("[%1, %2]")
		.arg(f.family())
		.arg(f.pointSize());
}


QtColorEditWidget::QtColorEditWidget(QWidget *parent) :
QWidget(parent),
m_pixmapLabel(new QLabel),
m_label(new QLabel),
m_button(new QToolButton)
{
	QHBoxLayout *lt = new QHBoxLayout(this);
	//setupTreeViewEditorMargin(lt);
	lt->setSpacing(0);
	lt->addWidget(m_pixmapLabel);
	lt->addWidget(m_label);
	lt->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Ignored));

	m_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);
	m_button->setFixedWidth(20);
	setFocusProxy(m_button);
	setFocusPolicy(m_button->focusPolicy());
	m_button->setText(tr("..."));
	m_button->installEventFilter(this);
	connect(m_button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
	lt->addWidget(m_button);
	m_pixmapLabel->setPixmap(QtPropertyBrowserUtils::brushValuePixmap(QBrush(m_color)));
	m_label->setText(QtPropertyBrowserUtils::colorValueText(m_color));
}

void QtColorEditWidget::setValue(const QColor &c)
{
	if (m_color != c) {
		m_color = c;
		m_pixmapLabel->setPixmap(QtPropertyBrowserUtils::brushValuePixmap(QBrush(c)));
		m_label->setText(QtPropertyBrowserUtils::colorValueText(c));
	}
}

void QtColorEditWidget::buttonClicked()
{
	bool ok = false;
	QRgb oldRgba = m_color.rgba();
	QRgb newRgba = QColorDialog::getRgba(oldRgba, &ok, this);
	if (ok && newRgba != oldRgba) {
		setValue(QColor::fromRgba(newRgba));
		emit valueChanged(m_color);
	}
}

bool QtColorEditWidget::eventFilter(QObject *obj, QEvent *ev)
{
	if (obj == m_button)
	{
		switch (ev->type()) 
		{
		case QEvent::KeyPress:
		case QEvent::KeyRelease:
			{ 
				switch (static_cast<const QKeyEvent*>(ev)->key()) 
				{
				case Qt::Key_Escape:
				case Qt::Key_Enter:
				case Qt::Key_Return:
					ev->ignore();
					return true;
				default:
					break;
				}
			}
			break;
		default:
			break;
		}
	}
	return QWidget::eventFilter(obj, ev);
}
