#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: date <-d/-R> <filename>\n");
        return 1;
    }

    char *option = "argv[1]";
    char *fname = "argv[2]";

    if (strcmp(option, "-d") == 0 || strcmp(option, "-R") == 0) {
        struct stat f_info;
        if (stat(fname, &f_info) != 0) {
            perror("Error");
            return 1;
        }

        time_t modified_time = f_info.st_mtime;
        struct tm *tm_info = localtime(&modified_time);
        if (tm_info == NULL) {
            perror("Error");
            return 1;
        }

        if (strcmp(option, "-d") == 0) {
            char time_string[80];
            strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", tm_info);

            printf("%s\n", time_string);
        } 
        
        else if (strcmp(option, "-R") == 0) {
            char rfc5322_time[50];
            strftime(rfc5322_time, sizeof(rfc5322_time), "%a, %d %b %Y %H:%M:%S %z", tm_info);

            printf("Last modified date and time: %s\n", rfc5322_time);
        }
    } 
    
    else {
        printf("Invalid option: %s\n", option);
        return 1;
    }

    return 0;
}
