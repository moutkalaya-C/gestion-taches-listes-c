#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tache {
    int id;
    char titre[100];
    int priorite; // 1 = Haute, 2 = Moyenne, 3 = Basse
    struct Tache *suivant;
} Tache;

Tache *tete = NULL;
int compteurId = 1;

void ajouterTache() {
    Tache *nouvelle = (Tache *)malloc(sizeof(Tache));
    if (nouvelle == NULL) {
        printf("Erreur d'allocation memoire.\n");
        return;
    }

    nouvelle->id = compteurId++;
    getchar(); // Nettoyer le buffer
    printf("Titre de la tache : ");
    fgets(nouvelle->titre, sizeof(nouvelle->titre), stdin);
    nouvelle->titre[strcspn(nouvelle->titre, "\n")] = 0;

    printf("Priorite (1: Haute, 2: Moyenne, 3: Basse) : ");
    scanf("%d", &nouvelle->priorite);

    nouvelle->suivant = tete;
    tete = nouvelle;
    printf("Tache ajoutee avec succes (ID: %d).\n", nouvelle->id);
}

void afficherTaches() {
    if (tete == NULL) {
        printf("\nAucune tache en cours.\n");
        return;
    }
    Tache *courant = tete;
    printf("\n--- Liste des Taches ---\n");
    while (courant != NULL) {
        printf("[ID: %d] %s | Priorite: %d\n", 
               courant->id, courant->titre, courant->priorite);
        courant = courant->suivant;
    }
}

void supprimerTache() {
    if (tete == NULL) {
        printf("La liste est vide.\n");
        return;
    }
    int idSuppr;
    printf("Entrez l'ID de la tache a supprimer : ");
    scanf("%d", &idSuppr);

    Tache *courant = tete;
    Tache *precedent = NULL;

    while (courant != NULL && courant->id != idSuppr) {
        precedent = courant;
        courant = courant->suivant;
    }

    if (courant == NULL) {
        printf("Tache avec ID %d introuvable.\n", idSuppr);
        return;
    }

    if (precedent == NULL) {
        tete = courant->suivant;
    } else {
        precedent->suivant = courant->suivant;
    }

    free(courant);
    printf("Tache supprimee et memoire liberee.\n");
}

void libererMemoire() {
    Tache *courant = tete;
    while (courant != NULL) {
        Tache *temp = courant;
        courant = courant->suivant;
        free(temp);
    }
    tete = NULL;
}

int main() {
    int choix;
    do {
        printf("\n=== GESTIONNAIRE DE TACHES (LISTES CHAINEES) ===\n");
        printf("1. Ajouter une tache\n");
        printf("2. Afficher les taches\n");
        printf("3. Supprimer une tache\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: ajouterTache(); break;
            case 2: afficherTaches(); break;
            case 3: supprimerTache(); break;
            case 0:
                libererMemoire();
                printf("Memoire liberee. Fermeture...\n");
                break;
            default: printf("Choix invalide.\n");
        }
    } while (choix != 0);
    return 0;
}
