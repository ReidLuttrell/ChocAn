#include "user.h"
#include "database.h"
#include "data.h"

void User::Create(User& user)
{
    std::string userName, userAddress;
    std::cout << "Enter username: ";
    std::cin >> userName;
    std::cin.ignore(999999, '\n');
    std::cout << "Enter address: ";
    std::cin >> userAddress;
    std::cin.ignore(999999, '\n');

    user = User(userName, userAddress);
}

void User::display()
{
    std::cout << "Displaying User:\n";
    std::cout << "username: " << this->userName << '\n';
    std::cout << "address: " << this->userAddress << '\n';
}

void Provider::WriteToFile(std::ofstream& file)
{
	file << this->userName << '\n';
    file << this->userAddress << '\n';
    file << this->providerNumber << '\n';
    file << this->totalConsultation << '\n';
    file << this->totalFee << '\n';

    for (const auto& [num, record] : this->records) { 
        record.WriteToFile(file);
    }
}

int Provider::ReadFromFile(std::ifstream& file)
{
    if (!std::getline(file, this->userName, '\n')) { // file empty
	    return 0;
    }

    std::getline(file, this->userAddress, '\n');
    std::getline(file, this->providerNumber, '\n');
    std::getline(file, this->totalConsultation, '\n');
    std::getline(file, this->totalFee, '\n');

    ProviderServiceRecord* record;
    
    do {
        record = new ProviderServiceRecord;
    }
    while (record->ReadFromFile(file) && this->AddRecord(*record)); 

    return 1;
}

void Provider::Create()
{
    std::string providerNumber, totalConsultation, totalFee;

    User user;
    User::Create(user);

    std::cout << "Enter Provider Number: ";
    std::cin >> providerNumber;
    std::cin.ignore(999999, '\n');
    std::cout << "Enter Total Consultation: ";
    std::cin >> totalConsultation;
    std::cin.ignore(999999, '\n');
    std::cout << "Enter Total Fee: ";
    std::cin >> totalFee;
    std::cin.ignore(999999, '\n');

    *this = Provider(user, providerNumber, totalConsultation, totalFee);
}

void Provider::GetFees(int& total)
{
    for (const auto& [num, record] : this->records)
        record.AddFee(total);
}

void Provider::GetConsultations(int& total)
{
    for (const auto& [num, record] : this->records)
        ++total;
}

void Provider::Flow()
{
    while (true) {
        std::string number;
        std::cout << "Enter your provider number, then press Enter: ";
        std::cin >> number;
        std::cin.ignore(9999999, '\n');
        Provider& provider = database.FindProvider(number);
        if (provider.GetNumber() == "") {
            std::cout << "NOT FOUND, please try again\n";
            return;
        }

        int option = 0;

        std::cout << "Choose Option:\n\t1) Bill a member\n\t2) Email to me the provider directory\n\t3) Exit and return to the home page\n\t";
        std::cin >> option;
        std::cin.ignore(99999, '\n');

        //Member* member = new Member;

        switch(option) {
        case(1):{ //not done yety
            //this->serviceFees = atoi(this->serviceFees.c_str()) + cost;
            //add fees to member
            break;
        }
        case(2):
        ///Provider::display();
        provider.display();
            // send email, print out the data
            /// notes on what to print out :
            // Provider name
            // provier number
            // provider streeet adress
            // provider city
            // provider state
            // provider zip code
            // each service provided in formated thing
            // :
            //  databasee->display  
            //  
            //  void Provider::display()
            // :
            //  total number of conultations with members 3 digits
            // total fee for week, 99,999.99 max
            break;
        case(3):
            // return to main page / home page
            return;

            //[[fallthrough]]; // c++17 keyword to silence switch fallthrough warnings
        //case(4):
            // return to home page
            //database.display();
            //break;
        //case(5):
            //database.display();
            //break;

        default:
            std::cout << "Invalid option, try again.\n";
            continue;
        }
    }
}

int Provider::AddRecord(ProviderServiceRecord& record)
{
    this->records.emplace(record.GetNumber(), record);

    return 1;
}

void Provider::display()
{
    User::display();
    std::cout << "provider number: " << this->providerNumber << '\n';
    std::cout << "total consultation: " << this->totalConsultation << '\n';
    std::cout << "total fee: " << this->totalFee << '\n';

    for (const auto& [num, record] : this->records)
        record.display();
}

void Manager::Create()
{
    User user;
    User::Create(user);

    *this = Manager(user);
}

