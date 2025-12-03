#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
using namespace std; 

enum enChoices {
	Show = 1,
	AddNew = 2,
	Delete = 3,
	UpDate = 4,
	Find = 5,
	Exit = 6
};

const string ClientsFileName = "Clients.txt";

struct stClient
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AccountBalance = 0;
	bool MarkForDelete = false;
};

enChoices ReadChoice()
{
	int Num = 0;
	cin >> Num;
	return enChoices(Num);

}

void ShowMainMenueScreen()
{
	cout << "===========================================" << endl;
	cout << right << setw(30) << "Main Menu Screen" << endl;
	cout << "===========================================" << endl;
	cout << "\t" << "[1] Show Clients List." << endl;
	cout << "\t" << "[2] Add New Clients." << endl;
	cout << "\t" << "[3] Delete Clients." << endl;
	cout << "\t" << "[4] Update Clients Info." << endl;
	cout << "\t" << "[5] Find Clients." << endl;
	cout << "\t" << "[6] Exit." << endl;
	cout << "===========================================" << endl;
	cout << "Choose what do you want to do?[1 to 6]?";

}

vector <string> SplitString(string S1, string Delim)
{
	vector <string> vString;
	short pos = 0;
	string sWord; // define a string variable
	// use fine() function to get the position of the delimiters
	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos);
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		// erase() until positon and move to next word
		S1.erase(0, pos + Delim.length());
	}
	if (S1 != "")
	{
		// it print last word of the string
		vString.push_back(S1);
	}
	return vString;
}

stClient CounvertLineToRecord(string Line, string Separator = "#//#")
{
	stClient Clinet;
	vector <string> vClinetData;
	vClinetData = SplitString(Line, Separator);
	Clinet.AccountNumber = vClinetData[0];
	Clinet.PinCode = vClinetData[1];
	Clinet.Name = vClinetData[2];
	Clinet.Phone = vClinetData[3];
	Clinet.AccountBalance = stod(vClinetData[4]); // case string to double
	return Clinet;
}

string CounvertRecordToLine(stClient Client, string Separator = "#//#")
{
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Separator;
	stClientRecord += Client.PinCode + Separator;
	stClientRecord += Client.Name + Separator;
	stClientRecord += Client.Phone + Separator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}

void AddDataLineToFile(string FileName, string strDataLine)
{
	fstream MyFile;
	char Revision = 'y';
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open())
	{
		MyFile << strDataLine << endl;
		MyFile.close();
	}
}

stClient ReadNewClient()
{
	stClient Client;
	cout << "Enter Account Number ? ";
	getline(cin >> ws, Client.AccountNumber);
	cout << "Enter PinCode ? ";
	getline(cin, Client.PinCode);
	cout << "Enter Name ? ";
	getline(cin, Client.Name);
	cout << "Enter Phone ? ";
	getline(cin, Client.Phone);
	cout << "Enter Account Balance ? ";
	cin >> Client.AccountBalance;

	return Client;
}

void AddNewClient()
{
	stClient Client;
	Client = ReadNewClient();
	AddDataLineToFile(ClientsFileName, CounvertRecordToLine(Client));
}

