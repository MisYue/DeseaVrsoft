#include "UserTool.h"

#include <QStringList>

#include <osg/PolygonOffset>
#include <osg/MatrixTransform>
#include <osg/BlendFunc>
#include <osg/LineWidth>

osg::Node* readNodeFromBuffer(char* buffer, size_t length, const char* extension) 
{ 
	osgDB::ReaderWriter* rw = osgDB::Registry::instance()->getReaderWriterForExtension(extension); 

	if (rw) 
	{ 
		NodeBuf sb(buffer, length);

		std::istream stream(&sb);

		osgDB::ReaderWriter::ReadResult rr = rw->readNode(stream); 

		return rr.takeNode();
	}

	return NULL;
}

bool writeNodeToBuffer(osg::Node &pNode, std::ostream& fout, const char* extension) 
{ 
	osgDB::ReaderWriter* rw = osgDB::Registry::instance()->getReaderWriterForExtension(extension); 

	if (rw) 
	{ 
		osg::ref_ptr<osgDB::ReaderWriter::Options> options = new osgDB::ReaderWriter::Options;
		options->setOptionString("OutputTextureFiles");

		osgDB::ReaderWriter::WriteResult rr = rw->writeNode(pNode, fout, options);

		return rr.success();
	}

	return false;
}

osg::Node* findNameNode(const std::string& searchName, osg::Node* currNode)
{
	FindNamedNodeVisitor fnnv(searchName);
	currNode->accept(fnnv);

	if (!fnnv._foundNodes.empty())
	{
		osg::Node *node = fnnv._foundNodes.front().get();

		if (node)
		{
			return node;
		}
	}

	return NULL;
}

std::string ws2s(const std::wstring& ws)
{
	std::string curLocale = setlocale(LC_ALL, NULL);        // curLocale = "C";

	setlocale(LC_ALL, "chs");

	const wchar_t* _Source = ws.c_str();

	size_t _Dsize = 2 * ws.size() + 1;

	char *_Dest = new char[_Dsize];

	memset(_Dest,0,_Dsize);

	wcstombs(_Dest,_Source,_Dsize);

	std::string result = _Dest;

	delete []_Dest;

	setlocale(LC_ALL, curLocale.c_str());

	return result;
}

std::wstring s2ws(const std::string& s)
{
	setlocale(LC_ALL, "chs"); 

	const char* _Source = s.c_str();

	size_t _Dsize = s.size() + 1;

	wchar_t *_Dest = new wchar_t[_Dsize];

	wmemset(_Dest, 0, _Dsize);

	mbstowcs(_Dest,_Source,_Dsize);

	std::wstring result = _Dest;

	delete []_Dest;

	setlocale(LC_ALL, "C");

	return result;
}

osg::Program *loadShader(std::string vertShaderSource, 
						 std::string fragShaderSource, 
						 std::string name)
{
	bool success = true;

	osg::Shader *vertShader = new osg::Shader(osg::Shader::VERTEX);

	success = vertShader->loadShaderSourceFromFile(vertShaderSource);

	if ( !success  )
	{
		std::cout << "Couldn't load file: " << vertShaderSource << std::endl;

		return NULL;
	}

	osg::Shader *fragShader = new osg::Shader(osg::Shader::FRAGMENT);

	success = fragShader->loadShaderSourceFromFile(fragShaderSource);

	if ( !success  )
	{
		std::cout << "Couldn't load file: " << fragShaderSource << std::endl;

		return NULL;
	}

	osg::ref_ptr<osg::Program> program = new osg::Program;
	program->setName( name );

	program->addShader( vertShader );
	program->addShader( fragShader );

	return program.release();
}

QString Encryption(QString str)
{
	QString strTemp = "";

	QByteArray byteArray = str.toLocal8Bit();

	int nlen = byteArray.size();

	for (int nI=0; nI<nlen; nI++)
	{
		int nNum = int( byteArray.at(nI) );

		strTemp.append( QString::number(nNum) );

		if (nI < nlen-1)
		{
			strTemp.append( " " );
		}
	}

	return strTemp;
}

QString Decryption(QString str)
{
	QStringList strList = str.split(" ");

	QByteArray byteArray;

	int nlen = strList.size();

	for (int nI=0; nI<nlen; nI++)
	{
		QString strNum = strList.at(nI);

		char buff = char(strNum.toInt());

		byteArray.append(buff);
	}

	QString strTemp = QString::fromLocal8Bit(byteArray.data());

	return strTemp;
}

