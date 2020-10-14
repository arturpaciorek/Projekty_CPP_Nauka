#include <iostream>
#include <windows.h>
#include<sstream>
#include<string>
#include <fstream>
#include <vector>

using namespace std;

struct Przyjaciel
{
    int id = 0;
    string imie = "", nazwisko = "", numerTel = "", email = "", adres = "";
};

vector <Przyjaciel> adresaci;
string konwersjaIntNaString(int liczba)
{
    stringstream wyraz;
    wyraz << liczba;
    string str = wyraz.str();
    return str;

}
int konwersjaStringNaInt(string wyraz)
{
    int liczba;
    stringstream intWyraz(wyraz);
    intWyraz>>liczba;
    return liczba;
}
void podzielStringNaWyrazy(const string& wczytanaLinia, char znacznikKoncaWyrazu, vector<string>& roboczyWektorWyrazow)
{
    int i = 0;
    int j = wczytanaLinia.find(znacznikKoncaWyrazu);

    while (j >= 0)
    {
        roboczyWektorWyrazow.push_back(wczytanaLinia.substr(i, j-i));
        i = ++j;
        j = wczytanaLinia.find(znacznikKoncaWyrazu, j);

        if (j < 0)
        {
            roboczyWektorWyrazow.push_back(wczytanaLinia.substr(i, wczytanaLinia.length()));
        }
    }
}

struct Przyjaciel przepiszLinieDoStruktury(vector<string> &liniaWczytana)
{
    struct Przyjaciel adresat;
    adresat.id = konwersjaStringNaInt(liniaWczytana[0]);
    adresat.imie = liniaWczytana[1];
    adresat.nazwisko = liniaWczytana[2];
    adresat.numerTel = liniaWczytana[3];
    adresat.email = liniaWczytana[4];
    adresat.adres = liniaWczytana[5];

    return adresat;
}
void zapiszPrzyjacieladoPliku(vector <Przyjaciel> &przyjaciele, int iloscPrzyjaciol)
{
    string imie, nazwisko, telefon, adresPocztowy, adresEmail;
    int idKontaktu, idNowe;
    vector<Przyjaciel>::iterator it ;
    fstream plik;
    int nrLinii = 0;
    string linia;

    for(it=przyjaciele.begin(); it<przyjaciele.end(); it++)
    {
        idKontaktu=it->id;
    }

    cout << endl << "Wpisz dane nowego kontaktu." << endl;
    cout << "Imie:";
    cin.sync();
    getline(cin, imie, '\n');
    cout << "Nazwisko:";
    cin.sync();
    getline(cin, nazwisko, '\n');
    cout << "Telefon:";
    cin.sync();
    getline(cin, telefon, '\n');
    cout << "Adres pocztowy - w jednej linii:";
    cin.sync();
    getline(cin, adresPocztowy, '\n');
    cout << "Adres email:";
    cin >> adresEmail;

    plik.open("ksiazkaAdresowa.txt", ios::in);
    if(plik.is_open())
    {
        while(!plik.eof())
        {
            getline(plik, linia);
            nrLinii++;
        }
        plik.close();
    }
    else
    {
        idKontaktu = 0;
        plik.close();
    }
    idNowe=idKontaktu+1;
    plik.open("ksiazkaAdresowa.txt", ios::out | ios::app);
    plik << idNowe<<"|";
    plik << imie <<"|";
    plik << nazwisko << "|";
    plik << telefon << "|";
    plik << adresEmail <<"|";
    plik << adresPocztowy << "|"<<endl;;
    plik.close();

    cout << "Kontakt zostal wpisany." << endl;
    Sleep(1500);
}
void zmodyfikujLinieWPliku(int nrLinii, string NowaLinia)
{
    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::in | ios::out | ios::app);

    vector <string> temp;
    string tekst;
    int index = 1;

    if (plik.good())
    {
        while (getline(plik, tekst))
        {
            if (index != nrLinii)
            {
                temp.push_back(tekst);
            }

            else temp.push_back(NowaLinia);

            index++;
        }
    }

    plik.close();
    plik.open("KsiazkaAdresowa.txt", ios::in | ios::out | ios::trunc);
    for (int i = 0; i < temp.size(); i++)
    {
        plik << temp.at(i) << endl;
    }
    plik.close();
}
void usunLinieWPliku(int nrLinii)
{
    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::in | ios::out | ios::app);

    vector <string> temp;
    string tekst;
    int index = 1;
    if (plik.good())
    {
        while (getline(plik, tekst))
        {
            if (index != nrLinii)
            {
                temp.push_back(tekst);
            }
            index++;
        }
    }
    plik.close();
    plik.open("KsiazkaAdresowa.txt", ios::in | ios::out | ios::trunc);
    for (int i = 0; i < temp.size(); i++)
    {
        plik << temp.at(i) << endl;
    }
    plik.close();
}
void podmienAdresataWPliku(int nrLinii,Przyjaciel adresat)
{
    string    id=konwersjaIntNaString(adresat.id);
    string Zamiennik= id+"|"+adresat.imie+"|"+adresat.nazwisko+"|"+adresat.numerTel+"|"+adresat.email+"|"+adresat.adres;
    zmodyfikujLinieWPliku(nrLinii,Zamiennik );
}

