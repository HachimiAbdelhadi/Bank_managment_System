#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<iomanip>

using namespace std;


namespace bankProjectEXT
{
	struct stUserInfo {
		string userName;
		string userPassWord;
		int  permission = 0;
		bool markToDelet = false;
	};
	enum mainMenue
	{
		showClient = 1, addNewClient = 2, deleteClient = 3, upateClient = 4, 
		findClient = 5, transaction = 6, mangeUsers = 7, logOut = 8
	};
	enum mangUser { showUser = 1, addNewClientUser = 2, deleteUser = 3, upateUser = 4, 
		findUser = 5, actifUser = 6, mainMenu = 7 };
	enum enTransactionMenue { deposit = 1, withdraw = 2, totalBalanses = 3, MainMenueP = 4 };
	enum enMangUserPermission{eAllP=-1,eshowClientP=1,eAddNewClientP=2,eDeleteClientP=4,eUpateClientP=8,eFindClientP=16,
		eTransactionP=32,eMangeUsers=62,
	};
	struct stWithDrawPerson { string Id; string fullName; string adress; string phoneNumber; };
	struct stClientRecords
	{
		stWithDrawPerson withDrawPerson;
		string accountNumber;
		string codePin;
		string fullName;
		string phoneNumber;
		float accountBalance = 0;
		bool markForDelet = false;
	};

	const string fileName = "bankClientData.txt";
	const string usersFileName = "users.txt";
	const string delimiter = "#//#";
	stUserInfo currentUser;
	void accessDenied();
	void logInScreen();
	void mangMenu();
	void startBankProgram();
	void toTransationClientData();
	bool searchClientByAccountNumber(string accountNumber);
	bool clientExistsByAccountNumber(string accountNumber);
	bool withDrawPersonExistsByID(string ID);


	//access on system 
	bool checkAccessPermission(enMangUserPermission permission)
	{
		return ((currentUser.permission & permission) == permission) ? true : false;
	}
	
	
	
	//input fundition of program
	string readString(string message)
	{
		cout << message;
		string s1;
		/*cin.ignore(1, '\n');*/
		getline(cin, s1);
		return s1;
	}
	stClientRecords addNewClient3(string accountNumber = "", bool updateAcountNumber = true)
	{
		stWithDrawPerson C;
		stClientRecords clientInfo;
		if (updateAcountNumber == true)
		{
			cout << "Enter Account Number ? ";
			getline(cin, clientInfo.accountNumber);
			while (clientExistsByAccountNumber(clientInfo.accountNumber))
			{
				cout << "Client with [" << clientInfo.accountNumber << "] already exist,Enter Another Account Number :?" << endl;
				getline(cin, clientInfo.accountNumber);

			}
		}
		else
		{
			clientInfo.accountNumber = accountNumber;
		}
		cout << "Enter Code pin ? ";
		getline(cin, clientInfo.codePin);
		cout << "Enter Full Name ? ";
		getline(cin, clientInfo.fullName);
		cout << "Enter Your Phone Number ? ";
		getline(cin, clientInfo.phoneNumber);
		cout << "Enter your Account Balance ? ";
		cin >> clientInfo.accountBalance;
		cin.ignore(1, '\n');

		//Information About withdraw person

		cout << endl << "Enter person how can withDraw From your account :" << endl;

		/*if (updateAcountNumber == true)
		{*/
		cout << "enter his Id : ";
		getline(cin, clientInfo.withDrawPerson.Id);
		while (withDrawPersonExistsByID(clientInfo.withDrawPerson.Id))
		{
			cout << "this Id it's exist enter another Id : ";
			getline(cin, clientInfo.withDrawPerson.Id);
		}
		/*}*/
		cout << "enter his full name : ";
		getline(cin, clientInfo.withDrawPerson.fullName);
		cout << "enter his adress : ";
		getline(cin, clientInfo.withDrawPerson.adress);
		cout << "enter his Phone Number : ";
		getline(cin, clientInfo.withDrawPerson.phoneNumber);

		return clientInfo;
	}
	vector<string> splitString(string strOfrecords, string delimiter = "#//#")
	{
		vector<string> records;
		short pos;
		string clientInfo;
		while ((pos = strOfrecords.find(delimiter)) != std::string::npos)
		{
			clientInfo = strOfrecords.substr(0, pos);
			if (clientInfo != "")
			{
				records.push_back(clientInfo);
			}
			strOfrecords.erase(0, pos + delimiter.length());
		}
		if (strOfrecords != "")
		{
			records.push_back(strOfrecords);
		}
		return records;
	}
	stClientRecords convertLineOfClientDataToStruct(string stOfRecordClient, string delimiter = "#//#")
	{
		vector<string> records = splitString(stOfRecordClient);
		stClientRecords ClientRecord;
		if(records.size()!=0)
		{
			ClientRecord.accountNumber = records[0];
			ClientRecord.codePin = records[1];
			ClientRecord.fullName = records[2];
			ClientRecord.phoneNumber = records[3];
			ClientRecord.accountBalance = stof(records[4]);
			ClientRecord.withDrawPerson.Id = records[5];
			ClientRecord.withDrawPerson.fullName = records[6];
			ClientRecord.withDrawPerson.adress = records[7];
			ClientRecord.withDrawPerson.phoneNumber = records[8];

			return ClientRecord;
		}
	}
	string convertClientDataToLine(stClientRecords clientData, string delimiter = "#//#")
	{
		string lineOfClientData = "";
		lineOfClientData += clientData.accountNumber + delimiter;
		lineOfClientData += clientData.codePin + delimiter;
		lineOfClientData += clientData.fullName + delimiter;
		lineOfClientData += clientData.phoneNumber + delimiter;
		lineOfClientData += to_string(clientData.accountBalance) + delimiter;
		lineOfClientData += clientData.withDrawPerson.Id + delimiter;
		lineOfClientData += clientData.withDrawPerson.fullName + delimiter;
		lineOfClientData += clientData.withDrawPerson.adress + delimiter;
		lineOfClientData += clientData.withDrawPerson.phoneNumber;


		return lineOfClientData;
	}
	vector< stClientRecords> loadDataFromFileAsStuctToVector()
	{
		vector< stClientRecords> VofStClientRecords;
		string stOfRecordClient;
		fstream FClientData;
		FClientData.open(fileName, ios::in);
		if (FClientData.is_open())
		{
			while (getline(FClientData, stOfRecordClient))
			{
				VofStClientRecords.push_back(convertLineOfClientDataToStruct(stOfRecordClient));
			}
			FClientData.close();

		}
		return VofStClientRecords;
	}
	string tabs(short numtab)
	{
		string tab = "";
		for (short i = 1; i <= numtab; i++)
		{
			tab += "\t";
		}
		return tab;

	}
	void goBackToMainMenu()
	{
		/*cout << "Press any key to go back to main menue ...";*/
		system("pause");
		startBankProgram();

	}
	bool questions(string message)
	{
		char answer = 'y';
		cout << message;
		cin >> answer;
		cin.ignore(1, '\n');
		while (toupper(answer) != 'Y' && toupper(answer) != 'N')
		{
			cin.ignore(1, '\n');
			cout << "Invalid charaqter "+ message;
			cin >> answer;

		}

		return (toupper(answer) == 'Y')? true: false;

	}


	
	//search on client by account number

