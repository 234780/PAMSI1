#include "drzewo.hh"
#include<iostream>
#include <cstdlib>

using namespace std;

string cr,cl,cp;      // łańcuchy do znaków ramek

// Metoda wypisuje drzewo
// kod zaczerpniety ze strony internetowej http://eduinf.waw.pl/inf/alg/001_search/0115.php
void Drzewo::printBT(string sp, string sn, ED* v)
{
  cr = cl = cp = "  ";
  cr[0] = 218; cr[1] = 196;
  cl[0] = 192; cl[1] = 196;
  cp[0] = 179;
  string s;

  if(v)
  {
    s = sp;
    if(sn == cr) s[s.length() - 2] = ' ';
    printBT(s + cp, cr, v->prawy);

    s = s.substr(0,sp.length()-2);
    cout << s << sn << v->wartosc << ":" << v->wsprownowagi << endl;

    s = sp;
    if(sn == cl) s[s.length() - 2] = ' ';
    printBT(s + cp, cl, v->lewy);
  }
}


//rotacja wezlow polaczonych lewymi galeziami
ED* Drzewo::RotujLL(ED* wezel){
  ED* nowy = wezel->lewy;
  ED* rodzic = wezel->ojciec;

  wezel->lewy = nowy->prawy;
  if(wezel->lewy != 0)
    wezel->lewy->ojciec = wezel;
  nowy->prawy = wezel;
  nowy->ojciec = rodzic;
  wezel->ojciec = nowy;
  if(rodzic!=0){
    if(rodzic->lewy == wezel)
      rodzic->lewy = nowy;
    else
      rodzic = rodzic->prawy = nowy;
  }
  else korzen = nowy;

  if(nowy->wsprownowagi == 1){ //jesli bylo 1
    wezel->wsprownowagi = 0;
    nowy->wsprownowagi = 0;
  }
  else{
    wezel->wsprownowagi = 1; 
    nowy->wsprownowagi = -1;
  }
  return nowy;
}


// rotacja wezlow polaczonych prawymi galeziami, symetrycznie do LL
ED* Drzewo::RotujRR(ED* wezel){
  ED* nowy = wezel->prawy;
  ED* rodzic = wezel->ojciec;

  wezel->prawy = nowy->lewy;
  
  if(wezel->prawy!=0)
    wezel->prawy->ojciec = wezel;
  nowy->lewy = wezel;
  nowy->ojciec=rodzic;
  wezel->ojciec = nowy;
  if(rodzic != 0){
    if(rodzic->lewy == wezel)
      rodzic->lewy = nowy;
    else
      rodzic->prawy = nowy;
  }//koniec if(rodzic!=0)
  else korzen = nowy;

  if(nowy->wsprownowagi == -1){
    wezel->wsprownowagi = 0;
    nowy->wsprownowagi = 0;
  }
  else{
    wezel->wsprownowagi = -1;
    nowy->wsprownowagi = 1;
  }
  return nowy;
}


//podwojna rotacja 
ED* Drzewo::RotujRL(ED* wezel){
  ED* pomocniczy = wezel->prawy;
  ED* nowy = pomocniczy->lewy;
  ED* rodzic = wezel->ojciec;

  pomocniczy->lewy = nowy->prawy;
  if(pomocniczy->lewy != 0) //jesli istnieje lewy syn
    pomocniczy->lewy->ojciec = pomocniczy;
  
  wezel->prawy = nowy->lewy;
  if(wezel->prawy != 0) // jesli istnieje prawy syn
    wezel->prawy->ojciec = wezel; //to ustaw odpowiedniego ojca
  nowy->lewy = wezel;
  nowy->prawy = pomocniczy;
  wezel->ojciec = pomocniczy->ojciec = nowy;
  nowy->ojciec = rodzic;
  if(rodzic!=0){ //jesli wezel nie jest korzeniem
    if(rodzic->lewy == wezel)
      rodzic->lewy = nowy;
    else
      rodzic->prawy = nowy;
  }
  else
    korzen = nowy; //jesli jest juz korzeniem

  if(nowy->wsprownowagi == -1)
    wezel->wsprownowagi = 1;
  else
    wezel->wsprownowagi = 0;

  if(nowy->wsprownowagi == 1)
    pomocniczy->wsprownowagi = -1;
  else
    pomocniczy->wsprownowagi = 0;
 
  nowy->wsprownowagi = 0;

  return nowy;
}

