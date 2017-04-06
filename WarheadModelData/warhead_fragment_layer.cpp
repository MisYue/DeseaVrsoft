#include "warhead_fragment_layer.h"
#include "warhead_section.h"
#include "spere_frag_lay.h"
#include <BIT2DComputeSupport/Bit_2DCompute.h>

void RotateRadianByXAxis(CoordinatesPosition& pos, double rad)
{
	double y = pos.Get_y();
	double z = pos.Get_z();

	double c = z;
	double b = y;

	y = b * cos(rad) - c * sin(rad);
	z = b * sin(rad) + c * cos(rad);

	pos.Set_y(y);
	pos.Set_z(z);
}

WarheadFragmentLayer::WarheadFragmentLayer(WarheadSection* section)
	: section_(section)
	, layer_num_(0)
	, frag_num_(0)
	, is_updated_circle_frag_(true)
{
	Q_ASSERT_X(section, "WarheadFragmentLayer::WarheadFragmentLayer", "section==0");
}

SphereFragmentLayer::SphereFragmentLayer(WarheadSection* section, double r)
	: WarheadFragmentLayer(section)
	, r_(r)
	, layout_method_(kLM0)
	, circle_lay_space_(0)
{
	Q_ASSERT_X(section, "SphereFragmentLayer::SphereFragmentLayer", "section=0");
}
void SphereFragmentLayer::UpdateFragments()
{
	Clear();
	SphereFragLay* lay = CreateLay();
	lay->set_circle_lay_space(circle_lay_space_);
	lay->Lay(fragments_, normal_angles_, frags_circle_radius_);
	is_updated_circle_frag_ = false;
	frag_num_ = lay->get_frag_num();
	thickness_.type = kUp;
	thickness_.left = lay->get_thickness_left();
	thickness_.right = lay->get_thickess_right();
	delete lay;
}
void SphereFragmentLayer::LayPerCircle(double circle_radius, QList<CoordinatesPosition>& frags_circle)
{
	CoordinatesPosition start_pos = frags_circle.back();
	//单个破片对圆周的角度
	double rad = asin(r_ / (r_ + circle_radius)) * 2;
	//圆周布设个数
	int num = 2 * M_PI / rad;
	//间距角度
	double s_rad = 2*M_PI / num;
	for(int i=1; i<num; ++i)
	{
		RotateRadianByXAxis(start_pos, s_rad);
		frags_circle.push_back(start_pos);
	}
}

SphereFragLay* SphereFragmentLayer::CreateLay()
{
	//距离高度
	double away_left_h, away_right_h ;
	section_->GetAwayHeight(this, away_left_h, away_right_h);
	//形状改变，布设对象也要改变
	if(shape_describe_->get_shape_type() == kOval)
		return new OvalShapeLay(layout_method_, layer_num_, r_, away_left_h, away_right_h, shape_describe_.get());
	else
		return new LineShapeLay(layout_method_, layer_num_, r_, away_left_h, away_right_h, shape_describe_.get());
}

void SphereFragmentLayer::CountVolume()
{
	volume_ = (4/3.0) * M_PI * pow(r_, 3) * frag_num_;
}