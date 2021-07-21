
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>

#define BOSLUK 0
#define DUVAR 1
#define ADAM 8
#define HEDEF 3
#define KUTU 4
#define YERLESME 7
#define BASLANGIC 5

using namespace std;

//0: " "bo�luk	
//1: # duvar	
//3	 * kutular�n ta��naca�� hedefler
//4: + g�t�r�lecek kutular
//5: oyuncun ba�lang�� konumu
//7: o kutu yerine yerle�mesi
//8: $ oyuncu

int labirent[][20][20] =  //labirent yap�s�
{
	{
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,3,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,4,0,1,0,4,3,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,3,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,0,0,0,0,5,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,3,0,0,1,
		1,0,0,0,0,0,0,0,0,1,1,0,0,4,0,0,1,1,1,1,
		1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,4,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0,1,
		1,0,0,3,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,}

};
int adam = 0;


// Harita g�r�n�m�
void Harita()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			
			switch (labirent[adam][i][j])
			{
			case BOSLUK:
				printf(" ");	//bo�luk
				break;
			case DUVAR:
				printf("#");	//duvar
				break;
			case HEDEF:
				printf("*");	//kutular�n ta��naca�� hedefler
				break;
			case KUTU:
				printf("+");	//g�t�r�lecek kutular
				break;
			case BASLANGIC:		//oyuncunun ba�lang�� konumu
			case ADAM:			//oyuncu 
				printf("$");
				break;
			case YERLESME:
				printf("o");	//kutunun yerine yerle�mesi
				break;
			}
		}
		printf("\n");
	}
}


void KonumBilgisi() //konum bilgisi belirleniyor
{
	int i, j;
		for (i = 0; i < 20; i++)
		{
			for (j = 0; j < 20; j++)
			{
			if (labirent[adam][i][j] == BASLANGIC || labirent[adam][i][j] == ADAM)
				break;
		}
		if (labirent[adam][i][j] == BASLANGIC || labirent[adam][i][j] == ADAM)
			break;
	}

	int  secim = _getch();  //konum bilgisi al�n�yor

	switch (secim)
	{
	//y�n bilgileri	
	case 'w':   //yukar� y�n
	case 'W':   //Bo�u�a veya hedefe gitmek 
		if (labirent[adam][i-1][j] == BOSLUK || labirent[adam][i-1][j] == HEDEF)
		{   
			labirent[adam][i][j] -= BASLANGIC;
			labirent[adam][i-1][j] += BASLANGIC;
		}   
		//adam�n yan�nda kutu varsa 
		else if (labirent[adam][i-1][j] == KUTU || labirent[adam][i-1][j] == YERLESME)
		{   //kutuyu itmesini sa�l�yor
			if (labirent[adam][i-2][j] == BOSLUK || labirent[adam][i-2] [j] == HEDEF)
			{
				labirent[adam][i][j] -= BASLANGIC;//yeni adam olu�mas�n� engelliyor
				labirent[adam][i-1][j] += DUVAR;//adam�n kutuya d�nmesini engelliyor
				labirent[adam][i-2][j] += KUTU; //kutu herket ediyor ve ta��nabiliyor
			}
		}
		break;	
	case 's':   //a�a�� y�n
	case 'S':
		if (labirent[adam][i + 1][j] == BOSLUK || labirent[adam][i + 1][j] == HEDEF)
		{
			labirent[adam][i][j] -= BASLANGIC;
			labirent[adam][i + 1][j] += BASLANGIC;
		}
		else if (labirent[adam][i + 1][j] == KUTU || labirent[adam][i + 1][j] == YERLESME)
		{
			if (labirent[adam][i + 2][j] == BOSLUK || labirent[adam][i + 2][j] == HEDEF)
			{
				labirent[adam][i][j] -= BASLANGIC;
				labirent[adam][i + 1][j] += DUVAR;
				labirent[adam][i + 2][j] += KUTU;
			}
		}
		break;
	case 'a':  //Sol y�n
	case 'A':	
		if (labirent[adam][i][j - 1] == BOSLUK || labirent[adam][i][j - 1] == HEDEF)
		{
			labirent[adam][i][j] -= BASLANGIC;
			labirent[adam][i][j - 1] += BASLANGIC;
		}
		else if (labirent[adam][i][j - 1] == KUTU || labirent[adam][i][j - 1] == YERLESME)
		{
			if (labirent[adam][i][j - 2] == BOSLUK || labirent[adam][i][j - 2] == HEDEF)
			{
				labirent[adam][i][j] -= BASLANGIC;
				labirent[adam][i][j - 1] += DUVAR;
				labirent[adam][i][j - 2] += KUTU;
			}
		}
		break;
	case 'd':   //sa� y�n
	case 'D':
		if (labirent[adam][i][j + 1] == BOSLUK || labirent[adam][i][j + 1] == HEDEF)
		{
			labirent[adam][i][j] -= BASLANGIC;
			labirent[adam][i][j + 1] += BASLANGIC;
		}
		else if (labirent[adam][i][j + 1] == KUTU || labirent[adam][i][j + 1] == YERLESME)
		{
			if (labirent[adam][i][j + 2] == BOSLUK || labirent[adam][i][j + 2] == HEDEF)
			{
				labirent[adam][i][j] -= BASLANGIC;
				labirent[adam][i][j + 1] += DUVAR;
				labirent[adam][i][j + 2] += KUTU;
			}
		}
		break;
	}

}
int OyunSonu()
{
	int count = 0;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (labirent[adam][i][j] == YERLESME)
				count++;
		}
	}
	return count;
}
int box[] = { 0 };

void GetBox(int n)
{
	for (int i = 0; i < n; i++)
	{
		int n_box = 0;
		for (int j = 0; j < 20; j++)
		{
			for (int k = 0; k < 20; k++)
			{
				switch (labirent[i][j][k])
				{
				case KUTU:
					n_box++;
				}
			}
		}
		box[i] = n_box;		//Seviye ba��na kutu say�s�

	}
}



int main()
{
	int n = sizeof(labirent) / sizeof(labirent[0]);
	GetBox(n);
	while (1)
	{
		printf("--ABDULKADIR YILMAZ--\n---SOKOBAN OYUNU---\n", adam + 1);
		Harita();
		if (OyunSonu() == box[adam])
		{
			adam++;
			if (adam == n)
				break;
		}
		KonumBilgisi();
		system("cls"); //ekran� temizliyor
	}
	printf("TEBRIKLER \n");
	system("pause");
	return 0;
}
