#include "drzewo.hh"
#include<iostream>
#include <cstdlib>

using namespace std;

string cr,cl,cp;      // łańcuchy do znaków ramek

// Metoda wypisuje drzewo
// kod zaczerpniety ze strony internetowej http://eduinf.waw.pl/inf/alg/001_search/0115.php
void Drzewo::printBT(string sp, string sn, ED* v)
{

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
  if(wezel->lewy != NULL) // jesli lewy syn istnieje (w sumie lewy wnuk pierwtnego wezla)
    wezel->lewy->ojciec = wezel; //to ustaw mu nowego ojca
  
  nowy->prawy = wezel; 
  nowy->ojciec = rodzic; 
  wezel->ojciec = nowy;
  
  if(rodzic!=NULL){ // jesli wezel nie byl korzeniem
    if(rodzic->lewy == wezel)
      rodzic->lewy = nowy;
    else
      rodzic = rodzic->prawy = nowy;
  }
  else //jesli byl korzeniem
    korzen = nowy; 

  //ustawiamy wspolczynniki rownowagi ;)
    wezel->wsprownowagi = Wysokosc(wezel->lewy)-Wysokosc(wezel->prawy);
    nowy->wsprownowagi = Wysokosc(nowy->lewy)-Wysokosc(nowy->prawy);
    
  return nowy;
}


// rotacja wezlow polaczonych prawymi galeziami, symetrycznie do LL
ED* Drzewo::RotujRR(ED* wezel){
  ED* nowy = wezel->prawy;
  ED* rodzic = wezel->ojciec;

  wezel->prawy = nowy->lewy;
  
  if(wezel->prawy!=NULL) //jesli prawy syn istnieje (czyli w sumie prawy wnuk pierwotnego wezla)
    wezel->prawy->ojciec = wezel; //to przyporzadkuj ojca
  
  nowy->lewy = wezel;
  nowy->ojciec = rodzic;
  wezel->ojciec = nowy;
  
  if(rodzic != NULL){ //jesli wezel nie byl korzeniem
    if(rodzic->lewy == wezel)
      rodzic->lewy = nowy;
    else
      rodzic->prawy = nowy;
  }
  else //jesli byl korzeniem
    korzen = nowy;

  // i ustawiamy wspolczynniki rownowagi
  wezel->wsprownowagi = Wysokosc(wezel->lewy)-Wysokosc(wezel->prawy);
  nowy->wsprownowagi = Wysokosc(nowy->lewy)-Wysokosc(nowy->prawy);
  return nowy;
}


//podwojna rotacja prawo-lewo
ED* Drzewo::RotujRL(ED* wezel){
  ED* nowy;
  wezel->prawy=RotujLL(wezel->prawy);
  nowy=RotujRR(wezel);
  return nowy;
}

//podwojna rotacja lewo-prawo
ED* Drzewo::RotujLR(ED* wezel){
  ED* nowy;
  wezel->lewy = RotujRR(wezel->lewy); // najpierw rotacja lewa, zeby przygotowac grunt do prawej
  nowy = RotujLL(wezel); // i mozna zrotowac LL
  return nowy;
}

