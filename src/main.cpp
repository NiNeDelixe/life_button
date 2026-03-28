#include "core/core.hpp"

#include "core/Constants.hpp"

#include "core/Polling.hpp"

void setup() 
{
	Serial.print("Programm Statring!");

	try
	{
		Polling::startUp();
	}
	catch(const std::exception& e)
	{
		Serial.print("exception!!!");
		Serial.print(e.what());
	}
}

void loop() 
{
	try
	{
		Polling::poll();
	}
	catch(const std::exception& e)
	{
		Serial.print("exception!!!");
		Serial.print(e.what());
	}
}