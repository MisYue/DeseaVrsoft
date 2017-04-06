#pragma once
#include "warhead_node.h"
#include <QtCore>

class WarheadLayer;
class Material;
class WARHEADMODELDATA_EXPORT WarheadSection : public WarheadNode
{
public:
	WarheadSection(ShapeDescribe* shape_describe, const Material* material);
	~WarheadSection();
	QList<WarheadLayer*> get_layers() const { return layers_; }
	QVector<WarheadLayer*> get_layers_vector() const { return layers_.toVector(); }
	void AddLayer(WarheadLayer* new_layer, WarheadLayer* pos_layer, bool outer_pos = true);
	void DeleteLayer(WarheadLayer* layer);
	WarheadLayer* GetFirstLayer();
	WarheadLayer* GetLastLayer();
	WarheadLayer* GetNextLayer(const WarheadLayer* layer);
	WarheadLayer* GetPreviousLayer(const WarheadLayer* layer);
	int GetLayerNum() const { return layers_.size(); }
	void ReplaceLayer(WarheadLayer* old_layer, WarheadLayer* new_layer);
	//�ƶ���
	void Translate(double dx) {	shape_describe_->Translate(dx); }

	//��״������������״����ʱ�����Զ�����������������
	void set_shape_describe(ShapeDescribe* shape_describe);
	const ShapeDescribe* get_shape_describe() const { return shape_describe_; }
	ShapeDescribe* get_shape_describe() { return shape_describe_; }
	//���Ⱥ͸߶�
	double get_length() const { return shape_describe_->get_shape_length(); }
	double get_outer_left_half_height() const ;
	double get_outer_right_half_height() const ;
	double get_inner_left_half_height() const { return shape_describe_->get_shape_left_half_height(); }
	double get_inner_right_half_height() const { return shape_describe_->get_shape_right_half_height(); }
	//��ȡָ����������ߵ����Ҹ߶�
	void GetAwayHeight(WarheadLayer* layer, double& left_h, double& right_h) const;

	//��������
	void CountMass();
protected:
	//���±����ڶ����֮�����ʹ��
	QList<WarheadLayer*> layers_;	//���еĲ�
	osg::ref_ptr<ShapeDescribe> shape_describe_; //�ε���״����
	//�������
	void CountVolume();
};