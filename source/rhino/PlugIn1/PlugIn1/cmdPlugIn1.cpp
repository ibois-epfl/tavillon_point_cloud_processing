// cmdPlugIn1.cpp : command file
//

#include "StdAfx.h"
#include "PlugIn1PlugIn.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN PlugIn1 command
//

#pragma region PlugIn1 command

// Do NOT put the definition of class CCommandPlugIn1 in a header
// file. There is only ONE instance of a CCommandPlugIn1 class
// and that instance is the static thePlugIn1Command that appears
// immediately below the class definition.

class CCommandPlugIn1 : public CRhinoCommand
{
public:
  // The one and only instance of CCommandPlugIn1 is created below.
  // No copy constructor or operator= is required.
  // Values of member variables persist for the duration of the application.

  // CCommandPlugIn1::CCommandPlugIn1()
  // is called exactly once when static thePlugIn1Command is created.
  CCommandPlugIn1() = default;

  // CCommandPlugIn1::~CCommandPlugIn1()
  // is called exactly once when static thePlugIn1Command is destroyed.
  // The destructor should not make any calls to the Rhino SDK. 
  // If your command has persistent settings, then override 
  // CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
  ~CCommandPlugIn1() = default;

  // Returns a unique UUID for this command.
  // If you try to use an id that is already being used, then
  // your command will not work. Use GUIDGEN.EXE to make unique UUID.
  UUID CommandUUID() override
  {
    // {4EBC0225-054F-40DE-82E1-DE2DFB422164}
    static const GUID PlugIn1Command_UUID =
    { 0x4EBC0225, 0x54F, 0x40DE, { 0x82, 0xE1, 0xDE, 0x2D, 0xFB, 0x42, 0x21, 0x64 } };
    return PlugIn1Command_UUID;
  }

  // Returns the English command name.
  // If you want to provide a localized command name, then override 
  // CRhinoCommand::LocalCommandName.
  const wchar_t* EnglishCommandName() override { return L"PlugIn1"; }

  // Rhino calls RunCommand to run the command.
  CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandPlugIn1 object
// Do NOT create any other instance of a CCommandPlugIn1 class.
static class CCommandPlugIn1 thePlugIn1Command;

CRhinoCommand::result CCommandPlugIn1::RunCommand(const CRhinoCommandContext& context)
{
  // CCommandPlugIn1::RunCommand() is called when the user
  // runs the "PlugIn1".

  // TODO: Add command code here.

  // Rhino command that display a dialog box interface should also support
  // a command-line, or script-able interface.

  ON_wString str;
  str.Format(L"The \"%s\" command is under construction.\n", EnglishCommandName());
  const wchar_t* pszStr = static_cast<const wchar_t*>(str);
  if (context.IsInteractive())
    RhinoMessageBox(pszStr, PlugIn1PlugIn().PlugInName(), MB_OK);
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
// END PlugIn1 command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
