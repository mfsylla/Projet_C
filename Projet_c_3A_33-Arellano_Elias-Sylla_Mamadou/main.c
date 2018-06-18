#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>
#include <fcntl.h>
#include "caos_mode.h"
#include "begin.h"
#include "bye.h"
#include "boom.h"

/*Structure pour creer une voiture*/
struct vehicule
{
	int valeur;
	int x;
	int y;
	struct vehicule *next;
};
typedef struct vehicule vehicule;

/*Structure qui contien la liste des voitures, c'est è dire le chemin des voitures*/
struct chemin_vehicule
{
	vehicule *queue;
	vehicule *tete;
	int size;
};
typedef struct chemin_vehicule chemin_vehicule;

/*Fonction qui sert à inisialiter le chemin des voitures à vide, techniquement c'est une liste vide au debut*/
void init_vehicule(chemin_vehicule *l)
{
	l->queue=NULL;
	l->tete=NULL;	
	l->size=0;	    
}

/*Cette fonction met en queue les elements de la liste, c'est à dire on crée au debut du program les chemins avec leur coordonés, cette fonction est appellé seulement une fois */
void mettre_en_queue(chemin_vehicule *l,int y,int x)
{
	//Ouvrir le fichier avec les coordonnees
	if(l->size==0)
		{
		vehicule *nouveau = malloc(sizeof(vehicule));
		
		nouveau->valeur=0;
		nouveau->x=x;
		nouveau->y=y;
		nouveau->next=NULL;
		
		l->tete=nouveau;
		l->queue=nouveau;
		l->size=l->size+1;
		
		}else{
			vehicule *nouveau = malloc(sizeof(vehicule));
			nouveau->valeur=0;
			nouveau->x=x;
			nouveau->y=y;
			l->queue->next = nouveau;
			l->queue = nouveau;
			l->size = l->size+1;
		}
}

/*Fonction special qui sert à afficher le tram*/
void affichages_des_trams(chemin_vehicule *l)
{
	/*Ici on affiche tout la liste qui va de l'extrem est à l'extreme ouest, c'est à dire que la liste
	traverse la map, ainsi le tram s'affiche en tout point de la raie dessinée*/
	vehicule *pourmontrer;	
	pourmontrer = l->tete;
	while(pourmontrer!=NULL)
	{
		printf("\033[%d;%df",pourmontrer->y,pourmontrer->x);
		switch(pourmontrer->valeur)
		{
			case 2: //si c'est 2, on affiche un morceau du tram
			printf("🚙"); //plusieurs voitures en ligne representent un tram
			break;
			case 3: //si c'est 3, on affiche un morceau de la raie
			printf("─"); //on affiche un morceau de raie à la fin de la liste pour écrasser les voitures qui restent afficher en arriere du tram deplacé
		//	case 0: //si c'est 3, on affiche un morceau de la raie
		//	printf(" ");
		}
		pourmontrer=pourmontrer->next; //on passe à l'element suivant pour l'afficher
		//on affiche rien s'il y a ni 2 ni 3
	}
}

/*Fonction special qui sert à afficher les voitures*/
void afficher(chemin_vehicule *l)
{
	vehicule *pourmontrer;	
	pourmontrer = l->tete;
	while(pourmontrer !=NULL)
	{	
		printf("\033[%d;%df",pourmontrer->y,pourmontrer->x);
		if(pourmontrer->valeur==0 || pourmontrer->valeur >10)// si la valeur est >10 ou 0, on affiche le vide
			{printf(" ");}
		else{
			switch(pourmontrer->valeur)
			{   //il existe 10 types de voitures avec leur couleur et modeles à afficher e, fonction des numeros entre 1 et 10
				case 1:
				printf("\033[31m"); printf("🚕"); printf("\033[37m");//🚙
				break;
				case 2:
				printf("\033[32m"); printf("🚘"); printf("\033[37m");//🚕
				break;
				case 3:
				printf("\033[33m"); printf("🚕"); printf("\033[37m");
				break;
				case 4:
				printf("\033[34m"); printf("🚘"); printf("\033[37m");
				break;
				case 5:
				printf("\033[35m"); printf("🚘"); printf("\033[37m");
				break;
				case 6:
				printf("\033[36m"); printf("🚕"); printf("\033[37m");
				break;
				case 7:
				printf("\033[31m"); printf("🚘"); printf("\033[37m");
				break;
				case 8:
				printf("\033[32m"); printf("🚘"); printf("\033[37m");
				break;
				case 9:
				printf("\033[33m"); printf("🚘"); printf("\033[37m");
				break;
				case 10:
				printf("\033[33m"); printf("🚕"); printf("\033[37m");
				break;
			}
		 }
		  pourmontrer=pourmontrer->next; //on passe à l'element suivant pour l'afficher
	}
}

/*Fonction qui prend un chemin et met les voitures dans un tableau */
void rewrite_tab(chemin_vehicule *l,int line, int tableau[][150])
{
	vehicule *pourcopier;	
	pourcopier = l->tete;
	while(pourcopier !=NULL)
	{	
		tableau[pourcopier->y][pourcopier->x]=pourcopier->valeur; //Dans le tableau on se place dans les coordonnés de chaqu'un des elements de la liste pour placer leurs valeurs dans les caises du tableau 
		pourcopier=pourcopier->next;
	}
}

/*Fonction void qui deplace le tram passé en paramettre*/
void deplacement_tram_to_left(chemin_vehicule *l,int recu)
{	
	//Declaration des variables
	int var_temp=0; //valeur temporel de l'element présent
	int var_prec=0; //valeur precedent de l'element precedent LOL
	vehicule *pourdeplacer;	//element courant
	pourdeplacer = l->tete; //courant inisialisé en tete
	
	pourdeplacer->valeur=recu; //la valeur recu et mis dans la tete
	
	//Preparer le deplacement: debut du deplacement dans la tête de la liste.
	var_temp=pourdeplacer->valeur;
	pourdeplacer->valeur=0;
	var_prec=var_temp;
	pourdeplacer=pourdeplacer->next;

	/*Maintenant on deplace les elements suivantes, on deplace une fois d'une case touts les valeurs, 
	  c'est a dire le tram, et à cette état, cette liste de tram sera affiché */
	while(pourdeplacer !=NULL)
	{	
		var_temp=pourdeplacer->valeur;
		pourdeplacer->valeur=var_prec;
		var_prec=var_temp ;
		pourdeplacer=pourdeplacer->next;
	}	
}
/*Fonction qui deplace le chemin 6*/
void deplacement_6(chemin_vehicule *l,int compteur_vert)
{	
	//Declaration des variables
	int var_temp=0;
	int var_prec=0;
	vehicule *pourdeplacer;	
	pourdeplacer = l->tete;
	/****************************************************************************/
	vehicule *temp;// pour avoir acces à l'element qui es derier le element pour deplacer
	vehicule *stop;

	/****************************************************************************/
	if(compteur_vert==1){ //Si le feut vert est éteint, le rouge s'active, donc on se met en mode feut rouge
		/*Maintenant je deplace pour trouver la caise egal à 0 la plus près du feu rouge*/

	while(pourdeplacer->x!=69 || pourdeplacer->y!=16) //Tant qu'on est pas dans l'element qui a cordonnés où c'est le point d'arret de feu rouge
	{
		//s'il n'y a pas de voitures (valeur==0 ou >10), c'est à dire, la caise est vide aussi si >10
		if(pourdeplacer->valeur==0 || pourdeplacer->valeur>10) 
		{ 
			//donc c'est dans cette coordonnées où je dois deplacer ma derniere voiture , c'est la coordonnes la plus proches du feu rouge
			//ainsi, je peux deplacer mes voitures qui sont deriere les voitures qui sont dans le feu rouge 
			temp=pourdeplacer; 
		}	
		pourdeplacer=pourdeplacer->next;
	}
	stop=temp->next; //Voila, j'ai trouvé mon nouveau point d'arret
	//Preparer le deplacement: debut du deplacement dans la tête de la liste
	pourdeplacer=l->tete;
	int r=rand()%100; // je met une valeur aleatoire pour mettre dans l'element en tete, (1 à 10 y a une voiture, 0 ou >10 y a pas de voitures)
	pourdeplacer->valeur=r;

	var_temp=pourdeplacer->valeur;
	pourdeplacer->valeur=0;
	var_prec=var_temp;
	pourdeplacer=pourdeplacer->next;

	//Tant que je ne suis pas dans le point d'arrete, je deplace d'une caise tous mes voitures qui sont derier le feu rouge
	while(pourdeplacer->y!=stop->y || pourdeplacer->x!=stop->x)
	{
		var_temp=pourdeplacer->valeur;
		pourdeplacer->valeur=var_prec;
		var_prec=var_temp;
		pourdeplacer=pourdeplacer->next;
	}
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	/*****On deplace normalement le reste des voitures qui sont apres le feu rouge******/
	// je me positionne d'abord dans le feu rouge pour deplacer le reste des voitures
	while(pourdeplacer->x!=69 || pourdeplacer->y!=16)
		{pourdeplacer=pourdeplacer->next;}

	//Preparer le deplacement: debut du deplacement la suite de la liste
	var_temp=pourdeplacer->valeur;
	pourdeplacer->valeur=0;
	var_prec=var_temp;
	pourdeplacer=pourdeplacer->next;
	//Deplacer les voitures suivantes
	while(pourdeplacer !=NULL)
	{	
		var_temp=pourdeplacer->valeur;
		pourdeplacer->valeur=var_prec;
		var_prec=var_temp;
		pourdeplacer=pourdeplacer->next;
	}


	}else{//si c'est vert, donce je deplace tous mes voitures normalement

	/*****************************************************************************/

 	int r=rand()%100;
	pourdeplacer->valeur=r;
	
	//Preparer le deplacement: debut du deplacement dans la tête de la liste
	var_temp=pourdeplacer->valeur;
	pourdeplacer->valeur=0;
	var_prec=var_temp;
	pourdeplacer=pourdeplacer->next;

	//Deplacer les voitures suivantes
	while(pourdeplacer !=NULL)
	{	
		var_temp=pourdeplacer->valeur;
		pourdeplacer->valeur=var_prec;
		var_prec=var_temp;
		pourdeplacer=pourdeplacer->next;
	}}	
}

