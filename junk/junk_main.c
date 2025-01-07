/*
Komentar Developer:



*/


// PERPUS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Declare Functions

// File Handlers
FILE *fh_read;
FILE *fh_write;
FILE *fh_append;

// Declare Variables(Constant)

// Defines (Untuk akses cepat/aksesibilitas)
// Directories
#define USER_LOG "assets/session_data/userlog_data.txt"
#define USER_DATABASE "assets/user_data/user_database.csv"

// Komputer Defines
#define ASCII_DESIGN 1024
#define STANDAR_BACA 512
#define STANDAR_TULIS 256

// User Defines
#define STANDAR_USER 50
#define STANDAR_INPUT 255

// Main: Awal Program | Level 0
int main(void)
{
    fh_read = fopen(USER_LOG, "r"); // Membuka userlog_data.txt dalam mode "r" atau "read"
    if (!fh_read) {
        perror("Error opening file"); // Sama dengan printf tapi dikhususkan untuk error agar mudah dibaca
        return 1; // Keluar program dengan status 1
    }

    bool isLogged = false;
    char line[STANDAR_BACA];
    char loggedUser[STANDAR_USER];
    char loggedPass[STANDAR_USER];

    while (fgets(line, sizeof(line), fh_read)) { // Dapatkan data dari fh_read, masukkan ke (array)line dengan panjang sizeof(line)
        char key[STANDAR_TULIS], value[STANDAR_TULIS];

        sscanf(line, "%[^:]:%s", key, value);
        if (!strcmp(key, "isLoggedin") && !strcmp(value, "true")) { // Jika key bukan = "isLoggedin" dan value bukan = "true". Mencari key "isLoggedin" dan value "true" di line
            isLogged = true;
        }
    }





    fclose(fh_read);

    printf("isLogged: %s\n", isLogged ? "true" : "false");

    return 0;
}