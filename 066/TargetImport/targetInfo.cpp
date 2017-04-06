#include "TargetInfo.h"
#include "../tinyxml/tinyxml.h"
#include "StringExtend.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stack>
#include <QUuid>

namespace TIMP
{
	static bool readline(std::istream& fin, char* line, const int LINE_SIZE)
	{
		if (LINE_SIZE<1) return false;

		bool eatWhiteSpaceAtStart = true;
		bool changeTabsToSpaces = true;

		char* ptr = line;
		char* end = line+LINE_SIZE-1;
		bool skipNewline = false;
		while (fin && ptr<end)
		{

			int c=fin.get();
			int p=fin.peek();
			if(c == ';') c = ' ';
			if (c=='\r')
			{
				if (p=='\n')
				{
					// we have a windows line endings.
					fin.get();
					// OSG_NOTICE<<"We have dos line ending"<<std::endl;
					if (skipNewline)
					{
						skipNewline = false;
						*ptr++ = ' ';
						continue;
					}
					else break;
				}
				// we have Mac line ending
				// OSG_NOTICE<<"We have mac line ending"<<std::endl;
				if (skipNewline)
				{
					skipNewline = false;
					*ptr++ = ' ';
					continue;
				}
				else break;
			}
			else if (c=='\n')
			{
				// we have unix line ending.
				// OSG_NOTICE<<"We have unix line ending"<<std::endl;
				if (skipNewline)
				{
					*ptr++ = ' ';
					continue;
				}
				else break;
			}
			else if (c=='\\' && (p=='\r' || p=='\n'))
			{
				// need to keep return;
				skipNewline = true;
			}
			else if (c!=std::ifstream::traits_type::eof()) // don't copy eof.
			{
				skipNewline = false;

				if (!eatWhiteSpaceAtStart || (c!=' ' && c!='\t'))
				{
					eatWhiteSpaceAtStart = false;
					*ptr++ = c;
				}
			}


		}

		// strip trailing spaces
		while (ptr>line && *(ptr-1)==' ')
		{
			--ptr;
		}

		*ptr = 0;

		if (changeTabsToSpaces)
		{

			for(ptr = line; *ptr != 0; ++ptr)
			{
				if (*ptr == '\t') *ptr=' ';
			}
		}

		return true;
	}
	PartExtraInfo::PartExtraInfo()
	{
		_properties["name"] = "未命名";
		_properties["code"] = "未命名";
		_properties["shell"] = "0";
		_properties["thickness"] = "15";
		_properties["material"] = "金属,铁";
		_properties["criterionEMT"] = "0,金属,铁,20";
		_properties["criterionKE"] = "0,长方体,100.0,150.0";
		_properties["criterionFRAG"] = "0,金属,铁,长方体,10,150.0,5";
		_properties["criterionSW"] = "0,0,0.05,0.0,0.0,10.0,15.0";
		_properties["geometryType"] = "长方体";
		_properties["geometryCoor"] = "0.0,0.0,0.0";
		_properties["geometryCoorDsb"] = "右手坐标系，以长方体的中心为原点";
		_properties["geometrySize"] = "0.0,1.0,1.0,1.0";
		_properties["geometryColor"] = "125,125,125,200";
		_properties["keyPart"] = "0";
	}

	TargetInfo::TargetInfo()
	{

	}

	void TargetInfo::Reset()
	{
		_name = "";
		_partsName.clear();

		_partsDrawInfo.clear();
		_partsExtraInfo.clear();
		_killTreeText.clear();
	}
	void TargetInfo::DeleteTarget()
	{
		if(_name.size()>0)
		{
			remove(_name.c_str());
			Reset();
		}
	}
	PartExtraInfo& TargetInfo::GetPartExtraInfo(const std::string& partName)
	{
		std::map<std::string, PartExtraInfo>::iterator iter = _partsExtraInfo.find(partName);
		if(_partsExtraInfo.end() != iter)
			return iter->second;
		else
		{
			return _partsExtraInfo.insert(std::make_pair(partName, PartExtraInfo())).first->second;
		}
	}

