#include "osg_tool.h"
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/PolygonOffset>
#include <osg/BlendFunc>
#include <osg/LineWidth>
#include <osg/Point>
#include <osg/Array>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osg/TriangleIndexFunctor>
#include <osgUtil/MeshOptimizers>
#include <osgText/Text>
#include <osg/PositionAttitudeTransform>

#include <iostream>
#include <algorithm>

std::ostream& operator << (std::ostream& out, const osg::Vec3& v)
{
	out << v[0] << ',' << v[1] << ',' << v[2] << '\n';
	return out;
}

osg::Geode* MakeGrid(GridType grid_type, 
						int num,
						double delta, 
						const osg::Vec4& axis_color, 
						const osg::Vec4& grid_color
						)
{
	osg::Geode *geode = new osg::Geode();
	if(delta <= 0.0)
		return geode;
	osg::StateSet *set = new osg::StateSet();
	set->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
	set->setMode(GL_DEPTH_TEST,osg::StateAttribute::ON);
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

	if(grid_type != kXY && grid_type != kYZ && grid_type != kXZ)
		return geode;
	osg::Vec3 v_axis_1;
	osg::Vec3 v_axis_2;
	if(grid_type == kXY)
	{
		v_axis_1 = osg::Vec3(1, 0, 0);
		v_axis_2 = osg::Vec3(0, 1, 0);
	}
	else if(grid_type == kYZ)
	{
		v_axis_1 = osg::Vec3(0, 1, 0);
		v_axis_2 = osg::Vec3(0, 0, 1);
	}
	else
	{
		v_axis_1 = osg::Vec3(1, 0, 1);
		v_axis_1 = osg::Vec3(0, 0, 1);
	}
	//绘制轴
	osg::Vec3Array* vertices_axis = new osg::Vec3Array;
	vertices_axis->push_back(v_axis_1 * (-radius));
	vertices_axis->push_back(v_axis_1 * radius);
	vertices_axis->push_back(v_axis_2 * (-radius));
	vertices_axis->push_back(v_axis_2 * radius);
	osg::Geometry* geom_axis = new osg::Geometry;
	geom_axis->setVertexArray(vertices_axis);
	osg::Vec4Array* colors_axis = new osg::Vec4Array;
	colors_axis->push_back(axis_color);
	geom_axis->setColorArray(colors_axis);
	geom_axis->setColorBinding(osg::Geometry::BIND_OVERALL);
	geom_axis->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, vertices_axis->size()));
	//绘制栅格
	osg::Vec3Array* vertices_grid = new osg::Vec3Array;
	osg::Vec3Array* vertices_grid_bold = new osg::Vec3Array;
	for (int nI=1; nI<=numLines; nI++)
	{
		osg::Vec3Array* vertices = NULL;
		if(nI % 5 == 0)
			vertices = vertices_grid_bold;
		else
			vertices = vertices_grid;

		vertices->push_back(v_axis_1 * ( -radius) + v_axis_2 * nI * delta);
		vertices->push_back( v_axis_1 * radius + v_axis_2 * nI * delta);

		vertices->push_back( v_axis_1 * (-radius) + -v_axis_2 * nI * delta);
		vertices->push_back( v_axis_1 * radius + -v_axis_2 * nI * delta);

		vertices->push_back( v_axis_2 * (-radius) + v_axis_1 * nI * delta);
		vertices->push_back( v_axis_2 * radius + v_axis_1 * nI * delta);

		vertices->push_back( v_axis_2 * (-radius) + -v_axis_1 * nI * delta);
		vertices->push_back( v_axis_2 * radius + -v_axis_1 * nI * delta);
	}
	osg::Geometry* geom_grid = new osg::Geometry;
	osg::Geometry* geom_grid_bold = new osg::Geometry;

	geom_grid->setVertexArray(vertices_grid);
	geom_grid_bold->setVertexArray(vertices_grid_bold);

	osg::Vec4Array* colors_grid = new osg::Vec4Array;
	colors_grid->push_back(grid_color);

	geom_grid->setColorArray(colors_grid);
	geom_grid->setColorBinding(osg::Geometry::BIND_OVERALL);
	geom_grid->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, vertices_grid->size()));
	geom_grid_bold->setColorArray(colors_grid);
	geom_grid_bold->setColorBinding(osg::Geometry::BIND_OVERALL);
	geom_grid_bold->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, vertices_grid_bold->size()));

	osg::ref_ptr<osg::LineWidth> grid_bold_width = new osg::LineWidth(1);
	geom_grid_bold->getOrCreateStateSet()->setAttributeAndModes(grid_bold_width.get(), osg::StateAttribute::ON);

	geode->addDrawable(geom_axis);
	geode->addDrawable(geom_grid);
	geode->addDrawable(geom_grid_bold);

	return geode;
}

