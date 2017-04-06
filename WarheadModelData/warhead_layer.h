#pragma once

#include "warhead_node.h"
#include <QtCore>

//����������
enum WarheadLayerType
{
	kShell,		//����
	kCharge,	//װҩ
	kSphereFragment,	//������Ƭ
	kLining,	//�ڴ���

};

class WarheadSection;
class WARHEADMODELDATA_EXPORT WarheadLayer : public WarheadMassNode
{
	friend WarheadSection;

public:
	//������
	void set_layer_type(WarheadLayerType type) { type_ = type; }
	WarheadLayerType get_layer_type() const { return type_; }


protected:
	WarheadLayerType type_;	//������


};