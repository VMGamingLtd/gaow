#include "./WsSocketContext.h"
#include "./message/Dispatcher.h"
#include <sstream>
#include <iostream>
#include <fstream>
/*
#include <iostream>

int main() {
    std::cout << "wsrv: Hello, World!" << std::endl;
    return 0;
}
*/

/* We simply call the root header file "App.h", giving you uWS::App and uWS::SSLApp */
#include <App.h> // this is the file 'uWebSockets/src/App.h' 

/* This is a simple WebSocket echo server example.
 * You may compile it with "WITH_OPENSSL=1 make" or with "make" */
int main()
{
    {
        GaoProtobuf::MessageHeader messageHeader;
        messageHeader.set_namespaceid(1);
        messageHeader.set_classid(1);
        messageHeader.set_methodid(1);
        messageHeader.set_msg("Hello from wsrv!");
        std::fstream output("/w1/pok/message_header", std::ios::out | std::ios::trunc | std::ios::binary);
        if (!messageHeader.SerializeToOstream(&output)) {
            std::cerr << "Failed to write messageHeader." << std::endl;
            return -1;
        }
    }

    {
        GaoProtobuf::MessageHeader messageHeader;
        std::fstream input("/w1/pok/message_header", std::ios::in | std::ios::binary);
        if (!messageHeader.ParseFromIstream(&input)) {
          std::cerr << "Failed to parse messageHeader." << std::endl;
          return -1;
        }
        std::cout << "messageHeader.namespaceid(): " << messageHeader.namespaceid() << std::endl;
        std::cout << "messageHeader.classid(): " << messageHeader.classid() << std::endl;
        std::cout << "messageHeader.classid(): " << messageHeader.methodid() << std::endl;
        std::cout << "messageHeader.msg(): " << messageHeader.msg() << std::endl;
    }

    {
        GaoProtobuf::Ping ping;
        ping.set_message("Hello from wsrv!");
        std::fstream output("/w1/pok/ping", std::ios::out | std::ios::trunc | std::ios::binary);
        if (!ping.SerializeToOstream(&output)) {
            std::cerr << "Failed to write ping." << std::endl;
            return -1;
        }
    }
    {
        GaoProtobuf::Ping ping;
        std::fstream input("/w1/pok/ping", std::ios::in | std::ios::binary);
        if (!ping.ParseFromIstream(&input)) {
          std::cerr << "Failed to parse ping." << std::endl;
          return -1;
        }
        std::cout << "ping.message(): " << ping.message() << std::endl;
    }



}

int main_1() {
    /* ws->getUserData returns one of these */
    /*
    struct SocketContextData {
    };
    */

    /* Keep in mind that uWS::SSLApp({options}) is the same as uWS::App() when compiled without SSL support.
     * You may swap to using uWS:App() if you don't need SSL */
    uWS::App({
        /* There are example certificates in uWebSockets.js repo */
        .key_file_name = "misc/key.pem",
        .cert_file_name = "misc/cert.pem",
        .passphrase = "1234"
    }).ws<SocketContextData>("/*", {
        /* Settings */
        .compression = uWS::CompressOptions(uWS::DEDICATED_COMPRESSOR_4KB | uWS::DEDICATED_DECOMPRESSOR),
        .maxPayloadLength = 100 * 1024 * 1024,
        .idleTimeout = 16,
        .maxBackpressure = 100 * 1024 * 1024,
        .closeOnBackpressureLimit = false,
        .resetIdleTimeoutOnSend = false,
        .sendPingsAutomatically = true,
        /* Handlers */
        .upgrade = nullptr,
        .open = [](auto */*ws*/) {
            /* Open event here, you may access ws->getUserData() which points to a PerSocketData struct */
            std::cout << "A client connected" << std::endl; //@@@@@@@@@@@@@@@@@@

        },
        .message = [](auto *ws, std::string_view message, uWS::OpCode opCode) {
            /* This is the opposite of what you probably want; compress if message is LARGER than 16 kb
             * the reason we do the opposite here; compress if SMALLER than 16 kb is to allow for 
             * benchmarking of large message sending without compression */

            //std::cout << "Message received: " << message << std::endl; //@@@@@@@@@@@@@@@@@@
            //ws->send("pong", opCode, message.length() > 16 * 1024);
            //ws->send(message, opCode, message.length() < 16 * 1024);

            // print message in hex
            std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@ cp100: data: " << message::Dispatcher::toHexString(message) << std::endl;

            GaoProtobuf::Ping ping;
            ping.set_message("Hello from wsrv!");
            std::ostringstream ostream;
            ping.set_message("Hello from wsrv!");
            ping.SerializeToOstream(&ostream);

            std::string str = ostream.str();
            //ping.ParseFromArray(message.data(), message.size());
            ping.ParseFromString(str);
            std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@ cp105: message: " << message::Dispatcher::toHexString(str) << std::endl;
            std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@ cp105: message: " << ping.message() << std::endl;

            // message::Dispatcher::handleMessage(ws, message, opCode); @@@@@@@@@@@@@@@@@@@@@@
        },
        .dropped = [](auto */*ws*/, std::string_view /*message*/, uWS::OpCode /*opCode*/) {
            /* A message was dropped due to set maxBackpressure and closeOnBackpressureLimit limit */
        },
        .drain = [](auto */*ws*/) {
            /* Check ws->getBufferedAmount() here */
        },
        .ping = [](auto */*ws*/, std::string_view) {
            /* Not implemented yet */
        },
        .pong = [](auto */*ws*/, std::string_view) {
            /* Not implemented yet */
        },
        .close = [](auto */*ws*/, int /*code*/, std::string_view /*message*/) {
            /* You may access ws->getUserData() here */
            std::cout << "A client disconnected" << std::endl; //@@@@@@@@@@@@@@@@@@
        }
    }).listen(9001, [](auto *listen_socket) {
        if (listen_socket) {
            std::cout << "Listening on port " << 9001 << std::endl;
        }
    }).run();
}