	//slow a littel sulotion to find clients 
	bool searchClientByAccountNumber(string accountNumber)
	{
		vector< stClientRecords> ClientRecords = loadDataFromFileAsStuctToVector();
		for (stClientRecords& stclient : ClientRecords)
		{
			if (stclient.accountNumber == accountNumber)
			{
				return true;
			}
		}
		return false;
	}
	bool findClientByAccountNumber(string accountNumber, stClientRecords& clientData)
	{
		vector< stClientRecords> ClientRecords = loadDataFromFileAsStuctToVector();
		for (stClientRecords& stclient : ClientRecords)
		{
			if (stclient.accountNumber == accountNumber)
			{
				clientData = stclient;
				return true;
			}
		}
		return false;
	}
	//fast sulotion to find clients 
	bool clientExistsByAccountNumber(string accountNumber)
	{
		string Line;
		stClientRecords stclient;
		fstream fClients;

		fClients.open(fileName, ios::in);
		if (fClients.is_open())
		{
			while (getline(fClients, Line))
			{
				stclient = convertLineOfClientDataToStruct(Line);
				if (stclient.accountNumber == accountNumber)
				{
					fClients.close();
					return true;
				}
			}
		}
		return false;

	}

	bool withDrawPersonExistsByID(string ID)
	{
		string Line;
		stClientRecords stclient;
		fstream fClients;

		fClients.open(fileName, ios::in);
		if (fClients.is_open())
		{
			while (getline(fClients, Line))
			{
				stclient = convertLineOfClientDataToStruct(Line);
				if ((stclient.withDrawPerson.Id == ID))
				{

					fClients.close();
					return true;
				}
			}
			fClients.close();

		}
		return false;

	}


	

	//SHOW CLIENT LIST [1]
	void printclientICard(stClientRecords Client)
	{
		cout << endl;
		cout << "_________________________________________________________________\n";
		cout << "| Account Number         :" << Client.accountNumber << endl;
		cout << "| Pin Code               :" << Client.codePin << endl;
		cout << "| Client Full Name       :" << Client.fullName << endl;
		cout << "| Client Phone Number    :" << Client.phoneNumber << endl;
		cout << "| Client Account Balance :" << Client.accountBalance << endl;
		cout << "_________________________________________________________________\n";

	}
	void printWithDrawPersonICard(stClientRecords personWithdraw)
	{
		cout << endl;
		cout << "_________________________________________________________________\n";
		cout << "| ID Number           :" << personWithdraw.withDrawPerson.Id << endl;
		cout << "| Person Full Name    :" << personWithdraw.withDrawPerson.fullName << endl;
		cout << "| Person Phone Number :" << personWithdraw.withDrawPerson.phoneNumber << endl;
		cout << "| ADRESS              :" << personWithdraw.withDrawPerson.adress << endl;
		cout << "_________________________________________________________________\n";
	}
	void printClientRecord(stClientRecords Client)
	{
		cout << " |" << left << setw(20) << Client.accountNumber;
		cout << " |" << left << setw(15) << Client.codePin;
		cout << " |" << left << setw(25) << Client.fullName;
		cout << " |" << left << setw(15) << Client.phoneNumber;
		cout << " |" << left << setw(15) << Client.accountBalance;
		/*cout << " |" << left << setw(15) << Client.withDrawPerson.Id;
		cout << " |" << left << setw(15) << Client.withDrawPerson.fullName;*/

		cout << endl;
	}
	void showClientList()
	{
		if (!checkAccessPermission(enMangUserPermission::eshowClientP))
		{
			system("cls");
			accessDenied();
		}
		vector< stClientRecords> clientStructures = loadDataFromFileAsStuctToVector();
		
		cout << endl;
		cout << "\n====================================================================================================\n";
		cout << tabs(5) << "Client List (" << clientStructures.size() << ") Client(s) \n";
		cout << "\n====================================================================================================\n";
		cout << " |" << left << setw(20) << "Account Number";
		cout << " |" << left << setw(15) << "Code Pin";
		cout << " |" << left << setw(25) << "Full Name";
		cout << " |" << left << setw(15) << "Phone Number";
		cout << " |" << left << setw(15) << "Account Balance";
		cout << endl;
		cout << "\n====================================================================================================\n";

		for (stClientRecords& Client : clientStructures)
		{
			printClientRecord(Client);
		}
		cout << "\n====================================================================================================\n";
		goBackToMainMenu();
	}


