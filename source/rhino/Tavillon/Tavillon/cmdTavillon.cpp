// cmdTavillon.cpp : command file
//

#include "StdAfx.h"
#include "TavillonPlugIn.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN Tavillon command
//

#pragma region Tavillon command

// Do NOT put the definition of class CCommandTavillon in a header
// file. There is only ONE instance of a CCommandTavillon class
// and that instance is the static theTavillonCommand that appears
// immediately below the class definition.

class CCommandTavillon : public CRhinoCommand
{
public:
  // The one and only instance of CCommandTavillon is created below.
  // No copy constructor or operator= is required.
  // Values of member variables persist for the duration of the application.

  // CCommandTavillon::CCommandTavillon()
  // is called exactly once when static theTavillonCommand is created.
  CCommandTavillon() = default;

  // CCommandTavillon::~CCommandTavillon()
  // is called exactly once when static theTavillonCommand is destroyed.
  // The destructor should not make any calls to the Rhino SDK. 
  // If your command has persistent settings, then override 
  // CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
  ~CCommandTavillon() = default;

  // Returns a unique UUID for this command.
  // If you try to use an id that is already being used, then
  // your command will not work. Use GUIDGEN.EXE to make unique UUID.
  UUID CommandUUID() override
  {
    // {A2630A60-5F30-43DB-9373-4150C5FF5BE6}
    static const GUID TavillonCommand_UUID =
    { 0xA2630A60, 0x5F30, 0x43DB, { 0x93, 0x73, 0x41, 0x50, 0xC5, 0xFF, 0x5B, 0xE6 } };
    return TavillonCommand_UUID;
  }

  // Returns the English command name.
  // If you want to provide a localized command name, then override 
  // CRhinoCommand::LocalCommandName.
  const wchar_t* EnglishCommandName() override { return L"Tavillon"; }

  // Rhino calls RunCommand to run the command.
  CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandTavillon object
// Do NOT create any other instance of a CCommandTavillon class.
static class CCommandTavillon theTavillonCommand;

CRhinoCommand::result CCommandTavillon::RunCommand(const CRhinoCommandContext& context)
{
  // CCommandTavillon::RunCommand() is called when the user
  // runs the "Tavillon".

  // TODO: Add command code here.

  // Rhino command that display a dialog box interface should also support
  // a command-line, or script-able interface.

  ON_wString str;
  str.Format(L"The \"%s\" command is under construction.\n", EnglishCommandName());
  const wchar_t* pszStr = static_cast<const wchar_t*>(str);
  if (context.IsInteractive())
    RhinoMessageBox(pszStr, TavillonPlugIn().PlugInName(), MB_OK);
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
// END Tavillon command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
