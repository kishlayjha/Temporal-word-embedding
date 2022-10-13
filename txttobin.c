#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static const int MAX_STRING_LENGTH = 1000;
typedef double real;

typedef struct cooccur_rec {
    int word1;
    int word2;
    real val;
} CREC;

char *file_list, *file_direct;

/* Efficient string comparison */
int scmp( char *s1, char *s2 ) {
    while(*s1 != '\0' && *s1 == *s2) {s1++; s2++;}
    return(*s1 - *s2);
}

/* convert txt to binary file*/
int individual_txttobin(char *input_file) {
    CREC trans;
    int flag;
    char str[MAX_STRING_LENGTH + 1];
    char *tmp1, *tmp2;
    tmp1 = malloc(sizeof(char) * MAX_STRING_LENGTH);
    tmp2 = malloc(sizeof(char) * MAX_STRING_LENGTH);

    sprintf(tmp1, "%s%s.cooccur", file_direct, input_file);
    sprintf(tmp2, "%s%s.cooccur.bin", file_direct, input_file);
    FILE *fid = fopen(tmp1,"r");
    FILE *fout = fopen(tmp2,"w");
    if(fid == NULL) {printf("Unable to open txt data %s.\n",tmp1); return 1;}
    while(fscanf(fid, "%d\t%d\t%lf\n", &trans.word1,&trans.word2,&trans.val) != EOF) {
        //printf("%d\t%d\t%lf\n",trans.word1,trans.word2,trans.val);
        fwrite(&trans, sizeof(CREC), 1, fout);
    }
    
    fclose(fid);
    fclose(fout);
    free(tmp1);
    free(tmp2);
    return 0;
}

int txttobin() {
    FILE *f_list;
    char *input_file;
    int time_slice = 0;
    char tmp[MAX_STRING_LENGTH + 1];
    strcpy(tmp, file_direct);
    strcat(tmp, file_list);

    input_file = malloc(sizeof(char) * MAX_STRING_LENGTH);
    f_list = fopen(tmp, "r");
    if(f_list == NULL) {fprintf(stderr, "Unable to open file list %s.\n",tmp); return 1;}
    while(fscanf(f_list, "%s\n", input_file) != EOF) {
        printf("Creating binary file for time slice %d: %s\n", time_slice, input_file);
        individual_txttobin(input_file);
        time_slice++;
    }
    fclose(f_list);
    free(input_file);
    return 0;
}

int find_arg(char *str, int argc, char **argv) {
    int i;
    for (i = 1; i < argc; i++) {
        if(!scmp(str, argv[i])) {
            if (i == argc - 1) {
                printf("No argument given for %s\n", str);
                exit(1);
            }
            return i;
        }
    }
    return -1;
}

int main(int argc, char **argv) {
    int i;
    file_list = malloc(sizeof(char) * MAX_STRING_LENGTH);
    file_direct = malloc(sizeof(char) * MAX_STRING_LENGTH);
    
    if (argc == 1) {
        printf("Tool to convert txt to bin\n");
        printf("\t-file-list <file>\n");
        printf("\t\tall the files\n");
        printf("\t-file-direct <file>\n");
        printf("\t\tthe directory\n");

        printf("\nExample usage:\n");
        printf("./txttobin -file-direct ./data/ -file-list filelist.txt\n\n");
        return 0;
    }

    if ((i = find_arg((char *)"-file-list", argc, argv)) > 0) strcpy(file_list, argv[i + 1]);
    else strcpy(file_list, (char *)"filelist.txt");
    if ((i = find_arg((char *)"-file-direct", argc, argv)) > 0) strcpy(file_direct, argv[i + 1]);
    else strcpy(file_direct, (char *)"./data/");
    
    int result = txttobin();
    free(file_list);
    free(file_direct);
    return result;
}