	//ADD NEW CLIENT [2]
	void addNewClientToFile(stClientRecords ClientRecords)
	{
		fstream FileClient;
		FileClient.open(fileName, ios::out | ios::app);
		if (FileClient.is_open())
		{
			FileClient << convertClientDataToLine(ClientRecords) << endl;
		}
		FileClient.close();
	}
	void AddingNewClient()
	{
		if (!checkAccessPermission(enMangUserPermission::eAddNewClientP))
		{
			system("cls");
			accessDenied();
		}
		stClientRecords ClientRecords;
		do
		{
			
			cout << "\n+++__________________________________________+++\n";
			cout << tabs(2) << "Add New Clients Screen\n";
			cout << "+++__________________________________________+++\n";
			cout << "Adding new client :" << endl;
			addNewClientToFile(addNewClient3("", true));

		} while (questions("Client Added Successfully. Do you want to add more client ? y/n :"));
		goBackToMainMenu();
	}


	//DELETE CLIENT RECORD [3]
	void saveClientDataToFileAfterDelete(vector< stClientRecords> ClientRecords)
	{
		fstream FClient;
		FClient.open(fileName, ios::out);
		if (FClient.is_open())
		{
			for (stClientRecords C : ClientRecords)
			{
				if (C.markForDelet == false)
				{
					FClient << convertClientDataToLine(C) << endl;
				}
			}
			FClient.close();
		}
	}
	void markForDeleteClient(vector< stClientRecords>& ClientRecords, stClientRecords clientData)
	{
		for (stClientRecords& stclient : ClientRecords)
		{
			if (stclient.accountNumber == clientData.accountNumber)
			{
				stclient.markForDelet = true;
			}
		}
	}
	void toDeleteClientRecords()
	{
		if (!checkAccessPermission(enMangUserPermission::eDeleteClientP))
		{
			system("cls");
			accessDenied();
		}
		vector< stClientRecords> ClientRecords;
		ClientRecords = loadDataFromFileAsStuctToVector();
		stClientRecords clientData;
		string accounNumber;
		do
		{
			
			cout << "+++=======================================================+++\n";
			cout << tabs(4) << "Delete Client Srcreen\n";
			cout << "+++=======================================================+++\n";
			cout << "please enter account numner ? ";
			getline(cin, accounNumber);
			if (findClientByAccountNumber(accounNumber, clientData))
			{
				printclientICard(clientData);
				if (questions("Are you sure you want to delete this client y/n :"))
				{
					markForDeleteClient(ClientRecords, clientData);
					saveClientDataToFileAfterDelete(ClientRecords);
					//to refrach info
					//ClientRecords = loadDataFromFileAsStuctToVector();
					cout << "Client Data Deleted succussfully..." << endl;
				}
				else
				{
					cout << "Client Data d'ont Deleted succussfully..." << endl;

				}

			}
			else
			{
				cout << "Client with Account Number (" << accounNumber << ") is not found !" << endl;
			}

		} while (questions("do you want to delete more client :"));
		goBackToMainMenu();
	}

	//UPDATE CLIENT INFORMATION [4]
	void UpdateClientRecord(vector< stClientRecords>& ClientRecords, stClientRecords clientData, bool updateAcountNumber = false)
	{
		for (stClientRecords& C : ClientRecords)
		{
			if (C.accountNumber == clientData.accountNumber)
			{
				C = addNewClient3(clientData.accountNumber, updateAcountNumber);
				break;
			}
		}
		saveClientDataToFileAfterDelete(ClientRecords);
	}
	void toUpdateClientRecord()
	{
		if (!checkAccessPermission(enMangUserPermission::eUpateClientP))
		{
			system("cls");
			accessDenied();
		}
		vector< stClientRecords> ClientRecords;
		ClientRecords = loadDataFromFileAsStuctToVector();
		stClientRecords clientData;
		string accounNumber;
		do {
			
			cout << "+++=======================================================+++\n";
			cout << tabs(4) << "Update Client Srcreen\n";
			cout << "+++=======================================================+++\n";
			cout << "please enter account numner ? ";
			getline(cin, accounNumber);
			if (findClientByAccountNumber(accounNumber, clientData))
			{
				printclientICard(clientData);
				if (questions("do you want to update this client y/n :"))
				{
					UpdateClientRecord(ClientRecords, clientData, questions("Do you want to Update Account Number ? "));

					cout << "Client Updated succussfully ..." << endl;
				}

			}
			else
			{
				cout << "Client with Account Number (" << accounNumber << ") is not found !" << endl;
			}
		} while (questions("Do you want to update more :"));
		goBackToMainMenu( );
	}


