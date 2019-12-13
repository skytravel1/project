#include <gtk/gtk.h>

typedef struct
{

char nom[20];
char prenom[20];
char cin[20];
char date_naissance[20];

}personne;

void ajouter_personne(personne p);
void afficher_personne(GtkWidget *liste);
