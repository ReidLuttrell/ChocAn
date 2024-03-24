#include <string.h>
#include <string>
#include <iostream>

//#include <fstream>
#include "data.h"
#include "user.h"

ProviderServiceRecord::ProviderServiceRecord()
{

}

ProviderServiceRecord::ProviderServiceRecord(std::string serviceDate, std::string currentDate, std::string providerNumber, std::string memberName, std::string memberNumber, std::string serviceCode, std::string fees)
{
    this->currentDate = serviceDate;
    this->serviceDate = currentDate;
    this->providerNumber = providerNumber;
    this->memberName = memberName;
    this->memberNumber = memberNumber;
    this->serviceCode = serviceCode;
    this->fees = fees;
}

ProviderServiceRecord::~ProviderServiceRecord()
{

}

void ProviderServiceRecord::WriteToFile(std::ofstream& file)
{
    file << this->serviceDate << '\n';
    file << this->currentDate << '\n';
    file << this->providerNumber << '\n';
    file << this->memberName << '\n';
    file << this->memberNumber << '\n';
    file << this->serviceCode << '\n';
    file << this->fees << '\n';
}

int ProviderServiceRecord::ReadFromFile(std::ifstream& file)
{ 
    if (!std::getline(file, this->serviceDate, '\n')) { // file empty
        return 0;
    }
    
    std::getline(file, this->currentDate, '\n');
    std::getline(file, this->providerNumber, '\n');
    std::getline(file, this->memberName, '\n');
    std::getline(file, this->memberNumber, '\n');
    std::getline(file, this->serviceCode, '\n');
    std::getline(file, this->fees, '\n');

    return 1;
}

void ProviderServiceRecord::AddFee(int& total)
{
    total += std::stoi(this->fees);
}

void ProviderServiceRecord::Create()
{
	std::cout << "Enter Service Date (MM-DD-YY): ";
	std::getline(std::cin, this->serviceDate, '\n');
    std::cout << "Enter Current Date (MM-DD-YY HH:MM:SS): ";
	std::getline(std::cin, this->currentDate, '\n');
    std::cout << "Enter Provider Number: ";
    std::getline(std::cin, this->providerNumber, '\n');
	std::cout << "Enter Member Name: ";
	std::getline(std::cin, this->memberName, '\n');
	std::cout << "Enter Member Number: ";
	std::getline(std::cin, this->memberNumber, '\n');
	std::cout << "Enter Service Code: ";
	std::getline(std::cin, this->serviceCode, '\n');
	std::cout << "Enter Fees: ";
	std::getline(std::cin, this->fees, '\n');
}

void ProviderServiceRecord::display()
{
    std::cout << "Displaying Record:\n";
    std::cout << "Service Date: " << this->serviceDate << '\n';
    std::cout << "Current Date: " << this->currentDate << '\n';
    std::cout << "Provider Number: " << this->providerNumber << '\n';
    std::cout << "Member Name: " << this->memberName << '\n';
    std::cout << "Member Number: " << this->memberNumber << '\n';
    std::cout << "Service Code: " << this->serviceCode << '\n';
    std::cout << "Fees: " << this->fees << '\n';
}

MemberServiceRecord::MemberServiceRecord(std::string serviceDate, std::string providerName, std::string serviceName, std::string memberNumber)
{
    this->serviceDate = serviceDate;
    this->providerName = providerName;
    this->serviceName = serviceName;
    this->memberNumber = memberNumber;
}

void MemberServiceRecord::WriteToFile(std::ofstream& file)
{
    file << this->serviceDate << '\n';
    file << this->providerName << '\n';
    file << this->serviceName << '\n';
    file << this->memberNumber << '\n';
}

int MemberServiceRecord::ReadFromFile(std::ifstream& file)
{

    if (!std::getline(file, this->serviceDate,'\n')) { // file empty
        return 0;
    }

    std::getline(file, this->providerName, '\n');
    std::getline(file, this->serviceName, '\n');
    std::getline(file, this->memberNumber, '\n');

    return 1;
}

void MemberServiceRecord::Create()
{
    std::cout << "Enter Service Date: ";
    std::getline(std::cin, this->serviceDate, '\n');
	std::cout << "Enter Provider Name: ";
	std::getline(std::cin, this->providerName, '\n');
	std::cout << "Enter Service Name: ";
	std::getline(std::cin, this->serviceName, '\n');
    std::cout << "Enter Member Number: ";
    std::getline(std::cin, this->memberNumber, '\n');
}

void MemberServiceRecord::display()
{
    std::cout << "Displaying Record:\n";
    std::cout << "Service Date: " << this->serviceDate << '\n';
    std::cout << "Provider Name: " << this->providerName << '\n';
    std::cout << "Service Name: " << this->serviceName << '\n';
    std::cout << "Member Number: " << this->memberNumber << '\n';
}