	//FIND CLIENT [5]
	void findClientInfo()
	{
		if (!checkAccessPermission(enMangUserPermission::eFindClientP))
		{
			system("cls");
			accessDenied();
		}
		string accounNumber;
		stClientRecords clientData;
		do
		{
			
			cout << "+++=======================================================+++\n";
			cout << tabs(3) << "Find Client Srcreen\n";
			cout << "+++=======================================================+++\n";
			cout << "please enter account number ? ";
			getline(cin, accounNumber);
			if (findClientByAccountNumber(accounNumber, clientData))
			{
				printclientICard(clientData);
			}
			else
			{
				cout << "Client with Account Number (" << accounNumber << ") is not found !" << endl;
			}
		} while (questions("do you want to search on more client ? "));
		goBackToMainMenu( );
	}

	//TRANSACION [6]
	bool checkAccountAmount(float userAmount, float depoAmount)
	{
		if (userAmount >= depoAmount)
			return true;
		else
			return false;
	}
	void goBacktoTransMenue()
	{
		cout << "Press any key to go back to main menue ...";
		system("pause>0");
		toTransationClientData();
	}
	void chooseAccount(string& accounNumber1, string& accounNumber2)
	{
		if (questions("you have account ?"))
		{
			cout << "please enter account numner that you want to access ? ";
			getline(cin, accounNumber1);
			cout << "please enter your account number ? ";
			getline(cin, accounNumber2);
		}
		else
		{
			cout << "please enter account numner that you want to access ? ";
			getline(cin, accounNumber1);
		}
	}

	//ACCESS ON ACCOUNTS 
	void accessFromAccountToAnother(float amount, stClientRecords clientData1, stClientRecords clientData2)
	{
		vector< stClientRecords> ClientRecords = loadDataFromFileAsStuctToVector();
		for (stClientRecords& C : ClientRecords)
		{
			if (C.accountNumber == clientData1.accountNumber)
			{
				C.accountBalance += amount;
				cout << "\nDone successfully ...New Account Balance of (" << C.accountNumber << ") :" << C.accountBalance << endl;

			}
			else if (C.accountNumber == clientData2.accountNumber)
			{
				C.accountBalance -= amount;
				cout << "\nDone successfully ...New Account Balance of (" << C.accountNumber << ") :" << C.accountBalance << endl;


			}
		}
		saveClientDataToFileAfterDelete(ClientRecords);

	}
	void accessToOneAccount(float amount, stClientRecords clientData1)
	{
		vector< stClientRecords> ClientRecords = loadDataFromFileAsStuctToVector();
		for (stClientRecords& clientAccount : ClientRecords)
		{
			if (clientAccount.accountNumber == clientData1.accountNumber)
			{
				clientAccount.accountBalance += amount;
				cout << "\nDone successfully ...New Account Balance of (" << clientAccount.accountNumber << ") :" << clientAccount.accountBalance << endl;

			}
		}
		saveClientDataToFileAfterDelete(ClientRecords);
	}


	//TRANSACTION DEPOSITE [1]
	void todeposite()
	{
		string accounNumber1 = "", accounNumber2 = "";
		stClientRecords clientData1, clientData2;
		float depo = 0;

		cout << "=======================================================\n";
		cout << tabs(3) << "Deposite Srcreen\n";
		cout << "=======================================================\n";
		chooseAccount(accounNumber1, accounNumber2);
		if (accounNumber2 != "")
		{
			if (accounNumber1 != accounNumber2)
			{
				if (findClientByAccountNumber(accounNumber1, clientData1) && findClientByAccountNumber(accounNumber2, clientData2))
				{

					printclientICard(clientData1);
					printclientICard(clientData2);
					cout << "please enter deposit amount : ";
					cin >> depo;
					if (checkAccountAmount(clientData2.accountBalance, depo))
					{
						accessFromAccountToAnother(depo, clientData1, clientData2);
						cout << "transaction deposite successfully..." << endl;
					}
					else
					{
						cout << "You d'ont have enough meny -( " << endl;
					}


				}
				else
				{
					cout << "Account(s) Number is not found !" << endl;
				}
			}
			else
			{
				cout << endl << "Possiable Transaction... " << endl;
			}
		}
		else
		{
			if (findClientByAccountNumber(accounNumber1, clientData1))
			{
				printclientICard(clientData1);
				cout << "please enter deposit amount : ";
				cin >> depo;
				accessToOneAccount(depo, clientData1);
				cout << "transaction deposite successfully..." << endl;
			}
			else
			{
				cout << "Account(s)  Number is not found !" << endl;
			}
		}

	}


