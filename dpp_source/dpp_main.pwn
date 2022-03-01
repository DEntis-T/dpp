/*
* D++ Language
*
* (c) Copyright - 2022, DEntisT
*
* Interpreter driver.
*
*/

#pragma dynamic 215750000

#define dpp_configfile "dpp_settings.cfg"

#include <a_samp>

enum enum_Config
{
	filetoconfig[32],
	execdebug,
	console_pkg,
	user_pkg
}

new g_Config[enum_Config];

// Core:
#include "dpp_interpreter\dpp_core.inc"

stock main()
{
	dpp_init();
	dpp_execute("script.dpp");
	printf("Value of MyVariable: %i", get Integer("MyVariable"));
}