void Manager::Flow()
{
	while (true) {
	    int option = 0;
        std::cout << "Select which report to run (for this week up to this day/time)\n\t1) Member Report\n\t2) Provider Report\n\t3) Summary report for accounts\n\t4) EFT Data for provider\n\t5) Quit\nEnter number, then press Enter:";
        std::cin >> option;
        std::cin.ignore(9999999, '\n');

        std::string memberNumber;
        std::string providerNumber;
        Provider provider;

        switch(option) {
        case(1): // Member Report
        {
	        std::cout << "Enter member's ID, then press enter: ";
            std::cin >> memberNumber;
            std::cin.ignore(99999, '\n');
            Member& member = database.FindMember(memberNumber);
            if (member.GetNumber() == "") {
                std::cout << "NOT FOUND, please try again\n";
                return;
            }
            else
                member.display();
            break;
        }
		case(2): // Provider Report
        {
	        std::cout << "Enter provider's ID, then press Enter: ";
            std::cin >> providerNumber;
            std::cin.ignore(99999, '\n');
            provider = database.FindProvider(providerNumber);
            if (provider.GetNumber() == "") {
                std::cout << "NOT FOUND, please try again\n";
                return;
            }
            else
                provider.display();
            break;
        }
        case(3): // Save Summary report for accounts ek;
            std::cout << "Enter provider's ID, then press Enter: ";
            std::cin >> providerNumber;
            std::cin.ignore(99999, '\n');
            provider = database.FindProvider(providerNumber);
            
			if (provider.GetNumber() == "") {
                std::cout << "NOT FOUND, please try again\n";
                return;
            }

			database.PrintSummary();

            break;
        case(4):
            std::cout << "EFT data saved to members and providers folder respectively.\n";
            break;
        case(5):
            return;
        default:
	        std::cout << "Invalid option, try again.\n";
            continue;
    	}
	}
}

void Manager::display()
{
    User::display();
}

void Operator::Create()
{
    User user;
    User::Create(user);

    *this = Operator(user);
}

void Operator::Flow()
{
    while (true) {
        int user_type = 0;
        std::cout << "Choose Which to Update:\n\t1) Member\n\t2) Provider\n\t3) Member Record\n\t4) Provider Record\n\t5) Quit\n";
        std::cin >> user_type;
        std::cin.ignore(9999999, '\n');

        if (user_type == 5)
            return;

        if (user_type < 1 || user_type > 4) {
            printf("Invalid option, try again.");
            continue;
        }

        int option = 0;
        std::cout << "Choose an Option:\n\t1) Add\n\t2) Delete\n\t3) Update\n";
        std::cin >> option;
        std::cin.ignore(9999999, '\n');

        std::string num;

        switch(option) {
        case(1): // Add
            if (user_type == 1) {
                Member* member = new Member;
                member->Create(); // accept input for all the members
                database.AddMember(*member);
            } else if (user_type == 2) {
                Provider* provider = new Provider;
                provider->Create();
                database.AddProvider(*provider);
            } else if (user_type == 3) {
                MemberServiceRecord* record = new MemberServiceRecord;
                record->Create();
                Member& member = database.FindMember(record->GetNumber());
                member.AddRecord(*record);
            } else {
                ProviderServiceRecord* record = new ProviderServiceRecord;
                record->Create();
                Provider& provider = database.FindProvider(record->GetNumber());
                provider.AddRecord(*record);
            }

            break;
        case(2): // Delete
            std::cout << "Input ID number\n";
            std::cin >> num;
            std::cin.ignore(99999999, '\n');

            if (user_type == 1) {
                database.DeleteMember(num);
            } else if (user_type == 2) {
                database.DeleteProvider(num);
            } else if (user_type == 3) {

            } else {

            }

            break;
        case(3): // Update
            if (user_type == 1) { 
                std::cout << "Enter member ID\n";
                std::cin >> num;
                std::cin.ignore(1000, '\n');
                Member& member = database.FindMember(num);
                if(member.GetNumber() == ""){
                    std::cout << "NOT FOUND, please try again\n";
                    continue;
                }
                else{
                    std::cout << "Enter V for valid or I for invalid and S for suspended\n";
                    char checkStatus = 'i';
                    std::cin >> checkStatus;
                    std::cin.ignore(1000, '\n');
                    if(checkStatus == 'i' || checkStatus == 'I')
                        member.updateStatus(0); // 0 = false = invlaid
                    else
                    {
                        if(checkStatus == 'v' || checkStatus == 'V')
                            member.updateStatus(1); //1 = true = valid
                        else
                        {
                            if(checkStatus == 's' || checkStatus == 'S')
                                member.updateStatus(2); //sus
                                else{
                                    std::cout << "Error, please try again and enter correct input\n";
                                    continue;
                                }
                        }
                    }
                }
            } else {
                //database.DeleteMember(num);
                /*Provider* provider = new Provider;
                provider->Create();
                database.UpdateProvider(*provider);*/
                //std::string number;
                std::cout << "Enter the provider number\n";
                std::cin >> num;
                std::cin.ignore(9999999, '\n');
                Provider& provider = database.FindProvider(num);
                if (provider.GetNumber() == "") {
                    std::cout << "NOT FOUND, please try again\n";
                    return;
                }
                else
                    provider.update();
            }
            break;
        default:
            std::cout << "Invalid option, try again.\n";
            continue;
        }
    }
}


