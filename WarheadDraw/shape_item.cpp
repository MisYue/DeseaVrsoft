#include "shape_item.h"
#include <WarheadModelData/WarheadModelWrap.h>
#include <WarheadModelData/warhead_layer.h>
#include <WarheadModelData/warhead_section.h>
#include <WarheadModelData/warhead_fragment_layer.h>
#include <WarheadModelData/warhead_model.h>
#include <BIT2DCSSupport/Bit_2DCSWithExpAndUS.h>
#include <BasicTool/expandqtcore.h>
#include <QtGui>

QFont ShapeItem::s_font_("Times", 9, QFont::Normal);

ShapeItem::ShapeItem(WarheadModelWrap* model_wrap, QGraphicsItem* parent)
	: QGraphicsItem(parent)
	, model_wrap_(model_wrap)
{
	setFlag(ItemIsSelectable, true);
	setAcceptDrops(true);
	setAcceptHoverEvents(true);
	setAcceptedMouseButtons(Qt::LeftButton);
}
ShapeItem::~ShapeItem()
{
};
void ShapeItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	QGraphicsItem::mousePressEvent(event);
}
void ShapeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{

}
void ShapeItem::hoverMoveEvent(QGraphicsSceneHoverEvent * event)
{
	QGraphicsItem::hoverMoveEvent(event);
}
void ShapeItem::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{

	QGraphicsItem::mouseMoveEvent(event);
}

LayerItem::LayerItem(WarheadModelWrap* model_wrap, WarheadLayer* layer, WarheadSection* section, QGraphicsItem* parent)
	: layer_(layer)
	, section_(section)
	, ShapeItem(model_wrap, parent)
{
	Q_ASSERT_X(layer_, "LayerItem::LayerItem", "layer!=NULL");
	Update();
}
QRectF LayerItem::boundingRect() const
{
	return path_.boundingRect();
}
void LayerItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QPen pen;
	pen.setWidthF(1);
	pen.setColor(Qt::black);
	painter->setPen(pen);
	//绘制轮廓线
	painter->drawPath(path_);
	//绘制填充区域
	pen.setWidthF(0.1);
	QColor fill_color = layer_->get_layer_type() == kCharge ? Qt::yellow : Qt::green;
	pen.setColor(fill_color);
	painter->setPen(pen);
	painter->setBrush(brush_);
	painter->drawPolygon(points_top_);
	painter->drawPolygon(points_bottom_);
}

QPainterPath LayerItem::shape() const
{
	QPainterPath shape_path;
	shape_path.addPolygon(points_top_);
	shape_path.addPolygon(points_bottom_);
	return shape_path;
}

void LayerItem::Update()
{
	const ShapeDescribe* shape_describe = layer_->get_shape_describe();
	Q_ASSERT_X(shape_describe, "LayerItem::Update()", "shape_describe != NULL");
	CurveEquation curve_equation(shape_describe);
	QVector<Bit_Point2D> points;
	double length_coef = model_wrap_->get_structure()->get_cs().Get_UnitSystem().Get_LengthCoefficient();
	curve_equation.DescreteCurve(points, shape_describe->get_shape_length() * length_coef);
	points_top_.clear();
	points_top_.reserve(points.size());
	for(int i=0, n=points.size(); i<n; ++i)
		points_top_.push_back(QPointF(points[i].Get_x(), -points[i].Get_y()) * length_coef);
	if(section_ == 0 || layer_ == section_->get_layers().first())
		UpdateInnerMostLayer();
	else
		UpdateOuterLayer();
	prepareGeometryChange();
	UpdateBrush();
	update();
}

void LayerItem::UpdateBrush()
{
	switch(layer_->get_layer_type())
	{
	case kShell:
		brush_ = QBrush(Qt::BDiagPattern/*Dense6Pattern*/);
		//brush_.setColor(Qt::green);
		break;
	case kSphereFragment:
		brush_ = QBrush();
		break;
	case kCharge:
		brush_ = QBrush(Qt::yellow);
		break;
	}
}

