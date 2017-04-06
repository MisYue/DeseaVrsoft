#pragma once
#include <QtWidgets>


enum TDirection
{
	kHor,
	kVer,
};
class TRuler : public QLabel
{
	Q_OBJECT
public:
	TRuler(QWidget* parent = NULL, TDirection dire = kVer, int min_value = -300);
	virtual ~TRuler();
	void set_min_value(int min_value) { min_value_ = min_value; }
	void set_direction(TDirection dire);
protected:
	virtual void paintEvent(QPaintEvent* ev);
private slots:
	void slot_horValueChanged(int);
	void slot_verValueChanged(int);
	void slot_verRangeChanged(int, int);
	void slot_scale(double s);
private:
	TDirection dire_;
	int hor_offset_;
	int ver_offset_;
	int max_ver_offset_;
	int min_value_;
	double scale_;
	double radio_;
};