// cmdtavillon_rhino.cpp : command file
//

#include "StdAfx.h"
#include "tavillon_rhinoPlugIn.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN tavillon_rhino command
//

#pragma region tavillon_rhino command

// Do NOT put the definition of class CCommandtavillon_rhino in a header
// file. There is only ONE instance of a CCommandtavillon_rhino class
// and that instance is the static thetavillon_rhinoCommand that appears
// immediately below the class definition.

class CCommandtavillon_rhino : public CRhinoCommand
{
public:
  // The one and only instance of CCommandtavillon_rhino is created below.
  // No copy constructor or operator= is required.
  // Values of member variables persist for the duration of the application.

  // CCommandtavillon_rhino::CCommandtavillon_rhino()
  // is called exactly once when static thetavillon_rhinoCommand is created.
  CCommandtavillon_rhino() = default;

  // CCommandtavillon_rhino::~CCommandtavillon_rhino()
  // is called exactly once when static thetavillon_rhinoCommand is destroyed.
  // The destructor should not make any calls to the Rhino SDK. 
  // If your command has persistent settings, then override 
  // CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
  ~CCommandtavillon_rhino() = default;

  // Returns a unique UUID for this command.
  // If you try to use an id that is already being used, then
  // your command will not work. Use GUIDGEN.EXE to make unique UUID.
  UUID CommandUUID() override
  {
    // {3C008B46-129B-49F2-9C2E-2DCE8800E5EF}
    static const GUID tavillon_rhinoCommand_UUID =
    { 0x3C008B46, 0x129B, 0x49F2, { 0x9C, 0x2E, 0x2D, 0xCE, 0x88, 0x0, 0xE5, 0xEF } };
    return tavillon_rhinoCommand_UUID;
  }

  // Returns the English command name.
  // If you want to provide a localized command name, then override 
  // CRhinoCommand::LocalCommandName.
  const wchar_t* EnglishCommandName() override { return L"tavillon_rhino"; }

  // Rhino calls RunCommand to run the command.
  CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandtavillon_rhino object
// Do NOT create any other instance of a CCommandtavillon_rhino class.
static class CCommandtavillon_rhino thetavillon_rhinoCommand;

CRhinoCommand::result CCommandtavillon_rhino::RunCommand(const CRhinoCommandContext& context)
{
  // CCommandtavillon_rhino::RunCommand() is called when the user
  // runs the "tavillon_rhino".

  // TODO: Add command code here.

  // Rhino command that display a dialog box interface should also support
  // a command-line, or script-able interface.

  ON_wString str;
  str.Format(L"The \"%s\" command is under construction.\n", EnglishCommandName());
  const wchar_t* pszStr = static_cast<const wchar_t*>(str);
  if (context.IsInteractive())
    RhinoMessageBox(pszStr, tavillon_rhinoPlugIn().PlugInName(), MB_OK);
  else
    RhinoApp().Print(pszStr);

  // TODO: Return one of the following values:
  //   CRhinoCommand::success:  The command worked.
  //   CRhinoCommand::failure:  The command failed because of invalid input, inability
  //                            to compute the desired result, or some other reason
  //                            computation reason.
  //   CRhinoCommand::cancel:   The user interactively canceled the command 
  //                            (by pressing ESCAPE, clicking a CANCEL button, etc.)
  //                            in a Get operation, dialog, time consuming computation, etc.

  return CRhinoCommand::success;
}

#pragma endregion

//
// END tavillon_rhino command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