void LayerItem::UpdateInnerMostLayer()
{
	QPainterPath path;
	int n1 = points_top_.size();
	points_top_.resize(n1*2);
	int n2 = points_top_.size();
	for(int i=n1, j=n1-1; i<n2; ++i, --j)
	{
		points_top_[i].rx() = points_top_[j].x();
		points_top_[i].ry() = -points_top_[j].y();
	}
	for(int i=0, k=n1-1; i<k; ++i)
	{
		path.moveTo(points_top_[i]); 
		path.lineTo(points_top_[i+1]);
	}
	for(int i=n1, k=n2-1; i<k; ++i)
	{
		path.moveTo(points_top_[i]); 
		path.lineTo(points_top_[i+1]);
	}
	path_ = path;
}
void LayerItem::UpdateOuterLayer()
{
	double length_coef = model_wrap_->get_structure()->get_cs().Get_UnitSystem().Get_LengthCoefficient();
	QList<WarheadLayer*> layers = section_->get_layers();
	QList<WarheadLayer*>::iterator iter = layers.begin();
	double left_h = 0;
	double right_h = 0;
	ShapeThickness thickness;
	while(++iter != layers.end())
	{
		if((*iter) == layer_)
			break;
		thickness = (*iter)->get_thickness();
		left_h += thickness.left;
		right_h += thickness.right;
	}
	left_h *= length_coef;
	right_h *= length_coef;

	thickness = layer_->get_thickness();
	thickness.left *= length_coef;
	thickness.right *= length_coef;

	int n1 = points_top_.size();
	points_top_.resize(n1*2);
	int n2 = points_top_.size();
	double ddh_1 = right_h - left_h;
	if(n1 > 1)
		ddh_1 = (right_h - left_h)/(n1-1);
	double dh = left_h;
	for(int i=0; i<n1; ++i)
	{
		points_top_[i].ry() -= dh;
		dh += ddh_1;
	}
	double current_left_h = thickness.left;
	double current_right_h = thickness.right;
	double ddh_2 = current_right_h - current_left_h;
	if(n1>1)
		ddh_2 = (current_left_h - current_right_h) / (n1-1);
	dh = current_right_h;
	for(int i=n1, j=n1-1; i<n2; ++i, --j)
	{
		points_top_[i].rx() = points_top_[j].x();
		points_top_[i].ry() = points_top_[j].y() - dh;
		dh += ddh_2;
	}

	points_bottom_ = points_top_;
	for(int i=0; i<n2; ++i)
		points_bottom_[i].ry() = -points_bottom_[i].y();
	QPainterPath path;
	for(int i=0, k=n2/2-1; i<k; ++i)
	{
		path.moveTo(points_top_[i]);
		path.lineTo(points_top_[i+1]);
	}
	for(int i=n2/2, k=n2-1; i<k; ++i)
	{
		path.moveTo(points_top_[i]);
		path.lineTo(points_top_[i+1]);
	}
	for(int i=0, k=n2/2-1; i<k; ++i)
	{
		path.moveTo(points_bottom_[i]);
		path.lineTo(points_bottom_[i+1]);
	}
	for(int i=n2/2, k=n2-1; i<k; ++i)
	{
		path.moveTo(points_bottom_[i]);
		path.lineTo(points_bottom_[i+1]);
	}
	path_ = path;
}


EndCapItem::EndCapItem(WarheadModelWrap* model_wrap, WarheadEndCap* end_cap, QGraphicsItem* parent)
	: ShapeItem(model_wrap, parent)
	, end_cap_(end_cap)
{
	Q_ASSERT_X(end_cap_, "EndCapItem::EndCapItem", "end_cap!=NULL");
	Update();
}
QRectF EndCapItem::boundingRect() const
{
	return rect_;
}
void EndCapItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QPen pen;
	pen.setWidthF(1);
	pen.setColor(Qt::black);
	painter->setPen(pen);
	QBrush brush(Qt::gray/*, Qt::Dense2Pattern*/);
	painter->setBrush(brush);
	painter->drawRect(rect_);

}
void EndCapItem::Update()
{
	const ShapeDescribe* shape = end_cap_->get_shape_describe();
	const CylinderDescribe* cylinder = dynamic_cast<const CylinderDescribe*>(shape);
	Q_ASSERT(cylinder);
	double length_coef = model_wrap_->get_structure()->get_cs().Get_UnitSystem().Get_LengthCoefficient();
	Bit_Point2D datum_point = shape->get_datum_point() * length_coef;
	double r = cylinder->get_r() * length_coef;
	double length = cylinder->get_length() * length_coef;
	QPointF top_left(datum_point.Get_x(), -datum_point.Get_y()-r);
	rect_ = QRectF(top_left, QSizeF(length, r*2));

	prepareGeometryChange();
	update();
}