ED* Drzewo::RotujLR(ED* wezel){
  ED* pomocniczy = wezel->lewy;
  ED* nowy = pomocniczy->prawy;
  ED* rodzic = wezel->ojciec;

  pomocniczy->prawy = nowy->lewy;
  if(pomocniczy->prawy!=0)
    pomocniczy->prawy->ojciec = pomocniczy;
  
  wezel->lewy = nowy->prawy;
  if(wezel->lewy!=0)
    wezel->lewy->ojciec = wezel;
  
  nowy->prawy = wezel;
  nowy->lewy = pomocniczy;
  wezel->ojciec = pomocniczy->ojciec = nowy;
  nowy->ojciec = rodzic;
  if(rodzic != 0){ //jesli rodzic istnieje
    if(rodzic->lewy == wezel)
      rodzic->lewy = nowy;
    else
      rodzic->prawy = nowy;
  }//koniec if(rodzic!=0)
  else
    korzen = nowy; //ustaw jako korzen

  
  if(nowy->wsprownowagi == 1)
    wezel->wsprownowagi = -1;
  else
    wezel->wsprownowagi = 0;

  if(nowy->wsprownowagi == -1)
    pomocniczy->wsprownowagi = 1;
  else
    pomocniczy->wsprownowagi = 0;
 
  nowy->wsprownowagi = 0;
  return nowy;
}

bool Drzewo::Dodaj(int element){
  ED* nowy=new ED;
  ED* ojciec=0;
  ED* aktualny=korzen;

  nowy->wartosc=element;
  nowy->lewy=0;
  nowy->prawy=0;
  nowy->wsprownowagi=0;

  while(aktualny!=0){ //jesli jestesmy jeszcze w drzewie
    if(element==aktualny->wartosc){
      delete nowy;
      return false;
    }
    else{
      ojciec=aktualny;
      if(element<aktualny->wartosc)
	aktualny=aktualny->lewy;
      else
	aktualny=aktualny->prawy;
    }
  }//koniec while

  nowy->ojciec=ojciec;
  if(ojciec==0){ //jesli drzewo jest puste
    korzen=nowy;
    return true;
  }
  else{
    if(element<ojciec->wartosc)
      ojciec->lewy=nowy;
    else
      ojciec->prawy=nowy;

    if(ojciec->wsprownowagi!=0){
      ojciec->wsprownowagi=0;
      return true;
    }
    else{
      if(ojciec->lewy==nowy)
	ojciec->wsprownowagi=1;
      else
	ojciec->wsprownowagi=-1;

      aktualny=ojciec;
      ojciec=ojciec->ojciec;

      while(ojciec!=0){ //przeszukujemy drzzewo
	if(ojciec->wsprownowagi!=0){
	  if(ojciec->wsprownowagi==-1){
	    if(ojciec->lewy==aktualny){
	      ojciec->wsprownowagi=0;
	      return true;
	    }
	    else{
	      if(aktualny->wsprownowagi==1)
		RotujRL(ojciec);
	      else
		RotujRR(ojciec);
	      return true;
	    }
	  }
	  else{
	    if(ojciec->prawy==aktualny){
	      ojciec->wsprownowagi=0;
	      return true;
	    }
	    else{
	      if(aktualny->wsprownowagi==-1)
		RotujLR(ojciec);
	      else
		RotujLL(ojciec);
	      return true;
	    }
	  }
	}
	else{
	  if(ojciec->lewy==aktualny)
	    ojciec->wsprownowagi=1;
	  else
	    ojciec->wsprownowagi=-1;

	  aktualny=ojciec;
	  ojciec=ojciec->ojciec;
	}
      }//koniec while
      return true;
    }

  }
    
}

