
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

//0: " "boþluk	
//1: # duvar	
//3	 * kutularýn taþýnacaðý hedefler
//4: + götürülecek kutular
//5: oyuncun baþlangýç konumu
//7: o kutu yerine yerleþmesi
//8: $ oyuncu

int labirent[][20][20] =  //labirent yapýsý
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


// Harita görünümü
void Harita()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			
			switch (labirent[adam][i][j])
			{
			case BOSLUK:
				printf(" ");	//boþluk
				break;
			case DUVAR:
				printf("#");	//duvar
				break;
			case HEDEF:
				printf("*");	//kutularýn taþýnacaðý hedefler
				break;
			case KUTU:
				printf("+");	//götürülecek kutular
				break;
			case BASLANGIC:		//oyuncunun baþlangýç konumu
			case ADAM:			//oyuncu 
				printf("$");
				break;
			case YERLESME:
				printf("o");	//kutunun yerine yerleþmesi
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

	int  secim = _getch();  //konum bilgisi alýnýyor

	switch (secim)
	{
	//yön bilgileri	
	case 'w':   //yukarý yön
	case 'W':   //Boþuða veya hedefe gitmek 
		if (labirent[adam][i-1][j] == BOSLUK || labirent[adam][i-1][j] == HEDEF)
		{   
			labirent[adam][i][j] -= BASLANGIC;
			labirent[adam][i-1][j] += BASLANGIC;
		}   
		//adamýn yanýnda kutu varsa 
		else if (labirent[adam][i-1][j] == KUTU || labirent[adam][i-1][j] == YERLESME)
		{   //kutuyu itmesini saðlýyor
			if (labirent[adam][i-2][j] == BOSLUK || labirent[adam][i-2] [j] == HEDEF)
			{
				labirent[adam][i][j] -= BASLANGIC;//yeni adam oluþmasýný engelliyor
				labirent[adam][i-1][j] += DUVAR;//adamýn kutuya dönmesini engelliyor
				labirent[adam][i-2][j] += KUTU; //kutu herket ediyor ve taþýnabiliyor
			}
		}
		break;	
	case 's':   //aþaðý yön
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
	case 'a':  //Sol yön
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
	case 'd':   //sað yön
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
		box[i] = n_box;		//Seviye baþýna kutu sayýsý

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
		system("cls"); //ekraný temizliyor
	}
	printf("TEBRIKLER \n");
	system("pause");
	return 0;
}