	//TRANSACTION WithDraw [2]	
	void toWithDraw()
	{
		string accounNumber1 = "", accounNumber2 = "", ID;
		stClientRecords clientData1, clientData2;
		float withDraw = 0;

		cout << "=======================================================\n";
		cout << tabs(3) << "WithDraw Srcreen\n";
		cout << "=======================================================\n";
		chooseAccount(accounNumber1, accounNumber2);
		if (accounNumber2 != "")
		{
			if (accounNumber1 != accounNumber2)
			{
				if (findClientByAccountNumber(accounNumber1, clientData1) && findClientByAccountNumber(accounNumber2, clientData2))
				{
					printclientICard(clientData1);
					printclientICard(clientData2);
					cout << "please enter withDraw amount : ";
					cin >> withDraw;
					if (checkAccountAmount(clientData1.accountBalance, withDraw))
					{
						accessFromAccountToAnother((withDraw) * (-1), clientData1, clientData2);
						cout << "transaction withDraw successfully..." << endl;
					}
					else
					{
						cout << "He d'ont have enough meny -( " << endl;
					}
				}
				else
				{
					cout << "Account Number(s) is not found !" << endl;
				}
			}
			else
			{
				cout << endl << "Possiable Transaction... " << endl;
			}
		}
		else
		{
			if (findClientByAccountNumber(accounNumber1, clientData1))
			{
				cout << "please enter your ID : ";
				getline(cin, ID);
				if (withDrawPersonExistsByID(ID))
				{
					printclientICard(clientData1);
					cout << "please enter withDraw amount : ";
					cin >> withDraw;
					if (checkAccountAmount(clientData1.accountBalance, withDraw))
					{
						accessToOneAccount(withDraw * (-1), clientData1);
						cout << "transaction withDraw successfully..." << endl;
						if (questions("Do you want to know how withdraw from you account : "))
						{
							printWithDrawPersonICard(clientData1);
						}
					}
					else
					{
						cout << "He d'ont have enough meny -( " << endl;
					}
				}
				else
				{
					cout << "you d'ont have permision to WITHDRAW on this Account -(";
				}
			}
			else
			{
				cout << "Account Number(s) is not found !" << endl;
			}
		}
	}



	//TOTAL BALANCE [3]
	void printClientBalance(stClientRecords clientRecords)
	{
		cout << "| " << left << setw(20) << clientRecords.accountNumber;
		cout << "| " << left << setw(35) << clientRecords.fullName;
		cout << "| " << left << setw(35) << clientRecords.accountBalance;
		cout << endl;
	}
	void showTotalBalanceList()
	{
		float totalBalance = 0;
		vector<stClientRecords>VclientData = loadDataFromFileAsStuctToVector();
		cout << tabs(5) << "Balance Client List (" << VclientData.size() << ") Client(s)." << endl;
		cout << endl;
		cout << "____________________________________________________________________________________________\n";
		cout << "| " << left << setw(20) << "Account Number";
		cout << "| " << left << setw(35) << "Full Name";
		cout << "| " << left << setw(35) << "Account Balance";
		cout << "\n___________________________________________________________________________________________\n";

		cout << endl;
		if (VclientData.size() == 0)
		{
			cout << tabs(5) << "No Clients avelibale in the System !" << endl;
		}
		{
			for (stClientRecords& accountClient : VclientData)
			{
				printClientBalance(accountClient);
				totalBalance += accountClient.accountBalance;
			}
		}
		cout << endl << tabs(6) << "| Total Balance : " << totalBalance << endl << endl;

	}
	void showTranactionScreen()
	{

		cout << "+++=======================================================+++\n";
		cout << tabs(3) << "Transaction Srcreen\n";
		cout << "+++=======================================================+++\n";
		cout << tabs(1) << " [1]Deposite ." << endl;
		cout << tabs(1) << " [2]Withdraw ." << endl;
		cout << tabs(1) << " [3]Total Balance ." << endl;
		cout << tabs(1) << " [4]Main Menue ." << endl;
		cout << "==================================================================\n";
	}

	//start transaction
	void toTransationClientData()
	{
		if (!checkAccessPermission(enMangUserPermission::eTransactionP))
		{
			system("cls");
			accessDenied();
		}
		system("cls");
		cout << "User Actif : " << currentUser.userName << endl;
		showTranactionScreen();
		short chooseNumber;
		cout << "choose wath do you want to do ?[1 to 4] ?";
		cin >> chooseNumber;
		cin.ignore(1, '\n');
		switch (chooseNumber)
		{
		case enTransactionMenue::deposit:
		{
			system("cls");
			cout << "User Actif : " << currentUser.userName << endl;
			todeposite();
			goBacktoTransMenue();

		}
		case enTransactionMenue::withdraw:
		{
			system("cls");
			cout << "User Actif : " << currentUser.userName << endl;
			toWithDraw();
			goBacktoTransMenue();
		}
		case enTransactionMenue::totalBalanses:
		{
			system("cls");
			cout << "User Actif : " << currentUser.userName << endl;
			showTotalBalanceList();
			goBacktoTransMenue();

		}
		case enTransactionMenue::MainMenueP:
		{
			startBankProgram();
		}
		default:
			startBankProgram();
			break;
		}
	}