int Drzewo::Wysokosc(ED* wezel){
  int wysokosc;
  if(wezel->lewy==0 && wezel->prawy==0)
    return 1;
  else if(wezel->lewy==0||wezel->prawy==0)
    return 2;
  else
  wysokosc=max(Wysokosc(wezel->lewy), Wysokosc(wezel->prawy))+1;
  return wysokosc;
}

int Drzewo::Korzen(){
  return korzen->wartosc;
}


ED* Drzewo::Poprzednik(ED* wezel){ //wezel o najwiekszej mozliwej wartosci, mniejszej od wezel->wartosc
  ED* pomocniczy;

  if(wezel!=0){
    if(wezel->lewy!=0){
      wezel = wezel->lewy;
      while(wezel->prawy!=0)
	wezel=wezel->prawy;
    }//koniec if
    else
      do{
        pomocniczy=wezel;
        wezel=wezel->ojciec;
      } while(wezel!=0 && wezel->prawy!=pomocniczy);
  }//koniec if
  return wezel;
}

ED* Drzewo::Znajdz(int element){
  ED* wezel=korzen;
  
  while(wezel!=0){
    if(wezel->wartosc!=element){
      if(element<wezel->wartosc)
	wezel=wezel->lewy;
      else
	wezel=wezel->prawy;
    }
    else
      return wezel;
  }//koniec while
  return 0;
}


ED* Drzewo::Usun(ED* wezel)
{
  ED  *A,*B,*C;
  bool zagniezdzenie;

  if(wezel->lewy!=0 && wezel->prawy!=0){ //jesli istnieja oboje synowie
    B=Usun(Poprzednik(wezel));
    zagniezdzenie=false;
  }//koniec if
  else{
    if(wezel->lewy!=0){
      B=wezel->lewy;
      wezel->lewy=0;
    }
    else{
      B=wezel->prawy;
      wezel->prawy=0;
    }
    wezel->wsprownowagi=0;
    zagniezdzenie=true;
  }//koniec else

  if(B!=0){
    B->ojciec=wezel->ojciec;
    B->lewy=wezel->lewy;

    if(B->lewy!=0)
      B->lewy->ojciec=B;

    B->prawy=wezel->prawy;

    if(B->prawy!=0)
      B->prawy->ojciec=B;
    
    B->wsprownowagi=wezel->wsprownowagi;
  }//koniec if

  if(wezel->ojciec!=0) {
    if(wezel->ojciec->lewy==wezel)
      wezel->ojciec->lewy=B;
    else
      wezel->ojciec->prawy=B;
  }//koniec if
  else
    korzen=B;

  if(zagniezdzenie!=0){
    C=B;
    B=wezel->ojciec;
    while(B!=0){
      if(B->wsprownowagi==0){              // Przypadek nr 1
        if(B->lewy==C)
	  B->wsprownowagi=-1;
	else B->wsprownowagi=1;
        break;
      }
      else{
        if(((B->wsprownowagi==1) && (B->lewy==C)) || ((B->wsprownowagi==-1) && (B->prawy==C))){           // Przypadek nr 2
          B->wsprownowagi=0;
          C=B;
	  B=B->ojciec;
        }
        else{
          if(B->lewy==C)
	    A=B->prawy;
	  else A=B->lewy;
	  
          if(A->wsprownowagi==0){         // Przypadek 3A
            if(B->wsprownowagi==1)
	      RotujLL(B);
	    else
	      RotujRR(B);
            break;
          }//koniec if
	  
          else if(B->wsprownowagi==A->wsprownowagi){         // Przypadek 3B
            if(B->wsprownowagi==1)
	      RotujLL(B);
	    else
	      RotujRR(B);
	    
            C = A;
	    B = A->ojciec;
          }
          else{         // Przypadek 3C
            if(B->wsprownowagi==1)
	      RotujLR(B);
	    else
	      RotujRL(B);

	    C=B->ojciec;
	    B=C->ojciec;
          }//koniec else
        }//koniec else
      }//koniec else
    }//koniec while
  }//koniec if 
  return wezel;
}