FirePointItem::FirePointItem(WarheadModelWrap* model_wrap, WarheadFirePoint* fire_point, QGraphicsItem* parent)
	: ShapeItem(model_wrap, parent)
	, fire_point_(fire_point)
	, d_(10)
{
	Q_ASSERT_X(fire_point_, "FirePointItem::FirePointItem", "fire_point!=NULL");
	Update();
}
QRectF FirePointItem::boundingRect() const
{
	return path_.boundingRect();
}
QPainterPath FirePointItem::shape() const
{
	return path_;
}
void FirePointItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QBrush brush(Qt::red);
	painter->setBrush(brush);
	painter->drawPath(path_);
	painter->drawText(boundingRect(), Qt::AlignCenter, QString::number(fire_point_->get_id()+1));
}

void FirePointItem::Update()
{
	QPainterPath path;
	double length_coef = model_wrap_->get_structure()->get_cs().Get_UnitSystem().Get_LengthCoefficient();
	Bit_Point2D c2d = fire_point_->get_pos() * length_coef;
	path.addEllipse(QPointF(c2d.Get_x(), -c2d.Get_y()), d_, d_);
	path_ = path;
	prepareGeometryChange();
	update();
}
ModelCoordItem::ModelCoordItem(WarheadModelWrap* model_wrap, Bit_2DCSWithExpAndUS* cs, QGraphicsItem* parent)
	: ShapeItem(model_wrap, parent), cs_(cs)
{
	cs_ = cs;
	Q_ASSERT_X(cs_, "ModelCoordItem::ModelCoordItem", "cs!=NULL");
	//setZValue(1);
	Update();
}
QRectF ModelCoordItem::boundingRect() const
{
	return path_.boundingRect();
}
void ModelCoordItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QPen pen;
	pen.setStyle(Qt::SolidLine);
	pen.setWidthF(1);
	pen.setColor(Qt::red);
	painter->setPen(pen);
	painter->drawPath(path_);
}
QPainterPath ModelCoordItem::shape() const
{
	return path_;
}
void ModelCoordItem::Update()
{
	Bit_2DCS cs = cs_->Get_2DCSWithExplain().Get_CS();
	double length_coef = model_wrap_->get_structure()->get_cs().Get_UnitSystem().Get_LengthCoefficient();
	Bit_Point2D origin_p = cs.Get_OriginalPoint() * length_coef;

	Bit_Point2D x_v = cs.Get_XAixVector();
	Bit_Point2D y_v = cs.Get_YAixVector();

	float x_axis_l = 50;
	float y_axis_l = 50;

	QPointF origin(origin_p.Get_x(), -origin_p.Get_y());

	Bit_Point2D x_end_v_p2d = x_v * x_axis_l;
	Bit_Point2D y_end_v_p2d = y_v * y_axis_l;

	QLineF x_axis(origin, origin + QPointF(x_end_v_p2d.Get_x(), -x_end_v_p2d.Get_y()));
	QLineF y_axis(origin + QPointF(y_end_v_p2d.Get_x(), -y_end_v_p2d.Get_y()), origin);

	path_ = QPainterPath();
	path_.moveTo(x_axis.p1());
	path_.lineTo(x_axis.p2());
	path_.moveTo(y_axis.p1());
	path_.lineTo(y_axis.p2());

	QFontMetricsF metrics(s_font_);
	QRectF text_rect = metrics.boundingRect("X");

	float axis_1 = 10;
	float axis_2 = 5;
	float text_space = 3;

	float v = 1;
	if(x_v.Get_x() == -1 && x_v.Get_y() == 0)
		v = -1;
	//X轴箭头
	QPointF x_end = x_axis.p2();
	path_.moveTo(x_end);
	path_.lineTo(x_end - QPointF(axis_1*v, axis_2));
	path_.moveTo(x_end);
	path_.lineTo(x_end - QPointF(axis_1*v, -axis_2));
	path_.addText(x_end + QPointF(v==1 ? text_space : -text_space-text_rect.width(), text_rect.height()/2), s_font_, "X");
	//Y轴箭头
	QPointF y_end = y_axis.p1();
	path_.moveTo(y_end);
	path_.lineTo(y_end + QPointF(axis_2, axis_1*v));
	path_.moveTo(y_end);
	path_.lineTo(y_end + QPointF(-axis_2, axis_1*v));
	path_.addText(y_end + QPointF(-text_rect.width()/2, v==1 ? -text_space : text_space+text_rect.height()), s_font_, "Y");
}


