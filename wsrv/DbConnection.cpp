#include "./DbConnection.h"
#include "./config.h"
#include <iostream>

DbConnection* DbConnection::wsrvDbConnection = nullptr;

DbConnection::DbConnection()
{
	 connection = nullptr;

	ppStmtStr_getUserGroups = "select Id from chatroom where OwnerId = ?";
	ppStmt_getUserGroups = nullptr;

	ppStmtStr_getGroupMembers = "select chm.UserId from chatroom chr join chatroommember chm on chr.Id = chm.ChatRoomId where chr.Id = 5";
	ppStmt_getGroupMembers = nullptr;
}

DbConnection::~DbConnection()
{
	disconnect();
}

std::string DbConnection::getDBconnectionString()
{
	std::string url = "";
	return url + "jdbc:mariadb://" + DB_HOST + "/" + DB_DATABASE_NAME;
}

void DbConnection::connect()
{
	sql::Driver* driver = sql::mariadb::get_driver_instance();
	std::string connStr = getDBconnectionString();
	sql::SQLString url(connStr);
	sql::Properties properties({{"user", DB_USER_NAME}, {"password", DB_PASSWORD}});

	if (connection == nullptr)
	{
		connection = driver->connect(url, properties);
		if (connection == nullptr)
		{
			std::cerr << "DbConnection::connect(): connection failed: " << connStr << std::endl;
		}
	}
}

void DbConnection::disconnect()
{
	if (connection != nullptr)
	{
		connection->close();
		delete connection;
		connection = nullptr;

		if (ppStmt_getUserGroups != nullptr)
		{
			delete ppStmt_getUserGroups;
			ppStmt_getUserGroups = nullptr;
		}

		if (ppStmt_getGroupMembers != nullptr)
		{
			delete ppStmt_getGroupMembers;
			ppStmt_getGroupMembers = nullptr;
		}
	}
}

std::vector<int> DbConnection::getUserGroups(int userId)
{
	std::vector<int> groups;

	if (connection == nullptr)
	{
		connect();
		if (connection == nullptr)
		{
			std::cerr << "DbConnection::getUserGroups(): connection failed" << std::endl;
			return groups;
		}
	}

	if (ppStmt_getUserGroups == nullptr)
	{
		try
		{
			ppStmt_getUserGroups = this->connection->prepareStatement(ppStmtStr_getUserGroups);
		}
		catch (sql::SQLException& e)
		{
			std::cerr << "DbConnection::getUserGroups(): prepareStatement failed: " << e.what() << std::endl;
			disconnect();
			return groups;
		}
	}
	ppStmt_getUserGroups->setInt(1, userId);
	sql::ResultSet* rs;
	try 
	{
		rs = ppStmt_getUserGroups->executeQuery();
	}
	catch (sql::SQLException& e)
	{
		std::cerr << "DbConnection::getUserGroups(): executeQuery failed: " << e.what() << std::endl;
		delete ppStmt_getUserGroups;
		ppStmt_getUserGroups = nullptr;
		disconnect();
		return groups;
	}
	while (rs->next())
	{
		groups.push_back(rs->getInt(1));
	}
	delete rs;

	return groups;
}

std::vector<int> DbConnection::getGroupMembers(int groupId)
{
	std::vector<int> members;

	if (connection == nullptr)
	{
		connect();
		if (connection == nullptr)
		{
			std::cerr << "DbConnection::getGroupMembers(): connection failed" << std::endl;
			return members;
		}
	}

	if (ppStmt_getGroupMembers == nullptr)
	{
		try
		{
			ppStmt_getGroupMembers = this->connection->prepareStatement(ppStmtStr_getGroupMembers);
		}
		catch (sql::SQLException& e)
		{
			std::cerr << "DbConnection::getGroupMembers(): prepareStatement failed: " << e.what() << std::endl;
			disconnect();
			return members;
		}
	}
	ppStmt_getGroupMembers->setInt(1, groupId);
	sql::ResultSet* rs;
	try
	{
		rs = ppStmt_getGroupMembers->executeQuery();
	}
	catch (sql::SQLException& e)
	{
		std::cerr << "DbConnection::getGroupMembers(): executeQuery failed: " << e.what() << std::endl;
		delete ppStmt_getGroupMembers;
		ppStmt_getGroupMembers = nullptr;
		disconnect();
		return members;
	}
	while (rs->next())
	{
		members.push_back(rs->getInt(1));
	}
	delete rs;

	return members;
}