ED* Drzewo::Usun(int element){
  if(Znajdz(element)==false)
    return 0;
  return Usun(Znajdz(element));
}

int Drzewo::Najwiekszy(){
  ED* pomocniczy=korzen;

  while(pomocniczy->prawy!=0)
    pomocniczy=pomocniczy->prawy;
  return pomocniczy->wartosc;
}

int Drzewo::Najmniejszy(){
  ED* pomocniczy=korzen;

  while(pomocniczy->lewy!=0)
    pomocniczy=pomocniczy->lewy;
  return pomocniczy->wartosc;
}

void Drzewo::Preorder(ED* wezel){
  if(wezel!=0){ //jesli wezel istnieje
    cout<<wezel->wartosc<<", ";
    Preorder(wezel->lewy); //przejscie rekurencyjne
    Preorder(wezel->prawy);
  }
}

void Drzewo::Postorder(ED* wezel){
  if(wezel!=0){
    if(wezel->lewy!=0) //jesli lewy istnieje
      Postorder(wezel->lewy);
    if(wezel->prawy!=0) //jeslli prawy
      Postorder(wezel->prawy);
    cout<<wezel->wartosc<<", ";
  }
}

void Drzewo::Inorder(ED* wezel){
  if(wezel!=0){
    if(wezel->lewy!=0) //jesli ma lewego syna
      Inorder(wezel->lewy);
    cout<<wezel->wartosc<<", ";
    if(wezel->prawy!=0) //jesli prawego
      Inorder(wezel->prawy);}
}

void Drzewo::WyswietlMenu(){
  cout<<"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"<<endl;
  cout<<"*                               DRZEWO AVL                                *"<<endl;
  cout<<"*                                                                         *"<<endl;
  cout<<"*            1 - dodaj wezel                                              *"<<endl;
  cout<<"*            2 - usun wezel                                               *"<<endl;
  cout<<"*            3 - sprawdz istnienie wezla                                  *"<<endl;
  cout<<"*            4 - wezel o najwiekszej wartosci                             *"<<endl;
  cout<<"*            5 - wezel o najmniejszej wartosci                            *"<<endl;
  cout<<"*            6 - wyswietl zawartosc drzewa                                *"<<endl;
  cout<<"*                                                                         *"<<endl;
  cout<<"*            7 - preorder                                                 *"<<endl;
  cout<<"*            8 - postorder                                                *"<<endl;
  cout<<"*            9 - inorder                                                  *"<<endl;
  cout<<"*                                                                         *"<<endl;
  cout<<"*           10 - sprawdz wysokosz drzewa                                  *"<<endl;
  cout<<"*           11 - sprawdz, co jest w korzeniu                              *"<<endl;
  cout<<"*                                                                         *"<<endl;
  cout<<"*            0 - koniec                                                   *"<<endl;
  cout<<"*                                                                         *"<<endl;
  cout<<"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"<<endl;
}

