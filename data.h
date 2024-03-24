#ifndef DATA_H
#define DATA_H

#include <fstream>
#include <map>

class Provider;
class Member;

class ProviderServiceRecord
{
public:
    ProviderServiceRecord();
    ProviderServiceRecord(std::string, std::string, std::string, std::string, std::string, std::string, std::string);
    ~ProviderServiceRecord();

    void WriteToFile(std::ofstream& file);
    int ReadFromFile(std::ifstream& file);

    void AddFee(int& total);

    std::string GetNumber() { return this->providerNumber; };

    void Create();

    void display();
private:
    std::string serviceDate;
    std::string currentDate;
    std::string providerNumber;
    std::string memberName;
    std::string memberNumber;
    std::string serviceCode;
    std::string fees;
};

class MemberServiceRecord
{
public:
    MemberServiceRecord() = default;
    MemberServiceRecord(std::string, std::string, std::string, std::string);
    ~MemberServiceRecord() = default;

    void WriteToFile(std::ofstream& file);
    int ReadFromFile(std::ifstream& file);

    std::string GetNumber() { return this->memberNumber; };

    void Create();

    void display();
private: 
    std::string serviceDate;
    std::string providerName;
    std::string serviceName;
    std::string memberNumber;
};

#endif
