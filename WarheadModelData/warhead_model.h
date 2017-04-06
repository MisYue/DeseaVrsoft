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
	QString country; //����
	QString served_time; //װ��ʱ��
	QString manufacturer; //���쳧��
	QString describe; //����
};

struct WarheadCharacterData
{
	WarheadCharacterData() : mass(0), length(0), charge_mass(0), shell_mass(0), charge_volume(0), frag_mass(0) {}
	double mass; //����
	double length; //����
	double charge_mass; //װҩ����
	double shell_mass; //��������
	double charge_volume; //װҩ���
	double frag_mass; //��Ƭ����
};

//����ģ����
class WARHEADMODELDATA_EXPORT WarheadModel : public WarheadNode
{
public:
	WarheadModel();
	~WarheadModel();
	//��
	void AddSection(WarheadSection* new_section, WarheadSection* pos_section = 0,  bool left_pos = false);
	void DeleteSection(WarheadSection* section);
	QList<WarheadSection*> get_sections() const { return sections_; }
	int GetNumSection() const { return sections_.size(); }
	WarheadSection* GetSection(const WarheadLayer* layer);
	WarheadSection* GetNextSection(const WarheadSection* section);
	WarheadSection* GetPreviousSection(const WarheadSection* section);
	//����ָ����֮��Ķ�λ��
	void AdjustAfterSectionPosX(WarheadSection* section, double dx);
	//��������
	void set_basic_data(const WarheadBasicData& basic_data) { basic_data_ = basic_data; }
	WarheadBasicData& get_basic_data() { return basic_data_; }
	WarheadBasicData get_basic_data() const { return basic_data_; }

	//��������
	void set_character_data(const WarheadCharacterData& character_data) { character_data_ = character_data; }
	WarheadCharacterData& get_character_data()  { return character_data_; }
	WarheadCharacterData get_character_data() const { return character_data_; }

	//����ϵ
	void set_cs(const Bit_2DCSWithExpAndUS& cs) 
	{ 
		cs_ = cs; 
	}
	Bit_2DCSWithExpAndUS get_cs() const { return cs_; }
	Bit_2DCSWithExpAndUS& get_cs() { return cs_; }

	//����
	void set_type(WarheadType type) { type_ = type; }
	WarheadType get_type() const { return type_; }

	//�˸�
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
	//�����˸�֮��Ķ�λ��
	void AdjustAfterNodePosX(const WarheadEndCap* end_cap, double dx);
	//�𱬵�
	WarheadFirePoint* AddFirePoint(const Bit_Point2D& pos);
	void DeleteFirePoint(int index);
	QList<WarheadFirePoint*> get_fire_points() const { return fire_points_; }

	//����
	void UpdateLength();
	//����
	void UpdateMass();
	//������������
	void UpdateCharacterData();

	//��ȡװҩ��
	QString GetChargeId() const;

	//�Ƿ�������ս������ֻ������ս�������ܽ�����������
	bool IsCompleteWarhaed() const ;
protected:
	WarheadType type_; //����
	WarheadBasicData basic_data_;
	WarheadCharacterData character_data_;
	Bit_2DCSWithExpAndUS cs_;	//����ϵ

	WarheadEndCap* left_end_cap_;	//��˸�
	WarheadEndCap* right_end_cap_;	//�Ҷ˸�
	QList<WarheadFirePoint*> fire_points_;	//�𱬵�
	QList<WarheadSection*> sections_; //���ж�
};

#endif // WARHEAD_MODEL_DATA_H
