//Defaults.h
//very simple file which just contains constant data for everything
//for example error codes
//-mgc480

#pragma once

namespace Defaults{
	enum Status {GOOD = 0, FILE_NOT_FOUND = 1, FILE_CORRUPT = 2, OUT_OF_MEMORY = 3, UNKNOWN_ERROR = 4, INVALID_FILE = 5};
}