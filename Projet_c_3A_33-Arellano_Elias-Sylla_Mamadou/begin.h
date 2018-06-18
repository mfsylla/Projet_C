#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void calcule(int a ){
	a=(a+1)%6;
	printf("%d",a);
}

void clignotage_panneau(int *compteur,int size, int tab_clignotage[])
{	
	if (*compteur==0)
	{
		tab_clignotage[0]=0;
		tab_clignotage[1]=1;
		tab_clignotage[2]=2;
		tab_clignotage[3]=3;
		tab_clignotage[4]=4;
		tab_clignotage[5]=5;
	}
	if(*compteur==125){
		tab_clignotage[0]=5;
		tab_clignotage[1]=4;
		tab_clignotage[2]=3;
		tab_clignotage[3]=2;
		tab_clignotage[4]=1;
		tab_clignotage[5]=0;
	}
	if(*compteur<60){
		for (int i = 0; i < size; ++i)
			{
				tab_clignotage[i] = ((tab_clignotage[i]+1)%6)+30;
			}
	}else{
		if(*compteur<125)
		{
		int couleur=((tab_clignotage[0]+1)%6)+30;
		for (int i = 0; i < size; ++i)
			{
				tab_clignotage[i] = couleur;
			}
		}else{
			if(*compteur<200){
			for (int i = 0; i < size; ++i)
			{
				tab_clignotage[i] = ((tab_clignotage[i]+1)%6)+30;
			}}else{
				int couleur=((tab_clignotage[0]+1)%6)+30;
				for (int i = 0; i < size; ++i)
				{
				tab_clignotage[i] = couleur;
				}
			}
	}}
	fflush(stdout);
	printf("\033[3;3f");printf("\033[%dm",tab_clignotage[0]);printf("▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒");printf("\033[37m");
	printf("\033[4;3f");printf("\033[%dm",tab_clignotage[1]);printf("▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒");printf("\033[37m");
	printf("\033[5;3f");printf("\033[%dm",tab_clignotage[2]);printf("▒▒▒▒                                                                                                                            ▒▒▒▒");printf("\033[37m");
	printf("\033[6;3f");printf("\033[%dm",tab_clignotage[3]);printf("▒▒▒▒                                                                                                                            ▒▒▒▒");printf("\033[37m");
	printf("\033[7;3f");printf("\033[%dm",tab_clignotage[4]);printf("▒▒▒▒                                                                                                                            ▒▒▒▒");printf("\033[37m");
	printf("\033[8;3f");printf("\033[%dm",tab_clignotage[5]);printf("▒▒▒▒                  🌴🌴🌴          🌴🌴🌴  🌴🌴🌴🌴🌴🌴  🌴🌴🌴     🌴🌴🌴🌴🌴🌴  🌴🌴🌴🌴🌴🌴🌴  🌴🌴🌴🌴    🌴🌴🌴🌴  🌴🌴🌴🌴🌴🌴                                   ▒▒▒▒");printf("\033[37m");
	printf("\033[9;3f");printf("\033[%dm",tab_clignotage[0]);printf("▒▒▒▒                   🌴🌴🌴         🌴🌴🌴  🌴🌴🌴     🌴🌴🌴     🌴🌴🌴     🌴🌴🌴  🌴🌴  🌴🌴🌴 🌴   🌴🌴🌴🌴🌴  🌴🌴🌴                                     ▒▒▒▒");printf("\033[37m");
	printf("\033[10;3f");printf("\033[%dm",tab_clignotage[0]);printf("▒▒▒▒                    🌴🌴🌴    🌴🌴  🌴🌴🌴  🌴🌴🌴🌴🌴🌴  🌴🌴🌴     🌴🌴🌴     🌴🌴🌴  🌴🌴  🌴🌴🌴  🌴 🌴🌴  🌴🌴🌴  🌴🌴🌴🌴🌴🌴                                 ▒▒▒▒");printf("\033[37m");
	printf("\033[11;3f");printf("\033[%dm",tab_clignotage[1]);printf("▒▒▒▒                     🌴🌴🌴  🌴🌴 🌴 🌴🌴🌴  🌴🌴🌴🌴🌴🌴  🌴🌴🌴     🌴🌴🌴     🌴🌴🌴  🌴🌴  🌴🌴🌴   🌴🌴    🌴🌴🌴  🌴🌴🌴🌴🌴🌴                                ▒▒▒▒");printf("\033[37m");
	printf("\033[12;3f");printf("\033[%dm",tab_clignotage[2]);printf("▒▒▒▒                      🌴🌴🌴🌴🌴🌴  🌴🌴🌴🌴  🌴🌴🌴     🌴🌴🌴     🌴🌴🌴     🌴🌴🌴  🌴🌴  🌴🌴🌴          🌴🌴🌴  🌴🌴🌴                                  ▒▒▒▒");printf("\033[37m");
	printf("\033[13;3f");printf("\033[%dm",tab_clignotage[3]);printf("▒▒▒▒                       🌴🌴🌴🌴    🌴🌴🌴  🌴🌴🌴🌴🌴🌴  🌴🌴🌴🌴🌴🌴  🌴🌴🌴🌴🌴🌴  🌴🌴🌴🌴🌴🌴🌴  🌴🌴🌴           🌴🌴🌴  🌴🌴🌴🌴🌴🌴                              ▒▒▒▒");printf("\033[37m");
	printf("\033[14;3f");printf("\033[%dm",tab_clignotage[4]);printf("▒▒▒▒                           ▒▒            🍁🍁🍁🍁🍁🍁🍁🍁  🍁🍁🍁   🍁🍁🍁🍁🍁🍁🍁🍁   🍁🍁🍁  🍁🍁🍁   🍁🍁🍁     🍁🍁🍁   🍁🍁🍁🍁🍁🍁   🍁🍁🍁🍁🍁🍁                ▒▒▒▒");printf("\033[37m");
	printf("\033[15;3f");printf("\033[%dm",tab_clignotage[5]);printf("▒▒▒▒                           ▒▒            🍁🍁🍁🍁      🍁🍁🍁🍁   🍁🍁🍁        🍁🍁🍁  🍁🍁🍁   🍁🍁🍁     🍁🍁🍁   🍁🍁🍁      🍁🍁🍁                  ▒▒▒▒");printf("\033[37m");
	printf("\033[16;3f");printf("\033[%dm",tab_clignotage[0]);printf("▒▒▒▒                         ▒▒▒▒▒▒  ▒▒▒▒▒   🍁🍁🍁🍁🍁🍁🍁🍁  🍁🍁🍁 🍁   🍁🍁🍁        🍁🍁🍁  🍁🍁🍁   🍁🍁🍁     🍁🍁🍁   🍁🍁🍁🍁🍁🍁   🍁🍁🍁🍁🍁🍁              ▒▒▒▒");printf("\033[37m");
	printf("\033[17;3f");printf("\033[%dm",tab_clignotage[0]);printf("▒▒▒▒                           ▒▒    ▒▒ ▒▒   🍁🍁🍁🍁🍁🍁🍁🍁  🍁🍁🍁🍁🍁🍁   🍁🍁🍁🍁🍁🍁🍁🍁   🍁🍁🍁🍁🍁🍁🍁🍁   🍁🍁🍁     🍁🍁🍁   🍁🍁🍁🍁🍁🍁   🍁🍁🍁🍁🍁🍁             ▒▒▒▒");printf("\033[37m");
	printf("\033[18;3f");printf("\033[%dm",tab_clignotage[1]);printf("▒▒▒▒                           ▒▒    ▒▒ ▒▒   🍁🍁🍁🍁🍁🍁🍁🍁  🍁🍁🍁   🍁        🍁🍁🍁        🍁🍁🍁   🍁🍁🍁     🍁🍁🍁   🍁🍁🍁      🍁🍁🍁               ▒▒▒▒");printf("\033[37m");
	printf("\033[19;3f");printf("\033[%dm",tab_clignotage[2]);printf("▒▒▒▒                           ▒▒▒▒  ▒▒▒▒▒   🍁🍁🍁🍁      🍁🍁🍁    🍁        🍁🍁🍁        🍁🍁🍁   🍁🍁🍁     🍁🍁🍁   🍁🍁🍁      🍁🍁🍁              ▒▒▒▒");printf("\033[37m");
	printf("\033[20;3f");printf("\033[%dm",tab_clignotage[3]);printf("▒▒▒▒                                         🍁🍁🍁🍁🍁🍁🍁🍁  🍁🍁🍁     🍁   🍁🍁🍁🍁🍁🍁🍁🍁    🍁🍁🍁🍁🍁🍁🍁   🍁🍁🍁🍁🍁🍁  🍁🍁🍁   🍁🍁🍁      🍁🍁🍁🍁🍁🍁          ▒▒▒▒");printf("\033[37m");
	printf("\033[21;3f");printf("\033[%dm",tab_clignotage[4]);printf("▒▒▒▒                🌷🌷🌷🌷🌷🌷🌷🌷🌷  🌷🌷🌷🌷🌷🌷🌷🌷🌷  🌷🌷🌷🌷🌷🌷  🌷🌷🌷🌷🌷🌷🌷🌷🌷🌷🌷  🌷🌷🌷🌷🌷🌷🌷🌷🌷🌷  🌷🌷🌷🌷  🌷🌷🌷🌷🌷🌷🌷🌷                                       ▒▒▒▒");printf("\033[37m");
	printf("\033[22;3f");printf("\033[%dm",tab_clignotage[5]);printf("▒▒▒▒                   🌷🌷🌷🌷    🌷🌷🌷🌷  🌷🌷🌷🌷  🌷🌷 🌷🌷🌷🌷  🌷🌷🌷🌷        🌷🌷🌷🌷        🌷🌷🌷🌷  🌷🌷🌷🌷                                          ▒▒▒▒");printf("\033[37m");
	printf("\033[23;3f");printf("\033[%dm",tab_clignotage[0]);printf("▒▒▒▒                   🌷🌷🌷🌷    🌷🌷🌷🌷  🌷🌷🌷🌷  🌷🌷  🌷🌷🌷🌷  🌷🌷🌷🌷🌷🌷🌷🌷🌷🌷  🌷🌷🌷🌷🌷🌷🌷🌷    🌷🌷🌷🌷  🌷🌷🌷🌷                                         ▒▒▒▒");printf("\033[37m");
	printf("\033[24;3f");printf("\033[%dm",tab_clignotage[0]);printf("▒▒▒▒                   🌷🌷🌷🌷    🌷🌷🌷🌷🌷🌷🌷🌷    🌷🌷   🌷🌷🌷🌷  🌷🌷🌷🌷🌷🌷🌷🌷🌷🌷  🌷🌷🌷🌷🌷🌷🌷🌷    🌷🌷🌷🌷  🌷🌷🌷🌷                                        ▒▒▒▒");printf("\033[37m");
	printf("\033[25;3f");printf("\033[%dm",tab_clignotage[1]);printf("▒▒▒▒                   🌷🌷🌷🌷    🌷🌷🌷🌷  🌷🌷🌷🌷  🌷🌷🌷🌷🌷🌷🌷🌷🌷   🌷🌷🌷🌷        🌷🌷🌷🌷        🌷🌷🌷🌷  🌷🌷🌷🌷                                       ▒▒▒▒");printf("\033[37m");
	printf("\033[26;3f");printf("\033[%dm",tab_clignotage[2]);printf("▒▒▒▒                   🌷🌷🌷🌷    🌷🌷🌷🌷  🌷🌷🌷🌷  🌷🌷     🌷🌷🌷🌷  🌷🌷🌷🌷        🌷🌷🌷🌷        🌷🌷🌷🌷  🌷🌷🌷🌷                                      ▒▒▒▒");printf("\033[37m");
	printf("\033[27;3f");printf("\033[%dm",tab_clignotage[3]);printf("▒▒▒▒                   🌷🌷🌷🌷    🌷🌷🌷🌷  🌷🌷🌷🌷  🌷🌷      🌷🌷🌷🌷  🌷🌷🌷🌷        🌷🌷🌷🌷        🌷🌷🌷🌷  🌷🌷🌷🌷                                     ▒▒▒▒");printf("\033[37m");
	printf("\033[28;3f");printf("\033[%dm",tab_clignotage[4]);printf("▒▒▒▒                   🌷🌷🌷🌷    🌷🌷🌷🌷  🌷🌷🌷🌷  🌷🌷       🌷🌷🌷🌷  🌷🌷🌷🌷        🌷🌷🌷🌷        🌷🌷🌷🌷  🌷🌷🌷🌷🌷🌷🌷🌷                                ▒▒▒▒");printf("\033[37m");
	printf("\033[29;3f");printf("\033[%dm",tab_clignotage[5]);printf("▒▒▒▒                                                                                                                            ▒▒▒▒");printf("\033[37m");
	printf("\033[30;3f");printf("\033[%dm",tab_clignotage[0]);printf("▒▒▒▒                                                                                                                            ▒▒▒▒");printf("\033[37m");
	printf("\033[31;3f");printf("\033[%dm",tab_clignotage[0]);printf("▒▒▒▒                                                                                                                            ▒▒▒▒");printf("\033[37m");
	printf("\033[32;3f");printf("\033[%dm",tab_clignotage[1]);printf("▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒");printf("\033[37m");
	printf("\033[33;3f");printf("\033[%dm",tab_clignotage[2]);printf("▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒");printf("\033[37m");


}

