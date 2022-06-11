#include <stdio.h>
#include <stdbool.h>
#include "sakk.h"

int main() {

    int option = 0;
    printf("Udvozlunk a sakk jatekprogramunkban!\n");

    while (option != 3) {

        printf("Uj jatek [1] / Jatek betoltese [2] / Kilepes [3]:\n");
        if (beolvas_int(&option)) {
            bool sikeres = false;
            switch (option) {
                case 1: {
                    printf("\n");

                    jatekos_beker();
                    tabla_inicializal();
                    tabla_feltolt();
                    tabla_kiir();
                    sikeres = true;
                }
                    break;
                case 2: {
                    char filename_user[50];
                    printf("Fajlnev, amibol betoltheto a jatek: ");
                    fgets(filename_user, 50, stdin);
                    if (jatek_betolt(filename_user)) {
                        printf("Sikeres fajlolvasas!\n");

                        sikeres = true;
                        break;
                    }

                    printf("Nem sikerult a fajl olvasasa!\n");
                }
                    break;
                case 3: {
                    printf("Sikeres kilepes!\n");
                    m_cleanup();
                }
                    break;
                default:
                    printf("Helytelen opcio!\n");
            }
            if (sikeres) {

                while (!nyert_e_valaki()) {

                    jatekos feher = get_jatekos(true), fekete = get_jatekos(false);
                    bool feher_sikeres = false, fekete_sikeres = false;

                    printf("\n%s kore kovetkezik!\n", feher.nev);
                    while (!feher_sikeres) {
                        int feher_option;
                        printf("Valassz mit szeretnel (parti feladas [1] / jatek elmentese [2] / sancolas [3] / atvaltozas [4] / "
                               "lepes babuval [5] / visszalepes [6] / kilepes [7]):\n");
                        if (beolvas_int(&feher_option)) {
                            fflush(stdin);
                            switch (feher_option) {
                                case 1: {
                                    printf("A jatekot sikeresen feladtad.\nNyertes %s!\n", fekete.nev);
                                    m_cleanup();
                                    feher_sikeres = true;
                                    return 0;
                                }
                                case 2: {
                                    char filename_save[50];
                                    printf("Fajlnev, amibe elmentheto a jatek: ");
                                    fgets(filename_save, 50, stdin);
                                    if (jatek_elment(filename_save)) {
                                        printf("Sikeres mentes!\n");
                                        feher_sikeres = true;
                                        return 0;
                                    } else {
                                        printf("Nem sikerult elmenteni a jatekot!\n");
                                    }
                                }
                                    break;
                                case 3: {
                                    if (sancolas(feher)) {
                                        tabla_kiir();
                                        feher_sikeres = true;
                                    }
                                }
                                    break;
                                case 4: {
                                    if (atvaltozas(feher)) {
                                        tabla_kiir();
                                        feher_sikeres = true;
                                    }
                                }
                                    break;
                                case 5: {
                                    if (lepes_f(feher)) {
                                        tabla_kiir();
                                        feher_sikeres = true;
                                    }
                                }
                                    break;
                                case 6: {
                                    list_print();
                                    if (list_count() > 0 && visszalepes_interact()) {
                                        tabla_kiir();
                                        feher_sikeres = true;
                                    } else{
                                        printf("Nem lehet visszalepni!\n");
                                    }
                                }
                                    break;
                                case 7: {
                                    printf("Sikeres kilepes!\n");
                                    m_cleanup();
                                    return 0;
                                }
                                default:
                                    printf("Nem jo opciot adott meg!\n");
                                    break;
                            }
                        } else {
                            printf("Vegzetes hiba tortent a beolvasas soran!\n");
                            m_cleanup();
                            return 0;
                        }
                    }

                    printf ("\n%s kore kovetkezik!\n", fekete.nev);
                    while (!fekete_sikeres) {
                        int fekete_option;
                        printf("Valassz mit szeretnel (parti feladas [1] / jatek elmentese [2] / sancolas [3] / atvaltozas [4] / "
                               "lepes babuval [5] / visszalepes [6] / kilepes [7]):\n");
                        if (beolvas_int(&fekete_option)) {
                            fflush(stdin);
                            switch (fekete_option) {
                                case 1: {
                                    printf("A jatekot sikeresen feladtad.\nNyertes %s!\n", feher.nev);
                                    m_cleanup();
                                    fekete_sikeres = true;
                                    return 0;
                                }
                                case 2: {
                                    char filename_save[50];
                                    printf("Fajlnev, amibe elmentheto a jatek: ");
                                    fgets(filename_save, 50, stdin);
                                    if (jatek_elment(filename_save)) {
                                        printf("Sikeres mentes!\n");
                                        fekete_sikeres = true;
                                        return 0;
                                    } else {
                                        printf("Nem sikerult elmenteni a jatekot!\n");
                                    }
                                }
                                    break;
                                case 3: {
                                    if (sancolas(fekete)) {
                                        tabla_kiir();
                                        fekete_sikeres = true;
                                    }
                                }
                                    break;
                                case 4: {
                                    if (atvaltozas(fekete)) {
                                        tabla_kiir();
                                        fekete_sikeres = true;
                                    }
                                }
                                    break;
                                case 5: {
                                    if (lepes_f(fekete)) {
                                        tabla_kiir();
                                        fekete_sikeres = true;
                                    }
                                }
                                    break;
                                case 6: {
                                    list_print();
                                    if (list_count() > 0 && visszalepes_interact()) {
                                        tabla_kiir();
                                        fekete_sikeres = true;
                                    } else{
                                        printf("Nem lehet visszalepni!\n");
                                    }
                                }
                                    break;
                                case 7: {
                                    printf("Sikeres kilepes!\n");
                                    m_cleanup();
                                    return 0;
                                }
                                default:
                                    printf("Nem jo opciot adott meg!\n");
                                    break;
                            }
                        } else {
                            printf("Vegzetes hiba tortent a beolvasas soran!\n");
                            m_cleanup();
                            return 0;
                        }
                    }

                }
            }
        } else {
            printf("Vegzetes hiba tortent a beolvasas soran!\n");
            m_cleanup();
            return 0;
        }
    }
    m_cleanup();
    return 0;
}

