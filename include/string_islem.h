#ifndef STRING_ISLEM_H
#define STRING_ISLEM_H

typedef struct {
    char *key;
    char *value;
} Hash;


char* virgul_sil(char *kelime);

char* key_tirnak_sil(char* key);

char* value_tirnak_sil(char* value);

Hash* newHash(char* key, char* value);

Hash* yazdir(char *key, char* value);


#endif