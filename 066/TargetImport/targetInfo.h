//***************************************
//	创建时间:	2015:10:25   17:13
//	文件名称: 	targetInfo.h
//	文件作者:	岳群磊
//	
//	功能说明:	定义目标类
//***************************************

#pragma once
#include "TargetImportGlobal.h"
#include <QStringList>
#include <map>
#include <vector>
#include <list>
#include <string>
#include <stack>
#include <osg/Array>

class TiXmlElement;

namespace TIMP
{
	//三角网格、包围盒
	struct PartDrawInfo
	{
		std::string _name;
		osg::ref_ptr<osg::Vec3Array> _vertexes;
		osg::ref_ptr<osg::Vec3Array> _normals;
		osg::ref_ptr<osg::Vec4Array> _colors;
		osg::Vec3 _centerBox;
		osg::Vec3 _sizeBox;
		PartDrawInfo()
			: _vertexes(new osg::Vec3Array),
			_normals(new osg::Vec3Array),
			_colors(new osg::Vec4Array)
		{}
	};

	struct PartExtraInfo
	{
	public:
		PartExtraInfo();
		std::string GetPropertyValue(const std::string& name) const
		{
			std::map<std::string, std::string>::const_iterator iter = _properties.find(name);
			if(iter != _properties.end())
				return iter->second;
			return "";
		}
		void SetPropertyValue(const std::string& name, const std::string& value)
		{
			std::map<std::string, std::string>::iterator iter = _properties.find(name);
			if(iter != _properties.end())
				iter->second = value;
		}
	private:
		std::map<std::string, std::string> _properties;
	};

	enum LogicGate
	{
		LG_AND,
		LG_OR,
	};
	struct KillTreeNode
	{
		std::vector<std::pair<std::string, bool> > childrenList;
		int childNum;
		int logic;
		int grade;
		double weight;
		std::string name;
		std::string code;

	};

	typedef std::map<std::string, PartDrawInfo> TargetDrawInfo;
	typedef std::map<std::string, PartExtraInfo> TargetExtraInfo;
	typedef std::map<std::string, KillTreeNode> TargetKillTree;


	class TARGETIMPORT_API TargetInfo
	{
	public:
		TargetInfo();
		void Reset();
		bool SaveTarget(const std::string& fileName);
		bool OpenTarget(const std::string& fileName);
		std::string GetXmlDamageTree();
		void DeleteTarget();
		void SetKillTreeText(const QString& text)
		{
			_killTreeText = text;
		}
		QString GetKillTreeText()
		{
			return _killTreeText;
		}
		PartExtraInfo& GetPartExtraInfo(const std::string& partName);
		
		osg::Vec4dArray* GetVertexes();
		void UpdateExtraInfo();
		std::string& GetName()
		{
			return _name;
		}
		const QStringList& GetPartsName()
		{
			return _partsName;
		}
		std::map<std::string, PartDrawInfo>& GetPartDrawInfo()
		{
			return _partsDrawInfo;
		}
		TargetKillTree& GetTargetKillTree()
		{
			return _killTree;
		}
		void UpdatePartName(const std::string& oldName, const std::string& newName)
		{
			if(oldName == newName)
				return ;
			std::map<std::string, PartDrawInfo>::iterator iter = _partsDrawInfo.find(oldName);
			if(iter != _partsDrawInfo.end())
			{
				PartDrawInfo& info = iter->second;
				info._name = newName;
				_partsDrawInfo.insert(std::make_pair(newName, info));
				_partsDrawInfo.erase(iter);
			}
			std::map<std::string, PartExtraInfo>::iterator iter2 = _partsExtraInfo.find(oldName);
			if(iter2 != _partsExtraInfo.end())
			{
				PartExtraInfo& info = iter2->second;
				info.SetPropertyValue("name", newName);
				_partsExtraInfo.insert(std::make_pair(newName, info));
				_partsExtraInfo.erase(iter2);
			}
		}
	private:
		std::string _name;
		QStringList _partsName;
		QString _killTreeText;
		std::map<std::string, PartDrawInfo> _partsDrawInfo;
		std::map<std::string, PartExtraInfo> _partsExtraInfo;
		std::map<std::string, KillTreeNode> _killTree;
		void CreateXmlElement(KillTreeNode& node, std::vector<std::stack<KillTreeNode> >& vec, TiXmlElement* parent);
	};

}