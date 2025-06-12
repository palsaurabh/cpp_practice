#include <iostream>
#include <string>
#include "command_ex.hpp"
   
int main() {
    CopyCommand cpcmd;
    PasteCommand pastecmd;
    DeleteCommand delcmd;
    UndoCommand undocmd;
    SaveCommand savecmd;
    // Create buttons for the text editor
    Button copyButton("Copy", cpcmd);
    Button pasteButton("Paste", pastecmd);
    Button deleteButton("Delete", delcmd);
    Button undoButton("Undo", undocmd);
    Button saveButton("Save", savecmd);

    // Create the text editor application with the buttons
    TextEditorApp textEditorApp(&copyButton, &pasteButton, &deleteButton, &undoButton, &saveButton);

    // Simulate button clicks
    Command& cmd = textEditorApp.clickCopyButton();
    textEditorApp.saveCommand(&cmd);
    Command& cmd1 = textEditorApp.clickPasteButton();
    textEditorApp.saveCommand(&cmd1);
    Command& cmd2 = textEditorApp.clickDeleteButton();
    textEditorApp.saveCommand(&cmd2);
    Command& cmd3 = textEditorApp.clickUndoButton();
    textEditorApp.saveCommand(&cmd3);
    Command& cmd4 = textEditorApp.clickSaveButton();
    textEditorApp.saveCommand(&cmd4);
    textEditorApp.getLastCommand()->execute();
    textEditorApp.getLastCommand()->execute();
    textEditorApp.getLastCommand()->execute();
    textEditorApp.getLastCommand()->execute();
    textEditorApp.getLastCommand()->execute();
    return 0;
}
