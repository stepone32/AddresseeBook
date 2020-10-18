#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <algorithm>

using namespace std;


struct AdressData
{
    int     idOfAdressee;
    int     idOfUser;
    string  surname;
    string  name;
    string  phoneNumber;
    string  address;
    string  email;
};

struct User
{
    int id;
    string userName, password;
};

char loadSign()
{
    string inputText = "";
    char sign  = {0};

    while (true)
    {
        getline(cin, inputText);

        if (inputText.length() == 1)
        {
            sign = inputText[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }
    return sign;
}

string loadLineOfText()
{
    string inputText = "";
    getline(cin, inputText);
    return inputText;
}

int loadIntegerNumber()
{
    string inputText = "";
    int number = 0;

    while (true)
    {
        getline(cin, inputText);

        stringstream myStream(inputText);
        if (myStream >> number)
            break;
        cout << "To nie jest liczba. Wpisz ponownie. " << endl;
    }
    return number;
}

int rejestracja(vector<User> &users,int usersCount)
{
    User user;
    string userName, password;
    cout << "Podaj nazwe uzytkownika: ";
    userName=loadLineOfText();

        if(users.empty())
       {
            cout << "Podaj haslo: ";
            password=loadLineOfText();
            user.userName=userName;
            user.password=password;
            user.id=usersCount+1;
            users.push_back(user);
            cout << "Konto zalozone." << endl;
            Sleep(1000);
       }
       else if(!users.empty())
       {

        for(vector<User>::iterator itr = users.begin(), endVectorWord=users.end(); itr!=endVectorWord; itr++)
        {

            if(itr->userName == userName)
            {
                cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
                userName=loadLineOfText();
            }
        }
            cout << "Podaj haslo: ";
            password=loadLineOfText();
            user.userName=userName;
            user.password=password;
            user.id=usersCount+1;
            users.push_back(user);
            cout << "Konto zalozone." << endl;
            Sleep(1000);
       }

    return usersCount+1;
}

int logowanie(vector<User> users)
{
    User userLog;
    string userName, password;
    cout << "Podaj nazwe uzytkownika: ";
    userName=loadLineOfText();

    for(vector<User>::iterator itr = users.begin(), endVectorWord=users.end(); itr!=endVectorWord; itr++)
    {
        if(itr->userName == userName)
        {
            for(int proby=0; proby<3; proby++)
            {
                cout << "Podaj haslo. Pozostalo prob " << 3-proby << ":";
                password=loadLineOfText();
                if(itr->password==password)
                {
                    cout << "Zalogowales sie.";
                    Sleep(1000);
                    return (itr->id);
                }
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba.";
            Sleep(3000);
            return 0;
        }
    }

    cout << "Nie ma uzytkownika z takim loginem";
    Sleep(1500);
    return 0;
}

void zmianaHasla(vector<User> &users,int idUser)
{
    string password;
    cout << "Podaj haslo:";
    password=loadLineOfText();

    for(vector<User>::iterator itr=users.begin(), endVectorWord=users.end(); itr!=endVectorWord; itr++)
        {
            if(itr->id==idUser)
            {
                itr->password=password;
                cout << "Haslo zostalo zmienione." << endl;
                Sleep(1500);
            }
        }
}

void enterTheAddresseeDetails(int idUser, vector <AdressData> &dataOfTheAddressee)
{

    AdressData dataOfAddressee;		// Dane Adresata
    if(!dataOfTheAddressee.empty())
        dataOfAddressee = dataOfTheAddressee.back();
    else
        dataOfAddressee.idOfAdressee=0;

    fstream file;
    file.open("Adresaci.txt", ios::in );

    if (file.good()==false)
    {
        cout<<"Nie udalo sie otworzyc pliku 'Adresaci.txt'!"<<endl;
        Sleep(3000);
        file.open("Adresaci.txt", ios::out );
        if(file.good()==true)
        {
            cout<<"Zostal utworzony nowy plik 'Adresaci.txt'z baza danych adresatow!"<<endl;
            Sleep(3000);
        }
    }
    if (file.good()==false)
    {
        cout<<"Nie udalo sie utworzyc pliku ""Adresaci.txt""!"<<endl;
        Sleep(3000);
        exit(0);
    }

    dataOfAddressee.idOfAdressee = dataOfAddressee.idOfAdressee + 1;
    dataOfAddressee.idOfUser = idUser;
    cout<<"Podaj nazwisko adresata: ";
    dataOfAddressee.surname = loadLineOfText();
    cout<<"Podaj imie adresata: ";
    dataOfAddressee.name = loadLineOfText();
    cout<<"Podaj numer telefonu adresata: ";
    dataOfAddressee.phoneNumber = loadLineOfText();
    cout<<"Podaj adres zamieszakania adresta: ";
    dataOfAddressee.address = loadLineOfText();
    cout<<"Podaj adres e-mail adresta: ";
    dataOfAddressee.email = loadLineOfText();

    dataOfTheAddressee.push_back(dataOfAddressee);
    cout<<"Adresat zostal utworzony."<<endl;
    Sleep(1500);

}

void saveToTxtFile(vector<AdressData> dataOfListAddressee)
{
    fstream file;
    file.open("Adresaci.txt", ios::out );

    for(vector<AdressData>::iterator itr = dataOfListAddressee.begin(), endVectorWord=dataOfListAddressee.end(); itr!=endVectorWord; itr++)
    {
        file<<itr->idOfAdressee<<'|'<<itr->idOfUser<<'|'<<itr->surname<<'|'<<itr->name<<'|'<<itr->phoneNumber<<'|'<<itr->address<<'|'<<itr->email<<'|'<<'\n';
    }

    file.close();
}

void readFromTxtFile(vector<AdressData> &writeToAddresseeList)
{
    AdressData dataOfAddresseeFromTxtFile;	// wskaznik/bufor na dane adrestata z txt

    string lineInTxtFile;
    int numberOfTheLineInTxtFile=1;

    fstream file;

    if(file.good()==true)
    {
        file.open("Adresaci.txt", ios::in );
    }

    while(getline(file,lineInTxtFile,'|') )
    {
        switch(numberOfTheLineInTxtFile)
        {
        case 1:
            dataOfAddresseeFromTxtFile.idOfAdressee=atoi(lineInTxtFile.c_str());
            break;
        case 2:
            dataOfAddresseeFromTxtFile.idOfUser=atoi(lineInTxtFile.c_str());
            break;
        case 3:
            dataOfAddresseeFromTxtFile.surname = lineInTxtFile;
            break;
        case 4:
            dataOfAddresseeFromTxtFile.name = lineInTxtFile;
            break;
        case 5:
            dataOfAddresseeFromTxtFile.phoneNumber = lineInTxtFile;
            break;
        case 6:
            dataOfAddresseeFromTxtFile.address = lineInTxtFile;
            break;
        case 7:
            dataOfAddresseeFromTxtFile.email = lineInTxtFile;
            break;
        }

        ++numberOfTheLineInTxtFile;
        if(numberOfTheLineInTxtFile==8)
        {
            numberOfTheLineInTxtFile=1;
            writeToAddresseeList.push_back(dataOfAddresseeFromTxtFile);
        }
    }
    file.close();
}

void searchTheAddresseeByName(vector<AdressData> &AddresseeList)
{
    string name;
    system("cls");
    cout<<"Podaj imie adresata: ";
    name = loadLineOfText();

    for(vector<AdressData>::iterator itr = AddresseeList.begin(), endVectorWord=AddresseeList.end(); itr!=endVectorWord; itr++)
    {
        if(itr->name==name)
        {
            cout<<"Numer id adresata: "<<itr->idOfAdressee<<endl;
            cout<<"Nazwisko adresata: "<<itr->surname<<endl;
            cout<<"Imie adresata: "<<itr->name<<endl;
            cout<<"Numer telefonu adresata: "<<itr->phoneNumber<<endl;
            cout<<"Adres zamieszakania adresta: "<<itr->address<<endl;
            cout<<"Adres e-mail adresta: "<<itr->email<<endl;
            cout<<"=========================================================\n";

            cout << "Aby wyjsc do menu wcisnij dowolny klawisz oraz potwierdzajac klawisz 'ENTER'!"<<endl;
            loadSign();
        }
    }
}

void searchTheAddresseeBySurname(vector<AdressData> &AddresseeList)
{
    string surname;
    system("cls");
    cout<<"Podaj nazwisko adresata: ";
    surname = loadLineOfText();

    for(vector<AdressData>::iterator itr = AddresseeList.begin(), endVectorWord=AddresseeList.end(); itr!=endVectorWord; itr++)
    {
        if(itr->surname==surname)
        {
            cout<<"Numer id adresata: "<<itr->idOfAdressee<<endl;
            cout<<"Nazwisko adresata: "<<itr->surname<<endl;
            cout<<"Imie adresata: "<<itr->name<<endl;
            cout<<"Numer telefonu adresata: "<<itr->phoneNumber<<endl;
            cout<<"Adres zamieszakania adresta: "<<itr->address<<endl;
            cout<<"Adres e-mail adresta: "<<itr->email<<endl;
            cout<<"=========================================================\n";

            cout << "Aby wyjsc do menu wcisnij dowolny klawisz oraz potwierdzajac klawisz 'ENTER'!"<<endl;
            loadSign();
        }
    }
}

void editAddressee(vector<AdressData> &AddresseeList)
{
    int id;
    //system("cls");
    cout<<"Podaj id adresata: ";
    id = loadIntegerNumber();
    vector<AdressData>::iterator itr = AddresseeList.begin();

    for(vector<AdressData>::iterator endVectorWord=AddresseeList.end(); itr!=endVectorWord; itr++)
    {
        if(itr->idOfAdressee==id)
        {
            system("cls");
            cout<<"Numer id adresata: "<<itr->idOfAdressee<<endl;
            cout<<"Nazwisko adresata: "<<itr->surname<<endl;
            cout<<"Imie adresata: "<<itr->name<<endl;
            cout<<"Numer telefonu adresata: "<<itr->phoneNumber<<endl;
            cout<<"Adres zamieszakania adresta: "<<itr->address<<endl;
            cout<<"Adres e-mail adresta: "<<itr->email<<endl;
            cout<<"=========================================================\n";

            char menuItem='0';

            while(menuItem!= '7')
            {
                switch(menuItem)
                {
                case '0':
                {
                    cout<<"1.Edytuj nazwisko adresata."<<endl;
                    cout<<"2.Edytuj imie adresata."<<endl;
                    cout<<"3.Edytuj numer telefonu adresata."<<endl;
                    cout<<"4.Edytuj adres zamieszakania adresta."<<endl;
                    cout<<"5.Edytuj adres e-mail adresta."<<endl;
                    cout<<"6.Wyjscie do Menu glowengo."<<endl;
                    menuItem = loadSign();
                }
                break;
                case '1':
                {
                    cout<<"Podaj nazwisko adresata: ";
                    itr->surname = loadLineOfText();
                    menuItem= '0';
                }
                break;
                case '2':
                {
                    cout<<"Podaj imie adresata: ";
                    itr->name = loadLineOfText();
                    menuItem= '0';
                }
                break;
                case '3':
                {
                    cout<<"Podaj numer telefonu adresata: ";
                    itr->phoneNumber = loadLineOfText();
                    menuItem= '0';
                }
                break;
                case '4':
                {
                    cout<<"Podaj adres zamieszakania adresta: ";
                    itr->address = loadLineOfText();
                    menuItem= '0';
                }
                break;
                case '5':
                {
                    cout<<"Podaj adres e-mail adresta: ";
                    itr->email = loadLineOfText();
                    menuItem= '0';
                }
                break;
                case '6':
                    menuItem= '7';
                    break;
                default:
                {
                    cout<<"Wybierz poprawna opcje menu wpisujac poprawna liczbe oraz potwierdzajac klawisz 'ENTER'!";
                    Sleep(2000);
                    menuItem = '0';
                }
                break;
                }
            }
            cout<<"Adresat zostal edytowany."<<endl;
            Sleep(1500);
        }
    }
}

void displayAdresseesId(vector<AdressData> printedVector)
{
    for(vector<AdressData>::iterator itr = printedVector.begin(), endVectorData=printedVector.end(); itr!=endVectorData; itr++)
    {
        cout<<"Numer id adresata: "<<itr->idOfAdressee<<", "<<"Nazwisko adresata: "<<itr->surname<<", "<<"Imie adresata: "<<itr->name<<endl;
    }
}

void printingTheVector(vector<AdressData> printedVector)
{
    for(vector<AdressData>::iterator itr = printedVector.begin(), endVectorData=printedVector.end(); itr!=endVectorData; itr++)
    {
        cout<<"Numer id adresata: "<<itr->idOfAdressee<<endl;
        cout<<"Nazwisko adresata: "<<itr->surname<<endl;
        cout<<"Imie adresata: "<<itr->name<<endl;
        cout<<"Numer telefonu adresata: "<<itr->phoneNumber<<endl;
        cout<<"Adres zamieszakania adresta: "<<itr->address<<endl;
        cout<<"Adres e-mail adresta: "<<itr->email<<endl;
        cout<<"=========================================================\n";
    }
}

void eraseAdressee(vector<AdressData> &vectorOfDeleteAddresses)
{
    int id;
    //system("cls");
    cout<<"Podaj id adresata: ";
    id = loadIntegerNumber();
    vector<AdressData>::iterator itr = vectorOfDeleteAddresses.begin();

    for(vector<AdressData>::iterator endVectorWord=vectorOfDeleteAddresses.end(); itr!=endVectorWord; itr++)
    {
        if(itr->idOfAdressee==id)
        {
            cout<<"Numer id adresata: "<<itr->idOfAdressee<<endl;
            cout<<"Nazwisko adresata: "<<itr->surname<<endl;
            cout<<"Imie adresata: "<<itr->name<<endl;
            cout<<"Numer telefonu adresata: "<<itr->phoneNumber<<endl;
            cout<<"Adres zamieszakania adresta: "<<itr->address<<endl;
            cout<<"Adres e-mail adresta: "<<itr->email<<endl;
            cout<<"=========================================================\n";

            cout << "Jezeli chcesz usunac adresata o wybranym id:" << itr->idOfAdressee << " " << itr->name << " " << itr->surname <<" "<< "wcisnij klawisz 't'"<<endl;
            cout << "Aby wyjsc do menu wcisnij dowolny inny klawisz oraz potwierdzajac klawisz 'ENTER'!"<<endl;
            if(loadSign()=='t')
            {
                vectorOfDeleteAddresses.erase(itr);
                cout<< "User o wskazanym id zostal usuniety !"<<endl;
                Sleep(1500);
            }
            else
            {
                break;
            }
        }
    }
}

int main()
{
    vector<AdressData> listOfAddresse;
    vector<User> users;
    int idUser=0;
    int iloscUzytkownikow=0;

    char wybor;
    char menuItemSelection = '0';

    string surname, name;

    readFromTxtFile(listOfAddresse);

    while(1)
    {

        if(idUser==0)
        {
            system("cls");
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" << endl;
            wybor=loadSign();

            if(wybor == '1')
            {
                iloscUzytkownikow = rejestracja(users,iloscUzytkownikow);
            }
            else if(wybor == '2')
            {
                idUser = logowanie(users);
            }
            else if(wybor == '9')
            {
                cout<<"Wcisnij enter, aby zamknac program...";
                cin.get();
                exit(0);
            }

        }
        else
        {
            switch(menuItemSelection)
            {
            case '0':
            {
                system("cls");
                cout << "KSIAZKA ADRESOWA\n";
                cout << "1. Dodaj adresata."  << endl;
                cout << "2. Wyszukaj po imieniu."      << endl;
                cout << "3. Wyszukaj po nazwisku."    << endl;
                cout << "4. Wyswietl wszystkich adresatow."  << endl;
                cout << "5. Usun adresata."      << endl;
                cout << "6. Edytuj adresata."    << endl;
                cout << "7. Zmiana hasla" << endl;
                cout << "8. Wylogowanie" << endl;
                cout << "Twoj wybor:"    << endl;

                menuItemSelection=loadSign();
            }
            break;

            case '1':
            {
                enterTheAddresseeDetails(idUser,listOfAddresse);
                saveToTxtFile(listOfAddresse);
                menuItemSelection = '0';
            }
            break;

            case '2':
            {
                searchTheAddresseeByName(listOfAddresse);
                menuItemSelection = '0';
            }
            break;

            case '3':
            {
                searchTheAddresseeBySurname(listOfAddresse);
                menuItemSelection = '0';
            }
            break;

            case '4':
            {
                printingTheVector(listOfAddresse);
                cout << "Aby wyjsc do menu wcisnij dowolny klawisz oraz potwierdzajac klawisz 'ENTER'!"<<endl;
                loadSign();
                menuItemSelection = '0';
            }
            break;

            case '5':
            {
                displayAdresseesId(listOfAddresse);
                eraseAdressee(listOfAddresse);
                saveToTxtFile(listOfAddresse);
                menuItemSelection = '0';
            }
            break;

            case '6':
            {
                displayAdresseesId(listOfAddresse);
                editAddressee(listOfAddresse);
                saveToTxtFile(listOfAddresse);
                menuItemSelection = '0';
            }
            break;

            case '7':
            {
                zmianaHasla(users,idUser);
                menuItemSelection = '0';
            }
            break;

            case '8':
            {
                idUser = 0;
                menuItemSelection = '0';
            }
            break;

            default:
            {
                cout<<"Wybierz poprawna opcje menu wpisujac poprawna liczbe oraz potwierdzajac klawisz ENTER!";
                Sleep(2000);
                menuItemSelection = '0';
            }
            break;

            }
        }
    }

    return 0;
}
