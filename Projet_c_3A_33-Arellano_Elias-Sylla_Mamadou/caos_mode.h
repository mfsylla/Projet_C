#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <time.h>

/*Structure pour creer une voiture*/
struct vehicule_caos
{
	int valeur;
	int x;
	int y;
	struct vehicule_caos *next;
};
typedef struct vehicule_caos vehicule_caos;

/*Structure qui contien la liste des voitures, c'est è dire le chemin des voitures*/
struct chemin_vehicule_caos
{
	vehicule_caos *queue;
	vehicule_caos *tete;
	int size;
};
typedef struct chemin_vehicule_caos chemin_vehicule_caos;

/*Fonction qui sert à inisialiter le chemin des voitures à vide, techniquement c'est une liste vide au debut*/
void init_vehicule_caos(chemin_vehicule_caos *l)
{
	l->queue=NULL;
	l->tete=NULL;	
	l->size=0;	    
}

/*Cette fonction met en queue les elements de la liste, c'est à dire on crée au debut du program les chemins avec leur coordonés, cette fonction est appellé seulement une fois */
void mettre_en_queue_caos(chemin_vehicule_caos *l,int y,int x)
{
	//Ouvrir le fichier avec les coordonnees
	if(l->size==0)
		{
		vehicule_caos *nouveau = malloc(sizeof(vehicule_caos));
		
		nouveau->valeur=0;
		nouveau->x=x;
		nouveau->y=y;
		nouveau->next=NULL;
		
		l->tete=nouveau;
		l->queue=nouveau;
		l->size=l->size+1;
		
		}else{
			vehicule_caos *nouveau = malloc(sizeof(vehicule_caos));
			nouveau->valeur=0;
			nouveau->x=x;
			nouveau->y=y;
			l->queue->next = nouveau;
			l->queue = nouveau;
			l->size = l->size+1;
		}
}

/*Fonction special qui sert à afficher le tram*/
void affichages_des_trams_caos(chemin_vehicule_caos *l)
{
	/*Ici on affiche tout la liste qui va de l'extrem est à l'extreme ouest, c'est à dire que la liste
	traverse la map, ainsi le tram s'affiche en tout point de la raie dessinée*/
	vehicule_caos *pourmontrer;	
	pourmontrer = l->tete;
	while(pourmontrer!=NULL)
	{
		printf("\033[%d;%df",pourmontrer->y,pourmontrer->x);
		switch(pourmontrer->valeur)
		{
			case 2: //si c'est 2, on affiche un morceau du tram
			printf("🚙"); //plusieurs voitures en ligne representent un tram
			break;
			case -1: //si c'est 3, on affiche un morceau de la raie
			printf("─"); //on affiche un morceau de raie à la fin de la liste pour écrasser les voitures qui restent afficher en arriere du tram deplacé
			break;
			/*case 1:
			printf("─"3);
			break;*/
		}
		pourmontrer=pourmontrer->next; //on passe à l'element suivant pour l'afficher
		//on affiche rien s'il y a ni 2 ni 3
	}
}

/*Fonction special qui sert à afficher les voitures*/

void afficher_ambu(chemin_vehicule_caos *l)
{
	vehicule_caos *pourmontrer;	
	pourmontrer = l->tete;
	while(pourmontrer !=NULL)
	{	
		printf("\033[%d;%df",pourmontrer->y,pourmontrer->x);
		if(pourmontrer->valeur==0)// si la valeur est >10 ou 0, on affiche le vide
			{printf(" ");}
		else{
				printf("\033[37m"); printf("🚑"); printf("\033[37m");	
			}
		  pourmontrer=pourmontrer->next; //on passe à l'element suivant pour l'afficher
	}	 
}


void afficher_caos(chemin_vehicule_caos *l)
{
	vehicule_caos *pourmontrer;	
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
				/*case 1:
				printf("\033[31m"); printf("🚙"); printf("\033[37m");
				break;
				case 2:
				printf("\033[32m"); printf("🚙"); printf("\033[37m");
				break;
				case 3:
				printf("\033[33m"); printf("🚙"); printf("\033[37m");
				break;
				case 4:
				printf("\033[34m"); printf("🚙"); printf("\033[37m");
				break;
				case 5:
				printf("\033[35m"); printf("🚙"); printf("\033[37m");
				break;
				case 6:
				printf("\033[36m"); printf("🚙"); printf("\033[37m");
				break;
				case 7:
				printf("\033[31m"); printf("🚐"); printf("\033[37m");
				break;
				case 8:
				printf("\033[32m"); printf("🚐"); printf("\033[37m");
				break;
				case 9:
				printf("\033[33m"); printf("🚐"); printf("\033[37m");
				break;
				case 10:
				printf("\033[33m"); printf("🚙"); printf("\033[37m");
				break;
				case 101:
				printf("\033[37m"); printf("🚑"); printf("\033[37m");
				break;*/
			}
		 }
		  pourmontrer=pourmontrer->next; //on passe à l'element suivant pour l'afficher
	}
}

/*Fonction qui prend un chemin et met les voitures dans un tableau */
void rewrite_tab_caos(chemin_vehicule_caos *l,int line, int tableau[][150])
{
	vehicule_caos *pourcopier;	
	pourcopier = l->tete;
	while(pourcopier !=NULL)
	{	
		tableau[pourcopier->y][pourcopier->x]=pourcopier->valeur; //Dans le tableau on se place dans les coordonnés de chaqu'un des elements de la liste pour placer leurs valeurs dans les caises du tableau 
		pourcopier=pourcopier->next;
	}
}

/*Fonction void qui deplace le tram passé en paramettre*/
void deplacement_tram_to_left_caos(chemin_vehicule_caos *l,int recu)
{	
	//Declaration des variables
	int var_temp=0; //valeur temporel de l'element présent
	int var_prec=0; //valeur precedent de l'element precedent LOL
	vehicule_caos *pourdeplacer;	//element courant
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
/*Fonction qui deplace le chemin 8, celui du caos 1*/
void deplacement_8_caos(chemin_vehicule_caos *l,int car_caos_1)
{	
	//Declaration des variables
	int var_temp=0;
	int var_prec=0;
	vehicule_caos *pourdeplacer;	
	pourdeplacer = l->tete;
	/****************************************************************************/
	//vehicule_caos *temp;// pour avoir acces à l'element qui es derier le element pour deplacer
	//vehicule_caos *stop;

	pourdeplacer->valeur=car_caos_1;
	
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
	}
}

