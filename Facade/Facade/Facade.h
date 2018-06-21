#pragma once
#include <iostream>

class HomeThreaterFacade
{
public:
	HomeThreaterFacade(Amplifier* amp,
		Tuner* tuner,
		DvdPlayer* dvd,
		CdPlayer* cd,
		Projector* projector,
		TheaterLights* lights,
		Screen* screen,
		PopcornPopper* popper)
	{
		this->amp = amp;
		this->tuner = tuner;
		this->dvd = dvd;
		this->cd = cd;
		this->projector = projector;
		this->screen = screen;
		this->lights = lights;
		this->popper = popper;
	}

	void WathcMovie(std::string movie)
	{
		std::cout << "Get ready to watch a movice..." << std::endl;
		popper->on();
		....
	}

	void EndMovie()
	{
		std::cout << "Shutting movie theater down..." << std::endl;
		popper->of();
	}

private:
	Amplifier *amp;
	Tuner* tuner;
	DvdPlayer* dvd;
	CdPlayer* cd;
	Projector* projector;
	TheaterLights* lights;
	Screen* screen;
	PopcornPopper* popper;
};

