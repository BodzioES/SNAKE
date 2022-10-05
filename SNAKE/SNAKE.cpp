#include <iostream>
#include <conio.h> //funkcja klawiszy ruchu :)
#include <cstdlib> //system CLS
#include <time.h>//generator losowania
#include <windows.h>//funckja Sleep() czyli czekanie przed kolejnym krokiem


using namespace std;

int szerokosc, wysokosc, szybkosc;
int gora, dol, lewo, prawo;
int wspolzednaXweza, wspolzednaYweza;
int wspolzednaXjedzenia, wspolzednaYjedzenia;
int dl = 3, historiaWspolzednejX[10000],historiaWspolzednejY[10000];
int ile = 0;
int klawisz;
char waz = 219, jedzenie = 177;
char pd = 188, pg = 187, ld =200, lg = 201, poz = 205, pion = 186;
char kierunek = 'p'; //p prawo l lewo g gora d dol
char pole[30][30]; //przechowuje wartosci ktore nie sa tylko liczbami

// to sprawia ze ekran nie migota jak najebany
void idzdoxy(int x, int y)
{
	HANDLE hCon;
	COORD dwPos;
	
	dwPos.X=x;
	dwPos.Y=y;
	
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon, dwPos);
}

int blad(int &x)
{
    cout << "Prosze podaj liczbe od 5 do 30" << endl;
    cout << "Wybierz jeszcze raz: " << endl;
    cout << "Jesli nie wybierzesz poprawnej liczby to gra wybierze automatycznie za ciebie :)" <<endl;
    cin >> x;
    if(x < 5 || x > 30) x = 15;
}

