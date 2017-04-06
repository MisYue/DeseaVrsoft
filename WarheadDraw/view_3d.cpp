#include "view_3d.h"
#include "ViewerWidget.h"
#include "compass_hud.h"
#include "osg_tool.h"
#include <WarheadModelData/warhead_layer.h>
#include <WarheadModelData/warhead_section.h>
#include <WarheadModelData/warhead_fragment_layer.h>
#include <WarheadModelData/warhead_model.h>
#include <osgViewer/Viewer>
#include <osg/Group>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Shape>
#include <osg/Quat>
#include <osg/Geometry>

#include <osgGA/TrackballManipulator>
#include <osg/PolygonOffset>
#include <osg/BlendFunc>
#include <osg/LineWidth>
#include <osg/Point>
#include <osg/Array>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osg/TriangleIndexFunctor>
#include <osg/PositionAttitudeTransform>
#include <osgUtil/SmoothingVisitor>
#include <osgUtil/Optimizer>
#include <iostream>
#include <osg/PositionAttitudeTransform>
#include <osg/Material>
#include <osgDB/WriteFile>

osg::Vec4 g_color(0.85, 0.85, 0.85, 1.0);
osg::Vec4 g_end_cap_color(0.6, 0.6, 0.6, 1.0);
osg::Vec4 g_fire_point_color(1, 0, 0, 1);
osg::Vec4 g_charge_color(1, 1, 0, 1);
osg::Vec4 g_frag_color(g_color);

osg::Geode* DrawCylinder(double length, double r, const osg::Vec3& center)
{
	osg::Geode* geode = new osg::Geode;
	osg::Cylinder* shape = new osg::Cylinder(center, r, length);
	shape->setRotation(osg::Quat(M_PI_2, osg::Vec3(0, 1, 0)));
	osg::ShapeDrawable* shape_drawable = new osg::ShapeDrawable(shape);
	geode->addDrawable(shape_drawable);
	shape_drawable->setColor(g_color);
	return geode;
}

osg::Geode* DrawCurveObject(const ShapeDescribe* shape, double left_h, double right_h)
{
	Q_ASSERT(shape);
	CurveEquation curve(shape);
	QVector<Bit_Point2D> points;
	//? 离散量需计算
	unsigned descrete_num = shape->get_shape_length()/20;
	if(descrete_num < 20)
		descrete_num = 20;
	curve.DescreteCurve(points, descrete_num);
	osg::Vec3Array* vertexes = new osg::Vec3Array;

	//? 每圈点个数为360
	unsigned per_circle_num = 60;
	double rotate_rad = (360 / per_circle_num) / (180/M_PI); 
	
	//点总个数
	unsigned whole_num = per_circle_num * descrete_num;
	vertexes->reserve(whole_num);

	osg::Matrix mat(osg::Quat(rotate_rad, osg::Vec3(1, 0, 0)));

	double dh = (right_h-left_h) / descrete_num;
	double h = left_h;
	for(unsigned i=0; i<descrete_num; ++i)
	{
		vertexes->push_back(osg::Vec3(points[i].Get_x(), points[i].Get_y()+h, 0));
		h+=dh;
	}

	for(int j=0, k=per_circle_num-1; j<k; ++j)
	{
		for(unsigned i=0; i<descrete_num; ++i)
		{
			vertexes->push_back(vertexes->at(j*descrete_num+i) * mat);
		}
	}

	osg::Geometry* geom = new osg::Geometry;
	osg::Geode* geode = new osg::Geode;
	geode->addDrawable(geom);

	geom->setVertexArray(vertexes);

	osg::Vec3Array* normals = new osg::Vec3Array;
	normals->reserve(per_circle_num * (descrete_num-1));

	for(int j=0; j<per_circle_num-1; ++j)
	{
		for(unsigned i=0, k=descrete_num-1; i<k; ++i)
		{
			osg::DrawElementsUInt* quad = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
			quad->reserveElements(4);
			unsigned m = j*descrete_num+i;
			unsigned n = (j+1)*descrete_num+i;
			
			quad->push_back(n);
			quad->push_back(n+1);
			quad->push_back(m+1);
			quad->push_back(m);
			geom->addPrimitiveSet(quad);
		}
	}
	for(unsigned i=0; i<descrete_num-1; ++i)
	{
		osg::DrawElementsUInt* quad = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
		unsigned m = (per_circle_num-1)*descrete_num+i;
		unsigned n = descrete_num+i;

		quad->push_back(n);
		quad->push_back(n+1);
		quad->push_back(m+1);
		quad->push_back(m);
		geom->addPrimitiveSet(quad);
	}
	osgUtil::SmoothingVisitor::smooth(*geom);
	return geode;
}

