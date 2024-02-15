#include "liste.h"
#include "makoto.h"

#include <math.h> 

/******************************************************************************************
*    simul.c: ce fichier concerne la partie de la simulation des lapins                   *
*            on utilise le code Makoto makoto.h pour avoir des nombres pseudo-aléatoires  *
*            on utilise aussi liste.h qui concerne toute la partie architecture qu'on va  *
*            utiliser pour ranger les Lapins et ses paramètres associés                   *
*******************************************************************************************/


/*********************************************************************************************
*   generateurMaturite: génère un chiffre qui représente la maturité choisite aléatoirement  *
*   entrée: rien                                                                             *
*                                                                                            *
*   sortie: un chiffre alétoire entre 5 et 8 avec genrand_real1()                            *
*            si le random est en dessous de 0.05 alors la valeur de retour est 4             *
*            si le random est en dessous de 0.2 alors la valeur de retour est 5              *
*            si le random est en dessous de 0.5 alors la valeur de retour est 6              *
*            si le random est en dessous de 0.8 alors la valeur de retour est 7              *
*            si le random est en dessous de 0.95 alors la valeur de retour est 8             *
*            sinon la valeur de retour est 9                                                 *
**********************************************************************************************/

int generateurMaturite()
{   
    double  maturite = genrand_real1();
    if(maturite < 0.05)
    {
        return 4;
    }
    else if(maturite < 0.2)
    {
        return 5;
    }
    else if(maturite < 0.5)
    {
        return 6;
    }
    else if(maturite < 0.8)
    {
        return 7;
    }
    else if(maturite < 0.95)
    {
        return 8;
    }
    return 9;
}


/********************************************************************************************
*    generateurMaleFemelle: génère un chiffre qui représente le sexe choisit aléatoirement  *
*                                                                                           *
*    entrée: rien                                                                           *
*                                                                                           *
*    sortie: un chiffre aléatoire entre 0 (mâle) et 1 (femelle) avec genrand_real1()        *
*            si il est en dessous de 0.5 alors la valeur de retour est 0 sinon 1            *
*********************************************************************************************/

int generateurMaleFemelle()
{
	double ran = genrand_real1();
	if( ran < 0.5 )
    {
		return 0;
	}
	return 1;
}


/***********************************************************************************************
*    lapereau: un Lapin plus le nouveau Lapin initialisée                                      *
*                                                                                              *
*    entrée: la liste de Lapin                                                                 *
*                                                                                              *
*    sortie: crée un nouveau élément dans la liste Lapin initilalisé comme un bébé lapin       *
*            on génère le sexe avec generateurMaleFemelle()                                    *
*            on génère l'âge de la maturité avec generateurMaturite()                          *
*            le reste des paramètres de Lapin est initialisé à 0 ou NULL pour les pointeurs    *
*            ensuite on regarde si la liste est vide ou pas pour reinitilaliser nb_elements,   *
*            la tail et le head de la liste                                                    *
************************************************************************************************/

ListeLapin * lapereau( ListeLapin* l ) 
{
	Lapin * E = malloc(sizeof(*E));
	if ( E == NULL ) 
    {
		fprintf(stderr, "Memory allocation error (E: NULL).");
		exit(EXIT_FAILURE);
	}

	E -> sexe         = generateurMaleFemelle();
    E -> age          = 0;
	E -> maturite     = generateurMaturite();
    E -> fertil       = 0;
    E -> nbPortee     = 0;
    E -> nbMoisPortee = 0;

	E -> next         = NULL;
	E -> prev         = NULL;

	if ( is_empty(l) ) 
    {
		l = malloc(sizeof(*l));
		if ( l == NULL ) {
			fprintf(stderr, "Memory allocation error (empty).");
			exit(EXIT_FAILURE);
		}

		l -> nb_elements    = 0;
		l -> head           = E;
		l -> tail           = E;
		
	}
	else 
    {
		l -> tail -> next   = E;
		E -> prev           = l -> tail;
		l -> tail           = E;
	}

	l -> nb_elements++;

	return l;
}


/**************************************************************************************************************
*    mort: tue un lapin                                                                                       *
*                                                                                                             *
*    entrée: un lapin                                                                                         *
*                                                                                                             *
*    sortie: un lapin avec toutes ses paramètres à 0 sauf pour l'âge qui est à -1  qui signifie la mort ici   *
***************************************************************************************************************/