QByteArray formHead(QByteArray by)
{  
	int len=by.length();  

	for(int i=10-len; i>0; i--)
	{  
		by=by.prepend('0');  
	} 

	return by;  
}

QVariantList FromByteArray(QByteArray &buff)
{
	int nValueListSize = buff.left(10).toInt();
	buff.remove(0, 10);

	QVariantList valueList;

	int nCurrSize = 0;
	while (nCurrSize < nValueListSize)
	{
		QString strValueType = QString::fromLocal8Bit( buff.left(10).data() );
		buff.remove(0, 10);
		strValueType = strValueType.trimmed();

		int nValueSize = buff.left(10).toInt();
		buff.remove(0, 10);

		QByteArray byteValue = buff.left(nValueSize);
		buff.remove(0, nValueSize);

		if (strValueType == "String")
		{
			QString strValue = QString::fromLocal8Bit( byteValue.data() );

			valueList.push_back(QVariant(strValue));
		}
		else if (strValueType == "Int")
		{
			int nVal = byteValue.toInt();

			valueList.push_back(QVariant(nVal));
		}
		else if (strValueType == "Double")
		{
			double lfVal = byteValue.toDouble();

			valueList.push_back(QVariant(lfVal));
		}
		else
		{
			valueList.push_back(QVariant(byteValue));
		}

		nCurrSize += 20 + nValueSize;
	}

	return valueList;
}

QByteArray ToByteArray(QVariantList valueList)
{
	QByteArray currBuff;

	for (int nJ=0; nJ<valueList.size(); nJ++)
	{
		QVariant valueVar = valueList.at(nJ);

		if (valueVar.type() == QVariant::String)
		{
			QByteArray tempBuff = valueVar.toString().toLocal8Bit();

			QString dataType = "    String";

			QByteArray typeBuff = dataType.toLocal8Bit();

			QByteArray numBuff = formHead(QByteArray::number(tempBuff.size()));

			currBuff += typeBuff + numBuff + tempBuff;
		}
		else if (valueVar.type() == QVariant::Int)
		{
			QByteArray tempBuff = valueVar.toByteArray();

			QString dataType = "       Int";

			QByteArray typeBuff = dataType.toLocal8Bit();

			QByteArray numBuff = formHead(QByteArray::number(tempBuff.size()));

			currBuff += typeBuff + numBuff + tempBuff;
		}
		else if (valueVar.type() == QVariant::Double)
		{
			QByteArray tempBuff = valueVar.toByteArray();

			QString dataType = "    Double";

			QByteArray typeBuff = dataType.toLocal8Bit();

			QByteArray numBuff = formHead(QByteArray::number(tempBuff.size()));

			currBuff += typeBuff + numBuff + tempBuff;
		}
		else
		{
			QByteArray tempBuff = valueVar.toByteArray();

			QString dataType = " ByteArray";

			QByteArray typeBuff = formHead(dataType.toLocal8Bit());

			QByteArray numBuff = formHead(QByteArray::number(tempBuff.size()));

			currBuff += typeBuff + numBuff + tempBuff;
		}
	}

	currBuff.prepend( formHead(QByteArray::number(currBuff.size())) );

	return currBuff;
}

//十进制转换为二进制
QString ConversionTen2Two(int nNum)
{
	int aa[20];
	int temp;

	temp = nNum;
	int num;
	int i=0;

	while(temp !=0)
	{
		num = temp%2;
		aa[i] = num;
		i++;
		temp = temp/2;
	}

	QString str = "";

	for(int nI=i-1; nI>=0; nI--)
	{
		str += QString::number(aa[nI]);
	}

	return str;
}

//二进制转换为十进制
int ConversionTwo2Ten(QString str)
{
	char buff[64];    // 输入缓存
	int n=0;        // 二进制位数
	int w=1;        // 当前位权重

	int number=0;    // 十进制值

	// 输入
	memcpy(buff, str.toLocal8Bit().data(), strlen(str.toLocal8Bit().data()));

	// 获取长度，去除非法数
	char* p=buff;
	while(*p>='0' && *p++<='1') n++; // 只能是1或0----这里注意：后缀++的优先级高于解引用*的优先级

	// 转换2进制到10进制
	while(n--)
	{
		number += (buff[n]-'0')*w;
		w*=2;
	}

	// 输出
	return number;
}