void Drzewo::Obsluz(){
  int wybor=193; //cokolwiek, tylko nie 0
  int element;
  ED* pomocniczy;
  WyswietlMenu();

  cr[0] = 218; cr[1] = 196;
  cl[0] = 192; cl[1] = 196;
  cp[0] = 179;


  while(wybor!=0){
    cout<<"Twoj wybor:   "<<endl;
    cin>>wybor;
    
    switch(wybor){

    case 1: //dodaj
      cout<<"Podaj wartosc elementu, ktory ma zostac dodany do drzewa:   ";
      cin>>element;
      if(Dodaj(element)==false)
	cout<<"Podany element istnieje juz na drzewie!"<<endl;
      break;
    case 2: //usun
      cout<<"Podaj wartosc elementu, ktory ma zostac usuniety z drzewa:   ";
      cin>>element;
      if(Znajdz(element)==false)
	cout<<"Element o zadanej wartosci nie istnieje w drzewie!"<<endl;
      else
	Usun(element);
      break;
    case 3://sprawdz istnienie
      cout<<"Podaj wartosc elementu, ktory ma byc znaleziony w drzewie:   ";
      cin>>element;
      if(Znajdz(element)!=0) //jesli istnieje
	cout<<"Element istnieje!"<<endl;
      else
	cout<<"Brak szukanego elementu"<<endl;
      break;
    case 4://max
      cout<<"Najwiekszy element drzewa:   "<<Najwiekszy()<<endl;
      break;
    case 5://min
      cout<<"Najmniejszy element drzewa:  "<<Najmniejszy()<<endl;
      break;
    case 6://zawartosc
      pomocniczy=korzen;
      if(pomocniczy!=0)
	printBT(" ", " ", pomocniczy);
      else
	cout<<"Drzewo puste!"<<endl;
      break;
    case 7://preorder
      pomocniczy=korzen;
      Preorder(pomocniczy);
      break;
    case 8://postorder
      cout<<"Chwilowo nie ma :("<<endl;
      break;
    case 9: //inorder
      cout<<"Chwilowo nie ma :("<<endl;
      break;
    case 0: //koniec
      break;
    case 10: //wysokosc
      pomocniczy=korzen;
      cout<<"Wysokosc drzewa:   "<<Wysokosc(pomocniczy)<<endl;
      break;
    case 11: //wartosc w korzeniu
      if(korzen!=0)
	cout<<"Wartosc w korzeniu drzewa:   "<<korzen->wartosc<<endl;
      else
	cout<<"Drzewo jest puste!"<<endl;
      break;
    case 111:
      Test111();
      break;
    case 112:
      Test112();
      break;
    case 113:
      Test113();
      break;
    default:
      cout<<"Nie rozpoznano."<<endl;
    }//koniec switch
  }//koniec while
  
}


void Drzewo::Test111(){
  int ilosc=40;
  int tablicawartosci[40];
  int indeks1, indeks2;
  int i;
  int pomoc;
  ED* pomocniczy;

  srand(time(NULL)); //generator pseudolosowy
  
  for(i=0; i<ilosc; i++){
    tablicawartosci[i]=i;
  }

  for(i=0; i<100; i++){ // 100 mieszan
    indeks1=rand()%ilosc; //losujemy dwa indeksy
    indeks2=rand()%ilosc;
    pomoc=tablicawartosci[indeks1];
    tablicawartosci[indeks1]=tablicawartosci[indeks2]; //zamieniamy
    tablicawartosci[indeks2]=pomoc;
  }

  //wstawiamy w drzewo
  for(i=0; i<ilosc; i++){
    Dodaj(tablicawartosci[i]);
  }
  for(i=0;i<ilosc; i++){ //usuwamy co 4 element
    if(i%4==0){
      Usun(tablicawartosci[i]);
    }
  }
    // i testujemy...
    pomocniczy=korzen;
    printBT(" "," ", pomocniczy);
    pomocniczy=korzen;
    cout<<"Wysokosc drzewa: "<<Wysokosc(pomocniczy)<<endl;
    cout<<"Wartosc w korzeniu: "<<Korzen()<<endl;
    cout<<"Najwieksza wartosc na drzewie: "<<Najwiekszy()<<endl;
    cout<<"Najmniejsza wartosc na drzewie: "<<Najmniejszy()<<endl;
    
  cout<<endl;
  pomocniczy=korzen;
  cout<<"PRE-ORDER"<<endl;
  Preorder(pomocniczy);
  cout<<endl<<endl<<"IN-ORDER"<<endl;
  pomocniczy=korzen;
  Inorder(pomocniczy);
  cout<<endl<<endl<<"POST-ORDER"<<endl;
  pomocniczy=korzen;
  Postorder(pomocniczy);
  cout<<endl;
  }
  