osg::Group* DrawSphereFragments(const SphereFragmentLayer* layer)
{
	Q_ASSERT(layer);
	osg::Group* group = new osg::Group;
	const Fragments& frags = layer->get_fragments(true);
	double radius = layer->get_r();
	foreach(const LayerFrags& layer_frags, frags)
	{
		foreach(const CircleFrags& circle_frags, layer_frags)
		{
			const CoordinatesPosition& coord_pos = circle_frags.first();
			osg::Vec3 center(coord_pos.Get_x(), coord_pos.Get_y(), coord_pos.Get_z());
			osg::Sphere* spere = new osg::Sphere(center, radius);
			osg::TessellationHints* hints = new osg::TessellationHints;
			hints->setDetailRatio(0.5);
			osg::ShapeDrawable* shape_drawable = new osg::ShapeDrawable(spere, hints);
			osg::Geode* geode = new osg::Geode;
			geode->addDrawable(shape_drawable);
			int n = circle_frags.size();
			//破片球心间隔
			double s_rad = 2*M_PI/n;
			for(int i=0; i<n; ++i)
			{
				osg::PositionAttitudeTransform* pat = new osg::PositionAttitudeTransform;
				pat->setAttitude(osg::Quat(i*s_rad, osg::Vec3(1, 0, 0)));
				pat->addChild(geode);
				group->addChild(pat);
			}
		}
	}
	return group;
}

osg::Geode* DrawFirePoint(const Bit_Point2D& pos, float radius)
{
	osg::Geode* geode = new osg::Geode;
	osg::Vec3 center(pos.Get_x(), pos.Get_y(), 0);
	osg::ShapeDrawable* shape = new osg::ShapeDrawable(new osg::Sphere(center, radius));
	//shape->setColor(g_fire_point_color);
	geode->addDrawable(shape);
	return geode;
}

void SetMaterialColor(osg::Node* node, const osg::Vec4& color)
{
	osg::Material* material = new osg::Material;
	material->setAmbient(osg::Material::FRONT_AND_BACK, color);
	material->setDiffuse(osg::Material::FRONT_AND_BACK, color);
	//material->setSpecular(osg::Material::FRONT_AND_BACK, color);
	//material->setShininess(osg::Material::FRONT_AND_BACK, 64);
	material->setTransparency(osg::Material::FRONT_AND_BACK, 0.2);
	node->getOrCreateStateSet()->setAttribute(material);
}
View3D::View3D(QWidget* parent ) : QMainWindow(parent)
{
	viewer_widget_ = new ViewerWidget((osg::Node*)0);
	viewer_ = dynamic_cast<osgViewer::Viewer*>(viewer_widget_->getViewer());
	scene_root_ = new osg::Group;
	viewer_->setSceneData(scene_root_);
	model_group_ = new osg::Group;
	scene_root_->addChild(model_group_);

	grid_ = MakeGrid(kXY, 20, 20, osg::Vec4(0, 0, 0, 1), osg::Vec4(0.7, 0.7, 0.7, 1));
	scene_root_->addChild(grid_);
	osgGA::TrackballManipulator* manipulator = dynamic_cast<osgGA::TrackballManipulator*>(viewer_->getCameraManipulator());
	osg::Quat rotation(
		osg::DegreesToRadians(90.0f), osg::Vec3f(1.0f, 0.0f, 0.0f),
		osg::DegreesToRadians(90.0f), osg::Vec3f(0.0f, 0.0f, 1.0f),
		osg::DegreesToRadians(-30.0f), osg::Vec3f(0.0f, 1.0f, 0.0f)
		);
	manipulator->setRotation(rotation);
	manipulator->setDistance(350);
	CompassHud* compass_hud = new CompassHud(viewer_);
	scene_root_->addChild(compass_hud->CreateAxisHud(0, 0, 1000, 800));
	
	setCentralWidget(viewer_widget_);

	//开启透明
	osg::StateSet* stateSet = model_group_->getOrCreateStateSet();
	stateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
	osg::ref_ptr<osg::BlendFunc> bfn = new osg::BlendFunc;
	bfn->setFunction(osg::BlendFunc::SRC_ALPHA, osg::BlendFunc::ONE_MINUS_SRC_ALPHA);
	stateSet->setAttributeAndModes(bfn, osg::StateAttribute::ON);
	//stateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	stateSet->setMode(GL_LIGHTING, osg::StateAttribute::ON);
	stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
}

View3D::~View3D()
{

}