int deplacement_5(chemin_vehicule *l,int compteur_vert)
{	
	//Declaration des variables
	int var_temp=0;
	int var_prec=0;
	vehicule *pourdeplacer;	
	pourdeplacer = l->tete;
	int envoie=0;
	/****************************************************************************/
	vehicule *temp;// pour avoir acces à l'element qui es derier le element pour deplacer
	vehicule *stop;

	/****************************************************************************/
	if(compteur_vert==1/*125*/){//Si le feut vert est éteint, le rouge s'active, donc on se met en mode feut rouge
		/*Maintenant je deplace pour trouver la caise egal à 0 la plus près du feu rouge*/

	while(pourdeplacer->x!=69 || pourdeplacer->y!=14) //Tant qu'on est pas dans l'element qui a cordonnés où c'est le point d'arret de feu rouge
	{
			//s'il n'y a pas de voitures (valeur==0 ou >10), c'est à dire, la caise est vide aussi si >10
		if(pourdeplacer->valeur==0 || pourdeplacer->valeur>10) 
		{
			//donc c'est dans cette coordonnées où je dois deplacer ma derniere voiture , c'est la coordonnes la plus proches du feu rouge
			//ainsi, je peux deplacer mes voitures qui sont deriere les voitures qui sont dans le feu rouge 
			temp=pourdeplacer;
		}	
		pourdeplacer=pourdeplacer->next;
	}

	stop=temp->next;//Voila, j'ai trouvé mon nouveau point d'arret
	//Preparer le deplacement: debut du deplacement dans la tête de la liste
	pourdeplacer=l->tete;
	int r=rand()%100; // je met une valeur aleatoire pour mettre dans l'element en tete, (1 à 10 y a une voiture, 0 ou >10 y a pas de voitures)
	pourdeplacer->valeur=r;

	var_temp=pourdeplacer->valeur;
	pourdeplacer->valeur=0;
	var_prec=var_temp;
	pourdeplacer=pourdeplacer->next;
	//Tant que je ne suis pas dans le point d'arrete, je deplace d'une caise tous mes voitures qui sont derier le feu rouge
	while(pourdeplacer->y!=stop->y || pourdeplacer->x!=stop->x)
	{
		if(pourdeplacer->y==14 && pourdeplacer->x==108)
		{
			r=rand()%2;
			if(r==1)
			{
				envoie=pourdeplacer->valeur;
				pourdeplacer->valeur=0;
			}else{
				envoie=0;
			}
		}
		var_temp=pourdeplacer->valeur;
		pourdeplacer->valeur=var_prec;
		var_prec=var_temp;
		pourdeplacer=pourdeplacer->next;
	}
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	/*****On deplace normalement le reste des voitures qui sont apres le feu rouge******/
	// je me positionne d'abord dans le feu rouge pour deplacer le reste des voitures
	while(pourdeplacer->x!=69 || pourdeplacer->y!=14)
		{pourdeplacer=pourdeplacer->next;}

	//Preparer le deplacement: debut du deplacement la suite de la liste
	var_temp=pourdeplacer->valeur;
	pourdeplacer->valeur=0;
	var_prec=var_temp;
	pourdeplacer=pourdeplacer->next;
	//Deplacer les voitures suivantes
	while(pourdeplacer !=NULL)
	{	
		var_temp=pourdeplacer->valeur;
		pourdeplacer->valeur=var_prec;
		var_prec=var_temp;
		pourdeplacer=pourdeplacer->next;
	}


	}else{ //si c'est vert, donce je deplace tous mes voitures normalement

	/*****************************************************************************/

 	int r=rand()%100;
	pourdeplacer->valeur=r;
	
	//Preparer le deplacement: debut du deplacement dans la tête de la liste
	var_temp=pourdeplacer->valeur;
	pourdeplacer->valeur=0;
	var_prec=var_temp;
	pourdeplacer=pourdeplacer->next;

	//Deplacer les voitures suivantes
	while(pourdeplacer !=NULL)
	{	
		var_temp=pourdeplacer->valeur;
		pourdeplacer->valeur=var_prec;
		var_prec=var_temp;
		pourdeplacer=pourdeplacer->next;
	}}
	return envoie;	
}

void put_in_liste_2_from_liste_4(chemin_vehicule *l,int dep_est)
{
	//mettre une voiture dans la liste 2 depuis la liste 4
	vehicule *pourdeplacer;
	pourdeplacer=l->tete;
	if(dep_est!=0){ //s'il y a une voiture , on met la valeur,(si c'est > 10 on s'en fout car quand meme il sera pas affiché, on peut optimiser le if si tu veux)
	for(int i=0;i<3;i++) //mettre la voiture dans le 5eme element, c'est à dire dans la 5eme coordonnés
		{pourdeplacer=pourdeplacer->next;}
		pourdeplacer->valeur=dep_est;}
}

void put_in_liste_5_from_liste_4(chemin_vehicule *l,int dep_est)
{
	//mettre une voiture dans la liste 5 depuis la liste 4
	vehicule *pourdeplacer;
	pourdeplacer=l->tete;
	if(dep_est!=0){ //s'il y a une voiture , on met la valeur,(si c'est > 10 on s'en fout car quand meme il sera pas affiché, on peut optimiser le if si tu veux)
	for(int i=0;i<41;i++) //mettre la voiture dans le 76eme element, c'est à dire dans la 76eme coordonnés
		{pourdeplacer=pourdeplacer->next;}
		pourdeplacer->valeur=dep_est;

	}
}

void put_in_liste_6_from_liste_3(chemin_vehicule *l,int dep_est)
{
	//mettre une voiture dans la liste 6 depuis la liste 3
	vehicule *pourdeplacer;
	pourdeplacer=l->tete;
	if(dep_est!=0){//s'il y a une voiture , on met la valeur,(si c'est > 10 on s'en fout car quand meme il sera pas affiché, on peut optimiser le if si tu veux)
		for(int i=0;i<41;i++)//mettre la voiture dans le 81eme element, c'est à dire dans la 81eme coordonnés
		{pourdeplacer=pourdeplacer->next;}
		pourdeplacer->valeur=dep_est;
	}
}

int deplacement_4(chemin_vehicule *l, int compteur_vert)
{	
	//Declaration des variables
	int var_temp=0;
	int var_prec=0;
	vehicule *pourdeplacer;	
	pourdeplacer = l->tete;
	int envoie=0;
	/****AJOUTE DES PROPRIETÉS POUR LE FEU*****/

	vehicule *temp;// pour avoir acces à l'element qui es derier le element pour deplacer
	vehicule *stop;
	/*Si c'est en rouge on s'arrete fur et à mesure*/
	if(compteur_vert==1){
		/*Maintenant je deplace pour trouver la caise egal à 0 la plus près du feu rouge*/

	while(pourdeplacer->x!=66 || pourdeplacer->y!=29) 
	{
		if(pourdeplacer->valeur==0 || pourdeplacer->valeur>10) //SI la caise est vide !!!!! >10
		{
			temp=pourdeplacer;
		}	
		pourdeplacer=pourdeplacer->next;
	}
	stop=temp->next;
	//Preparer le deplacement: debut du deplacement dans la tête de la liste
	pourdeplacer=l->tete;
	int r=rand()%100;
	pourdeplacer->valeur=r;

	var_temp=pourdeplacer->valeur;
	pourdeplacer->valeur=0;
	var_prec=var_temp;
	pourdeplacer=pourdeplacer->next;
	//while(/*pourdeplacer!=temp*///pourdeplacer->y!=pos_y_vide || pourdeplacer->x!=pos_x_vide)
	while(pourdeplacer->y!=stop->y || pourdeplacer->x!=stop->x)
	{
		var_temp=pourdeplacer->valeur;
		pourdeplacer->valeur=var_prec;
		var_prec=var_temp;
		pourdeplacer=pourdeplacer->next;
	}
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	/*******************On deplace normalement le reste des voitures********************************/
	//pourdeplacer=pourdeplacer->next->next;
	while(pourdeplacer->x!=66 || pourdeplacer->y!=29)
		{pourdeplacer=pourdeplacer->next;}

	//Preparer le deplacement: debut du deplacement la suite de la liste
	var_temp=pourdeplacer->valeur;
	pourdeplacer->valeur=0;
	var_prec=var_temp;
	pourdeplacer=pourdeplacer->next;
	//Deplacer les voitures suivantes
	while(pourdeplacer !=NULL)
	{	
		var_temp=pourdeplacer->valeur;
		pourdeplacer->valeur=var_prec;
		var_prec=var_temp;
		pourdeplacer=pourdeplacer->next;
	}


	}else{ //Si c'est pas rouges!!!!
	/****FIN DES PROPRIETÉS POUR LE FEU, A PARTIR DE LA LE CODE EST LE NORMAL***/
	//Obtenir valeur aleatoire
	int r=rand()%100;
	pourdeplacer->valeur=r;
	//Preparer le deplacement: debut du deplacement dans la tête de la liste
	var_temp=pourdeplacer->valeur;
	pourdeplacer->valeur=0;
	var_prec=var_temp;
	pourdeplacer=pourdeplacer->next;

	//Deplacer les voitures suivantes
	while(pourdeplacer !=NULL)
	{	if(pourdeplacer->y==27 && pourdeplacer->x==66 && pourdeplacer->valeur>5)
		{	int choix=rand()%1;
			if(choix==0){ //si la valeur aleatoire est 0, on envoie la valeur à la liste 2, apres la valeur sera traite par la liste 2
			envoie=pourdeplacer->valeur;
	//		pourdeplacer->valeur==0; // AVANT C'ETAIT pourdeplacer->valeur=0;????????? y a un truc bizare
		var_temp=0; //actuel = 0
		pourdeplacer->valeur=0;
		pourdeplacer=pourdeplacer->next; //actuel  = precedent
		}
		}else{
		var_temp=pourdeplacer->valeur; 
		pourdeplacer->valeur=var_prec; 
		var_prec=var_temp ; 
		pourdeplacer=pourdeplacer->next;
	}
	}
	}
	return envoie;
}

