#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "personne.h"



enum
{
	CIN,
	NOM,
	PRENOM,
	DATE_NAISSANCE,
	COLUMNS
};

void ajouter_personne(personne p)
{	
	FILE *f;
	f=fopen("utlisateurs.txt","a+");
	if(f!=NULL)
	{
		fprintf(f,"%s%s%s%s\n",p.nom,p.prenom,p.cin,p.date_naissance);
	}
		fclose(f);
}
		

void afficher_personne(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;

	GtkListStore *store;

	char nom[30];
	char prenom[30];
	char cin[30];
	char date_naissance[30];

	store=NULL;
	
	FILE *f;

	store=gtk_tree_view_get_model(liste);
	if (store==NULL)
	{
		
		renderer=gtk_cell_renderer_text_view_new();									column=gtk_tree_view_column_new_with_attributes("nom",renderer,"text",NOM,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);	
		
											   renderer=gtk_cell_renderer_text_view_new();								column=gtk_tree_view_column_new_with_attributes("prenom",renderer,"text",PRENOM,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);	


					renderer=gtk_cell_renderer_text_view_new();									column=gtk_tree_view_column_new_with_attributes("cin",renderer,"text",CIN,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);	


		renderer=gtk_cell_renderer_text_view_new();									column=gtk_tree_view_column_new_with_attributes("date_naissance",renderer,"text",DATE_NAISSANCE,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);	


	}

store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	
	f=fopen("utilisateurs.txt","r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		f=fopen("utlisateurs.txt","a+");
		while(fscanf(f,"%s %s %s %s \n",nom,prenom,cin,date_naissance)!=EOF)
		{
			gtk_list_store_append(store,&iter);
			gtk_list_store_set(store,&iter,NOM,nom,PRENOM,prenom,CIN,cin,DATE_NAISSANCE,date_naissance, -1);
		}
	fclose(f);
	gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
	g_object_unref(store);
	}
}

void supprimer (char *num_responsable)
{
hotel h;
FILE *old;
FILE *new=NULL;

new=fopen("ajout","wb");
fclose(new);

old=fopen("hotel.bin","rb");
new=fopen("hotel_test.bin","ab");

int i=0;
while(!(feof(old)))
       {i++;
        fread(&h,1,sizeof(hotel),old);
       }
fclose(old);
old=fopen("hotel.bin","rb");

int j=0;
while(j<i-1)
      {j++;
       fread(&h,1,sizeof(hotel),old);

       if(strcmp(h.num_responsable,num_responsable))
             {
             fwrite(&h,sizeof(hotel),1,new);
             }
      }
fclose(new);
fclose(old);
remove("hotel.bin");
rename("hotel_test.bin","hotel.bin");
}