	void TargetInfo::UpdateExtraInfo()
	{
		for(std::map<std::string, PartDrawInfo>::iterator beg = _partsDrawInfo.begin();
			beg != _partsDrawInfo.end();
			++beg)
		{
			const std::string& name = beg->first;
			_partsName.push_back(QString::fromLocal8Bit(name.c_str()));
			PartExtraInfo partExtraInfo;
			partExtraInfo.SetPropertyValue("name", name);
			partExtraInfo.SetPropertyValue("code", name);
			_partsExtraInfo.insert(std::make_pair(name, partExtraInfo));
		}
	}

	bool TargetInfo::SaveTarget(const std::string& fileName)
	{
		setlocale(LC_ALL, "Chinese-simplified");
		//std::locale::global(std::locale("")); //将全局区域设为操作系统默认区域
		std::ofstream ofs(fileName.c_str());
		//std::locale::global(std::locale("C")); //还原全局区域
		if(!ofs) return false;
		_name = fileName;
		//int pos1 = fileName.find_last_of('/');
		//if(pos1 == std::string::npos)
		//	pos1 = 0;
		//int pos2 = fileName.find_last_of('.');
		//_name = fileName.substr(pos1+1, pos2-pos1-1);
		int index=1;
		int partIndex = 1;
		char sep=';';
		osg::Vec3Array* nodes;
		ofs << "*Node\n";
		//*Node
		for(std::map<std::string, PartDrawInfo>::iterator beg = _partsDrawInfo.begin(); beg != _partsDrawInfo.end(); ++beg, ++partIndex)
		{
			nodes = beg->second._vertexes.get();
			for(unsigned i=0, n=nodes->size(); i<n; ++i)
				ofs << index++ << sep << partIndex << sep << nodes->at(i)[0] << sep << nodes->at(i)[1] << sep << nodes->at(i)[2] << "\n";
		}
		//*Box
		index = 1;
		partIndex = 1;
		ofs << "*Box\n";
		for(std::map<std::string, PartDrawInfo>::iterator beg = _partsDrawInfo.begin(); beg != _partsDrawInfo.end(); ++beg)
		{
			ofs << index++ << sep << partIndex++ << sep << beg->second._centerBox[0] << sep << beg->second._centerBox[1] << sep << beg->second._centerBox[2] << sep;
			ofs << beg->second._sizeBox[0] << sep << beg->second._sizeBox[1] << sep << beg->second._sizeBox[2] << "\n";
		}
		//*Part
		partIndex = 1;
		ofs << "*Part\n";
		for(std::map<std::string, PartExtraInfo>::iterator beg = _partsExtraInfo.begin(); beg != _partsExtraInfo.end(); ++beg)
		{
			ofs << partIndex++ << sep ;
			ofs << beg->second.GetPropertyValue("name") << sep;
			ofs << beg->second.GetPropertyValue("code") << sep;
			ofs << beg->second.GetPropertyValue("keyPart") << sep;
			ofs << beg->second.GetPropertyValue("shell") << sep;
			ofs << beg->second.GetPropertyValue("thickness") << sep;
			ofs << beg->second.GetPropertyValue("material") << sep;
			ofs << beg->second.GetPropertyValue("criterionEMT") << sep;
			ofs << beg->second.GetPropertyValue("criterionKE") << sep;
			ofs << beg->second.GetPropertyValue("criterionFRAG") << sep;
			ofs << beg->second.GetPropertyValue("criterionSW") << "\n";
		}

		ofs << "*Part_Group\n";
		ofs << _killTreeText.toLocal8Bit().data();
		return true;
	}
	bool TargetInfo::OpenTarget(const std::string& fileName)
	{
		if(fileName.substr(fileName.size()-4) != ".vrs")
			return false;
		setlocale(LC_ALL, "Chinese-simplified");
		//std::locale::global(std::locale("")); //将全局区域设为操作系统默认区域
		std::ifstream ifs(fileName.c_str());
		//std::locale::global(std::locale("C")); //还原全局区域
		if(!ifs) return false;
		_partsDrawInfo.clear();
		_name = fileName;
		_partsExtraInfo.clear();
		_partsName.clear();
		_killTreeText.clear();
		unsigned pos = fileName.find_last_of('/');
		//if(pos != std::string::npos)
		//	_name = fileName.substr(pos+1);
		//else _name = fileName;
		PartDrawInfo partDrawInfo;
		const int LINE_SIZE = 1024;
		char line[LINE_SIZE];
		int index, partIndex;
		char sep;
		osg::Vec3d vec3d;
		osg::Vec3d vec3d2;
		std::string name;
		std::string code;
		std::string keyPart;
		std::string shell;
		std::string thickness;
		std::string material;
		std::string criterionEMT;
		std::string criterionKE;
		std::string criterionFRAG;
		std::string criterionSW;

		int flag = 0; //1:Node 2:Part 3:Box 4:Part_Group

		std::map<int, osg::ref_ptr<osg::Vec3Array> > vertexes;
		std::map<int, osg::ref_ptr<osg::Vec3Array> >::iterator iter;
		std::map<int, std::string> partsName;
		std::map<int, std::pair<osg::Vec3d, osg::Vec3d> > boxes;
		
		while(!ifs.eof())
		{
			readline(ifs, line, LINE_SIZE);
			std::istringstream istr;
			istr.str(line);
			if(!strcmp("*Node", line)) 
				flag = 1;
			else if(!strcmp("*Part", line)) 
				flag = 2;
			else if(!strcmp("*Box", line))
				flag = 3;
			else if(!strcmp("*Part_Group", line))
			{	
				char c;
				std::string buffer;
				buffer.reserve(1024*10);
				while(!ifs.eof())
				{
					c = ifs.get();
					buffer.push_back(c);
				}
				_killTreeText = QString::fromLocal8Bit(buffer.c_str());
			}
			else
			{
				switch(flag)
				{
				case 1:
					{
						istr >> index /*>> sep*/ >> partIndex/* >> sep*/ >> vec3d[0] >> /*sep >>*/ vec3d[1] >> /*sep >>*/ vec3d[2];
						iter = vertexes.find(partIndex);
						if(iter == vertexes.end())
							iter = vertexes.insert(std::make_pair(partIndex, new osg::Vec3Array)).first;
						iter->second->push_back(vec3d);
					}
					break;
				case 2:
					{
						istr >> partIndex /*>> sep*/ >> name /*>> sep*/ >> code /*>> sep*/ >> keyPart >> /*sep >>*/ shell >> /*sep >>*/ thickness >> /*sep >>*/ material /*>> sep*/ ;
						istr >> criterionEMT /*>> sep*/ >> criterionKE >> /*sep >>*/ criterionFRAG >> /*sep >>*/ criterionSW;
						partsName.insert(std::make_pair(partIndex, name));
						PartExtraInfo partExtraInfo;
						partExtraInfo.SetPropertyValue("name", name);
						partExtraInfo.SetPropertyValue("code", code);
						partExtraInfo.SetPropertyValue("keyPart", keyPart);
						partExtraInfo.SetPropertyValue("shell", shell);
						partExtraInfo.SetPropertyValue("thickness", thickness);
						partExtraInfo.SetPropertyValue("material", material);
						partExtraInfo.SetPropertyValue("criterionEMT", criterionEMT);
						partExtraInfo.SetPropertyValue("criterionKE", criterionKE);
						partExtraInfo.SetPropertyValue("criterionFRAG", criterionFRAG);
						partExtraInfo.SetPropertyValue("criterionSW", criterionSW);
						_partsExtraInfo.insert(std::make_pair(name, partExtraInfo));
						_partsName.push_back(QString::fromLocal8Bit(name.c_str()));
					}
					break;
				case 3:
					{
						istr >> index >> partIndex >> vec3d[0] >> vec3d[1] >> vec3d[2] >> vec3d2[0] >> vec3d2[1] >> vec3d[2];
						boxes.insert(std::make_pair(partIndex, std::make_pair(vec3d, vec3d2)));
					}
					break;
				}
			}
		}

		for(std::map<int, osg::ref_ptr<osg::Vec3Array> >::iterator beg = vertexes.begin(); beg != vertexes.end(); ++beg)
		{
			int partIndex = beg->first;
			std::map<int, std::string>::iterator iter = partsName.find(partIndex);
			if(iter != partsName.end())
			{
				PartDrawInfo partDrawInfo;
				partDrawInfo._vertexes = beg->second;
				partDrawInfo._name = iter->second;
				int size = partDrawInfo._vertexes->size();
				partDrawInfo._normals = new osg::Vec3Array; 
				partDrawInfo._normals->reserve(size/3);
				std::map<int, std::pair<osg::Vec3d, osg::Vec3d> >::iterator iter2 = boxes.find(partIndex);
				partDrawInfo._centerBox = iter2->second.first;
				partDrawInfo._sizeBox = iter2->second.second;
				for(int i=0; i<size/3; ++i)
				{
					osg::Vec3& v1 = partDrawInfo._vertexes->at(i*3);
					osg::Vec3& v2 = partDrawInfo._vertexes->at(i*3+1);
					osg::Vec3& v3 = partDrawInfo._vertexes->at(i*3+2);
					osg::Vec3 normal = (v2-v1)^(v3-v2);
					normal.normalize();
					partDrawInfo._normals->push_back(normal);
				}
				_partsDrawInfo.insert(std::make_pair(iter->second, partDrawInfo));
			}
		}
		return true;
	}

