
#pragma once
#include "warhead_model_data_global.h"
#include "shape_describe.h"
#include <QtCore>

class WarheadModel;
class Material;

class WARHEADMODELDATA_EXPORT WarheadNode
{
public:
	WarheadNode();
	virtual ~WarheadNode();
	QString get_guid() const { return guid_; }
	QString get_name() const { return name_; }
	void set_name(const QString& name) { name_ = name; }
protected:
	QString name_;
	QString guid_;
};


//������״������ͣ�������
enum ThicknessType
{
	kNo,	//������
	kUp,	//����״������������
	kDown,	//����״������������
};
struct ShapeThickness
{
	ThicknessType type; //�������
	double left; //��˺��
	double right; //�Ҷ˺��

	ShapeThickness(ThicknessType _type = kNo, double _left = 0, double _right = 0) : left(_left), right(_right), type(_type) {}
	bool operator == (const ShapeThickness& thickness) const
	{
		return (thickness.left == left
			&& thickness.right == right
			&& thickness.type == type);
	}
	bool operator != (const ShapeThickness& thickness) const
	{
		return !((*this) == thickness);
	}
};

class WARHEADMODELDATA_EXPORT WarheadMassNode : public WarheadNode
{
public:
	WarheadMassNode();
	~WarheadMassNode();
	//���ϣ����ò���ʱ���Զ���������
	void set_material(const Material* material) { material_ = material; }
	const Material* get_material() const { return material_; }
	//void set_material_sign(const MaterialSign& material_sign);
	//MaterialSign get_material_sign() const { return material_sign_; }
	//��״������������״����ʱ�����Զ��������������
	void set_shape_describe(const ShapeDescribe* shape_describe);
	const ShapeDescribe* get_shape_describe() const { return shape_describe_; }

	double get_volume() const { return volume_; }
	//����
	void CountMass();
	double get_mass() const { return mass_; }
	//��ȣ����ú��ʱ�����Զ��������������
	void set_thickness(const ShapeThickness& thickness);
	ShapeThickness get_thickness() const { return thickness_; }


protected:
	//MaterialSign material_sign_; //���ϱ�ʶ
	const Material* material_;	//����
	double volume_; //���
	double mass_; //����
	osg::ref_ptr<const ShapeDescribe> shape_describe_; //��״��������
	ShapeThickness thickness_;
};


//����θ����ͣ��˸Ǿ�ΪԲ���Σ�
class WARHEADMODELDATA_EXPORT WarheadEndCap : public WarheadMassNode
{
	friend WarheadModel;
public:
	WarheadEndCap(const Bit_UnitSystem& us, double r, double pos_x, double length);
	double get_length() const { return shape_describe_->get_shape_length(); }
	void set_lenght(double length);
	double get_pos_x() const ;
	double get_r() const;
	//���
	void CountVolume();
private:
	void set_pos_x(double pos_x);
	void set_r(double r);
	Bit_UnitSystem us_;
};

//�����𱬵�����
class  WarheadFirePoint : public WarheadNode
{
	friend WarheadModel;
public:
	WarheadFirePoint(int id) : id_(id){}
	void Translate(double dx) { pos_.Set_x(pos_.Get_x()+dx); }
	void set_pos(const Bit_Point2D& pos) { pos_ = pos; }
	Bit_Point2D get_pos() const { return pos_; }
	int get_id() const { return id_; }
protected:
	Bit_Point2D pos_;
	int id_;
};