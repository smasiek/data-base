#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <fstream>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;
int staleId=1;
struct student
{
    const int id;
    string nazwisko;
    string specjalnosc;
    float srednia;
    student(const int idPomocnicze): id(idPomocnicze) {}
    student(int Id, string Nazwisko, string Specjalnosc, float Srednia):id(Id)
    {
        nazwisko=Nazwisko;
        specjalnosc=Specjalnosc;
        srednia=Srednia;
    }

};

vector <student*> studenci;
student* wprowadz()
{
    string nazwiskoTymcz,specjalnoscTymcz;
    float sredniaTymcz;
    student *dodawanyStudent = new student(staleId);
    staleId++;
    cout<<"Podaj nazwisko studenta: ";
    getline(cin, nazwiskoTymcz);
    cout<<"Podaj specjalnosc studenta: ";
    getline(cin, specjalnoscTymcz);
    char error='a';
    int again=1;

    while(again==1)
    {
        try
        {
            cout<<"Podaj srednia studenta: ";
            cin>>sredniaTymcz;
            if(!cin || getchar() != '\n')
                throw error;
            else
                again=0;
        }
        catch(...)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"\nBlad! Wpisz cyfre!!\n";
        }
    }
    dodawanyStudent->nazwisko=nazwiskoTymcz;
    dodawanyStudent->specjalnosc=specjalnoscTymcz;
    dodawanyStudent->srednia=sredniaTymcz;
    return dodawanyStudent;
}

void wypiszDane(student* nowy_student)
{
    cout<<"Id studenta: "<<setw(3)<<nowy_student->id<<", Nazwisko studenta: "<<setw(10)<<nowy_student->nazwisko<<", Specjalnosc studenta: "<<setw(10)<<nowy_student->specjalnosc<<", Srednia studenta: "<<nowy_student->srednia<<endl;
}



student edytowanie(student* &student_nowy)
{
    cout<<"Podaj nowe nazwisko studenta: ";
    getline(cin, student_nowy->nazwisko);
    cout<<"Podaj nowa specjalnosc studenta: ";
    getline(cin, student_nowy->specjalnosc);
    char error='a';
    int again=1;
    while(again==1)
    {
        try
        {
            cout<<"Podaj nowa srednia studenta: ";
            cin>>student_nowy->srednia;
            if(!cin || getchar() != '\n')
                throw error;
            else
                again=0;
        }
        catch(...)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"\nBlad! Wpisz cyfre!!\n";
        }
    }
    return *student_nowy;
}

void zapiszZawartoscBazy(string nazwa)
{
    ofstream baza;
    baza.open(nazwa,ios::trunc);
    for(int i=0; i<studenci.size(); i++)
    {
        baza<<setw(3)<<studenci[i]->id<<setw(10)<<studenci[i]->nazwisko<<setw(10)<<studenci[i]->specjalnosc<<setw(10)<<studenci[i]->srednia;
        if(i<studenci.size()-1)
            baza<<"\n";
    }
    baza.close();
}



void dopiszStudentowDoPliku(int ls,string nazwa)
{
    ofstream baza;
    baza.open(nazwa,ios::app);
    for(int i=(studenci.size()-ls); i<studenci.size(); i++)
    {
        baza<<endl<<setw(3)<<studenci[i]->id<<setw(10)<<studenci[i]->nazwisko<<setw(10)<<studenci[i]->specjalnosc<<setw(10)<<studenci[i]->srednia;
        if(i<ls-1)
            baza<<"\n";
    }
    baza.close();

}



int wczytaj_baze(string &nazwa)
{
    int tymczId;
    string tymczNazwisko,tymczSpecjalnosc;
    float tymczSrednia;
    ifstream baza{nazwa,ios::in};
    while(!baza)
    {
        cerr<<"\nNie udalo sie otworzyc pliku do wczytania..."<<endl;
        cout<<"\nPodaj nazwe istniejacej bazy";
        getline(cin,nazwa);
        nazwa+=".txt";
        cout<<nazwa;
        baza.open(nazwa,ios::in);
    }
    int k=0;
    try
    {
        while(!baza.eof())
        {
            baza>>tymczId>>tymczNazwisko>>tymczSpecjalnosc>>tymczSrednia;
            staleId=tymczId;
            student *dodawanyStudent = new student(staleId);
            dodawanyStudent->nazwisko=tymczNazwisko;
            dodawanyStudent->specjalnosc=tymczSpecjalnosc;
            dodawanyStudent->srednia=tymczSrednia;
            studenci.push_back(dodawanyStudent);
            if(dodawanyStudent->nazwisko.empty())
                throw 1;
            k++;
        }
    }
    catch (int)
    {
        cout<< "Baza jest pusta. Nastapi wyjscie z programu\n";
        exit(0);
    }
    catch(...)
    {
        cout<< "Baza jest uszkodzona i nie da sie jej wczytac. Nastapi wyjscie z programu\n";
        exit(0);
    }
    baza.close();
    cout<<"\nWczytano rekordow: "<<k<<"\nKontynuuj..."<<endl;
    int maximum=0;
    for(int i=0; i<studenci.size(); i++)
    {
        if(studenci[i]->id>maximum)
        {
            maximum=studenci[i]->id;
        }

    }
    staleId=++maximum;
    getch();
    return k;
}

