#include "StdAfx.h"
#include "tavillon_rhinoPlugIn.h"

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Point_set_3.h>
#include <CGAL/draw_point_set_3.h>

#include <fstream>
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::FT FT;
typedef Kernel::Point_3 Point;
typedef Kernel::Vector_3 Vector;
typedef CGAL::Point_set_3<Point> Point_set;

#pragma region tavillon_testcommand

class CCommandtavillon_test : public CRhinoCommand
{
public:
	CCommandtavillon_test() = default;

	~CCommandtavillon_test() = default;

	UUID CommandUUID() override
	{
		// {675B2686-1793-4EC4-8216-D92745BBA48D}
		static const GUID tavillon_point_cloud_processing_rhinoCommand_UUID =
		{ 0x675B2686, 0x1793, 0x4EC4, { 0x82, 0x16, 0xD9, 0x27, 0x45, 0xBB, 0xA4, 0x8D } };
		return tavillon_point_cloud_processing_rhinoCommand_UUID;
	}

	const wchar_t* EnglishCommandName() override { return L"tavillon_test"; }
	CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

static class CCommandtavillon_test thetavillon_rhinoCommand;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Convert Input to CGAL PointCloud
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel2;
//typedef Kernel2::Point_3 Point2;
//typedef Kernel2::Vector_3 Vector2;

void rhinocloud_to_cgalcloud(ON_PointCloud* rhinocloud) {
	Point_set point_set;
	point_set.resize(rhinocloud->m_P.Count());

	for (int i = 0; i < rhinocloud->m_P.Count(); i++) {
		auto& p = rhinocloud->m_P[i];

		point_set.insert(Point(p.x, p.y, p.z));

		//	if (rhinocloud->HasPointColors()) {
		//		//new_cloud.m_C.Append(cloudCopy->m_C[i]);
		//	}

		//	if (rhinocloud->HasPointNormals()) {
		//		//new_cloud.m_N.Append(cloudCopy->m_N[i]);
		//	}
	}
	//CGAL::draw(point_set);
	RhinoApp().Print(L"CGAL Pointset: Crop %zi ", point_set.size());
}

CRhinoCommand::result CCommandtavillon_test::RunCommand(const CRhinoCommandContext& context)
{
	///////////////////////////////////////////////////////////////////////////////////
	  // Get PointCloud/obj from Rhino
	  ///////////////////////////////////////////////////////////////////////////////////
	CRhinoGetObject go;
	go.SetCommandPrompt(L"Select point clouds");
	go.SetGeometryFilter(CRhinoGetObject::pointset_object);
	go.GetObjects(1, 0);

	if (go.CommandResult() == CRhinoCommand::success)
	{
		// Display line command options
		CRhinoGetOption gp;
		gp.SetCommandPrompt(L"Command options");
		gp.AcceptNothing();

		for (int i = 0; i < go.ObjectCount(); i++) {
			const CRhinoPointCloudObject* cloud_obj = CRhinoPointCloudObject::Cast(go.Object(i).Object());

			if (cloud_obj)
			{
				////////////////////////////////////////////////////////////////
				//Example Get PointCloud plane and duplicate it
				////////////////////////////////////////////////////////////////
				const ON_PointCloud* cloud = ON_PointCloud::Cast(cloud_obj->Geometry());

				ON_PointCloud* cloudCopy = cloud->Duplicate();
				rhinocloud_to_cgalcloud(cloudCopy);

				////////////////////////////////////////////////////////////////
				//Example Iterate PointCloud
				////////////////////////////////////////////////////////////////
				ON_PointCloud new_cloud;

				for (int i = 0; i < cloudCopy->m_P.Count(); i++) {
					auto& p = cloudCopy->m_P[i];

					new_cloud.m_P.Append(p);

					if (cloudCopy->HasPointColors())
						new_cloud.m_C.Append(cloudCopy->m_C[i]);

					if (cloudCopy->HasPointNormals())
						new_cloud.m_N.Append(cloudCopy->m_N[i]);
				}

				////////////////////////////////////////////////////////////////
				//Example Bake
				////////////////////////////////////////////////////////////////
				//CRhinoPointCloudObject* cloudNew_objOutside(new CRhinoPointCloudObject());
				//cloudNew_objOutside->SetPointCloud(outside);
				//context.m_doc.AddObject(cloudNew_objOutside);

				RhinoApp().Print(L"Cockroach: Crop %i ", cloudCopy->m_P.Count());
			}
		}
	}

	return CRhinoCommand::success;
}

#pragma endregion

//
// END tavillon_point_cloud_processing_rhino command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////