Lapin * mort( Lapin * E )
{
    E -> age          = -1;
    E -> nbPortee     = 0;
    E -> nbMoisPortee = 0;
    E -> fertil       = 0;
    E -> sexe         = 0;
    E -> maturite     = 0;
    return E;
}


/**********************************************************************************************
*    fertilite: fertilité initilalisé dans la liste                                          *
*                                                                                             *
*    entrée: un Lapin                                                                         *
*                                                                                             *
*    sortie: initialise aléatoirement un lapin matures leurs fertilités qu'il                 *
*            soit mâle ou femelle                                                             *
*            avec une probabilité de 10% pour l'infertilité                                   *
*            si le lapin a atteint ou dépassé son âge de maturité                             *
*            on prend un nombre pseudo-aléatoire du code de makoto                            *
*            si ce nombre est inférieur à 0.1 alors il est infertile 0 sinon il est fertile   *
***********************************************************************************************/

Lapin * fertilite( Lapin * E )
{
    if( E -> age >= E -> maturite )
    {
        double ran = genrand_real1();
        if( ran <= 0.1 )
        {
            E -> fertil = 0;
        }
        E -> fertil = 1;
    }
    
    return E;
}


/*****************************************************************************************
*   auMoinsUnMale: vérifie si il y a au moins un mâle fertile, vivant et mature          *
*                                                                                        *
*    entrée: la listeLapin                                                               *
*                                                                                        *
*    sortie: un booléen qui détermine si il existe dans la liste un mâle fertile         *
*            (si il est fertile alors il est forcément mature)                           *
*            et vivant dès qu'on en trouve un on renvoie true sinon false                *
******************************************************************************************/

bool auMoinsUnMale( ListeLapin * l )
{
    Lapin * E = l -> head;
    for( int i = 0; i < l->nb_elements; i++ )
    {
        if( E -> age != -1 && E -> sexe == 0 && E -> fertil == 1 )
        {
            return true;
        }
        E = E -> next;
    }
    return false;
}


/*****************************************************************************************************
*    nbLapereauParPortee: génère un chiffre qui représente le nombre de bébés par portée             *
*                        choisit aléatoirement entre 2 et 7                                          *
*                                                                                                    *
*    entrée: rien                                                                                    *
*                                                                                                    *
*    sortie: un chiffre alétoire entre 5 et 8 avec genrand_real1                                     *
*            si le random est en dessous de 0.05 alors la valeur de retour est 2                     *
*            si le random est en dessous de 0.2 alors la valeur de retour est 3                      *
*            si le random est en dessous de 0.5 alors la valeur de retour est 4                      *
*            si le random est en dessous de 0.8 alors la valeur de retour est 5                      *
*            si le random est en dessous de 0.95 alors la valeur de retour est 6                     *
*            sinon la valeur de retour est 7                                                         *
*******************************************************************************************************/

int nbLapereauParPortee()
{
    double  nbBebe = genrand_real1();
    if(nbBebe < 0.05)
    {
        return 2;
    }
    else if(nbBebe < 0.2)
    {
        return 3;
    }
    else if(nbBebe < 0.5)
    {
        return 4;
    }
    else if(nbBebe < 0.8)
    {
        return 5;
    }
    else if(nbBebe < 0.95)
    {
        return 6;
    }
    return 7;
}


/********************************************************************************************************************
* nbPortee: détermine le nombre de portée d'une lapine dans l'année                                                 *
*                                                                                                                   *
*    entrée: un Lapin et un tableau contenant toutes les probabilités pour le nombre de portée                      *
*                                                                                                                   *
*    sortie: un Lapin mofifié avec le nombre de portée de chaque femelle si celles-ci sont fertile                  *
*            et que son compteur de nbMoisPortee sont à 0 et qu'il existe au moins une mâle qui puis la fécondé     *
*            si toutes ces conditions sont remplis alors on choisit un psr aléatoirement                            *
*                et on le compare avec le tableau                                                                   *
*            si psr est plus petit que l'une des valeur du tableau                                                  *
*                alors on incrémente le nbPortee de la lapine de l'index du tableau+2                               *
*            et on incrémente nbMoisPortee de 12 pour dire que pendant 12 mois                                      *
*                la lapine ne pourra pas avoir des nouvelles portées                                                *
*********************************************************************************************************************/

