#include <iostream>
#include <string>

#ifndef drzewo_hh
#define drzewo_hh

using namespace std;

struct ED{
  ED* lewy;
  ED* prawy;
  ED* ojciec;
  int wartosc;
  int wsprownowagi;
};

class Drzewo{
public:
  //atrybuty:
  ED* korzen;
  
  //metody:
  Drzewo(){korzen=0;}; //konstruktor

  void WyswietlMenu();
  void Obsluz();
  ED* Znajdz(int element); //jest
  ED* Poprzednik(ED* wezel);
  void printBT(string sp, string sn, ED* v); //zapozyczone
  ED* RotujLL(ED* wezel);     // jest
  ED* RotujRR(ED* wezel);     // jest
  ED* RotujRL(ED* wezel);     // jest
  ED* RotujLR(ED* wezel);     // jest
  bool Dodaj(int element);    // chyba ok
  ED* Usun(ED* wezel);     // chyba jest
  ED* Usun(int element);   //chyba tez
  int Wysokosc(ED* wezel);  //
  int Korzen();               // jest
  int Najwiekszy();           // jest
  int Najmniejszy();           //jest

  void Preorder(ED* wezel);
  void Postorder(ED* wezel);
  void Inorder(ED* wezel);

  void Test111();
  void Test112();
  void Test113();
};


#endif
