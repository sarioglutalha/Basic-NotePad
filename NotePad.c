#include <stdio.h>
#include <conio.h>
#include "graphics.h"
#define STR 70
int h = 540, i=0;
char str_cumle[70], cumle[300][70];
char kopya_str_cumle[70], kopya_cumle[300][70];
int harf = 0, toplam_harf = 0, konum_y = 20, konum_x = 20, toplam_str = 0, mevcut_str = 0;
int a, b, c;
void yazdir()   //IMLEC
{
	int y = 20;
	for (int i = 0; i <= toplam_str; i++)
	{
		outtextxy(20, y, cumle[i]);
		y += 20;
	}
	line(konum_x, konum_y, konum_x, konum_y + 20);
}
int main()
{
	int secim, dil;
	char dosya_adi[20];
	FILE *iter;
	char ch, ch2;

	initwindow(640, 480);
	settextstyle(2, 0, 7);
	outtextxy(280, 100, "iEDIT");                                       //
	outtextxy(170, 190, "MOST POPULAR TEXT EDITOR");                    //        GIRIS EKRANI
	outtextxy(190, 220, "PRESS 'ENTER' TO START");                      //        SHOW MUST GO ON
	outtextxy(200, 250, "PRESS ANY KEY TO EXIT");                         //
	ch2 = getch();                                                      //
	if (ch2 == 13)  closegraph();                                       //       EKRANI KAPAMA
	else  exit(0);                                            //      CIKIS

																		// DIL SECYMY
	printf("\t1.English\n\t2.Turkish\n\tDil seciniz: ");
	scanf("%d", &dil);
	switch (dil)
	{
	case 1:
		printf("\n\tiEdit \t\t\t\t\tMOST POPULAR TEXT EDITOR");
		printf("\n\n\tMENU:\n\t\n ");
		printf("\n\t1.CREATE\n\t2.DISPLAY\n\t3.APPEND\n\t4.EXIT\n");
		printf("\n\tEnter your choice: ");
		scanf("%d", &secim);
		break;

	case 2:
		printf("\n\tiEdit \t\t\t\t\tEN POPULAR METIN EDITORU");
		printf("\n\n\tMENU:\n\t\n ");
		printf("\n\t1.YENI\n\t2.GORUNTULE\n\t3.DEGISTIR\n\t4.CIKIS\n");
		printf("\n\tSecimizi yapiniz: ");
		scanf("%d", &secim);
		break;
	}

	// ISLEM SECIMI
	switch (secim)
	{
	case 4:
		exit(0);
		break;

	case 3:     // DUZENLEME
	{
		printf("\n\tDosya ismini giriniz: ");
		scanf("%s", dosya_adi);
		int s = 0;
		iter = fopen(dosya_adi, "r");
		if (iter == NULL)
		{
			printf("\n\tDosya bulunamadi!");
			goto end2;
		}
		while (!feof(iter))
		{
			fscanf(iter, "%s", cumle[s]);
			s++;
		}
	end2:
		initwindow(875, 540, "okuma");
		toplam_str = s;
		settextstyle(8, 0, 2);
		setcolor(BLACK);
		bar(0, 0, 875, 540);
		setbkcolor(WHITE);
		yazdir();
		fclose(iter);
		int the_end = 0;
		do
		{
			setcolor(BLACK);
			bar(0, 0, 875, 540);
			setbkcolor(WHITE);
			yazdir();
			ch = getch();
			switch (ch)
			{
			case 1:     ///CTRL-A
				for (int i = 0; i<toplam_str; i++) {
					strcpy(kopya_cumle[i], cumle[i]);
				}
				break;

			case 3:     ///CTRL-C
				for (int i = 0; i<toplam_str; i++) {
					strcpy(kopya_cumle[i], cumle[i]);
				}
				break;

			case 22:    ///CTRL-V
				for (int i = 0; i <= toplam_str; i++)
				{
					outtextxy(konum_x, konum_y, kopya_cumle[i]);
				}
				getch();
				break;

			case 24:    ///CTRL-X
				for (int i = 0; i <= toplam_str; i++)
				{
					strcpy(kopya_cumle[i], cumle[i]);
					strcpy(cumle[i], " ");
				}
				break;
			case 8: //BACKSPACE
				if (harf>0)
				{
					if (harf<strlen(str_cumle))
					{
						toplam_harf = strlen(str_cumle);
						for (int i = harf; i <= toplam_harf; i++)
						{
							str_cumle[i - 1] = str_cumle[i];
						}
						harf--;
						konum_x = 20 + 12 * harf;
					}
					else
					{
						harf--;
						konum_x -= 12;
						str_cumle[harf] = '\0';
					}
				}
				else if (mevcut_str == 0) {}
				else
				{
					if (mevcut_str == toplam_str)
					{
						strcat(cumle[mevcut_str - 1], str_cumle);
						harf = strlen(cumle[mevcut_str - 1]);
						mevcut_str--;
						toplam_str--;
						strcpy(str_cumle, cumle[mevcut_str]);
						konum_x = 20 + 12 * harf;
						konum_y -= 20;
					}
					else
					{
						for (int i = mevcut_str; i <= toplam_str; i++)
						{
							strcpy(cumle[i], cumle[i + 1]);
						}
						strcpy(str_cumle, cumle[mevcut_str - 1]);
						mevcut_str--;
						toplam_str--;
						harf = strlen(str_cumle);
						konum_x = 20 + 12 * harf;
						konum_y -= 20;
					}
				}
				break;

			case 13:    /// ENTER TUSU
				if (toplam_str >= 23)
				{
					h += 20;
					closegraph();
					initwindow(875, h, "okuma");
					settextstyle(8, 0, 2);
					setcolor(BLACK);
					bar(0, 0, 875, h);
					setbkcolor(WHITE);
				}
				if (harf == strlen(cumle[mevcut_str]))
				{
					if (mevcut_str<toplam_str)
					{
						for (int i = toplam_str; i>mevcut_str; i--)
						{
							strcpy(cumle[i + 1], cumle[i]);
						}
						mevcut_str++;
						toplam_str++;
						konum_y += 20;
						konum_x = 20;
						str_cumle[0] = '\0';
						harf = 0;
					}
					else
					{
						mevcut_str++;
						toplam_str++;
						harf = 0;
						str_cumle[harf] = '\0';
						konum_y += 20;
						konum_x = 20;
					}
				}
				else
				{
					for (int i = toplam_str; i>mevcut_str; i--)
					{
						strcpy(cumle[i + 1], cumle[i]);
					}
					for (int i = harf, sayac = 0; i <= strlen(cumle[mevcut_str]); i++)
					{
						str_cumle[sayac] = cumle[mevcut_str][i];
						sayac++;
						str_cumle[sayac] = '\0';
					}
					cumle[mevcut_str][harf] = '\0';
					strcpy(cumle[mevcut_str + 1], str_cumle);
					strcpy(str_cumle, cumle[mevcut_str + 1]);
					harf = 0;
					mevcut_str++;
					toplam_str++;
					konum_y += 20;
					konum_x = 20;
				}
				harf = 0;
				break;

			case 75:    ///SOL TUSU
				if (harf>0)
				{
					harf = harf - 1;
					konum_x -= 12;
				}
				else if (mevcut_str != 0)
				{
					mevcut_str--;
					harf = strlen(cumle[mevcut_str]);
					konum_x = 20 + harf * 12;
					konum_y -= 20;
					strcpy(str_cumle, cumle[mevcut_str]);
				}
				continue;
				break;

			case 0x4d:  ///SAG TUSU
				if (harf<strlen(str_cumle))
				{
					harf++;
					konum_x += 12;
					strcpy(str_cumle, cumle[mevcut_str]);
				}
				else if (toplam_str != mevcut_str)
				{
					mevcut_str++;
					harf = 0;
					strcpy(str_cumle, cumle[mevcut_str]);
					konum_x = 20;
					konum_y += 20;
				}
				continue;
				break;

			case 0x50:  /// ALT TUSU
				if (mevcut_str<toplam_str)
				{
					mevcut_str++;
					strcpy(str_cumle, cumle[mevcut_str]);
					if (harf>strlen(str_cumle))
					{
						harf = strlen(str_cumle);
					}
					konum_y += 20;
					konum_x = 20 + 12 * harf;
				}
				continue;
				break;

			case 0x48:   //UST TUSU
				if (mevcut_str != 0)
				{
					mevcut_str--;
					strcpy(str_cumle, cumle[mevcut_str]);
					if (harf>strlen(str_cumle))
					{
						harf = strlen(str_cumle);
					}
					konum_y -= 20;
					konum_x = 20 + 12 * harf;
				}
				break;

			case 27:    // ESC
				closegraph();
				printf("\n\tDosya ismini giriniz...");
				scanf("%s", dosya_adi);
				iter = fopen(dosya_adi, "w");
				for (int m = 0; m <= toplam_str; m++)
				{
					fprintf(iter, "%s\n", cumle[m]);
				}
				fclose(iter);
				the_end = 1;
				break;

			default:
				if (ch != 224 && ch != 0)
				{
					if (harf < STR - 1)
					{
						toplam_harf = strlen(cumle[mevcut_str]);
						if (toplam_harf != harf)
						{
							for (int i = toplam_harf; i >= harf; i--)
							{
								str_cumle[i + 1] = str_cumle[i];
							}
							str_cumle[harf] = ch;
							harf++;
							konum_x += 12;
							str_cumle[toplam_harf + 1] = '\0';
						}
						else
						{
							str_cumle[harf] = ch;
							harf++;
							konum_x += 12;
							str_cumle[harf] = '\0';
						}
					}
					else
					{
						mevcut_str++;
						konum_y += 20;
						konum_x = 20;
						konum_x += 12;
						toplam_str++;
						harf = 0;
						str_cumle[harf] = ch;
						harf++;
						str_cumle[harf] = '\0';
					}
				}
				break;
			}
			strcpy(cumle[mevcut_str], str_cumle);
		} while (!the_end);

		break;
	}

	case 2:      /// GORUNTULEME
	{
		printf("\n\tDosya ismini giriniz: ");
		scanf("%s", dosya_adi);
		int s = 0;
		iter = fopen(dosya_adi, "r");
		if (iter == NULL)
		{
			printf("\n\tDosya bulunamadi!");
			goto end1;
		}
		while (!feof(iter))
		{
			fscanf(iter, "%s", cumle[s]);
			s++;
		}
	end1:
		initwindow(875, 540, "okuma");
		toplam_str = s;
		settextstyle(8, 0, 2);
		setcolor(BLACK);
		bar(0, 0, 875, 540);
		setbkcolor(WHITE);
		yazdir();
		fclose(iter);
		break;
	}

	case 1:     /// YAZMA
	{
		initwindow(875, 540, "deneme");
		settextstyle(8, 0, 2);
		int the_end = 0;
		do
		{
			setcolor(BLACK);
			bar(0, 0, 875, 540);
			setbkcolor(WHITE);
			yazdir();
			ch = getch();
			b = mevcut_str;
			c = harf;
			switch (ch)
			{
			case 1:     ///CTRL-A
				for(int i=0; i<toplam_str; i++) {
					strcpy(kopya_cumle[i], cumle[i]);
				}
				break;

			case 3:     ///CTRL-C
				for (int i = 0; i<toplam_str; i++) {
					strcpy(kopya_cumle[i], cumle[i]);
				}
				break;

			case 22:    ///CTRL-V
				for (int i = 0; i <= toplam_str; i++)
				{
					outtextxy(konum_x, konum_y, kopya_cumle[i]);
				}
				getch();
				break;

			case 24:    ///CTRL-X
				for (int i = 0; i <= toplam_str; i++)
				{
					strcpy(kopya_cumle[i], cumle[i]);
					strcpy(cumle[i], " ");
				}
				break;

			case 8: ///BACKSPACE:
				if (harf>0)
				{
					if (harf<strlen(str_cumle))
					{
						toplam_harf = strlen(str_cumle);
						for (int i = harf; i <= toplam_harf; i++)    str_cumle[i - 1] = str_cumle[i];
						harf--;
						konum_x = 20 + 12 * harf;
					}
					else
					{
						harf--;
						konum_x -= 12;
						str_cumle[harf] = '\0';
					}
				}
				else if (mevcut_str == 0) {}
				else
				{
					if (mevcut_str == toplam_str)
					{
						strcat(cumle[mevcut_str - 1], str_cumle);
						harf = strlen(cumle[mevcut_str - 1]);
						mevcut_str--;
						toplam_str--;
						strcpy(str_cumle, cumle[mevcut_str]);
						konum_x = 20 + 12 * harf;
						konum_y -= 20;
					}
					else
					{
						for (int i = mevcut_str; i <= toplam_str; i++)   strcpy(cumle[i], cumle[i + 1]);
						strcpy(str_cumle, cumle[mevcut_str - 1]);
						mevcut_str--;
						toplam_str--;
						harf = strlen(str_cumle);
						konum_x = 20 + 12 * harf;
						konum_y -= 20;
					}

				}
				break;

			case 13:    /// ENTER TUSU:
				if (toplam_str >= 23)
				{
					h += 20;
					closegraph();
					initwindow(875, h, "okuma");
					settextstyle(8, 0, 2);
					setcolor(BLACK);
					bar(0, 0, 875, h);
					setbkcolor(WHITE);
				}
				if (harf == strlen(cumle[mevcut_str]))
				{
					if (mevcut_str<toplam_str)
					{
						for (int i = toplam_str; i>mevcut_str; i--)    strcpy(cumle[i + 1], cumle[i]);
						mevcut_str++;
						toplam_str++;
						konum_y += 20;
						konum_x = 20;
						// konum_x+=12;
						str_cumle[0] = '\0';
						harf = 0;
					}
					else
					{
						mevcut_str++;
						toplam_str++;
						harf = 0;
						str_cumle[harf] = '\0';
						///printf("ilk if else  ");
						konum_y += 20;
						konum_x = 20;
					}
				}
				else
				{
					for (int i = toplam_str; i>mevcut_str; i--)    strcpy(cumle[i + 1], cumle[i]);
					for (int i = harf, sayac = 0; i <= strlen(cumle[mevcut_str]); i++)
					{
						str_cumle[sayac] = cumle[mevcut_str][i];
						sayac++;
						str_cumle[sayac] = '\0';
					}
					cumle[mevcut_str][harf] = '\0';
					strcpy(cumle[mevcut_str + 1], str_cumle);
					strcpy(str_cumle, cumle[mevcut_str + 1]);
					harf = 0;
					mevcut_str++;
					toplam_str++;
					konum_y += 20;
					konum_x = 20;
				}
				harf = 0;
				break;

			case 75:    ///SOL TUSU:
				if (harf>0)
				{
					harf = harf - 1;
					konum_x -= 12;
				}
				else if (mevcut_str != 0)
				{
					mevcut_str--;
					harf = strlen(cumle[mevcut_str]);
					konum_x = 20 + harf * 12;
					konum_y -= 20;
					strcpy(str_cumle, cumle[mevcut_str]);
				}
				continue;
				break;

			case 0x4d:  ///###SAG TUSU
				if (harf<strlen(str_cumle))
				{
					harf++;
					konum_x += 12;
					strcpy(str_cumle, cumle[mevcut_str]);
				}
				else if (toplam_str != mevcut_str)
				{
					mevcut_str++;
					harf = 0;
					strcpy(str_cumle, cumle[mevcut_str]);
					konum_x = 20;
					konum_y += 20;
				}
				continue;
				break;

			case 0x50:  /// ALT TUSU:
				if (mevcut_str<toplam_str)
				{
					mevcut_str++;
					strcpy(str_cumle, cumle[mevcut_str]);
					if (harf>strlen(str_cumle))  harf = strlen(str_cumle);
					konum_y += 20;
					konum_x = 20 + 12 * harf;
				}

				continue;
				break;

			case 0x48:   /// UST TUSU    ///
				if (mevcut_str != 0)
				{
					mevcut_str--;
					strcpy(str_cumle, cumle[mevcut_str]);
					if (harf>strlen(str_cumle))  harf = strlen(str_cumle);
					konum_y -= 20;
					konum_x = 20 + 12 * harf;
				}
				break;

			case 27:    /// ESC
				closegraph();
				printf("\n\tDosya ismini giriniz...");
				scanf("%s", dosya_adi);
				iter = fopen(dosya_adi, "w");
				for (int m = 0; m <= toplam_str; m++)    fprintf(iter, "%s\n", cumle[m]);
				fclose(iter);
				the_end = 1;
				break;

			default:
				if (ch != 224 && ch != 0)
				{
					if (harf < STR - 1)
					{
						toplam_harf = strlen(cumle[mevcut_str]);
						if (toplam_harf != harf)
						{
							for (int i = toplam_harf; i >= harf; i--)    str_cumle[i + 1] = str_cumle[i];
							str_cumle[harf] = ch;
							harf++;
							konum_x += 12;
							str_cumle[toplam_harf + 1] = '\0';
						}
						else
						{
							str_cumle[harf] = ch;
							harf++;
							konum_x += 12;
							str_cumle[harf] = '\0';
						}
					}
					else
					{
						mevcut_str++;
						konum_y += 20;
						konum_x = 20;
						konum_x += 12;
						toplam_str++;
						harf = 0;
						str_cumle[harf] = ch;
						harf++;
						str_cumle[harf] = '\0';
					}
				}
				break;
			}
			strcpy(cumle[mevcut_str], str_cumle);
		} while (!the_end);
		break;
	}
	}
	getch();
}
