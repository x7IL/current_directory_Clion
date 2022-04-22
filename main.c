#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

extern char *getwd ();

int mon_len(char *b){
    int a = 0;
    for(int i = 0 ; b[i]!='\0';i++){
        a++;
    }
    return a;
}


int est_dans_iter(char *chai, char *cher){      //renvoie la case du mot cherché dans la source
    int len = mon_len(chai);
    int add = 0;
    int add2 = 0;
    while( add != len){
        if(chai[add] == cher[add2]){
            add++;
            add2++;
            if(cher[add2] =='\0'){
                //printf("cela s'y trouve\n");
                return 0;
            }
        }
        else{
            add++;
            add2 = 0;
        }
    }
    //printf("cela ne s'y trouve pas\n");
    return -1;
}


void * mon_strcpy(void *dest, const void *src, size_t len){                //str copy du mot ou phrase
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
        if (mon_len (lepath) >= len) {
            return 0;
        }
        if(!buf){
            buf = malloc(sizeof(char)*len);
            if(!buf) {
                return 0;
            }
        }
        mon_strcpy(buf, lepath, mon_len(lepath) + 1);
    }
    return buf;
}

int main(int argc, char**argv) {
    char cwd[256];
    if(argv[1] != NULL) {
        DIR *rep = opendir(argv[1]);
        if (rep != NULL) {
            struct dirent *lecture;
            if(!est_dans_iter(lecture->d_name,argv[2])) {
                printf("Voici les fichiers en extension: %s", argv[2]);
                while ((lecture = readdir(rep))) {
                    struct stat st;
                    stat(lecture->d_name, &st);
                    {
/* Modified time */
                        time_t t = st.st_mtime;
                        struct tm tm = *localtime(&t);
                        char s[32];
                        if (!est_dans_iter(lecture->d_name, argv[2])) {
                            printf("%-32s  %s\n", lecture->d_name, s);
                        }
                    }
                }
            }
            else{
                DIR *rep = opendir(".");
                if (rep != NULL) {
                    struct dirent *lecture;
                    while ((lecture = readdir(rep))) {
                        struct stat st;
                        stat(lecture->d_name, &st);{
/* Modified time */
                            time_t t = st.st_mtime;
                            struct tm tm = *localtime(&t);
                            char s[32];
                            strftime(s, sizeof s, "%d/%m/%Y %H:%M:%S", &tm);
                            printf("%-32s", lecture->d_name);
                        }
                    }
                    closedir(rep), rep = NULL;
                }
            }
            closedir(rep), rep = NULL;
        }
    }
    else{
        DIR *rep = opendir(".");
        if (rep != NULL) {
            struct dirent *lecture;
            while ((lecture = readdir(rep))) {
                struct stat st;
                stat(lecture->d_name, &st);{
/* Modified time */
                    time_t t = st.st_mtime;
                    struct tm tm = *localtime(&t);
                    char s[32];
                    strftime(s, sizeof s, "%d/%m/%Y %H:%M:%S", &tm);
                    printf("%-32s  %s\n", lecture->d_name, s);

                }
            }
            closedir(rep), rep = NULL;
        }
    }

    current_direct(cwd, sizeof(cwd));
    printf("\ndirectoire courrant: %s\n", cwd);
    return 0;
}