void deplacement_3(chemin_vehicule *l,int compteur_vert)
{	
	//Declaration des variables
	int var_temp=0;
	int var_prec=0;
	vehicule *pourdeplacer;	
	pourdeplacer = l->tete;

	vehicule *temp;// pour avoir acces à l'element qui es derier le element pour deplacer
	vehicule *stop;

	/****************************************************************************/
	if(compteur_vert==1){
		/*Maintenant je deplace pour trouver la caise egal à 0 la plus près du feu rouge*/

	while(pourdeplacer->x!=58 || pourdeplacer->y!=24) 
	{
		if(pourdeplacer->valeur==0 || pourdeplacer->valeur>10) //SI la caise est vide !!!!! >10
		{
			temp=pourdeplacer;
		}	
		pourdeplacer=pourdeplacer->next;
	}
	stop=temp->next;
	//Preparer le deplacement: debut du deplacement dans la tête de la liste
	pourdeplacer=l->tete;
	int r=rand()%100;
	pourdeplacer->valeur=r;

	var_temp=pourdeplacer->valeur;
	pourdeplacer->valeur=0;
	var_prec=var_temp;
	pourdeplacer=pourdeplacer->next;
	//while(/*pourdeplacer!=temp*///pourdeplacer->y!=pos_y_vide || pourdeplacer->x!=pos_x_vide)
	while(pourdeplacer->y!=stop->y || pourdeplacer->x!=stop->x)
	{
		var_temp=pourdeplacer->valeur;
		pourdeplacer->valeur=var_prec;
		var_prec=var_temp;
		pourdeplacer=pourdeplacer->next;
	}
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	/*******************On deplace normalement le reste des voitures********************************/
	while(pourdeplacer->x!=58 || pourdeplacer->y!=24)
		{pourdeplacer=pourdeplacer->next;}

	//Preparer le deplacement: debut du deplacement la suite de la liste
	var_temp=pourdeplacer->valeur;
	pourdeplacer->valeur=0;
	var_prec=var_temp;
	pourdeplacer=pourdeplacer->next;
	//Deplacer les voitures suivantes
	while(pourdeplacer !=NULL)
	{	
		var_temp=pourdeplacer->valeur;
		pourdeplacer->valeur=var_prec;
		var_prec=var_temp;
		pourdeplacer=pourdeplacer->next;
	}


	}else{
	
 	int r=rand()%100;
	pourdeplacer->valeur=r;
	
	//Preparer le deplacement: debut du deplacement dans la tête de la liste
	var_temp=pourdeplacer->valeur;
	pourdeplacer->valeur=0;
	var_prec=var_temp;
	pourdeplacer=pourdeplacer->next;

	//Deplacer les voitures suivantes
	while(pourdeplacer !=NULL)
	{	
		var_temp=pourdeplacer->valeur;
		pourdeplacer->valeur=var_prec;
		var_prec=var_temp;
		pourdeplacer=pourdeplacer->next;
	}}	
}

void deplacement_10(chemin_vehicule *l,int recu)
{	
	//Declaration des variables
	int var_temp=0;
	int var_prec=0;
	vehicule *pourdeplacer;	
	pourdeplacer = l->tete;
	/****AJOUTE DES PROPRIETÉS POUR LE FEU*****/

	/****FIN DES PROPRIETÉS POUR LE FEU, A PARTIR DE LA LE CODE EST LE NORMAL***/
	//int r=rand()%100;
		pourdeplacer->valeur=recu;
	//Preparer le deplacement: debut du deplacement dans la tête de la liste
	var_temp=pourdeplacer->valeur;
	pourdeplacer->valeur=0;
	var_prec=var_temp;
	pourdeplacer=pourdeplacer->next;

	//Deplacer les voitures suivantes
	while(pourdeplacer !=NULL)
	{	
		var_temp=pourdeplacer->valeur;
		pourdeplacer->valeur=var_prec;
		var_prec=var_temp ;
		pourdeplacer=pourdeplacer->next;
	}	
}

void deplacement_pieton_tram_go(chemin_vehicule *l,int recu, int permission,int x_feu,int y_feu)
{	
	//Declaration des variables
	int var_temp=0;
	int var_prec=0;
	vehicule *pourdeplacer;
	vehicule *temp=NULL;
	vehicule *stop=NULL;
	pourdeplacer = l->tete;
	/****AJOUTE DES PROPRIETÉS POUR LE FEU*****/

	/****FIN DES PROPRIETÉS POUR LE FEU, A PARTIR DE LA LE CODE EST LE NORMAL***/
	if(recu==1)
	{
		while(pourdeplacer->x!=x_feu || pourdeplacer->y!=y_feu) 
	{
		if(pourdeplacer->valeur==0 || pourdeplacer->valeur>10) //SI la caise est vide !!!!! >10
		{
			temp=pourdeplacer;
		}	
		pourdeplacer=pourdeplacer->next;
	}
	stop=temp->next;
	//Preparer le deplacement: debut du deplacement dans la tête de la liste
	pourdeplacer=l->tete;
	if(permission==1)
	{
	int r=rand()%150;
	pourdeplacer->valeur=r;
	}else{
		pourdeplacer->valeur=0;}
	var_temp=pourdeplacer->valeur;
	pourdeplacer->valeur=0;
	var_prec=var_temp;
	pourdeplacer=pourdeplacer->next;
	//while(/*pourdeplacer!=temp*///pourdeplacer->y!=pos_y_vide || pourdeplacer->x!=pos_x_vide)
	while(pourdeplacer->y!=stop->y || pourdeplacer->x!=stop->x)
	{
		var_temp=pourdeplacer->valeur;
		pourdeplacer->valeur=var_prec;
		var_prec=var_temp;
		pourdeplacer=pourdeplacer->next;
	}
	
	}else{
	
	if(permission==1)
	{
	int r=rand()%150;
	pourdeplacer->valeur=r;
	}else{
		pourdeplacer->valeur=0;}
	//Preparer le deplacement: debut du deplacement dans la tête de la liste
	var_temp=pourdeplacer->valeur;
	pourdeplacer->valeur=0;
	var_prec=var_temp;
	pourdeplacer=pourdeplacer->next;

	//Deplacer les voitures suivantes
	while(pourdeplacer !=NULL)
	{	
		var_temp=pourdeplacer->valeur;
		pourdeplacer->valeur=var_prec;
		var_prec=var_temp ;
		pourdeplacer=pourdeplacer->next;
	}	
	//element_from_liste_5->valeur=var_temp;

		}//fin else
}

void deplacement_9(chemin_vehicule *l,int recu, vehicule *element_from_liste_5)
{	
	//Declaration des variables
	int var_temp=0;
	int var_prec=0;
	vehicule *pourdeplacer;
	vehicule *temp=NULL;
	vehicule *stop=NULL;
	pourdeplacer = l->tete;
	/****AJOUTE DES PROPRIETÉS POUR LE FEU*****/

	/****FIN DES PROPRIETÉS POUR LE FEU, A PARTIR DE LA LE CODE EST LE NORMAL***/
	if(recu>0 && recu<=10)
	{
		while(pourdeplacer->x!=103 || pourdeplacer->y!=13) 
	{
		if(pourdeplacer->valeur==0 || pourdeplacer->valeur>10) //SI la caise est vide !!!!! >10
		{
			temp=pourdeplacer;
		}	
		pourdeplacer=pourdeplacer->next;
	}
	stop=temp->next;
	//Preparer le deplacement: debut du deplacement dans la tête de la liste
	pourdeplacer=l->tete;
	int r=rand()%100;
	pourdeplacer->valeur=r;

	var_temp=pourdeplacer->valeur;
	pourdeplacer->valeur=0;
	var_prec=var_temp;
	pourdeplacer=pourdeplacer->next;
	//while(/*pourdeplacer!=temp*///pourdeplacer->y!=pos_y_vide || pourdeplacer->x!=pos_x_vide)
	while(pourdeplacer->y!=stop->y || pourdeplacer->x!=stop->x)
	{
		var_temp=pourdeplacer->valeur;
		pourdeplacer->valeur=var_prec;
		var_prec=var_temp;
		pourdeplacer=pourdeplacer->next;
	}
	
	}else{
	
	int r=rand()%100;
		pourdeplacer->valeur=r;
	//Preparer le deplacement: debut du deplacement dans la tête de la liste
	var_temp=pourdeplacer->valeur;
	pourdeplacer->valeur=0;
	var_prec=var_temp;
	pourdeplacer=pourdeplacer->next;

	//Deplacer les voitures suivantes
	while(pourdeplacer !=NULL)
	{	
		var_temp=pourdeplacer->valeur;
		pourdeplacer->valeur=var_prec;
		var_prec=var_temp ;
		pourdeplacer=pourdeplacer->next;
	}	
	element_from_liste_5->valeur=var_temp;

		}//fin else
}

