#include "warhead_write.h"
#include <QtXml>
#include <WarheadModelData/WarheadModelWrap.h>
#include <MaterialLib/materiallib.h>
#include <BasicTool/expandqtcore.h>
#include <BasicTool/CoordConvert2D.h>
#include <BIT2DComputeSupport/Bit_2DCompute.h>


class DataElement
{
public:
	DataElement(QDomDocument& doc, const QString& element_name) 
		: doc_(doc), next_id_(0), coord_convert_(0, 0, 0)
	{
		element_ = doc.createElement(element_name);
	}
	void set_coord_convert(const CoordConvert2D& coord_convert) { coord_convert_ = coord_convert; }
	QDomElement get_element() { return element_; }
	unsigned get_next_id() const { return next_id_; }
protected:
	QDomDocument& doc_;
	unsigned next_id_;
	QDomElement element_;
	CoordConvert2D coord_convert_;
	

};
//材料节点
class MaterialDataElement : public DataElement
{
public:
	MaterialDataElement(QDomDocument& doc) 
		: DataElement(doc, "MaterialData")
	{}
	void Append(const Material* material)
	{
		if(already_exist_.contains(material))
			return;
		QDomElement child = doc_.createElement("Material");
		child.setAttribute("ID", next_id_++);
		child.setAttribute("Type", dynamic_cast<const MetalMaterial*>(material) ? kMetal : kCharge);
		QString properties;
		foreach(const QString& value, material->GetPropertyValues())
		{
			properties.append(value);
			properties.append(',');
		}
		properties[properties.size()-1] = '\0';
		child.setAttribute("Properties", properties);
		element_.appendChild(child);
		already_exist_.insert(material);
	}
private:
	QSet<const Material*> already_exist_;
};
//形状节点
class ShapeDataElement : public DataElement
{
public:
	ShapeDataElement(QDomDocument& doc) : DataElement(doc, "ShapeData") {}
	void Append(const ShapeDescribe* shape)
	{
		QDomElement child = doc_.createElement("Shape");
		child.setAttribute("ID", next_id_++);
		child.setAttribute("Type", shape->get_shape_type());
		//child.setNodeValue(shape->GetShapeDescribe());
		QString shape_text = shape->GetShapeDescribe();
		QStringList strs = shape_text.split(',');
		double x = strs[0].toDouble();
		double y = 0;
		coord_convert_.Convert(x, y);
		strs[0] = QString::number(x);
		shape_text.clear();
		foreach(const QString& str, strs)
		{
			if(!shape_text.isEmpty())
				shape_text.append(',');
			shape_text.append(str);
		}
		child.setAttribute("Describe", shape_text);
		element_.appendChild(child);
	}
};

//曲线节点
class CurveDataElement : public DataElement
{
public:
	CurveDataElement(QDomDocument& doc) : DataElement(doc, "CurveData") {}
	void Append(const ShapeDescribe* shape, unsigned descrete_num)
	{
		QDomElement child = doc_.createElement("Curve");
		child.setAttribute("ID", next_id_++);
		QVector<Bit_Point2D> points;
		CurveEquation curve(shape);
		curve.DescreteCurve(points, descrete_num);
		foreach(const Bit_Point2D& point, points)
		{
			QDomElement Point = doc_.createElement("Point");
			double x = point.Get_x();
			double y = point.Get_y();
			coord_convert_.Convert(x, y);
			QString node_value = QString("%1,%2").arg(x).arg(y);
			//Point.setNodeValue(node_value);
			Point.setAttribute("Coord", node_value);
			child.appendChild(Point);
		}
		element_.appendChild(child);
	}
};