/*Fonction qui deplace le chemin 6*/
void deplacement_6_caos(int y_feu,int x_feu,chemin_vehicule_caos *l,int compteur_vert)
{	
	//Declaration des variables
	int var_temp=0;
	int var_prec=0;
	vehicule_caos *pourdeplacer;	
	pourdeplacer = l->tete;
	/****************************************************************************/
	vehicule_caos *temp;// pour avoir acces à l'element qui es derier le element pour deplacer
	vehicule_caos *stop;

	/****************************************************************************/
	if(compteur_vert==1){ //Si le feut vert est éteint, le rouge s'active, donc on se met en mode feut rouge
		/*Maintenant je deplace pour trouver la caise egal à 0 la plus près du feu rouge*/

	while(pourdeplacer->x!=x_feu || pourdeplacer->y!=y_feu) //Tant qu'on est pas dans l'element qui a cordonnés où c'est le point d'arret de feu rouge
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
	while(pourdeplacer->x!=x_feu || pourdeplacer->y!=y_feu)
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

int deplacement_5_caos(int y_feu,int x_feu,chemin_vehicule_caos *l,int compteur_vert)
{	
	//Declaration des variables
	int var_temp=0;
	int var_prec=0;
	vehicule_caos *pourdeplacer;	
	pourdeplacer = l->tete;
	/****************************************************************************/
	vehicule_caos *temp;// pour avoir acces à l'element qui es derier le element pour deplacer
	vehicule_caos *stop;
	int envoie=0;

	/****************************************************************************/
	if(compteur_vert==1/*125*/){//Si le feut vert est éteint, le rouge s'active, donc on se met en mode feut rouge
		/*Maintenant je deplace pour trouver la caise egal à 0 la plus près du feu rouge*/

	while(pourdeplacer->x!=x_feu || pourdeplacer->y!=y_feu) //Tant qu'on est pas dans l'element qui a cordonnés où c'est le point d'arret de feu rouge
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
			////////////////////////
			if(x_feu==37)
			{
				envoie=pourdeplacer->valeur;
				pourdeplacer->valeur=0;
			}else{
			r=rand()%2;
			if(r==1)
			{
				envoie=pourdeplacer->valeur;
				pourdeplacer->valeur=0;
			}else{
				envoie=0;
			}
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
	while(pourdeplacer->x!=x_feu || pourdeplacer->y!=y_feu)
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
	/*	if(pourdeplacer->y==14 && pourdeplacer->x==108)
		{
			r=rand()%2;
			if(r==1)
			{
				envoie=pourdeplacer->valeur;
				pourdeplacer->valeur=0;
			}else{
				envoie=0;
			}
		}*/
		var_temp=pourdeplacer->valeur;
		pourdeplacer->valeur=var_prec;
		var_prec=var_temp;
		pourdeplacer=pourdeplacer->next;
	}}
	return envoie;	
}

void put_in_liste_2_from_liste_4_caos(chemin_vehicule_caos *l,int dep_est)
{
	//mettre une voiture dans la liste 2 depuis la liste 4
	vehicule_caos *pourdeplacer;
	pourdeplacer=l->tete;
	if(dep_est!=0){ //s'il y a une voiture , on met la valeur,(si c'est > 10 on s'en fout car quand meme il sera pas affiché, on peut optimiser le if si tu veux)
	for(int i=0;i<3;i++) //mettre la voiture dans le 5eme element, c'est à dire dans la 5eme coordonnés
		{pourdeplacer=pourdeplacer->next;}
		pourdeplacer->valeur=dep_est;}
}

void put_in_liste_5_from_liste_4_caos(chemin_vehicule_caos *l,int dep_est)
{
	//mettre une voiture dans la liste 5 depuis la liste 4
	vehicule_caos *pourdeplacer;
	pourdeplacer=l->tete;
	if(dep_est!=0 && dep_est<=10){ //s'il y a une voiture , on met la valeur,(si c'est > 10 on s'en fout car quand meme il sera pas affiché, on peut optimiser le if si tu veux)
	for(int i=0;i<41;i++) //mettre la voiture dans le 76eme element, c'est à dire dans la 76eme coordonnés
		{pourdeplacer=pourdeplacer->next;}
		pourdeplacer->valeur=dep_est;

	}
}

void put_in_liste_6_from_liste_3_caos(chemin_vehicule_caos *l,int dep_est)
{
	//mettre une voiture dans la liste 6 depuis la liste 3
	vehicule_caos *pourdeplacer;
	pourdeplacer=l->tete;
	if(dep_est!=0 && dep_est<=10){//s'il y a une voiture , on met la valeur,(si c'est > 10 on s'en fout car quand meme il sera pas affiché, on peut optimiser le if si tu veux)
		for(int i=0;i<41;i++)//mettre la voiture dans le 81eme element, c'est à dire dans la 81eme coordonnés
		{pourdeplacer=pourdeplacer->next;}
		pourdeplacer->valeur=dep_est;
	}
}

int deplacement_4_caos(int collision_5_6,chemin_vehicule_caos *l, int compteur_vert)
{	
	//Declaration des variables
//	FILE *fichier_test=NULL;
//	fichier_test=fopen("random_test_1.txt","a");
	int var_temp=0;
	int var_prec=0;
	vehicule_caos *pourdeplacer;	
	pourdeplacer = l->tete;
	int envoie=0;
	/****AJOUTE DES PROPRIETÉS POUR LE FEU*****/

	vehicule_caos *temp;// pour avoir acces à l'element qui es derier le element pour deplacer
	vehicule_caos *stop;
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
	{	/*fprintf(fichier_test,"la valeur qui sera testé est %d\n",pourdeplacer->valeur);
		if(pourdeplacer->y==27 && pourdeplacer->x==66 && pourdeplacer->valeur<=10)
		{	fprintf(fichier_test,"la valeur qui peut passer au chemin 2 est %d\n",pourdeplacer->valeur);
			r=rand()%10;
			if(r<=5){ //si la valeur aleatoire est 0, on envoie la valeur à la liste 2, apres la valeur sera traite par la liste 2
			envoie=pourdeplacer->valeur;
			fprintf(fichier_test,"la valeur random sortie est %d\n",r);
			fprintf(fichier_test,"la valeur %d passe au chemin 2\n",pourdeplacer->valeur);
	//		pourdeplacer->valeur==0; // AVANT C'ETAIT pourdeplacer->valeur=0;????????? y a un truc bizare
		var_temp=0; //actuel = 0
		pourdeplacer->valeur=0;
		pourdeplacer=pourdeplacer->next; //actuel  = precedent
		}
		}else{*/
		var_temp=pourdeplacer->valeur; 
		pourdeplacer->valeur=var_prec; 
		var_prec=var_temp ; 
		pourdeplacer=pourdeplacer->next;    //}
	}
		pourdeplacer=l->tete;
		while(pourdeplacer->y!=27 || pourdeplacer->x!=66)
		{	pourdeplacer=pourdeplacer->next;	}

		if(pourdeplacer->valeur<=10)
		{
			if(collision_5_6==1)
				{envoie=pourdeplacer->valeur;
				pourdeplacer->valeur=0;}
				else{
			r=rand()%10;
			if(r<=5)
			{
				envoie=pourdeplacer->valeur;
				pourdeplacer->valeur=0;
			}}
		}

	}
	//fclose(fichier_test);
	return envoie;
}



int deplacement_3_caos(int collision_5_6,int y_feu,int x_feu,chemin_vehicule_caos *l,int compteur_vert)
{	
	//Declaration des variables
	int var_temp=0;
	int var_prec=0;
	vehicule_caos *pourdeplacer;	
	pourdeplacer = l->tete;
	int envoie=0;
	vehicule_caos *temp;// pour avoir acces à l'element qui es derier le element pour deplacer
	vehicule_caos *stop;

	/****************************************************************************/
	if(compteur_vert==1){
		/*Maintenant je deplace pour trouver la caise egal à 0 la plus près du feu rouge*/

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
	if(collision_5_6==0){
	while(pourdeplacer->x!=x_feu || pourdeplacer->y!=y_feu)
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
	}}

	return 0;
	}else{

 	/*int r=rand()%100;
	pourdeplacer->valeur=r;
	
	//Preparer le deplacement: debut du deplacement dans la tête de la liste
	var_temp=pourdeplacer->valeur;
	pourdeplacer->valeur=0;
	var_prec=var_temp;
	pourdeplacer=pourdeplacer->next;*/

	/**********************************************************************/
	if(collision_5_6==1)
	{
		while(pourdeplacer->x!=60 || pourdeplacer->y!=17) 
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

	pourdeplacer=l->tete;
		while(pourdeplacer->y!=24 || pourdeplacer->x!=58)
		{	pourdeplacer=pourdeplacer->next;	}

		if(pourdeplacer->valeur<=10)
		{
			r=rand()%10;
			if(r<=5)
			{
				envoie=pourdeplacer->valeur;
				pourdeplacer->valeur=0;
			}
		}

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	/*******************On deplace normalement le reste des voitures********************************/
	//Mais dans ce cas on ne doit pas deplacer car y aura pas des voitures
	/*while(pourdeplacer->x!=x_feu || pourdeplacer->y!=y_feu)
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
	}*/
	}else{

	

	/**********************************************************************/
	int r=rand()%100;
	pourdeplacer->valeur=r;
	
	//Preparer le deplacement: debut du deplacement dans la tête de la liste
	var_temp=pourdeplacer->valeur;
	pourdeplacer->valeur=0;
	var_prec=var_temp;
	pourdeplacer=pourdeplacer->next;

	//Deplacer les voitures suivantes
	while(pourdeplacer !=NULL) //c'eest bon ça
	{	
		var_temp=pourdeplacer->valeur;
		pourdeplacer->valeur=var_prec;
		var_prec=var_temp;
		pourdeplacer=pourdeplacer->next;
	}
	pourdeplacer=l->tete;
		while(pourdeplacer->y!=24 || pourdeplacer->x!=58)
		{	pourdeplacer=pourdeplacer->next;	}

		if(pourdeplacer->valeur<=10)
		{
			if(collision_5_6==1)
				{envoie=pourdeplacer->valeur;
				pourdeplacer->valeur=0;}
				else{
			r=rand()%10;
			if(r<=5)
			{
				envoie=pourdeplacer->valeur;
				pourdeplacer->valeur=0;
			}}
		}

}
return envoie;	
}}

