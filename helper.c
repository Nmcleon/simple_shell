#include "main.h"

/**
 * string_length - returns the length of a string
 * @s: pointer to the string
 * Return: integer length of the string
 */
int string_length(char *s)
{
    int i = 0;

    while (s[i] != '\0')
        i++;
    return i;
}

/**
 * string_compare - compares two strings.
 * @scp1: pointer to the first string
 * @scp2: pointer to the second string
 * Return: 0 if the strings are equal, a non-zero value otherwise.
 */
int string_compare(char *scp1, char *scp2)
{
    while ((*scp1 != '\0' && *scp2 != '\0') && *scp1 == *scp2)
    {
        scp1++;
        scp2++;
    }

    if (*scp1 == *scp2)
        return 0;
    else
        return *scp1 - *scp2;
}

/**
 * string_duplicate - duplicates the source string
 * @sd: pointer to the source string to be duplicated
 * Return: duplicated string
 */
char *string_duplicate(char *sd)
{
    int size;
    static char *duplicate;
    char *duplicate_offset;

    size = string_length(sd);
    duplicate = malloc(sizeof(char) * (size + 1));
    if (duplicate == NULL)
        return NULL;
    duplicate_offset = duplicate;
    while (*sd)
    {
        *duplicate_offset = *sd;
        duplicate_offset++;
        sd++;
    }
    *duplicate_offset = '\0';
    return duplicate;
}

/**
 * string_concatenate - concatenates the source string to the destination string
 * @scn: pointer to the destination string
 * @sd: pointer to the source string
 * Return: pointer to the concatenated string
 */
char *string_concatenate(char *scn, char *sd)
{
    char *ptr = scn + string_length(scn);

    while (*sd != '\0')
        *ptr++ = *sd++;
    *ptr = '\0';
    return scn;
}