#ifndef USER_H
#define USER_H

#include <fstream>
#include <iostream>
#include <string>
#include <map>

using namespace std;

class ProviderServiceRecord;
class MemberServiceRecord;

class User
{
public:
    User() : userName(), userAddress() {};
    User(const string& _userName, const string& _userAddress) 
        : userName(_userName), userAddress(_userAddress) {};
    User(const User& user) {
        this->userName = user.userName;
        this->userAddress = user.userAddress;
    }; 

    virtual void Create(User& user);
    
    virtual ~User() {};

    virtual string GetName() { return userName; };

    virtual void display();

    virtual void Flow() {}; // made non pure virtual for now
protected:
    string userName;
    string userAddress;
};

class Provider : public User
{
public:
    Provider() : User(), providerNumber(), totalConsultation(), totalFee() {};
	Provider(const string& _providerNumber)
		: User(), providerNumber(_providerNumber), totalConsultation(), totalFee() {};
    Provider(const string& _userName, const string& _userAddress, const string& _providerNumber, const string& _totalConsultation, const string& _totalFee) 
        : User(_userName, _userAddress), providerNumber(_providerNumber), totalConsultation(_totalConsultation), totalFee(_totalFee) {};
    Provider(const User& user, const string& _providerNumber, const string& _totalConsultation, const string& _totalFee)
        : User(user), providerNumber(_providerNumber), totalConsultation(_totalConsultation), totalFee(_totalFee) {};

    virtual ~Provider() {};

    void WriteToFile(std::ofstream& file);
    int ReadFromFile(std::ifstream& file);

    virtual void Create();

    string GetNumber() { return this->providerNumber; };
    string getTotalFee();
    void printProviderInfo(string);
    void printFile(string);
    void printAllProvider();
    void update();

    void GetConsultations(int& total);
    void GetFees(int& total);

    virtual void Flow();

    int AddRecord(ProviderServiceRecord& record);

    virtual void display();

private:
    string providerNumber;
    string totalConsultation;
    string totalFee;

    std::multimap<std::string, ProviderServiceRecord&> records;
};

class Manager : public User
{
public:
    Manager() 
        : User() {};
    Manager(const string& _userName, const string& _userAddress) 
        : User(_userName, _userAddress) {};
    Manager(const User& user)
        : User(user) {};

    virtual ~Manager() {};

    virtual void Create();

    virtual void Flow();

    virtual void display();
};

class Operator : public User
{
public:
    Operator() 
        : User() {};
    Operator(const string& _userName, const string& _userAddress) 
        : User(_userName, _userAddress) {};
    Operator(const User& user)
        : User(user) {};

    virtual ~Operator() {};

    virtual void Create();

    virtual void Flow();

    virtual void display();
};

// database -> map of members; member -> map of services provided; services provided -> write to file based on member ID or something

class Member : public User
{
public:
    Member() 
        : User(), memberNumber(), memberStatus() {};
	Member(const string& _memberNumber)
		: User(), memberNumber(_memberNumber), memberStatus() {};
    Member(const string& _userName, const string& _userAddress, const string& _memberNumber, const string& _memberStatus) 
        : User(_userName, _userAddress), memberNumber(_memberNumber), memberStatus(_memberStatus) {};
    Member(const User& user, const string& _memberNumber, const string& _memberStatus)
        : User(user), memberNumber(_memberNumber), memberStatus(_memberStatus) {};
    virtual ~Member() {};

    void WriteToFile(std::ofstream& file);
    int ReadFromFile(std::ifstream& file);

    virtual void Create();

    //string GetName(Member &source);
    string GetNumber() { return this->memberNumber; };
    void printMemberInfo(string);
    void printAllMembers(void);
    void printFile(string);
    void updateStatus(int);

    virtual void Flow();

    int AddRecord(MemberServiceRecord& record);

    virtual void display();

private:
    string memberNumber;
    string memberStatus;

    std::multimap<std::string, MemberServiceRecord&> records;
};

#endif
