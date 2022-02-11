//==============================================================================
// Created by Patrik Fusek 
// "c:\data\Install\STU FIIT\Predmety\PRPR_B\Projekt1pTableReverse\"
//
//==============================================================================

#define _CRT_SECURE_NO_WARNINGS

//==============================================================================
//
//==============================================================================

#include <stdio.h>
#include <stdlib.h> 
#include <conio.h>
#include<ctype.h>
#include <string.h>
//==============================================================================
//
//==============================================================================

void** Alokuj(int pocetZaznamov);
void AlokujPamet(char** pRetazec, int* velkost, int pocetRiadkovZaznamu);
void AlokujPametForIntArray(int** pInt, int velkost, int pocetRiadkovZaznamu);
void DealokujPamet(char** pRetazec, int pocetPrezenterov);
void Dealokuj(void** pTable, int pocetZaznamov);
void PrintZaznamy(void** pTable, int pocetZaznamov);
int KontrolaRodnehoCisla(char* buffer, int zaznam);

//==============================================================================
//
//==============================================================================
char* DajRiadokZaznamu(void** pTable, int cisloZaznamu, int cisloRiadku)
{
    return ((char**)(pTable[cisloZaznamu]))[cisloRiadku];  
  
}

//==============================================================================
//
//==============================================================================
void ZapisHodnotuInt(int** pInt, int cisloZaznamu, int cisloRiadku)
{
    int h = *(((char**)(pInt[cisloZaznamu]))[cisloRiadku]);
    h++;
    *(((char**)(pInt[cisloZaznamu]))[cisloRiadku]) = h;
}

//==============================================================================
//
//==============================================================================
int DajHodnotuInt(int** pInt, int cisloZaznamu, int cisloRiadku)
{
    return *(((char**)(pInt[cisloZaznamu]))[cisloRiadku]);
}

//==============================================================================
//
//==============================================================================
void DajRiadokZaznamuPrikazH(int** hodnota, int cisloZaznamu, int cisloRiadku)
{
    ZapisHodnotuInt(hodnota, cisloZaznamu, cisloRiadku);
}

//==============================================================================
//
//==============================================================================
char* VratRiadokZaznamu(void** pTableStore, int cisloZaznamu, int cisloRiadku)
{
    return ((char**)(pTableStore[cisloZaznamu]))[cisloRiadku];
}


//==============================================================================
//
//==============================================================================
int DajPocetZaznamov(FILE* zoznamF)
{
    int chCount = 0;
    int pocetZaznamov = 0;
    char ch;
    int  pocetCharNovyRiadok = 0;
    rewind(zoznamF);
    while (EOF != (ch = fgetc(zoznamF)))
    {
        chCount++;
        //if (ch == '\n' || ch == '\r' )
        if (ch == '\n')
        {
            pocetCharNovyRiadok++;
            if (pocetCharNovyRiadok == 2)
            {
                pocetCharNovyRiadok = 0;
                pocetZaznamov++;
            }
        }
        else
        {
            pocetCharNovyRiadok = 0;
        }
    }
    if (ch == EOF)
    {
        pocetZaznamov++;
    }
    rewind(zoznamF);
    return pocetZaznamov;
}

//==============================================================================
//
//==============================================================================
int KontrolaRodnehoCisla(char* buffer, int zaznam)
{
    int maxRC = 10;
    size_t i;

    long long num = 0;
    for (i = 0; i < strlen(buffer); i++)
    {
        num = num * 10 + ((long long)buffer[i] - '0');
    }
    if ((int)strlen(buffer) == maxRC && num % 11 == 0)
    {
        return 1;
    }
    else
    {
        printf("Nekorektne zadany vstup v zazname %d: rodne cislo %s\n", zaznam + 1, buffer);
        return 0;
    }
}

//==============================================================================
//
//==============================================================================
int KontrolaKoduMiestnosti(char* buffer, int zaznam)
{

    if (strlen(buffer) == 3 && isupper(buffer[0]) && isdigit(buffer[1]) && isdigit(buffer[2]))
    {
        return 1;
    }
    else
    {
        if (zaznam == -1)
        {
            printf("Nekorektne zadany vstup v prikazeO: kod miestnosti %s\n", buffer);
        }
        else if (zaznam == -2)
        {

        }
        else
        {
            printf("Nekorektne zadany vstup v zazname %d: kod miestnosti %s\n", zaznam + 1, buffer);
        }
        return 0;
    }
}

//==============================================================================
//
//==============================================================================
int KontrolaTypuPrezentovania(char* buffer, int zaznam)
{
    if (strcmp(buffer, "PP") != 0)
        if (strcmp(buffer, "PD") != 0)
            if (strcmp(buffer, "UP") != 0)
                if (strcmp(buffer, "UD") != 0)
                {
                    if (zaznam > -2)
                    {
                        printf("Nekorektne zadany vstup v zazname %d: Typ Prezentovania %s\n", zaznam + 1, buffer);
                    }
                    return 0;
                }
    return 1;
}

