#pragma once

#include "./../../protobuf/MessageHeader.pb.h"
#include "./../../protobuf/Ping.pb.h"
#include "./../Dispatcher.h"

#include <iostream>
#include <sstream>

namespace message
{
	namespace parser
	{
		class Ping
		{
		public:
			static void serialize(std::ostream& ostream, const GaoProtobuf::MessageHeader& messageHeader, const GaoProtobuf::Ping& message);
			static GaoProtobuf::Ping parse(std::istream& istream);
		};

		class Pong
		{
		public:
			static void serialize(std::ostream& ostream, const GaoProtobuf::MessageHeader& messageHeader, const GaoProtobuf::Pong& message);
			static GaoProtobuf::Pong parse(std::istream& istream);
		};
	}
}