//破片坐标数据节点
class PreFragmentDataElement : public DataElement
{
public:
	PreFragmentDataElement(QDomDocument& doc, const Bit_Point2D& fire_point) 
		: DataElement(doc, "PreFragmentData"), fire_point_(fire_point), rotated_(true)
	{
		if(coord_convert_.get_rad() == 0)
			rotated_ = false;
	}
	void Append(const Fragments& frags, const QList<QList<double> >& normal_angles)
	{
		QDomElement CoordList = doc_.createElement("CoordList");
		CoordList.setAttribute("ID", next_id_++);
		QList<QList<double> >::const_iterator iter = normal_angles.begin();
		foreach(const LayerFrags& layer_frags, frags)
		{
			const QList<double>& layer_normals = *iter;
			QList<double>::const_iterator layer_iter = layer_normals.begin();
			QDomElement Layer = doc_.createElement("Layer");
			int layer_num = 0;
			foreach(const CircleFrags& circle_frags, layer_frags)
			{
				QDomElement Circle = doc_.createElement("Circle");
				int cirlce_num = circle_frags.size();
				layer_num += cirlce_num;
				Circle.setAttribute("Num", cirlce_num);
				double normal_angle = *layer_iter;
				if(rotated_)
					normal_angle = M_PI - normal_angle;

				Circle.setAttribute("NormalAngle", *layer_iter);
				const CoordinatesPosition& coord = circle_frags.first();
				Circle.setAttribute("FirePointAngle", CountFirePointAngle(Bit_Point2D(coord.Get_x(), coord.Get_y())));
				foreach(const CoordinatesPosition& pos, circle_frags)
				{
					QDomElement Point = doc_.createElement("Frag");
					double x = pos.Get_x();
					double y = pos.Get_y();
					coord_convert_.Convert(x, y);
					QString node_value = QString("%1,%2,%3").arg(x).arg(y).arg(pos.Get_z());
					Point.setAttribute("Coord", node_value);
					Circle.appendChild(Point);
				}
				Layer.appendChild(Circle);
				++layer_iter;
			}
			Layer.setAttribute("Num", layer_num);
			Layer.setAttribute("CircleNum", layer_frags.size());
			CoordList.appendChild(Layer);
			++iter;
		}
		element_.appendChild(CoordList);
	}
protected:
	double CountFirePointAngle(const Bit_Point2D& point)
	{
		Bit_2DCompute sc2d;
		double rad = sc2d.ComputeAngleTwoV(point - fire_point_, rotated_ ? Bit_Point2D(-1, 0) : Bit_Point2D(1, 0));
		return rad;
	}
	const Bit_Point2D& fire_point_;
	bool rotated_;
};

WarheadWrite::WarheadWrite(const WarheadModelWrap* model_wrap)
	: model_wrap_(model_wrap)
{
	Q_ASSERT_X(model_wrap_, "WarheadWrite::WarheadWrite", "model==0");
}

