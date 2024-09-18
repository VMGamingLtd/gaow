#include "./DbConnection.h"
#include "./config.h"
#include <iostream>

DbConnection* DbConnection::wsrvDbConnection = nullptr;

DbConnection::DbConnection()
{
	connection = nullptr;

	ppStmtStr_getUserGroups = 

"select\n"
"  g.Id as GroupId\n"	
"from\n"
"  Groupp g\n"
"join GroupMember gm on g.Id = gm.GroupId\n"
"where\n"
"  gm.UserId = ?\n"
"\n"
"-- ensuure idempotency\n"
"-- so that limit 1  always yields same GroupId or none\n"
"order by GroupId\n"
"-- when creating the group there's a constraint that user cannot be member of more then one group,\n"
"-- also for every user there exists one and only one group such the user is owner of that group\n"
"limit 1\n"
";\n"


	;


	ppStmt_getUserGroups = nullptr;

	ppStmtStr_getGroupMembers = 
"select\n"
"  gm.UserId\n"
"from\n"
"  GroupMember gm\n"
"where\n"
"  gm.GroupId = ?\n"
";\n"
	;

	ppStmt_getGroupMembers = nullptr;

	ppStmtStr_getGroupMembersCount =
"select\n"
"  count(*) as cnt"
"from\n"
"  GroupMember gm\n"
"where\n"
"  gm.GroupId = ?\n"
";\n"
		;
	ppStmt_getGroupMembersCount = nullptr;

	ppStmtStr_getOwnerGroups =
"select\n"
"  g.Id as GroupId\n"
"from\n"
"  Groupp as g\n"
" where\n"
"  g.OwnerId = ?\n"
"order by g.Id\n"
"limit 1\n"
";\n"
;
	ppStmt_getOwnerGroups = nullptr;


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

		if (ppStmt_getGroupMembersCount != nullptr)
		{
			delete ppStmt_getGroupMembersCount;
			ppStmt_getGroupMembersCount = nullptr;
		}

		if (ppStmt_getOwnerGroups != nullptr)
		{
			delete ppStmt_getOwnerGroups;
			ppStmt_getOwnerGroups = nullptr;
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

int DbConnection::getGroupMembersCount(int groupId)
{
	int membersCount = 0;

	if (connection == nullptr)
	{
		connect();
		if (connection == nullptr)
		{
			std::cerr << "DbConnection::getGroupMembersCount(): connection failed" << std::endl;
			return membersCount;
		}
	}

	if (ppStmt_getGroupMembersCount == nullptr)
	{
		try
		{
			ppStmt_getGroupMembersCount = this->connection->prepareStatement(ppStmtStr_getGroupMembersCount);
		}
		catch (sql::SQLException& e)
		{
			std::cerr << "DbConnection::getGroupMembersCount(): prepareStatement failed: " << e.what() << std::endl;
			disconnect();
			return membersCount;
		}
	}
	ppStmt_getGroupMembersCount->setInt(1, groupId);
	sql::ResultSet* rs;
	try
	{
		rs = ppStmt_getGroupMembersCount->executeQuery();
	}
	catch (sql::SQLException& e)
	{
		std::cerr << "DbConnection::getGroupMembersCount(): executeQuery failed: " << e.what() << std::endl;
		disconnect();
		return membersCount;
	}
	while (rs->next())
	{
		membersCount = rs->getInt(1);
		break;
	}
	delete rs;

	return membersCount;
}
std::vector<int> DbConnection::getOwnerGroups(int userId)
{
	std::vector<int> groups;

	if (connection == nullptr)
	{
		connect();
		if (connection == nullptr)
		{
			std::cerr << "DbConnection::getOwnerGroups(): connection failed" << std::endl;
			return groups;
		}
	}

	if (ppStmt_getOwnerGroups == nullptr)
	{
		try
		{
			ppStmt_getOwnerGroups = this->connection->prepareStatement(ppStmtStr_getOwnerGroups);
		}
		catch (sql::SQLException& e)
		{
			std::cerr << "DbConnection::getOwnerGroups(): prepareStatement failed: " << e.what() << std::endl;
			disconnect();
			return groups;
		}
	}
	ppStmt_getOwnerGroups->setInt(1, userId);
	sql::ResultSet* rs;
	try
	{
		rs = ppStmt_getOwnerGroups->executeQuery();
	}
	catch (sql::SQLException& e)
	{
		std::cerr << "DbConnection::getOwnerGroups(): executeQuery failed: " << e.what() << std::endl;
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