SphereFragmentLayerItem::SphereFragmentLayerItem(WarheadModelWrap* model_wrap, SphereFragmentLayer* layer, WarheadSection* section, QGraphicsItem* parent)
	: LayerItem(model_wrap, layer, section, parent)
	, frag_layer_(layer)
{
	Q_ASSERT_X(layer_, "SphereFragmentLayerItem::SphereFragmentLayerItem", "layer!=NULL");
	Update();
}

void SphereFragmentLayerItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QPen pen;
	//pen.setColor(isSelected() ? Qt::green : Qt::black);
	painter->setPen(pen);
	painter->drawPath(path_);
}
QPainterPath SphereFragmentLayerItem::shape() const
{
	return path_;
}
void SphereFragmentLayerItem::Update()
{
	double length_coef = model_wrap_->get_structure()->get_cs().Get_UnitSystem().Get_LengthCoefficient();
	frag_layer_->UpdateFragments();
	QPainterPath path;
	const Fragments& frags = frag_layer_->get_fragments();
	double radius = frag_layer_->get_r()*length_coef;
	foreach(const LayerFrags& layer_frags, frags)
	{
		foreach(const CircleFrags& circle_frags, layer_frags)
		{
			const CoordinatesPosition& frag_center = circle_frags.first();
			QPointF center(frag_center.Get_x(), -frag_center.Get_y());
			center *= length_coef;
			QRectF rect(center - QPointF(radius, radius), QSizeF(2 * radius, 2 * radius));
			path.moveTo((rect.topRight() + rect.bottomRight())/2);
			path.arcTo(rect, 0, 360);
		}
	}

	foreach(const LayerFrags& layer_frags, frags)
	{
		foreach(const CircleFrags& circle_frags, layer_frags)
		{
			const CoordinatesPosition& frag_center = circle_frags.first();
			QPointF center(frag_center.Get_x(), frag_center.Get_y());
			center *= length_coef;
			QRectF rect(center - QPointF(radius, radius), QSizeF(2 * radius, 2 * radius));
			path.moveTo((rect.topRight() + rect.bottomRight())/2);
			path.arcTo(rect, 0, 360);
		}
	}
	path_ = path;
	prepareGeometryChange();
	update();
}

//标注字符串
static QString GetLabel(double d, int precision_hint = 6)
{
	QString label = QString::number(d, 'f', precision_hint);
	int i = 0;
	for(i=label.size()-1; i>-1; i--)
	{
		if(label[i] != '0')
			break;
	}
	if(label[i] == '.')
		--i;
	return label.left(i+1);
}
static QString GetLabel(int i)
{
	return QString::number(i);
}

LabelItem::LabelItem(WarheadModelWrap* model_wrap, NullItem* shape_item_parent, QGraphicsItem* parent)
	: shape_item_parent_(shape_item_parent)
	, ShapeItem(model_wrap, parent)
	, model_(model_wrap->get_structure())
	, info_node_(0)
	, a_x_(7)
	, a_y_(3)
{
	Q_ASSERT_X(shape_item_parent_, "LabelItem::LabelItem", "shape_item_parent!=NULL");
	Q_ASSERT_X(model_, "LabelItem::LabelItem", "model!=NULL");
	Update();
}

