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
    string  surname;
    string  name;
    string  phoneNumber;
    string  address;
    string  email;
};

struct Uzytkownik
{
    int id;
    string nazwa, haslo;
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

int rejestracja(Uzytkownik users[],int usersCount)
{
    string nazwa, haslo;
    cout << "Podaj nazwe uzytkownika: ";
    nazwa=loadLineOfText();
    int i=0;
    while(i < usersCount)
    {
        if(users[i].nazwa == nazwa)
        {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            nazwa=loadLineOfText();
            i = 0;
        }
        else
        {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    haslo=loadLineOfText();
    users[usersCount].nazwa=nazwa;
    users[usersCount].haslo=haslo;
    users[usersCount].id=usersCount+1;
    cout << "Konto zalozone." << endl;
    Sleep(1000);

    return usersCount+1;
}

int logowanie(Uzytkownik uzytkownicy[],int iloscUzytkownikow)
{
    string nazwa, haslo;
    cout << "Podaj nazwe uzytkownika: ";
    nazwa=loadLineOfText();
    int i=0;
    while(i < iloscUzytkownikow)
    {
        if(uzytkownicy[i].nazwa == nazwa)
        {
            for(int proby=0; proby<3; proby++)
            {
                cout << "Podaj haslo. Pozostalo prob " << 3-proby << ":";
                haslo=loadLineOfText();
                if(uzytkownicy[i].haslo==haslo)
                {
                    cout << "Zalogowales sie.";
                    Sleep(1000);
                    return uzytkownicy[i].id;
                }
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba.";
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout << "Nie ma uzytkownika z takim loginem";
    Sleep(1500);
    return 0;
}

void zmianaHasla(Uzytkownik uzytkownicy[],int iloscUzytkownikow,int idZalogowanegoUzytkownika)
{
    string haslo;
    cout << "Podaj haslo:";
    haslo=loadLineOfText();

    for(int i=0; i<iloscUzytkownikow; i++)
    {
        if(uzytkownicy[i].id == idZalogowanegoUzytkownika)
        {
            uzytkownicy[i].haslo = haslo;
            cout << "Haslo zostalo zmienione." << endl;
            Sleep(1500);
        }
    }
}

void enterTheAddresseeDetails(vector <AdressData> &dataOfTheAddressee)
{

    AdressData dataOfAddressee;		// Dane Adresata
    if(!dataOfTheAddressee.empty())
        dataOfAddressee = dataOfTheAddressee.back();
    else
        dataOfAddressee.idOfAdressee=0;
////////////////////////////////////////////////////////////////////
    fstream file;
    file.open("ksiazka_adresowa.txt", ios::in );

    if (file.good()==false)
    {
        cout<<"Nie udalo sie otworzyc pliku 'ksiazka_adresowa.txt'!"<<endl;
        Sleep(3000);
        file.open("ksiazka_adresowa.txt", ios::out );
        if(file.good()==true)
        {
            cout<<"Zostal utworzony nowy plik 'ksiazka_adresowa.txt'z baza danych adresatow!"<<endl;
            Sleep(3000);
        }
    }
    if (file.good()==false)
    {
        cout<<"Nie udalo sie utworzyc pliku ""ksiazka_adresowa.txt""!"<<endl;
        Sleep(3000);
        exit(0);
    }
///////////////////////////////////////////////////////////////////
    dataOfAddressee.idOfAdressee = dataOfAddressee.idOfAdressee + 1;
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
    file.open("ksiazka_adresowa.txt", ios::out );

    for(vector<AdressData>::iterator itr = dataOfListAddressee.begin(), endVectorWord=dataOfListAddressee.end(); itr!=endVectorWord; itr++)
    {
        file<<itr->idOfAdressee<<'|'<<itr->surname<<'|'<<itr->name<<'|'<<itr->phoneNumber<<'|'<<itr->address<<'|'<<itr->email<<'|'<<'\n';
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
        file.open("ksiazka_adresowa.txt", ios::in );
    }

    while(getline(file,lineInTxtFile,'|') )
    {
        switch(numberOfTheLineInTxtFile)
        {
        case 1:
            dataOfAddresseeFromTxtFile.idOfAdressee=atoi(lineInTxtFile.c_str());
            break;
        case 2:
            dataOfAddresseeFromTxtFile.surname = lineInTxtFile;
            break;
        case 3:
            dataOfAddresseeFromTxtFile.name = lineInTxtFile;
            break;
        case 4:
            dataOfAddresseeFromTxtFile.phoneNumber = lineInTxtFile;
            break;
        case 5:
            dataOfAddresseeFromTxtFile.address = lineInTxtFile;
            break;
        case 6:
            dataOfAddresseeFromTxtFile.email = lineInTxtFile;
            break;
        }

        ++numberOfTheLineInTxtFile;
        if(numberOfTheLineInTxtFile==7)
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
                default: // oznacza blok instrukcji wykonywany dla wszystkich pozostalych wartosci zmienna
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
                cout<< "Uzytkownik o wskazanym id zostal usuniety !"<<endl;
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
    vector <AdressData> listOfAddresse;
    Uzytkownik uzytkownicy[100];
    int idZalogowanegoUzytkownika=0;
    int iloscUzytkownikow=0;

    char wybor;
    char menuItemSelection = '0';

    string surname, name;

    readFromTxtFile(listOfAddresse);

    while(1)
    {

        if(idZalogowanegoUzytkownika==0)
        {
            system("cls");
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" << endl;
            wybor=loadSign();

            if(wybor == '1')
            {
                iloscUzytkownikow = rejestracja(uzytkownicy,iloscUzytkownikow);
            }
            else if(wybor == '2')
            {
                idZalogowanegoUzytkownika = logowanie(uzytkownicy,iloscUzytkownikow);
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
                enterTheAddresseeDetails(listOfAddresse);
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
                zmianaHasla(uzytkownicy,iloscUzytkownikow,idZalogowanegoUzytkownika);

            }
            break;

            case '8':
            {
                idZalogowanegoUzytkownika = 0;

            }
            break;

            default: // oznacza blok instrukcji wykonywany dla wszystkich pozosta³ych wartoœci zmienna
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
