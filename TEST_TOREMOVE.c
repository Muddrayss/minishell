/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TEST_TOREMOVE.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 00:41:05 by craimond          #+#    #+#             */
/*   Updated: 2024/02/06 11:45:27 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

//per testare le collisioni della hash table con i valori delle variabili d'ambiente default

uint8_t hash(char *str)
{
	uint32_t	hash_value; //tanto va in overfow o underflow

	hash_value = 5381;
	while (*str)
	{
		hash_value *= 33;
		hash_value = ((hash_value << 5) + hash_value) + *str++;
	}
	return (hash_value % 255);
}

int main(int argc, char **argv, char **envp)
{
    char *i;
    int array[255];
    int n_collisions = 0;
    char **start;

    start = envp;
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
        if (start[j] == NULL)
            break;
        printf("env_var = %s, pos = %d\n", start[j], hash(start[j]));
        if (array[j] > 1)
            n_collisions++;
    }
    printf("n of buckets with collisions = %d\n", n_collisions);
    return (0);
}