void LabelItem::ShowNodeInfo(WarheadNode* node)
{
	info_node_ = node;
	UpdateNodeInfo();
}
void LabelItem::UpdateNodeInfo()
{
	QPainterPath path;
	if(info_node_)
	{
		if(WarheadLayer* layer = dynamic_cast<WarheadLayer*>(info_node_))
		{
			double length_coef = model_wrap_->get_structure()->get_cs().Get_UnitSystem().Get_LengthCoefficient();
			QRectF rect = shape_item_parent_->childrenBoundingRect();
			//获取模型高度
			double model_h = rect.height()/2;
			double x = layer->get_shape_describe()->get_datum_point().Get_x()*length_coef;
			AddVerticalLabel4(path, QPointF(x, -model_h-30), CreateNodeLabel(info_node_));
		}
	}
	node_info_path_ = path;
	prepareGeometryChange();
	update();
}

void LabelItem::Update()
{
	double length_coef = model_wrap_->get_structure()->get_cs().Get_UnitSystem().Get_LengthCoefficient();
	QRectF rect = shape_item_parent_->childrenBoundingRect();
	//获取模型高度
	double model_h = rect.height()/2;
	model_->UpdateLength();
	double model_l = model_->get_character_data().length * length_coef;

	int precision_hint = model_wrap_->GetLengthPrecisionHint();
	QPainterPath path;
	double h_line_v = 40;
	double s_h_v = 10;
	if(model_h != 0 || model_l != 0)
	{
		QList<WarheadSection*> sections = model_->get_sections();
		double l_h = 0;
		double r_h = 0;
		double l_x = 0;
		double r_x = model_l;
		//左端盖
		if(WarheadEndCap* left_end_cap = model_->get_left_end_cap())
		{
			l_h = left_end_cap->get_r();
			AddVerticalLabel(path, QPointF(0, model_h), GetLabel(left_end_cap->get_length(), precision_hint), h_line_v, true);

		}
		else if(sections.size()>0)
		{
			WarheadSection* first_section = sections.front();
			l_h = first_section->get_shape_describe()->get_shape_left_half_height();
		}
		//右端盖
		if(WarheadEndCap* right_end_cap = model_->get_right_end_cap())
		{
			r_h = right_end_cap->get_r();
			AddVerticalLabel(path, QPointF(model_l, model_h), GetLabel(right_end_cap->get_length(), precision_hint), h_line_v, false);

		}
		else if(sections.size()>0)
		{
			WarheadSection* second_section = sections.back();
			r_h = second_section->get_shape_describe()->get_shape_right_half_height();
		}
		 if(sections.size()>0)
		 {
			 AddVerticalLabel3(path, QPointF(l_x, -l_h * length_coef), GetLabel(l_h*2, precision_hint), l_h*2* length_coef, true);
			 AddVerticalLabel3(path, QPointF(r_x, -r_h * length_coef), GetLabel(r_h*2, precision_hint), r_h*2* length_coef, false);
		 }
		foreach(WarheadSection* section, sections)
		{
			const ShapeDescribe* shape = section->get_shape_describe();
			double x = shape->get_datum_point().Get_x() * length_coef;
			double l =shape->get_shape_length() * length_coef;
			AddHorizontalLabel(path, QPointF(x, model_h), QPointF(x+l, model_h), GetLabel(shape->get_shape_length(), precision_hint), h_line_v);
			//AddVerticalLabel2(path, QPointF(x, -section->get_outer_left_half_height()*length_coef), model_h+20, CreateSectionLabel(section));
		}
		AddHorizontalLabel(path, QPointF(0, model_h+h_line_v+s_h_v), QPointF(model_l, model_h+h_line_v+s_h_v), GetLabel(model_->get_character_data().length, precision_hint), h_line_v);

	}
	path_ = path;
	UpdateNodeInfo();
	prepareGeometryChange();
	update();
}
QRectF LabelItem::boundingRect() const
{
	return path_.boundingRect().united(node_info_path_.boundingRect());
}
void LabelItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->setFont(s_font_);
	painter->drawPath(path_);
	painter->drawPath(node_info_path_);
}