void deplacement_2(chemin_vehicule *l,int recu)
{	
	//Declaration des variables
	int var_temp=0;
	int var_prec=0;
	vehicule *pourdeplacer;	
	pourdeplacer = l->tete;
	/****AJOUTE DES PROPRIETÉS POUR LE FEU*****/

	/****FIN DES PROPRIETÉS POUR LE FEU, A PARTIR DE LA LE CODE EST LE NORMAL***/
		pourdeplacer->valeur=recu;
	//Preparer le deplacement: debut du deplacement dans la tête de la liste
	var_temp=pourdeplacer->valeur;
	pourdeplacer->valeur=0;
	var_prec=var_temp;
	pourdeplacer=pourdeplacer->next;

	//Deplacer les voitures suivantes
	while(pourdeplacer !=NULL)
	{	
		var_temp=pourdeplacer->valeur;
		pourdeplacer->valeur=var_prec;
		var_prec=var_temp ;
		pourdeplacer=pourdeplacer->next;
	}	
}


int deplacement_1(chemin_vehicule *l,int compteur_vert)
{	
	//Declaration des variables
	int var_temp=0;
	int var_prec=0;
	vehicule *pourdeplacer;	
	pourdeplacer = l->tete;
	int envoie=0;
	/****AJOUTE DES PROPRIETÉS POUR LE FEU*****/

	vehicule *temp;// pour avoir acces à l'element qui es derier le element pour deplacer
	vehicule *stop;
	/*Si c'est en rouge on s'arrete fur et à mesure*/
	if(compteur_vert==1){
		/*Maintenant je deplace pour trouver la caise egal à 0 la plus près du feu rouge*/

	while(pourdeplacer->x!=58 || pourdeplacer->y!=26) 
	{
		if(pourdeplacer->valeur==0 || pourdeplacer->valeur>10) //SI la caise est vide !!!!! >10
		{
			temp=pourdeplacer;
		}	
		pourdeplacer=pourdeplacer->next;
	}
	stop=temp->next;
	//Preparer le deplacement: debut du deplacement dans la tête de la liste
	pourdeplacer=l->tete;
	int r=rand()%100;
	pourdeplacer->valeur=r;

	var_temp=pourdeplacer->valeur;
	pourdeplacer->valeur=0;
	var_prec=var_temp;
	pourdeplacer=pourdeplacer->next;
	//while(/*pourdeplacer!=temp*///pourdeplacer->y!=pos_y_vide || pourdeplacer->x!=pos_x_vide)
	while(pourdeplacer->y!=stop->y || pourdeplacer->x!=stop->x)
	{
		var_temp=pourdeplacer->valeur;
		pourdeplacer->valeur=var_prec;
		var_prec=var_temp;
		pourdeplacer=pourdeplacer->next;
	}
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	/*******************On deplace normalement le reste des voitures********************************/
	//pourdeplacer=pourdeplacer->next->next;
	while(pourdeplacer->x!=58 || pourdeplacer->y!=26)
		{pourdeplacer=pourdeplacer->next;}

	//Preparer le deplacement: debut du deplacement la suite de la liste
	var_temp=pourdeplacer->valeur;
	pourdeplacer->valeur=0;
	var_prec=var_temp;
	pourdeplacer=pourdeplacer->next;
	//Deplacer les voitures suivantes
	while(pourdeplacer !=NULL)
	{	
		var_temp=pourdeplacer->valeur;
		pourdeplacer->valeur=var_prec;
		var_prec=var_temp;
		pourdeplacer=pourdeplacer->next;
	}


	}else{ //Si c'est pas rouges!!!!
	/****FIN DES PROPRIETÉS POUR LE FEU, A PARTIR DE LA LE CODE EST LE NORMAL***/
	//Obtenir valeur aleatoire
	int r=rand()%100;
	pourdeplacer->valeur=r;
	//Preparer le deplacement: debut du deplacement dans la tête de la liste
	var_temp=pourdeplacer->valeur;
	pourdeplacer->valeur=0;
	var_prec=var_temp;
	pourdeplacer=pourdeplacer->next;

	//Deplacer les voitures suivantes
	while(pourdeplacer !=NULL)
	{	if(pourdeplacer->y==26 && pourdeplacer->x==60 && pourdeplacer->valeur>5)
		{	int choix=rand()%1;
			if(choix==0){ //si la valeur aleatoire est 0, alors on envoie la valeur à la liste 2, ensuite la valeur sera traite dans la liste 2
			envoie=pourdeplacer->valeur;
		//	pourdeplacer->valeur==0; // AVANT C'ETAIT pourdeplacer->valeur=0;????????? y a un truc bizare
		var_temp=0; //actuel = 0
		pourdeplacer->valeur=0;
		pourdeplacer=pourdeplacer->next; //actuel  = precedent
		}
		}else{
		var_temp=pourdeplacer->valeur; 
		pourdeplacer->valeur=var_prec; 
		var_prec=var_temp ; 
		pourdeplacer=pourdeplacer->next;
	}
	}
}
return envoie;}

void deplacement_pieton (chemin_vehicule *l)
{	
	//Declaration des variables
	int var_temp=0; //valeur temporelle de l'element présent
	int var_prec=0; //valeur precedent de l'element precedent LOL
	vehicule *pourdeplacer;	//element courant
	pourdeplacer = l->tete; //courant inisialisé en tete
	
	int r=rand()%100;
	pourdeplacer->valeur=r; //la valeur recu et mis dans la tete
	
	//Preparer le deplacement: debut du deplacement dans la tête de la liste.
	var_temp=pourdeplacer->valeur;
	pourdeplacer->valeur=0;
	var_prec=var_temp;
	pourdeplacer=pourdeplacer->next;

	/*Maintenant on deplace les elements suivantes, on deplace une fois d'une case touts les valeurs, 
	  c'est a dire le tram, et à cette état, cette liste de tram sera affiché */
	while(pourdeplacer !=NULL)
	{	
		var_temp=pourdeplacer->valeur;
		pourdeplacer->valeur=var_prec;
		var_prec=var_temp ;
		pourdeplacer=pourdeplacer->next;
	}	
}

