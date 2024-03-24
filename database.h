#ifndef DATABASE_H
#define DATABASE_H

#include <fstream>
#include <vector>

class ProviderServiceRecord;
class MemberServiceRecord;

class Provider;
class Member;

class Database
{
public:
    Database(); // pull all the data from the file
    
    Database(Database const&) = delete; // cuz singleton
    Database& operator=(Database const&) = delete;

    ~Database(); // loop through members/providers, write name, address, and then loop records and call records->write_to_file();
    void WriteToFile();
    int ReadFromFile();

    void AddProvider(Provider& record);
    void DeleteProvider(std::string key); // key = provider number
    void UpdateProvider(Provider& provider);
    Member& FindMember(std::string key);

    void AddMember(Member& member);
    void DeleteMember(std::string key); // key = member number
    void UpdateMember(Member& member);
    Provider& FindProvider(std::string key);

    void DisplayProviders();
    void DisplayMembers();

    void display();

    void PrintSummary();

private:
    std::ofstream oFile;
    std::ifstream iFile;

    std::map<std::string, Provider&> providers;
    std::map<std::string, Member&> members;
	std::vector<std::string> providerNums;
	std::vector<std::string> memberNums;
};

extern Database database;

#endif