Lapin * nbPortee( Lapin * E, double tabProbaPortee[9], bool auMoinsUnMale )
{
    if( E -> sexe == 1 && E -> fertil == 1 && auMoinsUnMale && E -> nbMoisPortee == 0 )
    {
        double psr = genrand_real1();
        for( int j = 0; j < 9; j++ )
        {
            if( psr <= tabProbaPortee[j] && E -> nbMoisPortee == 0 )
            {
                E -> nbPortee       = j + 2;
                E -> nbMoisPortee   = 12;
            }
        }
    }
    return E;
}


/***********************************************************************************************************
*    naissance: crée des nouveaux lapereau en fonction d'une portée                                        *
*                                                                                                          *
*    entrée: un lapin                                                                                      *         
*                                                                                                          *
*    sortie: si les lapines qui ont nbPortee > 0                                                           *
*            alors nbLapereauParPortee() lapereau est crée et le nbPortee est décrémenté de 1              *
*                en inilisant un nombre random avec genrand_real1()                                        *
*                si nombre random est inférieur à 0.15 alors la lapine qui vient de crée une portée meurt  *
************************************************************************************************************/

int naissance( Lapin * E )
{
    int c = 0;
	if( E -> nbPortee != 0 )
    {
        c = nbLapereauParPortee(E);
        E -> nbPortee = E -> nbPortee - 1;

        double ran = genrand_real1();
        if( ran <= 0.15 )
        {
            E = mort( E );
        }
    }
    return c;
}


/******************************************************************************************
*    ageMois: incrémente l'âge de 1                                                       *
*                                                                                         *
*    entrée: un Lapin                                                                     *
*                                                                                         *
*    sortie: un Lapin avec l'âge incrémenté de 1 pour les lapins vivants                  *
*            et pour les lapines qui ont le nbMoisPortee strictement positif              *
*            alors nbMoisPortee est décrémenté de 1                                       *
*******************************************************************************************/

Lapin * ageMois( Lapin * E )
{   
    if( E -> age != -1 )
    {   if(E -> nbMoisPortee != 0)
        {
            E -> nbMoisPortee = E -> nbMoisPortee - 1;
        }
        E -> age = E -> age + 1;
    }
    return E;
}


/******************************************
*    anneeEnMois: change l'année en mois  *
*                                         *
*    entrée: un entier année              *
*                                         *
*    sortie: année * 12                   *
*******************************************/

double anneeEnMois( int annee )
{
    return annee * 12;
}


/*****************************************************************************
*    tauxEnMois: change le taux de l'année en mois grâce à la formule        *
*                (1 + tmois)^12 = (1 + tannee)                               *
*                                                                            *
*    entrée: un flottant annee                                               *
*                                                                            *
*    sortie: retourne le flottant issus de ( 1 + annee ) ^ ( 1 / 12 ) - 1    *
******************************************************************************/

float tauxEnMois( float annee )
{
    return pow( 1 + annee, 1.0 / 12 ) - 1;
}


/*****************************************************************************************************************************************
*    tauxDeSurvie: calcul pour chaque lapin son taux de survie en fonction de son âge                                                    *
*                                                                                                                                        *
*    entrée: uun Lapin                                                                                                                   *
*                                                                                                                                        *
*    sortie: un lapin modifiée s'l est mort                                                                                              *
*            d'abord on vérifie si le lapin n'est pas déjà mort avant de calculer son taux de survie                                     *
*            ensuite on initialise un renard qui peut manger des lapins selon un nombre pseudo-aléaotire                                 *
*                et un nombre pseudo-aléatoire pour calculer le taux aléatoire                                                           *
*            pour chaque année de la vie d'un il a un certain taux de survie                                                             *
*                (on a calculé le taux de survie par mois car notre itération est en mois / pareil pour l'année)                         *
*                donc                                                                                                                    *
*                si il n'est pas mature et qu'il a un taux de survie inférieur à tauxEnMois(0.5) alors il meurt                          *
*                si il est entre sa maturite et ses 8ans et qu'il a un taux de survie inférieur à tauxEnMois(0.75) alors il meurt        *
*                si il a 8ans et qu'il a un taux de survie inférieur à tauxEnMois(0.6) alors il meurt                                    *
*                si il a 9ans et qu'il a un taux de survie inférieur à tauxEnMois(0.45) alors il meurt                                   *
*                si il a 10ans et qu'il a un taux de survie inférieur à tauxEnMois(0.3) alors il meurt                                   *
*                si il a 11ans et qu'il a un taux de survie inférieur à tauxEnMois(0.15) alors il meurt                                  *
*                si il a 12ans alors il meurt                                                                                            *
*                si le renard est inferieur à 0.05 alors le renard a mangé le lapin                                                      *
******************************************************************************************************************************************/

