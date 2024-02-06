/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TEST_TOREMOVE.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 00:41:05 by craimond          #+#    #+#             */
/*   Updated: 2024/02/06 01:03:55 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

//per testare le collisioni della hash table con i valori delle variabili d'ambiente default

uint8_t hash(char *str)
{
	uint32_t	hash_value; //tanto va in overfow o underflow
	uint32_t	i;

	hash_value = 5381;
	i = 0;
	while (str[i])
	{
		hash_value *= 33;
		hash_value += str[i++];
        hash_value++;
	}
	return (hash_value % 255);
}

int main(int argc, char **argv, char **envp)
{
    char *i;
    int array[255];

    memset(array, 0, sizeof(array));
    while (*envp)
    {
        i = strchr(*envp, '=');
        *i = '\0';
        array[hash(*envp)] += 1;
        envp++;
    }
    for (int j = 0; j < 255; j++)
    {
        if (array[j] > 1)
            printf("Collisione da %d elem\n", array[j]);
    }
    return (0);
}