int main()
{
    cout << "Podaj szerokosc planszy od 5 do 30:" << endl;
    cin >> szerokosc;
    if(szerokosc < 5 || szerokosc > 30) blad(szerokosc);

    cout << "Podaj wysokosc planszy od 5 do 30:" << endl;
    cin >> wysokosc;
    if(wysokosc < 5 || wysokosc > 30) blad(wysokosc);

    cout << "Podaj szybkosc od 1 do 10" <<endl;
    cin >> szybkosc;
    if(szybkosc < 1) szybkosc = 1;
    if(szybkosc > 10) szybkosc = 10;

    cout << "Nacisnij kalwisze ktorymi chcesz zagrac" << endl;
    
    cout << "GORA";
    gora  = getch();
	if(gora == 224)gora += getch();
    if(gora == 0)gora -= getch();

    cout << "DOL";
    dol  = getch();
    if(dol == 224)dol += getch();
    if(dol == 0)dol -= getch();

    cout << "LEWO";
    lewo  = getch();
    if(lewo == 224)lewo += getch();
    if(lewo == 0)lewo -= getch();

    cout << "PRAWO";
    prawo  = getch();
    if(prawo == 224)prawo += getch();
    if(prawo == 0)prawo -= getch();

	for(int i = 0 ; i < wysokosc ; i++)
	{
		for(int j = 0 ; j < szerokosc ; j++)
		{
			pole[j][i] = 'p';
		}
	}
	srand(time(NULL)); //generator losowania
	//losowanie pola dla weza
	wspolzednaXweza = rand()%szerokosc;
	wspolzednaYweza = rand()%wysokosc;
	
	pole[wspolzednaXweza][wspolzednaYweza] = 'w';
	
	//losowanie pola dla jedzonka
	do{ 
	wspolzednaXjedzenia = rand()%szerokosc;
	wspolzednaYjedzenia = rand()%wysokosc;
	}
	while(pole[wspolzednaXjedzenia][wspolzednaYjedzenia] !='p');
	
	pole[wspolzednaXjedzenia][wspolzednaYjedzenia] = 'j';

	system("cls"); //oczyszczanie ekranu
	//rozpoczecie gry
	
	idzdoxy(0,0); //wraca na poczatek
		cout << lg;
    	for(int i=0; i<szerokosc ; i++)
    	{
        	cout << poz << poz; 
    	}
    	cout << pg;

    	for(int i=0; i<=wysokosc; i++)
    	{
        	cout << endl << pion;
        	for(int j = 0; j < szerokosc ;j++)
        	{
            	if(pole[j][i] =='p') cout << "  "; //pole
            	if(pole[j][i] =='w') cout << waz << waz; //waz
            	if(pole[j][i] =='j') cout << jedzenie << jedzenie; //jedzenie
        	}
        	cout  << pion;
        
    	}

    	cout << endl;
		
		cout << ld;
    	for(int i=0; i<szerokosc ; i++)
    	{
        	cout << poz << poz; 
    	}
    	cout << pd;
	
	for(;;)
	{
		ile++;
		historiaWspolzednejX[ile] = wspolzednaXweza;
		historiaWspolzednejY[ile] = wspolzednaYweza;
		
    	Sleep(1000 / szybkosc); //czekanie przed krokiem
    	if(kbhit()) //jesli zostanie nacisniety przycisk
    	{
    		klawisz = getch();
			if(klawisz == 224)klawisz+=	getch();
			if(klawisz == 0)klawisz-=getch();
			
			if(klawisz == gora && (kierunek == 'l' || kierunek == 'p'))kierunek = 'g';
			if(klawisz == dol && (kierunek == 'l' || kierunek == 'p'))kierunek = 'd';
			if(klawisz == lewo && (kierunek == 'g' || kierunek == 'd'))kierunek = 'l';
			if(klawisz == prawo && (kierunek == 'g' || kierunek == 'd'))kierunek = 'p';
			
		}
    	
    	if(kierunek == 'd')wspolzednaYweza++;
    	if(kierunek == 'g')wspolzednaYweza--;
    	if(kierunek == 'l')wspolzednaXweza--;
    	if(kierunek == 'p')wspolzednaXweza++;
    	
    	//przechodzenie przez sciany
    	if(wspolzednaXweza == szerokosc) wspolzednaXweza = 0;
    	if(wspolzednaXweza == -1) wspolzednaXweza = szerokosc -1;
    	if(wspolzednaYweza == wysokosc) wspolzednaYweza = 0;
    	if(wspolzednaYweza == -1) wspolzednaYweza = wysokosc -1;
    	
    	//jesli dotknie siebie
    	if(pole[wspolzednaXweza][wspolzednaYweza] == 'w')
    	{
    		idzdoxy(0,wysokosc + 4);
    		cout << endl << "\aKoniec gry      dlugosc - " << dl + 1;
			break;
		}
    	
    	//jesli zje jedzenie
    	if(pole[wspolzednaXweza][wspolzednaYweza] == 'j')
    	{
    		dl++;
    		do{ 
				wspolzednaXjedzenia = rand()%szerokosc;
				wspolzednaYjedzenia = rand()%wysokosc;
				} while(pole[wspolzednaXjedzenia][wspolzednaYjedzenia] !='p');
				
			pole[wspolzednaXjedzenia][wspolzednaYjedzenia] = 'j';
			idzdoxy(wspolzednaXjedzenia*2+1,wspolzednaYjedzenia+1);
			cout << jedzenie << jedzenie;
		}
    	else //kasowanie ogonka w sensie zeby ten ogon nie byl nieskonczony
    		{
			pole[historiaWspolzednejX[ile - dl]][historiaWspolzednejY[ile - dl]] = 'p';
			idzdoxy(historiaWspolzednejX[ile - dl]*2+1,historiaWspolzednejY[ile - dl]+1);
			cout << "  ";
			}
			
		pole[wspolzednaXweza][wspolzednaYweza] = 'w';
		idzdoxy(wspolzednaXweza*2+1,wspolzednaYweza+1);
		cout << waz << waz;
	}
		
	getch();
	

    return 0;
}