void clignotage_gagnant(int *compteur,int size, int tab_clignotage[])
{	
	if (*compteur==0)
	{
		tab_clignotage[0]=0;
		tab_clignotage[1]=1;
		tab_clignotage[2]=2;
		tab_clignotage[3]=3;
		tab_clignotage[4]=4;
		tab_clignotage[5]=5;
	}
	if(*compteur==125){
		tab_clignotage[0]=5;
		tab_clignotage[1]=4;
		tab_clignotage[2]=3;
		tab_clignotage[3]=2;
		tab_clignotage[4]=1;
		tab_clignotage[5]=0;
	}
	if(*compteur<60){
		for (int i = 0; i < size; ++i)
			{
				tab_clignotage[i] = ((tab_clignotage[i]+1)%6)+30;
			}
	}else{
		if(*compteur<125)
		{
		int couleur=((tab_clignotage[0]+1)%6)+30;
		for (int i = 0; i < size; ++i)
			{
				tab_clignotage[i] = couleur;
			}
		}else{
			if(*compteur<200){
			for (int i = 0; i < size; ++i)
			{
				tab_clignotage[i] = ((tab_clignotage[i]+1)%6)+30;
			}}else{
				int couleur=((tab_clignotage[0]+1)%6)+30;
				for (int i = 0; i < size; ++i)
				{
				tab_clignotage[i] = couleur;
				}
			}
	}}
	fflush(stdout);
	printf("\033[3;3f");printf("\033[%dm",tab_clignotage[0]);printf("▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒");printf("\033[37m");
	printf("\033[4;3f");printf("\033[%dm",tab_clignotage[1]);printf("▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒");printf("\033[37m");
	printf("\033[5;3f");printf("\033[%dm",tab_clignotage[2]);printf("▒▒▒▒                                                                                                                            ▒▒▒▒");printf("\033[37m");
	printf("\033[6;3f");printf("\033[%dm",tab_clignotage[3]);printf("▒▒▒▒                                       ▒                                        ▒                                           ▒▒▒▒");printf("\033[37m");
	printf("\033[7;3f");printf("\033[%dm",tab_clignotage[4]);printf("▒▒▒▒                         ▒                                   ▒                                             ▒                ▒▒▒▒");printf("\033[37m");
	printf("\033[8;3f");printf("\033[%dm",tab_clignotage[5]);printf("▒▒▒▒     ▒                                                                           ▒                 ▒                        ▒▒▒▒");printf("\033[37m");
	printf("\033[9;3f");printf("\033[%dm",tab_clignotage[0]);printf("▒▒▒▒                     ▒                ▒                                                                                     ▒▒▒▒");printf("\033[37m");
	printf("\033[10;3f");printf("\033[%dm",tab_clignotage[0]);printf("▒▒▒▒                                                                      ▒               ▒                                     ▒▒▒▒");printf("\033[37m");
	printf("\033[11;3f");printf("\033[%dm",tab_clignotage[1]);printf("▒▒▒▒                                                                                                                            ▒▒▒▒");printf("\033[37m");
	printf("\033[12;3f");printf("\033[%dm",tab_clignotage[2]);printf("▒▒▒▒                                                                                                        ▒          ▒        ▒▒▒▒");printf("\033[37m");
	printf("\033[13;3f");printf("\033[%dm",tab_clignotage[3]);printf("▒▒▒▒                        ▒▒    ▒▒                ▒▒     ▒▒    ▒▒     ▒▒   ▒▒    ▒▒    ▒                                      ▒▒▒▒");printf("\033[37m");
	printf("\033[14;3f");printf("\033[%dm",tab_clignotage[4]);printf("▒▒▒▒                         ▒▒  ▒▒                  ▒▒     ▒▒  ▒▒     ▒▒          ▒▒▒   ▒                                      ▒▒▒▒");printf("\033[37m");
	printf("\033[15;3f");printf("\033[%dm",tab_clignotage[5]);printf("▒▒▒▒   ▒                      ▒▒▒▒                    ▒▒     ▒▒▒▒     ▒▒     ▒▒    ▒ ▒▒  ▒                                      ▒▒▒▒");printf("\033[37m");
	printf("\033[16;3f");printf("\033[%dm",tab_clignotage[0]);printf("▒▒▒▒                           ▒▒    ▒▒▒▒▒ ▒▒  ▒▒      ▒▒     ▒▒     ▒▒      ▒▒    ▒  ▒▒ ▒                          ▒           ▒▒▒▒");printf("\033[37m");
	printf("\033[17;3f");printf("\033[%dm",tab_clignotage[0]);printf("▒▒▒▒                           ▒▒    ▒▒ ▒▒ ▒▒  ▒▒       ▒▒   ▒▒▒▒   ▒▒       ▒▒    ▒   ▒▒▒                   ▒                  ▒▒▒▒");printf("\033[37m");
	printf("\033[18;3f");printf("\033[%dm",tab_clignotage[1]);printf("▒▒▒▒                ▒          ▒▒    ▒▒ ▒▒ ▒▒  ▒▒        ▒▒ ▒▒  ▒▒ ▒▒        ▒▒    ▒    ▒▒                                      ▒▒▒▒");printf("\033[37m");
	printf("\033[19;3f");printf("\033[%dm",tab_clignotage[2]);printf("▒▒▒▒                           ▒▒    ▒▒▒▒▒ ▒▒▒▒▒▒         ▒▒▒    ▒▒▒         ▒▒    ▒     ▒                                      ▒▒▒▒");printf("\033[37m");
	printf("\033[20;3f");printf("\033[%dm",tab_clignotage[3]);printf("▒▒▒▒                                                                                                        ▒                   ▒▒▒▒");printf("\033[37m");
	printf("\033[21;3f");printf("\033[%dm",tab_clignotage[4]);printf("▒▒▒▒                                   ▒                                                                                        ▒▒▒▒");printf("\033[37m");
	printf("\033[22;3f");printf("\033[%dm",tab_clignotage[5]);printf("▒▒▒▒        ▒                                                                                                                   ▒▒▒▒");printf("\033[37m");
	printf("\033[23;3f");printf("\033[%dm",tab_clignotage[0]);printf("▒▒▒▒                    ▒                                  ▒           ▒                  ▒                                     ▒▒▒▒");printf("\033[37m");
	printf("\033[24;3f");printf("\033[%dm",tab_clignotage[0]);printf("▒▒▒▒                               ▒        ▒                                                          ▒                        ▒▒▒▒");printf("\033[37m");
	printf("\033[25;3f");printf("\033[%dm",tab_clignotage[1]);printf("▒▒▒▒                                                                           ▒                                                ▒▒▒▒");printf("\033[37m");
	printf("\033[26;3f");printf("\033[%dm",tab_clignotage[2]);printf("▒▒▒▒          ▒                                                                             ▒                         ▒         ▒▒▒▒");printf("\033[37m");
	printf("\033[27;3f");printf("\033[%dm",tab_clignotage[3]);printf("▒▒▒▒                                                                                                            ▒               ▒▒▒▒");printf("\033[37m");
	printf("\033[28;3f");printf("\033[%dm",tab_clignotage[4]);printf("▒▒▒▒                                               ▒            ▒           ▒                                                   ▒▒▒▒");printf("\033[37m");
	printf("\033[29;3f");printf("\033[%dm",tab_clignotage[5]);printf("▒▒▒▒              ▒                      ▒                                                                                      ▒▒▒▒");printf("\033[37m");
	printf("\033[30;3f");printf("\033[%dm",tab_clignotage[0]);printf("▒▒▒▒                                                                                                             ▒    ▒         ▒▒▒▒");printf("\033[37m");
	printf("\033[31;3f");printf("\033[%dm",tab_clignotage[0]);printf("▒▒▒▒                                                                                                                            ▒▒▒▒");printf("\033[37m");
	printf("\033[32;3f");printf("\033[%dm",tab_clignotage[1]);printf("▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒");printf("\033[37m");
	printf("\033[33;3f");printf("\033[%dm",tab_clignotage[2]);printf("▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒");printf("\033[37m");


}