void View3D::showEvent(QShowEvent * event)
{
	DrawModel();
}
bool View3D::Write(const QString& file_name)
{
	if(!isVisible())
		DrawOuterShell();
	return osgDB::writeNodeFile(*model_outer_shell_, file_name.toStdString());
}
void View3D::DrawOuterShell()
{
	Q_ASSERT(model_);
	model_outer_shell_ = new osg::Group;
	model_group_->addChild(model_outer_shell_);
	WarheadEndCap* left_end_cap = model_->get_left_end_cap();
	if(left_end_cap)
	{
		double r = left_end_cap->get_r();
		double length = left_end_cap->get_length();
		Bit_Point2D datum_point = left_end_cap->get_shape_describe()->get_datum_point();
		osg::Vec3 center(datum_point.Get_x(), datum_point.Get_y(), 0);
		center[0] += length/2;
		osg::Geode* geode = DrawCylinder(length, r, center);
		model_outer_shell_->addChild(geode);
		SetMaterialColor(geode, g_end_cap_color);
	}
	WarheadEndCap* right_end_cap = model_->get_right_end_cap();
	if(right_end_cap)
	{
		double r = right_end_cap->get_r();
		double length = right_end_cap->get_length();
		Bit_Point2D datum_point = right_end_cap->get_shape_describe()->get_datum_point();
		osg::Vec3 center(datum_point.Get_x(), datum_point.Get_y(), 0);
		center[0] += length/2;
		osg::Geode* geode = DrawCylinder(length, r, center);
		model_outer_shell_->addChild(geode);
		SetMaterialColor(geode, g_end_cap_color);
	}
	foreach(WarheadSection* section, model_->get_sections())
	{
		WarheadLayer* layer = section->get_layers().back();
		{
			if(SphereFragmentLayer* sphere_layer = dynamic_cast<SphereFragmentLayer*>(layer))
			{
				osg::Group* group = DrawSphereFragments(sphere_layer);
				SetMaterialColor(group, g_frag_color);
				model_outer_shell_->addChild(group);
			}
			else 
			{
				double left_h = 0;
				double right_h = 0;
				osg::Vec4 color = g_charge_color;
				if(layer->get_layer_type() != kCharge)
				{
					section->GetAwayHeight(layer, left_h, right_h);
					ShapeThickness thickness = layer->get_thickness();
					left_h = left_h - section->get_inner_left_half_height() + thickness.left;
					right_h = right_h - section->get_inner_right_half_height() + thickness.right;
					color = g_color;
				}
				osg::Geode* geode = DrawCurveObject(layer->get_shape_describe(), left_h, right_h);
				SetMaterialColor(geode, color);
				model_outer_shell_->addChild(geode);
			}
		}
	}
}

void View3D::DrawModel()
{
	if(!model_)
		return ;
	model_group_->removeChildren(0, model_group_->getNumChildren());

	DrawOuterShell();

	foreach(WarheadSection* section, model_->get_sections())
	{
		QList<WarheadLayer*> layers = section->get_layers();
		layers.removeLast();
		foreach(WarheadLayer* layer, layers)
		{
			if(SphereFragmentLayer* sphere_layer = dynamic_cast<SphereFragmentLayer*>(layer))
			{
				osg::Group* group = DrawSphereFragments(sphere_layer);
				SetMaterialColor(group, g_frag_color);
				model_group_->addChild(group);
			}
			else 
			{
				double left_h = 0;
				double right_h = 0;
				osg::Vec4 color = g_charge_color;
				if(layer->get_layer_type() != kCharge)
				{
					section->GetAwayHeight(layer, left_h, right_h);
					ShapeThickness thickness = layer->get_thickness();
					left_h = left_h - section->get_inner_left_half_height() + thickness.left;
					right_h = right_h - section->get_inner_right_half_height() + thickness.right;
					color = g_color;
				}
				osg::Geode* geode = DrawCurveObject(layer->get_shape_describe(), left_h, right_h);
				SetMaterialColor(geode, color);
				model_group_->addChild(geode);
			}
		}
	}
	double length_coef = model_->get_cs().Get_UnitSystem().Get_LengthCoefficient();
	float fire_point_radius = 10 / length_coef;
	foreach(WarheadFirePoint* fire_point, model_->get_fire_points())
	{
		osg::Geode* geode = DrawFirePoint(fire_point->get_pos(), fire_point_radius);
		model_group_->addChild(geode);
		SetMaterialColor(geode, g_fire_point_color);
	}
	UpdateGrid();
	osgGA::TrackballManipulator* manipulator = dynamic_cast<osgGA::TrackballManipulator*>(viewer_->getCameraManipulator());
	manipulator->setDistance(scene_root_->getBound().radius());
}
void View3D::UpdateGrid()
{
	double model_r = model_group_->getBound().radius();
	osg::Geode* grid = MakeGrid(kXY, 20, model_r*2 / 20, osg::Vec4(0, 0, 0, 1), osg::Vec4(0.7, 0.7, 0.7, 1));
	scene_root_->replaceChild(grid_, grid);
	grid_ = grid;
};