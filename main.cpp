#include "drzewo.hh"
#include <iostream>
#include <time.h>

using namespace std;

int main(){
  time_t start, koniec;
  Drzewo drzewo;
  int i;
  ED* pomocniczy;
  int ilosc=38000000;

  time(&start);
  
  for (i=0; i<ilosc; i++)
    drzewo.Dodaj(i);

  for (i=0; i<ilosc; i++)
    if(i%4==0)
      drzewo.Usun(i);

  pomocniczy=drzewo.korzen;
  drzewo.printBT(" "," ", pomocniczy);
  pomocniczy=drzewo.korzen;
  drzewo.Wysokosc(pomocniczy);
  drzewo.Korzen();
  drzewo.Najwiekszy();
  drzewo.Najmniejszy();

  cout<<endl;
  pomocniczy=drzewo.korzen;
  drzewo.Preorder(pomocniczy);
  cout<<endl;
  pomocniczy=drzewo.korzen;
  drzewo.Inorder(pomocniczy);
  cout<<endl;
  pomocniczy=drzewo.korzen;
  drzewo.Postorder(pomocniczy);
  cout<<endl;
  //drzewo.Obsluz();

  time (&koniec);

    cout<<"Calosc zajela:   "<<difftime(koniec, start)<<"sekund"<<endl;
  return 1;
}
