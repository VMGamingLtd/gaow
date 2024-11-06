#include "./config.h"
#include <iostream>
#include <cstdlib>

const char* ENVORONMENT_VAR_NAME = "GAO_ENVIRONMENT";

std::string Config::get__VERIFY_TOKEN_PUB_CERT_FILE_PATH()
{
	const char* environment = std::getenv(ENVORONMENT_VAR_NAME);
	if (environment != nullptr && std::string(environment) == "Test")
	{
		char* val = std::getenv("VERIFY_TOKEN_PUB_CERT_FILE_PATH");
		if (val != nullptr)
		{
			return std::string(val);
		}
		else
		{
			std::cerr << "Environment variable VERIFY_TOKEN_PUB_CERT_FILE_PATH is not set." << std::endl;
			return "";
		}
	}
	return std::string(VERIFY_TOKEN_PUB_CERT_FILE_PATH);
}

std::string Config::get__DB_HOST()
{
	const char* environment = std::getenv(ENVORONMENT_VAR_NAME);
	if (environment != nullptr && std::string(environment) == "Test")
	{
		char* val = std::getenv("DB_HOST");
		if (val != nullptr)
		{
			return std::string(val);
		}
		else
		{
			std::cerr << "Environment variable DB_HOST is not set." << std::endl;
			return "";
		}
	}
	return std::string(DB_HOST);
}

std::string Config::get__DB_DATABASE_NAME()
{
	const char* environment = std::getenv(ENVORONMENT_VAR_NAME);
	if (environment != nullptr && std::string(environment) == "Test")
	{
		char* val = std::getenv("DB_DATABASE_NAME");
		if (val != nullptr)
		{
			return std::string(val);
		}
		else
		{
			std::cerr << "Environment variable DB_DATABASE_NAME is not set." << std::endl;
			return "";
		}
	}
	return std::string(DB_DATABASE_NAME);
}

std::string Config::get__DB_USER_NAME()
{
	const char* environment = std::getenv(ENVORONMENT_VAR_NAME);
	if (environment != nullptr && std::string(environment) == "Test")
	{
		char* val = std::getenv("DB_USER_NAME");
		if (val != nullptr)
		{
			return std::string(val);
		}
		else
		{
			std::cerr << "Environment variable DB_USER_NAME is not set." << std::endl;
			return "";
		}
	}
	return std::string(DB_USER_NAME);
}

std::string Config::get__DB_PASSWORD()
{
	const char* environment = std::getenv(ENVORONMENT_VAR_NAME);
	if (environment != nullptr && std::string(environment) == "Test")
	{
		char* val = std::getenv("DB_PASSWORD");
		if (val != nullptr)
		{
			return std::string(val);
		}
		else
		{
			std::cerr << "Environment variable DB_PASSWORD is not set." << std::endl;
			return "";
		}
	}
	return std::string(DB_PASSWORD);
}
