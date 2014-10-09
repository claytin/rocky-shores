#include "test.h"
#include "SettingManager.h"

//TEST_CASE( "vectors can be sized and resized", "[vector]" ) {

	//std::vector<int> v( 5 );

	//REQUIRE( v.size() == 5 );
	//REQUIRE( v.capacity() >= 5 );

	//SECTION( "resizing bigger changes size and capacity" ) {
		//v.resize( 10 );

		//REQUIRE( v.size() == 10 );
		//REQUIRE( v.capacity() >= 10 );
	//}
	//SECTION( "resizing smaller changes size but not capacity" ) {
		//v.resize( 0 );

		//REQUIRE( v.size() == 0 );
		//REQUIRE( v.capacity() >= 5 );
	//}
	//SECTION( "reserving bigger changes capacity but not size" ) {
		//v.reserve( 10 );

		//REQUIRE( v.size() == 5 );
		//REQUIRE( v.capacity() >= 10 );
	//}
	//SECTION( "reserving smaller does not change size or capacity" ) {
		//v.reserve( 0 );

		//REQUIRE( v.size() == 5 );
		//REQUIRE( v.capacity() >= 5 );
	//}
//}

TEST_CASE("the setting manager can be created", "[settings]"){
	SettingManager *settings = new SettingManager();
	REQUIRE(settings != NULL);
}

TEST_CASE("the setting manager parses command line arguments", "[settings]"){

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
}
