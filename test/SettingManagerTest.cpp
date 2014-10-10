#include "test.h"
#include "SettingManager.h"

TEST_CASE("the setting manager can be created", "[settings]"){
	SettingManager *settings = new SettingManager();
	REQUIRE(settings != NULL);
}

TEST_CASE("the setting manager parses command line arguments",
		"[settings][args]"){

	SettingManager *settings = new SettingManager();

	SECTION("invalid arguments throw an exception"){
		//the arguments that will be passed
		const char *args[2];

		//some test arguments, these shouldn't be real arguments
		args[0] = "prog_name"; //program name
		args[1] = "-asspiss"; //first arg

		REQUIRE_THROWS(settings->passCmdLineArgs(2, args));
	}

	SECTION("valid arguments should throw nothing"){
		//the arguments that will be passed
		const char *args[2];

		//some test arguments, these shouldn't be real arguments
		args[0] = "prog_name"; //program name
		args[1] = "-h"; //first arg

		REQUIRE_NOTHROW(settings->passCmdLineArgs(2, args));
	}

	SECTION("lets see if printing usage works"){
		//ass
	}
}
