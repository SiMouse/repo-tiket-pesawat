// Aditya: File asli bernama "main.c", lokasi di directory utama

#include <stdio.h>
#include <stdlib.h>

// File Handlers
FILE *fh_read;
FILE *fh_write;
FILE *fh_append;

int main(void)
{
    fh_append = fopen("assets/user_data/user_database.csv", "a+");
    if (!fh_append){
        printf("Error opening file\n");
        return 1;
    } else {
        printf("File opened\n");
        fprintf(fh_append, "aditya,adit123,2\n");
        rewind(fh_append);
        char buffer[256]; 
        while (fgets(buffer, sizeof(buffer), fh_append)) {
            printf("%s", buffer); 
        }
        fclose(fh_append);
    }
    return 0;
}