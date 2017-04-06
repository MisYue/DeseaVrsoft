#pragma once

#include "structHead.h"
#include <osg/Node>
#include <osg/Shader>

osg::Node* readNodeFromBuffer(char* buffer, size_t length, const char* extension) ;

bool writeNodeToBuffer(osg::Node &pNode, std::ostream& fout, const char* extension);

osg::Node* findNameNode(const std::string& searchName, osg::Node* currNode);

std::string ws2s(const std::wstring& ws);

std::wstring s2ws(const std::string& s);

osg::Program *loadShader(std::string vertShaderSource, std::string fragShaderSource, std::string name = "");

//����
QString Encryption(QString str);

//����
QString Decryption(QString str);

QByteArray formHead(QByteArray by);

QByteArray ToByteArray(QVariantList valueList);
QVariantList FromByteArray(QByteArray &buff);

//ʮ����ת��Ϊ������
QString ConversionTen2Two(int nNum);

//������ת��Ϊʮ����
int ConversionTwo2Ten(QString str);

osg::MatrixTransform *MakeGrid(std::string strAixs, int num, double delta = 1.0);

osg::ref_ptr<osg::Geode> DrawTaget(
								   osg::Matrix matrix, QuadModel *quadModel, 
								   bool bDepthTest, bool bBlend, double lw, 
								   osg::Vec4 fillColor, osg::Vec4 lineColor,
								   QStringList damageParts, osg::Vec4 damageColor);
osg::ref_ptr<osg::Geode> DrawTaget(osg::Matrix matrix, QuadModel *quadModel, 
								   bool bDepthTest, bool bBlend, double lw, 
								   osg::Vec4 fillColor, osg::Vec4 lineColor);