void dopisz_baze(vector <student*> &studenci,string nazwa)
{
    int tymczId;
    string tymczNazwisko,tymczSpecjalnosc;
    float tymczSrednia;
    ifstream baza{nazwa,ios::in};
    while(!baza)
    {
        cerr<<"\nNie udalo sie otworzyc pliku do wczytania..."<<endl;
        cout<<"\nPodaj nazwe istniejacej bazy";
        getline(cin,nazwa);
        nazwa+=".txt";
        baza.open(nazwa,ios::in);
    }
    int k=0;

    try
    {
        while(!baza.eof())
        {
            baza>>tymczId>>tymczNazwisko>>tymczSpecjalnosc>>tymczSrednia;
            tymczId=staleId;
            student *dodawanyStudent = new student(staleId);
            dodawanyStudent->nazwisko=tymczNazwisko;
            dodawanyStudent->specjalnosc=tymczSpecjalnosc;
            dodawanyStudent->srednia=tymczSrednia;
            studenci.push_back(dodawanyStudent);
            staleId++;
            k++;
        }

    }
    catch(...)
    {
        cout<< "Baza jest uszkodzona i nie da sie jej wczytac. Nastapi wyjscie z programu\n";
        exit(0);
    }

    baza.close();
    cout<<"\nWczytano rekordow: "<<k<<"\nKontynuuj..."<<endl;
    cout<<staleId;
    getch();
}
//  bool schematSortowaniaId(student ele1, student ele2)
// {
//      return (ele1.id < ele2.id);
//  }
void sortowanie(vector <student*> &studenci, char kategoria)
{
    int zapamietaneI=0,zapamietaneJ=0,zapamietaneJMaksymalne=0;
    //  int rozmiarVectora=sizeof(studenci)/sizeof(studenci[0]);
    switch (kategoria)
    {
    case '1':
    {

        vector <int> vectorSortowany;
        for(int i=0; i<studenci.size(); i++)
        {
            int idDoWepchniecia=studenci[i]->id;
            vectorSortowany.push_back(idDoWepchniecia);
        }

        sort(vectorSortowany.begin(), vectorSortowany.end());
        for(int i=0; i<vectorSortowany.size(); i++)
        {
            for(int j=0; j<vectorSortowany.size(); j++)
                if(vectorSortowany[i]==studenci[j]->id)
                    iter_swap(studenci.begin() + i, studenci.begin() + j);
        }
        break;

    }
    case '2':
    {


        vector <string> vectorSortowany;

        for(int i=0; i<studenci.size(); i++)
        {
            string nazwiskoDoWepchniecia=studenci[i]->nazwisko;
            vectorSortowany.push_back(nazwiskoDoWepchniecia);
        }

        sort(vectorSortowany.begin(), vectorSortowany.end());
        for(int i=0; i<vectorSortowany.size(); i++)
        {
            for(int j=1; j<vectorSortowany.size(); j++)
                if(vectorSortowany[i]==studenci[j]->nazwisko)
                    iter_swap(studenci.begin() + i, studenci.begin() + j);
        }

        break;

    }
    case '3':
    {

        vector <string> vectorSortowany;
        for(int i=0; i<studenci.size(); i++)
        {
            string specjalnoscDoWepchniecia=studenci[i]->specjalnosc;
            vectorSortowany.push_back(specjalnoscDoWepchniecia);
        }

        sort(vectorSortowany.begin(), vectorSortowany.end());
        for(int i=0; i<vectorSortowany.size(); i++)
        {
            for(int j=0; j<vectorSortowany.size(); j++)
                if(vectorSortowany[i]==studenci[j]->specjalnosc)
                    iter_swap(studenci.begin() + i, studenci.begin() + j);
        }
        break;

    }
    case '4':
    {

        vector <float> vectorSortowany;
        for(int i=0; i<studenci.size(); i++)
        {
            float sredniaDoWepchniecia=studenci[i]->srednia;
            vectorSortowany.push_back(sredniaDoWepchniecia);
        }

        sort(vectorSortowany.begin(), vectorSortowany.end());
        for(int i=0; i<vectorSortowany.size(); i++)
        {
            for(int j=0; j<vectorSortowany.size(); j++)
                if(vectorSortowany[i]==studenci[j]->srednia)
                    iter_swap(studenci.begin() + i, studenci.begin() + j);
        }
        break;

    }
    }

}

