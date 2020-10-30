#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <algorithm>
#include <cstdio>

using namespace std;


struct AdressData
{
    int     idOfAdressee;
    int     idOfUser;
    string  name;
    string  surname;
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
    cout<<"Podaj imie adresata: ";
    dataOfAddressee.name = loadLineOfText();
    cout<<"Podaj nazwisko adresata: ";
    dataOfAddressee.surname = loadLineOfText();
    cout<<"Podaj numer telefonu adresata: ";
    dataOfAddressee.phoneNumber = loadLineOfText();
    cout<<"Podaj adres e-mail adresta: ";
    dataOfAddressee.email = loadLineOfText();
    cout<<"Podaj adres zamieszakania adresta: ";
    dataOfAddressee.address = loadLineOfText();

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
        file<<itr->idOfAdressee<<'|'<<itr->idOfUser<<'|'<<itr->name<<'|'<<itr->surname<<'|'<<itr->phoneNumber<<'|'<<itr->email<<'|'<<itr->address<<'|'<<'\n';
    }

    file.close();
}

void readFromTxtFile(vector<AdressData> &writeToAddresseeList, int idUser)
{
    AdressData dataOfAddresseeFromTxtFile;

    string lineInTxtFile;
    int numberOfTheLineInTxtFile=1;

    fstream file;

    if(file.good()==true)
    {
        file.open("Adresaci.txt", ios::in );
    }

    while(getline(file,lineInTxtFile,'|'))
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
            dataOfAddresseeFromTxtFile.name = lineInTxtFile;
            break;
        case 4:
            dataOfAddresseeFromTxtFile.surname = lineInTxtFile;
            break;
        case 5:
            dataOfAddresseeFromTxtFile.phoneNumber = lineInTxtFile;
            break;
        case 6:
            dataOfAddresseeFromTxtFile.email = lineInTxtFile;
            break;
        case 7:
            dataOfAddresseeFromTxtFile.address = lineInTxtFile;
            break;
        }

        ++numberOfTheLineInTxtFile;
        if(numberOfTheLineInTxtFile==8)
        {
            numberOfTheLineInTxtFile=1;
            if(dataOfAddresseeFromTxtFile.idOfUser==idUser)
            {
                writeToAddresseeList.push_back(dataOfAddresseeFromTxtFile);
            }
        }
    }
    file.close();
}

void enterTheUsersDetails(vector<User> &users)
{

    User dataOfUser;		// Dane Adresata
    if(!users.empty())
        dataOfUser = users.back();
    else
        dataOfUser.id=0;

    fstream fileUsers;
    fileUsers.open("Uzytkownicy.txt", ios::in );

    if (fileUsers.good()==false)
    {
        cout<<"Nie udalo sie otworzyc pliku 'Uzytkownicy.txt'!"<<endl;
        Sleep(3000);
        fileUsers.open("Uzytkownicy.txt", ios::out );
        if(fileUsers.good()==true)
        {
            cout<<"Zostal utworzony nowy plik 'Uzytkownicy.txt'z baza danych adresatow!"<<endl;
            Sleep(3000);
        }
    }
    if (fileUsers.good()==false)
    {
        cout<<"Nie udalo sie utworzyc pliku ""Uzytkownicy.txt""!"<<endl;
        Sleep(3000);
        exit(0);
    }

    dataOfUser.id = dataOfUser.id + 1;
    cout<<"Podaj nazwie uzytkownika: ";
    dataOfUser.userName = loadLineOfText();
    cout<<"Podaj haslo uzytkownika: ";
    dataOfUser.password = loadLineOfText();

    users.push_back(dataOfUser);
    cout<<"User zostal utworzony."<<endl;
    Sleep(1500);

}

