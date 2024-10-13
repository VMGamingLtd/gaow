#include "./config.h"
#include "./WsSocketContext.h"
#include "./message/Dispatcher.h"
#include "./WsConnection.h"
#include "./Utils.h"
#include "./DbConnection.h"
#include "./groups/Groups.h"
#include "./gaos/gaos.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <jwt-cpp/jwt.h>


void verifyToken(std::string jwt) {
    try
    {
        std::cout << "jwt:" << std::endl;
        std::cout << jwt << std::endl;

        std::string token = jwt;

        std::string rsa_pub_key = Utils::readFileContents(VERIFY_TOKEN_PUB_CERT_FILE_PATH);
        std::cout << "rsa_pub_key:" << std::endl;
        std::cout << rsa_pub_key << std::endl;

        auto verify = jwt::verify()
            // We only need an RSA public key to verify tokens
            .allow_algorithm(jwt::algorithm::rs256(rsa_pub_key, "", "", ""));
            // We expect token to come from a known authorization server
            //.with_issuer("auth0");

        auto decoded = jwt::decode(token);

        verify.verify(decoded);

        for (auto& e : decoded.get_header_json())
            std::cout << e.first << " = " << e.second << std::endl;
        for (auto& e : decoded.get_payload_json())
            std::cout << e.first << " = " << e.second << std::endl;
    }
	catch (const jwt::error::token_verification_exception& e)
	{
		std::cout << "verifyToken(): warning: unauthorized" << e.what() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "verifyToken(): error: " << e.what() << std::endl;
	}
}

int main_1()
{
    std::string token = "eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiJCcm9vZDkyODMwIiwiZXhwIjo0ODc0MTg4MTE0LCJ1c2VyX2lkIjo3NiwidXNlcl90eXBlIjoiR3Vlc3RVc2VyIiwiZGV2aWNlX2lkIjoxfQ.Zte9sXrjX5_yDrR73U7pt3uFbxiuZrx4W2WiJqYlkTublY0f2_MJZUjqhk9ENuy1UiZq5sroEY8jfPfvLG7saNS0Crv0E0Ed2eTmRN3I-ytuVVYsiiZYHjY1G8PUOux-qJjWUdl2uTG2nGZG-wAluRvoUpKoGiaFxuI4nb8N5V9vzZGrtaSJcDepoK6YSn_25BS_tHzw0Hy4arTPowW_xQ-Tke_O9DlHS8YxoJsbU7Tnur5_XwMvdfFEHO1YMyGf4GEzeTFQ6-EqMX5fenPRa61-5dDFQto8wDGPxEgnDJSjrt00kva3GT4SCAwQWWytxF1TnYBvZV1fMJba5WXJetcygibhnk4zwma642FCVp0547syPeJUjsh9zRKbpe0drIDKzScoO8kHW9hf1koWrxrOeChNAC1YZQGLBtW3PEDfa0MZnZMgaWKWlgQMz4OKNgSyMvcm2SDUmqGw24RVR2_RPj3n1tMUVrv0fOQFac3jIRAwK6ckt8j8INujHXmItlKFoh5pXadj5Lz82E-3vJGimb1wkldb8awsyr2a5Njr9gYmb4HD3BM7K2RLEUlyyVES_07OBsnLc0-xhLamMHrHPNhe01jwNrMDSslThekvgHfq45kC-YTWNn29_0nqsJKXpeXl0i5sB0orxiL6-Qssb9_3Ctdz1_-31HBl_Ic";
    verifyToken(token);
    return 0;
}

/*
#include <iostream>

int main() {
    std::cout << "wsrv: Hello, World!" << std::endl;
    return 0;
}
*/

/* We simply call the root header file "App.h", giving you uWS::App and uWS::SSLApp */
#include <App.h> // this is the file 'uWebSockets/src/App.h' 

int main() {
    /* ws->getUserData returns one of these */
    /*
    struct SocketContextData {
    };
    */

	gaos::GaosServer::runInThread();
    // sleep for 1s
	std::this_thread::sleep_for(std::chrono::seconds(1));

    Groups::startCacheCleaningThread();

    /* Keep in mind that uWS::SSLApp({options}) is the same as uWS::App() when compiled without SSL support.
     * You may swap to using uWS:App() if you don't need SSL */
    DbConnection::wsrvDbConnection = new DbConnection();
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
        .open = [](auto *ws) {
            /* Open event here, you may access ws->getUserData() which points to a PerSocketData struct */
            std::cout << "A client connected" << std::endl; //@@@@@@@@@@@@@@@@@@
            WsConnection::addConnection(ws);

        },
        .message = [](auto *ws, std::string_view message, uWS::OpCode opCode) {
            /* This is the opposite of what you probably want; compress if message is LARGER than 16 kb
             * the reason we do the opposite here; compress if SMALLER than 16 kb is to allow for 
             * benchmarking of large message sending without compression */

            //std::cout << "Message received: " << message << std::endl; //@@@@@@@@@@@@@@@@@@
            //ws->send("pong", opCode, message.length() > 16 * 1024);
            //ws->send(message, opCode, message.length() < 16 * 1024);

            // print message in hex
            //std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@ cp100: data: " << message::Dispatcher::toHexString(message) << std::endl;

            message::Dispatcher::handleMessage(ws, message, opCode); 
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
        .close = [](auto *ws, int /*code*/, std::string_view /*message*/) {
            /* You may access ws->getUserData() here */
            std::cout << "A client disconnected" << std::endl; //@@@@@@@@@@@@@@@@@@
            WsConnection::removeConnection(ws);
        }
    }).listen("127.0.0.1", 9001, [](auto *listen_socket) {
        if (listen_socket) {
            std::cout << "Listening on port " << 9001 << std::endl;
        }
    }).run();



    return 0;
}
