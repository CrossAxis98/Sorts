#include <iostream>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <functional>

#define ROZMIAR 10000

using namespace std;

class Sortowania
{
public:
template<class typ>
void zamianaWartosci(typ *tablica, int indexPierwszego, int indexDrugiego);

template<class typ>
typ medianaTrzech(typ *tablica, int indexPierwszego, int indexOstatniego);

template<class typ>
void walidacja(typ *tablica, int rozmiarKopca, int indexKorzenia);

template<class typ>
void sortowaniePrzezKopcowanie(typ *tablica);

template <class typ>
void sortowaniePrzezWstawienie(typ *tablica, int N);

template < class typ >
int podzielNaPodtablice(typ *tablica, int i, int &j);

template<class typ>
void introSort(typ *tablica, int rozmiar, int maxGlebokosc);

template<class typ>
void sortowanieIntrospektywne(typ *tablica, int rozmiar);

template < class typ >
void quicksort(typ *tablica, int lewy, int prawy);

template< class typ>
void sortowanie_przez_scalanie(typ *tab,int lewy, int prawy);

template<class typ>
void scal(typ *tab, int lewy, int srodek, int prawy);

template<class typ>
void sprawdzSortowanie(typ * tablica);
};

template<class typ>
void Sortowania::zamianaWartosci(typ *tablica, int indexPierwszego, int indexDrugiego)
{
    //unique_ptr<typ> tmp (new typ);
    //*tmp=tablica[indexPierwszego];
    typ tmp=tablica[indexPierwszego];
    tablica[indexPierwszego]=tablica[indexDrugiego];
    tablica[indexDrugiego]=tmp;
}

template<class typ>
typ Sortowania::medianaTrzech(typ *tablica, int indexPierwszego, int indexOstatniego)
{

int indexSrodkowego=(indexPierwszego+indexOstatniego)/2;

if(tablica[indexPierwszego]>tablica[indexOstatniego])
zamianaWartosci<typ>(tablica, indexPierwszego, indexOstatniego);

if(tablica[indexPierwszego]>tablica[indexSrodkowego])
zamianaWartosci<typ>(tablica, indexPierwszego, indexSrodkowego);

if(tablica[indexSrodkowego]>tablica[indexOstatniego])
zamianaWartosci<typ>(tablica, indexSrodkowego, indexOstatniego);

return tablica[indexSrodkowego];
}

template<class typ>
void Sortowania::walidacja(typ *tablica, int rozmiarKopca, int indexKorzenia)
{
int indexMaxElementu=indexKorzenia;
int prawaGalaz=2*indexKorzenia+1;
int lewaGalaz=2*indexKorzenia+2;

if((lewaGalaz<rozmiarKopca)&&(tablica[lewaGalaz]>tablica[indexMaxElementu]))
   indexMaxElementu=lewaGalaz;

if((prawaGalaz<rozmiarKopca)&&(tablica[prawaGalaz]>tablica[indexMaxElementu]))
    indexMaxElementu=prawaGalaz;

if(indexMaxElementu!=indexKorzenia)
{
    zamianaWartosci<typ>(tablica, indexMaxElementu, indexKorzenia);
    walidacja<typ>(tablica, rozmiarKopca, indexMaxElementu);
}
}

template<class typ>
void Sortowania::sortowaniePrzezKopcowanie(typ *tablica)
{
    int rozmiarKopca=ROZMIAR;
    for(int i=(rozmiarKopca/2)-1; i>=0; i--)
    {
        walidacja<typ>(tablica, rozmiarKopca, i);
    }

    for(int j=rozmiarKopca-1; j>0; j--)
    {
        zamianaWartosci<typ>(tablica, 0, j);
        rozmiarKopca--;
        walidacja<typ>(tablica, rozmiarKopca, 0);
    }
}

template <class typ>
void Sortowania::sortowaniePrzezWstawienie(typ *tablica, int N)
{
  int i, j;
  typ temp;
  for (i=1; i<N; ++i)
  {
    temp=tablica[i];
    for (j=i; j>0 && temp<tablica[j-1]; --j)
      tablica[j]=tablica[j-1];
    tablica[j]=temp;
  }
}


template < class typ >
int Sortowania::podzielNaPodtablice(typ *tablica, int i, int &j)
{
typ pivot=tablica[(i+j)/2];
if(j>=3)
{
pivot=medianaTrzech(tablica, i, j);
}


 do
    {
        while(tablica[i]<pivot) i++;
        while(tablica[j]>pivot) j--;
        if(i<=j)
        {
        zamianaWartosci<typ>(tablica, i, j);
            i++;
            j--;
        }
    }
    while(i<=j);

    return i;
}



template<class typ>
void Sortowania::introSort(typ *tablica, int rozmiar, int maxGlebokosc)
{

int i, ostatni=rozmiar-1;
  if (maxGlebokosc<=0)
  {
    sortowaniePrzezKopcowanie(tablica);
    return;
  }

 i=podzielNaPodtablice(tablica,0,ostatni);
  if (i>9)
    introSort(tablica,i,maxGlebokosc-1);
  if (rozmiar-1-i>9)
    introSort(tablica+i+1,rozmiar-1-i,maxGlebokosc-1);
}

template<class typ>
void Sortowania::sortowanieIntrospektywne(typ *tablica, int rozmiar)
{
int maxGlebokosc=(2*log(rozmiar)/M_LN2);
introSort(tablica, rozmiar, maxGlebokosc);
sortowaniePrzezWstawienie(tablica, rozmiar);
}

