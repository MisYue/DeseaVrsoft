#include "Warhead_Read.h"
#include <WarheadModelData/WarheadModelWrap.h>
#include <MaterialLib/materiallib.h>
#include <BasicTool/expandqtcore.h>
#include <BasicTool/CoordConvert2D.h>
#include <QtXml>

class ShapeData
{
public:
	ShapeData(QDomElement _element, const Bit_UnitSystem& us, const CoordConvert2D& coord_convert) 
		: element_(_element), coord_convert_(coord_convert), us_(us)
	{
		if(!element_.isNull())
		{
			for(QDomElement Shape = element_.firstChildElement("Shape");
				!Shape.isNull();
				Shape = Shape.nextSiblingElement("Shape"))
			{
				int id = Shape.attribute("ID").toInt();
				ShapeType type = static_cast<ShapeType>(Shape.attribute("Type").toInt());
				QString describe = Shape.attribute("Describe");
				QStringList strs = describe.split(',');
				QVector<double> params;
				params.reserve(strs.size());
				foreach(const QString& str, strs)
				{
					double d = str.toDouble();
					params.push_back(d);
				}
				double y = 0;
				coord_convert_.Reverse(params[0], y);
				describe.clear();
				foreach(const double& param, params)
				{
					QString str = QString::number(param, 'g', 15);
					if(!describe.isEmpty())
						describe.append(',');
					describe.append(str);
				}
				ShapeDescribe* shape = ShapeDescribe::CreateShape(us, type, describe);
				id_2_shape_.insert(id, shape);
			}
		}
	}
	ShapeDescribe* GetShape(int id) { return id_2_shape_.value(id, 0); }
protected:
	QDomElement element_;
	QMap<int, ShapeDescribe*> id_2_shape_;
	CoordConvert2D coord_convert_;
	Bit_UnitSystem us_;
};

class MaterialData
{
public:
	MaterialData(QDomElement _element, WarheadModelWrap* model_wrap) 
		: element_(_element), model_wrap_(model_wrap)
	{
		if(!element_.isNull())
		{
			for(QDomElement Material_Element = element_.firstChildElement("Material");
				!Material_Element.isNull();
				Material_Element = Material_Element.nextSiblingElement("Material"))
			{
				int id = Material_Element.attribute("ID").toInt();
				MaterialType type = static_cast<MaterialType>(Material_Element.attribute("Type").toInt());
				QString props = Material_Element.attribute("Properties");
				const Material* material = 0;
				if(type == kMetal)
					material = model_wrap_->get_metal_lib()->Append(props);
				else
					material = model_wrap_->get_charge_lib()->Append(props);
				if(material)
				{
					id_2_material_.insert(id, material);
				}
			}
		}
	}
	const Material* GetMaterial(int id) const { return id_2_material_.value(id, 0); }
protected:
	QDomElement element_;
	WarheadModelWrap* model_wrap_;
	QMap<int, const Material*> id_2_material_;
};
WarheadRead::WarheadRead(void)
{
}


WarheadRead::~WarheadRead(void)
{
}