	//MANGE USERS [7]
	//fundetion Part Users
	void goBackToMangMenu()
	{
		/*cout << "Press any key to go back to main menue ...";*/
		system("pause");
		mangMenu( );

	}
	stUserInfo converLineOfUserInfoToStruct(string stuserInform, string delimiter = "#//#")
	{
		vector< string> vUserInfo = splitString(stuserInform, delimiter);
		stUserInfo user;
		if(vUserInfo.size()!=0)
		{
			user.userName = vUserInfo[0];
			user.userPassWord = vUserInfo[1];
			user.permission = stoi(vUserInfo[2]);
			return user;
		}
		
	}
	string converStOfUserInfoToLineString(stUserInfo UserInfo, string delimiter = "#//#")
	{
		string userRecord="";
		userRecord = UserInfo.userName + delimiter;
		userRecord += UserInfo.userPassWord + delimiter;
		userRecord += to_string(UserInfo.permission);

		return userRecord;
	}
	vector< stUserInfo> loadUserInfoFromFile()
	{
		vector< stUserInfo> Stusers;
		string Line;
		fstream userrecord;
		userrecord.open(usersFileName, ios::in);
		if (userrecord.is_open())
		{
			while (getline(userrecord, Line))
			{
				Stusers.push_back(converLineOfUserInfoToStruct(Line));
			}
			userrecord.close();
		}
		return Stusers;
	}
	bool userExistsByUserName(stUserInfo UserInfo)
	{
		string Line;
		stUserInfo stUser;
		fstream fUser;

		fUser.open(usersFileName, ios::in);
		if (fUser.is_open())
		{
			while (getline(fUser, Line))
			{
				stUser = converLineOfUserInfoToStruct(Line);
				if ((stUser.userName == UserInfo.userName) && (stUser.userPassWord == UserInfo.userPassWord))
				{
					fUser.close();
					return true;
				}
			}
		}
		return false;

	}
	stUserInfo validationUser(bool valPassWord=true)
	{
		stUserInfo user;
		cout << "Enter a user name? : ";
		getline(cin >> ws, user.userName);
		if(valPassWord = true){
			cout << "Enter a userName? : ";
			getline(cin >> ws, user.userPassWord);
		}
		while (!userExistsByUserName(user))
		{
			cout << "Invalide Username/Password " << endl;;
			cout << "Enter a user name : ";
			getline(cin >> ws, user.userName);
			if (valPassWord = true) {
				cout << "Enter a userName? : ";
				getline(cin >> ws, user.userPassWord);
			}
		}
		return user;
	}
	stUserInfo findUserByNamePassword(bool valPassWord = true)
	{
		stUserInfo User = validationUser(valPassWord);
		vector< stUserInfo> Stusers = loadUserInfoFromFile();
		for (stUserInfo& st : Stusers)
		{
			if ((st.userName == User.userName) && (st.userPassWord == User.userPassWord))
			{
				
				return st;
			}
		}
	}
	// SHOW USEER LIST [1]
	void printUserRecord(stUserInfo UserInfo)
	{
		cout << endl;
		cout << "_________________________________________________________________\n";
		cout << "| User Name         :" << UserInfo.userName << endl;
		cout << "| User Password     :" << UserInfo.userPassWord << endl;
		cout << "| User Permission   :" << UserInfo.permission << endl;
		cout << "_________________________________________________________________\n";
	}
	void printUser(stUserInfo UserInfo)
	{
		cout << " |" << left << setw(20) << UserInfo.userName 
			 << " |" << left << setw(15) << UserInfo.userPassWord
			 << " |" << left << setw(20) << UserInfo.permission << endl;
	}
	void toshowUserList()
	{
		

		vector< stUserInfo> Stusers  = loadUserInfoFromFile();
		cout << endl;
		cout << "\n====================================================================================================\n";
		cout << tabs(5) << "User List (" << Stusers.size() << ") User(s) \n";
		cout << "\n====================================================================================================\n";
		cout << " |" << left << setw(20) << "User Name";
		cout << " |" << left << setw(15) << "User Password";
		cout << " |" << left << setw(20) << "Permission";
		cout << endl;
		cout << "====================================================================================================\n";
		if (Stusers.size() == 0)
		{
			cout << tabs(5) << "No Users Avaliable In THis System";
		}
		else
		{
			for (stUserInfo& st : Stusers)
			{
				printUser(st);
			}
		}
		cout << "====================================================================================================\n";
		goBackToMangMenu( );
	}
	

	//ADD NEW USER[2]
	
	short GivePermissions()
	{
		short permission = 0;
		if (!questions("Do you want to give full access Y/N ?"))
		{
			cout << "Do you Want To give access To :" << endl;
			questions("Show Client List Y/N ?") ? permission +=enMangUserPermission::eshowClientP   : permission | 0;
			questions("Add New Client  Y/N ?") ?  permission +=enMangUserPermission::eAddNewClientP : permission | 0;
			questions("Delete Client  Y/N ?") ?   permission +=enMangUserPermission::eDeleteClientP : permission | 0;
			questions("Update Client  Y/N ?") ?   permission +=enMangUserPermission::eUpateClientP  : permission | 0;
			questions("Find Client  Y/N ?") ?     permission +=enMangUserPermission::eFindClientP   : permission | 0;
			questions("Transaction  Y/N ?") ?     permission +=enMangUserPermission::eTransactionP  : permission | 0;
			questions("Mange Users  Y/N ?") ?     permission +=enMangUserPermission::eMangeUsers    : permission | 0;
		}
		else
			permission = enMangUserPermission::eAllP;

		return permission;
	}
	stUserInfo addNewUser(string userName, bool updateUserName = true)
	{
		stUserInfo user;
		if (updateUserName == true)
		{
			cout << "Enter a user name? : ";
			getline(cin >> ws, user.userName);
		}
		else
		{
			user.userName = userName;
		}
		while (userExistsByUserName(user))
		{
			cout << "Invalide Username/Password " << endl;;
			cout << "User with [" << user.userName << "] already exist Enter another user name : ";
			getline(cin >> ws, user.userName);
		}
		cout << "Enter a userName? : ";
		getline(cin >> ws, user.userPassWord);

		user.permission = GivePermissions();
		return user;
	}
	void addNewUserToFile(stUserInfo  UserInfo)
	{
		fstream userFile;
		userFile.open(usersFileName, ios::out | ios::app);
		if (userFile.is_open())
		{
			userFile << converStOfUserInfoToLineString(UserInfo) ;
			userFile << endl;
			userFile.close();
		}

	}
	void toAddNewUser()
	{

		do
		{
			system("cls");
			cout << "User Actif : " << currentUser.userName << endl;
			cout << "\n================================================================\n";
			cout << tabs(5) << "Add New User screen \n";
			cout << "\n================================================================\n";
			stUserInfo UserInfo;
			UserInfo = addNewUser("");
			addNewUserToFile(UserInfo);
		} while (questions("User Adding Successfully ,Do You Want To Add More User Y/N?"));
		goBackToMangMenu( );

	}