Lapin * tauxDeSurvie( Lapin * E )
{
    if ( E -> age != -1 )
    {
        double renard = genrand_real1();
        double ran = genrand_real1();
        if ( E -> age < E -> maturite )
        {
            if ( ran <= tauxEnMois( 0.5 ) )
            {
                E = mort( E );
            } 
        }
        else if ( E -> age >= E -> maturite && E -> age < anneeEnMois( 8 ) )
        {
            if ( ran <= tauxEnMois( 0.75 ) )
            {
                E = mort( E );
            } 
        } 
        else if ( E -> age >= anneeEnMois( 8 ) && E -> age < anneeEnMois( 9 ) )
        {
            if ( ran <= tauxEnMois( 0.6 ) )
            {
                E = mort( E );
            } 
        } 
        else if ( E -> age >= anneeEnMois( 9 ) && E -> age < anneeEnMois( 10 ) )
        {
            if ( ran <= tauxEnMois( 0.45 ) )
            {
                E = mort( E );
            } 
        }  
        else if ( E -> age >= anneeEnMois( 10 ) && E -> age < anneeEnMois( 11 ) )
        {
            if ( ran <= tauxEnMois( 0.3 ) )
            {
                E = mort( E );
            } 
        }         
        else if ( E -> age >= anneeEnMois( 11 ) && E -> age < anneeEnMois( 12 ) )
        {
            if ( ran <= tauxEnMois( 0.15 ) )
            {
                E = mort( E );
            } 
        }
        if ( E -> age >= anneeEnMois( 12 ) || renard <= 0.05 ) 
        {
            E = mort( E );
        }     
    }
    return E;
}

/*********************************************MAIN***************************************************************/



int main(){
    // Initialisation de Matsumoto
    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    init_by_array(init, length);

    // Initialisation liste et constante
    ListeLapin *l                   = new_liste();
    double      tabProbaPortee[9]   = {0.01, 0.05, 0.16, 0.33, 0.68, 0.87, 0.96, 0.99, 1};
    int         n_t                 = 0,
                duree_t             = 0;

    printf("Combien de lapins voulez-vous pour commencer la simulation ?\n");
    scanf("%d", &n_t);

    printf("Pendant combien de temps voulez-vous que la simulation dure en mois ? (conseille pas plus de 100 mois)\n");
    scanf("%d", &duree_t);

    // Création de n lapins comme initialisation
    for( int i = 0; i < n_t; i++ )
    {
        l = lapereau(l);
    }

    // Simulation pendant duree_t mois pour toute la liste de lapin
    for( int nbMois = 0; nbMois <= duree_t; nbMois++ )
    { 
        Lapin * E           = l -> head;
        bool    maleFertil  = auMoinsUnMale(l);
        int     lapinEnVie  = 0,
                nouveauBebe = 0;

        for(int i = 0; i < l -> nb_elements; i++)
        {
            E           = fertilite( E );
            E           = nbPortee( E, tabProbaPortee, maleFertil);
            nouveauBebe += naissance( E );
            E           = tauxDeSurvie( E );

            if( E -> age != -1 )
            {
                lapinEnVie++;
            }

            E           = ageMois( E );
            E           = E -> next;
        }

        for( int j = 0; j < nouveauBebe; j++)
        {
            l = lapereau( l );
            lapinEnVie++;
        }

        printf("mois: %d\nLapins en vie: %d\nLapins morts: %d\nLapins durant l'experience: %d\n\n", nbMois, lapinEnVie, l -> nb_elements - lapinEnVie, l -> nb_elements);
    }

    // Fin de la simulation, libération de la liste
    freeListe( l );

    return 0;
}