osg::Drawable* DrawPoint(const osg::Vec3& coord, const osg::Vec4& color, float size)
{
	osg::Geometry* geom = new osg::Geometry;
	osg::Vec3Array* vertexes = new osg::Vec3Array;
	vertexes->push_back(coord);
	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(color);
	geom->setVertexArray(vertexes);
	geom->setColorArray(colors);
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, vertexes->size()));
	osg::StateSet* set = geom->getOrCreateStateSet();
	set->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
	set->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);

	osg::Point* point = new osg::Point(size);
	//point->setMinSize(size);
	set->setAttributeAndModes(point, osg::StateAttribute::ON);
	return geom;
	//osg::ShapeDrawable* shape = new osg::ShapeDrawable(new osg::Sphere(coord, size));
	//shape->setColor(color);
	//return shape;
}

osg::Drawable* DrawLine(const osg::Vec3& first_vertex_coord, const osg::Vec3& second_vertex_coord, const osg::Vec4& color, float line_width)
{
	osg::Geometry* geom = new osg::Geometry;
	osg::Vec3Array* vertexes = new osg::Vec3Array;
	vertexes->push_back(first_vertex_coord);
	vertexes->push_back(second_vertex_coord);
	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(color);
	geom->setVertexArray(vertexes);
	geom->setColorArray(colors);
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, vertexes->size()));
	osg::StateSet* set = geom->getOrCreateStateSet();
	set->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
	set->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);
	//设置线宽
	osg::ref_ptr<osg::LineWidth> line_width_attribute = new osg::LineWidth(line_width);
	set->setAttributeAndModes(line_width_attribute.get(), osg::StateAttribute::ON);
	return geom;
}


typedef std::vector<unsigned int> IndexList;
// A helper class that gathers up all the attribute arrays of an
// osg::Geometry object that are BIND_PER_VERTEX and runs an
// ArrayVisitor on them.
struct GeometryArrayGatherer
{
	typedef std::vector<osg::Array*> ArrayList;

	GeometryArrayGatherer(osg::Geometry& geometry)
		: _useDrawElements(true)
	{
		add(geometry.getVertexArray());
		//add(geometry.getNormalArray());
		//add(geometry.getColorArray());
		//add(geometry.getSecondaryColorArray());
		//add(geometry.getFogCoordArray());
		//unsigned int i;
		//for(i=0;i<geometry.getNumTexCoordArrays();++i)
		//{
		//	add(geometry.getTexCoordArray(i));
		//}
		//for(i=0;i<geometry.getNumVertexAttribArrays();++i)
		//{
		//	add(geometry.getVertexAttribArray(i));
		//}
	}

	void add(osg::Array* array)
	{
		if (array)
		{
			_arrayList.push_back(array);
		}
	}

	void accept(osg::ArrayVisitor& av)
	{
		for(ArrayList::iterator itr=_arrayList.begin();
			itr!=_arrayList.end();
			++itr)
		{
			(*itr)->accept(av);
		}
	}

	ArrayList _arrayList;
	// True if geometry contains bindings that are compatible with
	// DrawElements.
	bool _useDrawElements;
};
// Compare vertices in a mesh using all their attributes. The vertices
// are identified by their index. Extracted from TriStripVisitor.cpp
struct VertexAttribComparitor : public GeometryArrayGatherer
{
	VertexAttribComparitor(osg::Geometry& geometry)
		: GeometryArrayGatherer(geometry)
	{
	}

	bool operator() (unsigned int lhs, unsigned int rhs) const
	{
		for(ArrayList::const_iterator itr=_arrayList.begin();
			itr!=_arrayList.end();
			++itr)
		{
			int compare = (*itr)->compare(lhs,rhs);
			if (compare==-1) return true;
			if (compare==1) return false;
		}
		return false;
	}