void wyjatek()
{
    cout<<"Wystapil blad krytyczny, nastepuje bezpieczne zamkniecie programu z zapisem zawartosci bazy";

    ofstream baza;
    baza.open("Baza zapisana przed wystapieniem bledu.txt");
    for(int i=0; i<studenci.size(); i++)
    {
        baza<<setw(3)<<studenci[i]->id<<setw(10)<<studenci[i]->nazwisko<<setw(10)<<studenci[i]->specjalnosc<<setw(10)<<studenci[i]->srednia;
        if(i<studenci.size()-1)
            baza<<"\n";
    }
    baza.close();
    exit(0);

}

int main()
{

    char nowaStara,wybor;
    bool wczytana=false,menu=true;
    int ls;
    string nazwa;
    fstream baza(nazwa);
    set_terminate(wyjatek);

    system("cls");
    while(menu)
    {
        cout<<"Projekt Baza Danych Milosz Momot"<<endl;
        cout<<"Chce:"<<endl;
        cout<<"1.Utworzyc nowa baze"<<endl;
        cout<<"2.Uzywac istniejacej"<<endl;
        cin >> nowaStara;

        while (!cin || getchar() != '\n' || (nowaStara!='1' && nowaStara!='2') )
        {
            cout <<"Blad!!! Prosze wprowadzic numer od 1-2."<<endl<<"Kontynuuj..."<<endl;
            while (getchar() != '\n');
            cin.clear();
            cin>>nowaStara;

        }
        system ("cls");

        switch (nowaStara)
        {
        case '1':
        {
            bool odNowa=true;
            bool blad=true;
            string x;
            int wyborek;
            char error='a';
            int again=1;
            while(odNowa)
            {
                cout<<"Podaj nazwe bazy do utworzenia\n";
                getline(cin, nazwa);
                nazwa+=".txt";
                cout<<nazwa;
                baza.open(nazwa);
                x.clear();
                baza>>x;
                cout<<x;
                if(!x.empty())
                {
                    system("cls");
                    cout<<"Baza o podanej nazwie istnieje.Co chcesz zrobic?\n1.Kontynuowac dzialanie na istniejacej bazie\n2.Wpisac nowa nazwe.\n";
                    while(again==1)
                    {
                        try
                        {

                            cin>>wyborek;
                            if(!cin || getchar() != '\n')
                                throw error;
                            else
                                again=0;
                            if(wyborek!=1 && wyborek !=2)
                            {
                                cout << "Blad!!! Prosze wprowadzic numer od 1-2."<<endl;
                                again=1;
                            }
                            else
                            {
                                switch (wyborek)
                                {

                                case 1 :
                                {
                                    odNowa=false;

                                    wczytaj_baze(nazwa);

                                    break;
                                }
                                case 2 :
                                {
                                    odNowa=true;
                                    baza.close();
                                    break;
                                }

                                }
                            }
                        }
                        catch(...)
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout<<"Blad! Wpisz liczbe!!\n\n";
                        }
                    }
                }
                else
                    odNowa=false;
            }
            menu=false;
            break;

        }
        case '2':
        {
            cout<<"Podaj nazwe istniejacej bazy\n";
            getline(cin,nazwa);
            nazwa+=".txt";
            wczytaj_baze(nazwa);
            wczytana=true;
            menu=false;
            break;
        }
        default:
        {
            cin.clear();
            system("cls");
            cout << "Blad!!! Prosze wprowadzic numer od 1-2."<<endl;

        }

        }

    }
    vector <student*> kopiaVectora;
    for(int i=0; i<studenci.size(); i++)
    {
        kopiaVectora.push_back(studenci[i]);
    }
    for(;;)
    {
        system("cls");
        cout<<"Operacje na bazie: "<<nazwa<<endl;
        cout<<"Co chcesz zrobic?"<<endl;
        cout<<"1.Dodac studentow"<<endl;
        cout<<"2.Usunac studenta"<<endl;
        cout<<"3.Edytowac studenta"<<endl;
        cout<<"4.Szukaj elementu"<<endl;
        cout<<"5.Wyswietlic baze"<<endl;
        cout<<"6.Dopisz rekordy z innej bazy(powoduje nadpisanie ID!)"<<endl;
        cout<<"7.Sortuj rekordy"<<endl;
        cout<<"8.Zapisz baze"<<endl;
        cout<<"9.Cofnij zmiany w bazie"<<endl;
        cout<<"x.Zapisz i wyjdz"<<endl;

        cin>>wybor;
        while (!cin || getchar() != '\n' || (wybor!='1' && wybor!='2' && wybor!='3' && wybor!='4' && wybor!='5' && wybor!='6' && wybor!='7' && wybor!='8'&& wybor!='9' && wybor!='x'))
        {
            cout << "Blad!!! Prosze wprowadzic numer od 1-9 lub x." << endl<<"Kontynuuj..."<<endl;

            while (getchar() != '\n');
            cin.clear();
            cin>>wybor;

        }
        system ("cls");
        switch(wybor)
        {
        case '1':
        {
            char error='a';
            int again=1;
            while(again==1)
            {
                try
                {
                    cout<<"Podaj liczbe studentow\n";
                    cin>>ls;
                    if(!cin || getchar() != '\n')
                        throw error;
                    else
                        again=0;
                }
                catch(...)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout<<"Blad! Wpisz liczbe!!\n\n";
                }
            }
            system("cls");
            for(int a=0; a<ls; a++)
            {
                cout<<"Podaj dane studenta nr: "<<(a+1)<<endl;
                studenci.push_back(wprowadz());
            }
            dopiszStudentowDoPliku(ls,nazwa);

            break;
        }
        case '2':
        {
            for(int a=0; a<studenci.size(); a++)
            {
                wypiszDane(studenci[a]);
            }
            int usun;
            bool czyUsunieto=false;
            char error='a';
            int again=1;
            while(again==1)
            {
                try
                {
                    cout<<"\nPodaj ID studenta ktorego chcesz usunac\n";
                    cin>>usun;
                    if(!cin || getchar() != '\n')
                        throw error;
                    else
                        again=0;
                }
                catch(...)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout<<"\nBlad! Wpisz odpowiednie ID!!\n";
                }
            }

            for(int i=0; i<studenci.size(); i++)
            {
                if(usun==studenci[i]->id)
                {
                    studenci.erase(studenci.begin()+i);
                    czyUsunieto=true;
                    break;
                }
            }
            if(!czyUsunieto)
            {
                cout<<"\nW bazie nie istnieje student o podanym ID, nikt nie zostal usuniety\nKontynuuj...";
                getch();
            }
            else
                zapiszZawartoscBazy(nazwa);

            system ("cls");

            break;
        }
        case '3':
        {

            for(int a=0; a<studenci.size(); a++)
            {
                wypiszDane(studenci[a]);
            }

            int edytuj;
            char error='a';
            int again=1;

            while(again==1)
            {
                try
                {
                    cout<<"\nPodaj ID studenta ktorego chcesz edytowac\n";
                    cin>>edytuj;
                    if(!cin || getchar() != '\n')
                        throw error;
                    else
                        again=0;
                }
                catch(...)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout<<"\nBlad! Wpisz cyfre!!\n";
                }
            }
            bool czyEdytowano=0;
            for(int i=0; i<studenci.size(); i++)
            {
                if(edytuj==studenci[i]->id)
                {
                    student* a=studenci[i];
                    edytowanie(a);
                    czyEdytowano=1;
                }

            }
            if(czyEdytowano)
            {
                zapiszZawartoscBazy(nazwa);
                cout<<"Student zostal poprawnie edytowany\nKontynuuj...";
            }
            else
                cout<<"\nW bazie nie istnieje student o podanym ID, nikt nie zostal edytowany\nKontynuuj...";

            getch();
            system ("cls");

            break;

        }
        case '4':
        {
            system ("cls");
            char kategoria;
            bool wyszukiwanie(true);
            char error='a';
            int again=1;
            while(wyszukiwanie)
            {
                cout<<"Wedlug czego chcesz wyszukiwac??"<<endl;
                cout<<"1.Id"<<endl;
                cout<<"2.Nazwiska"<<endl;
                cout<<"3.Sredniej"<<endl;
                cout<<"4.Specjalnosci"<<endl;
                cin>>kategoria;
                while(!cin || getchar() != '\n' || (kategoria!='1' && kategoria!='2' && kategoria!='3' && kategoria!='4') )

                {
                    cout << "Blad!!! Prosze wprowadzic numer od 1-4." << endl<<"Kontynuuj..."<<endl;
                    while (getchar() != '\n');
                    cin>>kategoria;
                }
                switch(kategoria)
                {
                case '1':
                {
                    int kryterium;
                    bool czyZnaleziono=false;
                    char error='a';
                    int again=1;

                    while(again==1)
                    {
                        try
                        {
                            cout<<"\nPodaj Id, ktore chcesz znalezc...\n";
                            cin>>kryterium;
                            if(!cin || getchar() != '\n')
                                throw error;
                            else
                                again=0;
                        }
                        catch(...)
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout<<"\nBlad! Wpisz cyfre!!\n";
                        }
                    }
                    for(int j=0; j<studenci.size(); j++)
                    {
                        if(kryterium==studenci[j]->id)
                        {
                            cout<<"\nId studenta: "<<studenci[j]->id<<", Nazwisko studenta: "<<studenci[j]->nazwisko<<", Specjalnosc studenta: "<<studenci[j]->specjalnosc<<", Srednia studenta: "<<studenci[j]->srednia;
                            czyZnaleziono=true;
                            cout<<endl<<"Kontynuuj...";
                        }

                    }
                    if(!czyZnaleziono)
                        cout<<"\nW bazie nie istnieje student o podanym ID\nKontynuuj...";
                    wyszukiwanie=false;
                    break;
                }
                case '2':
                {
                    string kryterium;
                    int iloscWynikow=0;
                    cout<<"Podaj nazwisko lub poczatek szukanego nazwiska...\n";
                    cin>>kryterium;

                    for(int j=0; j<studenci.size(); j++)
                    {
                        int zgodnosc=0;
                        for(int z=0; z<kryterium.size(); z++)
                        {
                            if(kryterium[z]==studenci[j]->nazwisko[z])
                                zgodnosc++;
                            else
                                break;
                        }
                        if (zgodnosc==kryterium.size())
                        {
                            iloscWynikow++;

                            cout<<"\nId studenta: "<<studenci[j]->id<<", Nazwisko studenta: "<<studenci[j]->nazwisko<<", Specjalnosc studenta: "<<studenci[j]->specjalnosc<<", Srednia studenta: "<<studenci[j]->srednia;
                        }


                    }
                    if(iloscWynikow)
                        cout<<"\nZnaleziono: "<<iloscWynikow<<" studentow spelniajacych podane kryteria.\nKontynuuj...";
                    else
                        cout<<"\n\n\nNie znaleziono studentow spelniajacych podane kryteria.\n\nKontynuuj...";
                    wyszukiwanie=false;
                    break;
                }
                case '3':
                {
                    float kryterium;
                    int iloscWynikow=0;
                    char error='a';
                    int again=1;

                    while(again==1)
                    {
                        try
                        {
                            cout<<"\nPodaj srednia szukanego studenta...\n";
                            cin>>kryterium;
                            if(!cin || getchar() != '\n')
                                throw error;
                            else
                                again=0;
                        }
                        catch(...)
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout<<"\nBlad! Wpisz cyfre!!\n";
                        }
                    }
                    for(int j=0; j<studenci.size(); j++)
                    {

                        if (kryterium==studenci[j]->srednia)
                        {
                            cout<<"\nId studenta: "<<studenci[j]->id<<", Nazwisko studenta: "<<studenci[j]->nazwisko<<", Specjalnosc studenta: "<<studenci[j]->specjalnosc<<", Srednia studenta: "<<studenci[j]->srednia;
                            iloscWynikow++;
                        }


                    }
                    if(iloscWynikow)
                        cout<<"\nZnaleziono: "<<iloscWynikow<<" studentow spelniajacych podane kryteria.\nKontynuuj...";
                    else
                        cout<<"\nNie znaleziono studentow spelniajacych podane kryteria.\nKontynuuj...";
                    wyszukiwanie=false;
                    break;
                }
                case '4':
                {
                    string kryterium;
                    int iloscWynikow=0;
                    cout<<"Podaj specjalnosc szukanego studenta...\n";
                    cin>>kryterium;

                    for(int j=0; j<studenci.size(); j++)
                    {

                        if (kryterium==studenci[j]->specjalnosc)
                        {
                            iloscWynikow++;
                            cout<<"\nId studenta: "<<studenci[j]->id<<", Nazwisko studenta: "<<studenci[j]->nazwisko<<", Specjalnosc studenta: "<<studenci[j]->specjalnosc<<", Srednia studenta: "<<studenci[j]->srednia;
                        }
                    }
                    if(iloscWynikow)
                        cout<<"\nZnaleziono: "<<iloscWynikow<<" studentow spelniajacych podane kryteria.\nKontynuuj...";
                    else
                        cout<<"\n\n\nNie znaleziono studentow spelniajacych podane kryteria.\n\nKontynuuj...";
                    wyszukiwanie=false;
                    break;
                }
                default:
                {
                    cin.clear();

                    cout << "\nBlad!!! Prosze wprowadzic numer od 1-4.\nKontynuuj...";
                    getch();
                    system("cls");


                }

                }
            }
            getch();
            system ("cls");

            break;
        }
        case '5':
        {
            for(int a=0; a<studenci.size(); a++)
            {
                wypiszDane(studenci[a]);
            }
            cout<<"\nW bazie znajduje sie: "<<studenci.size()<<" studentow\nKontynuuj...";
            getch();

            break;
        }
        case '6':
        {
            string import;
            vector <student*> importowani;
            cout<<"Podaj nazwe bazy danych z ktorej chcesz dopisac rekordy(Id zostana podmienione)";
            getline(cin,import);
            import+=".txt";

            dopisz_baze(importowani,import);
            for(int i=0; i<importowani.size(); i++)
            {
                studenci.push_back(importowani[i]);
            }
            zapiszZawartoscBazy(nazwa);


            break;
        }
        case '7':
        {


            system ("cls");
            char kategoria;
            bool sor=true;
            char error='a';
            while(sor)
            {
                cout<<"Podaj kategorie wedlug ktorej chcesz sortowac\n";
                cout<<"1.Id"<<endl;
                cout<<"2.Nazwiska"<<endl;
                cout<<"3.Specjalnosci"<<endl;
                cout<<"4.Sredniej"<<endl;
                cin>>kategoria;
                while(!cin || getchar() != '\n' || (kategoria!='1' && kategoria!='2' && kategoria!='3' && kategoria!='4') )

                {
                    cout << "Blad!!! Prosze wprowadzic numer od 1-4." << endl<<"Kontynuuj..."<<endl;
                    while (getchar() != '\n');
                    cin>>kategoria;
                }
                switch(kategoria)
                {
                case '1':
                {
                    sortowanie(studenci,kategoria);
                    cout<<"Baza zostala posortowana wedlug id\nKontynuuj...\n";
                    sor=false;
                    break;
                }
                case '2':
                {
                    sortowanie(studenci,kategoria);
                    cout<<"Baza zostala posortowana wedlug nazwiska\nKontynuuj...\n";
                    sor=false;
                    break;
                }
                case '3':
                {
                    sortowanie(studenci,kategoria);
                    cout<<"Baza zostala posortowana wedlug specjalnosci\nKontynuuj...\n";
                    sor=false;
                    break;
                }
                case '4':
                {
                    sortowanie(studenci,kategoria);
                    cout<<"Baza zostala posortowana wedlug sredniej\nKontynuuj...\n";
                    sor=false;
                    break;
                }
                default:
                {
                    cin.clear();
                    cout << "\nBlad!!! Prosze wprowadzic numer od 1-4.\nKontynuuj...";
                    getch();
                    system("cls");
                }

                }
            }
            getch();
            system ("cls");




            break;
        }
        case '8':
        {
            cout<<"Zmiany zostaly zapisane...\nKontynuuj...";
            zapiszZawartoscBazy(nazwa);

            getch();
            break;
        }
        case '9':
        {
            cout<<"Wszelkie zmiany zostaly cofniete. Baza powraca do stanu poczatkowego...\nKontynuuj...";
            studenci.clear();
            for(int i=0; i<kopiaVectora.size(); i++)
            {
                studenci.push_back(kopiaVectora[i]);
            }
            getch();
            break;
        }
        case 'x':
        {
            cout<<"Nastepuje wyjscie z programu, wprowadzone do tej pory zmiany zostana zapisane...\nKontynuuj...";
            zapiszZawartoscBazy(nazwa);

            getch();
            exit(0);
        }
        default:
        {
            cin.clear();
            cout << "Blad!!! Prosze wprowadzic numer od 1-9 lub x.\nKontynuuj..." <<endl;
            getch();

        }
        }
    }
    return 0;
}
