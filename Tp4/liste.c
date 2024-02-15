#include "liste.h"
#include <stdio.h>
#include <stdlib.h>


ListeLapin * new_liste( void ) 
{
	return NULL;
}

bool is_empty( ListeLapin* l ) 
{
	if (l == NULL) 
	{
		return true;
	}
	return false;
}

void freeLapin( ListeLapin* l ) 
{
	if(l == NULL)
	{
		exit(EXIT_FAILURE);
	}
    else if(l -> nb_elements > 1)
    {
        Lapin* tmp = l -> head;
        l -> head = tmp -> next;
        l -> nb_elements--;
        free(tmp);
    }
    else if(l -> nb_elements == 1)
    {
        free(l -> head);
        l -> head = NULL;
        l -> tail = NULL;
        l -> nb_elements = 0;
    }
}

void freeListe( ListeLapin* l )
{
    while( l -> nb_elements > 0 )
    {
        freeLapin(l);
    }
    free(l);
	l = NULL;
}

void afficheListe( ListeLapin* l ) {
	Lapin   * 	E = malloc(sizeof(*E));
				E = l->head;
	int 		i = 0;
	do
	{
		printf("Lapin %d -> ", i);
		printf("sexe: %d, ", E->sexe);
		printf("age: %d, ", E->age);
		printf("maturite: %d, ", E->maturite);
		printf("fertil: %d, ", E->fertil);
		printf("nbPortee: %d, ", E->nbPortee);
		printf("nbMoisPortee: %d\n", E->nbMoisPortee);
		E = E->next;
		i++;
	} while (E != NULL);
}