void saveUsersToTxtFile(vector<User> &users)
{
    fstream fileUsers;
    fileUsers.open("Uzytkownicy.txt", ios::out );

    for(vector<User>::iterator itr = users.begin(), endVectorWord=users.end(); itr!=endVectorWord; itr++)
    {
        fileUsers<<itr->id<<'|'<<itr->userName<<'|'<<itr->password<<'|'<<'\n';
    }

    fileUsers.close();
}

void readUsersFromTxtFile(vector<User> &users)
{
    User dataOfUser;

    string lineInTxtFile;
    int numberOfTheLineInTxtFile=1;

    fstream fileUsers;

    if(fileUsers.good()==true)
    {
        fileUsers.open("Uzytkownicy.txt", ios::in );
    }

    while(getline(fileUsers,lineInTxtFile,'|') )
    {
        switch(numberOfTheLineInTxtFile)
        {
        case 1:
            dataOfUser.id = atoi(lineInTxtFile.c_str());
            break;
        case 2:
            dataOfUser.userName = lineInTxtFile;
            break;
        case 3:
            dataOfUser.password = lineInTxtFile;
            break;
        }

        ++numberOfTheLineInTxtFile;
        if(numberOfTheLineInTxtFile==4)
        {
            numberOfTheLineInTxtFile=1;
            users.push_back(dataOfUser);
        }
    }
    fileUsers.close();
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
            cout<<"Imie adresata: "<<itr->name<<endl;
            cout<<"Nazwisko adresata: "<<itr->surname<<endl;
            cout<<"Numer telefonu adresata: "<<itr->phoneNumber<<endl;
            cout<<"Adres e-mail adresta: "<<itr->email<<endl;
            cout<<"Adres zamieszakania adresta: "<<itr->address<<endl;
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
            cout<<"Imie adresata: "<<itr->name<<endl;
            cout<<"Nazwisko adresata: "<<itr->surname<<endl;
            cout<<"Numer telefonu adresata: "<<itr->phoneNumber<<endl;
            cout<<"Adres e-mail adresta: "<<itr->email<<endl;
            cout<<"Adres zamieszakania adresta: "<<itr->address<<endl;
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

    AdressData dataOfAddresseeFromTxtFile;

    string lineInTxtFile;
    int numberOfTheLineInTxtFile=1;

    fstream file, fileTemp;
    fileTemp.open("Adresaci_tymczasowy.txt", ios::out );

    if(file.good()==true)
    {
        file.open("Adresaci.txt", ios::in );
    }

    for(vector<AdressData>::iterator endVectorWord=AddresseeList.end(); itr!=endVectorWord; itr++)
    {
        if(itr->idOfAdressee==id)
        {
            char menuItem='0';

            while(menuItem!= '7')
            {
                switch(menuItem)
                {
                case '0':
                {
                    system("cls");
                    cout<<"Numer id adresata: "<<itr->idOfAdressee<<endl;
                    cout<<"Imie adresata: "<<itr->name<<endl;
                    cout<<"Nazwisko adresata: "<<itr->surname<<endl;
                    cout<<"Numer telefonu adresata: "<<itr->phoneNumber<<endl;
                    cout<<"Adres e-mail adresta: "<<itr->email<<endl;
                    cout<<"Adres zamieszakania adresta: "<<itr->address<<endl;
                    cout<<"=========================================================\n";

                    cout<<"1.Edytuj imie adresata."<<endl;
                    cout<<"2.Edytuj nazwisko adresata."<<endl;
                    cout<<"3.Edytuj numer telefonu adresata."<<endl;
                    cout<<"4.Edytuj adres e-mail adresta."<<endl;
                    cout<<"5.Edytuj adres zamieszakania adresta."<<endl;
                    cout<<"6.Wyjscie do Menu glowengo."<<endl;
                    menuItem = loadSign();
                }
                break;
                case '1':
                {
                    cout<<"Podaj imie adresata: ";
                    itr->name = loadLineOfText();
                    menuItem= '0';
                }
                break;
                case '2':
                {
                    cout<<"Podaj nazwisko adresata: ";
                    itr->surname = loadLineOfText();
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
                    cout<<"Podaj adres e-mail adresta: ";
                    itr->email = loadLineOfText();
                    menuItem= '0';
                }
                break;
                case '5':
                {
                    cout<<"Podaj adres zamieszakania adresta: ";
                    itr->address = loadLineOfText();
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

            while(getline(file,lineInTxtFile,'|'))
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
                    dataOfAddresseeFromTxtFile.name = lineInTxtFile;
                    break;
                case 4:
                    dataOfAddresseeFromTxtFile.surname = lineInTxtFile;
                    break;
                case 5:
                    dataOfAddresseeFromTxtFile.phoneNumber = lineInTxtFile;
                    break;
                case 6:
                    dataOfAddresseeFromTxtFile.email = lineInTxtFile;
                    break;
                case 7:
                    dataOfAddresseeFromTxtFile.address = lineInTxtFile;
                    break;
                }

                ++numberOfTheLineInTxtFile;
                if(numberOfTheLineInTxtFile==8)
                {
                    numberOfTheLineInTxtFile=1;
                    if(dataOfAddresseeFromTxtFile.idOfAdressee==id)
                    {
                        fileTemp<<itr->idOfAdressee<<'|'<<itr->idOfUser<<'|'<<itr->name<<'|'<<itr->surname<<'|'<<itr->phoneNumber<<'|'<<itr->email<<'|'<<itr->address<<'|'<<'\n';
                    }
                    else if(dataOfAddresseeFromTxtFile.idOfAdressee!=id)
                    {
                        fileTemp<<dataOfAddresseeFromTxtFile.idOfAdressee<<'|'<<dataOfAddresseeFromTxtFile.idOfUser<<'|'<<dataOfAddresseeFromTxtFile.name<<'|'<<dataOfAddresseeFromTxtFile.surname<<'|'<<dataOfAddresseeFromTxtFile.phoneNumber<<'|'<<dataOfAddresseeFromTxtFile.email<<'|'<<dataOfAddresseeFromTxtFile.address<<'|'<<'\n';
                    }
                }
            }
            file.close();
            fileTemp.close();
        }
    }
    remove("Adresaci.txt"); // delete file
    rename("Adresaci_tymczasowy.txt", "Adresaci.txt");
    cout<<"Adresat zostal edytowany."<<endl;
    Sleep(1500);
}

void displayAdresseesId(vector<AdressData> printedVector)
{
    for(vector<AdressData>::iterator itr = printedVector.begin(), endVectorData=printedVector.end(); itr!=endVectorData; itr++)
    {
        cout<<"Numer id adresata: "<<itr->idOfAdressee<<", "<<"Imie adresata: "<<itr->name<<", "<<"Nazwisko adresata: "<<itr->surname<<endl;
    }
}

void printingTheVector(vector<AdressData> printedVector)
{
    for(vector<AdressData>::iterator itr = printedVector.begin(), endVectorData=printedVector.end(); itr!=endVectorData; itr++)
    {
        cout<<"Numer id adresata: "<<itr->idOfAdressee<<endl;
        cout<<"Imie adresata: "<<itr->name<<endl;
        cout<<"Nazwisko adresata: "<<itr->surname<<endl;
        cout<<"Numer telefonu adresata: "<<itr->phoneNumber<<endl;
        cout<<"Adres e-mail adresta: "<<itr->email<<endl;
        cout<<"Adres zamieszakania adresta: "<<itr->address<<endl;
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
    AdressData dataOfAddresseeFromTxtFile;

    string lineInTxtFile;
    int numberOfTheLineInTxtFile=1;

    fstream file, fileTemp;
    fileTemp.open("Adresaci_tymczasowy.txt", ios::out );

    if(file.good()==true)
    {
        file.open("Adresaci.txt", ios::in );
    }

    for(vector<AdressData>::iterator endVectorWord=vectorOfDeleteAddresses.end(); itr!=endVectorWord; itr++)
    {
        if(itr->idOfAdressee==id)
        {
            cout<<"Numer id adresata: "<<itr->idOfAdressee<<endl;
            cout<<"Imie adresata: "<<itr->name<<endl;
            cout<<"Nazwisko adresata: "<<itr->surname<<endl;
            cout<<"Numer telefonu adresata: "<<itr->phoneNumber<<endl;
            cout<<"Adres e-mail adresta: "<<itr->email<<endl;
            cout<<"Adres zamieszakania adresta: "<<itr->address<<endl;
            cout<<"=========================================================\n";

            cout << "Jezeli chcesz usunac adresata o wybranym id:" << itr->idOfAdressee << " " << itr->name << " " << itr->surname <<" "<< "wcisnij klawisz 't'"<<endl;
            cout << "Aby wyjsc do menu wcisnij dowolny inny klawisz oraz potwierdzajac klawisz 'ENTER'!"<<endl;
            if(loadSign()=='t')
            {
                vectorOfDeleteAddresses.erase(itr);
                ///////////////////////////////////////////////



                while(getline(file,lineInTxtFile,'|'))
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
                        dataOfAddresseeFromTxtFile.name = lineInTxtFile;
                        break;
                    case 4:
                        dataOfAddresseeFromTxtFile.surname = lineInTxtFile;
                        break;
                    case 5:
                        dataOfAddresseeFromTxtFile.phoneNumber = lineInTxtFile;
                        break;
                    case 6:
                        dataOfAddresseeFromTxtFile.email = lineInTxtFile;
                        break;
                    case 7:
                        dataOfAddresseeFromTxtFile.address = lineInTxtFile;
                        break;
                    }


                    ++numberOfTheLineInTxtFile;
                    if(numberOfTheLineInTxtFile==8)
                    {
                        numberOfTheLineInTxtFile=1;
                        if(dataOfAddresseeFromTxtFile.idOfAdressee!=id)
                        {
                            fileTemp<<dataOfAddresseeFromTxtFile.idOfAdressee<<'|'<<dataOfAddresseeFromTxtFile.idOfUser<<'|'<<dataOfAddresseeFromTxtFile.name<<'|'<<dataOfAddresseeFromTxtFile.surname<<'|'<<dataOfAddresseeFromTxtFile.phoneNumber<<'|'<<dataOfAddresseeFromTxtFile.email<<'|'<<dataOfAddresseeFromTxtFile.address<<'|'<<'\n';
                        }
                    }
                }
                file.close();
                fileTemp.close();


                ////////////////////////////////////////////////
                cout<< "User o wskazanym id zostal usuniety !"<<endl;
                Sleep(1500);
            }
            else
            {
                break;
            }
        }
    }
    remove("Adresaci.txt"); // delete file
    rename("Adresaci_tymczasowy.txt", "Adresaci.txt");

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

    readUsersFromTxtFile(users);

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
                readFromTxtFile(listOfAddresse,idUser);
            }
            else if(wybor == '9')
            {
                cout<<"Wcisnij enter, aby zamknac program...";
                cin.get();
                //saveUsersToTxtFile(users);
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
                //saveToTxtFile(listOfAddresse);
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
                //saveToTxtFile(listOfAddresse);
                menuItemSelection = '0';
            }
            break;

            case '6':
            {
                displayAdresseesId(listOfAddresse);
                editAddressee(listOfAddresse);
                //saveToTxtFile(listOfAddresse);
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
                listOfAddresse.clear();
                menuItemSelection = '0';
                idUser = 0;
            }
            break;

            default:
            {
                cout<<"Wybierz poprawna opcje menu wpisujac poprawna liczbe oraz potwierdzajac klawisz ENTER!";
                Sleep(2000);
                idUser = 0;
            }
            break;

            }
        }
    }

    return 0;
}