osg::MatrixTransform *MakeGrid(std::string strAixs, int num, double delta)
{
	osg::MatrixTransform *transform = new osg::MatrixTransform();
	osg::Geode *geode = new osg::Geode();
	osg::Geometry *geom = new osg::Geometry();
	osg::Vec3Array *vertices = new osg::Vec3Array();
	osg::StateSet *set = new osg::StateSet();
	set->setMode(GL_LIGHTING,osg::StateAttribute::ON);
	set->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);
	set->setMode(GL_LINE_SMOOTH,osg::StateAttribute::ON );
	set->setMode(GL_BLEND, osg::StateAttribute::ON);
	osg::ref_ptr<osg::BlendFunc> bfn = new osg::BlendFunc;
	bfn->setFunction(osg::BlendFunc::SRC_ALPHA, osg::BlendFunc::ONE_MINUS_SRC_ALPHA);
	set->setAttributeAndModes(bfn, osg::StateAttribute::ON);
	//设置线宽
	osg::ref_ptr<osg::LineWidth> linewidth = new osg::LineWidth(0.0005);
	set->setAttributeAndModes(linewidth.get(), osg::StateAttribute::ON);

	geode->setStateSet(set);

	int numLines = num;
	float radius = delta * numLines;

	if (strAixs.compare("X-Y") == 0)
	{
		vertices->push_back( osg::Vec3(0.0f, -radius, 0.0f) );
		vertices->push_back( osg::Vec3(0.0f, radius, 0.0f) );
		vertices->push_back( osg::Vec3(-radius, 0.0f, 0.0f) );
		vertices->push_back( osg::Vec3( radius, 0.0f, 0.0f) );

		for (int nI=1; nI<=numLines; nI++)
		{
			vertices->push_back( osg::Vec3(delta * nI, -radius, 0.0f) );
			vertices->push_back( osg::Vec3(delta * nI, radius, 0.0f) );

			vertices->push_back( osg::Vec3(delta * -nI, -radius, 0.0f) );
			vertices->push_back( osg::Vec3(delta * -nI, radius, 0.0f) );

			vertices->push_back( osg::Vec3(-radius, delta * nI, 0.0f) );
			vertices->push_back( osg::Vec3(radius, delta * nI, 0.0f) );

			vertices->push_back( osg::Vec3(-radius, delta * -nI, 0.0f) );
			vertices->push_back( osg::Vec3(radius, delta * -nI, 0.0f) );
		}
	}
	else if (strAixs.compare("X-Z") == 0)
	{
		vertices->push_back( osg::Vec3(0.0f, 0.0f, -radius) );
		vertices->push_back( osg::Vec3(0.0f, 0.0f, radius) );
		vertices->push_back( osg::Vec3(-radius, 0.0f, 0.0f) );
		vertices->push_back( osg::Vec3( radius, 0.0f, 0.0f) );

		for (int nI=1; nI<=numLines; nI++)
		{
			vertices->push_back( osg::Vec3(delta * nI, 0.0f, -radius) );
			vertices->push_back( osg::Vec3(delta * nI, 0.0f, radius) );

			vertices->push_back( osg::Vec3(delta * -nI, 0.0f, -radius) );
			vertices->push_back( osg::Vec3(delta * -nI, 0.0f, radius) );

			vertices->push_back( osg::Vec3(-radius, 0.0f, delta * nI) );
			vertices->push_back( osg::Vec3(radius, 0.0f, delta * nI) );

			vertices->push_back( osg::Vec3(-radius, 0.0f, delta * -nI) );
			vertices->push_back( osg::Vec3(radius, 0.0f, delta * -nI) );
		}
	}
	else if (strAixs.compare("Y-Z") == 0)
	{
		vertices->push_back( osg::Vec3(0.0f, -radius, 0.0f) );
		vertices->push_back( osg::Vec3(0.0f, radius, 0.0f) );
		vertices->push_back( osg::Vec3(0.0f, 0.0f, -radius) );
		vertices->push_back( osg::Vec3(0.0f, 0.0f, radius) );

		for (int nI=1; nI<=numLines; nI++)
		{
			vertices->push_back( osg::Vec3(0.0f, -radius, delta * nI) );
			vertices->push_back( osg::Vec3(0.0f, radius, delta * nI) );

			vertices->push_back( osg::Vec3(0.0f, -radius, delta * -nI) );
			vertices->push_back( osg::Vec3(0.0f, radius, delta * -nI) );

			vertices->push_back( osg::Vec3(0.0f, delta * nI, -radius) );
			vertices->push_back( osg::Vec3(0.0f, delta * nI, radius) );

			vertices->push_back( osg::Vec3(0.0f, delta * -nI, -radius) );
			vertices->push_back( osg::Vec3(0.0f, delta * -nI, radius) );
		}
	}

	geom->setVertexArray(vertices);
	osg::Vec4Array* colors = new osg::Vec4Array();
	colors->push_back( osg::Vec4(0.0f, 0.0f, 0.0f,0.5f) );
	colors->push_back( osg::Vec4(0.83f, 0.83f, 0.83f, 0.5f) );
	geom->setColorArray(colors);
	geom->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
	geom->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES,0,4) );
	geom->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES,4,vertices->size() - 4) );
	geode->addDrawable(geom);
	transform->addChild(geode);
	transform->setName("transformGrid");

	return transform;
}

