// wow this got complicated!

#include <string>
#include <map>
#include <iostream>

#include "database.h"
#include "user.h"

Database::Database()
{
	ReadFromFile(); // load objects
}

Database::~Database()
{
    WriteToFile(); // save objects
}

void Database::WriteToFile() // write provider info to file named 'providers\providerNumber
{
	for (const auto& [num, provider] : this->providers) {
		this->providerNums.emplace_back(provider.GetNumber());
		this->oFile.open("providers/" + provider.GetNumber()); // this name should be unique to member or session or something

		provider.WriteToFile(this->oFile);

		this->oFile.close();
	}

	for (const auto& [num, member] : this->members) {
		this->memberNums.emplace_back(member.GetNumber());
		this->oFile.open("members/" + member.GetNumber());

		member.WriteToFile(this->oFile);
		this->oFile.close();
	}

    this->oFile.open("providers/provider_nums");
	for (const auto& num : this->providerNums) {
		oFile << num << '\n';
	}
    this->oFile.close();

    this->oFile.open("members/member_nums");
	for (const auto& num : this->memberNums) {
		oFile << num << '\n';
	}
    this->oFile.close();
}

int Database::ReadFromFile()
{
	this->iFile.open("providers/provider_nums");	

	std::string providerNum;

	while (std::getline(this->iFile, providerNum, '\n')) { // while file not empty, grab line
        if (providerNum != "") // weird edge case where a file is empty but an empty string is still grabbed
		    this->providerNums.emplace_back(providerNum);
	}

	this->iFile.close();

	this->iFile.open("members/member_nums");

	std::string memberNum;

	while (std::getline(this->iFile, memberNum, '\n')) {
        if (memberNum != "")
		    this->memberNums.emplace_back(memberNum);
	}

	this->iFile.close();

	for (const auto& num : this->providerNums) {
		Provider* provider = new Provider(num);

		this->iFile.open("providers/" + num);
		if (!provider->ReadFromFile(this->iFile)) {
			this->iFile.close();
			//return 0; // take this out for now...
		} else {
			this->AddProvider(*provider);
		}
	
		this->iFile.close();
	}

	for (const auto& num : this->memberNums) {
		Member* member = new Member(num);

		this->iFile.open("members/" + num);
		if (!member->ReadFromFile(this->iFile)) {
			this->iFile.close();
			//return 0; // take this out for now...
		} else {
			this->AddMember(*member);
		}

		this->iFile.close();
	}

	return 1;
}

void Database::AddProvider(Provider& provider)
{
    this->providers.emplace(provider.GetNumber(), provider);
}

void Database::DeleteProvider(std::string key)
{
    this->providers.erase(key);
}
                  
void Database::UpdateProvider(Provider& provider) // use the map::swap function, gotta worry about swapping records too
{
    this->DeleteProvider(provider.GetNumber());
    this->AddProvider(provider);
}

Provider& Database::FindProvider(std::string key)
{
    auto found = this->providers.find(key);
    if (found != this->providers.end()) {
        return found->second;
    } else {
        Provider* empty_provider = new Provider;
        return *empty_provider;
    }
}

void Database::AddMember(Member& member)
{
    this->members.emplace(member.GetNumber(), member);
}

void Database::DeleteMember(std::string key)
{
    this->members.erase(key);
}

void Database::UpdateMember(Member& member) // use the map::Swap function instead, gotta worry about swapping records too
{
    this->DeleteMember(member.GetNumber());
    this->AddMember(member);
}

Member& Database::FindMember(std::string key)
{
    //return this->members.find(key)->second;
    auto found = this->members.find(key);
    if (found != this->members.end()) {
        return found->second;
    } else {
        Member* empty_member = new Member;
        return *empty_member;
    }
}

void Database::DisplayProviders()
{
    for (const auto& [num, provider] : this->providers) {
        provider.display();
    }
}

void Database::DisplayMembers()
{
    for (const auto& [num, member] : this->members) {
        member.display();
    }
}

void Database::display()
{
    printf("Displaying Members:\n");
    this->DisplayMembers();
    printf("Displaying Providers:\n");
    this->DisplayProviders();
}

void Database::PrintSummary()
{
    int totalConsultations = 0;
    int totalFee = 0;
    std::cout << "Providers: " << this->providers.size() << '\n';
    for (const auto& [num, provider] : this->providers) {
        std::cout << "Provider Number: " << provider.GetNumber() << "\n\t";
        provider.GetConsultations(totalConsultations);
        std::cout << "Consultations: " << totalConsultations << "\n\t";
        provider.GetFees(totalFee);
        std::cout << "Total Fees: " << totalFee << '\n';
    }
}

Database database;
