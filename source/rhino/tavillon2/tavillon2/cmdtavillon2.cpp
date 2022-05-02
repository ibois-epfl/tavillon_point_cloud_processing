// cmdtavillon2.cpp : command file
//

#include "StdAfx.h"
#include "tavillon2PlugIn.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN tavillon2 command
//

#pragma region tavillon2 command

// Do NOT put the definition of class CCommandtavillon2 in a header
// file. There is only ONE instance of a CCommandtavillon2 class
// and that instance is the static thetavillon2Command that appears
// immediately below the class definition.

class CCommandtavillon2 : public CRhinoCommand
{
public:
  // The one and only instance of CCommandtavillon2 is created below.
  // No copy constructor or operator= is required.
  // Values of member variables persist for the duration of the application.

  // CCommandtavillon2::CCommandtavillon2()
  // is called exactly once when static thetavillon2Command is created.
  CCommandtavillon2() = default;

  // CCommandtavillon2::~CCommandtavillon2()
  // is called exactly once when static thetavillon2Command is destroyed.
  // The destructor should not make any calls to the Rhino SDK. 
  // If your command has persistent settings, then override 
  // CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
  ~CCommandtavillon2() = default;

  // Returns a unique UUID for this command.
  // If you try to use an id that is already being used, then
  // your command will not work. Use GUIDGEN.EXE to make unique UUID.
  UUID CommandUUID() override
  {
    // {5D412917-2208-429A-9217-06F0B0F6AA37}
    static const GUID tavillon2Command_UUID =
    { 0x5D412917, 0x2208, 0x429A, { 0x92, 0x17, 0x6, 0xF0, 0xB0, 0xF6, 0xAA, 0x37 } };
    return tavillon2Command_UUID;
  }

  // Returns the English command name.
  // If you want to provide a localized command name, then override 
  // CRhinoCommand::LocalCommandName.
  const wchar_t* EnglishCommandName() override { return L"tavillon2"; }

  // Rhino calls RunCommand to run the command.
  CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandtavillon2 object
// Do NOT create any other instance of a CCommandtavillon2 class.
static class CCommandtavillon2 thetavillon2Command;

CRhinoCommand::result CCommandtavillon2::RunCommand(const CRhinoCommandContext& context)
{
  // CCommandtavillon2::RunCommand() is called when the user
  // runs the "tavillon2".

  // TODO: Add command code here.

  // Rhino command that display a dialog box interface should also support
  // a command-line, or script-able interface.

  ON_wString str;
  str.Format(L"The \"%s\" command is under construction.\n", EnglishCommandName());
  const wchar_t* pszStr = static_cast<const wchar_t*>(str);
  if (context.IsInteractive())
    RhinoMessageBox(pszStr, tavillon2PlugIn().PlugInName(), MB_OK);
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
// END tavillon2 command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
