#include "warhead_model.h"
#include "warhead_section.h"
#include "warhead_layer.h"
#include <MaterialLib/Material.h>

WarheadModel::WarheadModel()
	: left_end_cap_(0)
	, right_end_cap_(0)
	, type_(kKill)
{
	name_ = "New Warhead";
	cs_.Set_Initial(Bit_2DCSWithExplain(0, "CS", Bit_2DCS(Bit_Point2D(0, 0), 1, Bit_Point2D(1, 0)), "模型坐标系为右手坐标系，中轴线为X轴，弹头朝向正X轴"), Bit_UnitSystem());
}

WarheadModel::~WarheadModel()
{
	if(left_end_cap_)
		delete left_end_cap_;
	if(right_end_cap_)
		delete right_end_cap_;
	qDeleteAll(fire_points_);
	qDeleteAll(sections_);
}

void WarheadModel::AddSection(WarheadSection* new_section, WarheadSection* pos_section,  bool left_pos)
{
	//左侧长度
	double left_length = 0;
	if(left_end_cap_)
		left_length += left_end_cap_->get_length();
	if(0 == pos_section)
	{
		//基准点
		new_section->get_shape_describe()->set_datum_point(Bit_Point2D(left_length, 0));
		sections_.push_back(new_section);
	}
	else
	{
		//找到位置段
		QList<WarheadSection*>::iterator pos_iter = sections_.begin();
		while(pos_iter != sections_.end())
		{
			if(*pos_iter == pos_section)
				break;
			left_length += (*pos_iter)->get_length();
			++pos_iter;
		}
		//移动位置段右侧的段
		QList<WarheadSection*>::iterator temp_iter = pos_iter;
		double dx = new_section->get_length();
		while(temp_iter != sections_.end())
		{
			if(++temp_iter != sections_.end())
				(*temp_iter)->Translate(dx);
		}
		//若在位置段的左侧插入移动当前段
		if(left_pos)
		{
			pos_section->Translate(dx);
			sections_.insert(pos_iter, new_section); //注意：pos_iter指向已改变
			//基准点
			new_section->get_shape_describe()->set_datum_point(Bit_Point2D(left_length, 0));
		}
		else
		{
			sections_.insert((pos_iter+1), new_section);
			//基准点
			double current_section_length = pos_section->get_length();
			new_section->get_shape_describe()->set_datum_point(Bit_Point2D(left_length+current_section_length, 0));
		}
	}
	//更新端盖
	UpdateEndCap();

}
void WarheadModel::DeleteSection(WarheadSection* section)
{
	//向前移动之后的段
	AdjustAfterSectionPosX(section, -section->get_shape_describe()->get_shape_length());
	int index = sections_.indexOf(section);
	if(index != -1)
		delete sections_.takeAt(index);
	UpdateEndCap();
}

WarheadSection* WarheadModel::GetSection(const WarheadLayer* layer)
{
	WarheadSection* result = 0;
	foreach(WarheadSection* section, sections_)
	{
		foreach(WarheadLayer* _layer, section->get_layers())
		{
			if(_layer == layer)
				return section;
		}
	}
	return result;
}

WarheadSection* WarheadModel::GetNextSection(const WarheadSection* section)
{
	WarheadSection* result = 0;
	QList<WarheadSection*>::iterator iter = sections_.begin();
	while(iter != sections_.end())
	{
		if(*iter == section)
			break;
		++iter;
	}
	if(iter != sections_.end() && (iter+1) != sections_.end())
		result = *(iter+1);
	return result;
}
WarheadSection* WarheadModel::GetPreviousSection(const WarheadSection* section)
{
	WarheadSection* result = 0;
	QList<WarheadSection*>::iterator iter = sections_.begin();
	while(iter != sections_.end())
	{
		if(*iter == section)
			break;
		++iter;
	}
	if(iter != sections_.begin() && iter != sections_.end() && (iter-1) != sections_.end())
		result = *(iter-1);
	return result;
}
void WarheadModel::AdjustAfterSectionPosX(WarheadSection* section, double dx)
{
	QList<WarheadSection*>::iterator iter = sections_.begin();
	while(iter != sections_.end())
	{
		if(*iter == section)
			break;
		++iter;
	}
	while(++iter != sections_.end())
	{
		(*iter)->Translate(dx);
	}
	if(right_end_cap_)
		right_end_cap_->set_pos_x(right_end_cap_->get_pos_x() + dx);
}
WarheadFirePoint* WarheadModel::AddFirePoint(const Bit_Point2D& pos)
{
	WarheadFirePoint* fire_point = new WarheadFirePoint(fire_points_.size());
	fire_point->set_pos(pos);
	fire_points_.push_back(fire_point);
	return fire_point;
}
void WarheadModel::DeleteFirePoint(int index)
{
	if(index >=0 && index < fire_points_.size())
	{
		delete fire_points_.takeAt(index);
		QList<WarheadFirePoint*>::iterator iter = (fire_points_.begin()+index);
		while(iter != fire_points_.end())
		{
			(*iter)->id_ = index++;
			++iter;
		}
	}
}

