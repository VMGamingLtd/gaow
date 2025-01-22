#pragma once

#include <string>

#define IS_DEBUG true

#define VERIFY_TOKEN_PUB_CERT_FILE_PATH "/w1/gaow/certs/gao/cert.crt"

#define DB_HOST "localhost"
#define DB_DATABASE_NAME "gaos"
#define DB_USER_NAME "root"
#define DB_PASSWORD "root"

class Config {
public:
	static std::string get__VERIFY_TOKEN_PUB_CERT_FILE_PATH();
	static std::string get__DB_HOST();
	static std::string get__DB_DATABASE_NAME();
	static std::string get__DB_USER_NAME();
	static std::string get__DB_PASSWORD();
};
