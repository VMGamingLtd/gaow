#include "Ping.h"

namespace message
{
    namespace parser
    {

        void Ping::serialize(std::ostream& ostream, const GaoProtobuf::MessageHeader& messageHeader, const GaoProtobuf::Ping& message)
        {

            // serialize the message header
            Dispatcher::serializeMessageHeader(ostream, messageHeader);

            uint32_t messageSize = message.ByteSizeLong();
            Dispatcher::serializeMessageaObjectSize(ostream, messageSize);

            if (!message.SerializeToOstream(&ostream))
            {
                throw std::runtime_error("Ping::serializePing(): Failed to serialize message");
            }
        }

        GaoProtobuf::Ping Ping::parse(std::istream& istream)
        {
            // parse the message header
            GaoProtobuf::MessageHeader messageHeader = Dispatcher::parseMessageHeader(istream);

            // get the size of the message
            uint32_t messageSize = Dispatcher::parseMessageaObjectSize(istream);

            // read the message
            std::vector<char> messageBuffer(messageSize);
            istream.read(messageBuffer.data(), messageSize);

            GaoProtobuf::Ping message;
            if (!message.ParseFromArray(messageBuffer.data(), messageSize))
            {
                throw std::runtime_error("Ping::parsePing(): Failed to parse message");
            }

            return message;
        }

        void Pong::serialize(std::ostream& ostream, const GaoProtobuf::MessageHeader& messageHeader, const GaoProtobuf::Pong& message)
        {
            // serialize the message header
            Dispatcher::serializeMessageHeader(ostream, messageHeader);

            uint32_t messageSize = message.ByteSizeLong();
            Dispatcher::serializeMessageaObjectSize(ostream, messageSize);

            if (!message.SerializeToOstream(&ostream))
            {
                throw std::runtime_error("Dispatcher::serializePong(): Failed to serialize message");
            }
        }

        GaoProtobuf::Pong Pong::parse(std::istream& istream)
        {
            // parse the message header
            GaoProtobuf::MessageHeader messageHeader = Dispatcher::parseMessageHeader(istream);

            // get the size of the message
            uint32_t messageSize = Dispatcher::parseMessageaObjectSize(istream);

            // read the message
            std::vector<char> messageBuffer(messageSize);
            istream.read(messageBuffer.data(), messageSize);

            GaoProtobuf::Pong message;
            if (!message.ParseFromArray(messageBuffer.data(), messageSize))
            {
                throw std::runtime_error("Dispatcher::parsePong(): Failed to parse message");
            }

            return message;
        }
    }
}