/*fonction qu'inisialise le tableau à 0, c'est pour eviter des bugs au cas où*/
void reboot_tab(int line,int tableau[][150]){
	for (int i=0;i<line;i++)
		{for(int j=0;j<150;j++)
			{tableau[i][j]=0;}
		}	
}
/*Ta fonction qui sert à afficher le plan, pas modifié a part le nom du fichier */
void AffichePlan (char*nom_fichier){
  FILE *Plan = fopen(nom_fichier,"r"); 
   char c;
   while ((c=fgetc(Plan))!=EOF){

     if (c == 'p'){ printf("\033[32m");printf("🌴");printf("\033[37m");} // white   
     else if (c=='j'){  printf("\033[33m"); printf("🍁"); printf("\033[37m");}      
     else if(c=='l'){ printf("\033[32m"); printf("▒");printf("\033[37m");} 
     else if(c=='t'){ printf("\033[32m"); printf("🌷");printf("\033[37m");}               
     else if(c=='i'){ printf("\033[31m"); printf("🍁"); printf("\033[37m");}                              
     else if (c=='e'){printf("\033[31m");printf("🚓");printf("\033[37m");}  
     else if (c=='o'){ printf("\033[36m"); printf("🚐"); printf("\033[37m");}
     else if (c=='u'){ printf("\033[33m"); printf("🚙"); printf("\033[37m");}
     else if (c=='m'){ printf("\033[33m"); printf("╬"); printf("\033[37m");}
     else{ printf("%c",c);}
  }
   fclose(Plan);
 }

 void creation_des_chemins_vides(chemin_vehicule *liste_1,chemin_vehicule *liste_2,chemin_vehicule *liste_3,chemin_vehicule *liste_4,chemin_vehicule *liste_5,chemin_vehicule *liste_6,chemin_vehicule *liste_9,chemin_vehicule *liste_10,chemin_vehicule *liste_tram_to_left,chemin_vehicule *liste_tram_to_right,chemin_vehicule *trottoir3, chemin_vehicule *trottoir4, chemin_vehicule *trottoir5 ,chemin_vehicule *trottoir6, chemin_vehicule *trottoirst, chemin_vehicule *trottoir_tram_up_go, chemin_vehicule *trottoir_tram_up_arrive,chemin_vehicule *trottoir_tram_down_go, chemin_vehicule *trottoir7)
    {
 	/*Ouverture du fichier avec les coordonnes*/
    /*Chaque numero correspond eplicitement aux chemins de la photo*/
	FILE *fichier_1=NULL;
	FILE *fichier_2=NULL;
	FILE *fichier_3=NULL;
	FILE *fichier_5=NULL;
	FILE *fichier_4=NULL;
	FILE *fichier_6=NULL;
	FILE *fichier_9=NULL;
	FILE *fichier_10=NULL;
	FILE *fichier_tram_to_left=NULL;
	FILE *fichier_tram_to_right=NULL;
	FILE *fichier_pieton = NULL;
	FILE *fichier_pieton4 = NULL;
    FILE *fichier_pieton5 = NULL;
    FILE *fichier_pieton6 = NULL;
    FILE *fichier_pieton7 = NULL;
    FILE *fichier_pietonst = NULL;
    FILE *fichier_trottoir_tram_up_go = NULL;
    FILE *fichier_trottoir_tram_up_arrive=NULL;
    FILE *fichier_trottoir_tram_down_go=NULL;

	fichier_1=fopen("coordonnees_1_b.txt","r");//chemin A qui va à l'ouest et tourne au sud
	fichier_2=fopen("coordonnees_2_b.txt","r"); //chemin A qui commence au milieu et qui va à l'ouest toutdroit
	fichier_3=fopen("cordonnees_3_b.txt","r"); //chemin B qui va à l'ouest et tourne au nord
	fichier_5=fopen("cordonnees_5_b.txt","r"); //chemin C au dessus qui va à l'ouest toutdroit
	fichier_4=fopen("cordonnees_4_b.txt","r"); //chemin D qui va au nord et tourne à l'ouest
	fichier_6=fopen("cordonnees_6_b.txt","r"); //chemin qui est au dessous du C et c'est en paralléle
	fichier_9=fopen("cordonnees_9.txt","r");
	fichier_10=fopen("cordonnees_10.txt","r");
	fichier_tram_to_left=fopen("cordonnees_tram_to_left.txt","r"); //chemin du tram qui va à gauche
	fichier_tram_to_right=fopen("cordonnees_tram_to_right.txt","r"); // chemin du tram qui va à droite
	fichier_pieton = fopen("trottoir_3.txt","r");
	fichier_pieton4 = fopen("trottoir_4.txt","r");
    fichier_pieton5 = fopen("trottoir_5.txt","r");
    fichier_pieton6 = fopen("trottoir_6.txt","r");
    fichier_pieton7 = fopen("trottoir_7.txt","r");
    fichier_pietonst = fopen("trottoir_st.txt","r");
    fichier_trottoir_tram_up_go=fopen("trottoir_tram_up_go.txt","r");
    fichier_trottoir_tram_up_arrive=fopen("trottoir_tram_up_arrive.txt","r");
    fichier_trottoir_tram_down_go=fopen("trottoir_tram_down_go.txt","r");
	//Variables des cordonnees x et y
	int x=0;
	int y=0;

	/*La on crée dans le debut du programme les elements de chaque chemin qui auront seulement leurs cordonnés */
	for (int i=0 ; i<37 ;i++) //76 caises, c'est à dire 76 cordonnes dont les voiteures peuvent passer, pareils pour les autres
	{//76	
		fscanf(fichier_1, "%d %d",&y,&x);
		mettre_en_queue(liste_1,y,x);
	}

	for (int i=0;i<41;i++)
	{//82
		fscanf(fichier_2, "%d %d",&y,&x);
		mettre_en_queue(liste_2,y,x);
	}
	
	for (int i=0;i<35;i++)
	{//129
		fscanf(fichier_3, "%d %d",&y,&x);
		mettre_en_queue(liste_3,y,x);
	}
	
	for(int i=0;i<15;i++)
	{
		fscanf(fichier_4, "%d %d",&y,&x);
		mettre_en_queue(liste_4,y,x);
	}
	
	for (int i=0;i<75;i++)
	{
		fscanf(fichier_5, "%d %d",&y,&x);
		mettre_en_queue(liste_5,y,x);
	}
	
	for (int i=0;i<71;i++)
	{
		fscanf(fichier_6, "%d %d",&y,&x);
		mettre_en_queue(liste_6,y,x);
	}

	for (int i=0;i<13;i++)
	{
		fscanf(fichier_9, "%d %d",&y,&x);
		mettre_en_queue(liste_9,y,x);
	}

	for (int i=0;i<14;i++)
	{
		fscanf(fichier_10, "%d %d",&y,&x);
		mettre_en_queue(liste_10,y,x);
	}

	for (int i=0;i<142;i++)
	{
		fscanf(fichier_tram_to_left, "%d %d",&y,&x);
		mettre_en_queue(liste_tram_to_left,y,x);
	}

	for (int i=0;i<142;i++)
	{
		fscanf(fichier_tram_to_right, "%d %d",&y,&x);
		mettre_en_queue(liste_tram_to_right,y,x);
	}
	   for (int i=0;i<107;i++)
	{
		fscanf(fichier_pieton, "%d %d",&y,&x);
		mettre_en_queue(trottoir3,y,x);
	}
    
                 for (int i=0;i<64;i++)
	{
		fscanf(fichier_pieton4, "%d %d",&y,&x);
		mettre_en_queue(trottoir4,y,x);
	}
           for (int i=0;i<64;i++)
	{
		fscanf(fichier_pieton5, "%d %d",&y,&x);
		mettre_en_queue(trottoir5,y,x);
	}

	          for (int i=0;i<33;i++)
	{
		fscanf(fichier_pieton6, "%d %d",&y,&x);
		mettre_en_queue(trottoir6,y,x);
	}
              for (int i=0;i<38;i++)
	{
		fscanf(fichier_pietonst, "%d %d",&y,&x);
		mettre_en_queue(trottoirst,y,x);
	}

	          for (int i=0;i<37;i++)
	{
		fscanf(fichier_trottoir_tram_up_go, "%d %d",&y,&x);
		mettre_en_queue(trottoir_tram_up_go,y,x);
	}

	          for (int i=0;i<31;i++)
	{
		fscanf(fichier_trottoir_tram_up_arrive, "%d %d",&y,&x);
		mettre_en_queue(trottoir_tram_up_arrive,y,x);
	}

	          for (int i=0;i<31;i++)
	{
		fscanf(fichier_trottoir_tram_down_go, "%d %d",&y,&x);
		mettre_en_queue(trottoir_tram_down_go,y,x);
	}

	          for (int i=0;i<50;i++)
	{
		fscanf(fichier_pieton7, "%d %d",&y,&x);
		mettre_en_queue(trottoir7,y,x);
	}

	//Fermeture du fichier avec les coordonnees car on n'a plus besoin
	fclose(fichier_1);
	fclose(fichier_2);
	fclose(fichier_3);
	fclose(fichier_5);
	fclose(fichier_4);
	fclose(fichier_6);
	fclose(fichier_9);
	fclose(fichier_10);
	fclose(fichier_tram_to_left);
	fclose(fichier_tram_to_right);
	fclose(fichier_pieton);
	fclose(fichier_pieton4);
    fclose(fichier_pieton5);
 	fclose(fichier_pieton6);
 	fclose(fichier_pieton7);
    fclose(fichier_pietonst);
    fclose(fichier_trottoir_tram_up_go);
    fclose(fichier_trottoir_tram_up_arrive);
    fclose(fichier_trottoir_tram_down_go);
 }

 void feu_tab(int a,int b,int c,int line,int tableau[][150])
 {
	if(a==1) //Si c'est vert, on fait ça
	{   /*1 si c'est vert, 0 si c'est rouge, on les mets dans les cordonnées de la map mais dans le tableau 2D passé en paramettre*/
		/*D'abord dans un tableau sont les lignes et apres les colonnes*/
		
		/*ATENTION ! Peut etre 1 est rouge et 0 est vert*/
		tableau[26][58]=1; //feu du chemin 1
		tableau[24][58]=0; //feu du chemin 3
		tableau[29][66]=0; //feu du chemin 4
		tableau[14][69]=1; //feu du chemin 5
		tableau[16][69]=1; //feu du chemin 6
		tableau[20][69]=1; //feu du tram qui va à gauche
		tableau[20][56]=1; //feu du tram qui va à droite
		//31=rouge, 32=vert
		printf("\033[27;58f");printf("\033[31m"); printf("█"); printf("\033[37m");
		printf("\033[23;58f");printf("\033[32m"); printf("█"); printf("\033[37m");
		printf("\033[29;68f");printf("\033[32m"); printf("█"); printf("\033[37m");
		printf("\033[13;69f");printf("\033[31m"); printf("█"); printf("\033[37m");
		printf("\033[17;69f");printf("\033[31m"); printf("█"); printf("\033[37m");
		printf("\033[20;70f");printf("\033[31m"); printf("█"); printf("\033[37m");
		printf("\033[20;56f");printf("\033[31m"); printf("█"); printf("\033[37m");
	}
		if(b==1){
		tableau[26][58]=1; //feu du chemin 1
		tableau[24][58]=1; //feu du chemin 3
		tableau[29][66]=1; //feu du chemin 4
		tableau[14][69]=1; //feu du chemin 5
		tableau[16][69]=1; //feu du chemin 6
		tableau[20][69]=1; //feu du tram qui va à gauche
		tableau[20][56]=1; //feu du tram qui va à droite
		
		printf("\033[27;58f");printf("\033[33m"); printf("█"); printf("\033[37m");
		printf("\033[23;58f");printf("\033[33m"); printf("█"); printf("\033[37m");
		printf("\033[29;68f");printf("\033[33m"); printf("█"); printf("\033[37m");
		printf("\033[13;69f");printf("\033[33m"); printf("█"); printf("\033[37m");
		printf("\033[17;69f");printf("\033[33m"); printf("█"); printf("\033[37m");
		printf("\033[20;70f");printf("\033[33m"); printf("█"); printf("\033[37m");
		printf("\033[20;56f");printf("\033[33m"); printf("█"); printf("\033[37m");
		}
		if(c==1){
		//sinon, c'est rouge
		tableau[26][58]=0; //feu du chemin 1
		tableau[24][58]=1; //feu du chemin 3
		tableau[29][66]=1; //feu du chemin 4
		tableau[14][69]=0; //feu du chemin 5
		tableau[16][69]=0; //feu du chemin 6
		tableau[20][69]=0; //feu du tram qui va à gauche
		tableau[20][56]=0; //feu du tram qui va à droite
		
		printf("\033[27;58f");printf("\033[32m"); printf("█"); printf("\033[37m");
		printf("\033[23;58f");printf("\033[31m"); printf("█"); printf("\033[37m");
		printf("\033[29;68f");printf("\033[31m"); printf("█"); printf("\033[37m");
		printf("\033[13;69f");printf("\033[32m"); printf("█"); printf("\033[37m");
		printf("\033[17;69f");printf("\033[32m"); printf("█"); printf("\033[37m");
		printf("\033[20;70f");printf("\033[32m"); printf("█"); printf("\033[37m");
		printf("\033[20;56f");printf("\033[32m"); printf("█"); printf("\033[37m");
	}
	}

