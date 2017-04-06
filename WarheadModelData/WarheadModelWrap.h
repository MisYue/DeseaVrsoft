#pragma once
#include "warhead_model.h"

class MaterialLib;
class WARHEADMODELDATA_EXPORT WarheadModelWrap
{
public:
	enum UnitLength
	{
		kMm = 1,
		kCm = 2,
		kM = 3,
		kKm = 4,
	};
	enum UnitMass
	{
		kG = 1,
		kKg = 2,
	};

	WarheadModelWrap();
	virtual ~WarheadModelWrap(void);
	// ��ȡ�ṹ
	WarheadModel* get_structure(void)
	{
		return structure_;
	}
	const WarheadModel* get_structure(void) const
	{
		return structure_;
	}

	// ��ȡ������
	MaterialLib* get_metal_lib(void)
	{
		return metal_lib_;
	}
	const MaterialLib* get_metal_lib(void) const
	{
		return metal_lib_;
	}

	// ��ȡװҩ��
	MaterialLib* get_charge_lib(void)
	{
		return charge_lib_;
	}
	const MaterialLib* get_charge_lib(void) const
	{
		return charge_lib_;
	}

	// ��ȡϵͳ����ĳ��Ⱦ��ȣ�����С��λ��
	int GetLengthPrecisionHint() const;

	// ��ȡϵͳ������������ȣ�����С��λ��
	int GetMassPrecisionHint() const;
	
	// ��ȡ���ȵ�λ
	QString GetLengthUnit() const;

	// ��ȡ������λ
	QString GetMassUnit() const;

protected:
	// �ṹ
	WarheadModel* structure_;
	// ������
	MaterialLib* metal_lib_;
	// װҩ��
	MaterialLib* charge_lib_;
};

