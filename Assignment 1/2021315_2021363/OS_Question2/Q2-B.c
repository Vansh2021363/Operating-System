#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void print_usage() {
    printf("Usage: dir [-r] [-v] [dir_name]\n");
}

int main(int argc, char *argv[]) {
    int fr = 0;
    int fv = 0;
    const char *dName = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-r") == 0) {
            fr = 1;
        } else if (strcmp(argv[i], "-v") == 0) {
            fv = 1;
        } else {
            dName = argv[i];
        }
    }

    if (dName == NULL) {
        print_usage();
        return 1;
    }

    struct stat dStat;
    if (stat(dName, &dStat) == 0) {
        if (fr) {
            if (fv) {
                printf("Directory '%s' already exists. Removing...\n", dName);
            }
            if (rmdir(dName) != 0) {
                fprintf(stderr, "Error removing directory: %s\n", strerror(errno));
                return 1;
            }
        } else {
            fprintf(stderr, "Error: Directory '%s' already exists.\n", dName);
            return 1;
        }
    }

    if (mkdir(dName, 0777) != 0) {
        fprintf(stderr, "Error creating directory: %s\n", strerror(errno));
        return 1;
    }

    if (chdir(dName) != 0) {
        fprintf(stderr, "Error changing directory: %s\n", strerror(errno));
        return 1;
    }

    if (fv) {
        printf("Directory created and path changed to: %s\n", dName);
    }

    return 0;
}
