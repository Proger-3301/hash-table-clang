#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#define RAND_MULTIPLIER 3183517231
#define RAND_INCREMENT 12345
#define RAND_MODULUS 2147483648

#define ht_hashf(htype, type1) \
unsigned long int htype##_hashf(type1 rand_seed){ \
    return (RAND_MULTIPLIER * rand_seed + RAND_INCREMENT) % RAND_MODULUS; \
}

#define node(htype, type1, type2) \
    struct htype##_node { \
        type1 key;\
        type2 val;\
        struct htype##_node *next; \
    }

#define hashtable(htype) \
    struct { \
        htype##_node **arr; \
        int size; \
        int count; \
    }

#define ht_create(htype, type1, type2) \
htype *htype##_create(int size){ \
    htype *ht = (htype *) malloc(sizeof(htype)); \
    ht->arr = (htype##_node**)malloc(sizeof(htype##_node*) * size); \
    ht->size = size;\
    ht->count = 0; \
    for(int i = 0; i < ht->size; i++){\
        ht->arr[i] = NULL;\
    }\
    return ht;\
}

#define ht_add(htype, type1, type2) \
void htype##_add(htype *ht, type1 key, type2 val){ \
    if(++ht->count > ht->size * 2){ \
        htype##_increaseCap(ht); \
        htype##_add(ht, key, val); \
        return; \
    }\
    unsigned long int k = htype##_hashf(key) % ht->size; \
    htype##_node *a = (htype##_node*)malloc(sizeof(htype##_node)); \
    a->key = key; \
    a->val = val; \
    htype##_node *cur = ht->arr[k]; \
    if(cur == NULL) ht->arr[k] = a; \
    else { while(1) { \
        if(cur->key == key){ cur->val = val; free(a); break; } \
        if(cur->next == NULL){ cur->next = a; break; } \
        cur = cur->next; \
    } } \
}

#define ht_increaseCap(htype) \
void htype##_increaseCap(htype *ht){ \
    htype *nht = htype##_create(ht->size * 3); \
    for(int i = 0; i < ht->size; i++){ \
        htype##_node *cur = ht->arr[i]; \
        while(cur != NULL){ \
            htype##_add(nht, cur->key, cur->val); \
            cur = cur->next; \
        }\
    } \
    free(ht->arr); \
    *ht = *nht; \
}


#define ht_get(htype, type1, type2) \
type2 htype##_get(htype *ht, type1 key) { \
    unsigned long int k = htype##_hashf(key) % ht->size; \
    htype##_node *cur = ht->arr[k]; \
    while(cur != NULL){ \
        if(cur->key == key) return cur->val;\
        cur = cur->next; \
    }\
    return (type2) NULL; \
}

#define ht_remove(htype, type1, type2) \
void htype##_remove(htype *ht, type1 key){ \
    unsigned long int k = htype##_hashf(key) % ht->size; \
    htype##_node *cur = ht->arr[k]; \
    htype##_node *prev = NULL; \
    while(cur != NULL){ \
        if(cur->key == key){ \
            if(prev != NULL) prev->next = cur->next; \
            else ht->arr[k] = NULL; \
            free(cur); \
        }\
        prev = cur; \
        cur = cur->next; \
    }\
}

#define init_hash_table(htype, type1, type2) \
    typedef node(htype, type1, type2) htype##_node; \
    typedef hashtable(htype) htype; \
    ht_create(htype, type1, type2) \
    ht_hashf(htype, type1) \
    ht_add(htype, type1, type2) \
    ht_increaseCap(htype) \
    ht_get(htype, type1, type2) \
    ht_remove(htype, type1, type2)

unsigned long int strh(char* str) {
    unsigned long int i = 0;
    for (int j = 0; str[j]; j++)
        i += str[j] * (j + 1);
    return (RAND_MULTIPLIER * i + RAND_INCREMENT) % RAND_MODULUS;
}

#endif