bool Drzewo::Dodaj(int element){
  ED* nowy=new ED;
  ED* ojciec=NULL;
  ED* aktualny=korzen; //do przejscia po drzewie

  //ustawiamy wartosci nowego elementu, bedzie lisciem, wiec wsprownowagi=0
  nowy->wartosc=element; 
  nowy->lewy=NULL;
  nowy->prawy=NULL;
  nowy->wsprownowagi=0;

  //szukamy czy taki element jest juz w drzewie
  while(aktualny!=NULL){ //jesli jestesmy jeszcze w drzewie
    if(element==aktualny->wartosc){
      delete nowy;
      return false; //jesli jest juz taki
    }
    else{ //jesli nie ma elementu w drzewie, to szukamy gdzie go wstawic
      ojciec=aktualny;
      if(element<aktualny->wartosc)
	aktualny=aktualny->lewy;
      else
	aktualny=aktualny->prawy;
    }
  }//koniec while

  nowy->ojciec=ojciec; //ojciec wskazuje gdzie go mozna wsadzic
  if(ojciec==0){ //jesli drzewo jest puste
    korzen=nowy;
    return true; // i mamy jednoelementowe drzewko ;)
  }
  else{ //a jesli drzewo nie bylo puste...
    if(element<ojciec->wartosc) // to w zaleznosci od wartosci wpisz nowy w miejsce syna
      ojciec->lewy=nowy;
    else
      ojciec->prawy=nowy;

    if(ojciec->wsprownowagi!=0){ // jesli ojciec mial jednego syna
      ojciec->wsprownowagi=0; // to juz ma dwoch
      return true; // czyli sukces!
    }
    else{// gdy ojciec mial wsprownowagi==0
      if(ojciec->lewy==nowy) // to w zaleznosci ktorym synem jest nowy
	ojciec->wsprownowagi=1;
      else
	ojciec->wsprownowagi=-1;

      aktualny=ojciec;
      ojciec=ojciec->ojciec;

      while(ojciec!=NULL){ //przeszukujemy drzzewo w poszuiwaniu niezrownowazonych wezlow
	if(ojciec->wsprownowagi!=0){
	  if(ojciec->wsprownowagi==-1){//przewaza prawa galaz
	    if(ojciec->lewy==aktualny){ // i do lewej wpisalismy
	      ojciec->wsprownowagi=0; // to juz jest rownowaga ;)
	      return true; //czyli wszystko gra!
	    }
	    else{//a jesli polaczenie jest z prawej
	      if(aktualny->wsprownowagi==1) // i w nowym przewaza lewa
		RotujRL(ojciec); //to rotujemy prawa-lewa
	      else// jesli w nowym przewaza prawa
		RotujRR(ojciec); // to rotujemy prawa-prawa
	      return true; //i znow sukces 
	    }
	  }//if(ojciec->wsprownowagi==-1)
	  else{// wsprownowagi ojca==1, czyli przewaza lewa galaz
	    if(ojciec->prawy==aktualny){ // wpisalismy do prawej?
	      ojciec->wsprownowagi=0; // to rownowaga!
	      return true;// i sukces
	    }
	    else{// wspisalismy po lewej?
	      if(aktualny->wsprownowagi==-1) // przewaza prawa?
		RotujLR(ojciec); // polaczenie lewa-prawa
	      else // przewaza lewa?
		RotujLL(ojciec); // polaczenie lewa-lewa
	      return true; // i tez pasuje ;)
	    }//else
	  }//else
	}// koniec if(ojciec->wsprownowagi!=0)
	else{// jesli wsp rownowagi ojca ==0
	  ojciec->wsprownowagi=Wysokosc(ojciec->lewy)-Wysokosc(ojciec->prawy);// to ustaw mu wysokosc

	  // i przygotuj warunki do kolejnego obrotu petli
	  aktualny=ojciec;
	  ojciec=ojciec->ojciec;
	}
      }//koniec while
      return true; // wszystko sie udalo!!!
    }
  }  
}

//Rekurencyjnie wylicza wysokosc 
int Drzewo::Wysokosc(ED* wezel){
  int wysokosc;
  if(wezel==NULL) //jesli wezel nie istnieje...
    return 0;
  if(wezel->lewy==NULL && wezel->prawy==NULL) // jesli obaj synowie nie istnieja
    return 1;
  else if(wezel->lewy==NULL||wezel->prawy==NULL) //jesli nie istnieje tylko jeden z synow
    return 2;
  else // a jak istnieja oboje
    wysokosc=max(Wysokosc(wezel->lewy), Wysokosc(wezel->prawy))+1; // to wyliczamy rekurencyjnie, bierzemy wieksza wartosc i dodajemy 1 
  return wysokosc;
}


int Drzewo::Korzen(){
  return korzen->wartosc;
}


ED* Drzewo::Poprzednik(ED* wezel){ //wezel o najwiekszej mozliwej wartosci, mniejszej od wezel->wartosc
  ED* pomocniczy;

  if(wezel!=NULL){ // jesli wezel istnieje
    if(wezel->lewy!=NULL){ // i jego lewy syn tez
      wezel = wezel->lewy;
      while(wezel->prawy!=NULL)
	wezel=wezel->prawy;
    }//koniec if
    else // jesli wezel nie istnieje
      do{
        pomocniczy=wezel;
        wezel=wezel->ojciec;
      } while(wezel!=NULL && wezel->prawy!=pomocniczy);
  }//koniec if
  return wezel; 
}

//szuka elementu o danej wartosci w drzewie
ED* Drzewo::Znajdz(int element){
  ED* wezel=korzen;
  
  while(wezel!=NULL){ // jesli wezel na cokolwiek wskazuje
    if(wezel->wartosc!=element){ // to nie szukany?
      if(element<wezel->wartosc) // jak szukamy mniejszej to na lewo
	wezel=wezel->lewy;
      else // jak wiekszej to na prawo
	wezel=wezel->prawy;
    }
    else // znalezlismy czego szukalismy!
      return wezel;
  }//koniec while
  return NULL;// nie bylo takiej wartosci? 
}


