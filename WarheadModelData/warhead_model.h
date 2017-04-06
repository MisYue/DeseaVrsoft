#ifndef WARHEAD_MODEL_DATA_H
#define WARHEAD_MODEL_DATA_H

#include <WarheadModelData/warhead_layer.h>
#include <WarheadModelData/warhead_section.h>
#include <WarheadModelData/warhead_fragment_layer.h>

class WarheadSection;
class WarheadLayer;

enum WarheadType
{
	kKill = 0,
	kPenetrator,
};
struct WarheadBasicData
{
	QString country; //国别
	QString served_time; //装备时间
	QString manufacturer; //制造厂家
	QString describe; //描述
};

struct WarheadCharacterData
{
	WarheadCharacterData() : mass(0), length(0), charge_mass(0), shell_mass(0), charge_volume(0), frag_mass(0) {}
	double mass; //质量
	double length; //长度
	double charge_mass; //装药质量
	double shell_mass; //壳体质量
	double charge_volume; //装药体积
	double frag_mass; //破片质量
};

//定义模型类
class WARHEADMODELDATA_EXPORT WarheadModel : public WarheadNode
{
public:
	WarheadModel();
	~WarheadModel();
	//段
	void AddSection(WarheadSection* new_section, WarheadSection* pos_section = 0,  bool left_pos = false);
	void DeleteSection(WarheadSection* section);
	QList<WarheadSection*> get_sections() const { return sections_; }
	int GetNumSection() const { return sections_.size(); }
	WarheadSection* GetSection(const WarheadLayer* layer);
	WarheadSection* GetNextSection(const WarheadSection* section);
	WarheadSection* GetPreviousSection(const WarheadSection* section);
	//调整指定段之后的段位置
	void AdjustAfterSectionPosX(WarheadSection* section, double dx);
	//基本数据
	void set_basic_data(const WarheadBasicData& basic_data) { basic_data_ = basic_data; }
	WarheadBasicData& get_basic_data() { return basic_data_; }
	WarheadBasicData get_basic_data() const { return basic_data_; }

	//特性数据
	void set_character_data(const WarheadCharacterData& character_data) { character_data_ = character_data; }
	WarheadCharacterData& get_character_data()  { return character_data_; }
	WarheadCharacterData get_character_data() const { return character_data_; }

	//坐标系
	void set_cs(const Bit_2DCSWithExpAndUS& cs) 
	{ 
		cs_ = cs; 
	}
	Bit_2DCSWithExpAndUS get_cs() const { return cs_; }
	Bit_2DCSWithExpAndUS& get_cs() { return cs_; }

	//类型
	void set_type(WarheadType type) { type_ = type; }
	WarheadType get_type() const { return type_; }

	//端盖
	WarheadEndCap* get_left_end_cap() { return left_end_cap_; }
	WarheadEndCap* get_right_end_cap() { return right_end_cap_; }
	const WarheadEndCap* get_left_end_cap() const { return left_end_cap_; }
	const WarheadEndCap* get_right_end_cap() const { return right_end_cap_; }
	void AddLeftEndCap(double length);
	void AddRightEndCap(double length);
	void DeleteLeftEndCap() 
	{ 
		AdjustAfterNodePosX(left_end_cap_, -left_end_cap_->get_length());
		delete left_end_cap_; 
		left_end_cap_ = 0;
	}
	void DeleteRightEndCap() 
	{ 
		delete right_end_cap_; 
		right_end_cap_ = 0; 
	}
	void UpdateEndCap();
	void UpdateLeftEndCap();
	void UpdateRightEndCap();
	//调整端盖之后的段位置
	void AdjustAfterNodePosX(const WarheadEndCap* end_cap, double dx);
	//起爆点
	WarheadFirePoint* AddFirePoint(const Bit_Point2D& pos);
	void DeleteFirePoint(int index);
	QList<WarheadFirePoint*> get_fire_points() const { return fire_points_; }

	//长度
	void UpdateLength();
	//质量
	void UpdateMass();
	//更新特性数据
	void UpdateCharacterData();

	//获取装药号
	QString GetChargeId() const;

	//是否是完整战斗部，只有完整战斗部才能进行威力分析
	bool IsCompleteWarhaed() const ;
protected:
	WarheadType type_; //类型
	WarheadBasicData basic_data_;
	WarheadCharacterData character_data_;
	Bit_2DCSWithExpAndUS cs_;	//坐标系

	WarheadEndCap* left_end_cap_;	//左端盖
	WarheadEndCap* right_end_cap_;	//右端盖
	QList<WarheadFirePoint*> fire_points_;	//起爆点
	QList<WarheadSection*> sections_; //所有段
};

#endif // WARHEAD_MODEL_DATA_H