void LabelItem::AddHorizontalLabel(QPainterPath& path, const QPointF& p1, const QPointF& p2, const QString& label, double h)
{
	QFontMetricsF metrics(s_font_);
	QRectF text_rect = metrics.boundingRect(label);
	double space_v = 15;
	double label_line_v = h;
	double text_space = 10;
	double length = sqrt(pow(p1.x() - p2.x(), 2) + pow(p1.y() - p2.y(), 2));
	double h_line_l = (length-text_rect.width() - text_space) / 2;
	bool arrow = true;
	if(h_line_l < 5)
	{
		text_space = 0;
		h_line_l = (length-text_rect.width() - text_space) / 2;
		arrow = false;
	}

	QVector<QPointF> points;
	points.reserve(16);

	QPointF p11(p1 + QPointF(0, space_v));	points.push_back(p11);
	QPointF p12(p11 + QPointF(0, label_line_v));	points.push_back(p12);
	QPointF p13((p11+p12)/2);	points.push_back(p13);
	QPointF p14(p13 + QPointF(h_line_l, 0));	points.push_back(p14);
	if(arrow)
	{
		QPointF p15(p13);	points.push_back(p15);
		QPointF p16(p15 + QPointF(a_x_, -a_y_));	points.push_back(p16);
		QPointF p17(p13);	points.push_back(p17);
		QPointF p18(p17 + QPointF(a_x_, a_y_));	points.push_back(p18);
	}

	QPointF p21(p2 + QPointF(0, space_v));	points.push_back(p21);
	QPointF p22(p21 + QPointF(0, label_line_v));	points.push_back(p22);
	QPointF p23((p21+p22)/2);	points.push_back(p23);
	QPointF p24(p23 + QPointF(-h_line_l, 0));	points.push_back(p24);
	if(arrow)
	{
		QPointF p25(p23);	points.push_back(p25);
		QPointF p26(p25 + QPointF(-a_x_, -a_y_));	points.push_back(p26);
		QPointF p27(p23);	points.push_back(p27);
		QPointF p28(p27 + QPointF(-a_x_, a_y_));	points.push_back(p28);
	}


	for(int i=0; i<points.size(); i+=2)
	{
		path.moveTo(points[i]);
		path.lineTo(points[i+1]);
	}

	path.addText(p14+QPointF(text_space/2, text_rect.height()/2), s_font_, label);

}

void LabelItem::AddVerticalLabel(QPainterPath& path, const QPointF& p, const QString& label, double h, bool is_left)
{
	QFontMetricsF metrics(s_font_);
	QRectF text_rect = metrics.boundingRect(label);
	QVector<QPointF> points;
	points.reserve(8);
	double space_v = 15;
	double label_line_v = h;
	double h_line_l = 30;

	QPointF p11(p + QPointF(0, space_v));	points.push_back(p11);
	QPointF p12(p11 + QPointF(0, label_line_v));	points.push_back(p12);
	QPointF p13((p11+p12)/2);	points.push_back(p13);
	if(is_left)
	{
		QPointF p14(p13 - QPointF(h_line_l, 0));	 points.push_back(p14);
		QPointF p15(p13);	points.push_back(p15);
		QPointF p16(p15 + QPointF(-a_x_, -a_y_));	points.push_back(p16);
		QPointF p17(p13);	points.push_back(p17);
		QPointF p18(p17 + QPointF(-a_x_, a_y_));	points.push_back(p18);
		path.addText((p13+p14)/2 + QPointF(-text_rect.width(), -3), s_font_, label);
	}
	else
	{
		QPointF p14(p13 + QPointF(h_line_l, 0));	 points.push_back(p14);
		QPointF p15(p13);	points.push_back(p15);
		QPointF p16(p15 + QPointF(a_x_, -a_y_));	points.push_back(p16);
		QPointF p17(p13);	points.push_back(p17);
		QPointF p18(p17 + QPointF(a_x_, a_y_));	points.push_back(p18);
		path.addText((p13+p14)/2 + QPointF(0, -3), s_font_, label);
	}
	for(int i=0; i<points.size(); i+=2)
	{
		path.moveTo(points[i]);
		path.lineTo(points[i+1]);
	}
}