void Provider::update(){
    std::cout << "What to update? Enter y or n, for yes or no.\n";
    char decision;
    /*std::cout << "Provider number?\n";
    std::cin >> decision;
    std::cin.ignore(1000, '\n');
    if(decision == 'y' || decision == 'Y'){
        std::string newprovnum;
        std::cout << "Enter new number\n";
        std::cin >> newprovnum;
        std::cin.ignore(1000, '\n');
        providerNumber = newprovnum;
    }
    decision = 'n';*/
    std::cout << "Provider total consultation?\n";
    std::cin >> decision;
    std::cin.ignore(1000, '\n');
    if(decision == 'y' || decision == 'Y'){
        std::string newtotcon;
        std::cout << "Enter new total consultation\n";
        std::cin >> newtotcon;
        std::cin.ignore(1000, '\n');
        totalConsultation = newtotcon;
    }
    decision = 'n';
    std::cout << "Provider fee total?\n";
    std::cin >> decision;
    std::cin.ignore(1000, '\n');
    if(decision == 'y' || decision == 'Y'){
        std::string newfee;
        std::cout << "Enter new total fee\n";
        std::cin >> newfee;
        std::cin.ignore(1000, '\n');
        totalFee = newfee;
    }
    return;
    /*string providerNumber;
    string totalConsultation;
    string totalFee;*/
}



void Operator::display()
{
    User::display();
}

void Member::WriteToFile(std::ofstream& file)
{
    file << this->userName << '\n';
    file << this->userAddress << '\n';
    file << this->memberNumber << '\n';
    file << this->memberStatus << '\n';

    for (const auto& [num, record] : this->records) {
	    record.WriteToFile(file);
	}
}

int Member::ReadFromFile(std::ifstream& file)
{
    if (!std::getline(file, this->userName, '\n'))
        return 0;

    std::getline(file, this->userAddress, '\n');
    std::getline(file, this->memberNumber, '\n');
    std::getline(file, this->memberStatus, '\n');

    MemberServiceRecord* record;

    do {
        record = new MemberServiceRecord;
    }
    while (record->ReadFromFile(file) && this->AddRecord(*record));

	return 1;
}

void Member::Create()
{
    std::string memberNumber, memberStatus;

    User user;
    User::Create(user);

    std::cout << "Enter Member Number: ";
    std::cin >> memberNumber;
    std::cin.ignore(999999, '\n');
    char statusCheck = 'I';
    std::cout << "Member status? Enter V for valid or I for invalid\n";
    std::cin >> statusCheck;
    std::cin.ignore(1000, '\n');
    if(statusCheck == 'I' || statusCheck == 'i')
        memberStatus = "Invalid";
    else
        memberStatus = "Valid";

    *this = Member(user, memberNumber, memberStatus);
}

void Member::Flow()
{
    std::string number;
    std::cout << "Enter member ID\n";
    std::cin >> number;
    std::cin.ignore(1000, '\n');
    Member& member = database.FindMember(number);
    if(member.GetNumber() == ""){
        std::cout << "NOT FOUND, please try again\n";
        return;
    }
	while (true) {
	    int option = 0;
        std::cout << "Enter the option you want to use\n\t(1 Check if valid member status\n\t(2 display services recieved\n\t(3 Quit\n";
        std::cin >> option;
        std::cin.ignore(9999999, '\n');

        std::string memberNumber;
        std::string providerNumber;

        switch(option) {
        case(1): // Valid
        {
            if(member.memberStatus == "Valid"){
                std::cout << member.memberStatus << std::endl;
            }
            else{
                if(member.memberStatus == "Invalid"){
                    std::cout << "Invalid\n";
                }
                    else{
                        std::cout << "Suspended\n";
                    }
            }
            break;
        }
		case(2): // services
            //Member::display();
            member.display();
            break;
        case(3):
            return;
        default:
	        std::cout << "Invalid option, try again.\n";
            continue;
    	}
    }
}

int Member::AddRecord(MemberServiceRecord& record)
{
    this->records.emplace(record.GetNumber(), record);

    return 1;
}

void Member::display()
{
    User::display();
    std::cout << "Member Number: " << this->memberNumber << '\n';
    std::cout << "Member Status: " << this->memberStatus << '\n';
    
    for (const auto& [num, record] : this->records)
        record.display();
}



void Member::updateStatus(int newstatus){
    if(newstatus == 1)
        memberStatus = "Valid";
    else
    {
        if(newstatus == 0 )
            memberStatus = "Invalid";
        else
        {
            memberStatus = "Suspended";
        }
    }
}
