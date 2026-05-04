#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <array>
#include <fstream>

using namespace std;
const string ClientsFileName = "Bank_Client.txt";

enum enMainMenueOptions { ShowClientList = 1, AddClient = 2, DeleteClient = 3, UpdateClientInfo = 4, FindClient = 5, Exit = 6 };

struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

void ShowMainMenue();

vector<string> SplitString(string Text, string separator)
{
	vector <string> vWord;
	short Position = 0;
	string sWord;
	while ((Position = Text.find(separator)) != std::string::npos)
	{
		sWord = Text.substr(0, Position);
		if (sWord != "")
		{
			vWord.push_back(sWord);

		}
		Text.erase(0, Position + separator.length());
	}
	if (Text != "")
	{
		vWord.push_back(Text);
	}
	return vWord;
}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
	sClient Client;
	vector<string> vClientData;
	vClientData = SplitString(Line, Seperator);

	if (vClientData.size() >= 5)
	{
		Client.AccountNumber = vClientData[0];
		Client.PinCode = vClientData[1];
		Client.Name = vClientData[2];
		Client.Phone = vClientData[3];
		Client.AccountBalance = stod(vClientData[4]);
	}
	return Client;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		sClient Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return false;
}

sClient ReadNewClient()
{
	sClient Client;
	cout << "Enter Account Number? ";

	getline(cin >> ws, Client.AccountNumber);

	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
	{
		cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
		getline(cin >> ws, Client.AccountNumber);
	}

	cout << "Enter PinCode? ";
	getline(cin, Client.PinCode);

	cout << "Enter Name? ";
	getline(cin, Client.Name);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;

	return Client;
}

vector <sClient> LoadCleintsDataFromFile(string FileName)
{
	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		sClient Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}

void PrintClientRecord(sClient Client)
{
	cout << "\n\nThe following is the extracted client record:\n";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code : " << Client.PinCode;
	cout << "\nName : " << Client.Name;
	cout << "\nPhone : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
}

void PrintClientCard(sClient Client)
{
	cout << "\n__________________________________________";
	cout << "\n\tClient Details Card";
	cout << "\n__________________________________________";
	cout << "\nAccout Number  : " << Client.AccountNumber;
	cout << "\nPin Code       : " << Client.PinCode;
	cout << "\nName           : " << Client.Name;
	cout << "\nPhone          : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
	cout << "\n__________________________________________\n";
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open())
	{
		MyFile << stDataLine << endl;
	}
	MyFile.close();
}

void AddNewClient()
{
	sClient Client = ReadNewClient();
	AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddNewClientsScreen()
{
	char AddClient = 'y';
	do
	{
		system("cls");
		cout << "-------------------------------------------" << endl;
		cout << "\tAdd New Clients Screen" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "Adding New Client:\n\n";

		AddNewClient();
		cout << "\nClient Added Successfully, do you want to add more clients ? Y/N ? ";
		cin >> AddClient;

	} while (tolower(AddClient) == 'y');
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenue();
}

vector<sClient> ReadAllLineFromFile()
{
	fstream MyFile;
	vector <sClient> vLine;
	MyFile.open(ClientsFileName, ios::in);
	if (MyFile.is_open())
	{
		sClient Client;
		string Line;
		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);
			vLine.push_back(Client);
		}
		MyFile.close();
	}
	return vLine;
}