void LabelItem::AddVerticalLabel2(QPainterPath& path, const QPointF& p, double h, const QStringList& label)
{
	if(label.size() == 0)
		return ;
	double label_line_v = 0;
	QPointF p11(p.x(), -h);

	QPointF point(p11 + QPointF(2, 0));
	foreach(const QString& text, label)
	{
		QFontMetricsF metrics(s_font_);
		QRectF text_rect = metrics.boundingRect(text);
		path.addText(point + QPointF(0, -text_rect.height()), s_font_, text);
		label_line_v += text_rect.height()+2;
		point = QPointF(point.x(), p11.y()-label_line_v);

	}
	QPointF p12(p11 - QPointF(0, label_line_v+20));
	path.moveTo(p);
	path.lineTo(p12);

}

void LabelItem::AddVerticalLabel3(QPainterPath& path, const QPointF& p, const QString& label, double h, bool is_left)
{
	QFontMetricsF metrics(s_font_);
	QRectF text_rect = metrics.boundingRect(label);

	double label_line_h = 40;
	double space_h = (text_rect.width() - label_line_h)/2;
	space_h = space_h < 3 ? 3 : space_h;
	double text_space = 8;
	double h_line_l = (h-text_rect.height() - text_space) / 2;
	int temp = a_x_;
	int a_x_ = a_y_;
	int a_y_ = temp;
	QVector<QPointF> points;
	points.reserve(16);
	//考虑起爆点在端点，留一定位置
	double fire_space = 5;
	space_h += fire_space*2;

	int coef = 1;
	if(is_left)
		coef = -1;
	QPointF p11(p + QPointF(coef*space_h, 0));	points.push_back(p11);
	QPointF p12(p11 + QPointF(coef*label_line_h, 0));	points.push_back(p12);
	QPointF p13((p11+p12)/2);	points.push_back(p13);
	QPointF p14(p13 + QPointF(0, h_line_l));	points.push_back(p14);
	QPointF p15(p13);	points.push_back(p15);
	QPointF p16(p15 + QPointF(a_x_, a_y_));	points.push_back(p16);
	QPointF p17(p13);	points.push_back(p17);
	QPointF p18(p17 + QPointF(-a_x_, a_y_));	points.push_back(p18);
	QPointF p21(p11 + QPointF(0, h));	points.push_back(p21);
	QPointF p22(p21 + QPointF(coef*label_line_h, 0));	points.push_back(p22);
	QPointF p23((p21+p22)/2);	points.push_back(p23);
	QPointF p24(p23 + QPointF(0, -h_line_l));	points.push_back(p24);
	QPointF p25(p23);	points.push_back(p25);
	QPointF p26(p25 + QPointF(a_x_, -a_y_));	points.push_back(p26);
	QPointF p27(p23);	points.push_back(p27);
	QPointF p28(p27 + QPointF(-a_x_, -a_y_));	points.push_back(p28);

	for(int i=0; i<points.size(); i+=2)
	{
		path.moveTo(points[i]);
		path.lineTo(points[i+1]);
	}
	path.addText(p24+QPointF(-text_rect.width()/2+coef*fire_space, -text_space/2), s_font_, label);
}
void LabelItem::AddVerticalLabel4(QPainterPath& path, const QPointF& p, const QStringList& label)
{
	if(label.size() == 0)
		return ;
	double label_line_v = 0;
	QPointF p11 = p;

	QPointF point(p11 + QPointF(2, 0));
	//foreach(const QString& text, label)
	for(int i=label.size()-1; i>-1; --i)
	{
		QString text = label[i];
		QFontMetricsF metrics(s_font_);
		QRectF text_rect = metrics.boundingRect(text);
		path.addText(point + QPointF(0, -text_rect.height()), s_font_, text);
		label_line_v += text_rect.height()+2;
		point = QPointF(point.x(), p11.y()-label_line_v);
	}
}
QStringList LabelItem::CreateSectionLabel(WarheadSection* section)
{
	const ShapeDescribe* shape = section->get_shape_describe();
	QString param = shape->GetShapeDescribe();
	QStringList params = param.split(',');
	param.clear();
	for(int i=2; i<params.size(); ++i)
	{
		if(!param.isEmpty())
			param += ",";
		param += params[i];
	}
	QString shape_name;
	switch(shape->get_shape_type())
	{
	case kOval: shape_name = ExpandQtCore::fromGBK("卵形"); break;
	case kCylinder: shape_name = ExpandQtCore::fromGBK("圆柱"); break;
	case kCone: shape_name = ExpandQtCore::fromGBK("圆台"); break;
	default: Q_ASSERT(0);
	}
	QStringList result;
	result.push_back(shape_name + "," + param);

	QList<WarheadLayer*> layers = section->get_layers();
	QList<WarheadLayer*>::iterator iter = layers.begin();
	int precision_hint = model_wrap_->GetLengthPrecisionHint();
	while(++iter != layers.end())
	{
		if((*iter)->get_layer_type() == kSphereFragment)
		{
			SphereFragmentLayer* frag_layer = dynamic_cast<SphereFragmentLayer*>(*iter);
			Q_ASSERT(frag_layer);
			result.push_back(
				ExpandQtCore::fromGBK("破片:") + 
				GetLabel((int)frag_layer->get_layer_num()) + "," + 
				GetLabel(frag_layer->get_r(), precision_hint) + "," + 
				GetLabel((int)frag_layer->get_frag_num()));
		}
		else
		{
			ShapeThickness thickness = (*iter)->get_thickness();
			result.push_back(ExpandQtCore::fromGBK("壳体,") + 
				GetLabel(thickness.left, precision_hint) + "," + 
				GetLabel(thickness.right, precision_hint));
		}
	}
	return result;
}