	int compare(unsigned int lhs, unsigned int rhs)
	{
		for(ArrayList::iterator itr=_arrayList.begin();
			itr!=_arrayList.end();
			++itr)
		{
			int compare = (*itr)->compare(lhs,rhs);
			if (compare==-1) return -1;
			if (compare==1) return 1;
		}
		return 0;
	}

protected:
	VertexAttribComparitor& operator = (const VertexAttribComparitor&) { return *this; }

};

// Construct an index list of triangles for DrawElements for any input
// primitives.
struct MyTriangleOperator
{

	IndexList _remapIndices;
	IndexList _in_indices;

	inline void operator()(unsigned int p1, unsigned int p2, unsigned int p3)
	{
		if (_remapIndices.empty())
		{
			_in_indices.push_back(p1);
			_in_indices.push_back(p2);
			_in_indices.push_back(p3);
		}
		else
		{
			_in_indices.push_back(_remapIndices[p1]);
			_in_indices.push_back(_remapIndices[p2]);
			_in_indices.push_back(_remapIndices[p3]);
		}
	}

};
typedef osg::TriangleIndexFunctor<MyTriangleOperator> MyTriangleIndexFunctor;
// Compact the vertex attribute arrays. Also stolen from TriStripVisitor
class RemapArray : public osg::ArrayVisitor
{
public:
	RemapArray(const IndexList& remapping):_remapping(remapping) {}

	const IndexList& _remapping;

	template<class T>
	inline void remap(T& array)
	{
		for(unsigned int i=0;i<_remapping.size();++i)
		{
			if (i!=_remapping[i])
			{
				array[i] = array[_remapping[i]];
			}
		}
		array.erase(array.begin()+_remapping.size(),array.end());
	}

	virtual void apply(osg::Array&) {}
	virtual void apply(osg::ByteArray& array) { remap(array); }
	virtual void apply(osg::ShortArray& array) { remap(array); }
	virtual void apply(osg::IntArray& array) { remap(array); }
	virtual void apply(osg::UByteArray& array) { remap(array); }
	virtual void apply(osg::UShortArray& array) { remap(array); }
	virtual void apply(osg::UIntArray& array) { remap(array); }
	virtual void apply(osg::FloatArray& array) { remap(array); }
	virtual void apply(osg::DoubleArray& array) { remap(array); }

	virtual void apply(osg::Vec2Array& array) { remap(array); }
	virtual void apply(osg::Vec3Array& array) { remap(array); }
	virtual void apply(osg::Vec4Array& array) { remap(array); }

	virtual void apply(osg::Vec4ubArray& array) { remap(array); }

	virtual void apply(osg::Vec2bArray& array) { remap(array); }
	virtual void apply(osg::Vec3bArray& array) { remap(array); }
	virtual void apply(osg::Vec4bArray& array) { remap(array); }

	virtual void apply(osg::Vec2sArray& array) { remap(array); }
	virtual void apply(osg::Vec3sArray& array) { remap(array); }
	virtual void apply(osg::Vec4sArray& array) { remap(array); }

	virtual void apply(osg::Vec2dArray& array) { remap(array); }
	virtual void apply(osg::Vec3dArray& array) { remap(array); }
	virtual void apply(osg::Vec4dArray& array) { remap(array); }

	virtual void apply(osg::MatrixfArray& array) { remap(array); }
protected:

	RemapArray& operator = (const RemapArray&) { return *this; }
};

