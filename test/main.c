#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define FILENAME_SIZE 1024
#define MAX_LINE 2048

struct kniha
{
    char nazov[30];
    char autor[30];
    int rok;
    char ISBN[20];
};

int pokracovat;
int menu()
{
    printf("Zadaj číslo 1 ak chceš zobraziť knihy v knižnici: \n");
    printf("Zadaj číslo 2 ak chceš pridať knihu do knižnice: \n");
    printf("Zadaj číslo 3 ak chceš odstrániť knihu z knižnice: \n");
    printf("Zadaj číslo 4 ak chceš ukončit program: \n");

    int zadane_cislo;
    scanf("%d", &zadane_cislo);

    return zadane_cislo;
}

void zadajKnihu(struct kniha *kn)
{
    printf("Zadaj nazov knihy:\n");
    fflush(stdout);
    scanf(" %30[^\n]%*[^\n]", kn->nazov);
    printf("Zadaj autora knihy: \n");
    fflush(stdout);
    scanf(" %30[^\n]%*[^\n]", kn->autor);
    printf("Zadaj rok knihy: \n");
    fflush(stdout);
    scanf("%d", &(kn->rok));
    printf("Zadaj ISBN knihy: \n");
    fflush(stdout);
    scanf(" %20[^\n]%*[^\n]", kn->ISBN);
}

int main()
{
    for (;;)
    {
        int zvolene_menu = menu();

        if (zvolene_menu == 2)
        {
            do
            {
                struct kniha kn;

                zadajKnihu(&kn);

                FILE *subor = fopen("kniznica.txt", "a+");
                fprintf(subor, "%s,%s,%d,%s\n", kn.nazov, kn.autor, kn.rok, kn.ISBN);
                pokracovat = 1;

                fclose(subor);

                pokracovat = 0;
                printf("Ak chceš zadávat dalšiu knihu zadaj 1 a ak nie zadaj 0: ");
                scanf("%d", &pokracovat);
            } while (pokracovat == 1);
        }
        if (zvolene_menu == 1)
        {
            char riadok[100];
            FILE *subor = fopen("kniznica.txt", "r");

            for (int i = 0; i < 100; i++)
            {

                fscanf(subor, " %100[^\n]%*[^\n]", riadok);
                printf("%s\n", riadok);
                if (riadok[0] == '\0')
                {
                    break;
                }
                fflush(stdout);
                memset(riadok, 0, sizeof(riadok));
            }
        }
        if (zvolene_menu == 3)
        {

            FILE *subor, *subor2;

            char subor1[1024];
            char docasny_subor[1024];

            char buffer[2048];
            int vymazat = 0;

            strcpy(docasny_subor, "docasny____");
            strcat(docasny_subor, "kniznica.txt");

            printf("Zadajte číslo riadka od hora, ktorý chcete vymazať: ");
            scanf("%d", &vymazat);

            subor = fopen("kniznica.txt", "r");
            subor2 = fopen(docasny_subor, "w");

            if (subor == NULL || subor2 == NULL)
            {
                printf("Nedá sa\n");
                return 1;
            }

            bool citat = true;
            int moment_riadok = 1;
            do
            {
                fgets(buffer, 2048, subor);

                if (feof(subor))
                    citat = false;
                else if (moment_riadok != vymazat)
                    fputs(buffer, subor2);

                moment_riadok++;

            } while (citat);

            fclose(subor);
            fclose(subor2);

            remove(subor1);
            rename(docasny_subor, "kniznica.txt");
        }
        if (zvolene_menu == 4)
        {
            return 0;
        }
        printf("\n");
    }
    return 0;
}
