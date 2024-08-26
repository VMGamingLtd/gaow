#pragma once

#include <string>
#include <vector>
#include <mariadb/conncpp.hpp>

class DbConnection
{
private:
	std::string getDBconnectionString();
	sql::Connection* connection;

	std::string ppStmtStr_getUserGroups;
	sql::PreparedStatement* ppStmt_getUserGroups;

	std::string ppStmtStr_getGroupMembers;
	sql::PreparedStatement* ppStmt_getGroupMembers;

	std::string ppStmtStr_getGroupMembersCount;
	sql::PreparedStatement* ppStmt_getGroupMembersCount;

	std::string ppStmtStr_getOwnerGroups;
	sql::PreparedStatement* ppStmt_getOwnerGroups;

	void connect();
	void disconnect();

public:
	DbConnection();
	~DbConnection();
	std::vector<int> getUserGroups(int userId);
	std::vector<int> getGroupMembers(int groupId);
	int getGroupMembersCount(int groupId);
	std::vector<int> getOwnerGroups(int userId);

	static DbConnection* wsrvDbConnection;
	
};