void Drzewo::Test112(){
int ilosc=100000;
  int tablicawartosci[100000];
  int indeks1, indeks2;
  int i;
  int pomoc;
  ED* pomocniczy;

  srand(time(NULL)); //generator pseudolosowy
  
  for(i=0; i<ilosc; i++){
    tablicawartosci[i]=i;
  }

  for(i=0; i<1000000; i++){ // 1000000 mieszan
    indeks1=rand()%ilosc; //losujemy dwa indeksy
    indeks2=rand()%ilosc;
    pomoc=tablicawartosci[indeks1];
    tablicawartosci[indeks1]=tablicawartosci[indeks2]; //zamieniamy
    tablicawartosci[indeks2]=pomoc;
  }

  //wstawiamy w drzewo
  for(i=0; i<ilosc; i++){
    Dodaj(tablicawartosci[i]);
  }
    // i testujemy...

    pomocniczy=korzen;
    cout<<"Wysokosc drzewa: "<<Wysokosc(pomocniczy)<<endl;
    cout<<"Wartosc w korzeniu: "<<Korzen()<<endl;
    cout<<"Najwieksza wartosc na drzewie: "<<Najwiekszy()<<endl;
    cout<<"Najmniejsza wartosc na drzewie: "<<Najmniejszy()<<endl;
    
    //cout<<endl;
    //pomocniczy=korzen;
    //cout<<"PRE-ORDER"<<endl;
    //Preorder(pomocniczy);
    //cout<<endl<<endl<<"IN-ORDER"<<endl;
    //pomocniczy=korzen;
    //Inorder(pomocniczy);
    //cout<<endl<<endl<<"POST-ORDER"<<endl;
    //pomocniczy=korzen;
    //Postorder(pomocniczy);
    //cout<<endl;
}

void Drzewo::Test113(){
  long int ilosc=1000000;
  long int tablicawartosci[1000000];
  int indeks1, indeks2;
  long int i;
  int pomoc;
  ED* pomocniczy;

  srand(time(NULL)); //generator pseudolosowy
  
  for(i=0; i<ilosc; i++){
    tablicawartosci[i]=i;
  }

  for(i=0; i<100000; i++){ // 1000000000 mieszan
    indeks1=rand()%ilosc; //losujemy dwa indeksy
    indeks2=rand()%ilosc;
    pomoc=tablicawartosci[indeks1];
    tablicawartosci[indeks1]=tablicawartosci[indeks2]; //zamieniamy
    tablicawartosci[indeks2]=pomoc;
  }

  //wstawiamy w drzewo
  for(i=0; i<ilosc; i++){
    Dodaj(tablicawartosci[i]);
  }
 
    // i testujemy...
    pomocniczy=korzen;
    cout<<"Wysokosc drzewa: "<<Wysokosc(pomocniczy)<<endl;
    cout<<"Wartosc w korzeniu: "<<Korzen()<<endl;
    cout<<"Najwieksza wartosc na drzewie: "<<Najwiekszy()<<endl;
    cout<<"Najmniejsza wartosc na drzewie: "<<Najmniejszy()<<endl;
    
    //cout<<endl;
    //pomocniczy=korzen;
    //cout<<"PRE-ORDER"<<endl;
    //Preorder(pomocniczy);
    //cout<<endl<<endl<<"IN-ORDER"<<endl;
    //pomocniczy=korzen;
    //Inorder(pomocniczy);
    //cout<<endl<<endl<<"POST-ORDER"<<endl;
    //pomocniczy=korzen;
    //Postorder(pomocniczy);
    //   cout<<endl;
}
