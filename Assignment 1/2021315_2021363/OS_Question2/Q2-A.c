#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int word_count(const char *fname) {
    FILE *file = fopen(fname, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    int count = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == ' ' || ch == '\n') {
            count++;
        }
    }
    fclose(file);
    return count;
}


int w_count(const char *fname) {
    FILE *file = fopen(fname, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    int wordCount = 0;
    char word[100];

    while (fscanf(file, "%s", word) == 1) {
        wordCount++;
    }

    fclose(file);

    return wordCount;
}

void word_com(const char *c) {
    char option = c[5];
    if (option == '-') {
        char subOption = c[6];
        if (subOption == 'n') {
            char fname[100];
            int i;
            for (i = 8; c[i] != '\n'; i++) {
                fname[i - 8] = c[i];
            }
            fname[i - 8] = '\0';

            int count = w_count(fname);
            if (count != -1) {
                printf("%d\n", count);
            }
        } else if (subOption == 'd') {
            char fname1[100], fname2[100];
            int i;
            for (i = 8; c[i] != ' '; i++) {
                fname1[i - 8] = c[i];
            }
            fname1[i - 8] = '\0';

            int k = i + 1;
            int j;
            for (j = k; c[j] != '\n'; j++) {
                fname2[j - k] = c[j];
            }
            fname2[j - k] = '\0';

            int count1 = word_count(fname1);
            int count2 = word_count(fname2);

            if (count1 != -1 && count2 != -1) {
                int ans = (count1 >= count2) ? (count1 - count2) : (count2 - count1);
                printf("%d\n", ans);
            }
        }
        
        else{printf("Wrong Option\n");}
        
    } else {
        char fname[100];
        int i;
        for (i = 5; c[i] != '\n'; i++) {
            fname[i - 5] = c[i];
        }
        fname[i - 5] = '\0';

        int ans = word_count(fname);
        printf("%d\n", ans);


    }
}

void execute_external_command(const char *command) {
    char *arguments[100];
    int arg_count = 0;

    char *token = strtok((char *)command, " \n");
    while (token != NULL) {
        arguments[arg_count] = token;
        arg_count++;
        token = strtok(NULL, " \n");
    }
    arguments[arg_count] = NULL; 

    
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);

    } else if (pid == 0) {
        execvp(arguments[0], arguments);
        perror("execvp failed");
        exit(EXIT_FAILURE);

    } else {
        wait(NULL);
    }
}

int main() {
    char c[1000], com[10];
    printf("Enter command: ");
    fgets(c, sizeof(c), stdin);

    int i;
    for (i = 0; c[i] != ' ' && c[i] != '\0'; i++) {
        com[i] = c[i];
    }
    com[i] = '\0';

    if (strcmp(com, "word") == 0) {
        word_com(c);
    } else if (strcmp(com, "dir") == 0) { 
        execute_external_command(c);
    } else if (strcmp(com, "date") == 0) {
        execute_external_command(c);
    } else {
        printf("Wrong Command\n");
    }

    return 0;
}