QStringList LabelItem::CreateNodeLabel(WarheadNode* node)
{
	QStringList result;
	int precision_hint = model_wrap_->GetLengthPrecisionHint();
	if(WarheadLayer* layer = dynamic_cast<WarheadLayer*>(node))
	{
		switch(layer->get_layer_type())
		{
		case kCharge:
			{
				const ShapeDescribe* shape = layer->get_shape_describe();
				QString param = shape->GetShapeDescribe();
				QStringList params = param.split(',');
				switch(shape->get_shape_type())
				{
				case kOval:
					Q_ASSERT(params.size()==6);
					result.push_back(ExpandQtCore::fromGBK("形状:卵形"));
					result.push_back(ExpandQtCore::fromGBK("左端高:") + params[2]);
					result.push_back(ExpandQtCore::fromGBK("右端高:") + params[3]);
					result.push_back(ExpandQtCore::fromGBK("半径:") + params[4]);
					result.push_back(ExpandQtCore::fromGBK("长度:") + params[5]);
					break;
				case kCylinder:
					Q_ASSERT(params.size()==4);
					result.push_back(ExpandQtCore::fromGBK("形状:圆柱"));
					result.push_back(ExpandQtCore::fromGBK("半径:") + params[2]);
					result.push_back(ExpandQtCore::fromGBK("长度:") + params[3]);
					break;
				case kCone:
					Q_ASSERT(params.size()==5);
					result.push_back(ExpandQtCore::fromGBK("形状:圆台"));
					result.push_back(ExpandQtCore::fromGBK("左端半径:") + params[2]);
					result.push_back(ExpandQtCore::fromGBK("右端半径:") + params[3]);
					result.push_back(ExpandQtCore::fromGBK("长度:") + params[4]);
					break;
				default: Q_ASSERT(0);
				}
			}
			break;
		case kShell:
			{
				ShapeThickness thickness = layer->get_thickness();
				result.push_back(ExpandQtCore::fromGBK("类型:壳体"));
				result.push_back(ExpandQtCore::fromGBK("左端厚度:") + GetLabel(thickness.left, precision_hint));
				result.push_back(ExpandQtCore::fromGBK("右端厚度:") + GetLabel(thickness.right, precision_hint));
			}
			break;
		case kSphereFragment:
			if(SphereFragmentLayer* frag_layer = dynamic_cast<SphereFragmentLayer*>(layer))
			{
				result.push_back(ExpandQtCore::fromGBK("类型:球形破片"));
				result.push_back(ExpandQtCore::fromGBK("破片层数:") + GetLabel((int)frag_layer->get_layer_num()));
				result.push_back(ExpandQtCore::fromGBK("破片半径:") + GetLabel(frag_layer->get_r(), precision_hint));
				result.push_back(ExpandQtCore::fromGBK("破片枚数:") + GetLabel((int)frag_layer->get_frag_num()));
			}
			break;
		}
	}
	return result;

}