	//DELETE USER [3]

	void markForDeleteUser(vector<stUserInfo> &VStuser,stUserInfo stUser)
	{
		for (stUserInfo& C : VStuser)
		{
			if (C.userName == stUser.userName && C.userPassWord == stUser.userPassWord)
			{
				C.markToDelet = true;
				break;
			}
		}
	}

	void saveVectorAfterEditing(vector<stUserInfo> VStuser)
	{
		string line;
		fstream userFile;
		userFile.open(usersFileName, ios::out);
		if (userFile.is_open())
		{   for(stUserInfo &C:VStuser)
			{
				if(C.markToDelet==false)
				{
	
					userFile << converStOfUserInfoToLineString(C) << endl;
				}
			}
		   
		userFile.close();
		}
	}

	void toDeleteUser()
	{
		do
		{
			system("cls");
			cout << "User Actif : " << currentUser.userName << endl;
			vector<stUserInfo> VStuser = loadUserInfoFromFile();

			cout << "\n================================================================\n";
			cout << tabs(5) << "Delete User screen \n";
			cout << "\n================================================================\n";
			stUserInfo userToDelet = findUserByNamePassword(false);
			if (userToDelet.userName == "Admin" && userToDelet.userPassWord == "1234")
			{
				cout << "You Cannot Delete This User ";
				goBackToMangMenu();
				
			}
			else
			{
				if (questions("Are you sure Do you want to delete this user ?Y/N? "))
				{
					printUserRecord(userToDelet);
					markForDeleteUser(VStuser, userToDelet);
					saveVectorAfterEditing(VStuser);
				}
			}

		} while (questions("DO you want to delete more user Y/N ?"));
		goBackToMangMenu( );

	}


	//UPDATE USER [4]

	void UpdateUser(vector<stUserInfo> &VStuser, stUserInfo user)
	{
		for (stUserInfo& C : VStuser)
		{
			if (C.userPassWord == user.userPassWord)
			{
				C = addNewUser(user.userName,false);
				addNewUserToFile(C);
				break;
			}
		}
	}
	void toUpdateUser()
	{
		do
		{
			system("cls");
			cout << "User Actif : " << currentUser.userName << endl;
			vector<stUserInfo> VStuser = loadUserInfoFromFile();

			cout << "\n===============================================================\2\n";
			cout << tabs(5) << "Update User screen \n";
			cout << "\n================================================================\n";
			stUserInfo user = findUserByNamePassword(false);
			if (questions("Are you sure Do you want to Update this user ?Y/N? "))
			{
				printUserRecord(user);
				UpdateUser(VStuser, user);
				saveVectorAfterEditing(VStuser);
			}

		} while (questions("DO you want to Update more user Y/N ?"));
		goBackToMangMenu( );

	}

	//FIND USEER [5]
	void toFindUser()
	{
		do
		{
			system("cls");
			cout << "User Actif : " << currentUser.userName << endl;
			vector<stUserInfo> VStuser = loadUserInfoFromFile();

			cout << "\n================================================================\n";
			cout << tabs(5) << "Find User screen \n";
			cout << "\n================================================================\n";
			
			if (questions("Do you want to Search About user ?Y/N? "))
			{
				stUserInfo user = validationUser(false);
				for(stUserInfo &C: VStuser)
				{
					if(C.userName==user.userName&& C.userPassWord == user.userPassWord)
					{
						printUserRecord(C);
						break;
					}
				}
			
			}

		} while (questions("DO you want to Find more user Y/N ?"));
		goBackToMangMenu( );

	}
	// Actif User [6]
	void toActifUser(stUserInfo user)
	{ 
		
		cout << "Active User \7\6";
		printUserRecord(user);
		goBackToMangMenu();

	}



	// MAIN MENU[7]
	void toMainMenu()
	{
		startBankProgram();
	}


	//MANGE USER 
	void mangeUserScreen()
	{
		
		cout << "==================================================================\n";
		cout << tabs(3) << "Main Menue Screen\n";
		cout << "==================================================================\n";
		cout << tabs(1) << " [1]Show Users List ." << endl;
		cout << tabs(1) << " [2]Add New User ." << endl;
		cout << tabs(1) << " [3]Delete User ." << endl;
		cout << tabs(1) << " [4]Update User Info ." << endl;
		cout << tabs(1) << " [5]Find User ." << endl;
		cout << tabs(1) << " [6]Actif User ." << endl;
		cout << tabs(1) << " [7]Main Menu  ." << endl;
		cout << "==================================================================\n";

	}

