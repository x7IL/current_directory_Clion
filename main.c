#include <stdlib.h>
#include <stdio.h>

extern char *getwd ();

int strlen(char * tab){                                 //str len compte la longueur du mot ou phrase
    int a = 0;
    for(int i = 0; tab[i] !='\0';i++){
        a++;
    }
    return a;
}

void * strcpy(void *dest, const void *src, size_t len){                //str copy du mot ou phrase
    char *d = dest;
    const char *s = src;
    while (len--)
        *d++ = *s++;
    return dest;
}

char * current_direct(char *buf, size_t len){
    char lepath[1000];
    char *result;

    result = getwd(lepath);
    if(result){
        if (strlen (lepath) >= len) {
            return 0;
        }
        if(!buf){
            buf = malloc(sizeof(char)*len);
            if(!buf) {
                return 0;
            }
        }
        strcpy(buf, lepath, strlen(lepath) + 1);
    }
    return buf;
}

int main() {
    char cwd[256];
    current_direct(cwd, sizeof(cwd));
    printf("directoire courrant: %s\n", cwd);
    /*if (current_direct(cwd, sizeof(cwd)) == NULL)
        perror("getcwd() error");
    else
        printf("directoire courrant: %s\n", cwd);*/
    return 0;
}