//metoda powstala dzieki pomocy http://eduinf.waw.pl/inf/alg/001_search/0119.php#P2
ED* Drzewo::Usun(ED* wezel)
{
  ED  *A,*B,*C;
  bool zagniezdzenie;

  if(wezel->lewy!=NULL && wezel->prawy!=NULL){ //jesli istnieja oboje synowie
    B=Usun(Poprzednik(wezel));
    zagniezdzenie=false;
  }//koniec if
  else{
    if(wezel->lewy!=NULL){
      B=wezel->lewy;
      wezel->lewy=NULL;
    }
    else{
      B=wezel->prawy;
      wezel->prawy=NULL;
    }
    wezel->wsprownowagi=0;
    zagniezdzenie=true;
  }//koniec else

  if(B!=NULL){
    B->ojciec=wezel->ojciec;
    B->lewy=wezel->lewy;

    if(B->lewy!=NULL)
      B->lewy->ojciec=B;

    B->prawy=wezel->prawy;

    if(B->prawy!=NULL)
      B->prawy->ojciec=B;
    
    B->wsprownowagi=wezel->wsprownowagi;
  }//koniec if

  if(wezel->ojciec!=NULL) {
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
    while(B!=NULL){
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
  if(Znajdz(element)==false) //jesli taki element juz jest w drzewie
    return NULL;
  return Usun(Znajdz(element));// i jesli nie ma jestvze takiego
}

//zwraca najwieksza wartosc na drzewie
int Drzewo::Najwiekszy(){
  ED* pomocniczy=korzen;

  while(pomocniczy->prawy!=NULL) // zawsze w prawo, dopoki sie tylko da
    pomocniczy=pomocniczy->prawy;
  return pomocniczy->wartosc;
}

//zwraca najmniejsza wartosc na drzewie
int Drzewo::Najmniejszy(){
  ED* pomocniczy=korzen;

  while(pomocniczy->lewy!=NULL) // zawsze w lewo, o ile sie tylko da
    pomocniczy=pomocniczy->lewy;
  return pomocniczy->wartosc;
}


//rekurencyjne przejscie Preorder przez drzewo
void Drzewo::Preorder(ED* wezel){
  if(wezel!=NULL){ //jesli wezel istnieje
    cout<<wezel->wartosc<<", "; //odwiedzamy wezel
    Preorder(wezel->lewy); // przechodzimy lewe poddrzewo
    Preorder(wezel->prawy); // przechodzimy prawe poddrzewo
  }
}

//rekurencyjne przejscie Postorder przez drzewo
void Drzewo::Postorder(ED* wezel){
  if(wezel!=NULL){
    if(wezel->lewy!=NULL) //jesli lewy istnieje
      Postorder(wezel->lewy); //przechodzimy lewe poddrzewo
    if(wezel->prawy!=0) //jeslli prawy
      Postorder(wezel->prawy); // przechodzimy prawe poddrzewo
    cout<<wezel->wartosc<<", "; // o odwiedzamy wezel 
  }
}

// rekurencyjne przejscie Inorder
void Drzewo::Inorder(ED* wezel){
  if(wezel!=NULL){ // jesli wezel nie wskazuje na pustke
    if(wezel->lewy!=0) //jesli ma lewego syna
      Inorder(wezel->lewy); // to przechodzimy lewe poddrzewo
    cout<<wezel->wartosc<<", "; // odwiedzamy wezel
    if(wezel->prawy!=0) //jesli prawego
      Inorder(wezel->prawy);
  } // i przechodzimy prawe poddrzewo
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
  cout<<"*           10 - sprawdz wysokosc drzewa                                  *"<<endl;
  cout<<"*           11 - sprawdz, co jest w korzeniu                              *"<<endl;
  cout<<"*           12 - usun drzewo                                              *"<<endl;
  cout<<"*                                                                         *"<<endl;
  cout<<"*            0 - koniec                                                   *"<<endl;
  cout<<"*                                                                         *"<<endl;
  cout<<"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"<<endl;
}

void Drzewo::Obsluz(){
  int wybor=193; //cokolwiek, tylko nie 0
  int element;
  ED* pomocniczy;

  cr = cl = cp = "  ";
  cr[0] = 218; cr[1] = 196;
  cl[0] = 192; cl[1] = 196;
  cp[0] = 179;
  WyswietlMenu();

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
      if(korzen==NULL)
	cout<<"Drzewo jest puste!"<<endl;
      else
      cout<<"Najwiekszy element drzewa:   "<<Najwiekszy()<<endl;
      break;
    case 5://min
      if(korzen==NULL)
	cout<<"Drzewo jest puste!"<<endl;
      else
      cout<<"Najmniejszy element drzewa:  "<<Najmniejszy()<<endl;
      break;
    case 6://zawartosc
      pomocniczy=korzen;
      if(pomocniczy!=NULL)
	printBT(" ", " ", pomocniczy);
      else
	cout<<"Drzewo puste!"<<endl;
      break;
    case 7://preorder
      if(korzen==NULL)
	cout<<"Drzewo jest puste!"<<endl;
      else{
      pomocniczy=korzen;
      Preorder(pomocniczy);
      }
      break;
    case 8://postorder
      if(korzen==NULL)
	cout<<"Drzewo jest puste!"<<endl;
      else{
      pomocniczy=korzen;
      Postorder(pomocniczy);
      }
      break;
    case 9: //inorder
      if(korzen==NULL)
	cout<<"Drzewo jest puste!"<<endl;
      else{
      pomocniczy=korzen;
      Inorder(pomocniczy);
      }
      break;
    case 0: //koniec
      break;
    case 10: //wysokosc
      pomocniczy=korzen;
      if(pomocniczy!=NULL)
	cout<<"Wysokosc drzewa:   "<<Wysokosc(pomocniczy)<<endl;
      else
	cout<<"Drzewo jest puste!"<<endl;
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

//testy na drzewie
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