//==============================================================================
//
//==============================================================================
int KontrolaCasuPrezentovania(char* buffer, int zaznam)
{
    int  isValidFlag = 1;
    char aHour[3];
    char aMinute[3];

    aHour[2] = 0;
    aMinute[2] = 0;
    memcpy(aHour, buffer, 2);
    memcpy(aMinute, buffer + 2, 2);

    if (isdigit(buffer[0]) && isdigit(buffer[1]) && isdigit(buffer[2]) && isdigit(buffer[3]) && strlen(buffer) == 4)
    {
        int hour = atoi(aHour);
        int minute = atoi(aMinute);

        if ((hour < 0 || hour > 23) || (minute < 0 || minute > 59))
        {
            isValidFlag = 0;
        }
    }
    else
    {
        isValidFlag = 0;
    }

    if (isValidFlag == 0 && zaznam > -2)
    {
        printf("Nekorektne zadany vstup v zazname %d: Cas Prezentovania %s\n", zaznam + 1, buffer);

    }
    return isValidFlag;
}

//==============================================================================
//
//==============================================================================
int KontrolaDatumu(char* buffer, int zaznam)
{
    if (strlen(buffer) != 8 && zaznam > -2)
    {
        if (zaznam == -1)
        {
            printf("Nekorektne zadany vstup v prikazeO: Datum %s\n", buffer);
        }
        else
        {
            printf("Nekorektne zadany vstup v zazname %d: Datum %s\n", zaznam + 1, buffer);
        }
        return 0;
    }
    char aYear[5];
    char aMonth[3];
    char aDay[3];

    aYear[4] = 0;
    aMonth[2] = 0;
    aDay[2] = 0;

    memcpy(aYear, buffer, 4);
    memcpy(aMonth, buffer + 4, 2);
    memcpy(aDay, buffer + 6, 2);

    int year = atoi(aYear);
    int month = atoi(aMonth);
    int day = atoi(aDay);

    int pocetDnivMesiaci[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    if ((year <= 0 || year > 9999) || (month <= 0 || month > 12) || (day <= 0 || day > pocetDnivMesiaci[month - 1]))
    {
        if (zaznam == -1)
        {
            printf("Nekorektne zadany vstup v prikazeO: Datum %s\n", buffer);
        }
        else if (zaznam == -2) {}
        else
        {
            printf("Nekorektne zadany vstup v zazname %d: Datum %s\n", zaznam + 1, buffer);
        }

        return 0;
    }

    return 1;
}

//==============================================================================
//
//==============================================================================
void DajObsahZaznamovFiltrovany(FILE* zoznamF)
{
    int pocetCharNovyRiadok = 0;
    char ch = 0;
    char buffer[8][200];

    int i = 0;

    int	pocetZaznamov = DajPocetZaznamov(zoznamF);

    for (; ch != EOF && i < pocetZaznamov;)
    {
        int bufIdx = 0;
        int j;
        for (j = 0; j < 8; )
        {
            ch = fgetc(zoznamF);

            //if (ch == '\n' || ch == '\r')
            if (ch == '\n')
            {
                pocetCharNovyRiadok++;
                if (pocetCharNovyRiadok == 1)
                {
                    buffer[j][bufIdx] = 0;
                    bufIdx = 0;
                    j++;
                }
                if (pocetCharNovyRiadok == 2)
                {
                    pocetCharNovyRiadok = 0;
                    i++;
                    if (i >= pocetZaznamov)
                    {
                        break;
                    }
                }
            }
            else if (ch == EOF)
            {
                //printf("%s: %s\n", "datum:", buffer[j]);
                break;
            }
            else
            {
                pocetCharNovyRiadok = 0;
                buffer[j][bufIdx] = ch;
                bufIdx++;
                buffer[j][bufIdx] = 0;
            }
        }

        if (1)
        {
            printf("%s\t", buffer[6]);
            printf("%s\t", buffer[5]);
            printf("%s\t", buffer[0]);
            printf("%s\t", buffer[3]);
            printf("\n");

        }
    }
    rewind(zoznamF);
}

//==============================================================================
//
//==============================================================================
void DajObsahZaznamov(FILE* zoznamF, void** pTable, int pocetZaznamov)
{
    int pocetCharNovyRiadok = 0;
    char ch = 0;
    char buffer[200];

    char* prefix = "";
    int i = 0;
    buffer[0] = 0;

    if (pocetZaznamov == 0)
    {
        pocetZaznamov = DajPocetZaznamov(zoznamF);
    }
    for (; ch != EOF && i < pocetZaznamov;)
    {
        int bufIdx = 0;
        int j;
        for (j = 0; j < 8; )
        {
            ch = fgetc(zoznamF);

            //if (ch == '\n' || ch == '\r')
            if (ch == '\n')
            {
                pocetCharNovyRiadok++;
                if (pocetCharNovyRiadok == 1)
                {
                    switch (j)
                    {
                    case 0: prefix = "Prezenter";
                        break;
                    case 1: prefix = "rodne cislo";
                        KontrolaRodnehoCisla(buffer, i);
                        break;
                    case 2: prefix = "kod prezentacnej miestnosti";
                        KontrolaKoduMiestnosti(buffer, i);
                        break;
                    case 3: prefix = "nazov prispevku";
                        break;
                    case 4: prefix = "mena autorov";
                        break;
                    case 5: prefix = "typ prezentovania";
                        KontrolaTypuPrezentovania(buffer, i);
                        break;
                    case 6: prefix = "cas prezentovania";
                        KontrolaCasuPrezentovania(buffer, i);
                        break;
                    case 7: prefix = "datum";
                        KontrolaDatumu(buffer, i);
                        break;
                    default:
                        break;
                    }
                    if (pTable != NULL)
                    {
                        strcpy(DajRiadokZaznamu(pTable, i, j), buffer);
                    }
                    else
                    {
                        printf("%s: %s\n", prefix, buffer);
                    }
                    bufIdx = 0;
                    buffer[bufIdx] = 0;
                    j++;
                }
                if (pocetCharNovyRiadok == 2)
                {
                    pocetCharNovyRiadok = 0;
                    if (pTable == 0)
                    {
                        printf("\n");
                    }

                    i++;
                    if (i >= pocetZaznamov)
                    {
                        break;
                    }
                }
            }
            else if (ch == EOF)
            {
                if (pTable != NULL)
                {
                    strcpy(DajRiadokZaznamu(pTable, i, j), buffer);
                }
                else
                {
                    printf("%s %s\n", "datum:", buffer);
                }
                break;
            }
            else
            {
                pocetCharNovyRiadok = 0;
                buffer[bufIdx] = ch;
                if (buffer[bufIdx] == '#')
                {
                    buffer[bufIdx] = ' ';
                }
                bufIdx++;
                buffer[bufIdx] = 0;
            }
        }
    }
    if (pTable != NULL)
    {
        //PrintZaznamy(pTable, pocetZaznamov);
    }
    rewind(zoznamF);
}

//==============================================================================
//
//==============================================================================
void** prikazN(FILE* zoznamF, void** pTable, int* pocetZaznamov)
{
    *pocetZaznamov = 0;
    if (zoznamF != NULL)
    {
        *pocetZaznamov = DajPocetZaznamov(zoznamF);
    }
    else
    {
        printf("@Neotvoreny subor\n");
    }

    if (pTable != 0)
    {
        Dealokuj(pTable, *pocetZaznamov);
        pTable = 0;
    }

    if (zoznamF != NULL)
    {
        pTable = Alokuj(*pocetZaznamov);
        DajObsahZaznamov(zoznamF, pTable, *pocetZaznamov);
    }

    return pTable;
}

//==============================================================================
//
//==============================================================================
FILE* FileOpen(FILE* zoznamF, void** pTable, int pocetZaznamov)
{
    if (zoznamF == NULL)
    {
        zoznamF = fopen("konferencny_zoznam.txt", "rb");
        if (zoznamF == NULL)
        {
            printf("Neotvoreny subor\n");
        }
    }
    else
    {
        //printf("Subor uz bol otvoreny\n");
    }

    if (zoznamF != NULL)
    {
        if (pTable != NULL)
        {
            PrintZaznamy(pTable, pocetZaznamov);
        }
        else
        {
            DajObsahZaznamov(zoznamF, pTable, pocetZaznamov);
        }
    }

    return zoznamF;
}

//==============================================================================
//
//==============================================================================
FILE* prikazV(FILE* zoznamF, void** pTable, int pocetZaznamov)
{
    return FileOpen(zoznamF, pTable, pocetZaznamov);
}

//==============================================================================
//
//==============================================================================
void DajFiltrovanyDatum(int* datumMTM, void** pTable, int pocetZaznamov)
{

    int temp;
    int previous;
    int flag = 1;
    int indexCount = 0;
    int i;
    for (i = 0; i < pocetZaznamov; i++)
    {
        if (pTable[i] == NULL)
        {
            continue;
        }

        //printf("%s\t", DajRiadokZaznamu(pTable, i, 6));
        previous = atoi(DajRiadokZaznamu(pTable, i, 6));
        int j;
        for (j = 0; j < pocetZaznamov; j++)
        {

            if (datumMTM[j] != previous)
            {
                flag = 1;
            }
            else
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1)
        {
            datumMTM[indexCount] = atoi(DajRiadokZaznamu(pTable, i, 6));
            indexCount++;
        }
        else
        {
            datumMTM[indexCount] = 0;
            indexCount++;
        }

    }
    for (i = 0; i < pocetZaznamov; i++) {
        int j;
        for (j = i + 1; j < pocetZaznamov; j++) {
            if (datumMTM[i] > datumMTM[j]) {
                temp = datumMTM[i];
                datumMTM[i] = datumMTM[j];
                datumMTM[j] = temp;
            }
        }
    }
}

//==============================================================================
//
//==============================================================================
void DajObsahZaznamovPrikazO(void** pTable, char* datum, char* kodMiestnosti, int pocetZaznamov)
{
    int datumFlag = 1;
    int kodMiestnostiFlag = 1;
    int* datumMTM = malloc(sizeof(int*) * pocetZaznamov);
    int temp;

    DajFiltrovanyDatum(datumMTM, pTable, pocetZaznamov);
    datumFlag = KontrolaDatumu(datum, pocetZaznamov);
    kodMiestnostiFlag = KontrolaKoduMiestnosti(kodMiestnosti, pocetZaznamov);
    if (datumFlag == 1 && kodMiestnostiFlag == 1)
    {
        int i;
        for (i = 0; i < pocetZaznamov; i++)
        {
            if (pTable[i] == NULL)
            {
                continue;
            }
           
            int j;
            for (j = 0; j < pocetZaznamov; j++)
            {
                if (pTable[j] == NULL)
                {
                    continue;
                }
                char* pDatum = DajRiadokZaznamu(pTable, j, 7); //((char**)(pTable[7]))[i];
                char* pKodM = DajRiadokZaznamu(pTable, j, 2); //((char**)(pTable[2]))[i];
                temp = atoi(DajRiadokZaznamu(pTable, j, 6));

                if (datumMTM[i] != temp)
                {
                    continue;
                }
                if (strcmp(DajRiadokZaznamu(pTable, j, 5), "UD") != 0 && strcmp(DajRiadokZaznamu(pTable, j, 5), "UP") != 0)
                {
                    continue;
                }
                if (strcmp(datum, pDatum) != 0 || strcmp(kodMiestnosti, pKodM) != 0)
                {
                    continue;
                }
                printf("%s\t", DajRiadokZaznamu(pTable, j, 6));
                printf("%s\t", DajRiadokZaznamu(pTable, j, 5));
                printf("%s\t", DajRiadokZaznamu(pTable, j, 0));
                printf("%s\t", DajRiadokZaznamu(pTable, j, 3));
                printf("\n");
            }
        }
        printf("\n");
        for (i = 0; i < pocetZaznamov; i++)
        {
            if (pTable[i] == NULL)
            {
                continue;
            }
            int j;
            for (j = 0; j < pocetZaznamov; j++)
            {
                if (pTable[j] == NULL)
                {
                    continue;
                }
                char* pDatum = DajRiadokZaznamu(pTable, j, 7); //((char**)(pTable[7]))[i];
                char* pKodM = DajRiadokZaznamu(pTable, j, 2); //((char**)(pTable[2]))[i];
                temp = atoi(DajRiadokZaznamu(pTable, j, 6));

                if (datumMTM[i] != temp)
                {
                    continue;
                }
                if (strcmp(DajRiadokZaznamu(pTable, j, 5), "PP") != 0 && strcmp(DajRiadokZaznamu(pTable, j, 5), "PD") != 0)
                {
                    continue;
                }
                if (strcmp(datum, pDatum) != 0 || strcmp(kodMiestnosti, pKodM) != 0)
                {
                    continue;
                }
                printf("%s\t", DajRiadokZaznamu(pTable, j, 6));
                printf("%s\t", DajRiadokZaznamu(pTable, j, 5));
                printf("%s\t", DajRiadokZaznamu(pTable, j, 0));
                printf("%s\t", DajRiadokZaznamu(pTable, j, 3));
                printf("\n");
            }

        }
    }
}

//==============================================================================
//
//==============================================================================
void DajObsahZaznamovPrikazS(void** pTable, char* datum, char* typPrezentovania, int pocetZaznamov)
{
    int datumFlag = 1;
    int typPrezentovaniaFlag = 1;
    int prazdnyZaznamFlag = 0;

    datumFlag = KontrolaDatumu(datum, pocetZaznamov);
    typPrezentovaniaFlag = KontrolaTypuPrezentovania(typPrezentovania, pocetZaznamov);
    if (datumFlag == 1 && typPrezentovaniaFlag == 1)
    {
        //UD,UP 
        int i;
        for (i = 0; i < pocetZaznamov; i++)
        {
            if (pTable[i] == NULL)
            {
                continue;
            }
            char* pDatum = DajRiadokZaznamu(pTable, i, 7); //((char**)(pTable[7]))[i];
            char* pTypP = DajRiadokZaznamu(pTable, i, 5); //((char**)(pTable[2]))[i];
            if (strcmp(datum, pDatum) != 0 || strcmp(typPrezentovania, pTypP) != 0)
            {
                continue;
            }
            printf("%s\t", DajRiadokZaznamu(pTable, i, 6));
            printf("%s\t", DajRiadokZaznamu(pTable, i, 0));
            printf("%s\t", DajRiadokZaznamu(pTable, i, 3));
            printf("\n");
            prazdnyZaznamFlag = 1;
        }
    }
    if (prazdnyZaznamFlag == 0)
    {
        printf("Pre dany vstup neexistuju zaznamy.");
    }
}

//==============================================================================
//
//==============================================================================
void prikazO(FILE* zoznamF, void** pTable, int pocetZaznamov)
{
    char iDatum[20];
    char iKodMiestnosti[20];
    if (zoznamF != NULL)
    {
        if (pTable != NULL)
        {
            if (scanf("%s %s", iDatum, iKodMiestnosti) != 0)
            {
                DajObsahZaznamovPrikazO(pTable, iDatum, iKodMiestnosti, pocetZaznamov);
            }
        }
        else
        {
            DajObsahZaznamovFiltrovany(zoznamF);
            //printf("@Nenacitany prikaz N\n");
        }
    }
    else
    {
        printf("@Neotvoreny subor\n");
    }
}
//==============================================================================
//
//==============================================================================
void prikazS(FILE* zoznamF, void** pTable, int pocetZaznamov)
{
    char iDatum[20];
    char iTypPrezentovania[20];
    if (zoznamF != NULL)
    {
        if (pTable != NULL)
        {
            if (scanf("%s %s", iDatum, iTypPrezentovania) != 0)
            {
                DajObsahZaznamovPrikazS(pTable, iDatum, iTypPrezentovania, pocetZaznamov);
            }
        }
        else
        {
            printf("@Polia nie su vytvorene\n");
        }
    }
    else
    {
        printf("@Neotvoreny subor\n");
    }
}

//==============================================================================
//
//==============================================================================
void DajPocetVymazanychZaznamovPrikazZ(void** pTable, int pocetZaznamov, char* rodneCislo)
{
    int pocetRiadkovZaznamu = 8;
    int vymazanyZaznamCount = 0;
    int i;
    for (i = 0; i < pocetZaznamov; i++)
    {
        if (pTable[i] == NULL) continue;
        char* pRodneCislo = DajRiadokZaznamu(pTable, i, 1);
        if (strcmp(rodneCislo, pRodneCislo) == 0)
        {
            //char * p = DajRiadokZaznamu(pTable, i, 0);
            //*p = NULL;
            pTable[i] = NULL;
            vymazanyZaznamCount++;
        }
    }
    printf("Vymazalo sa : %d zaznamov !\n", vymazanyZaznamCount);

    FILE* testFileDeleted = fopen("konferencny_zoznam_vymazany.txt", "w");
    for (i = 0; i < pocetZaznamov; i++)
    {
        if (pTable[i] == NULL) continue;
        int j;
        for (j = 0; j < pocetRiadkovZaznamu; j++)
        {
            fputs(DajRiadokZaznamu(pTable, i, j), testFileDeleted);
            if (j + 1 == pocetRiadkovZaznamu && i + 1 == pocetZaznamov)
            {
                break;
            }
            fputs("\n", testFileDeleted);
        }
        if (i + 1 == pocetZaznamov)
        {
            break;
        }
        fputs("\n", testFileDeleted);
    }
    fclose(testFileDeleted);

}

//==============================================================================
//
//==============================================================================
void prikazZ(void** pTable, int pocetZaznamov)
{
    char iRodneCislo[20];
    if (pTable != NULL)
    {
        if (scanf("%s", iRodneCislo) != 0)
        {
            DajPocetVymazanychZaznamovPrikazZ(pTable, pocetZaznamov, iRodneCislo);
        }
    }
    else
    {
        printf("@Polia nie su vytvorene\n");
    }
    //PrintZaznamy(pTable, pocetZaznamov);
}


//==============================================================================
//
//==============================================================================
void DajPocetMuzovZien(void** pTable, int pocetZaznamov, int** hodnota, int poh1, int poh2)
{
    int aktualnyRok = 2021;
    int storocie21 = 2000;
    int storocie20 = 1900;
    int vek = 0;
    int pohlavie = 0;
    int vekI = 0;
    int typPrezentovaniaJ = 0;
    char vekRodneCislo[3];
    char pohlavieRodneCislo[2];
    int i;
    for (i = 0; i < pocetZaznamov; i++)
    {
        if (pTable[i] == NULL)
        {
            continue;
        }
        char* pRodneCislo = DajRiadokZaznamu(pTable, i, 1); //((char**)(pTable[7]))[i];
        char* pTypP = DajRiadokZaznamu(pTable, i, 5); //((char**)(pTable[2]))[i];


        vekRodneCislo[2] = 0;
        pohlavieRodneCislo[1] = 0;
        memcpy(vekRodneCislo, pRodneCislo, 2);
        memcpy(pohlavieRodneCislo, pRodneCislo + 2, 1);
        vek = atoi(vekRodneCislo);
        pohlavie = atoi(pohlavieRodneCislo);
        if (vek >= 0 && vek <= 21)
        {
            vek = aktualnyRok - (vek + storocie21);
        }
        if (vek >= 22 && vek <= 99)
        {
            vek = aktualnyRok - (vek + storocie20);
        }
        if (pohlavie != poh1 && pohlavie != poh2)
        {
            continue;
        }

        if (vek >= 0 && vek <= 9)
        {
            vekI = 0;
        }
        else
        {
            vekI = vek / 10;
        }

        if (strcmp(pTypP, "UP") == 0)
            typPrezentovaniaJ = 0;
        if (strcmp(pTypP, "UD") == 0)
            typPrezentovaniaJ = 1;
        if (strcmp(pTypP, "PP") == 0)
            typPrezentovaniaJ = 2;
        if (strcmp(pTypP, "PD") == 0)
            typPrezentovaniaJ = 3;
        DajRiadokZaznamuPrikazH(hodnota, vekI, typPrezentovaniaJ);
    }
}

//==============================================================================
//
//==============================================================================
void DajHistogramPrikazH(void** pTable, int pocetZaznamov)
{

    int pocetVekovychKategorii = 10;
    int typPrezentovaniaKategorie = 4;
    //char* vek = malloc(sizeof(char) * pocetVekovychKategorii);
    //char** typPrezentovaniaCount = malloc(sizeof(char*) * pocetVekovychKategorii);
    char* vek[10] = { "0-9:", "10-19:", "20-29:","30-39:", "40-49:", "50-59:", "60-69:","70-79:", "80-89:", "90-99:" };

    int** pHodnota;
    pHodnota = malloc(sizeof(int**) * pocetVekovychKategorii);
    int i;
    for (i = 0; i < pocetVekovychKategorii; i++)
    {
        int** pRow;
        pRow = malloc(sizeof(int*) * pocetVekovychKategorii);
        AlokujPametForIntArray(pRow, typPrezentovaniaKategorie, pocetVekovychKategorii);
        pHodnota[i] = (int*)pRow;
    }

    //MUZI
    DajPocetMuzovZien(pTable, pocetZaznamov, pHodnota, 0, 1);
    printf("\nMuzi\tUP\tUD\tPP\tPD\n");
    for (i = 0; i < 10; i++)
    {
        printf("%s\t", vek[i]);
        size_t j;
        for (j = 0; j < 4; j++)
        {
            printf("%d\t", DajHodnotuInt(pHodnota, i, j));
        }
        printf("\n");
    }
    if (pHodnota != 0)
    {
        Dealokuj((void**)pHodnota, pocetVekovychKategorii);
        pHodnota = 0;
    }
    pHodnota = malloc(sizeof(int**) * pocetVekovychKategorii);
    for (i = 0; i < pocetVekovychKategorii; i++)
    {
        int** pRow;
        pRow = malloc(sizeof(int*) * pocetVekovychKategorii);
        AlokujPametForIntArray(pRow, typPrezentovaniaKategorie, pocetVekovychKategorii);
        pHodnota[i] = (int*)pRow;
    }
    //ZENY
    DajPocetMuzovZien(pTable, pocetZaznamov, pHodnota, 5, 6);
    printf("\nZENY\tUP\tUD\tPP\tPD\n");
    for (i = 0; i < 10; i++)
    {
        printf("%s\t", vek[i]);
        size_t j;
        for (j = 0; j < 4; j++)
        {
            printf("%d\t", DajHodnotuInt(pHodnota, i, j));
        }
        printf("\n");
    }



    if (pHodnota != 0)
    {
        Dealokuj((void**)pHodnota, pocetVekovychKategorii);
        pHodnota = 0;
    }
}

//==============================================================================
//
//==============================================================================
void prikazH(void** pTable, int pocetZaznamov)
{
    if (pTable != NULL)
    {
        DajHistogramPrikazH(pTable, pocetZaznamov);
    }
    else
    {
        printf("@Polia nie su vytvorene\n");
    }
}

//==============================================================================
//
//==============================================================================
void PrepisDat(void** pTable, int poradoveCislo, char* kodMiestnosti, char* typPrezentovania, char* casPrezentovania, char* datum, char* rodneCislo, int pocetZaznamov)
{
    int pCislo = 0;
    int pocetRiadkovZaznamu = 8;
    int i;
    for (i = 0; i < pocetZaznamov; i++)
    {
        char* pRodneCislo = DajRiadokZaznamu(pTable, i, 1); //((char**)(pTable[7]))[i];
        if (strcmp(rodneCislo, pRodneCislo) != 0)
        {
            continue;
        }
        pCislo++;
        if (pCislo == poradoveCislo)
        {

            strcpy(DajRiadokZaznamu(pTable, i, 2), kodMiestnosti);
            strcpy(DajRiadokZaznamu(pTable, i, 5), typPrezentovania);
            strcpy(DajRiadokZaznamu(pTable, i, 6), casPrezentovania);
            strcpy(DajRiadokZaznamu(pTable, i, 7), datum);
        }
    }

    FILE* testFile = fopen("konferencny_zoznam_prepisany.txt", "w");
    for (i = 0; i < pocetZaznamov; i++)
    {
        int j;
        for (j = 0; j < pocetRiadkovZaznamu; j++)
        {
            fputs(DajRiadokZaznamu(pTable, i, j), testFile);
            if (j + 1 == pocetRiadkovZaznamu && i + 1 == pocetZaznamov)
            {
                break;
            }
            fputs("\n", testFile);
        }
        if (i + 1 == pocetZaznamov)
        {
            break;
        }
        fputs("\n", testFile);
    }
    fclose(testFile);
}

//==============================================================================
//
//==============================================================================
void DajObsahZaznamovPrikazP(void** pTable, char* poradoveCislo, char* rodneCislo, int pocetZaznamov)
{
  
    int pCislo = 1;
    int i;
    for (i = 0; i < pocetZaznamov; i++)
    {
        if (pTable[i] == NULL)
        {
            continue;
        }
        char* pRodneCislo = DajRiadokZaznamu(pTable, i, 1); //((char**)(pTable[7]))[i];
        if (strcmp(rodneCislo, pRodneCislo) != 0)
        {
            continue;
        }
        poradoveCislo[pCislo - 1] = pCislo;
        printf("%d\t", poradoveCislo[pCislo - 1]);
        printf("%s\t", DajRiadokZaznamu(pTable, i, 0));
        printf("%s\t", DajRiadokZaznamu(pTable, i, 3));
        printf("\n");
        pCislo++;
        
    }
  
}

//==============================================================================
//
//==============================================================================
void prikazP(void** pTable, int pocetZaznamov)
{
    char iRodneCislo[20];
    unsigned int iPoradoveCislo;
    char* iPoradCislo = malloc(sizeof(char) * pocetZaznamov);
    char iKodMiestnosti[20];
    char iTypPrezentovania[20];
    char iCasPrezentovania[20];
    char iDatum[20];
    int k0Flag = 1;
    int k1Flag = 1;
    int k2Flag = 1;
    int k3Flag = 1;
    int k4Flag = 1;

    //set null for all indexes in iPoradCislo
    int i;
    int flag = 1;
    for (i = 0; i < pocetZaznamov; i++)
    {
        if (pTable[i] == NULL)
        {
            flag = 0;
        }
        iPoradCislo[i] = 0;
    }

    if (pTable != NULL)
    {
        if (scanf("%s", iRodneCislo) != 0)
        {
            DajObsahZaznamovPrikazP(pTable, iPoradCislo, iRodneCislo, pocetZaznamov);



            while (flag == 1)
            {
                
                if (scanf("%d %s %s %s %s", &iPoradoveCislo, iKodMiestnosti, iTypPrezentovania, iCasPrezentovania, iDatum) != 0)
                {

                    if (iPoradoveCislo > strlen(iPoradCislo))
                    {
                        k0Flag = 0;
                    }
                    else
                    {
                        k0Flag = 1;
                    }
                    k1Flag = KontrolaKoduMiestnosti(iKodMiestnosti, -2);
                    k2Flag = KontrolaTypuPrezentovania(iTypPrezentovania, -2);
                    k3Flag = KontrolaCasuPrezentovania(iCasPrezentovania, -2);
                    k4Flag = KontrolaDatumu(iDatum, -2);
                    if (k0Flag == 1 && k1Flag == 1 && k2Flag == 1 && k3Flag == 1 && k4Flag == 1)
                    {
                        PrepisDat(pTable, iPoradoveCislo, iKodMiestnosti, iTypPrezentovania, iCasPrezentovania, iDatum, iRodneCislo, pocetZaznamov);
                        printf("Aktualizacia udajov prebehla v poriadku\n");
                        break;

                    }
                    else
                    {
                        printf("Zadane udaje nie su korektne, zadaj novy retazec: ");
                    }
                }

            }
            //if (flag == 0)
            //{
            //    printf("Zadane udaje neexistuju, zadaj novy prikaz:\n ");
            //}
        }

    }
    else
    {

        printf("@Polia nie su vytvorene\n");

    }
}


//==============================================================================
// main function
//==============================================================================
int main()
{
    int pocetZaznamov = 0;
    void** pTable = 0;

    FILE* zoznamF = NULL;

    char prikazy;
    int inf = 1;

    while (inf == 1)
    {
        if (scanf("%c", &prikazy) != 0)
        {
            switch (prikazy)
            {
            case 'v': zoznamF = prikazV(zoznamF, pTable, pocetZaznamov);
                break;
            case 'n': pTable = prikazN(zoznamF, pTable, &pocetZaznamov);
                break;
            case 'o': prikazO(zoznamF, pTable, pocetZaznamov);
                break;
            case 's': prikazS(zoznamF, pTable, pocetZaznamov);
                break;
            case 'z': prikazZ(pTable, pocetZaznamov);
                break;
            case 'h': prikazH(pTable, pocetZaznamov);
                break;
            case 'p': prikazP(pTable, pocetZaznamov);
                break;
            case 'k': inf = 0;
                break;
            default:
                break;
            }
        }

    }

    //==============================================================================

    if (pTable != 0) //NULL
    {
        Dealokuj(pTable, pocetZaznamov);
        pTable = 0; //NULL
    }

    if (zoznamF != NULL)
    {
        fclose(zoznamF);
    }

    //printf("Koniec Programu.\n");
    return 0;
}

//==============================================================================
//
//==============================================================================
void PrintZaznamy(void** pTable, int pocetZaznamov)
{
    int i;
    for (i = 0; i < pocetZaznamov; i++)
    {
        //char* p = DajRiadokZaznamu(pTable, i, 0);
        if (pTable[i] == NULL) continue;
        printf("Prezenter: %s\n\r", DajRiadokZaznamu(pTable, i, 0)); // ((char**)(pTable[0]))[i]
        printf("rodne cislo: %s\n\r", DajRiadokZaznamu(pTable, i, 1));
        printf("kod prezentacnej miestnosti: %s\n\r", DajRiadokZaznamu(pTable, i, 2));
        printf("nazov prispevku: %s\n\r", DajRiadokZaznamu(pTable, i, 3));
        printf("mena autorov: %s\n\r", DajRiadokZaznamu(pTable, i, 4));
        printf("typ prezentovania: %s\n\r", DajRiadokZaznamu(pTable, i, 5));
        printf("cas prezentovania: %s\n\r", DajRiadokZaznamu(pTable, i, 6));
        printf("datum: %s\n\r", DajRiadokZaznamu(pTable, i, 7));

        printf("\n\r");

    }

}


//==============================================================================
//
//==============================================================================
void** Alokuj(int pocetZaznamov)
{
    int pocetRiadkovZaznamu = 8; // 0-7

    void** pTable;
    pTable = malloc(sizeof(char**) * pocetZaznamov);
    int riadkyZoznamuMaxSize[] = { 50 + 1, 10 + 1, 3 + 1, 150 + 1, 200 + 1, 2 + 1, 4 + 1, 8 + 1 };
    int i;
    for (i = 0; i < pocetZaznamov; i++)
    {
        char** pZaznam;
        pZaznam = malloc(sizeof(char*) * pocetRiadkovZaznamu);
        AlokujPamet(pZaznam, riadkyZoznamuMaxSize, pocetRiadkovZaznamu);
        pTable[i] = pZaznam;
    }

    return pTable;
}

//==============================================================================
//
//==============================================================================
void Dealokuj(void** pTable, int pocetZaznamov)
{
    if (pTable != 0)
    {
        int i;
        for (i = 0; i < pocetZaznamov; i++)
        {
            DealokujPamet(/*zaznam*/ pTable[i], 8);
        }
        free(pTable);
    }
}

//==============================================================================
//
//==============================================================================
void AlokujPametForIntArray(int** pInt, int velkost, int pocetRiadkovZaznamu)
{
    int i;
    for (i = 0; i < pocetRiadkovZaznamu; i++)
    {
        pInt[i] = malloc(sizeof(char) * velkost);
        pInt[i][0] = 0;
    }
}

//==============================================================================
//
//==============================================================================
void AlokujPamet(char** pRetazec, int* velkost, int pocetRiadkovZaznamu)
{
    int i;
    for (i = 0; i < pocetRiadkovZaznamu; i++)
    {
        pRetazec[i] = malloc(sizeof(char) * velkost[i]);
        //pRetazec[i][0] = 'a' + i;
        //pRetazec[i][velkost[i] - 2] = 'A' + i;
        //pRetazec[i][velkost[i] - 1] = 0;
    }
}


//==============================================================================
//
//==============================================================================
void DealokujPamet(char** pRetazec, int pocetRiadkov)
{
    int i;
    for (i = 0; i < pocetRiadkov; i++)
    {
        if (pRetazec != 0)
        {
            free(pRetazec[i]);
        }
    }
}

//==============================================================================
// end of file
//==============================================================================