void makeMesh(osg::Geometry* geom)
{
	using namespace osg;
	// no point optimizing if we don't have enough vertices.
	if (!geom->getVertexArray() || geom->getVertexArray()->getNumElements()<3) return;

	// check for the existence of surface primitives
	unsigned int numSurfacePrimitives = 0;
	unsigned int numNonIndexedPrimitives = 0;
	osg::Geometry::PrimitiveSetList& primitives = geom->getPrimitiveSetList();
	osg::Geometry::PrimitiveSetList::iterator itr;
	for(itr=primitives.begin();
		itr!=primitives.end();
		++itr)
	{
		switch((*itr)->getMode())
		{
		case(PrimitiveSet::TRIANGLES):
		case(PrimitiveSet::TRIANGLE_STRIP):
		case(PrimitiveSet::TRIANGLE_FAN):
		case(PrimitiveSet::QUADS):
		case(PrimitiveSet::QUAD_STRIP):
		case(PrimitiveSet::POLYGON):
			++numSurfacePrimitives;
			break;
		default:
			// For now, only deal with polygons
			return;
		}
		PrimitiveSet::Type type = (*itr)->getType();
		if (!(type == PrimitiveSet::DrawElementsUBytePrimitiveType
			|| type == PrimitiveSet::DrawElementsUShortPrimitiveType
			|| type == PrimitiveSet::DrawElementsUIntPrimitiveType))
			numNonIndexedPrimitives++;
	}

	// nothing to index
	if (!numSurfacePrimitives || !numNonIndexedPrimitives) return;

	// duplicate shared arrays as it isn't safe to rearrange vertices when arrays are shared.
	if (geom->containsSharedArrays()) geom->duplicateSharedArrays();

	// compute duplicate vertices
	typedef std::vector<unsigned int> IndexList;
	unsigned int numVertices = geom->getVertexArray()->getNumElements();
	IndexList indices(numVertices);
	unsigned int i,j;
	for(i=0;i<numVertices;++i)
	{
		indices[i] = i;
	}

	VertexAttribComparitor arrayComparitor(*geom);
	std::sort(indices.begin(),indices.end(),arrayComparitor);

	unsigned int lastUnique = 0;
	unsigned int numUnique = 1;
	for(i=1;i<numVertices;++i)
	{
		if (arrayComparitor.compare(indices[lastUnique],indices[i]) != 0)
		{
			lastUnique = i;
			++numUnique;
		}

	}
	IndexList remapDuplicatesToOrignals(numVertices);
	lastUnique = 0;
	for(i=1;i<numVertices;++i)
	{
		if (arrayComparitor.compare(indices[lastUnique],indices[i])!=0)
		{
			// found a new vertex entry, so previous run of duplicates needs
			// to be put together.
			unsigned int min_index = indices[lastUnique];
			for(j=lastUnique+1;j<i;++j)
			{
				min_index = osg::minimum(min_index,indices[j]);
			}
			for(j=lastUnique;j<i;++j)
			{
				remapDuplicatesToOrignals[indices[j]]=min_index;
			}
			lastUnique = i;
		}

	}
	unsigned int min_index = indices[lastUnique];
	for(j=lastUnique+1;j<i;++j)
	{
		min_index = osg::minimum(min_index,indices[j]);
	}
	for(j=lastUnique;j<i;++j)
	{
		remapDuplicatesToOrignals[indices[j]]=min_index;
	}


	// copy the arrays.
	IndexList finalMapping(numVertices);
	IndexList copyMapping;
	copyMapping.reserve(numUnique);
	unsigned int currentIndex=0;
	for(i=0;i<numVertices;++i)
	{
		if (remapDuplicatesToOrignals[i]==i)
		{
			finalMapping[i] = currentIndex;
			copyMapping.push_back(i);
			currentIndex++;
		}
	}

	for(i=0;i<numVertices;++i)
	{
		if (remapDuplicatesToOrignals[i]!=i)
		{
			finalMapping[i] = finalMapping[remapDuplicatesToOrignals[i]];
		}
	}


	MyTriangleIndexFunctor taf;
	taf._remapIndices.swap(finalMapping);

	Geometry::PrimitiveSetList new_primitives;
	new_primitives.reserve(primitives.size());

	for(itr=primitives.begin();
		itr!=primitives.end();
		++itr)
	{
		// For now we only have primitive sets that play nicely with
		// the TriangleIndexFunctor.
		(*itr)->accept(taf);
	}

	// remap any shared vertex attributes
	RemapArray ra(copyMapping);
	arrayComparitor.accept(ra);
	if (taf._in_indices.size() < 65536)
	{
		osg::DrawElementsUShort* elements = new DrawElementsUShort(GL_TRIANGLES);
		for (IndexList::iterator itr = taf._in_indices.begin(),
			end = taf._in_indices.end();
			itr != end;
		++itr)
		{
			elements->push_back((GLushort)(*itr));
		}
		new_primitives.push_back(elements);
	}
	else
	{
		osg::DrawElementsUInt* elements
			= new DrawElementsUInt(GL_TRIANGLES, taf._in_indices.begin(),
			taf._in_indices.end());
		new_primitives.push_back(elements);
	}
	geom->setPrimitiveSetList(new_primitives);
}