void wypiszNaEkranPrzyjaciela(vector <Przyjaciel> &przyjaciele, int index)
{
    Sleep(1000);
    cout<<"----------------------------"<<endl;
    cout<<"Id: "<<przyjaciele[index].id<<endl ;
    cout<<"Imie: "<<przyjaciele[index].imie<<endl ;
    cout<<"Nazwisko: "<<przyjaciele[index].nazwisko<<endl;
    cout<<"Nr tel: "<<przyjaciele[index].numerTel<<endl;
    cout<<"e-mail: "<<przyjaciele[index].email<<endl;
    cout<<"Adres: "<<przyjaciele[index].adres<<endl;
    cout<<"----------------------------"<<endl;

}
void wypiszImiona(vector <Przyjaciel> &przyjaciele, int iloscPrzyjaciol)
{
    string imie;
    int znacznik=0;
    cout<<"Podaj imie ktore wypisac: "<<endl;
    cin>>imie;
    for(int i=0; i<iloscPrzyjaciol; i++)
    {
        if(przyjaciele[i].imie==imie)
        {
            wypiszNaEkranPrzyjaciela(przyjaciele,i);
            znacznik++;
        }
    }
    if (znacznik==0)
    {
        cout<<"Niestety nie ma rekordow z podanym imieniem :( "<<endl;
    }
}
void wypiszNazwiska(vector <Przyjaciel> &przyjaciele, int iloscPrzyjaciol)
{
    string nazwisko;
    int znacznik=0;
    cout<<"Podaj nazwisko ktore wypisac: "<<endl;
    cin>>nazwisko;
    for(int i=0; i<iloscPrzyjaciol; i++)
    {
        if(przyjaciele[i].nazwisko==nazwisko)
        {
            wypiszNaEkranPrzyjaciela(przyjaciele,i);
            znacznik++;
        }
    }
    if (znacznik==0)
    {
        cout<<"Niestety nie ma rekordow z podanym nazwiskiem :( "<<endl;
    }
}

int czytajPlik(vector <Przyjaciel> &przyjaciele)
{
    string linia; // tworze zmienna do ktorej bede zapisywal odczytane linie z pliku tekstowego
    int nr_linii = 1;
    int iloscOsob = 0;
    vector<string> wczytanaLinia;
    Przyjaciel strukturka;
    fstream plik;
    plik.open("KsiazkaAdresowa.txt",ios::in);  // aby otworzyc plik do odczytu
    if (plik.good() == true)
    {
        // odczytuje linie po kolei. Linie w pliku tekstowym w przeciwienstwie do tablic sa numerowane od 1
        // funkcja getline odczytuje ze zmiennej plikowej plik i zapisuje linie jako stringa do zmiennej linia.
        // funkcja zwraca true dopoki sa linie do odczytania. Zwroci false, gdy plik sie skonczy
        while (getline(plik,linia))
        {
            wczytanaLinia.clear();
            podzielStringNaWyrazy(linia,'|',wczytanaLinia);
            strukturka=przepiszLinieDoStruktury(wczytanaLinia);
            przyjaciele.push_back(strukturka);
            nr_linii++;
        }
        plik.close();
    }
    iloscOsob=nr_linii-1;
    return iloscOsob;
}

