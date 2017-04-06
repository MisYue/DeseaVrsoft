#pragma once
#include "warhead_layer.h"
#include <BITPointSupport/Bit_Point3D.h>

class WarheadSection;

typedef Bit_Point3D CoordinatesPosition;
typedef QList<CoordinatesPosition>  CircleFrags;
typedef QList<CircleFrags> LayerFrags;
typedef QList<LayerFrags> Fragments;

//��Ƭ�ڵ㣬ά�������Ϣ
class WARHEADMODELDATA_EXPORT WarheadFragmentLayer : public WarheadLayer
{
public:
	WarheadFragmentLayer(WarheadSection* section);
	WarheadSection* get_section() { return section_; }
	void set_layer_num(unsigned num) 
	{ 
		if(num != layer_num_)
		{
			layer_num_ = num; 
			if(shape_describe_.valid())
			{
				UpdateFragments();
			}
		}
	}
	unsigned get_layer_num() const { return layer_num_; }
	//������Ƭ
	virtual void UpdateFragments() = 0;
	////���º��
	//virtual void UpdateThickness()=0;
	//��ȡ������Ƭ����ʾ�Ƿ����Բ�ܵ���Ƭ�������ƶ�άģ��ʱ��ֻ��ȡ���ּ��ɣ��������Ӧ�ٶ�
	const Fragments& get_fragments(bool include_circle = false) const
	{
		if(include_circle && !is_updated_circle_frag_ && frags_circle_radius_.size() > 0)
		{
			WarheadFragmentLayer* this_object = const_cast<WarheadFragmentLayer*>(this);
			this_object->UpdateFragmentCircle();
			this_object->is_updated_circle_frag_ = true;
		}
		return fragments_;
	}
	const QList<double>& get_circle_radius() const { return frags_circle_radius_; };
	const QList<QList<double> > get_normal_angles() const { return normal_angles_; }
	unsigned get_frag_num() const { return frag_num_; }
protected:
	unsigned layer_num_;
	unsigned frag_num_;
	WarheadSection* section_;

	//QList<QList<CoordinatesPosition> > fragments_;
	Fragments fragments_;
	QList<QList<double> > normal_angles_;
	QList<double> frags_circle_radius_;
	bool is_updated_circle_frag_;
	void Clear()
	{
		frag_num_ = 0;
		fragments_.clear();
		frags_circle_radius_.clear();
		normal_angles_.clear();
	}
	void UpdateFragmentCircle()
	{
		int circle_num = 0;
		foreach(const LayerFrags& layer_frags, fragments_)
		{
			circle_num += layer_frags.size();
		}
		Q_ASSERT_X(circle_num == frags_circle_radius_.size(), 
			"SpherePreFragmentPart::UpdateFragmentCircle", 
			"fragments_.size() != frags_circle_radius_.size()");
		Fragments::iterator beg_1 = fragments_.begin();
		QList<double>::iterator beg_2 = frags_circle_radius_.begin();
		while(beg_1 != fragments_.end())
		{
			LayerFrags& layer_frags = *beg_1;
			LayerFrags::iterator layer_iter = layer_frags.begin();
			while(layer_iter != layer_frags.end())
			{
				LayPerCircle(*beg_2, *layer_iter);
				++layer_iter;
				++beg_2;
			}
			++beg_1;
		}
	}
	virtual void LayPerCircle(double circle_radius, QList<CoordinatesPosition>& frags_circle)=0;
};
class SphereFragLay;
class WARHEADMODELDATA_EXPORT SphereFragmentLayer : public WarheadFragmentLayer
{
public:
	//��Ƭ�Ų�����
	enum LayoutMethod
	{
		kLM0,	//Ĭ�Ϸ�������Ⱥ���ṩ
		kLM1,	//����һ�������ṩ
		kLM2,	//�������������ṩ
	};
	SphereFragmentLayer(WarheadSection* section, double r);
	//�뾶
	void set_r(double r) 
	{
		if(r != r_)
		{
			r_ = r;  
			if(shape_describe_.valid())
			{
				UpdateFragments();
			}
		}
	}
	double get_r() const { return r_; }

	//�����Ų��������
	void set_circle_lay_space(double rad) 
	{
		if(circle_lay_space_ != rad)
		{
			circle_lay_space_ = rad; 
			if(shape_describe_.valid())
			{
				UpdateFragments();
			}
		}
	}
	double get_circle_lay_space() const { return circle_lay_space_; }
	//��Ƭ�Ų�����
	void set_layout_method(LayoutMethod method) 
	{
		if(layout_method_ != method)
		{
			layout_method_ = method;
			if(shape_describe_.valid())
			{
				UpdateFragments();
			}
		}
	}
	LayoutMethod get_layout_method() const { return layout_method_; }
	//������Ƭ
	virtual void UpdateFragments();
	////���º��
	//virtual void UpdateThickness();
	//���
	virtual void CountVolume();

protected:
	double r_; //�뾶
	double circle_lay_space_;	//�����Ų��������
	virtual void LayPerCircle(double circle_radius, QList<CoordinatesPosition>& frags_circle);
	SphereFragLay* CreateLay();
	LayoutMethod layout_method_;
};