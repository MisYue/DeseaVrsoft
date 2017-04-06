#include "warhead_section.h"
#include "warhead_layer.h"
#include "warhead_fragment_layer.h"
#include <BasicTool/expandqtcore.h>

WarheadSection::WarheadSection(ShapeDescribe* shape_describe, const Material* material)
	: shape_describe_(shape_describe)
{
	Q_ASSERT_X(shape_describe_, ExpandQtCore::fromGBK("WarheadSection构造函数").toStdString().c_str(), ExpandQtCore::fromGBK("ShapeDescribe为空").toStdString().c_str());
	WarheadLayer* charge_layer = new WarheadLayer;
	charge_layer->set_layer_type(kCharge);
	charge_layer->set_material(material);
	charge_layer->set_shape_describe(shape_describe);
	layers_.push_back(charge_layer);
}
WarheadSection::~WarheadSection()
{
	qDeleteAll(layers_);
}
double WarheadSection::get_outer_left_half_height() const 
{
	double outer_left_half_height = get_inner_left_half_height();
	QList<WarheadLayer*>::const_iterator iter = layers_.begin()+1;
	while(iter != layers_.end())
	{
		ShapeThickness thickness = (*iter)->get_thickness();
		Q_ASSERT(thickness.type != kNo);
		outer_left_half_height += thickness.left;
		++iter;
	}
	return outer_left_half_height;
}
double WarheadSection::get_outer_right_half_height() const 
{
	double outer_right_half_height = get_inner_right_half_height();
	QList<WarheadLayer*>::const_iterator iter = layers_.begin()+1;
	while(iter != layers_.end())
	{
		ShapeThickness thickness = (*iter)->get_thickness();
		Q_ASSERT(thickness.type != kNo);
		outer_right_half_height += thickness.right;
		++iter;
	}
	return outer_right_half_height;
}
void WarheadSection::GetAwayHeight(WarheadLayer* layer, double& left_h, double& right_h) const
{
	left_h = get_inner_left_half_height();
	right_h = get_inner_right_half_height();
	QList<WarheadLayer*>::const_iterator iter = layers_.begin();
	while(++iter != layers_.end())
	{
		if((*iter) == layer)
			break;
		ShapeThickness thickness = (*iter)->get_thickness();
		Q_ASSERT(thickness.type != kNo);
		left_h += thickness.left;
		right_h += thickness.right;
	}
}
void WarheadSection::AddLayer(WarheadLayer* new_layer, WarheadLayer* pos_layer, bool outer_pos)
{
	Q_ASSERT_X(pos_layer != 0, "WarheadSection::AddLayer", "pos_layer == NULL");
	QList<WarheadLayer*>::iterator pos_iter = layers_.begin();
	while(pos_iter != layers_.end())
	{
		if((*pos_iter) == pos_layer)
			break;
		++pos_iter;
	}
	if(pos_iter != layers_.end())
	{
		if(!outer_pos)
			layers_.insert(pos_iter, new_layer);
		else
			layers_.insert(pos_iter+1, new_layer);
		new_layer->set_shape_describe(shape_describe_);
	}
	if(WarheadFragmentLayer* frag_layer = dynamic_cast<WarheadFragmentLayer*>(new_layer))
		frag_layer->UpdateFragments();
}
void WarheadSection::DeleteLayer(WarheadLayer* layer)
{
	int i = layers_.indexOf(layer);
	if (i != -1)
		delete layers_.takeAt(i);
}
WarheadLayer* WarheadSection::GetFirstLayer()
{
	WarheadLayer* result = 0;
	if(!layers_.isEmpty())
		result = layers_.front();
	return result;
}
WarheadLayer* WarheadSection::GetLastLayer()
{
	WarheadLayer* result = 0;
	if(!layers_.isEmpty())
		result = layers_.back();
	return result;
}
WarheadLayer* WarheadSection::GetNextLayer(const WarheadLayer* layer)
{
	WarheadLayer* result = 0;
	QList<WarheadLayer*>::iterator iter = layers_.begin();
	while(iter != layers_.end())
	{
		if(*iter == layer)
			break;
		++iter;
	}
	if(iter != layers_.end() && (iter+1) != layers_.end())
		result = *(iter+1);
	return result;
}
WarheadLayer* WarheadSection::GetPreviousLayer(const WarheadLayer* layer)
{
	WarheadLayer* result = 0;
	QList<WarheadLayer*>::iterator iter = layers_.begin();
	while(iter != layers_.end())
	{
		if(*iter == layer)
			break;
		++iter;
	}
	if(iter != layers_.end() && (iter-1) != layers_.end())
		result = *(iter-1);
	return result;
}
void WarheadSection::ReplaceLayer(WarheadLayer* old_layer, WarheadLayer* new_layer)
{
	Q_ASSERT_X(old_layer != 0, "WarheadSection::ReplaceLayer", "old_layer == NULL");
	QList<WarheadLayer*>::iterator pos_iter = layers_.begin();
	while(pos_iter != layers_.end())
	{
		if((*pos_iter) == old_layer)
			break;
		++pos_iter;
	}
	if(pos_iter != layers_.end())
	{
		layers_.insert(pos_iter, new_layer);
		layers_.removeAll(old_layer);
		delete old_layer;
		new_layer->set_shape_describe(shape_describe_);
		if(WarheadFragmentLayer* frag_layer = dynamic_cast<WarheadFragmentLayer*>(new_layer))
			frag_layer->UpdateFragments();
		new_layer->set_shape_describe(shape_describe_);
	}

}

void WarheadSection::set_shape_describe(ShapeDescribe* shape_describe)
{
	shape_describe_ = shape_describe;
	foreach(WarheadLayer* layer, layers_)
		layer->set_shape_describe(shape_describe);
}

//计算体积
void WarheadSection::CountVolume()
{
	double left_h = 0;
	double right_h = 0;
	QList<WarheadLayer*>::iterator iter = layers_.begin();
	(*iter)->volume_ = shape_describe_->CountVolume(0, 0);
	double volume_inner = (*iter)->volume_;
	while(++iter != layers_.end())
	{
		ShapeThickness thickness = (*iter)->get_thickness();
		left_h += thickness.left;
		right_h += thickness.right;
		if(SphereFragmentLayer* spere_layer = dynamic_cast<SphereFragmentLayer*>(*iter))
		{
			spere_layer->CountVolume();
			volume_inner = shape_describe_->CountVolume(left_h, right_h);
		}
		else
		{
			double volume = shape_describe_->CountVolume(left_h, right_h);
			(*iter)->volume_ = volume - volume_inner;
			volume_inner = volume;
		}
	}
}

//计算质量
void WarheadSection::CountMass()
{
	CountVolume();
	foreach(WarheadLayer* layer, layers_)
		layer->CountMass();
}