WarheadModelWrap* WarheadRead::ReadXMLFile(const QString& file_name) const
{
	QDomDocument doc("WarheadDirect");
	QFile file(file_name);
	if (!file.open(QIODevice::ReadOnly))
		return 0;
	if (!doc.setContent(&file)) {
		file.close();
		return 0;
	}
	file.close();
	WarheadModelWrap* model_wrap = new WarheadModelWrap;
	WarheadModel* model = model_wrap->get_structure();

	QDomElement root = doc.documentElement();


	//	<!--��λ��-->
	//	<US Length="����" Mass="����" Time="ʱ��" Temp="�¶�"/>



	//<!--ս��������-->
	//<WarheadBase Name="����" ID="���" CS="��������ϵ����" CS_Explain="����ϵ˵��" />
	QDomElement WarheadBase = root.firstChildElement("WarheadBase");
	if(WarheadBase.isNull())
		return 0;
	model->set_name(WarheadBase.attribute("Name"));

	//	<!--��λ��-->
	//	<US Length="����" Mass="����" Time="ʱ��" Temp="�¶�"/>
	QDomElement US = root.firstChildElement("US");
	if(US.isNull())
		return 0;
	int unit_length = US.attribute("Length").toInt();
	int unit_mass = US.attribute("Mass").toInt();
	int unit_time = US.attribute("Time").toInt();

	QString cs_explain = WarheadBase.attribute("CS_Explain");
	QString cs_2d_text = WarheadBase.attribute("CS");
	QStringList strs = cs_2d_text.split(',');
	Q_ASSERT(strs.size() == 4);

	//����ת��ϵ��
	Bit_UnitSystem us(unit_length, unit_mass, unit_time);

	Bit_2DCS cs_2d(Bit_Point2D(strs[0].toDouble(), strs[1].toDouble()), 1, Bit_Point2D(strs[2].toDouble(), strs[3].toDouble()));

	Bit_2DCSWithExplain cse(0, "", cs_2d, cs_explain.toLocal8Bit().data());
	Bit_2DCSWithExpAndUS cs(cse, us);
	model->set_cs(cs);
	

	double rad = 0;
	if(cs_2d.Get_XAixVector().Get_x() == -1)
		rad = M_PI;
	CoordConvert2D coord_convert(rad, cs_2d.Get_OriginalPoint().Get_x(), 0);

	//	<!--ս�����ṹ����-->
	//	<WarheadSData Type="ս��������" Length="ս�������峤��" Mass="ս������������" ChargeMass="װҩ����" ShellMass="��������" />
	QDomElement WarheadSData = root.firstChildElement("WarheadSData");
	if(WarheadSData.isNull())
		return 0;
	int warhead_type = WarheadSData.attribute("Type", "0").toInt();
	model->set_type(static_cast<WarheadType>(warhead_type));

	//��������
	MaterialData material_data(root.firstChildElement("MaterialData"), model_wrap);
	QDomElement ShapeDataElement = root.firstChildElement("ShapeData");
	ShapeData shape_data(ShapeDataElement, us, coord_convert);

	QDomElement SectionData = root.firstChildElement("SectionData");
	if(SectionData.isNull())
		return 0;
	for(QDomElement Section = SectionData.firstChildElement("Section"); 
		!Section.isNull(); 
		Section = Section.nextSiblingElement("Section"))
	{
		int shape_id = Section.attribute("ShapeID").toInt();
		ShapeDescribe* shape = shape_data.GetShape(shape_id);
		WarheadSection* section = new WarheadSection(shape, material_data.GetMaterial(Section.attribute("MaterialID").toInt()));
		if(model->GetNumSection() > 0)
			model->AddSection(section, model->get_sections().back(), false);
		else
			model->AddSection(section);
		for(QDomElement Layer = Section.firstChildElement(); !Layer.isNull(); Layer = Layer.nextSiblingElement())
		{
			QString TagName = Layer.tagName();
			WarheadLayer* layer = 0;
			if(TagName == "Shell")
			{
				ShapeThickness thickness;
				thickness.type = kUp;
				//���ȵ�λת��
				thickness.left = Layer.attribute("LeftThickness").toDouble();
				thickness.right = Layer.attribute("RightThickness").toDouble();
				layer = new WarheadLayer;
				layer->set_layer_type(kShell);
				layer->set_thickness(thickness);
			}
			else if(TagName == "SphereFrag")
			{
				//���ȵ�λת��
				SphereFragmentLayer* frag_layer = new SphereFragmentLayer(section, Layer.attribute("Radius").toDouble());
				frag_layer->set_layer_num(Layer.attribute("LayerNum").toInt());
				layer = frag_layer;
				layer->set_layer_type(kSphereFragment);
			}
			if(layer)
			{
				layer->set_material(material_data.GetMaterial(Layer.attribute("MaterialID").toInt()));
				section->AddLayer(layer, section->get_layers().back(), true);
			}
		}
	}
	//<!--�𱬵�-->
	//	<BlastPosition>
	//	<Pos Coord="�𱬵�����" />
	//	<Pos Coord="�𱬵�����" />
	//	</BlastPosition>

	QDomElement BlastPosition = root.firstChildElement("BlastPosition");
	if(!BlastPosition.isNull())
	{
		for(QDomElement Pos=BlastPosition.firstChildElement("Pos"); !Pos.isNull(); Pos = Pos.nextSiblingElement("Pos"))
		{
			QString coord_text = Pos.attribute("Coord");
			QStringList strs = coord_text.split(',');
			Q_ASSERT(strs.size()==2);
			if(strs.size() == 2)
			{
				//���ȵ�λת��
				double x= strs[0].toDouble();
				double y = strs[1].toDouble();
				//����ϵת��-��������ϵת��ͼϵͳ����ϵ
				coord_convert.Reverse(x, y);
				model->AddFirePoint(Bit_Point2D(x, y));
			}
		}
	}
	//ע�⣬���ж����ж˸�
	if(model->GetNumSection() > 0)
	{
		//<!--��˸�����-->
		//	<WarheadLeftEndCap MaterialID="���Ϻ�" Length="����" Radius="�뾶" mass="����"/>
		//	<!--�Ҷ˸�����-->
		//	<WarheadRightEndCap MaterialID="���Ϻ�" Length="����" Radius="�뾶" mass="����"/>
		QDomElement LeftEndCap = root.firstChildElement("WarheadLeftEndCap");
		if(!LeftEndCap.isNull())
		{
			//���ȵ�λת��
			double length = LeftEndCap.attribute("Length").toDouble();
			int material_id = LeftEndCap.attribute("MaterialID").toInt();
			model->AddLeftEndCap(length);
			model->get_left_end_cap()->set_material(material_data.GetMaterial(material_id));
		}
		QDomElement RightEndCap = root.firstChildElement("WarheadRightEndCap");
		if(!RightEndCap.isNull())
		{
			//���ȵ�λת��
			double length = RightEndCap.attribute("Length").toDouble();
			int material_id = RightEndCap.attribute("MaterialID").toInt();
			model->AddRightEndCap(length);
			model->get_right_end_cap()->set_material(material_data.GetMaterial(material_id));
		}
	}


	return model_wrap;
}