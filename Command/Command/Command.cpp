#include <iostream>

class Command
{
public:
	virtual void execute() = 0;
};

class LightOnCommand : public Command
{
public:
	LightOnCommand()
	{

	}

	void execute()
	{

	}
};

class SimpleRemoteControl
{
public:
	SimpleRemoteControl() {}

	void SetCommand(Command* command)
	{
		slot = command;
	}

	void ButtonWasPressed()
	{
		slot->execute();
	}

private:
	Command* slot;
};

class RemoteControlTest
{
public:
	void start()
	{
		SimpleRemoteControl *remote = new SimpleRemoteControl();
		LightOnCommand* lightOn = new LightOnCommand();

		remote->SetCommand(lightOn);
		remote->ButtonWasPressed();
	}
};