double intersectionAngle(const osg::Vec3& p0, const osg::Vec3& p1)
{
	double cos_angle = ( p0[0]*p1[0] + p0[1]*p1[1] + p0[2]*p1[2] ) /
		( sqrt( pow(p0[0] ,2) + pow(p0[1], 2) + pow(p0[2], 2) ) *
		sqrt( pow(p1[0], 2) + pow(p1[1], 2) + pow(p1[2], 2) ) );
	double angle = acos( cos_angle );
	return angle;
	//if ( angle>(osg::PI/2.0) )
	//{
	//	return (osg::PI - angle);
	//}
	//else
	//{
	//	return angle;
	//}
}

osg::Geode* CreateAxis()
{
	osg::Geode* geode  = new osg::Geode; 

	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();

	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array();
	vertices->push_back (osg::Vec3 ( 0.0, 0.0, 0.0));
	vertices->push_back (osg::Vec3 ( 50.0, 0.0, 0.0));
	vertices->push_back (osg::Vec3 ( 0.0, 0.0, 0.0));
	vertices->push_back (osg::Vec3 ( 0.0, 50.0, 0.0));
	vertices->push_back (osg::Vec3 ( 0.0, 0.0, 0.0));
	vertices->push_back (osg::Vec3 ( 0.0, 0.0, 50.0));
	geometry->setVertexArray (vertices.get());

	osg::ref_ptr<osg::Vec4Array> colors (new osg::Vec4Array());
	colors->push_back (osg::Vec4 (1.0f, 0.0f, 0.0f, 1.0f));
	colors->push_back (osg::Vec4 (1.0f, 0.0f, 0.0f, 1.0f));
	colors->push_back (osg::Vec4 (0.0f, 1.0f, 0.0f, 1.0f));
	colors->push_back (osg::Vec4 (0.0f, 1.0f, 0.0f, 1.0f));
	colors->push_back (osg::Vec4 (0.0f, 0.0f, 1.0f, 1.0f));
	colors->push_back (osg::Vec4 (0.0f, 0.0f, 1.0f, 1.0f));
	geometry->setColorArray (colors.get());

	geometry->setColorBinding (osg::Geometry::BIND_PER_VERTEX);    
	geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES,0,6));

	//设置线宽
	osg::ref_ptr<osg::LineWidth> lw = new osg::LineWidth(2.0);
	geometry->getOrCreateStateSet()->setAttribute(lw.get());

	geode->addDrawable( geometry.get() );
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, false);

	return geode;
}

osg::Geode* CreateLables(const osg::Vec3& pos, float size, const osg::Vec4& color, const std::string& label)
{
	osg::Geode* geode = new osg::Geode();
	geode->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
	geode->getOrCreateStateSet()->setMode( GL_DEPTH_TEST , osg::StateAttribute::OFF ) ;
	geode->getOrCreateStateSet()->setRenderBinDetails( 5000, "RenderBin" ) ;

	std::string timesFont("fonts/simhei.ttf");
		osgText::Text* text = new  osgText::Text;
	text->setDataVariance(osg::Object::DYNAMIC);
	geode->addDrawable( text );
	text->setFont(timesFont);
	text->setPosition(pos);
	text->setCharacterSize(size);
	text->setColor(color);
	text->setAutoRotateToScreen(true);
	text->setBackdropType(osgText::Text::OUTLINE);
	text->setBackdropColor(color);
	text->setAxisAlignment(osgText::Text::SCREEN);
	text->setAlignment(osgText::Text::CENTER_CENTER);
	text->setCharacterSizeMode(osgText::Text::SCREEN_COORDS);
	text->setText(label);
	return geode;
}

osg::PositionAttitudeTransform* CreatePosPAT(const osg::Vec3& pos)
{
	osg::PositionAttitudeTransform* pos_pat = new osg::PositionAttitudeTransform;
	pos_pat->setPosition( pos );
	pos_pat->addChild( CreateAxis() );
	pos_pat->addChild( CreateLables(osg::Vec3(51.0, 0.0, 1.0), 15.0, osg::Vec4 (1.0f, 0.0f, 0.0f, 1.0f), "X") );
	pos_pat->addChild( CreateLables(osg::Vec3(0.0, 51.0, 1.0), 15.0, osg::Vec4 (0.0f, 1.0f, 0.0f, 1.0f), "Y") );
	pos_pat->addChild( CreateLables(osg::Vec3(0.0, 0.0, 51.0), 15.0, osg::Vec4 (0.0f, 0.0f, 1.0f, 1.0f), "Z") );
	return pos_pat;
}