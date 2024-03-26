#include <stdio.h>
#include "hashtable.h"

//initializing hash tables
init_hash_table(iiht, int, int)
init_hash_table(lsht, unsigned long int, char*)

int main()
{
    iiht *ht = iiht_create(3);
    system("clear");
    for(int i = 0; i < 10; i++){
        iiht_add(ht, i, i * i + i);
    }
    for(int i = 0; i < 10; i++){
        printf("%i ", iiht_get(ht, i));
    }
    lsht *nht = lsht_create(5);
    //strh() returns a hash of string value
    lsht_add(nht, strh("Hello"), "World!");
    lsht_add(nht, strh("How"), "are you");
    printf("\nHello %s\n", lsht_get(nht, strh("Hello")));
    printf("How %s\n", lsht_get(nht, strh("How")));
    return 0;
}
