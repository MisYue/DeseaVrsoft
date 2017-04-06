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
	//移动段
	void Translate(double dx) {	shape_describe_->Translate(dx); }

	//形状描述，设置形状描述时，会自动计算各层体积和质量
	void set_shape_describe(ShapeDescribe* shape_describe);
	const ShapeDescribe* get_shape_describe() const { return shape_describe_; }
	ShapeDescribe* get_shape_describe() { return shape_describe_; }
	//长度和高度
	double get_length() const { return shape_describe_->get_shape_length(); }
	double get_outer_left_half_height() const ;
	double get_outer_right_half_height() const ;
	double get_inner_left_half_height() const { return shape_describe_->get_shape_left_half_height(); }
	double get_inner_right_half_height() const { return shape_describe_->get_shape_right_half_height(); }
	//获取指定层距中轴线的左右高度
	void GetAwayHeight(WarheadLayer* layer, double& left_h, double& right_h) const;

	//计算质量
	void CountMass();
protected:
	//以下变量在段与段之间对齐使用
	QList<WarheadLayer*> layers_;	//段中的层
	osg::ref_ptr<ShapeDescribe> shape_describe_; //段的形状描述
	//计算体积
	void CountVolume();
};