/*Fonction qui appelle à la fonction afficher pour afficher les voitures , c'est à dire, afficher les listes*/
 void affichages_des_voitures(chemin_vehicule *liste_1,chemin_vehicule *liste_2,chemin_vehicule *liste_3,chemin_vehicule *liste_4,chemin_vehicule *liste_5,chemin_vehicule *liste_6,chemin_vehicule *liste_9,chemin_vehicule *liste_10)
 {
 	afficher(liste_1);
	fflush(stdout);
	afficher(liste_2);
	fflush(stdout);
	afficher(liste_3);
	fflush(stdout);
	afficher(liste_5);
	afficher(liste_4);
	fflush(stdout);
	afficher(liste_6);
	afficher(liste_9);
	fflush(stdout);
	afficher(liste_10);
	fflush(stdout);
 }

 void affichages_pieton(chemin_vehicule *l)
{
	/*Ici on affiche tout la liste qui va de l'extrem est à l'extreme ouest, c'est à dire que la liste
	traverse la map, ainsi le tram s'affiche en tout point de la raie dessinée*/
	vehicule *pourmontrer;	
	pourmontrer = l->tete;
	while(pourmontrer!=NULL)
	{
		fflush(stdout);
		printf("\033[%d;%df",pourmontrer->y,pourmontrer->x);
		if(pourmontrer->valeur==0 || pourmontrer->valeur >10)// si la valeur est >10 ou 0, on affiche le vide
			{printf(" ");}
		else{
		switch(pourmontrer->valeur)
		{
			case 1:
				printf("\033[37m"); printf("🚶‍"); printf("\033[37m");//🚙 🚶‍♀️🚶🚶‍♀️🏃🚖🚘
				break;
				case 2:
				printf("\033[37m"); printf("🚶‍"); printf("\033[37m");//🚕
				break;
				case 3:
				printf("\033[37m"); printf("🚶‍"); printf("\033[37m");
				break;
				case 4:
				printf("\033[37m"); printf("🚶‍"); printf("\033[37m");
				break;
				case 5:
				printf("\033[37m"); printf("🚶‍"); printf("\033[37m");
				break;
				case 6:
				printf("\033[36m"); printf("🚶‍"); printf("\033[37m");
				break;//37
				case 7:
				printf("\033[36m"); printf("🚶‍"); printf("\033[37m");
				break;
				case 8:
				printf("\033[36m"); printf("🚶‍"); printf("\033[37m");
				break;
				case 9:
				printf("\033[36m"); printf("🚶‍"); printf("\033[37m");
				break;
				case 10:
				printf("\033[36m"); printf("🚶‍"); printf("\033[37m");
				break;
		}
	//civil = civil->next; //on passe à l'element suivant pour l'afficher
		//on affiche rien s'il y a ni 2 ni 3
		
	}
	pourmontrer=pourmontrer->next;
	}
}

/*Fonction qui envoie l'adresse de l'element qui se trouve dans la cordonné d'intersection entre le chemin 4 et 5*/
vehicule *send_adress_5(chemin_vehicule *l){
 	vehicule *element;
 	element=l->tete;
 	for(int i=0;i<14;i++){element=element->next;}
 	return element;
 }
/*Fonction qui envoie l'adresse de l'element qui se trouve dans la cordonné d'intersection entre le chemin 3 et 6*/
vehicule *send_adress_6(chemin_vehicule *l){
 	vehicule *element;
 	element=l->tete;
 	for(int i=0;i<34;i++){element=element->next;} //67
 	return element;
 }