void PrintAllClientsData(vector<sClient> vLines)
{
	cout << "\n\t\t\t\t\tClient List (" << vLines.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	for (sClient& Client : vLines)
	{
		cout << "| " << left << setw(15) << Client.AccountNumber;
		cout << "| " << left << setw(10) << Client.PinCode;
		cout << "| " << left << setw(40) << Client.Name;
		cout << "| " << left << setw(12) << Client.Phone;
		cout << "| " << left << setw(12) << Client.AccountBalance;
		cout << endl;
	}
	cout << "_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

void PrintAllClientsScreen()
{
	system("cls");
	vector <sClient> vLines = ReadAllLineFromFile();
	PrintAllClientsData(vLines);

	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenue();
}

string ReadAccountNumber()
{
	string AccountNumber;
	cout << "Enter the Client AccountNumber?: ";
	cin >> AccountNumber;
	return AccountNumber;
}

bool FindClientAccountNumber(string AccountNumber, vector<sClient> vClient, sClient& Client)
{
	for (sClient& C : vClient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

void FindClientScreen()
{
	system("cls");
	cout << "-------------------------------------------" << endl;
	cout << "\tFind Clients Screen" << endl;
	cout << "-------------------------------------------\n\n" << endl;
	string AccountNumber = ReadAccountNumber();
	vector <sClient> vClient = ReadAllLineFromFile();
	sClient Clinet;
	FindClientAccountNumber(AccountNumber, vClient, Clinet);
	PrintClientCard(Clinet);
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenue();
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClient)
{
	for (sClient& C : vClient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

vector <sClient> SaveCleintsDataToFile(string FileName, vector<sClient> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	string DataLine;
	if (MyFile.is_open())
	{
		for (sClient C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';
	if (FindClientAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveCleintsDataToFile(ClientsFileName, vClients);
			vClients = ReadAllLineFromFile();
			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}
}

void DeleteClientScreen()
{
	cout << "-------------------------------------------" << endl;
	cout << "\tDelete Client Screen" << endl;
	cout << "-------------------------------------------" << endl;

	vector <sClient> vClients = ReadAllLineFromFile();
	string AccountNumber = ReadAccountNumber();

	if (DeleteClientByAccountNumber(AccountNumber, vClients))
	{
		cout << "\nThe client has been successfully deleted\n";
	}

	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenue();
}

sClient ChangeClientRecord(string AccountNumber)
{
	sClient Client;
	Client.AccountNumber = AccountNumber;
	cout << "Enter PinCode? ";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	return Client;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
	sClient Clinent;
	char Answer = 'n';
	if (FindClientAccountNumber(AccountNumber, vClients, Clinent))
	{
		PrintClientCard(Clinent);
		cout << "\n\nAre you sure you want update this client? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			for (sClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}
			SaveCleintsDataToFile(ClientsFileName, vClients);
			cout << "\n\nClient Updated Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}
}

void UpdateClientScreen()
{
	cout << "-------------------------------------------" << endl;
	cout << "\tUpdate Client Info Screen" << endl;
	cout << "-------------------------------------------" << endl;

	vector <sClient> Clin = ReadAllLineFromFile();
	UpdateClientByAccountNumber(ReadAccountNumber(), Clin);

	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenue();
}

void PerformMainMenueOption(enMainMenueOptions Choice)
{
	switch (Choice)
	{
	case enMainMenueOptions::ShowClientList:
		PrintAllClientsScreen();
		break;
	case enMainMenueOptions::AddClient:
		AddNewClientsScreen();
		break;
	case enMainMenueOptions::DeleteClient:
		DeleteClientScreen();
		break;
	case enMainMenueOptions::UpdateClientInfo:
		UpdateClientScreen();
		break;
	case enMainMenueOptions::FindClient:
		FindClientScreen();
		break;
	case enMainMenueOptions::Exit:
		exit(0);
	}
}

short ReadMainMenueOption()
{
	cout << "Choose what do you want to do? [1 to 6]? ";
	short Choice = 0;
	cin >> Choice;

	while (Choice < 1 || Choice > 6)
	{
		cout << "Invalid Choice, enter a number between 1 and 6: ";
		cin >> Choice;
	}
	return Choice;
}

void ShowMainMenue()
{
	system("cls");
	cout << "==================================================" << endl;
	cout << "\t\tMain Menue Screen" << endl;
	cout << "==================================================" << endl;
	cout << "\t[1] Show Client List." << endl;
	cout << "\t[2] Add New Client." << endl;
	cout << "\t[3] Delete Client." << endl;
	cout << "\t[4] Update Client Info." << endl;
	cout << "\t[5] Find Client." << endl;
	cout << "\t[6] Exit." << endl;
	cout << "==================================================" << endl;

	PerformMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}

int main()
{
	ShowMainMenue();
	system("pause>0");
	return 0;
}