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
        printf("Error opening file"); // Sama dengan printf tapi dikhususkan untuk error agar mudah dibaca
        return 1; // Keluar program dengan status 1
    }

    bool isLogged = false;          // Variabel untuk isLoggedin
    char line[STANDAR_BACA];        // Variabel untuk membaca
    char loggedUser[STANDAR_USER];  // Variabel untuk LOGGED_USER
    char loggedPass[STANDAR_USER];  // Variabel untuk LOGGED_PASS
    int loggedUSID = -1;            // Variabel untuk LOGGED_USID(Default adalah -1 sebagai NULLIFIER(exit) jika NULL maka loggedUSID = 0)
    char sessionCOU[STANDAR_USER];  // Variabel untuk LOGGED_COU
    char sessionCTY[STANDAR_USER];  // Variabel untuk LOGGED_CTY


    while (fgets(line, sizeof(line), fh_read)) { // Dapatkan data dari fh_read, masukkan ke (array)line dengan panjang sizeof(line)
        char key[STANDAR_TULIS], value[STANDAR_TULIS];

        sscanf(line, "%[^:]:%s", key, value); // Mengecualikan tanda ":" dalam line untuk memisahkan key dan value.
        if (!strcmp(key, "isLoggedin")) { // Mencari key "isLoggedin" di line. Jika key bukan = "isLoggedin".
            isLogged = (!strcmp(value, "true")) ? true : false; // Mengecek jika value = "true" atau "false"
        } else if (!strcmp(key, "LOGGED_USER")) { // Mencari key "LOGGED_USER" di line. Jika key bukan = "LOGGED_USER".
            strcpy(loggedUser, value); // Masukkan value ke (array)loggedUser
        } else if (!strcmp(key, "LOGGED_PASS")) { // Mencari key "LOGGED_PASS" di line. Jika key bukan = "LOGGED_PASS".
            strcpy(loggedPass, value); // Masukkan value ke (array)loggedPass
        } else if (!strcmp(key, "LOGGED_USID")) { // Mencari key "LOGGED_USID" di line. Jika key bukan = "LOGGED_USID".
            loggedUSID = atoi(value); // atoi() untuk mengubah string menjadi integer. Memasukkan value ke (integer)loggedUSID
        } else if (!strcmp(key, "SESSION_COU")) {
            strcpy(sessionCOU, value);
        } else if (!strcmp(key, "SESSION_CTY")) {
            strcpy(sessionCTY, value);
        }
    }

    fclose(fh_read); // Menutup userlog_data.txt

    printf("isLogged: %s\n", isLogged ? "true" : "false"); // Mengecek apakah isLogged = true atau false lalu mengkonversi boolean(1,0) menjadi boolean("true","false").
    printf("LOGGED_USER: %s\n", loggedUser);
    printf("LOGGED_PASS: %s\n", loggedPass);
    if (loggedUSID != -1){
        printf("LOGGED_USID: %d\n", loggedUSID);
    } else {
        printf("LOGGED_USID: INVALID ID");
        return 1;
    }
    printf("SESSION_COU: %s\n", sessionCOU);
    printf("SESSION_CTY: %s\n", sessionCTY);

    return 0;
}