vehicule *send_adress_5_for_9(chemin_vehicule *l){
 	vehicule *element;
 	element=l->tete;
 	for(int i=0;i<21;i++){element=element->next;}
 	return element;
 }

  char key_pressed()
{
	struct termios oldterm, newterm;
	int oldfd; char c, result = 0;
	tcgetattr (STDIN_FILENO, &oldterm);
	newterm = oldterm; newterm.c_lflag &= ~(ICANON | ECHO);
	tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
	oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
	c = getchar();
	tcsetattr (STDIN_FILENO,TCSANOW,&oldterm);
	fcntl (STDIN_FILENO, F_SETFL, oldfd);
	if(c!=EOF)
		{ungetc(c, stdin); result = getchar();}
	return result;
}

 void fluide_mode(int game){
 	int count_cycle=0;
 	system("clear");
system("play -q son_city.mp3 repeat 10000 &");
	//Declaration des listes des chemins des voitures et initialisation
	chemin_vehicule liste_1, liste_2, liste_3, liste_4, liste_5, liste_6, liste_9, liste_10;
	chemin_vehicule liste_tram_to_left,liste_tram_to_right,trottoir,trottoir4,trottoir5, trottoir6,trottoirst,trottoir7;
	chemin_vehicule trottoir_tram_up_go,trottoir_tram_up_arrive,trottoir_tram_down_go;
	
	/*Initialisation des listes des vehicules*/
	init_vehicule(&liste_1);
	init_vehicule(&liste_2);
	init_vehicule(&liste_3);
	init_vehicule(&liste_4);
	init_vehicule(&liste_5);
	init_vehicule(&liste_6);
	init_vehicule(&liste_9);
	init_vehicule(&liste_10);
	init_vehicule(&liste_tram_to_left);
	init_vehicule(&liste_tram_to_right);
	init_vehicule(&trottoir);
	init_vehicule(&trottoir4);
    init_vehicule(&trottoir5);
	init_vehicule(&trottoir6);
	init_vehicule(&trottoir7);
    init_vehicule(&trottoirst);
    init_vehicule(&trottoir_tram_up_go);
    init_vehicule(&trottoir_tram_down_go);
    init_vehicule(&trottoir_tram_up_arrive);

	/* Declaration du tableau 2D*/
	int col=150;
	int line=150;
	int tableau[line][col];

	/*Inisialisation du tableau*/
	reboot_tab(line,tableau);	
	
	/*Creation des chemins vides des voitures avec leur coordonnés*/
	creation_des_chemins_vides(&liste_1,&liste_2,&liste_3,&liste_4,&liste_5,&liste_6,&liste_9,&liste_10,&liste_tram_to_left,&liste_tram_to_right,&trottoir,&trottoir4,&trottoir5,&trottoir6,&trottoirst,&trottoir_tram_up_go,&trottoir_tram_up_arrive,&trottoir_tram_down_go,&trottoir7);

	//Affichage de la ville
	char plan[]="officialplan_3.txt";
//	printf("Voila\n");
	AffichePlan(plan);

	//variable constante qui sert à ne pas arreter le programme
	int constante=3;

	//Variables du feu rouge_vert de la liste_1
	int compteur_vert =0;
	int compteur_rouge = 0;
	int compteur_tram_to_left=0;
	int compteur_delay_feu=0;
	int a=0;
	int b=0;
	int c=0;
	int dep_pieton=0;
	int station_tram_down=0;
	int station_tram_up=0;
	//int show_trottoir_tram_up=0;
	//Variable longueur du tram;
	int longueur_tram=0;
	int stop_apparition_du_tram_to_left=0;
//	printf("Voila\n");
	/****************Ville qui circulle normallement*********************/

	/*Nouvelle manière d'envoyer les voitures dans une autre liste*/
	/*Je recupere l'adresse des elements dont les voitures peuvent changer de chemin
	grace à cette adresse, je peut recuperer les voitures des ces elements sans faire des
	longs opperations, je passe ces valeurs (voitures) en parametre et puis c'est bon, je 
	le fais dans les fonctions put_in_liste_5_from_liste_4 et put_in_liste_6_from_liste_3,
	je pourrais le faire pour le deplacement_1 et 2 qui font un calcul chelou pour mettre la voiture dans le chemin 2*/
	vehicule *element_from_liste_4=NULL;
	vehicule *element_from_liste_3=NULL;
	vehicule *element_from_liste_5=NULL;
//	printf("Voila\n");
	element_from_liste_4=send_adress_5(&liste_4);
	element_from_liste_3=send_adress_6(&liste_3);
	element_from_liste_5=send_adress_5_for_9(&liste_5);

//	printf("Voila\n");

	/*Fonctions sans arrete qui fait bouger la ville*/ 

	/*Les fonctions deplacement_x representent le deplacement 
	des voitures de chaque liste, leur numero correspondent au numero du chemin*/
	int played=0;
	if(game==0){
	while(constante==3){
		if(key_pressed()=='q')
			{constante=0;}
	//Deplacer les valeurs
	fflush(stdout); //ne pas supprimer, sinon ça saute un deplacement total
	
	/*****************liste_1 avec feu rouge et vert dans le coin*********/
	if(played==0)
	{
	//system("play -q 'son_city.mp3' repeat 1000000 &");
	played=1;
	}
	feu_tab(a,b,c,line,tableau);
	/*****************Compteur d'apparition du tram_to_left****************/
//	printf("Voila 5\n");
	//à 250, le tram apparait, sinon j'incremente
	if(compteur_tram_to_left<250){compteur_tram_to_left++;}
	else{
		if(longueur_tram<8)
		{//Le tram commence à apparaitre
			if(longueur_tram==0)
				{system("play -q 'son_tram.mp3' &");}
		deplacement_tram_to_left(&liste_tram_to_left,2); 
		deplacement_tram_to_left(&liste_tram_to_right,2);longueur_tram++;}
		else{
			if(longueur_tram==8)
				{//J'ajoute une image du raie à la fin de la liste, ainsi on laisse pas vide le chemin apres le deplacement
				deplacement_tram_to_left(&liste_tram_to_left,3);
				deplacement_tram_to_left(&liste_tram_to_right,3);longueur_tram=9;}
					else{//je fais un deplacement normal 

					//	if()

						if(tableau[21][46]==0 || tableau[21][53]==0 || tableau[20][56]==0)
						{

							if(tableau[21][105]>0 && tableau[21][112]>0 && station_tram_down<200)
							{
								station_tram_down++;
							}else{
								deplacement_tram_to_left(&liste_tram_to_right,0);
							}
						
						}else{
							if(tableau[20][56]!=1){
								deplacement_tram_to_left(&liste_tram_to_right,0);
						}}

						if(tableau[19][71]==0 || tableau[19][78]==0 || tableau[20][56]==0)
						{

							if(tableau[19][105]>0 && tableau[19][112]>0 && station_tram_up<200)
							{

								station_tram_up++;

							}else{
								deplacement_tram_to_left(&liste_tram_to_left,0);
							}
						
						}else{
							if(tableau[20][56]!=1){
								deplacement_tram_to_left(&liste_tram_to_left,0);
						}}					
					
					}
			}
		stop_apparition_du_tram_to_left++;
	}
//	printf("Voila 6\n");
	/************Mettre des feus rouges et verts dans les cordonnees*******/
//	feu_tab(a,b,c,line,tableau);

	/*****************Deplacement total des voitures******************/

	int dep_est=deplacement_1(&liste_1,tableau[26][58]);	//chemin A :on deplace les voitures de &liste_1 et on envoie les "1" ou "0" s'il n'y a pas de voitures qui continue tout droit
	deplacement_2(&liste_2,dep_est); //chemin A on deplace les voitures qui continuent tout droit de la liste precedent (les 1 continuent tout droit et la fonction re^oit en paramettre "0" ou "1")
	
	/******************Reinisialisation des compteurs***********/
	if(compteur_vert<125 && compteur_delay_feu==0 && compteur_rouge==0)
	{
		a=1;
		b=0;
		c=0;
		compteur_vert++;
	}
	if(compteur_vert==125 && compteur_delay_feu<40 && compteur_rouge==0)
	{
		a=0;
		b=1;
		c=0;
		compteur_delay_feu++;
	}
	if(compteur_vert==125 && compteur_delay_feu==40 && compteur_rouge<125)
	{
		a=0;
		b=0;
		c=1;
		compteur_rouge++;
	
	if(compteur_rouge==125 && compteur_delay_feu==40)
	{
	//	compteur_rouge=0;
	//	compteur_vert=0;
		compteur_delay_feu=0;
	}

	}

	if(compteur_vert==125 && compteur_delay_feu<40 && compteur_rouge==125)
		{
		a=0;
		b=1;
		c=0;
		compteur_delay_feu++;
	
	if(compteur_vert==125 && compteur_delay_feu==40 && compteur_rouge==125)
		{
		compteur_rouge=0;
		compteur_vert=0;
		compteur_delay_feu=0;
		a=1;
		b=0;
		c=0;
	}


	}


	if (stop_apparition_du_tram_to_left==700)
	{
		stop_apparition_du_tram_to_left=0;
		compteur_tram_to_left=0;
		longueur_tram=0;
		station_tram_down=0;
		station_tram_up=0;
	}
//	printf("Voila 7\n");
	if(dep_pieton==3)
	{
	deplacement_pieton(&trottoir); // test du mouvement du pieton
        deplacement_pieton(&trottoir4);
        deplacement_pieton(&trottoir5);
         deplacement_pieton(&trottoir6);
        deplacement_pieton(&trottoirst);
    	deplacement_pieton(&trottoir7);
    	if(tableau[19][105]>0 && tableau[19][112]>0 && station_tram_up<200) //200
    		{deplacement_pieton_tram_go(&trottoir_tram_up_go,0,0,105,18);} //a
    	else{
    		deplacement_pieton_tram_go(&trottoir_tram_up_go,1,1,105,18);
    		}

    	if(tableau[21][105]>0 && tableau[21][112]>0 && station_tram_down<200) //200
    		{deplacement_pieton_tram_go(&trottoir_tram_down_go,0,0,112,22);} //a
    	else{
    		deplacement_pieton_tram_go(&trottoir_tram_down_go,1,1,112,22);
    		}	


    	}
    /*	*/
	//	deplacement_pieton_tram_go(&trottoir_tram_up_go,1);
	
	//un deplacement sur 2 fait le pieton
	if(dep_pieton<3){dep_pieton++;}
	else{dep_pieton=0;}
//	printf("Voila 8\n");
	deplacement_3(&liste_3,tableau[24][58]);			//chemin B se deplace 
//	printf("Voila 9\n");
	dep_est=deplacement_4(&liste_4,tableau[29][66]);//chemin D se deplace
	put_in_liste_2_from_liste_4(&liste_2,dep_est);
	put_in_liste_5_from_liste_4(&liste_5,element_from_liste_4->valeur);
//	printf("Voila 10\n");
	put_in_liste_6_from_liste_3(&liste_6,element_from_liste_3->valeur);
//	printf("Voila 11\n");
	int cart_to_10=deplacement_5(&liste_5,tableau[14][69]);	//chemin C se deplace
	deplacement_6(&liste_6,tableau[16][69]);
	deplacement_9(&liste_9,element_from_liste_5->valeur,element_from_liste_5);
	deplacement_10(&liste_10,cart_to_10);

	/*Mise à jour du tabeau*/
	reboot_tab(line,tableau); //Reinisialisation du tableau;
	rewrite_tab(&liste_1,line,tableau); 
	rewrite_tab(&liste_2,line,tableau);
	rewrite_tab(&liste_3,line,tableau);
	rewrite_tab(&liste_5,line,tableau);
	rewrite_tab(&liste_4,line,tableau);
	rewrite_tab(&liste_6,line,tableau);
	rewrite_tab(&liste_9,line,tableau);
	rewrite_tab(&liste_10,line,tableau);
	rewrite_tab(&trottoir,line,tableau);
	rewrite_tab(&liste_tram_to_left,line,tableau);
	rewrite_tab(&liste_tram_to_right,line,tableau);
	//Affichage des voitures deplacés
   	affichages_des_voitures(&liste_1,&liste_2,&liste_3,&liste_4,&liste_5,&liste_6,&liste_9,&liste_10);
   	affichages_des_trams(&liste_tram_to_left);
   	affichages_des_trams(&liste_tram_to_right);
   	   	affichages_pieton(&trottoir);
        affichages_pieton(&trottoir4);
        affichages_pieton(&trottoir5);
        affichages_pieton(&trottoir6);
        affichages_pieton(&trottoir7);
        affichages_pieton(&trottoirst);
       
        affichages_pieton(&trottoir_tram_up_go);
        affichages_pieton(&trottoir_tram_down_go);
	usleep(80000);
	}
	

	}else{

		while(count_cycle<200){
	//Deplacer les valeurs
	fflush(stdout); //ne pas supprimer, sinon ça saute un deplacement total
	
	/*****************liste_1 avec feu rouge et vert dans le coin*********/
	if(played==0)
	{
	//system("play -q 'son_city.mp3' repeat 1000000 &");
	played=1;
	}
	feu_tab(a,b,c,line,tableau);
	/*****************Compteur d'apparition du tram_to_left****************/
//	printf("Voila 5\n");
	//à 250, le tram apparait, sinon j'incremente
	if(compteur_tram_to_left<250){compteur_tram_to_left++;}
	else{
		if(longueur_tram<8)
		{//Le tram commence à apparaitre
			if(longueur_tram==0)
				{system("play -q 'son_tram.mp3' &");}
		deplacement_tram_to_left(&liste_tram_to_left,2); 
		deplacement_tram_to_left(&liste_tram_to_right,2);longueur_tram++;}
		else{
			if(longueur_tram==8)
				{//J'ajoute une image du raie à la fin de la liste, ainsi on laisse pas vide le chemin apres le deplacement
				deplacement_tram_to_left(&liste_tram_to_left,3);
				deplacement_tram_to_left(&liste_tram_to_right,3);longueur_tram=9;}
					else{//je fais un deplacement normal 

					//	if()

						if(tableau[21][46]==0 || tableau[21][53]==0 || tableau[20][56]==0)
						{

							if(tableau[21][105]>0 && tableau[21][112]>0 && station_tram_down<200)
							{
								station_tram_down++;
							}else{
								deplacement_tram_to_left(&liste_tram_to_right,0);
							}
						
						}else{
							if(tableau[20][56]!=1){
								deplacement_tram_to_left(&liste_tram_to_right,0);
						}}

						if(tableau[19][71]==0 || tableau[19][78]==0 || tableau[20][56]==0)
						{

							if(tableau[19][105]>0 && tableau[19][112]>0 && station_tram_up<200)
							{

								station_tram_up++;

							}else{
								deplacement_tram_to_left(&liste_tram_to_left,0);
							}
						
						}else{
							if(tableau[20][56]!=1){
								deplacement_tram_to_left(&liste_tram_to_left,0);
						}}					
					
					}
			}
		stop_apparition_du_tram_to_left++;
	}
//	printf("Voila 6\n");
	/************Mettre des feus rouges et verts dans les cordonnees*******/
//	feu_tab(a,b,c,line,tableau);

	/*****************Deplacement total des voitures******************/

	int dep_est=deplacement_1(&liste_1,tableau[26][58]);	//chemin A :on deplace les voitures de &liste_1 et on envoie les "1" ou "0" s'il n'y a pas de voitures qui continue tout droit
	deplacement_2(&liste_2,dep_est); //chemin A on deplace les voitures qui continuent tout droit de la liste precedent (les 1 continuent tout droit et la fonction re^oit en paramettre "0" ou "1")
	
	/******************Reinisialisation des compteurs***********/
	if(compteur_vert<125 && compteur_delay_feu==0 && compteur_rouge==0)
	{
		a=1;
		b=0;
		c=0;
		compteur_vert++;
	}
	if(compteur_vert==125 && compteur_delay_feu<40 && compteur_rouge==0)
	{
		a=0;
		b=1;
		c=0;
		compteur_delay_feu++;
	}
	if(compteur_vert==125 && compteur_delay_feu==40 && compteur_rouge<125)
	{
		a=0;
		b=0;
		c=1;
		compteur_rouge++;
	
	if(compteur_rouge==125 && compteur_delay_feu==40)
	{
	//	compteur_rouge=0;
	//	compteur_vert=0;
		compteur_delay_feu=0;
	}

	}

	if(compteur_vert==125 && compteur_delay_feu<40 && compteur_rouge==125)
		{
		a=0;
		b=1;
		c=0;
		compteur_delay_feu++;
	
	if(compteur_vert==125 && compteur_delay_feu==40 && compteur_rouge==125)
		{
		compteur_rouge=0;
		compteur_vert=0;
		compteur_delay_feu=0;
		a=1;
		b=0;
		c=0;
	}


	}


	if (stop_apparition_du_tram_to_left==700)
	{
		stop_apparition_du_tram_to_left=0;
		compteur_tram_to_left=0;
		longueur_tram=0;
		station_tram_down=0;
		station_tram_up=0;
	}
//	printf("Voila 7\n");
	if(dep_pieton==3)
	{
	deplacement_pieton(&trottoir); // test du mouvement du pieton
        deplacement_pieton(&trottoir4);
        deplacement_pieton(&trottoir5);
         deplacement_pieton(&trottoir6);
        deplacement_pieton(&trottoirst);
    	deplacement_pieton(&trottoir7);
    	if(tableau[19][105]>0 && tableau[19][112]>0 && station_tram_up<200) //200
    		{deplacement_pieton_tram_go(&trottoir_tram_up_go,0,0,105,18);} //a
    	else{
    		deplacement_pieton_tram_go(&trottoir_tram_up_go,1,1,105,18);
    		}

    	if(tableau[21][105]>0 && tableau[21][112]>0 && station_tram_down<200) //200
    		{deplacement_pieton_tram_go(&trottoir_tram_down_go,0,0,112,22);} //a
    	else{
    		deplacement_pieton_tram_go(&trottoir_tram_down_go,1,1,112,22);
    		}	


    	}
    /*	*/
	//	deplacement_pieton_tram_go(&trottoir_tram_up_go,1);
	
	//un deplacement sur 2 fait le pieton
	if(dep_pieton<3){dep_pieton++;}
	else{dep_pieton=0;}
//	printf("Voila 8\n");
	deplacement_3(&liste_3,tableau[24][58]);			//chemin B se deplace 
//	printf("Voila 9\n");
	dep_est=deplacement_4(&liste_4,tableau[29][66]);//chemin D se deplace
	put_in_liste_2_from_liste_4(&liste_2,dep_est);
	put_in_liste_5_from_liste_4(&liste_5,element_from_liste_4->valeur);
//	printf("Voila 10\n");
	put_in_liste_6_from_liste_3(&liste_6,element_from_liste_3->valeur);
//	printf("Voila 11\n");
	int cart_to_10=deplacement_5(&liste_5,tableau[14][69]);	//chemin C se deplace
	deplacement_6(&liste_6,tableau[16][69]);
	deplacement_9(&liste_9,element_from_liste_5->valeur,element_from_liste_5);
	deplacement_10(&liste_10,cart_to_10);

	/*Mise à jour du tabeau*/
	reboot_tab(line,tableau); //Reinisialisation du tableau;
	rewrite_tab(&liste_1,line,tableau); 
	rewrite_tab(&liste_2,line,tableau);
	rewrite_tab(&liste_3,line,tableau);
	rewrite_tab(&liste_5,line,tableau);
	rewrite_tab(&liste_4,line,tableau);
	rewrite_tab(&liste_6,line,tableau);
	rewrite_tab(&liste_9,line,tableau);
	rewrite_tab(&liste_10,line,tableau);
	rewrite_tab(&trottoir,line,tableau);
	rewrite_tab(&liste_tram_to_left,line,tableau);
	rewrite_tab(&liste_tram_to_right,line,tableau);
	//Affichage des voitures deplacés
   	affichages_des_voitures(&liste_1,&liste_2,&liste_3,&liste_4,&liste_5,&liste_6,&liste_9,&liste_10);
   	affichages_des_trams(&liste_tram_to_left);
   	affichages_des_trams(&liste_tram_to_right);
   	   	affichages_pieton(&trottoir);
        affichages_pieton(&trottoir4);
        affichages_pieton(&trottoir5);
        affichages_pieton(&trottoir6);
        affichages_pieton(&trottoir7);
        affichages_pieton(&trottoirst);
       
        affichages_pieton(&trottoir_tram_up_go);
        affichages_pieton(&trottoir_tram_down_go);
	usleep(80000);
	count_cycle++;
	}

	}

 }