void AddClients()
{
	char AddMore = 'Y';
	do
	{
		system("cls");
		cout << "\n______________________________________\n\n";
		cout << setw(30) << "Add New Clients Screen" << endl;
		cout << "______________________________________" << endl;

		cout << "Adding New Client : \n\n";
		AddNewClient();
		cout << "\nClient Added Successfully , do you want to add more clients ? [Y or N] ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}

vector <stClient> LoadClientsDataFromFile(string FileName)
{
	vector <stClient> vClient;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		stClient Clinet;
		while (getline(MyFile, Line))
		{
			Clinet = CounvertLineToRecord(Line);
			vClient.push_back(Clinet);
		}
		MyFile.close();
	}
	return vClient;
}

void PrintClientRecord(stClient Client)
{
	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(10) << Client.PinCode;
	cout << "| " << left << setw(25) << Client.Name;
	cout << "| " << left << setw(12) << Client.Phone;
	cout << "| " << left << setw(12) << Client.AccountBalance << "|";
}

void PrintOneClinet(stClient Client)
{
	//cout << "\n\nThe following is the extracted client record : \n\n";
	cout << "\n\nThe following are the client details : \n\n";
	cout << "Account Number  : " << Client.AccountNumber << endl;
	cout << "PinCode         : " << Client.PinCode << endl;
	cout << "Name            : " << Client.Name << endl;
	cout << "Phone           : " << Client.Phone << endl;
	cout << "Account Balance : " << Client.AccountBalance << endl;
}

void PrintAllClientsData(vector <stClient> vClients)
{
	cout << "\n\t\t\t Client List (" << vClients.size() << ") Client(s). ";
	cout << "\n______________________________________________________";
	cout << "_______________________________\n\n";


	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "Pin Code ";
	cout << "| " << left << setw(25) << "Client Name";
	cout << "| " << left << setw(12) << "Phone ";
	cout << "| " << left << setw(12) << "Balance     |";
	cout << "\n______________________________________________________";
	cout << "_______________________________\n";

	for (stClient Client : vClients)
	{
		PrintClientRecord(Client);
		cout << endl;
	}
	cout << "______________________________________________________";
	cout << "_______________________________\n";

}

void ShowClientList()
{
	vector <stClient> vClient = LoadClientsDataFromFile(ClientsFileName);
	PrintAllClientsData(vClient);
}

bool FindClientByAccountNumber(string AccountNumber, vector <stClient> vClients, stClient& Client)
{
	for (stClient C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "\nPlease enter AccountNumber ? ";
	cin >> AccountNumber;
	return AccountNumber;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{
	for (stClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

vector <stClient> SaveClientsDataToFile(string FileName, vector <stClient> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out); //overwrite
	string DataLine;
	if (MyFile.is_open())
	{
		for (stClient C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				// we only write record that are not marked for delete
				DataLine = CounvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{
	stClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintOneClinet(Client);
		cout << "\n\nAre you sure you want delete client ? [Y or N] ?";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveClientsDataToFile(ClientsFileName, vClients);
			vClients = LoadClientsDataFromFile(ClientsFileName);
			cout << "\n\n Client Deleted Successfully. \n";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is NOT Found!\n";
		return false;
	}
}

void DeleteClient()
{
	system("cls");
	cout << "\n______________________________________\n\n";
	cout << setw(30) << "Delete Client Screen" << endl;
	cout << "______________________________________" << endl;

	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);

}

stClient ChangeClientRecord(string AccountNumber)
{
	stClient Client;
	Client.AccountNumber = AccountNumber;

	cout << "Enter PinCode ? ";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name ? ";
	getline(cin, Client.Name);
	cout << "Enter Phone ? ";
	getline(cin, Client.Phone);
	cout << "Enter Account Balance ? ";
	cin >> Client.AccountBalance;
	return Client;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{
	stClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintOneClinet(Client);
		cout << "\n\nAre you sure you want Update client ? n/y ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			for (stClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}
			SaveClientsDataToFile(ClientsFileName, vClients);
			// Refresh Clients
			vClients = LoadClientsDataFromFile(ClientsFileName);
			cout << "\n\nClient Updated Successfully. \n";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is NOT Found!\n";
		return false;
	}
}

void Update_ClientInfo()
{
	system("cls");
	cout << "\n______________________________________\n\n";
	cout << setw(30) << "Update Client Screen" << endl;
	cout << "______________________________________" << endl;

	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);

}

bool FindClientByAccountNumber(string AccountNumber, stClient& Client)
{
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	for (stClient C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

void FindClientInfo()
{

	system("cls");
	cout << "\n______________________________________\n\n";
	cout << setw(30) << "Find Client Screen" << endl;
	cout << "______________________________________" << endl;


	stClient Client;
	string AccountNumber = ReadClientAccountNumber();
	if (FindClientByAccountNumber(AccountNumber, Client))
	{
		PrintOneClinet(Client);
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is NOT Found!\n";
	}

}

void Start()
{
	enChoices Choices;

	do {
		ShowMainMenueScreen();
		Choices = ReadChoice();

		switch (Choices)
		{
		case Show:
			system("cls");
			ShowClientList();
			break;

		case AddNew:
			system("cls");
			AddClients();
			break;

		case Delete:
			system("cls");
			DeleteClient();
			break;

		case UpDate:
			system("cls");
			Update_ClientInfo();
			break;

		case Find:
			system("cls");
			FindClientInfo();
			break;

		case Exit:
			break;
		}

		if (Choices != Exit) {
			cout << "\nPress any key to go back to Main Menue...";
			system("pause>0");
			system("cls");
		}

	} while (Choices != Exit);

	system("cls");
	cout << "\n______________________________________\n\n";
	cout << setw(30) << "Program ends :-)" << endl;
	cout << "______________________________________" << endl;

}

int main()
{
	Start();

	return 0;
}
