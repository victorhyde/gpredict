#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Replaces the default module with moduleName in the Gpredict conf
 **/
int setDefaultModule(char *moduleName) {
    char buffer[1001];
    char *file = "../../.config/Gpredict/gpredict.cfg"; // Contingent on setup
    char newLine[1001];
    char *token;
    FILE *fp = fopen(file, "r");

    if (fp == NULL) {
        perror("Error while opening the file\n");
        exit(1); // arbitrary status code
    }

    fread(buffer, 1, 1000, fp);

    // Close file then reopen for writing
    fclose(fp);
    fp = fopen(file, "w");

    token = strtok(buffer, "\n");

    // Write contents of buffer into file
    while (token != NULL) {
        if (strstr(token, "OPEN_MODULES")) {
            sprintf(newLine, "%s%s\n", "OPEN_MODULES=", moduleName);
            fwrite(newLine, strlen(newLine), 1, fp);
        } else {
            sprintf(newLine, "%s\n", token);
            fwrite(newLine, strlen(newLine), 1, fp);
        }

        token = strtok(NULL, "\n"); // move pointer to next string
    }

    fclose(fp);
    return 0;
}

// For debugging purposes
// int main() {
//     setDefaultModule("Test");
//     return 0;
// }