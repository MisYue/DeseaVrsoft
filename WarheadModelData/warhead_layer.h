#pragma once

#include "warhead_node.h"
#include <QtCore>

//定义层的类型
enum WarheadLayerType
{
	kShell,		//壳体
	kCharge,	//装药
	kSphereFragment,	//球形破片
	kLining,	//内纯层

};

class WarheadSection;
class WARHEADMODELDATA_EXPORT WarheadLayer : public WarheadMassNode
{
	friend WarheadSection;

public:
	//层类型
	void set_layer_type(WarheadLayerType type) { type_ = type; }
	WarheadLayerType get_layer_type() const { return type_; }


protected:
	WarheadLayerType type_;	//层类型


};