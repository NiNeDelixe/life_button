#include "core/core.hpp"

#include "core/Constants.hpp"

#include "core/Polling.hpp"

void setup() 
{
	Serial.begin(115200);
	Serial.setDebugOutput(true); 

	LOG(INFO, "Programm Statring!");

	try
	{
		Polling::startUp();
	}
	catch(const std::exception& e)
	{
		LOG(ERROR, "exception!!!");
		LOG(ERROR, e.what());
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
		LOG(ERROR, "exception!!!");
		LOG(ERROR, e.what());
	}
}