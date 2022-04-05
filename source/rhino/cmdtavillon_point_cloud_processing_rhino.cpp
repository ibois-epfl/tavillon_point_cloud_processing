// cmdtavillon_point_cloud_processing_rhino.cpp : command file
//

#include "StdAfx.h"
#include "tavillon_point_cloud_processing_rhinoPlugIn.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN tavillon_point_cloud_processing_rhino command
//

#pragma region tavillon_point_cloud_processing_rhino command

// Do NOT put the definition of class CCommandtavillon_point_cloud_processing_rhino in a header
// file. There is only ONE instance of a CCommandtavillon_point_cloud_processing_rhino class
// and that instance is the static thetavillon_point_cloud_processing_rhinoCommand that appears
// immediately below the class definition.

class CCommandtavillon_point_cloud_processing_rhino : public CRhinoCommand
{
public:
	// The one and only instance of CCommandtavillon_point_cloud_processing_rhino is created below.
	// No copy constructor or operator= is required.
	// Values of member variables persist for the duration of the application.

	// CCommandtavillon_point_cloud_processing_rhino::CCommandtavillon_point_cloud_processing_rhino()
	// is called exactly once when static thetavillon_point_cloud_processing_rhinoCommand is created.
	CCommandtavillon_point_cloud_processing_rhino() = default;

	// CCommandtavillon_point_cloud_processing_rhino::~CCommandtavillon_point_cloud_processing_rhino()
	// is called exactly once when static thetavillon_point_cloud_processing_rhinoCommand is destroyed.
	// The destructor should not make any calls to the Rhino SDK.
	// If your command has persistent settings, then override
	// CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
	~CCommandtavillon_point_cloud_processing_rhino() = default;

	// Returns a unique UUID for this command.
	// If you try to use an id that is already being used, then
	// your command will not work. Use GUIDGEN.EXE to make unique UUID.
	UUID CommandUUID() override
	{
		// {675B2686-1793-4EC4-8216-D92745BBA48D}
		static const GUID tavillon_point_cloud_processing_rhinoCommand_UUID =
		{ 0x675B2686, 0x1793, 0x4EC4, { 0x82, 0x16, 0xD9, 0x27, 0x45, 0xBB, 0xA4, 0x8D } };
		return tavillon_point_cloud_processing_rhinoCommand_UUID;
	}

	// Returns the English command name.
	// If you want to provide a localized command name, then override
	// CRhinoCommand::LocalCommandName.
	const wchar_t* EnglishCommandName() override { return L"tavillon_get_pointclouds"; }

	// Rhino calls RunCommand to run the command.
	CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandtavillon_point_cloud_processing_rhino object
// Do NOT create any other instance of a CCommandtavillon_point_cloud_processing_rhino class.
static class CCommandtavillon_point_cloud_processing_rhino thetavillon_point_cloud_processing_rhinoCommand;

CRhinoCommand::result CCommandtavillon_point_cloud_processing_rhino::RunCommand(const CRhinoCommandContext& context)
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