void AfficheEnter(char*nom_fichier){
   FILE *Enter = fopen(nom_fichier,"r"); 
   char c;
   while ((c=fgetc(Enter))!=EOF){
   if (c == 'i'){ printf("\033[32m");printf("🌴");printf("\033[37m");}
   else if (c=='o'){printf("\033[37m"); printf("▒"); printf("\033[37m");}
   else if(c=='b'){printf("\033[31m"); printf("🌷");printf("\033[37m");}
   else if (c == 'u'){ printf("\033[33m");printf("🍁");printf("\033[37m");}
   else{ printf("%c",c);} 
 }  fclose(Enter);
  }


int main(){
	srand ( time (NULL) );
	system("clear");
	int choice=0;
	int tab_clignotage[6]={0,1,2,3,4,5};
	int compteur=0;
	char election='a';
	int constante=3;
	while(constante==3){
	//AfficheEnter("enterPlan");
	system("clear");
	do{
		fflush(stdout);
		clignotage_panneau(&compteur,6,tab_clignotage);
		if(compteur<250){compteur++;}else{compteur=0;}
	printf("\nAppuyez sur '1' pour initialiser le mode fluide\n");
	printf("Appuyez sur '2' pour initialiser le mode chaos\n");
	printf("Appuyez sur '3' pour inisialiter le mode game\n");
	printf("INFO: Appuyez sur 'q' si vous voulez sortir du mode fluide ou du mode chaos \n");
	printf("INFO: Pour sortir du mode game, il faut jouer et finir la partie \n");
	printf("INFO: SI vous avez des problemes d'affichages, reduisez la taille du terminal avec 'CTRL-'\n");
	usleep(80000);
	election=key_pressed();
	}while(election!='1' && election!='2' && election!='3');


	if(election=='1')
	{
		fluide_mode(0);
	}
	if(election=='2')
	{
		caos_mode();
	}
	if(election=='3')
	{	
		int scanned=0;
	//	system("clear");

		printf("\nCombien des touches du clavier est-tu capables de faire en 15 secondes pour sauver la ville d'une bombe atomique?\n");
		printf("Rentre une valeur plus grande que 200 pour voir si tu es vraiment un héro, le test commence rapidement\n");
		scanf("%d",&scanned);
		int lose_game=0;
		int combien_touches=0;
	//	system("clear");
		//	printf("En 7 secondes le jeu commencera");
	//	printf("En 7 secondes le jeu commencera");
	//	usleep(1500000);
	//	printf("Tape plus de %d touches pour sauver la ville, ATTENTION",scanned);
	//	sleep(5);
		fluide_mode(1);
		for(int i=0;i<scanned;i++)
		{
			if(key_pressed()=='\0')
			{
				lose_game=1;
			}else{
				combien_touches++;
			}
		}
			if(lose_game==1)
			{	
				system("clear");
				system("killall play");
				system("play -q 'wtf boom.mp3' &");
				//printf("\033[1;1f");printf("game_over_you_lose");
				for(int k=0;k<7;k++)
				{
				boom();
				usleep(600000);
				system("clear");
				usleep(600000);
				}
			}else{
				system("clear");
				system("killall play");
				system("play -q 'piano.mp3' &");
				while(key_pressed()!='q'){
				clignotage_gagnant(&compteur,6,tab_clignotage);
		if(compteur<250){compteur++;}else{compteur=0;}
				}
			}
		}
	
	system("clear");
	system("killall play");
	good_bye();

	printf("Aimeriez vous continuer à jouer? (N'importe quelle valeur)=Oui | 2=Non\n");
	scanf("%d",&choice);
	if(choice==2){
		constante=0;
	}else{
		constante=3;
	}

}
	return 0;
}