// SPDalgorytmNEH.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "job.h"

using namespace std;


int cmax(int** tab, int prace, int maszyny)
{
    int czas;
    prace++;
    maszyny++;
    int** cmaxTab = new int* [prace];
    for (int i = 0; i < prace; i++)
    {
        cmaxTab[i] = new int[maszyny];
    }

    for (int i = 0; i < prace; i++)
    {
        cmaxTab[i][0] = 0;
    }
    for (int i = 0; i < maszyny; i++)
    {
        cmaxTab[0][i] = 0;
    }
    for (int i = 1; i < prace; i++)
    {
        for (int j = 1; j < maszyny; j++)
        {
            cmaxTab[i][j] = max(cmaxTab[i-1][j], cmaxTab[i][j-1]) + tab[i-1][j-1];
        }
    }
    

    czas = cmaxTab[prace-1][maszyny-1];

    for (int i = 0; i < prace; i++)
        delete[] cmaxTab[i];

    delete[] cmaxTab;
    return czas;
}


int NEH(int** tab, int prace, int maszyny)
{
    int min=99999999999;
    int currCmax;
    int suma = 0;
    int index;
    int wielkosc = 0;
    int currentIndex;
    int swapNumber=0;
    int bestSwapNumber=0;
    
    
    vector<job> jobs;
    // inicjalizacja tablicy wynikowej
    int** resultTab = new int* [prace];
    for (int i = 0; i < prace; i++)
    {
        resultTab[i] = new int[maszyny];
    }

    // liczenie sumy
    for (int i = 0; i < prace; i++)
    {     
        for (int j = 0; j < maszyny; j++)
        {
            suma += tab[i][j];
        }
        job temp;
        temp.index = i;
        temp.sum = suma;
        jobs.push_back(temp);
        suma = 0;    
    }
    //sortowanie sum 
    sort(jobs.begin(), jobs.end());

    index = jobs.back().index;
    jobs.pop_back();

    if (wielkosc == 0)
    {
        resultTab[0] = tab[index];
        wielkosc = 2;
    }

    for (int i = 1; i < wielkosc; i++)
    {
        index = jobs.back().index;
        jobs.pop_back();
        resultTab[i] = tab[index];

        bestSwapNumber = 0;
        min = 9999999999;
        // sprawdzenie cmax po dodaniu elementu na koniec tablicy
        currCmax = cmax(resultTab, wielkosc, maszyny);
        if (currCmax < min) min = currCmax;

        // szukanie najmniejszego cmax po kazdym swapie
        for (int j = wielkosc - 1; j > 0; j--)
        {
            swap(resultTab[j], resultTab[j - 1]);
            swapNumber++;
            currCmax = cmax(resultTab, wielkosc, maszyny);
            if (currCmax < min)
            {
                min = currCmax;
                bestSwapNumber = swapNumber;
            }
        }
        
        // cofanie swapów do najlepszego
        for (int k = 1; k <= (swapNumber - bestSwapNumber); k++)
        {
            swap(resultTab[k], resultTab[k - 1]);
        }
        /*
        for (int i = 0; i < wielkosc; i++)
        {
            for (int j = 0; j < maszyny; j++)
            {
                cout << resultTab[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        */
        swapNumber = 0;
        wielkosc++;
        if (wielkosc > prace) break;
    }
   
    // wyswietlenie tablicy wynikowej
    for (int i = 0; i < prace; i++)
    {
        for (int j = 0; j < maszyny; j++)
        {
            cout << resultTab[i][j]<< " ";
        }
        cout << endl;
    }
    
    for (int i = 0; i < prace ; i++)
        delete[] resultTab[i];

    delete[] resultTab;
    return min;
}


int main()
{
    ifstream stream("neh.data.txt");  // Otwarcie pliku do odczytu

    if (!stream)
    {
        cout << "BŁĄD: nie można otworzyć pliku do odczytu." << endl;
    }

    string text; // nazwa danych
    int prace;
    int maszyny;
   // while (!stream.eof())
    //{
        stream >> text;
        cout << text << endl;
        stream >> prace;
        stream >> maszyny;
        string linia;
        double czas;

        int** tab = new int * [prace];
        for (int i = 0; i < prace; i++)
        {
            tab[i] = new int[maszyny];
            for (int j = 0; j < maszyny; j++)
            {
                stream >> tab[i][j];
            }
        }
        cout << "wynik:" << NEH(tab,prace,maszyny)<<endl;
        stream >> linia;
        //cout << linia << endl;
        stream >> czas;
        //cout << czas << endl;
        for (int i = 0; i < prace; i++)
        {
            stream >> linia;
        }
        
        // tu wywala
        for (int i = 0; i < prace; i++)
            delete[] tab[i];

        delete[] tab;
        
        
        
   // }
    


   
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
