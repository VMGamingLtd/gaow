#pragma once

#include <string>
#include "./uuid.h"

struct SocketContextData {
	std::string uid;
	SocketContextData() : uid(generate_uuid()) {}
};
