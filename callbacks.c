#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "personne.h"





enum
{
	CIN,
	NOM,
	PRENOM,
	DATE,
	COLUMNS
};

void ajouter_personne(personne p)
{	
	FILE *f;
	f=fopen("utlisateurs.txt","a+");
	if(f!=NULL)
	{
		fprintf(f,"%s%s%s%s\n",p.nom,p.prenom,p.cin,p.date_naissance);
		fclose(f);
	}
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


		renderer=gtk_cell_renderer_text_view_new();									column=gtk_tree_view_column_new_with_attributes("date_naissance",renderer,"text",DATE,NULL);
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
			gtk_list_store_set(store,&iter,NOM,nom,PRENOM,prenom,CIN,cin,DATE,date_naissance, -1);
		}
	fclose(f);
	gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
	g_object_unref(store);
	}
}


void
on_ajouter_clicked                     (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{

personne p;

GtkWidget *nom;
GtkWidget *prenom;
GtkWidget *cin;
GtkWidget *date_naissance;

GtkWidget *fenetre_ajout;

nom=lookup_widget(objet_graphique,"nom");
prenom=lookup_widget(objet_graphique,"prenom");
cin=lookup_widget(objet_graphique,"cin");
date_naissance=lookup_widget(objet_graphique,"date_naissance");

strcpy(p.nom,gtk_entry_get_text(GTK_ENTRY(nom)));
strcpy(p.prenom,gtk_entry_get_text(GTK_ENTRY(prenom)));
strcpy(p.cin,gtk_entry_get_text(GTK_ENTRY(cin)));
strcpy(p.date_naissance,gtk_enty_get_text(GTK_ENTRY(date_naissance)));

ajouter_personne(p);

}


void on_afficher_clicked                    (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{

GtkWidget *fenetre_ajout;
GtkWidget *fenetre_afficher;
GtkWidget *treeview1;

fenetre_ajout=lookup_widget(objet_graphique,"fenetre_ajout");
gtk_widget_destroy(fenetre_ajout);

fenetre_afficher=lookup_widget(objet_graphique,"fenetre_afficher");
fenetre_afficher=create_fenetre_afficher();
gtk_widget_show(fenetre_afficher);

treeview1=lookup_widget(fenetre_afficher,"treeview1");

afficher_personne(treeview1);
}


void on_retour_clicked                      (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{

GtkWidget *fenetre_ajout;
GtkWidget *fenetre_afficher;

fenetre_afficher=lookup_widget(objet_graphique,"fenetre_afficher");

gtk_widget_destroy(fenetre_afficher);
fenetre_ajout=creat_fenetre_ajout();
gtk_widget_show(fenetre_ajout);

}

void
on_supprimer_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *treeview1;
supprimer ((char *)h.num_responsable);
GtkWidget *fenetre_afficher=lookup_widget(GTK_WIDGET(button),"fenetre_afficher");
treeview1=lookup_widget(fenetre_afficher,"treeview1");
afficher_hotel(treeview1);
gtk_widget_show(treeview1);

}