template < class typ >
void Sortowania::quicksort(typ *tablica, int lewy, int prawy)
{

    int i,j;
    i=lewy;
    j=prawy;

    i=podzielNaPodtablice(tablica, i, j);

    if(j>lewy) quicksort(tablica,lewy, j);
    if(i<prawy) quicksort(tablica, i, prawy);
}

//scalenie posortowanych podtablic
template<class typ>
void Sortowania::scal(typ *tab, int lewy, int srodek, int prawy)
{
    //vector<typ> pom;

    typ pom[ROZMIAR];

    int indexLewy = lewy, indexPrawy = srodek + 1, obecnyIndex=lewy;

  //kopiujemy lewą i prawą część tablicy do tablicy pomocniczej
  for(int i = lewy;i<=prawy; i++)
    //pom.push_back(tab[i]);
    pom[i] = tab[i];

  //scalenie dwóch podtablic pomocniczych i zapisanie ich
  //we własciwej tablicy
  while((indexLewy<=srodek)&&(indexPrawy<=prawy))
  {
    if(pom[indexLewy]<=pom[indexPrawy])
    {
        tab[obecnyIndex]=pom[indexLewy];
        indexLewy++;
    }
    else
    {
        tab[obecnyIndex]=pom[indexPrawy];
        indexPrawy++;
    }
    obecnyIndex++;
  }

  while(indexLewy<=srodek)
  {
  tab[obecnyIndex]=pom[indexLewy];
  obecnyIndex++;
  indexLewy++;
  }

}

template< class typ>
void Sortowania::sortowanie_przez_scalanie(typ *tab,int lewy, int prawy)
{
    //gdy mamy jeden element, to jest on już posortowany
    if(lewy<prawy)
    {

    //znajdujemy srodek podtablicy
    int srodek = (prawy+lewy)/2;

    //dzielimy tablice na częsć lewą i prawa
    sortowanie_przez_scalanie<typ>(tab, lewy, srodek);
    sortowanie_przez_scalanie<typ>(tab, srodek+1, prawy);

    //scalamy dwie już posortowane tablice
    scal<typ>(tab, lewy, srodek, prawy);
    }
}

template <class typ>
void Sortowania::sprawdzSortowanie(typ *tablica)
{
if(ROZMIAR < 2)
{cout<<"Za maly rozmiar tablicy"<<endl;
return;
}
int licznikPoprawnychPorwownan=0;
for(int i=0; i<3; i++ )
{
int wartoscLosowa=rand()%(ROZMIAR-1)+1;
if(tablica[wartoscLosowa]>=tablica[wartoscLosowa-1])
    ++licznikPoprawnychPorwownan;
}
if(licznikPoprawnychPorwownan!=3)
    cout<<"Sortowanie nie poprawne!!"<<endl;
else
    cout<<"GIT"<<endl;
}


int main()
{

srand(time(NULL));
    int *tablica=new int [ROZMIAR];
    double cpu_time_used, calkowityCzas(0), minCzas(10), maxCzas(0);

    Sortowania testMed;

    clock_t start, endd;
for(int g=0; g<100; g++)
{
    for(int i=0; i<ROZMIAR; i++ )
    {
        tablica[i]=rand();
    }
    sort(tablica, tablica+ROZMIAR/2);

    start = clock();
    testMed.sortowanie_przez_scalanie<int>(tablica,0, ROZMIAR-1);
    endd = clock();
    cpu_time_used = ((double) (endd - start)) / CLOCKS_PER_SEC;
    calkowityCzas+=cpu_time_used;
    if(cpu_time_used<minCzas)
        minCzas=cpu_time_used;
    if(cpu_time_used>maxCzas)
        maxCzas=cpu_time_used;


}

    cout<<"CZAS Sredni MERGESORT: "<<calkowityCzas/100<<endl;
    cout<<minCzas<<endl;
    cout<<maxCzas<<endl;
    calkowityCzas=0;
    minCzas=10;
    maxCzas=0;
    for(int g=0; g<100; g++)
{
    for(int i=0; i<ROZMIAR; i++ )
    {
        tablica[i]=rand();
    }
    sort(tablica, tablica+ROZMIAR/2);
    start = clock();
    testMed.quicksort<int>(tablica,0, ROZMIAR-1);
    endd = clock();
    cpu_time_used = ((double) (endd - start)) / CLOCKS_PER_SEC;
    calkowityCzas+=cpu_time_used;
    if(cpu_time_used<minCzas)
        minCzas=cpu_time_used;
    if(cpu_time_used>maxCzas)
        maxCzas=cpu_time_used;


}

    cout<<"CZAS Sredni QUICKSORT: "<<calkowityCzas/100<<endl;
    cout<<minCzas<<endl;
    cout<<maxCzas<<endl;
    calkowityCzas=0;
    minCzas=10;
    maxCzas=0;
    for(int g=0; g<100; g++)
{
    for(int i=0; i<ROZMIAR; i++ )
    {
        tablica[i]=rand();
    }
    sort(tablica, tablica+ROZMIAR/2);

    start = clock();
    testMed.sortowanieIntrospektywne<int>(tablica, ROZMIAR);
    endd = clock();
    cpu_time_used = ((double) (endd - start)) / CLOCKS_PER_SEC;
    calkowityCzas+=cpu_time_used;
    if(cpu_time_used<minCzas)
        minCzas=cpu_time_used;
    if(cpu_time_used>maxCzas)
        maxCzas=cpu_time_used;


}
    cout<<"CZAS Sredni INTROSORT: "<<calkowityCzas/100<<endl;
    cout<<minCzas<<endl;
    cout<<maxCzas<<endl;
    delete [] tablica;
    return 0;
}