void WarheadModel::AddLeftEndCap(double length)
{
	if(left_end_cap_ /*|| sections_.size() == 0*/)
		return ;
	Q_ASSERT(sections_.size()>0);
	double r = sections_.first()->get_outer_left_half_height();
	left_end_cap_ = new WarheadEndCap(cs_.Get_UnitSystem(), r, 0, length);
	//移动右侧段及由端盖
	foreach(WarheadSection* section, sections_)
		section->Translate(length);
	if(right_end_cap_)
		right_end_cap_->set_pos_x(right_end_cap_->get_pos_x()+length);
	//更新所有起爆点

}
void WarheadModel::AddRightEndCap(double length)
{
	if(right_end_cap_/* || sections_.size() == 0*/)
		return ;
	Q_ASSERT(sections_.size()>0);
	double r = sections_.back()->get_outer_right_half_height();
	UpdateLength();
	double pos_x = character_data_.length;
	right_end_cap_ = new WarheadEndCap(cs_.Get_UnitSystem(), r, pos_x, length);
}
void WarheadModel::UpdateEndCap()
{
	UpdateLeftEndCap();
	UpdateRightEndCap();
}
void WarheadModel::UpdateLeftEndCap()
{
	if(left_end_cap_)
	{
		if(sections_.size()>0)
			left_end_cap_->set_r(sections_.first()->get_outer_left_half_height());
	}
}
void WarheadModel::UpdateRightEndCap()
{
	if(right_end_cap_)
	{
		UpdateLength();
		right_end_cap_->set_pos_x(character_data_.length-right_end_cap_->get_length());
		if(sections_.size()>0)
			right_end_cap_->set_r(sections_.back()->get_outer_right_half_height());
	}
}
void WarheadModel::AdjustAfterNodePosX(const WarheadEndCap* end_cap, double dx)
{
	Q_ASSERT(end_cap);
	if(end_cap != left_end_cap_)
		return ;
	foreach(WarheadSection* section, sections_)
		section->Translate(dx);
	if(right_end_cap_)
		right_end_cap_->set_pos_x(right_end_cap_->get_pos_x() + dx);
}
void WarheadModel::UpdateLength()
{
	character_data_.length = 0;
	if(left_end_cap_)
		character_data_.length += left_end_cap_->get_length();
	foreach(WarheadSection* section, sections_)
		character_data_.length += section->get_length();
	if(right_end_cap_)
		character_data_.length += right_end_cap_->get_length();
}

void WarheadModel::UpdateMass()
{
	character_data_.charge_mass = 0;
	character_data_.shell_mass = 0;
	character_data_.frag_mass = 0;
	character_data_.mass = 0;
	foreach(WarheadSection* section, sections_)
	{
		section->CountMass();
		foreach(WarheadLayer* layer, section->get_layers())
		{
			double mass = layer->get_mass();
			switch(layer->get_layer_type())
			{
			case kShell: character_data_.shell_mass += mass; break;
			case kCharge: character_data_.charge_mass += mass; break;
			case kSphereFragment: character_data_.frag_mass += mass; break;
			case kLining: character_data_.mass += mass; break;
			}
		}
	}
	character_data_.mass += character_data_.charge_mass;
	character_data_.mass += character_data_.shell_mass;
	character_data_.mass += character_data_.frag_mass;

	if(left_end_cap_)
	{
		left_end_cap_->CountVolume();
		left_end_cap_->CountMass();
		character_data_.mass += left_end_cap_->get_mass();
	}
	if(right_end_cap_)
	{
		right_end_cap_->CountVolume();
		right_end_cap_->CountMass();
		character_data_.mass += right_end_cap_->get_mass();
	}
}

void WarheadModel::UpdateCharacterData()
{
	UpdateLength();
	UpdateMass();
}

//获取装药号
QString WarheadModel::GetChargeId() const
{
	if(sections_.size()>0)
	{
		WarheadLayer* layer = sections_.first()->get_layers().first();
		const Material* material = layer->get_material();
		if(material)
			return material->get_id();
	}
	return QString();
}
//是否是完整战斗部
bool WarheadModel::IsCompleteWarhaed() const
{
	if(fire_points_.size() > 0 && sections_.size() > 0)
		return true;
	return false;
}