void deplacement_7_caos(chemin_vehicule_caos *l,int recu)
{	
	//Declaration des variables
	int var_temp=0;
	int var_prec=0;
	vehicule_caos *pourdeplacer;	
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

void deplacement_10_caos(chemin_vehicule_caos *l,int recu)
{	
	//Declaration des variables
	int var_temp=0;
	int var_prec=0;
	vehicule_caos *pourdeplacer;	
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

void deplacement_9_caos(chemin_vehicule_caos *l,int recu, vehicule_caos *element_from_liste_5)
{	
	//Declaration des variables
	int var_temp=0;
	int var_prec=0;
	vehicule_caos *pourdeplacer;
	vehicule_caos *temp=NULL;
	vehicule_caos *stop=NULL;
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

void deplacement_2_caos(chemin_vehicule_caos *l,int recu)
{	
	//Declaration des variables
	int var_temp=0;
	int var_prec=0;
	vehicule_caos *pourdeplacer;	
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


int deplacement_1_caos(chemin_vehicule_caos *l,int compteur_vert, int *car_caos_1)
{	
	//Declaration des variables
	int var_temp=0;
	int var_prec=0;
	vehicule_caos *pourdeplacer;	
	pourdeplacer = l->tete;
	int envoie=0;
	/****AJOUTE DES PROPRIETÉS POUR LE FEU*****/

	vehicule_caos *temp;// pour avoir acces à l'element qui es derier le element pour deplacer
	vehicule_caos *stop;
	/*Si c'est en rouge on s'arrete fur et à mesure*/
	if(compteur_vert==1){
		/*Maintenant je deplace pour trouver la caise egal à 0 la plus près du feu rouge*/

	while(pourdeplacer->x!=58 || pourdeplacer->y!=26) 
	{
		if(pourdeplacer->valeur==0 || pourdeplacer->valeur>10) //SI la caise est vide !!!!! >10
		{
			temp=pourdeplacer;
		}	
		if(pourdeplacer->x==22 && pourdeplacer->y==26) //SI on est dans cette possition, on envoie la voiture (o le vide)
		{
			if(*car_caos_1==0 || *car_caos_1>10)
			{
			*car_caos_1=pourdeplacer->valeur;
			pourdeplacer->valeur=0;
			}
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
	{	
		if(pourdeplacer->x==22 && pourdeplacer->y==26) //SI on est dans cette possition, on envoie la voiture (o le vide)
		{
			if(*car_caos_1==0 || *car_caos_1>10)
			{
			*car_caos_1=pourdeplacer->valeur;
			pourdeplacer->valeur=0;
			}
		}
		if(pourdeplacer->y==26 && pourdeplacer->x==60 && pourdeplacer->valeur>5)
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

void deplacement_pieton_caos (chemin_vehicule_caos *l)
{	
	//Declaration des variables
	int var_temp=0; //valeur temporelle de l'element présent
	int var_prec=0; //valeur precedent de l'element precedent LOL
	vehicule_caos *pourdeplacer;	//element courant
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
void reboot_tab_caos(int line,int tableau[][150]){
	for (int i=0;i<line;i++)
		{for(int j=0;j<150;j++)
			{tableau[i][j]=0;}
		}	
}
/*Ta fonction qui sert à afficher le plan, pas modifié a part le nom du fichier */
void AffichePlan_caos (char*nom_fichier){
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

 void creation_des_chemins_vides_caos(chemin_vehicule_caos *liste_1,chemin_vehicule_caos *liste_2,chemin_vehicule_caos *liste_3,chemin_vehicule_caos *liste_4,chemin_vehicule_caos *liste_5,chemin_vehicule_caos *liste_6,chemin_vehicule_caos *liste_7,chemin_vehicule_caos *liste_8,chemin_vehicule_caos *liste_9,chemin_vehicule_caos *liste_10,chemin_vehicule_caos *liste_tram_to_left,chemin_vehicule_caos *liste_tram_to_right , chemin_vehicule_caos *liste_ambu_1, chemin_vehicule_caos *liste_ambu_2,chemin_vehicule_caos *liste_ambu_3,chemin_vehicule_caos *trottoir3,chemin_vehicule_caos *trottoir4,chemin_vehicule_caos *trottoir5,chemin_vehicule_caos *trottoir6,chemin_vehicule_caos *trottoirst,chemin_vehicule_caos *trottoir7)
    {
 	/*Ouverture du fichier avec les coordonnes*/
    /*Chaque numero correspond eplicitement aux chemins de la photo*/
	FILE *fichier_1=NULL;
	FILE *fichier_2=NULL;
	FILE *fichier_3=NULL;
	FILE *fichier_5=NULL;
	FILE *fichier_4=NULL;
	FILE *fichier_6=NULL;
	FILE *fichier_7=NULL;
	FILE *fichier_8=NULL; //caos_way_1
	FILE *fichier_9=NULL;
	FILE *fichier_10=NULL;
	FILE *fichier_ambu_1=NULL;
	FILE *fichier_ambu_2=NULL;
	FILE *fichier_ambu_3=NULL;
	FILE *fichier_tram_to_left=NULL;
	FILE *fichier_tram_to_right=NULL;
	FILE *fichier_pieton = NULL;
	FILE *fichier_pieton4 = NULL;
	FILE *fichier_pieton5 = NULL;
	FILE *fichier_pieton6 = NULL;
	FILE *fichier_pieton7 = NULL;
	FILE *fichier_pietonst = NULL;

	fichier_1=fopen("coordonnees_1_caos.txt","r");//chemin A qui va à l'ouest et tourne au sud
	fichier_2=fopen("coordonnees_2_caos.txt","r"); //chemin A qui commence au milieu et qui va à l'ouest toutdroit
	fichier_3=fopen("cordonnees_3_caos.txt","r"); //chemin B qui va à l'ouest et tourne au nord
	fichier_5=fopen("cordonnees_5_caos.txt","r"); //chemin C au dessus qui va à l'ouest toutdroit
	fichier_4=fopen("cordonnees_4_caos.txt","r"); //chemin D qui va au nord et tourne à l'ouest
	fichier_6=fopen("cordonnees_6_caos.txt","r"); //chemin qui est au dessous du C et c'est en paralléle
	fichier_7=fopen("cordonnees_7_caos.txt","r"); 
	fichier_8=fopen("cordonnees_8_caos.txt","r"); //chemin dont les voirtures peuvent virer du chemin A et s'ecraser avec le batiment
	fichier_9=fopen("cordonnees_9_caos.txt","r");
	fichier_10=fopen("cordonnees_10_caos.txt","r");
	fichier_ambu_1=fopen("cordonnees_ambu_1.txt","r");
	fichier_ambu_2=fopen("cordonnees_ambu_2.txt","r");
	fichier_ambu_3=fopen("cordonnees_ambu_3.txt","r");
	fichier_pieton = fopen("trottoir_3.txt","r");
	fichier_pieton4 = fopen("trottoir_4.txt","r");
    fichier_pieton5 = fopen("trottoir_5.txt","r");
    fichier_pieton6 = fopen("trottoir_6.txt","r");
    fichier_pieton7 = fopen("trottoir_7.txt","r");
    fichier_pietonst = fopen("trottoir_st.txt","r");

	fichier_tram_to_left=fopen("cordonnees_tram_to_left_caos.txt","r"); //chemin du tram qui va à gauche
	fichier_tram_to_right=fopen("cordonnees_tram_to_right_caos.txt","r"); // chemin du tram qui va à droite

	//Variables des cordonnees x et y
	int x=0;
	int y=0;

	/*La on crée dans le debut du programme les elements de chaque chemin qui auront seulement leurs cordonnés */
	for (int i=0 ; i<37 ;i++) //76 caises, c'est à dire 76 cordonnes dont les voiteures peuvent passer, pareils pour les autres
	{	
		fscanf(fichier_1, "%d %d",&y,&x);
		mettre_en_queue_caos(liste_1,y,x);
	}

	for (int i=0;i<41;i++)
	{
		fscanf(fichier_2, "%d %d",&y,&x);
		mettre_en_queue_caos(liste_2,y,x);
	}
	
	for (int i=0;i<129;i++)
	{
		fscanf(fichier_3, "%d %d",&y,&x);
		mettre_en_queue_caos(liste_3,y,x);
	}
	
	for(int i=0;i<91;i++)
	{
		fscanf(fichier_4, "%d %d",&y,&x);
		mettre_en_queue_caos(liste_4,y,x);
	}
	
	for (int i=0;i<74;i++)
	{
		fscanf(fichier_5, "%d %d",&y,&x);
		mettre_en_queue_caos(liste_5,y,x);
	}
	
	for (int i=0;i<72;i++)
	{
		fscanf(fichier_6, "%d %d",&y,&x);
		mettre_en_queue_caos(liste_6,y,x);
	}

	for (int i=0;i<13;i++)
	{
		fscanf(fichier_9, "%d %d",&y,&x);
		mettre_en_queue_caos(liste_9,y,x);
	}

	for (int i=0;i<14;i++)
	{
		fscanf(fichier_10, "%d %d",&y,&x);
		mettre_en_queue_caos(liste_10,y,x);
	}

	for (int i=0;i<142;i++)
	{
		fscanf(fichier_tram_to_left, "%d %d",&y,&x);
		mettre_en_queue_caos(liste_tram_to_left,y,x);
	}

	for (int i=0;i<42;i++)
	{
		fscanf(fichier_7, "%d %d",&y,&x);
		mettre_en_queue_caos(liste_7,y,x);
	}

	for (int i=0;i<142;i++)
	{
		fscanf(fichier_tram_to_right, "%d %d",&y,&x);
		mettre_en_queue_caos(liste_tram_to_right,y,x);
	}

	for (int i = 0; i < 17; ++i)
	{
		fscanf(fichier_8, "%d %d",&y,&x);
		mettre_en_queue_caos(liste_8,y,x);
	}

	for (int i = 0; i < 17; ++i)
	{
		fscanf(fichier_ambu_1, "%d %d",&y,&x);
		mettre_en_queue_caos(liste_ambu_1,y,x);
	}

	for (int i = 0; i < 17; ++i)
	{
		fscanf(fichier_ambu_2, "%d %d",&y,&x);
		mettre_en_queue_caos(liste_ambu_2,y,x);
	}

	for (int i = 0; i < 40; ++i)
	{
		fscanf(fichier_ambu_3, "%d %d",&y,&x);
		mettre_en_queue_caos(liste_ambu_3,y,x);
	}

	   for (int i=0;i<107;i++)
	{
		fscanf(fichier_pieton, "%d %d",&y,&x);
		mettre_en_queue_caos(trottoir3,y,x);
	}

	                 for (int i=0;i<64;i++)
	{
		fscanf(fichier_pieton4, "%d %d",&y,&x);
		mettre_en_queue_caos(trottoir4,y,x);
	}
           for (int i=0;i<64;i++)
	{
		fscanf(fichier_pieton5, "%d %d",&y,&x);
		mettre_en_queue_caos(trottoir5,y,x);
	}

	          for (int i=0;i<33;i++)
	{
		fscanf(fichier_pieton6, "%d %d",&y,&x);
		mettre_en_queue_caos(trottoir6,y,x);
	}
              for (int i=0;i<38;i++)
	{
		fscanf(fichier_pietonst, "%d %d",&y,&x);
		mettre_en_queue_caos(trottoirst,y,x);
	}

	          for (int i=0;i<50;i++)
	{
		fscanf(fichier_pieton7, "%d %d",&y,&x);
		mettre_en_queue_caos(trottoir7,y,x);
	}

	//Fermeture du fichier avec les coordonnees car on n'a plus besoin
	fclose(fichier_1);
	fclose(fichier_2);
	fclose(fichier_3);
	fclose(fichier_5);
	fclose(fichier_4);
	fclose(fichier_6);
	fclose(fichier_7);
	fclose(fichier_8);
	fclose(fichier_9);
	fclose(fichier_10);
	fclose(fichier_ambu_1);
	fclose(fichier_ambu_2);
	fclose(fichier_ambu_3);
	fclose(fichier_tram_to_left);
	fclose(fichier_tram_to_right);
	fclose(fichier_pieton);
	fclose(fichier_pieton4);
    fclose(fichier_pieton5);
 	fclose(fichier_pieton6);
 	fclose(fichier_pieton7);
    fclose(fichier_pietonst);
 }

 void feu_tab_caos(int a,int b,int c,int line,int tableau[][150])
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
/*
 void feu_tab_caos(int a,int b,int c,int line,int tableau[][150]){
	
	if(a==1) //Si c'est vert, on fait ça
		{ */  /*1 si c'est vert, 0 si c'est rouge, on les mets dans les cordonnées de la map mais dans le tableau 2D passé en paramettre*/
		/*D'abord dans un tableau sont les lignes et apres les colonnes*/
	/*	tableau[26][58]=1; //feu du chemin 1
		tableau[24][58]=0; //feu du chemin 3
		tableau[29][66]=0; //feu du chemin 4
		tableau[14][69]=1; //feu du chemin 5
		tableau[16][69]=1; //feu du chemin 6
		tableau[19][69]=1; //feu du tram qui va à gauche
		tableau[19][56]=1; //feu du tram qui va à droite
	}
		if(b==1){
		tableau[26][58]=1; //feu du chemin 1
		tableau[24][58]=1; //feu du chemin 3
		tableau[29][66]=1; //feu du chemin 4
		tableau[14][69]=1; //feu du chemin 5
		tableau[16][69]=1; //feu du chemin 6
		tableau[19][69]=1; //feu du tram qui va à gauche
		tableau[19][56]=1; //feu du tram qui va à droite
		}
		if(c==1){
		//sinon, c'est rouge
		tableau[26][58]=0; //feu du chemin 1
		tableau[24][58]=1; //feu du chemin 3
		tableau[29][66]=1; //feu du chemin 4
		tableau[14][69]=0; //feu du chemin 5
		tableau[16][69]=0; //feu du chemin 6
		tableau[19][69]=0; //feu du tram qui va à gauche
		tableau[19][56]=0; //feu du tram qui va à droite
	}
	}
*/
/*Fonction qui appelle à la fonction afficher pour afficher les voitures , c'est à dire, afficher les listes*/
 void affichages_des_voitures_caos(chemin_vehicule_caos *liste_1,chemin_vehicule_caos *liste_2,chemin_vehicule_caos *liste_3,chemin_vehicule_caos *liste_4,chemin_vehicule_caos *liste_5,chemin_vehicule_caos *liste_6,chemin_vehicule_caos *liste_7 ,chemin_vehicule_caos *liste_8,chemin_vehicule_caos *liste_9,chemin_vehicule_caos *liste_10)
 {
 	afficher_caos(liste_1);
	fflush(stdout);
	afficher_caos(liste_2);
	fflush(stdout);
	afficher_caos(liste_3);
	fflush(stdout);
	afficher_caos(liste_5);
	fflush(stdout);
	afficher_caos(liste_4);
	fflush(stdout);
	afficher_caos(liste_6);
	fflush(stdout);
	afficher_caos(liste_7);
	fflush(stdout);
	afficher_caos(liste_8);
	fflush(stdout);
	afficher_caos(liste_9);
	fflush(stdout);
	afficher_caos(liste_10);
	fflush(stdout);
 }

void affichages_pieton_caos(chemin_vehicule_caos *l)
{
	/*Ici on affiche tout la liste qui va de l'extrem est à l'extreme ouest, c'est à dire que la liste
	traverse la map, ainsi le tram s'affiche en tout point de la raie dessinée*/
	vehicule_caos *pourmontrer;	
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

 void affichage_explosions_caos(int collision_5_6,int collision_3_tram_to_left, int line,int tableau[][150])
 {
 	if(tableau[37][34]>0 && tableau[37][34]<=10)
 	{
 		printf("\033[38;30f");printf("\033[33m");printf("🔥🔥🔥🔥🔥🔥🔥🔥");
 		printf("\033[39;30f");printf("\033[33m");printf("🔥🔥🔥🔥🔥🔥🔥🔥");
 		printf("\033[40;30f");printf("\033[33m");printf("🔥🔥🔥🔥🔥🔥🔥🔥");
 		printf("\033[41;30f");printf("\033[33m");printf("🔥🔥🔥🔥🔥🔥🔥🔥");
 	}

 	if(collision_5_6==1)
 	{
 		fflush(stdout);
 		printf("\033[14;35f");printf("\033[33m");printf("🔥🔥🔥🔥🔥🔥");
 		printf("\033[15;35f");printf("\033[33m");printf("🔥🔥🔥🔥🔥🔥");
 		printf("\033[16;35f");printf("\033[33m");printf("🔥🔥🔥🔥🔥🔥");
 	}

 	if(collision_3_tram_to_left==1)
 	{
 		printf("\033[19;58f");printf("\033[33m");printf("🔥🔥🔥🔥🔥🔥🔥🔥");
 		printf("\033[20;58f");printf("\033[33m");printf("🔥🔥🔥🔥🔥🔥🔥🔥");
 		printf("\033[21;58f");printf("\033[33m");printf("🔥🔥🔥🔥🔥🔥🔥🔥");
 		printf("\033[22;58f");printf("\033[33m");printf("🔥🔥🔥🔥🔥🔥🔥🔥");
 	}

 }
/*Fonction qui envoie l'adresse de l'element qui se trouve dans la cordonné d'intersection entre le chemin 4 et 5*/
vehicule_caos *send_adress_5_caos(chemin_vehicule_caos *l){
 	vehicule_caos *element;
 	element=l->tete;
 	for(int i=0;i<14;i++){element=element->next;}
 	return element;
 }
/*Fonction qui envoie l'adresse de l'element qui se trouve dans la cordonné d'intersection entre le chemin 3 et 6*/
vehicule_caos *send_adress_6_caos(chemin_vehicule_caos *l){
 	vehicule_caos *element;
 	element=l->tete;
 	for(int i=0;i<35;i++){element=element->next;}
 	return element;
 }

vehicule_caos *send_adress_5_for_9_caos(chemin_vehicule_caos *l){
 	vehicule_caos *element;
 	element=l->tete;
 	for(int i=0;i<21;i++){element=element->next;}
 	return element;
 }

int test_collision_3_tram_to_left_caos(int collision_3_tram_to_left,int line,int tableau[][150]){
if(tableau[22][60]>0 && tableau[22][60]<=10 && tableau[21][59]>0 &&tableau[21][59]<=10){
	collision_3_tram_to_left=1;
}else{
	if(tableau[20][60]>0 && tableau[20][60]<=10 && tableau[19][61]>0 &&tableau[19][61]<=10){
	collision_3_tram_to_left=1;}
	else{collision_3_tram_to_left=0;}
}
return collision_3_tram_to_left;
} 

int test_collision_5_6_caos(int collision_5_6,int line,int tableau[][150]){
if(tableau[14][37]>0 && tableau[14][37]<=10 && tableau[16][37]>0 &&tableau[16][37]<=10){
	int r=rand()%5;
	if (r==3)
	{
	collision_5_6=1;
}else{
	collision_5_6=0;
}}
return collision_5_6;
} 
 char key_pressed_2()
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

void caos_mode(){
	system("clear");
	system("play -q 'GTA-San-Andreas-Theme-Song-Full-.mp3' repeat 10000 &");
//	srand ( time (NULL) );
	//Declaration des listes des chemins des voitures et initialisation
	chemin_vehicule_caos liste_1, liste_2, liste_3, liste_4, liste_5, liste_6,liste_7,liste_8,liste_9, liste_10;
	chemin_vehicule_caos liste_tram_to_left,liste_tram_to_right,liste_ambu_1,liste_ambu_2,liste_ambu_3;
	chemin_vehicule_caos trottoir,trottoir4,trottoir5, trottoir6,trottoirst,trottoir7;;
	
	/*Initialisation des listes des vehicules*/
	init_vehicule_caos(&liste_1);
	init_vehicule_caos(&liste_2);
	init_vehicule_caos(&liste_3);
	init_vehicule_caos(&liste_4);
	init_vehicule_caos(&liste_5);
	init_vehicule_caos(&liste_6);
	init_vehicule_caos(&liste_7);
	init_vehicule_caos(&liste_8); //caos_way_1
	init_vehicule_caos(&liste_9);
	init_vehicule_caos(&liste_10);
	init_vehicule_caos(&liste_ambu_1);
	init_vehicule_caos(&liste_ambu_2);
	init_vehicule_caos(&liste_ambu_3);
	init_vehicule_caos(&liste_tram_to_left);
	init_vehicule_caos(&liste_tram_to_right);
	init_vehicule_caos(&trottoir);
	init_vehicule_caos(&trottoir4);
    init_vehicule_caos(&trottoir5);
	init_vehicule_caos(&trottoir6);
	init_vehicule_caos(&trottoir7);
    init_vehicule_caos(&trottoirst);


	
	/* Declaration du tableau 2D*/
	int col=150;
	int line=150;
	int tableau[line][col];

	/*Inisialisation du tableau*/
	reboot_tab_caos(line,tableau);	
	
	/*Creation des chemins vides des voitures avec leur coordonnés*/
	creation_des_chemins_vides_caos(&liste_1,&liste_2,&liste_3,&liste_4,&liste_5,&liste_6,&liste_7,&liste_8,&liste_9,&liste_10,&liste_tram_to_left,&liste_tram_to_right,&liste_ambu_1,&liste_ambu_2,&liste_ambu_3,&trottoir,&trottoir4,&trottoir5, &trottoir6,&trottoirst,&trottoir7);

	//Affichage de la ville
	char plan[]="officialplan_3.txt";
	AffichePlan_caos(plan);

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
	int cart_to_10=0;
	int show_ambu_1=0;
	int time_ambu_1=0;
	int show_ambu_3=0;
	int time_ambu_3=0;
	int random=0;
	int dep_pieton=0;
	//Variable longueur du tram;
	int longueur_tram=0;
	int stop_apparition_du_tram_to_left=0;

	// variable qui prend la voiture des cordonnees 26:22 du chemin 1 pour qu'il fasse le caos en batiment
	int car_caos_1=0; //y a pas de voiture au debut, il sera modifié jusqu'a avoir une voiture qui passe dans le chemin caos_1
	int already_sent=0;	

	//Variable qui distingue s'il y a des collisions ou pas
	int collision_3_tram_to_left=0; //colision entre le chemin 3 et le tram_to_left
//	int collision_3_tram_to_right=0; //colision entre le chemin 3 et le tram_to_right
	int collision_5_6=0;
	int go_to_7th_way=0;
	/****************Ville qui circulle normallement*********************/

	/*Nouvelle manière d'envoyer les voitures dans une autre liste*/
	/*Je recupere l'adresse des elements dont les voitures peuvent changer de chemin
	grace à cette adresse, je peut recuperer les voitures des ces elements sans faire des
	longs opperations, je passe ces valeurs (voitures) en parametre et puis c'est bon, je 
	le fais dans les fonctions put_in_liste_5_from_liste_4 et put_in_liste_6_from_liste_3,
	je pourrais le faire pour le deplacement_1 et 2 qui font un calcul chelou pour mettre la voiture dans le chemin 2*/
	vehicule_caos *element_from_liste_4=NULL;
	vehicule_caos *element_from_liste_3=NULL;
	vehicule_caos *element_from_liste_5=NULL;

	element_from_liste_4=send_adress_5_caos(&liste_4);
	element_from_liste_3=send_adress_6_caos(&liste_3);
	element_from_liste_5=send_adress_5_for_9_caos(&liste_5);


	/*Fonctions sans arrete qui fait bouger la ville*/ 

	/*Les fonctions deplacement_x representent le deplacement 
	des voitures de chaque liste, leur numero correspondent au numero du chemin*/
	int played_tram_1=0;
	int played_5_6_accident=0;
	int played_ambulance=0;
	int played_house_crash=0;
	while(constante==3){
	//Deplacer les valeurs
	if(key_pressed_2()=='q')
		{constante=0;}
	fflush(stdout); //ne pas supprimer, sinon ça saute un deplacement total
	
	/*****************liste_1 avec feu rouge et vert dans le coin*********/

	/*****************Compteur d'apparition du tram_to_left****************/	

	//à 250, le tram apparait, sinon j'incremente
	if(compteur_tram_to_left<280){compteur_tram_to_left++;}
	else{
		if(longueur_tram<14)
		{//Le tram commence à apparaitre
		if(collision_3_tram_to_left==0){ //teste si on a pas de collision, on avance le tram
			deplacement_tram_to_left_caos(&liste_tram_to_left,2); 
			deplacement_tram_to_left_caos(&liste_tram_to_right,2);
		}
		longueur_tram++;}
		else{
			if(longueur_tram==14)
				{//J'ajoute une image du raie à la fin de la liste, ainsi on laisse pas vide le chemin apres le deplacement
				if(collision_3_tram_to_left==0){
			deplacement_tram_to_left_caos(&liste_tram_to_left,-1); 
			deplacement_tram_to_left_caos(&liste_tram_to_right,-1);
					}
				longueur_tram=15;}
					else{//je fais un deplacement normal 
						if(collision_3_tram_to_left==0){
						deplacement_tram_to_left_caos(&liste_tram_to_left,0); 
						deplacement_tram_to_left_caos(&liste_tram_to_right,0);
						}
					}
			}
		stop_apparition_du_tram_to_left++;
	}
	
	/************Mettre des feus rouges et verts dans les cordonnees*******/
	feu_tab_caos(a,b,c,line,tableau);

	collision_3_tram_to_left=test_collision_3_tram_to_left_caos(collision_3_tram_to_left,150,tableau);
	if(collision_3_tram_to_left==1)
	{go_to_7th_way=deplacement_3_caos(collision_5_6, 21,60,&liste_3,1);
		if(played_tram_1==0)
		{
		system("play -q 'son_crash_car.mp3' &");
		played_tram_1=1;}
		if(show_ambu_3<100)
			{show_ambu_3++;}}
	else{
	go_to_7th_way=deplacement_3_caos(collision_5_6, 24,58,&liste_3,tableau[24][58]);
	}



	collision_5_6=test_collision_5_6_caos(collision_5_6,150,tableau);
/*	if(collision_5_6==1)
	{cart_to_10=deplacement_5(14,37,&liste_5,1);
		deplacement_6(16,37,&liste_6,1);}
	else{
	cart_to_10=deplacement_5(14,69,&liste_5,tableau[14][69]);
	deplacement_6(16,69,&liste_6,tableau[14][69]);
	}*/


	/*****************Deplacement total des voitures******************/

	int dep_est=deplacement_1_caos(&liste_1,tableau[26][58],&car_caos_1);	//chemin A :on deplace les voitures de &liste_1 et on envoie les "1" ou "0" s'il n'y a pas de voitures qui continue tout droit
	deplacement_2_caos(&liste_2,dep_est); //chemin A on deplace les voitures qui continuent tout droit de la liste precedent (les 1 continuent tout droit et la fonction re^oit en paramettre "0" ou "1")

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

	if (stop_apparition_du_tram_to_left==170)
	{
		stop_apparition_du_tram_to_left=0;
		compteur_tram_to_left=0;
		longueur_tram=0;
	}

	if(dep_pieton==3)
	{
	deplacement_pieton_caos(&trottoir); // test du mouvement du pieton
        deplacement_pieton_caos(&trottoir4);
        deplacement_pieton_caos(&trottoir5);
         deplacement_pieton_caos(&trottoir6);
        deplacement_pieton_caos(&trottoirst);
    	deplacement_pieton_caos(&trottoir7);
    }

    if(dep_pieton<3){dep_pieton++;}
	else{dep_pieton=0;}
	
	deplacement_7_caos(&liste_7,go_to_7th_way);
	dep_est=deplacement_4_caos(collision_5_6,&liste_4,tableau[29][66]);//chemin D se deplace
	put_in_liste_2_from_liste_4_caos(&liste_2,dep_est);
	put_in_liste_5_from_liste_4_caos(&liste_5,element_from_liste_4->valeur);
	put_in_liste_6_from_liste_3_caos(&liste_6,element_from_liste_3->valeur);
	if(collision_5_6==1)
	{cart_to_10=deplacement_5_caos(14,37,&liste_5,1);
		if(played_5_6_accident==0)
		{
		system("play -q 'son_crash_car.mp3' &");
		played_5_6_accident=1;}
		deplacement_6_caos(16,37,&liste_6,1);
		if(show_ambu_1<100)
			{show_ambu_1++;}
	}
	else{
	cart_to_10=deplacement_5_caos(14,69,&liste_5,tableau[14][69]);
	deplacement_6_caos(16,69,&liste_6,tableau[14][69]);
	}



	deplacement_9_caos(&liste_9,element_from_liste_5->valeur,element_from_liste_5);
	deplacement_10_caos(&liste_10,cart_to_10);
//	deplacement_5(&liste_5,tableau[14][69]);	//chemin C se deplace
//	deplacement_6(&liste_6,tableau[16][69]);

	if(already_sent==0){
	if(car_caos_1>0 && car_caos_1<=10)
			{
			if(played_house_crash==0)
		{
		system("play -q 'son_crash_car.mp3' &");
		system("play -q 'son_gens_crient.mp3' repeat 1000 &");
		played_house_crash=1;}
			deplacement_8_caos(&liste_8,car_caos_1);
			already_sent=1;
			}
	}else{deplacement_8_caos(&liste_8,0);}

	if(show_ambu_1==100 && time_ambu_1<16){
		if(played_ambulance==0){
		system("play -q 'son_ambulance.mp3' repeat 10000 &");
		played_ambulance=1;
		}
		random=rand()%4;
		if(random==1){
//		if(un_sur_deux==0){
		deplacement_2_caos(&liste_ambu_1,1);
	//	un_sur_deux=1;
		}else{
			deplacement_2_caos(&liste_ambu_1,0);
		}

		random=rand()%4;
		if(random==1){
//		if(un_sur_deux==0){
		deplacement_2_caos(&liste_ambu_2,1);
	//	un_sur_deux=1;
		}else{
			deplacement_2_caos(&liste_ambu_2,0);
		}

		time_ambu_1++;

	}

	if(show_ambu_3==100 && time_ambu_3<39){
		if(played_ambulance==0){
		system("play -q 'son_ambulance.mp3 repeat' 10000 &");
		played_ambulance=1;
		}
		random=rand()%4;
		if(random==1){
//		if(un_sur_deux==0){
		deplacement_2_caos(&liste_ambu_3,1);
	//	un_sur_deux=1;
		}else{
			deplacement_2_caos(&liste_ambu_3,0);
		}
		time_ambu_3++;
	}
	
	
	/*Mise à jour du tabeau*/
	reboot_tab_caos(line,tableau); //Reinisialisation du tableau;
	rewrite_tab_caos(&liste_1,line,tableau); 
	rewrite_tab_caos(&liste_2,line,tableau);
	rewrite_tab_caos(&liste_3,line,tableau);
	rewrite_tab_caos(&liste_5,line,tableau);
	rewrite_tab_caos(&liste_4,line,tableau);
	rewrite_tab_caos(&liste_6,line,tableau);
	rewrite_tab_caos(&liste_7,line,tableau);
	rewrite_tab_caos(&liste_8,line,tableau);
	rewrite_tab_caos(&liste_9,line,tableau);
	rewrite_tab_caos(&liste_10,line,tableau);
	rewrite_tab_caos(&liste_tram_to_left,line,tableau);
	rewrite_tab_caos(&liste_tram_to_right,line,tableau);
	//Affichage des voitures deplacés
   	affichages_des_voitures_caos(&liste_1,&liste_2,&liste_3,&liste_4,&liste_5,&liste_6,&liste_7,&liste_8,&liste_9,&liste_10);
  	if(show_ambu_1==100 && time_ambu_1<=32){
 	fflush(stdout);
  	afficher_ambu(&liste_ambu_1);
  	fflush(stdout);
  	afficher_ambu(&liste_ambu_2);
  	}

  	if(show_ambu_3==100 && time_ambu_3<=79){
 	fflush(stdout);
  	afficher_ambu(&liste_ambu_3);
  	}

   	affichages_des_trams_caos(&liste_tram_to_left);
   	affichages_des_trams_caos(&liste_tram_to_right);
   	affichage_explosions_caos(collision_5_6,collision_3_tram_to_left, line,tableau);
   	affichage_explosions_caos(collision_5_6,collision_3_tram_to_left, line,tableau);
   	affichage_explosions_caos(collision_5_6,collision_3_tram_to_left, line,tableau);
	affichages_pieton_caos(&trottoir);
	        affichages_pieton_caos(&trottoir4);
        affichages_pieton_caos(&trottoir5);
       // affichages_pieton_caos(&trottoir6);
        affichages_pieton_caos(&trottoir7);
        affichages_pieton_caos(&trottoirst);
	usleep(80000);
	}
	
}