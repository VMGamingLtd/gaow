#pragma once

#include "../../protobuf/MessageHeader.pb.h"
#include <iostream>
#include <libusockets.h>

namespace message
{
	namespace gaos
	{
		class GaosBroadcast
		{
		private:
		public:
			static void groupCreditsChange(struct us_socket_t* s, const GaoProtobuf::MessageHeader& messageHeader, std::istream& message);
		};
	}
}
