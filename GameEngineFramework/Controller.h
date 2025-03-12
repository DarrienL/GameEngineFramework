#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "StandardIncludes.h"

struct ControllerInfo
{
	// Members
	SDL_JoystickID ID = -1;
	SDL_GameController* Controller = nullptr;
	string Name;
	vector<SDL_GameControllerButton> Buttons;
	Position LeftAxis = { };
	Position RightAxis = { };

	// Methods
	string ToString() {
		string ButtonsString = "Buttons Down: ";
		for (unsigned int count = 0; count < Buttons.size(); count++) {
			ButtonsString += to_string(Buttons[count]) + "; ";
		}
		ButtonsString += " [LX: " + to_string(LeftAxis.X) + ", LY: " + to_string(LeftAxis.Y) + "] ";
		ButtonsString += " [RX: " + to_string(RightAxis.X) + ", RY: " + to_string(RightAxis.Y) + "] ";
		return ButtonsString;
	}
};

class Controller
{
public:
	// Constructors/Destructors
	Controller();
	virtual ~Controller();

	// Accessors
	vector<ControllerInfo>& GetControllers() { return m_controllers; }

	// Methods
	void DetectControllers();
	bool Added(SDL_Event _event);
	bool Removed(SDL_Event _event);
	bool ProcessButtons(SDL_Event _event);
	bool ProcessMotion(SDL_Event _event);
	string ToString();

private:
	// Methods
	void Add(SDL_GameController* _controller, int _controllerID);

	// Members
	vector<ControllerInfo> m_controllers;
};

#endif

