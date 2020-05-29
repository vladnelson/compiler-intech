#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexer.h"
#include "buffer.h"

bool isalphanum(char chr)
{
    if ('a' <= chr && chr <= 'z')
        return true;
    if ('A' <= chr && chr <= 'Z')
        return true;
    if (0 <= chr && chr <= 9)
        return true;
    else
        return false;
}

bool isnumber(char chr)
{
    if (0 <= chr && chr <= 9)
        return true;
    if (chr == '-')
        return true;

    return false;
}

bool isop(char chr)
{

    return false;
}

char *lexer_getalphanum(buffer_t *buffer)
{
    // boucle qui s'arrête lorsque l'on tombe sur un caractère
    // qui ne correspond pas à isalphanum()
    /*
    tant que (buf_getchar(buffer) correspond à un caractère autorisé
      par isalphanum(), alors
        continuer
      sinon s'arrêter
    créer une chaîne de caractères contenant les caractères qu'on
       vient de lire
    et retourner cette chaine
  */
    char save[LEXEM_SIZE] = "";
    size_t count = 0;
    buf_lock(buffer);
    do
    {
        save[count] = buf_getchar(buffer);
            printf("%d \n", save[count]);
        count++;
    } while (count < LEXEM_SIZE && isalphanum(save[count - 1]));

    buf_rollback(buffer, 1);
    buf_unlock(buffer);

    if (count == LEXEM_SIZE)
    {
        printf("Error parsing identifier: identifier too long!. exiting\n");
        exit(1); // arrêt brutal du programme
    }

    char *out = malloc(sizeof(char) * count);
    save[count - 1] = '\0';
    strncpy(out, save, count);

    return out;
}

char *lexer_getalpha(buffer_t *buffer)
{

    char save[LEXEM_SIZE] = "";
    size_t count = 0;
    buf_lock(buffer);
    do
    {
        save[count] = buf_getchar(buffer);
        printf("%d \n", save[count]);
        count++;
    } while (count < LEXEM_SIZE && (isalphanum(save[count - 1] || isnumber(save[count - 1]))));

    buf_rollback(buffer, 1);
    buf_unlock(buffer);

    if (count == LEXEM_SIZE)
    {
        printf("Error parsing identifier: identifier too long!. exiting\n");
        exit(1); // arrêt brutal du programme
    }

    char *out = malloc(sizeof(char) * count);
    save[count - 1] = '\0';
    strncpy(out, save, count);

    return out;
}

char *lexer_getalphanum_rollback(buffer_t *buffer)
{
    // boucle qui s'arrête lorsque l'on tombe sur un caractère
    // qui ne correspond pas à isalphanum()
    /*
    tant que (buf_getchar(buffer) correspond à un caractère autorisé
      par isalphanum(), alors
        continuer
      sinon s'arrêter
    créer une chaîne de caractères contenant les caractères qu'on
       vient de lire
    et retourner cette chaine
  */
    char save[LEXEM_SIZE] = "";
    size_t count = 0;
    buf_lock(buffer);
    do
    {
        save[count] = buf_getchar(buffer);
        count++;
    } while (count < LEXEM_SIZE && isalphanum(save[count - 1]));

    buf_rollback(buffer, count);
    buf_unlock(buffer);

    if (count == LEXEM_SIZE)
    {
        printf("Error parsing identifier: identifier too long!. exiting\n");
        exit(1); // arrêt brutal du programme
    }

    char *out = malloc(sizeof(char) * count);
    save[count - 1] = '\0';
    strncpy(out, save, count);

    return out;
}

long lexer_getnumber(buffer_t *buffer)
{
    char save[LEXEM_SIZE] = "";
    size_t count = 0;
    buf_lock(buffer);
    do
    {
        save[count] = buf_getchar(buffer);
        count++;
    } while (count < LEXEM_SIZE && isnumber(save[count - 1]));

    buf_rollback(buffer, 1);
    buf_unlock(buffer);

    if (count == LEXEM_SIZE)
    {
        printf("Error parsing identifier: identifier too long!. exiting\n");
        exit(1); // arrêt brutal du programme
    }

    save[count - 1] = '\0';
    long out = strtol(save, NULL, 10);

    return out;
}