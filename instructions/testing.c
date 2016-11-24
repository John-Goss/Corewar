#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define IND_SIZE            2
#define REG_SIZE            4
#define DIR_SIZE            REG_SIZE



unsigned int                 trans_two_bytes(char *transfer_bytes)
{
    unsigned int value;
    int decal; 
    int i;

    i = 0;//index counter for the loop
    decal = 24;
    while (i < IND_SIZE && transfer_bytes[i] != '\0')
    {
        value |= (transfer_bytes[i] << decal);
        decal = decal - 8;
        i++;
    }
    return (value);

unsigned int                 trans_four_bytes(char *transfer_bytes)
{
    unsigned int value;
    int decal; 
    int i;

    i = 0;//index counter for the loop
    decal = 24;
    while (i < DIR_SIZE && transfer_bytes[i] != '\0')
    {
        value |= (transfer_bytes[i] << decal);
        decal = decal - 8;
        i++;
    }
    return (value);
}

int                main(int argc, char **argv)
{
	unsigned int   four_bytes;
    char *transfer_bytes;

    four_bytes = 0;
	if (argc != 2)
		return (0);

	transfer_bytes = argv[1];
    four_bytes = trans_four_bytes(transfer_bytes);
//    printf("\n->\t%d\n", four_bytes);

	return (0);
}
//1094795585

//This file is just for testing
