#include <iostream>
#include <string>

#include "command_ex.hpp"


void CopyCommand::execute() const {
      std::cout<<"Executing Copy Command.\n";
}

void PasteCommand::execute() const {
      std::cout<<"Executing Paste Command.\n";
}

void DeleteCommand::execute() const{
      std::cout<<"Executing Delete Command.\n";
}

void UndoCommand::execute() const {
      std::cout<<"Executing Undo Command.\n";
}

void SaveCommand::execute() const {
      std::cout<<"Executing Save Command.\n";
}

Command& Button::click() const {
  std::cout << "Button " << label_ << " clicked.\n";
  command_.execute();
  return command_;
}

Command& TextEditorApp::clickCopyButton() const {
  return copyButton->click();
}
Command& TextEditorApp::clickPasteButton() const {
    return pasteButton->click();
}
Command& TextEditorApp::clickDeleteButton() const {
    return deleteButton->click();
}
Command& TextEditorApp::clickUndoButton() const {
    return undoButton->click();
}

Command& TextEditorApp::clickSaveButton() const {
    return saveButton->click();
}