	void mangMenu()
	{
		if (!checkAccessPermission(enMangUserPermission::eMangeUsers))
		{
			system("cls");
			accessDenied();
		}
		system("cls");
		cout << "User Actif : " << currentUser.userName << endl;
		mangeUserScreen();
		short answe;
		cout << "Choose wath do you want to do [1-7]";
		cin >> answe;
		switch (answe)
		{
		case mangUser::showUser:
		{
			system("cls");
			cout << "User Actif : " << currentUser.userName << endl;
			toshowUserList();
		}
		case mangUser::addNewClientUser:
		{
			system("cls");
			cout << "User Actif : " << currentUser.userName << endl;
			toAddNewUser();
		}
		case mangUser::deleteUser:
		{
			system("cls");
			cout << "User Actif : " << currentUser.userName << endl;
			toDeleteUser();
		}
		case mangUser::upateUser:
		{
			system("cls");
			cout << "User Actif : " << currentUser.userName << endl;
			toUpdateUser();
		}
		case mangUser::findUser:
		{
			system("cls");
			cout << "User Actif : " << currentUser.userName << endl;
			toFindUser();
		}
		case mangUser::actifUser:
		{
			system("cls");
			cout << "User Actif : " << currentUser.userName << endl;
			toActifUser(currentUser);
		}
		case mangUser::mainMenu:
		{
			system("cls");
			cout << "User Actif : " << currentUser.userName << endl;
			toMainMenu( );
		}
		default:
			break;
		}
	}


	// Access Denied 
	void accessDenied()
	{
		
		cout << "________________________________________________________________\n";
		cout << "Access Denied \2 \3 \4" << endl;
		cout << "You D'ont Have Permission To Do This,\nplease Contact Your Adimin\n";
		cout << "________________________________________________________________\n";
		goBackToMainMenu();
	}


	



	//EXIT PROGRAM

	void programEnd()
	{
		system("cls");
		cout << "==================================================================\n";
		cout << tabs(3) << "THANK YOU...PROGRAMME BANK END\n";
		cout << "==================================================================\n";
		system("pause>0");
		logInScreen();
	}

	//MAIN MENUE SCREEN
	void mainMenueScreen()
	{
		
		cout << "==================================================================\n";
		cout << tabs(3) << "Main Menue Screen\n";
		cout << "==================================================================\n";
		cout << tabs(1) << " [1]Show Client List ." << endl;
		cout << tabs(1) << " [2]Add New Client ." << endl;
		cout << tabs(1) << " [3]Delete Client ." << endl;
		cout << tabs(1) << " [4]Update Client Info ." << endl;
		cout << tabs(1) << " [5]Find Client ." << endl;
		cout << tabs(1) << " [6]Transaction ." << endl;
		cout << tabs(1) << " [7]Mange User  ." << endl;
		cout << tabs(1) << " [8]LogOut ." << endl;
		cout << "==================================================================\n";


	}
	
	
	//start program
	void startBankProgram()
	{
		system("cls");	
		cout << "User Actif : " << currentUser.userName << endl;
		mainMenueScreen();

		short chooseNumber;
		cout << "choose what do you want to do ?[1 to 8] ?";
		cin >> chooseNumber;
		cin.ignore(1, '\n');

		switch (chooseNumber)
		{
		case (mainMenue::showClient):
		{
				system("cls");
				cout << "User Actif : " << currentUser.userName << endl;
				showClientList();
			
			break;
		}
		case (mainMenue::addNewClient):
		{
				system("cls");
				cout << "User Actif : " << currentUser.userName << endl;
				AddingNewClient();
			
			break;

		}
		case (mainMenue::deleteClient):
		{

				system("cls");
				cout << "User Actif : " << currentUser.userName << endl;
				toDeleteClientRecords();
		
			break;

		}
		case (mainMenue::upateClient):
		{

				system("cls");
				cout << "User Actif : " << currentUser.userName << endl;
				toUpdateClientRecord( );
			
			break;

		}
		case (mainMenue::findClient):
		{
				system("cls");
				cout << "User Actif : " << currentUser.userName << endl;
				findClientInfo( );
			
			break;

		}
		case mainMenue::transaction:
		{
				system("cls");
				cout << "User Actif : " << currentUser.userName << endl;
				toTransationClientData( );		
			
			break;
		}
		case mainMenue::mangeUsers:
		{

				system("cls");
				cout << "User Actif : " << currentUser.userName << endl;
				mangMenu( );
		}
		case (mainMenue::logOut):
		{
			logInScreen();
			break;

		}
		default:
		{
		    logInScreen();
			break;
		}

		}

	
			
	}

	 
	//logIN
	void logInScreen()
	{
		system("cls");
		cout << "==================================================================\n";
		cout << tabs(3) << "WELLCOM To PROGRAMME BANK\n";
		cout << "==================================================================\n";
		if (questions("Do you want to LogIn ?Y/N ? :"))
		{
			system("cls");
			cout << "==================================================================\n";
			cout << tabs(3) << "Login Screen\n";
			cout << "==================================================================\n";

			currentUser = findUserByNamePassword();

			startBankProgram();
		}
		else
		{
			programEnd();
		}

	}

}





