osg::ref_ptr<osg::Geode> DrawTaget(osg::Matrix matrix, QuadModel *quadModel, 
											bool bDepthTest, bool bBlend, double lw, 
											osg::Vec4 fillColor, osg::Vec4 lineColor,
											QStringList damageParts, osg::Vec4 damageColor)
{
	osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;

	pGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	pGeode->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL,osg::StateAttribute::ON);

	if (bDepthTest)
	{
		pGeode->getOrCreateStateSet()->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );
	}
	else
	{
		pGeode->getOrCreateStateSet()->setMode( GL_DEPTH_TEST, osg::StateAttribute::OFF );
	}

	if (bBlend)
	{
		pGeode->getOrCreateStateSet()->setMode( GL_BLEND, osg::StateAttribute::ON );
	}
	else
	{
		pGeode->getOrCreateStateSet()->setMode( GL_BLEND, osg::StateAttribute::OFF );
	}

	pGeode->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

	//设置线宽
	osg::ref_ptr<osg::LineWidth> linewidth = new osg::LineWidth(lw);
	pGeode->getOrCreateStateSet()->setAttribute(linewidth.get());

	osg::ref_ptr<osg::Geometry> gm = new osg::Geometry;
	pGeode->addDrawable( gm.get() );

	osg::ref_ptr<osg::Vec3Array> vertex = new osg::Vec3Array;
	osg::ref_ptr<osg::Vec3Array> normal = new osg::Vec3Array;
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;

	QList<Component *>::iterator ite = quadModel->componentList.begin();
	while (ite != quadModel->componentList.end())
	{
		Component *pComponent = *ite;

		int nSize = pComponent->pointSumList.size();

		for (int nI=0; nI<nSize; nI++)
		{
			int nStartIndex = vertex->size();

			PointIndexSum *pPointIndexSum = pComponent->pointSumList.at(nI);

			for (int nJ=0; nJ<pPointIndexSum->pointIndexList.size(); nJ++)
			{
				int nIndexGeom = pPointIndexSum->pointIndexList.at(nJ);

				PointValue point = quadModel->pointSum.pointList.at(nIndexGeom-1);

				osg::Vec3 pos = osg::Vec3(point.x, point.y, point.z);

				osg::Vec4 temp = osg::Vec4(pos, 1.0);
				temp = matrix * temp;
				pos.x() = temp.x();
				pos.y() = temp.y();
				pos.z() = temp.z();

				vertex->push_back( pos );
			}

			osg::Vec3f v1 = vertex->at(1) -  vertex->at(0);
			osg::Vec3f v2 = vertex->at(2) -  vertex->at(1);

			osg::Vec3f nor = v1 ^ v2;

			nor.normalize();

			//压入法线
			normal->push_back( nor );

			if (damageParts.contains(pComponent->strName))
			{
				colors->push_back( damageColor );
			}
			else
			{
				colors->push_back( fillColor );
			}

			int nNum = vertex->size() - nStartIndex;

			osg::DrawArrays *pDrawArraysShape = new osg::DrawArrays(osg::PrimitiveSet::POLYGON, nStartIndex, nNum);

			QString strName = pComponent->strName + "/ShapeGeom-" + QString::number(nI);
			pDrawArraysShape->setName(strName.toLocal8Bit());

			gm->addPrimitiveSet( pDrawArraysShape );

			//---------------------------------------------------------------------------------------------
			colors->push_back( lineColor );

			osg::DrawArrays *pDrawArraysLine = new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP, nStartIndex, nNum);

			QString strTemp = pComponent->strName + "/LineGeom-" + QString::number(nI);
			pDrawArraysLine->setName(strTemp.toLocal8Bit());

			gm->addPrimitiveSet( pDrawArraysLine );
		}

		++ite;
	}

	gm->setVertexArray( vertex.get() );

	gm->setUseVertexBufferObjects(true);

	gm->setNormalArray( normal.get() );
	gm->setNormalBinding( osg::Geometry:: BIND_OVERALL );

	gm->setColorArray(colors);
	gm->setColorBinding( osg::Geometry::BIND_PER_PRIMITIVE_SET );

	return pGeode;
}
osg::ref_ptr<osg::Geode> DrawTaget(osg::Matrix matrix, QuadModel *quadModel, 
								   bool bDepthTest, bool bBlend, double lw, 
								   osg::Vec4 fillColor, osg::Vec4 lineColor)
{
	osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;

	pGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	pGeode->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL,osg::StateAttribute::ON);

	if (bDepthTest)
	{
		pGeode->getOrCreateStateSet()->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );
	}
	else
	{
		pGeode->getOrCreateStateSet()->setMode( GL_DEPTH_TEST, osg::StateAttribute::OFF );
	}

	if (bBlend)
	{
		pGeode->getOrCreateStateSet()->setMode( GL_BLEND, osg::StateAttribute::ON );
	}
	else
	{
		pGeode->getOrCreateStateSet()->setMode( GL_BLEND, osg::StateAttribute::OFF );
	}

	pGeode->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

	//设置线宽
	osg::ref_ptr<osg::LineWidth> linewidth = new osg::LineWidth(lw);
	pGeode->getOrCreateStateSet()->setAttribute(linewidth.get());

	osg::ref_ptr<osg::Geometry> gm = new osg::Geometry;
	pGeode->addDrawable( gm.get() );

	osg::ref_ptr<osg::Vec3Array> vertex = new osg::Vec3Array;
	osg::ref_ptr<osg::Vec3Array> normal = new osg::Vec3Array;
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;

	QList<Component *>::iterator ite = quadModel->componentList.begin();
	while (ite != quadModel->componentList.end())
	{
		Component *pComponent = *ite;

		int nSize = pComponent->pointSumList.size();

		for (int nI=0; nI<nSize; nI++)
		{
			int nStartIndex = vertex->size();

			PointIndexSum *pPointIndexSum = pComponent->pointSumList.at(nI);

			for (int nJ=0; nJ<pPointIndexSum->pointIndexList.size(); nJ++)
			{
				int nIndexGeom = pPointIndexSum->pointIndexList.at(nJ);

				PointValue point = quadModel->pointSum.pointList.at(nIndexGeom-1);

				osg::Vec3 pos = osg::Vec3(point.x, point.y, point.z);
				vertex->push_back( pos );
			}

			osg::Vec3f v1 = vertex->at(1) -  vertex->at(0);
			osg::Vec3f v2 = vertex->at(2) -  vertex->at(1);

			osg::Vec3f nor = v1 ^ v2;

			nor.normalize();

			//压入法线
			normal->push_back( nor );
			colors->push_back( fillColor );

			int nNum = vertex->size() - nStartIndex;

			osg::DrawArrays *pDrawArraysShape = new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, nStartIndex, nNum);

			QString strName = pComponent->strName + "/ShapeGeom-" + QString::number(nI);
			pDrawArraysShape->setName(strName.toLocal8Bit());

			gm->addPrimitiveSet( pDrawArraysShape );

			//---------------------------------------------------------------------------------------------
			colors->push_back( lineColor );

			osg::DrawArrays *pDrawArraysLine = new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP, nStartIndex, nNum);

			QString strTemp = pComponent->strName + "/LineGeom-" + QString::number(nI);
			pDrawArraysLine->setName(strTemp.toLocal8Bit());

			gm->addPrimitiveSet( pDrawArraysLine );
		}

		++ite;
	}

	gm->setVertexArray( vertex.get() );

	gm->setUseVertexBufferObjects(true);

	gm->setNormalArray( normal.get() );
	gm->setNormalBinding( osg::Geometry:: BIND_OVERALL );

	gm->setColorArray(colors);
	gm->setColorBinding( osg::Geometry::BIND_PER_PRIMITIVE_SET );

	return pGeode;
}