void  edytujAdresata(vector <Przyjaciel> &przyjaciele)
{
    int idDoEdycji, index;
    char wybor;
    string noweImie, noweNazwisko, nowyTel, nowyMail, nowyAdres;
    string rekord;
    cout<<"Podaj nr id adresata, ktorego chcesz edytowac: "<<endl;
    cin>>idDoEdycji;
    vector<Przyjaciel>::iterator it;
    for(it=przyjaciele.begin(); it<przyjaciele.end(); it++)
    {
        if(it->id==idDoEdycji)
        {
            index=distance(przyjaciele.begin(),it);
            system("cls");

            cout << "-----MENU EDYCJI ADRESATA-----" << endl;
            cout<<"1. Imie. "<<endl;
            cout<<"2. Nazwisko. "<<endl;
            cout<<"3. Numer Telefonu. "<<endl;
            cout<<"4. e-mail. "<<endl;
            cout<<"5. adres. "<<endl;
            cout<<"6. Powrot do menu. "<<endl;
            cin>>wybor;


            if (wybor=='1')
            {
                cout<<"Imie ktore chcesz zamienic: "<<it->imie<<endl;
                cout<<"Wpisz nowe imie: "<<endl;

                cin.sync();
                getline(cin, noweImie, '\n');
                przyjaciele[index].imie=noweImie;

                podmienAdresataWPliku(index+1, przyjaciele[index]);
                cout<<"Imie zostalo pomyslnie podmienione."<<endl;
                Sleep(1000);
            }
            else if(wybor=='2')
            {
                cout<<"Nazwisko ktore chcesz zamienic: "<<it->nazwisko<<endl;
                cout<<"Wpisz nowe nazwisko: "<<endl;
                cin.sync();
                getline(cin, noweNazwisko, '\n');
                przyjaciele[index].nazwisko=noweNazwisko;
                podmienAdresataWPliku(index+1, przyjaciele[index]);
                cout<<"Nazwisko zostalo pomyslnie podmienione."<<endl;
                Sleep(1000);
            }
            else if(wybor=='3')
            {
                cout<<"Nr tel ktore chcesz zamienic: "<<it->numerTel<<endl;
                cout<<"Wpisz nowy numer: "<<endl;
                cin.sync();
                getline(cin, nowyTel, '\n');
                przyjaciele[index].numerTel=nowyTel;
                podmienAdresataWPliku(index+1, przyjaciele[index]);
                cout<<"Nr tel zostal pomyslnie podmieniony."<<endl;
                Sleep(1000);
            }
            else if(wybor=='4')
            {
                cout<<"Email ktore chcesz zamienic: "<<it->email<<endl;
                cout<<"Wpisz nowy email: "<<endl;
                cin.sync();
                getline(cin, nowyMail, '\n');
                przyjaciele[index].email=nowyMail;
                podmienAdresataWPliku(index+1, przyjaciele[index]);
                cout<<"Email zostal pomyslnie podmieniony."<<endl;
                Sleep(1000);
            }
            else if(wybor=='5')
            {
                cout<<"Adres ktore chcesz zamienic: "<<it->adres<<endl;
                cout<<"Wpisz nowy adres: "<<endl;
                cin.sync();
                getline(cin, nowyAdres, '\n');
                przyjaciele[index].adres=nowyAdres+"|";
                podmienAdresataWPliku(index+1, przyjaciele[index]);
                cout<<"Adres zostal pomyslnie podmieniony."<<endl;
                Sleep(1000);
            }
            else if(wybor=='6')
            {

            }

            break;
        }
        else if(it==(przyjaciele.end()-1))
        {
            cout<<"niestety nie ma adresata o podanym id."<<endl;
            system("pause");
            break;
        }
    }


}

void usunAdresata(vector <Przyjaciel> &przyjaciele)
{
    int idDoEdycji, index;
    char wybor;
    //string noweImie, noweNazwisko, nowyTel, nowyMail, nowyAdres;
    // string rekord;
    cout<<"Podaj nr id adresata, ktorego chcesz usunac: "<<endl;
    cin>>idDoEdycji;
    vector<Przyjaciel>::iterator it;
    for(it=przyjaciele.begin(); it<=przyjaciele.end(); it++)
    {
        if(it->id==idDoEdycji)
        {
            index=distance(przyjaciele.begin(),it);

            cout<<"Czy jestes pewien, ze chcesz usunac danego adresata z ksiazki? (t- tak /n-nie) "<<endl;
            cin>>wybor;


            if (wybor=='t')
            {
                usunLinieWPliku(index+1);
            }
            break;
        }
        else if(it==(przyjaciele.end()))
        {
            cout<<"niestety nie ma adresata o podanym id."<<endl;
            system("pause");
            break;
        }
    }

}
int main()
{

    int iloscPrzyjaciol =0;
    char wybor;
    adresaci.clear();

    while(true)
    {
        adresaci.clear();
        iloscPrzyjaciol= czytajPlik(adresaci);

        system("cls");
        cout << "-----MENU GLOWNE-----" << endl;
        cout<<"1. Dodaj adresata. "<<endl;
        cout<<"2. Wyszukaj po imieniu. "<<endl;
        cout<<"3. Wyszukaj po nazwisku. "<<endl;
        cout<<"4. Wyswietl wszystkich adresatow. "<<endl;
        cout<<"5. Usun adresata. "<<endl;
        cout<<"6. Edytuj adresata. "<<endl;
        cout<<"9. Zakoncz Program "<<endl;

        cin>>wybor;
        if (wybor=='1')
        {
            system("cls");
            zapiszPrzyjacieladoPliku(adresaci, iloscPrzyjaciol);
        }
        else if(wybor=='2')
        {
            adresaci.clear();
            system("cls");
            wypiszImiona(adresaci, iloscPrzyjaciol);
            system("pause");

        }
        else if(wybor=='3')
        {
            adresaci.clear();
            system("cls");
            wypiszNazwiska(adresaci, iloscPrzyjaciol);
            system("pause");
        }
        else if(wybor=='4')
        {
            adresaci.clear();
            system("cls");
            for(int i=0; i<iloscPrzyjaciol; i++)
            {
                wypiszNaEkranPrzyjaciela(adresaci, i);
            }
            system("pause");

        }
        else if(wybor=='5')
        {
            usunAdresata(adresaci);

        }
        else if(wybor=='6')
        {
            edytujAdresata(adresaci);
        }

        else if(wybor=='9')
        {
            exit(0);
        }
    }
    return 0;
}