WarheadWrite::~WarheadWrite()
{

}
class CSVFragmentData
{
public:
	CSVFragmentData(QTextStream& stream, const Bit_Point2D& fire_point, const CoordConvert2D& coord_convert, const WarheadModel* model) 
		: stream_(stream), fire_point_(fire_point), next_section_id_(0), coord_convert_(coord_convert), model_(model), rotated_(true)
	{
		if(coord_convert_.get_rad() == 0)
			rotated_ = false;
		stream << "*Fragment\n";
		stream << ExpandQtCore::fromGBK("//段ID,层ID,圈ID,X坐标,Y坐标,法线与模型正X轴夹角(弧度),起爆点连线与模型正X轴夹角(弧度),该圈破片个数,该圈半径,破片半径,破片质量") << "\n";

		QList<WarheadSection*> sections = model_->get_sections();
		foreach(WarheadSection* section, sections)
		{
			QList<WarheadLayer*> layers = section->get_layers();
			QList<WarheadLayer*>::iterator iter = layers.begin();
			while(++iter != layers.end())
			{
				switch((*iter)->get_layer_type())
				{
				case kSphereFragment:
					{
						SphereFragmentLayer* sphere_layer = dynamic_cast<SphereFragmentLayer*>(*iter);
						Q_ASSERT(sphere_layer);
						double mass = sphere_layer->get_mass() / sphere_layer->get_frag_num();
						Append(sphere_layer->get_fragments(true), sphere_layer->get_normal_angles(), sphere_layer->get_circle_radius(), sphere_layer->get_r(), mass);
					}
					break;
				}
			}
		}
	}
	void Append(const Fragments& frags, const QList<QList<double> >& normal_angles, const QList<double>& circle_radius, double r, double m)
	{
		QList<QList<double> >::const_iterator iter = normal_angles.begin();
		QList<double>::const_iterator c_r_iter = circle_radius.begin();
		int layer_id = 0;
		foreach(const LayerFrags& layer_frags, frags)
		{
			const QList<double>& layer_normals = *iter;
			QList<double>::const_iterator layer_iter = layer_normals.begin();
			int circle_id = 0;
			foreach(const CircleFrags& circle_frags, layer_frags)
			{
				int cirlce_num = circle_frags.size();
				const CoordinatesPosition& pos = circle_frags.first();
				double x = pos.Get_x();
				double y = pos.Get_y();
				coord_convert_.Convert(x, y);
				stream_ << next_section_id_ << "," 
					<< layer_id << ","
					<< circle_id << ","
					<< x << "," 
					<< y << "," 
					<< ConvertNormalAngle(*layer_iter) << "," 
					<< CountFirePointAngle(Bit_Point2D(pos.Get_x(), pos.Get_y())) << "," 
					<< cirlce_num << ","
					<< *c_r_iter << ","
					<< r << ","
					<< m << "\n";

				++layer_iter;
				++c_r_iter;
				++circle_id;
			}
			++layer_id;
			++iter;
		}
		++next_section_id_;
	}
protected:
	QTextStream& stream_;
	Bit_Point2D fire_point_;
	int next_section_id_;
	CoordConvert2D coord_convert_;
	const WarheadModel* model_;
	bool rotated_;
	double CountFirePointAngle(const Bit_Point2D& point)
	{
		Bit_2DCompute sc2d;
		double rad = sc2d.ComputeAngleTwoV(point - fire_point_, rotated_ ? Bit_Point2D(-1, 0) : Bit_Point2D(1, 0));
		return rad;
	}
	double ConvertNormalAngle(double rad)
	{
		if(rotated_)
			return M_PI - rad;
		return rad;
	}
};
bool WarheadWrite::WriteCSVFile(const QString& file_name)
{
	QFile file(file_name);
	if(!file.open(QFile::WriteOnly | QFile::Text))
		return false;
	QTextStream stream(&file);
	const WarheadModel* model = model_wrap_->get_structure();
	const_cast<WarheadModel*>(model)->UpdateCharacterData();
	stream << ExpandQtCore::fromGBK("//为注释行") << "\n";
	stream << "*US\n";
	stream << ExpandQtCore::fromGBK("//单位制") << "\n";
	Bit_2DCSWithExpAndUS cs = model->get_cs();
	Bit_UnitSystem us = cs.Get_UnitSystem();
	Bit_2DCS cs_2d = cs.Get_2DCSWithExplain().Get_CS();
	//坐标系转换对象
	double rad = 0;
	if(cs_2d.Get_XAixVector().Get_x() == -1)
		rad = M_PI;
	CoordConvert2D coord_convert(rad, cs_2d.Get_OriginalPoint().Get_x(), 0);

	stream << us.Get_LengthUnit() << "," << us.Get_MassUnit() << "," << us.Get_TimeUnit() << "\n";
	stream << "*CharacterData\n";
	const WarheadCharacterData& character_data = model->get_character_data();
	double charge_l = character_data.length;
	if(const WarheadEndCap* left = model->get_left_end_cap())
		charge_l -= left->get_length();
	if(const WarheadEndCap* right = model->get_right_end_cap())
		charge_l -= right->get_length();
	stream << ExpandQtCore::fromGBK("//壳体加破片质量,装药质量,装药质量") << "\n";
	stream << character_data.shell_mass+character_data.frag_mass << "," << character_data.charge_mass << "," << charge_l << "\n";
	stream << "*FirePoint\n";
	//起爆点由绘图坐标系转为弹体坐标系
	Bit_Point2D fire_point = model->get_fire_points().first()->get_pos();
	double x = fire_point.Get_x();
	double y = fire_point.Get_y();
	coord_convert.Convert(x, y);
	stream << x << "," << y << "\n";
	stream << ExpandQtCore::fromGBK("*Charge") << "\n";
	stream << ExpandQtCore::fromGBK("//属性列表") << "\n";
	QList<WarheadSection*> sections = model->get_sections();
	const Material* charge_material = sections.first()->get_layers().first()->get_material();
	QString properties;
	foreach(const QString& value, charge_material->GetPropertyValues())
	{
		properties.append(value);
		properties.append(',');
	}
	properties[properties.size()-1] = '\0';
	stream << properties << "\n";
	CSVFragmentData csv_frag_data(stream, fire_point, coord_convert, model);
	return true;
}

