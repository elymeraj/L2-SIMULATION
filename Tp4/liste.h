/*
	Ce fichier contient les srtuctures des listes ainsi que les signatures des fonctions primaires
	associé à ces structures qui permet notamment de créer, d'accéder et de libérer aux listes
	Ce fichier est utilie pour la création de Lapereau, de débuggage (afficheListe) et de libération
	de la liste.
*/

#ifndef __DLIST__H__
#define __DLIST__H__

#include <stdio.h>
#include <stdlib.h>


/*
	bool: structure qui possède 2 types: soit true ou false 
*/

typedef enum 
{
	false,
	true
}bool;


typedef struct Lapin Lapin;
typedef struct ListeLapin ListeLapin;


/*
	Lapin: structure qui possède tous les paramètres qu'un lapin pourrait avoir besoin 
		next: un pointeur sur l'élément suivant de la liste
		prev: un pointeur sur l'élément précèdent de la liste

		un entier sexe: 0 pour mâle et 1 pour femelle
		un entier age: l'âge courant du lapin en mois si l'âge du lapin est -1 alors il est mort
		un entier maturite: l'âge à laquel le lapin devient mature
		un entier fertil: si le lapin est fertile 1 ou pas 0
		un entier nbPortee: le nombre de portée qu'une lapine a dans l'année
		un entier nbMoisPortee: le décompte dans laquelle la lapine ne peut pas avoir de lapereau
								car la lapine accouche les 1er mois (cad 5 nombre de portée alors la lapine accouche les 5 1er mois)
								puis pendant le reste de l'année (12-nbPortee) on attend qu'elle soit fécondable
*/

struct Lapin
{
	Lapin * next;
	Lapin * prev;
	int sexe;
	int age;
	int maturite; 
	int fertil;
	int nbPortee;
	int nbMoisPortee;
};


/*
	ListeLapin: une structure qui prend en paramètre une autre structure pour former une liste
				nb_elements: le nombre d'élément Lapin qu'il y a dans la liste
				head: un pointeur sur la tête de la liste
				tail: un pointeur sur la queue de la liste
*/

struct ListeLapin
{
	int nb_elements;
	Lapin * head;
	Lapin * tail;
};


/*
	new_liste: créer une nouvelle structure qui pointe sur NULL

	entrée: void

	sortie: une nouvelle struture dites listeLapin
*/

ListeLapin * new_liste( void );


/*
	is_empty: vérifie si la structure est vide

	entrée: une liste de Lapin

	sortie: retourne true si la liste est NULL et false sinon
*/

bool is_empty( ListeLapin* l );


/*
	freeListe: libère la listeLapin de chaque paramètre de la struture Lapin

	entrée: une liste de Lapin

	sortie: rien
*/

void freeLapin( ListeLapin* l );
void freeListe( ListeLapin* l );


/*
	afficheListe: affiche les éléments de Lapin de la listeLapin (utile juste pour le débuggage)

	entrée: une liste de Lapin

	sortie: affiche chaque éléments de Lapin de la listeLapin
*/

void afficheListe( ListeLapin* l );

#endif