	void TargetInfo::CreateXmlElement(KillTreeNode& node, std::vector<std::stack<KillTreeNode> >& vec, TiXmlElement* parent)
	{
		if(node.childNum == 0)
		{
			TiXmlElement element("Pa");
			element.SetAttribute("FunctionPartName", node.name);
			std::string guid = QUuid::createUuid().toString().toLocal8Bit().data();
			element.SetAttribute("GUID", guid);
			element.SetAttribute("Weight", node.weight);
			std::map<std::string, PartExtraInfo>::iterator iter = _partsExtraInfo.find(node.name);
			std::map<std::string, PartDrawInfo>::iterator iter2 = _partsDrawInfo.find(node.name);
			PartExtraInfo& partExtraInfo = iter->second;
			PartDrawInfo& partDrawInfo = iter2->second;
			element.SetAttribute("T", partExtraInfo.GetPropertyValue("thickness"));
			element.SetAttribute("Shell", partExtraInfo.GetPropertyValue("shell")!="0"? "YES" : "NO");
			element.SetAttribute("MaterialGUID", StringExtend::toString(0));
			std::vector<std::string> params;
			StringExtend::toStrings(partExtraInfo.GetPropertyValue("material"), ',', params);
			element.SetAttribute("MaterialType", params[0]);
			element.SetAttribute("MaterialName", params[1]);
			element.SetAttribute("GeometryType", "CUBE");
			double scale = 1000;
			TiXmlElement center("Centre");
			{
				TiXmlElement child_X("CuboidCenterPoint_x");
				child_X.SetAttribute("value", StringExtend::toString(partDrawInfo._centerBox[0]*scale));
				TiXmlElement child_Y("CuboidCenterPoint_y");
				child_Y.SetAttribute("value", StringExtend::toString(partDrawInfo._centerBox[1]*scale));
				TiXmlElement child_Z("CuboidCenterPoint_z");
				child_Z.SetAttribute("value", StringExtend::toString(partDrawInfo._centerBox[2]*scale));
				center.InsertEndChild(child_X);
				center.InsertEndChild(child_Y);
				center.InsertEndChild(child_Z);
			}
			TiXmlElement size("EquivalentModelSize");
			{
				TiXmlElement size_X("CuboidXDirectionLength");
				size_X.SetAttribute("value", StringExtend::toString(partDrawInfo._sizeBox[0]*scale));
				TiXmlElement size_Y("CuboidYDirectionLength");
				size_Y.SetAttribute("value", StringExtend::toString(partDrawInfo._sizeBox[1]*scale));
				TiXmlElement size_Z("CuboidZDirectionLength");
				size_Z.SetAttribute("value", StringExtend::toString(partDrawInfo._sizeBox[2]*scale));
				size.InsertEndChild(size_X);
				size.InsertEndChild(size_Y);
				size.InsertEndChild(size_Z);
			}
			TiXmlElement fragment("Fragment");
			fragment.SetAttribute("PartDamageCriterionType", "YES");
			{
				TiXmlElement material("Material");
				material.SetAttribute("value", StringExtend::toString(0));
				TiXmlElement shape("Shape");
				shape.SetAttribute("value", "CUBE");
				TiXmlElement velocity("Velocity");
				velocity.SetAttribute("value", "1400");
				TiXmlElement angle("Angle");
				angle.SetAttribute("value", "90");
				TiXmlElement quality("Quality");
				quality.SetAttribute("value", "10");
				TiXmlElement num("Num");
				num.SetAttribute("value", "20");
				fragment.InsertEndChild(material);
				fragment.InsertEndChild(shape);
				fragment.InsertEndChild(velocity);
				fragment.InsertEndChild(angle);
				fragment.InsertEndChild(quality);
				fragment.InsertEndChild(num);
			}
			TiXmlElement shockWave("ShockWave");
			shockWave.SetAttribute("PartDamageCriterionType", "YES");
			{
				TiXmlElement selectValue("SelectValue");
				selectValue.SetAttribute("value", "1");
				TiXmlElement overPressure("OverPressure");
				overPressure.SetAttribute("value", "0.05");
				TiXmlElement specificImpulse("SpecificImpulse");
				specificImpulse.SetAttribute("value", "15");
				TiXmlElement shockWave_OPSI("ShockWave_OPSI");
				shockWave_OPSI.SetAttribute("OverPressure", "10");
				shockWave_OPSI.SetAttribute("SpecificImpulse", "15");
				shockWave_OPSI.SetAttribute("threshold", "10");
				shockWave.InsertEndChild(selectValue);
				shockWave.InsertEndChild(overPressure);
				shockWave.InsertEndChild(specificImpulse);
				shockWave.InsertEndChild(shockWave_OPSI);
			}
			element.InsertEndChild(center);
			element.InsertEndChild(size);
			element.InsertEndChild(fragment);
			element.InsertEndChild(shockWave);
			parent->InsertEndChild(element);
		}
		else
		{
			std::string elementName;
			std::string attributeName;
			if(node.grade == 3)
			{
				elementName = "SFS";
				attributeName = "SubFunctionSystemModuleName";
			}
			else
			{
				elementName = "FS";
				attributeName = "FunctionSystemModuleName";
			}
			TiXmlElement fsElement(elementName);
			fsElement.SetAttribute(attributeName, node.name);
			std::string guid = QUuid::createUuid().toString().toLocal8Bit().data();
			fsElement.SetAttribute("GUID", guid);
			TiXmlElement logicGate("FS");
			logicGate.SetAttribute("FunctionSystemModuleName", node.logic==1?"与":"或");
			guid = QUuid::createUuid().toString().toLocal8Bit().data();
			logicGate.SetAttribute("GUID", guid);
			for(int i=0; i<node.childNum; ++i)
			{
				std::stack<KillTreeNode>& st = vec[node.grade];
				KillTreeNode cnode = st.top();
				st.pop();
				CreateXmlElement(cnode, vec, &logicGate);
			}
			fsElement.InsertEndChild(logicGate);
			parent->InsertEndChild(fsElement);
		}
	}
	std::string TargetInfo::GetXmlDamageTree(/*const std::string& fileName*/)
	{
		bool bResult = false;
		std::string damageTreeText;
		if(/*OpenTarget(fileName) &&*/ !_killTreeText.isEmpty())
		{
			const int LINE_SIZE = 1024;
			char line[LINE_SIZE];
			int grade = 0;
			int childNum = 0;
			int logicGate = 0;
			double weight = 0;
			std::string name, code;
			std::string guid;
			std::vector<std::stack<KillTreeNode> > vec;
			std::map<std::string, TiXmlElement> elementMap;

			std::istringstream istr;
			istr.str(_killTreeText.toLocal8Bit().data());
			std::string header;
			istr >> header;
			while(!istr.eof())
			{
				//获取等级、代码、名称、子个数、逻辑门、权重
				istr >> grade >> code >> name >> childNum >> logicGate >> weight;
				if(!istr.good())
				{
					break;
				}
				KillTreeNode node;
				node.name = name;
				node.code = code;
				node.childNum = childNum;
				node.grade = grade;
				node.logic = logicGate;
				node.weight = weight;
				if(vec.size() < grade)
				{
					std::stack<KillTreeNode> st;
					st.push(node);
					vec.push_back(st);
				}
				else
				{
					std::stack<KillTreeNode>& st = vec[grade-1];
					st.push(node);
				}
			}
			TiXmlElement parent("V");
			KillTreeNode node = vec[0].top();
			vec[0].pop();
			CreateXmlElement(node, vec, &parent);
			std::stringstream stream;
			stream << *(parent.FirstChildElement("FS"));
			damageTreeText = stream.str();
		}
		return damageTreeText;
	}
}