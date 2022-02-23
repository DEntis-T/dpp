/*
* D++ Language
*
* (c) Copyright - 2022, DEntisT
*
* Interpreter driver.
*
*/

#define dpp_configfile "../gamemodes/dpp_settings.cfg"

#include <a_samp>

enum enum_Config
{
	file[32]
}

new g_Config[enum_Config];

// Core:
#include "dpp_interpreter\dpp_core.inc"

stock main()
{
	return dpp_execute();
}