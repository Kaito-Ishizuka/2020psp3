#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define DEBUG

#define ALPHABET_LEN    255

char StrOriginal[] = "On a dark deseart highway, cool wind in my hair.";
char StrKey[] = "wind";

char* ForceSearch(char text[], char key[])
{
    //  ここを実装する
size_t text_len = strlen(text);
size_t key_len = strlen(key);

if (text_len < key_len)
{
    return NULL;
}
for (size_t text_i = 0, E = text_len - key_len; text_i <= E; ++text_i)
{
    bool match = true;
     for (size_t key_i = 0; key_i < key_len; ++key_i) {
            if (text[text_i + key_i] != key[key_i]) {
                match = false;
                break;
            }
        }

        if (match) {
            return text + text_i;
        }
    }
    return NULL;
}


char* BMSearch(char text[], char key[])
{
    //  ここを実装する
    size_t skip_tbl[ALPHABET_LEN];
    size_t key_len = strlen(key);
    size_t text_len = strlen(text);
    for (size_t i = 0; i < ALPHABET_LEN; ++i) {
        skip_tbl[i] = key_len;
    }
    for (size_t i = 0; i < key_len; ++i) {
        skip_tbl[(size_t)key[i]] = key_len - 1 - i; 
    }

    size_t pos = key_len - 1;
    while (pos < text_len) {
        for (size_t i = 0; i < key_len; ++i) {
            size_t key_pos = key_len - 1 - i;
            if (key[key_pos] != text[pos - i]) {
                size_t new_pos = pos - i + skip_tbl[(size_t)text[pos]];
                if (new_pos <= pos) {
                    new_pos = pos + 1;
                }
                pos = new_pos;
                break;
            }

            if (key_pos == 0) {
                return text + pos - i;
            }
        }
    }

    return NULL;
}

int main(void)
{
    char*   str;
    str = ForceSearch(StrOriginal, StrKey);
    printf("Force Search. Find keyword at:%s\n", str);

    str = BMSearch(StrOriginal, StrKey);
    printf("BM Search. Find keyword at:%s\n", str);

    return 0;
}