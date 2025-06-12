#include <iostream>
#include <string>
#include <vector>
/**
 * Command design pattern:
 * The command design pattern is used when we need to decouple the sender of a request from the
 * receiver of the request.
 * It allows us to encapsulate a request as a command object, which can then be passed around and
 * executed at a later time.
 * This pattern is useful for implementing features like undo/redo functionality, logging, and
 * queueing of requests.
 * In this example we will implement a simple command pattern with a command interface, and corresponding
 * concrete command classes. We will also implement a simple invoker class that will execute the commands.
 * We will implement a sample application which is a editor that can execute commands like copy, paste, delete,
 * and undo.
 * How should I start? Let me start by defining the application class first.
 *  */
// Command Interface
class Command
{
public:
  virtual ~Command() = default;
  virtual void execute() const = 0;
};

//Concrete Command classes
class CopyCommand: public Command
{
  public:
    void execute() const override;
};

class PasteCommand: public Command
{
  public:
    void execute() const override;
};

class DeleteCommand: public Command
{
  public:
    void execute() const override;
};

class UndoCommand: public Command
{
  public:
    void execute() const override;
};

class SaveCommand: public Command
{
  public:
    void execute() const override;
};

//Button Class
class Button
{
  public:
    Button(const std::string& label, Command& command) : label_{label}, command_{command}{}
    Command& click() const;
private:
    std::string label_;
    Command& command_;
};

//Text Editor Task History
class TextEditorCommandHistory
{
  std::vector<Command*> history_;
public:
  void addCommand(Command *command) {
    history_.push_back(command);
  }

  Command* getLastCommand() {
    if (!history_.empty()) {
      Command * cmd = history_.back();
      history_.pop_back();
      return cmd;
    }
  }
};

// Application class
class TextEditorApp
{
private:
  std::string editorText;
  TextEditorCommandHistory commandHistory;
public:
  Button  *copyButton{nullptr};
  Button  *pasteButton{nullptr};
  Button  *deleteButton{nullptr};
  Button  *undoButton{nullptr};
  Button  *saveButton{nullptr};

  TextEditorApp(Button *copyButton, 
                Button *pasteButton,
                Button *deleteButton,
                Button *undoButton,
                Button *saveButton)
      : copyButton(copyButton), pasteButton(pasteButton),
        deleteButton(deleteButton), undoButton(undoButton), saveButton(saveButton) {}
  Command& clickCopyButton() const;
  Command& clickPasteButton() const;
  Command& clickDeleteButton() const;
  Command& clickUndoButton() const;
  Command& clickSaveButton() const;
  void saveCommand(Command *command) {
    commandHistory.addCommand(command);
  }
  Command* getLastCommand() {
    return commandHistory.getLastCommand();
  }
};