bool WarheadWrite::WriteXMLFile(const QString& file_name, unsigned curve_descrete_num) const
{
	QFile file(file_name);
	if(!file.open(QFile::WriteOnly | QFile::Text))
		return false;

	QDomDocument doc("WarheadDirect");
	QDomElement root = doc.createElement("WarheadDirect");

	const WarheadModel* model = model_wrap_->get_structure();
	const_cast<WarheadModel*>(model)->UpdateCharacterData();
	//战斗部基础
	QDomElement WarheadBase = doc.createElement("WarheadBase");
	WarheadBase.setAttribute("Name", model->get_name());
	WarheadBase.setAttribute("ID", 0);
	Bit_2DCS cs_2d = model->get_cs().Get_2DCSWithExplain().Get_CS();
	Bit_Point2D origin = cs_2d.Get_OriginalPoint();
	Bit_Point2D x_v = cs_2d.Get_XAixVector();
	QString CS = QString("%1,%2,%3,%4").arg(origin.Get_x()).arg(origin.Get_y()).arg(x_v.Get_x()).arg(x_v.Get_y());
	WarheadBase.setAttribute("CS", CS);
	WarheadBase.setAttribute("CS_Explain", ExpandQtCore::fromGBK(model->get_cs().Get_2DCSWithExplain().Get_Explain().c_str()));
	root.appendChild(WarheadBase);

	double rad = 0;
	if(cs_2d.Get_XAixVector().Get_x() == -1)
		rad = M_PI;
	CoordConvert2D coord_convert(rad, cs_2d.Get_OriginalPoint().Get_x(), 0);

	//单位制
	QDomElement US = doc.createElement("US");
	Bit_2DCSWithExpAndUS cs = model->get_cs();
	Bit_UnitSystem us = cs.Get_UnitSystem();
	US.setAttribute("Length", us.Get_LengthUnit());
	US.setAttribute("Mass", us.Get_MassUnit());
	US.setAttribute("Time", us.Get_TimeUnit());
	root.appendChild(US);

	//<!--战斗部结构数据-->
	//<WarheadSData Type="战斗部类型" Length="战斗部整体长度" Mass="战斗部整体质量" ChargeMass="装药质量" ShellMass="壳体质量" />
	QDomElement WarheadSData = doc.createElement("WarheadSData");
	WarheadSData.setAttribute("Type", model->get_type());
	const WarheadCharacterData& character_data = model->get_character_data();
	WarheadSData.setAttribute("Length", character_data.length);
	WarheadSData.setAttribute("Mass", character_data.mass);
	WarheadSData.setAttribute("ChargeMass", character_data.charge_mass);
	WarheadSData.setAttribute("ShellMass", character_data.shell_mass);
	root.appendChild(WarheadSData);

	//形状数据
	ShapeDataElement shapes(doc);
	shapes.set_coord_convert(coord_convert);
	//材料数据
	MaterialDataElement materials(doc);
	
	//左端盖
	const WarheadEndCap* left_end_cap = model->get_left_end_cap();
	if(left_end_cap)
	{
		QDomElement end_cap_element = doc.createElement("WarheadLeftEndCap");
		end_cap_element.setAttribute("MaterialID", materials.get_next_id());
		materials.Append(left_end_cap->get_material());
		end_cap_element.setAttribute("Length", left_end_cap->get_length());
		end_cap_element.setAttribute("Radius", left_end_cap->get_r());
		end_cap_element.setAttribute("Mass", left_end_cap->get_mass());
		root.appendChild(end_cap_element);
	}
	//右端盖
	const WarheadEndCap* right_end_cap = model->get_right_end_cap();
	if(right_end_cap)
	{
		QDomElement end_cap_element = doc.createElement("WarheadRightEndCap");
		end_cap_element.setAttribute("MaterialID", materials.get_next_id());
		materials.Append(right_end_cap->get_material());
		end_cap_element.setAttribute("Length", right_end_cap->get_length());
		end_cap_element.setAttribute("Radius", right_end_cap->get_r());
		end_cap_element.setAttribute("Mass", right_end_cap->get_mass());
		root.appendChild(end_cap_element);
	}

	double charge_length = 0;
	foreach(WarheadSection* section, model->get_sections())
	{
		WarheadLayer* layer = section->get_layers().first();
		Q_ASSERT(layer->get_layer_type() == kCharge);
		charge_length += layer->get_shape_describe()->get_shape_length();
	}
	//段数据
	QDomElement SectionData = doc.createElement("SectionData");
	QList<WarheadSection*> sections = model->get_sections();
	foreach(WarheadSection* section, sections)
	{
		QList<WarheadLayer*> layers = section->get_layers();
		WarheadLayer* charge_layer = layers.first();
		QDomElement Section = doc.createElement("Section");
		Section.setAttribute("MaterialID", materials.get_next_id());
		materials.Append(charge_layer->get_material());
		Section.setAttribute("Mass", charge_layer->get_mass());
		Section.setAttribute("ShapeID", shapes.get_next_id());
		shapes.Append(section->get_shape_describe());
		//段内各层，第一层为装药，装药数据保存在段属性中，从第二段开始
		QList<WarheadLayer*>::iterator iter = layers.begin();
		while(++iter != layers.end())
		{
			switch((*iter)->get_layer_type())
			{
			case kShell:
				{
					QDomElement Shell = doc.createElement("Shell");
					Shell.setAttribute("MaterialID", materials.get_next_id());
					materials.Append((*iter)->get_material());
					Shell.setAttribute("Mass", (*iter)->get_mass());
					ShapeThickness thickness = (*iter)->get_thickness();
					Shell.setAttribute("LeftThickness", thickness.left);
					Shell.setAttribute("RightThickness", thickness.right);
					Section.appendChild(Shell);
				}
				break;
			case kSphereFragment:
				{
					SphereFragmentLayer* sphere_layer = dynamic_cast<SphereFragmentLayer*>(*iter);
					Q_ASSERT(sphere_layer);
					QDomElement SphereFrag = doc.createElement("SphereFrag");
					SphereFrag.setAttribute("MaterialID", materials.get_next_id());
					materials.Append((*iter)->get_material());
					SphereFrag.setAttribute("Mass", (*iter)->get_mass());
					SphereFrag.setAttribute("LayerNum", sphere_layer->get_layer_num());
					SphereFrag.setAttribute("Radius", sphere_layer->get_r());
					Section.appendChild(SphereFrag);
				}
				break;
			}
		}
		SectionData.appendChild(Section);
	}
	root.appendChild(SectionData);
	//起爆点
	QDomElement BlastPosition = doc.createElement("BlastPosition");
	foreach(const WarheadFirePoint* fire_point, model->get_fire_points())
	{
		QDomElement Pos = doc.createElement("Pos");
		Bit_Point2D point = fire_point->get_pos();
		double x = point.Get_x();
		double y = point.Get_y();
		coord_convert.Convert(x, y);
		QString value = QString("%1,%2").arg(x).arg(y);
		Pos.setAttribute("Coord", value);
		BlastPosition.appendChild(Pos);
	}
	root.appendChild(BlastPosition);

	root.appendChild(materials.get_element());
	root.appendChild(shapes.get_element());

	doc.appendChild(root);

	QTextStream out(&file);
	doc.save(out, 4);
	file.close();

	return true;
}