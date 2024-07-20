#pragma once

#include "./uuid.h"
#include <string>

struct SocketContextData {
	std::string uid;
	SocketContextData() : uid{generate_uuid()} {}
};
