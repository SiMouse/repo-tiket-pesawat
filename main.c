/*
Komentar Developer:

    Catatan PENTING:
        # int main()
            pilihDev === pilihNormal

    Akbar Aditya (04/01/2024):
        v0.1.3
        # Komentar: 
            

        # Changelog:
            - Perpindahan file USER_LOG(userlog_data.txt) dari "assets/user_data" ke "assets/session_data"
            - Perubahan value USER_LOG dari "assets/user_data/userlog_data.txt" ke "assets/session_data/userlog_data.txt"


        # Ditambahkan:
            - Realisasi fungsi menuDomestik() dan menuInternasional()

            

*/


// PERPUS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

// File Handlers
FILE *fh_read;
FILE *fh_write;
FILE *fh_rewrite;
FILE *fh_append;

// Defines (Untuk akses cepat/aksesibilitas) # Kumpulan untuk menyimpan nilai
    // Versi Program
#define CURRENT_VERSION "v0.1.1"

// Kumpulan warna
        // Regular
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"


        // High-intensity
#define HRED "\e[0;91m"
#define HGRN "\e[0;92m"
#define HYEL "\e[0;93m"
#define HBLU "\e[0;94m"

        // Underlined
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"

        // Default
#define CRESET "\e[0m"

    // Define Miscellaneous
#define RUN_SUCCESS "SUCCESS"
#define RUN_FAILED "FAILED"

    // Alamat Folder / Directory
#define USER_LOG "assets/user_data/userlog_data.txt"

#define AKUN_LIST "assets/user_data/akun_list.csv"

#define BUAT_RESI "assets/user_data/resi.txt"

    // Alamat Folder Khusus Desain ASCII / ASCII Directory
#define PILIH_SISTEM_PROGRAM "assets/ascii_list/pilih_sistem_program.txt"
#define MASUK_REGISTER "assets/ascii_list/masuk_register.txt"
#define MENU "assets/ascii_list/menu.txt"
#define DOMESTIK "assets/ascii_list/domestik.txt"
#define INTERNASIONAL "assets/ascii_list/internasional.txt"
#define REGISTRASI "assets/ascii_list/registrasi.txt"
#define LOGIN "assets/ascii_list/login.txt"

    // Alamat Folder Khusus Teks di Layar / Text Directory
#define PILIH_SISTEM_PROGRAM_TEXT "assets/text_list/pilih_sistem_program.txt"
#define MASUK_REGISTER_TEXT "assets/text_list/masuk_register.txt"
#define MENU_TEXT "assets/text_list/menu.txt"
#define DOMESTIK_TEXT "assets/text_list/domestik.txt"
#define INTERNASIONAL_TEXT "assets/text_list/internasional.txt"

    // Alamat Folder Khusus Data / Data Directory
#define DOMESTIK_DATA "assets/session_data/domestik.txt"
#define INTERNASIONAL_DATA "assets/session_data/internasional.txt"
// #define DATA "lokasi data"
// char LokasiDATA[] = "lokasi data"
    // Deklarasi nilai yang tidak akan berubah / Define Konstanta
#define BUFFER 1024
#define STANDAR_KOLOM 512
#define STANDAR_BARIS 256
#define STANDAR_INPUT 128
#define STANDAR_READCHAR 50

// Membuat sinonim dari tipe data
    // Sinonim dari fungsi yang berinteraksi langsung dengan user
typedef void fungsiVoid; // Untuk membuat fungsi dengan tipe data void
typedef int fungsiInt; // Untuk membuat fungsi dengan tipe data integer
typedef char fungsiChar; // Untuk membuat fungsi dengan tipe data char

    // Sinonim dari fungsi yang tidak berinteraksi langsung dengan user / Dibelakang layar
typedef void debugFungsiVoid;
typedef int debugFungsiInt;
typedef char debugFungsiChar;

// Deklarasi Fungsi
    // Halaman-halaman sistem Developer
fungsiVoid devSystem(void); // Membuka laman developer

    // Halaman-halaman sistem Portal (Validasi, Registrasi, Login)
fungsiInt portalSystem(char isInvalid[]); // Laman login dan registrasi
fungsiInt validasiAkun(void); // Fungsi otomatis ke main page jika user sudah login
fungsiInt loginAkun(void); // Laman login
fungsiInt registrasiAkun(void); // Laman registrasi
fungsiInt prosesLogin(char username[], char password[], char country[], char city[]);
fungsiInt logoutAkun(void);

    // Halaman-halaman sistem Utama
fungsiInt mainMENU(char Logged_USER[], char Logged_PASS[], char Logged_COUNTRY[], char Logged_CITY[], char MSG[], char isInvalid[]); // Laman utama
fungsiInt lokasiSekarang(char Logged_USER[], char Logged_PASS[], char Logged_COUNTRY[], char Logged_CITY[], char isInvalid[]); // Laman lokasi sekarang
fungsiInt menuDomestic(char Logged_USER[], char Logged_PASS[], char Logged_COUNTRY[], char Logged_CITY[], char isInvalid[]); // Laman menu domestik
fungsiInt menuInternasional(char Logged_USER[], char Logged_PASS[], char Logged_COUNTRY[], char Logged_CITY[], char isInvalid[]); // Laman menu internasional
fungsiInt menuResip(char Logged_USER[], char Logged_PASS[], char Logged_COUNTRY[], char Logged_CITY[], char isInvalid[]); // Laman menu resip

fungsiInt konfirmasiTiket(char Logged_USER[], char Logged_PASS[], char Logged_COUNTRY[], char Logged_CITY[], char isInvalid[], char tipeTiket[], char tujuanCOUNTRYTiket[], char tujuanCITYTiket[], int hargaTiket);
fungsiInt pembuatanTiket(char Logged_USER[], char Logged_PASS[], char Logged_COUNTRY[], char Logged_CITY[], char isInvalid[], char tipeTiket[], char tujuanCOUNTRYTiket[], char tujuanCITYTiket[], int hargaTiket, char statusTiket[]);

    // Fungsi background sebagai validator, transit, dan atau background check
debugFungsiInt runTest(char msg[], char type[], int param); // Untuk mengakhiri program (DEBUGGING ONLY!)
debugFungsiInt bacaFungsi(char func[]);

// int main();


/**
 * @brief Fungsi utama program yang akan dijalankan ketika program dijalankan.
 *
 * Fungsi ini akan menampilkan menu awal program yang dapat dipilih oleh user.
 * User dapat memilih 2 opsi: "Normal" atau "Dev". Jika user memilih "Normal",
 * maka program akan menjalankan fungsi validasiAkun() yang akan memvalidasi
 * input user dan membuka laman login atau registrasi. Jika user memilih "Dev",
 * maka program akan menjalankan fungsi devSystem() yang akan membuka laman
 * developer. Jika input user tidak valid, maka program akan menampilkan pesan
 * error dan menjalankan fungsi main() lagi dengan parameter "true".
 *
 * @param isInvalid Parameter yang digunakan untuk menentukan apakah input user
 *                   valid atau tidak. Jika "true", maka program akan
 *                   menampilkan pesan error dan menjalankan fungsi main() lagi.
 *                   Jika "false", maka program akan menampilkan menu awal
 *                   program.
 * @return int Nilai yang dikembalikan oleh fungsi ini. Jika program dijalankan
 *             dengan benar, maka fungsi ini akan mengembalikan nilai 0.
 *             Jika terjadi error, maka fungsi ini akan mengembalikan nilai
 *             yang tidak sama dengan 0.
 */
fungsiInt main(char isInvalid[])
{
    // CLS
    system("cls");
    // Start Placeholder

    // ASCII Art
    fh_read = fopen(PILIH_SISTEM_PROGRAM, "r");
    if (!fh_read) {
        runTest("Error opening file: int main();", RUN_FAILED, __LINE__ - 2);
    }

    char buffer[BUFFER];

    while (fgets(buffer, sizeof(buffer), fh_read)) {
        printf(HGRN "%s" CRESET, buffer);
    }

    fclose(fh_read);

    printf(HYEL "\nCurrent Version: " HBLU "%s\n\n" CRESET, CURRENT_VERSION);

    // Text Placeholder
    fh_read = fopen(PILIH_SISTEM_PROGRAM_TEXT, "r");
    if (!fh_read) {
        runTest("Error opening file: int main();", RUN_FAILED, __LINE__ - 2);
    }

    while (fgets(buffer, sizeof(buffer), fh_read)) {
        printf(HGRN "%s" CRESET, buffer);
    }

    fclose(fh_read);
    // End Placeholder


    // Separator
    printf("\n\n");

    // Variabel untuk memilih sistem
    char pilihNormal[7][10] = {"1", "1.", "Normal", "normal", "NORMAL", "norm", "nor"}; // Maksimum array: 7, maksimum karakter per array: 10
    char pilihDev[7][10] = {"2", "2.", "Dev", "dev", "developer", "DEVELOPER", "Developer"}; // Maksimum array: 7, maksimum karakter per array: 10 // sizeof(pilihDev) === sizeof(pilihNormal)
    int pilihMaksimal = 7; // pilihNormal == pilihMaksimal && pilihDev == pilihMaksimal

    // Invalid Check
    if ( isInvalid == "true" ) { // Mencari perbedaan dari isInvalid dengan "true", jika tidak ada perbedaan, value akan menjadi 0. Secara logika 0 akan mengubah value false menjadi true, karena perbedaan tidak ditemukan.
        printf(HRED "Input tidak valid!" HYEL " Pilih Sistem: " CRESET);
    } else printf(HYEL "Pilih Sistem: " CRESET);

    // Memasukkan input
    char input[STANDAR_INPUT]; // Maksimum input karakter: 128
    scanf("%s", &input);
    
    // Memproses input
    for (int i = 0; i < pilihMaksimal; i++) { // Setiap loop, i + 1, dan kondisi di dalam for loop body mencari perbedaan dari input dengan array[i]. Jika perbedaan tidak ada, maka otomatis kondisi = true.
        if ( strcmp(input, pilihNormal[i]) == 0 ) {
            validasiAkun();
            return 0;
        }

        if ( strcmp(input, pilihDev[i]) == 0 ) {
            devSystem();
            return 0;
        }
    }
    main("true");

    // Return 0
    return 0;
}

// Sistem Portal ========================================================================================

/**
 * @brief Fungsi untuk validasi akun user.
 *
 * Fungsi ini akan membuka file userlog_data.txt dan mencari data user yang
 * sesuai dengan yang diinputkan oleh user. Jika data user tidak ditemukan,
 * maka fungsi ini akan mengubah isLoggedIn di USER_LOG menjadi false dan
 * mengubah loggedUser hingga sessionCTY menjadi NULL.
 *
 * @return int Nilai yang dikembalikan oleh fungsi ini. Jika program dijalankan
 *             dengan benar, maka fungsi ini akan mengembalikan nilai 0.
 *             Jika terjadi error, maka fungsi ini akan mengembalikan nilai
 *             yang tidak sama dengan 0.
 */
fungsiInt validasiAkun() {

    printf(HYEL "\nFungsi dijalankan: " HBLU "%s\n" CRESET, __func__);

    // Membuka FILE

    // Membuka userlog_data.txt
    fh_rewrite = fopen(USER_LOG, "r+"); // Membuka userlog_data.txt dalam mode "r" atau "read"
    if (!fh_rewrite) {
        printf("Error opening file di line: %d\n", __LINE__ - 2); // Sama dengan printf tapi dikhususkan untuk error agar mudah dibaca
        return 1; // Keluar program dengan status 1
    }

    // Kumpulan Variabel untuk USER_LOG
    int loggedUSID = -1;             // Variabel untuk LOGGED_USID(Default adalah -1 sebagai NULLIFIER(exit) jika NULL maka loggedUSID = 0)
    bool isLogged = false;           // Variabel untuk key isLoggedin
    char lineUSER_LOG[BUFFER];       // Variabel buffer untuk membaca kolom yang ada di file userlog_data.txt
    char loggedUser[STANDAR_KOLOM];  // Variabel untuk key LOGGED_USER
    char loggedPass[STANDAR_KOLOM];  // Variabel untuk key LOGGED_PASS
    char sessionCOU[STANDAR_KOLOM];  // Variabel untuk key LOGGED_COU
    char sessionCTY[STANDAR_KOLOM];  // Variabel untuk key LOGGED_CTY

    // Kumpulan Fungsi untuk USER_LOG
    while (fgets(lineUSER_LOG, sizeof(lineUSER_LOG), fh_rewrite)) { // Dapatkan data dari fh_read, masukkan ke (array)line dengan panjang sizeof(line)
        char key[STANDAR_READCHAR], value[STANDAR_READCHAR];

        sscanf(lineUSER_LOG, "%[^:]:%s", key, value); // Mengecualikan tanda ":" dalam line untuk memisahkan key dan value.
        if ( !strcmp(key, "isLoggedin") ) { // Mencari key "isLoggedin" di line. Jika key bukan = "isLoggedin".
            isLogged = (!strcmp(value, "true")) ? true : false; // Mengecek jika value = "true" atau "false"
        } else if ( !strcmp(key, "LOGGED_USER") ) { // Mencari key "LOGGED_USER" di line. Jika key bukan = "LOGGED_USER".
            strcpy(loggedUser, value); // Masukkan value ke (array)loggedUser
        } else if ( !strcmp(key, "LOGGED_PASS") ) { // Mencari key "LOGGED_PASS" di line. Jika key bukan = "LOGGED_PASS".
            strcpy(loggedPass, value); // Masukkan value ke (array)loggedPass
        } else if ( !strcmp(key, "SESSION_COU") ) { // Mencari key "SESSION_COU" di line. Jika key bukan = "SESSION_COU".
            strcpy(sessionCOU, value); // Masukkan value ke (array)sessionCOU
        } else if ( !strcmp(key, "SESSION_CTY") ) { // Mencari key "SESSION_CTY" di line. Jika key bukan = "SESSION_CTY".
            strcpy(sessionCTY, value); // Masukkan value ke (array)sessionCTY
        }
    }
    fclose(fh_rewrite); // Menutup userlog_data.txt

    // Jika isLogged = false, maka langsung pergi ke halaman portal
    if (!isLogged){
        portalSystem("false");
        return 0;
    }

    // Membuka akun_list.csv
    fh_read = fopen(AKUN_LIST, "r");
    if (!fh_read) {
        runTest("Error opening file: int validasiAkun();", RUN_SUCCESS, __LINE__ - 2); // Sama dengan printf tapi dikhususkan untuk error agar mudah dibaca
    }

    // Kumpulan Variabel untuk AKUN_LIST
    char lineAKUN[BUFFER]; // Variabel buffer untuk membaca kolom yang ada di file akun_list.csv
    int isKetemu = 0; // Variabel boolean mencari perbandingan antara USER_LOG dengan AKUN_LIST
    char USER_DATABASE[STANDAR_KOLOM]; // Variabel untuk key USER
    char PASS_DATABASE[STANDAR_KOLOM]; // Variabel untuk key PASS
    char COUT_DATABASE[STANDAR_KOLOM]; // Variabel untuk key COU
    char CITY_DATABASE[STANDAR_KOLOM]; // Variabel untuk key CTY

    // Dapatkan data dari AKUN_LIST lalu masukkan ke (array)lineAKUN
    while(fgets(lineAKUN, sizeof(lineAKUN), fh_read)) {
        // Dari (array)lineAKUN, masukkan ke variabel yang ada
        sscanf(lineAKUN, "%[^,],%[^,],%[^,],%s[^\n]", USER_DATABASE, PASS_DATABASE, COUT_DATABASE, CITY_DATABASE); // Mengecualikan tanda "," dalam line untuk memisahkan key dan value.

        // printf("User: %s\nPassword: %s\nCountry: %s\nCity: %s\n", USER_DATABASE, PASS_DATABASE, COUT_DATABASE, CITY_DATABASE); // Test Print
        
        // Perbandingan USER_LOG dengan AKUN_LIST untuk mencari data dari user, jika tidak ada set isLoggedIn(di USER_LOG) ke false.
        if ( !strcmp(USER_DATABASE, loggedUser) && !strcmp(PASS_DATABASE, loggedPass) && !strcmp(COUT_DATABASE, sessionCOU) && !strcmp(CITY_DATABASE, sessionCTY) ) {
            isKetemu = 1;
            mainMENU(loggedUser, loggedPass, sessionCOU, sessionCTY, HYEL "Welcome back, %s!" CRESET, "false");
        } 
        
    }

    fclose(fh_read); // Menutup AKUN_LIST.csv

    if (!isKetemu) {
        // Mengubah isLoggedIn di USER_LOG menjadi false, dan mengubah loggedUser hingga sessionCTY menjadi NULL
        printf("\n");
        printf("User tidak terdaftar!\n");
        printf(HYEL "AKUN_LIST: " HGRN "[%s, %s, %s, %s]\n" CRESET, USER_DATABASE, PASS_DATABASE, COUT_DATABASE, CITY_DATABASE);
        printf(HYEL "USER_LOG: " HGRN "[%s, %s, %s, %s]\n" CRESET, loggedUser, loggedPass, sessionCOU, sessionCTY);
        fh_rewrite = fopen(USER_LOG, "w"); // Membuka userlog_data.txt dalam mode "w" atau "write"
        if (!fh_rewrite) {
            runTest("Error membuka file", RUN_FAILED, __LINE__ - 2); // Sama dengan printf tapi dikhususkan untuk error agar mudah dibaca
        }
        fprintf(fh_rewrite, "isLoggedin:false\n");
        fprintf(fh_rewrite, "LOGGED_USER:NULL\n");
        fprintf(fh_rewrite, "LOGGED_PASS:NULL\n");
        fprintf(fh_rewrite, "SESSION_COU:NULL\n");
        fprintf(fh_rewrite, "SESSION_CTY:NULL\n");
        fclose(fh_rewrite);

        printf("\n\n" HRED "Kembali ke titik awal.\n" CRESET);
        Sleep(2000);
        printf("\n\n");
        main("false");
    }

    return 0;
}

/**
 * @brief Fungsi yang digunakan untuk memilih login atau registrasi
 *
 * Fungsi ini akan menampilkan menu portal system yang dapat dipilih oleh user.
 * User dapat memilih 3 opsi: "Login", "Register", dan "Kembali". Jika user memilih
 * "Login", maka fungsi akan menjalankan fungsi loginAkun(). Jika user memilih
 * "Register", maka fungsi akan menjalankan fungsi registrasiAkun(). Jika user
 * memilih "Kembali", maka fungsi akan menjalankan fungsi main() dengan parameter
 * "false". Jika input user tidak valid, maka fungsi akan menampilkan pesan error
 * dan menjalankan fungsi portalSystem() lagi dengan parameter "true".
 *
 * @param isInvalid Parameter yang digunakan untuk menentukan apakah input user
 *                   valid atau tidak. Jika "true", maka fungsi akan menampilkan
 *                   pesan error dan menjalankan fungsi portalSystem() lagi.
 *                   Jika "false", maka fungsi akan menampilkan menu portal system.
 * @return int Nilai yang dikembalikan oleh fungsi ini. Jika program dijalankan
 *             dengan benar, maka fungsi ini akan mengembalikan nilai 0.
 *             Jika terjadi error, maka fungsi ini akan mengembalikan nilai
 *             yang tidak sama dengan 0.
 */
fungsiInt portalSystem(char isInvalid[]) {

    // CLS
    system("cls");
    // Start Placeholder
    char buffer[BUFFER];
    
        // ASCII Art
    fh_read = fopen(MASUK_REGISTER, "r");
    if (!fh_read) {
        runTest("Error opening file: int portalSystem();", RUN_FAILED, __LINE__ - 2);
    }

    while (fgets(buffer, sizeof(buffer), fh_read)) {
        printf(HBLU "%s" CRESET, buffer);
    }

    fclose(fh_read);

        // Text Placeholder
    fh_read = fopen(MASUK_REGISTER_TEXT, "r");

    if (!fh_read){
        runTest("Error opening file: int portalSystem();", RUN_FAILED, __LINE__ - 2);
    }

    while (fgets(buffer, sizeof(buffer), fh_read)) {
        printf(HYEL "%s" CRESET, buffer);
    }

    fclose(fh_read);
    // End Placeholder

    // Variabel untuk menyimpan array input

    char loginArray[4][BUFFER] = {"1","Login","login","Login"};
    char regisArray[4][BUFFER] = {"2","Register","register","Register"};
    char kembaliArray[4][BUFFER] = {"0","Kembali","kembali","Kembali"};
    char input[BUFFER];

    // Separator
    printf("\n\n");

    // Pilihan

    if (isInvalid == "true") { 
        printf(HRED "Piihan tidak valid! " HYEL "Ulangi Pilihan: " CRESET);
    } else {
        printf(HYEL "Pilihan: " CRESET);
    }

    scanf("%s", &input);

        for (int i = 0; i < sizeof(loginArray) / sizeof(loginArray[0]); i++) {
        if (strcmp(input, loginArray[i]) == 0) {
            loginAkun();
            return 0;
        } else if (strcmp(input, regisArray[i]) == 0) {
            registrasiAkun();
            return 0;
        } else if (strcmp(input, kembaliArray[i]) == 0) {
            main("false");
            return 0;
        }
    }
    portalSystem("true");


    return 0;
}

fungsiInt loginAkun() {

    // CLS
    system("cls");

    // Start Placeholder
    fh_read = fopen(LOGIN, "r");
    if (!fh_read) {
        runTest("Error opening file: int loginAkun();", RUN_FAILED, __LINE__ - 2);
    }

    char buffer[BUFFER];
    while (fgets(buffer, sizeof(buffer), fh_read)) {
        printf(HBLU "%s" CRESET, buffer);
    }

    fclose(fh_read);
    // End Placeholder

    // Separator
    printf("\n\n");

    char logUsername[BUFFER];
    char logPassword[BUFFER];

    printf(HYEL "Username: " CRESET);
    scanf("%s", &logUsername);

    printf(HYEL "Password: " CRESET);
    scanf("%s", &logPassword);
    
    fh_read = fopen(AKUN_LIST, "r");
    if (!fh_read) {
        runTest("Error opening file: int loginAkun();", RUN_FAILED, __LINE__ - 2);
    }

    char lineAKUN[BUFFER];
    char username[STANDAR_KOLOM];
    char password[STANDAR_KOLOM];
    char country[STANDAR_KOLOM];
    char city[STANDAR_KOLOM];
    int isKetemu = 0;
    while (fgets(lineAKUN, sizeof(lineAKUN), fh_read)) {

        sscanf(lineAKUN, "%[^,],%[^,],%[^,],%s[^\n]\n", username, password, country, city);

        if ( strcmp(username, logUsername) == 0 && strcmp(password, logPassword) == 0 ) {
            isKetemu = 1;
        } else if ( strcmp(username, logUsername) != 0 || strcmp(password, logPassword) != 0 ) {
            isKetemu = 0;
        }

        if (isKetemu == 1) {
            printf(HGRN "User ditemukan!\n" CRESET);
            prosesLogin(username, password, country, city);
            break;
        } else if (isKetemu != 0) {
            printf(HRED "%s" HYEL " dan " HRED "%s" HYEL " tidak ditemukan!\n" CRESET, username, password);
            printf(HGRN "%s, %s\n" CRESET, username, password);
            printf(HRED "%s, %s\n" CRESET, logUsername, logPassword);
            Sleep(1500);
            loginAkun();
            break;
        }
    }

    fclose(fh_read);

}

fungsiInt prosesLogin(char username[], char password[], char country[], char city[]) {

    fh_rewrite = fopen(USER_LOG, "w"); // Membuka userlog_data.txt dalam mode "w" atau "write"
    if (!fh_rewrite) {
        runTest("Error membuka file", RUN_FAILED, __LINE__ - 2); // Sama dengan printf tapi dikhususkan untuk error agar mudah dibaca
    }
    fprintf(fh_rewrite, "isLoggedin:true\n");
    fprintf(fh_rewrite, "LOGGED_USER:%s\n", username);
    fprintf(fh_rewrite, "LOGGED_PASS:%s\n", password);
    fprintf(fh_rewrite, "SESSION_COU:%s\n", country);
    fprintf(fh_rewrite, "SESSION_CTY:%s\n", city);
    fclose(fh_rewrite);

    printf("\n\n");
    printf(HGRN "Login berhasil!\n" CRESET);
    printf(HYEL "Meredireksi ke menu utama.\n" CRESET);
    Sleep(1500);

    validasiAkun();
}

fungsiInt registrasiAkun() {

    // CLS
    system("cls");
    
    // Start Placeholder
    fh_read = fopen(REGISTRASI, "r");
    if (!fh_read) {
        runTest("Error opening file: int registrasiAkun();", RUN_FAILED, __LINE__ - 2);
    }

    char buffer[BUFFER];
    while (fgets(buffer, sizeof(buffer), fh_read)) {
        printf(HBLU "%s" CRESET, buffer);
    }

    fclose(fh_read);
    // End Placeholder

    // Separator
    printf("\n\n");


    // Lokasi Default
    char defaultCountry[STANDAR_KOLOM] = "Indonesia";
    char defaultCity[STANDAR_KOLOM] = "Jakarta";

    // Variabel penampung input dari user
    char newUsername[BUFFER];
    char newPassword[BUFFER];

    // User input
    printf(HYEL "Make a username: " CRESET);
    scanf("%s", &newUsername);

    printf(HYEL "Make a password: " CRESET);
    scanf("%s", &newPassword);

    // Membuat akun baru
    fh_append = fopen(AKUN_LIST, "a+");
    if (!fh_append) {
        runTest("Error opening file: int registrasiAkun();", RUN_FAILED, __LINE__ - 2);
    }

    fprintf(fh_append, "%s,%s,%s,%s\n", newUsername, newPassword, defaultCountry, defaultCity);
    fclose(fh_append);

    // Auto login dan redirect ke validasiAkun()
    fh_rewrite = fopen(USER_LOG, "w");
    if (!fh_rewrite) {
        runTest("Error opening file: int registrasiAkun();", RUN_FAILED, __LINE__ - 2);
    }

    fprintf(fh_rewrite, "isLoggedin:true\n");
    fprintf(fh_rewrite, "LOGGED_USER:%s\n", newUsername);
    fprintf(fh_rewrite, "LOGGED_PASS:%s\n", newPassword);
    fprintf(fh_rewrite, "SESSION_COU:%s\n", defaultCountry);
    fprintf(fh_rewrite, "SESSION_CTY:%s\n", defaultCity);
    fclose(fh_rewrite);

    printf("\n\n");
    printf(HGRN "Registrasi akun berhasil!\n" CRESET);
    printf("\n");
    printf(HRED "Kamu akan di redireksi ke laman utama..." CRESET);
    Sleep(2000);

    validasiAkun();

}

fungsiInt logoutAkun(){

    // CLS
    system("cls");
    
    // Bersihkan resi
    fh_write = fopen(BUAT_RESI, "w");
    if (!fh_write) {
        runTest("Error opening file: int logoutAkun();", RUN_FAILED, __LINE__ - 2);
    }

    fprintf(fh_write, "");
    fclose(fh_write);

    fh_rewrite = fopen(USER_LOG, "w");
    if (!fh_rewrite) {
        runTest("Error opening file: int logoutAkun();", RUN_FAILED, __LINE__ - 2);
    }

    fprintf(fh_rewrite, "isLoggedin:false\n");
    fprintf(fh_rewrite, "LOGGED_USER:NULL\n");
    fprintf(fh_rewrite, "LOGGED_PASS:NULL\n");
    fprintf(fh_rewrite, "SESSION_COU:NULL\n");
    fprintf(fh_rewrite, "SESSION_CTY:NULL\n");
    fclose(fh_rewrite);

    validasiAkun();
}

// Menu Utama ==========================================================================================

fungsiInt mainMENU(char Logged_USER[], char Logged_PASS[], char Logged_COUNTRY[], char Logged_CITY[], char MSG[], char isInvalid[]) {

    // CLS
    system("cls");

    // Start Placeholder
    char buffer[BUFFER];

    // ASCII Art
    fh_read = fopen(MENU, "r");
    if (!fh_read) {
        runTest("Error opening file: int mainMENU();", RUN_FAILED, __LINE__ - 2);
    }

    while (fgets(buffer, sizeof(buffer), fh_read)) {
        printf(HBLU "%s" CRESET, buffer);
    }

    fclose(fh_read);
    
    // Greet
    printf("\n\n");
    printf(MSG, Logged_USER);
    printf(HYEL "\nMau kemana sekarang?" CRESET);
    printf("\n\n");

    // Text Placeholder
    fh_read = fopen(MENU_TEXT, "r");
    if (!fh_read) {
        runTest("Error opening file: int mainMENU();", RUN_FAILED, __LINE__ - 2);
    }

    while (fgets(buffer, sizeof(buffer), fh_read)) {
        printf(HGRN "%s" CRESET, buffer);
    }

    fclose(fh_read);

    // End Placeholder

    // Separator
    printf("\n\n");

    // Input User
    char input[STANDAR_INPUT];

    if (isInvalid == "true") { 
        printf(HRED "Piihan tidak valid! " HYEL "Ulangi Pilihan: " CRESET);
    } else {
        printf(HYEL "Pilihan: " CRESET);
    }
    scanf("%s", &input);

    // Proses Input untuk membuka laman domestic atau laman international
        // Variabel untuk input select, ARRAY HARUS 4
    char domesticArray[4][15] = {"1", "Domestic", "domestic", "dom"};
    char internationalArray[4][15] = {"2", "Internasional", "internasional", "int"};
    char lokasiSekArray[4][15] = {"3", "Lokasi Sekarang", "lokasi sekarang", "lokasi"};
    char logoutArray[4][15] = {"4", "Logout", "logout", "logout"};
    char resipArray[4][15] = {"5", "Resip", "resip", "res"};
    char kembaliArray[4][15] = {"0", "Kembali", "kembali", "back"};

        // Memproses input
    for (int i = 0; i < sizeof(domesticArray) / sizeof(domesticArray[0]); i++) {
        if (strcmp(input, domesticArray[i]) == 0) {
            menuDomestic(Logged_USER, Logged_PASS, Logged_COUNTRY, Logged_CITY, 0);
            return 0;
        } else if (strcmp(input, internationalArray[i]) == 0) {
            menuInternasional(Logged_USER, Logged_PASS, Logged_COUNTRY, Logged_CITY, 0);
            return 0;
        } else if (strcmp(input, lokasiSekArray[i]) == 0) {
            lokasiSekarang(Logged_USER, Logged_PASS, Logged_COUNTRY, Logged_CITY, 0);
            return 0;
        } else if (strcmp(input, logoutArray[i]) == 0) {
            logoutAkun();
            return 0;
        } else if (strcmp(input, resipArray[i]) == 0) {
            menuResip(Logged_USER, Logged_PASS, Logged_COUNTRY, Logged_CITY, "false");
            return 0;
        } else if (strcmp(input, kembaliArray[i]) == 0) {
            main("false");
            return 0;
        }
    }
    mainMENU(Logged_USER, Logged_PASS, Logged_COUNTRY, Logged_CITY, MSG, "true");
    return 0;
}

fungsiInt menuDomestic(char Logged_USER[], char Logged_PASS[], char Logged_COUNTRY[], char Logged_CITY[], char isInvalid[]) {

    // CLS
    system("cls");

    // Local Declare
    int hargaDestinasi = 0;

    // Start Placeholder
    char buffer[BUFFER];

    // ASCII Art
    fh_read = fopen(DOMESTIK, "r");
    if (!fh_read) {
        runTest("Error opening file: int menuDomestic();", RUN_FAILED, __LINE__ - 2);
    }

    while (fgets(buffer, sizeof(buffer), fh_read)) {
        printf(HBLU "%s" CRESET, buffer);
    }
    fclose(fh_read);

    // Separator
    printf("\n\n");

    // Text Placeholder
    fh_read = fopen(DOMESTIK_TEXT, "r");
    if (!fh_read) {
        runTest("Error opening file: int menuDomestic();", RUN_FAILED, __LINE__ - 2);
    }

    while (fgets(buffer, sizeof(buffer), fh_read)) {
        printf(HGRN "%s" CRESET, buffer);
    }

    fclose(fh_read);
    // End Placeholder

    // Separator
    printf("\n");
    

    fh_read = fopen(DOMESTIK_DATA, "r");
    if (!fh_read) {
        runTest("Error opening file: int menuDomestic();", RUN_FAILED, __LINE__ - 2);
    }

        // Komentar Developer: Hasil dari AI
    char lineDATA_DOMESTIK[BUFFER];
    char *foundCountry = NULL;

    while (fgets(lineDATA_DOMESTIK, sizeof(lineDATA_DOMESTIK), fh_read) != NULL) {
        // Check if the line starts with the target country
        if (strncmp(lineDATA_DOMESTIK, Logged_COUNTRY, strlen(Logged_COUNTRY)) == 0 && lineDATA_DOMESTIK[strlen(Logged_COUNTRY)] == ':') {
            foundCountry = lineDATA_DOMESTIK;
            break;
        }
    }
    fclose(fh_read);

    if (foundCountry != NULL) {
        char *start = strchr(foundCountry, '[');
        char *end = strchr(foundCountry, ']');

        if (start != NULL && end != NULL && start < end) {
            char destinations[BUFFER];
            strncpy(destinations, start + 1, end - start - 1);
            destinations[end - start - 1] = '\0'; // Null-terminate the string

            // Tokenize destinations and display to user
            char *token = strtok(destinations, ",");
            int index = 0;
            char city[BUFFER];
            int price;

            printf( 
                HRED "%s:\n" CRESET, Logged_COUNTRY);
            while (token != NULL) {
                sscanf(token, "%[^:]:%d", city, &price); // Split city and price
                printf(HYEL "%d." HBLU " %s: " HGRN "USD %d\n" CRESET, index + 1, city, price);
                token = strtok(NULL, ",");
                index++;
            }

            printf(HYEL "0. " HBLU "Kembali\n" CRESET);

            // Separator
            printf("\n");
            // Get user input for selection
            int input;
            if (isInvalid == "true") { 
                printf(HRED "Piihan tidak valid! " HYEL "Ulangi Pilihan: " CRESET);
            } else {
                printf(HYEL "Pilihan: " CRESET);
            }
            scanf("%d", &input);

            if (input == 0) {
                mainMENU(Logged_USER, Logged_PASS, Logged_COUNTRY, Logged_CITY, HYEL "Welcome back %s!" CRESET, "false");
            }


            // Reset tokenization to retrieve the selected destination
            token = strtok(destinations, ",");
            index = 0;
            // Create a copy of the original destinations string for re-tokenization
            char destinationsCopy[BUFFER];
            strncpy(destinationsCopy, start + 1, end - start - 1);
            destinationsCopy[end - start - 1] = '\0';

            // Reset tokenization to retrieve the selected destination
            token = strtok(destinationsCopy, ",");
            index = 0;

            while (token != NULL) {
                sscanf(token, "%[^:]:%d", city, &price);
                if ( token == NULL ){
                    menuDomestic(Logged_USER, Logged_PASS, Logged_COUNTRY, Logged_CITY, "true");
                }

                if (index + 1 != 0 && index + 1 == input) {
                    konfirmasiTiket(Logged_USER, Logged_PASS, Logged_COUNTRY, Logged_CITY, "false", "domestik", Logged_COUNTRY, city, price);
                    break;
                }
                token = strtok(NULL, ",");
                index++;
            }

        } else {
            perror("Error parsing destinations.");
        }
    } else {
        printf("Country %s not found in file.\n", Logged_COUNTRY);
    }
        // End Komentar Developer

    return 0;
}

fungsiInt menuInternasional(char Logged_USER[], char Logged_PASS[], char Logged_COUNTRY[], char Logged_CITY[], char isInvalid[]) {

    // CLS
    system("cls");

    // Start Placeholder
    fh_read = fopen(INTERNASIONAL, "r");
    if (!fh_read) {
        runTest("Error opening file: int menuInternasional();", RUN_FAILED, __LINE__ - 2);
    }

    char buffer[BUFFER];
    while (fgets(buffer, sizeof(buffer), fh_read)) {
        printf(HBLU "%s" CRESET, buffer);
    }

    fclose(fh_read);

    // Separator
    printf("\n\n");

    // Text Placeholder
    fh_read = fopen(INTERNASIONAL_TEXT, "r");
    if (!fh_read) {
        runTest("Error opening file: int menuInternasional();", RUN_FAILED, __LINE__ - 2);
    }

    while (fgets(buffer, sizeof(buffer), fh_read)) {
        printf(HRED "%s" CRESET, buffer);
    }

    fclose(fh_read);

    // Separator
    printf("\n");

    fh_read = fopen(INTERNASIONAL_DATA, "r");
    if (!fh_read) {
        runTest("Error opening file: int menuInternasional();", RUN_FAILED, __LINE__ - 2);
    }

    char lineLIST_DESTINASI[BUFFER];
    char otherDestinations[BUFFER] = "";
    int index = 0;

    while (fgets(lineLIST_DESTINASI, sizeof(lineLIST_DESTINASI), fh_read) != NULL) {
        char country[BUFFER];
        char city[BUFFER];
        int price;
        // Skip the logged country
        if (strncmp(lineLIST_DESTINASI, Logged_COUNTRY, strlen(Logged_COUNTRY)) != 0 && lineLIST_DESTINASI[strlen(country)] != ':') { // Aku tidak paham???
            sscanf(lineLIST_DESTINASI, "%[^,],%[^:]:%d", country, city, &price);
            printf(HYEL "%d. " HBLU "%s, %s: " HGRN "USD %d\n" CRESET, index + 1, country, city, price);
            index++;
            continue;
        }
    }
    printf(HYEL "0. " HBLU "Kembali\n" CRESET);

    fclose(fh_read);

    fh_read = fopen(INTERNASIONAL_DATA, "r");
    if (!fh_read) {
        runTest("Error opening file: int menuInternasional();", RUN_FAILED, __LINE__ - 2);
    }

    // Separator
    printf("\n");

    // Jika input tidak valid, repeat fungsi dengan output "Pilihan tidak valid! Ulangi pilihan"
    if (isInvalid == "true") { 
        printf(HRED "Piihan tidak valid! " HYEL "Ulangi Pilihan: " CRESET);
    } else {
        printf(HYEL "Pilihan: " CRESET);
    }

    int input;
    scanf("%d", &input);

    if (input == 0) {
        mainMENU(Logged_USER, Logged_PASS, Logged_COUNTRY, Logged_CITY, HYEL "Welcome back %s!" CRESET, "false");
    }


    char lineDestinasi_Dipilih[BUFFER];
    index = 0;
    // Bookmarked
    while (fgets(lineDestinasi_Dipilih, sizeof(lineDestinasi_Dipilih) + 2, fh_read) != NULL) {
        char country[BUFFER];
        char city[BUFFER];
        int price;

        if (strncmp(lineDestinasi_Dipilih, Logged_COUNTRY, strlen(Logged_COUNTRY)) != 0 && lineDestinasi_Dipilih[strlen(country)] != ':') {
            sscanf(lineDestinasi_Dipilih, "%[^,],%[^:]:%d", country, city, &price);
            if (index + 1 == input) {
                konfirmasiTiket(Logged_USER, Logged_PASS, Logged_COUNTRY, Logged_CITY, "false", "internasional", country, city, price);
                break;
            }
            index++;
            continue;
        }
        if (input < 0 || input != index + 1) {   
            menuInternasional(Logged_USER, Logged_PASS, Logged_COUNTRY, Logged_CITY, "true");
        }
    }

    fclose(fh_read);


    // Separator
}

fungsiInt lokasiSekarang(char Logged_USER[], char Logged_PASS[], char Logged_COUNTRY[], char Logged_CITY[], char isInvalid[]) {

    // CLS
    system("cls");

    printf(HYEL "Lokasimu saat ini: " HGRN "%s, %s\n" CRESET, Logged_CITY,Logged_COUNTRY);
    
    // Separator
    printf("\n");

    printf(HYEL "0. " HGRN "Kembali\n" CRESET);

    if (isInvalid != "true") {
        printf(HYEL "Pilihan: " CRESET);
    } else
        printf(HRED "Piihan tidak valid! " HYEL "Ulangi Pilihan: " CRESET);

    // Separator
    printf("\n");

    int input;
    scanf("%d", &input);

    switch (input) {
        case 0:
            mainMENU(Logged_USER, Logged_PASS, Logged_COUNTRY, Logged_CITY, HYEL "Welcome back %s!" CRESET, "false");
            break;
        default:
            lokasiSekarang(Logged_USER, Logged_PASS, Logged_COUNTRY, Logged_CITY, "true");
            break;
    }


}

fungsiInt menuResip(char Logged_USER[], char Logged_PASS[], char Logged_COUNTRY[], char Logged_CITY[], char isInvalid[]) {

    // CLS
    system("cls");

    // Start String Copy

    fh_read = fopen(BUAT_RESI, "r");
    if (!fh_read) {
        runTest("Error opening file: int menuResip();", RUN_FAILED, __LINE__ - 2);
    }

    char buffer[BUFFER];
    while (fgets(buffer, sizeof(buffer), fh_read)) {
        printf(HBLU "%s" CRESET, buffer);
    }

    fclose(fh_read);

    // Separator
    printf("\n");


    printf(HYEL "0. " HGRN "Kembali\n" CRESET);

    if (isInvalid != "true") {
        printf(HYEL "Pilihan: " CRESET);
    } else
        printf(HRED "Piihan tidak valid! " HYEL "Ulangi Pilihan: " CRESET);

    // Separator
    printf("\n");
    
    int input;
    scanf("%d", &input);

    switch (input) {
        case 0:
            mainMENU(Logged_USER, Logged_PASS, Logged_COUNTRY, Logged_CITY, HYEL "Welcome back %s!" CRESET, "false");
            break;
        default:
            lokasiSekarang(Logged_USER, Logged_PASS, Logged_COUNTRY, Logged_CITY, "true");
            break;
    }
}

    // Buat tiket =====================================================================================

fungsiInt pembuatanTiket(char Logged_USER[], char Logged_PASS[], char Logged_COUNTRY[], char Logged_CITY[], char isInvalid[], char tipeTiket[], char tujuanCOUNTRYTiket[], char tujuanCITYTiket[], int hargaTiket, char statusTiket[]) {

    // CLS
    system("cls");

    fh_append = fopen(BUAT_RESI, "a+");
    if (!fh_append) {
        runTest("Error opening file: int pembuatanTiket();", RUN_FAILED, __LINE__ - 2);
    }

    fprintf(fh_append, "USER: %s\nTIPE: %s\nLOKASI: %s, %s\nTUJUAN: %s, %s\nHARGA: %d\nSTATUS: %s\n\n\0", Logged_USER, tipeTiket, Logged_COUNTRY, Logged_CITY, tujuanCOUNTRYTiket, tujuanCITYTiket, hargaTiket, statusTiket = "true" ? "Dibayar" : "Belum Dibayar");
    fclose(fh_append);

    // Ganti isi "userlog_data.txt"
    fh_write = fopen(USER_LOG, "w");
    if (!fh_write) {
        runTest("Error opening file: int pembuatanTiket();", RUN_FAILED, __LINE__ - 2);
    }

    fprintf(fh_write, "isLoggedin:true\nLOGGED_USER:%s\nLOGGED_PASS:%s\nSESSION_COU:%s\nSESSION_CTY:%s\n", Logged_USER, Logged_PASS, tujuanCOUNTRYTiket, tujuanCITYTiket);
    fclose(fh_write);

    // Ganti isi "akun_list.csv"
    fh_read = fopen(AKUN_LIST, "r");
    fh_write = fopen("assets/user_data/akun_list_temp.csv", "w");
    if (!fh_read || !fh_write) {
        runTest("Error opening file: int pembuatanTiket();", RUN_FAILED, __LINE__ - 2);
    }

    char lineAKUN_LIST[BUFFER];
    char field_username[BUFFER], field_password[BUFFER], field_country[BUFFER], field_city[BUFFER];

    fgets(lineAKUN_LIST, sizeof(lineAKUN_LIST), fh_read);
    fputs(lineAKUN_LIST, fh_write);

    while (fgets(lineAKUN_LIST, sizeof(lineAKUN_LIST), fh_read)) {
        sscanf(lineAKUN_LIST, "%[^,],%[^,],%[^,],%s", field_username, field_password, field_country, field_city);

        if (strcmp(field_username, Logged_USER) == 0) {
            fprintf(fh_write, "%s,%s,%s,%s\n", field_username, field_password, tujuanCOUNTRYTiket, tujuanCITYTiket);
        } else {
            fputs(lineAKUN_LIST, fh_write);
        }
    }

    fclose(fh_read);
    fclose(fh_write);

    // Copy into "akun_list.csv"
    fh_rewrite = fopen(AKUN_LIST, "w");
    fh_read = fopen("assets/user_data/akun_list_temp.csv", "r");
    if (!fh_rewrite || !fh_read) {
        runTest("Error opening file: int pembuatanTiket();", RUN_FAILED, __LINE__ - 2);
    }

    while (fgets(lineAKUN_LIST, sizeof(lineAKUN_LIST), fh_read)) {
        fputs(lineAKUN_LIST, fh_rewrite);
    }

    fclose(fh_read);
    fclose(fh_rewrite);

    // Output layar
    printf(HBLU "TIKET BERHASIL DIBUAT\n" CRESET);
    printf(HYEL "RESI:\n" HYEL "    USER: " HBLU "%s\n" HYEL "    TUJUAN: " HRED "%s, %s\n" CRESET, Logged_USER, tujuanCOUNTRYTiket, tujuanCITYTiket, hargaTiket);

    // Separator
    printf("\n\n");

    char input[STANDAR_KOLOM];
    printf(HYEL "Kembali ke menu awal input huruf lalu " HRED "[ENTER]" CRESET);
    scanf("%s", input);

    validasiAkun();
}

fungsiInt konfirmasiTiket(char Logged_USER[], char Logged_PASS[], char Logged_COUNTRY[], char Logged_CITY[], char isInvalid[], char tipeTiket[], char tujuanCOUNTRYTiket[], char tujuanCITYTiket[], int hargaTiket) {
    // Separator
    printf("\n\n");

    printf(HYEL "Apakah anda ingin membeli tiket " HBLU "%s" HYEL " ke " HRED "%s, %s" HYEL " dengan harga " HGRN "USD %d?" CRESET, tipeTiket, tujuanCOUNTRYTiket, tujuanCITYTiket, hargaTiket);

    //Separator
    printf("\n\n");
    printf(HYEL "Input " HRED "[Yes/No]" HYEL ": " CRESET);

    char enterYes[4][STANDAR_KOLOM] = {"Y", "y", "Yes", "yes"};
    char enterNo[4][STANDAR_KOLOM] = {"N", "n", "No", "no"};
    char input[STANDAR_KOLOM];
    scanf("%s", input);

    for (int i = 0; i < 4; i++) {
        if (strcmp(input, enterYes[i]) == 0) {
            pembuatanTiket(Logged_USER, Logged_PASS, Logged_COUNTRY, Logged_CITY, "false", tipeTiket, tujuanCOUNTRYTiket, tujuanCITYTiket, hargaTiket, "true");
            break;
        } else if (strcmp(input, enterNo[i]) == 0) {
            mainMENU(Logged_USER, Logged_PASS, Logged_COUNTRY, Logged_CITY, HYEL "Welcome back %s!" CRESET, "false");
            break;
        }
    }

}




// Sistem Developer ======================================================================================

fungsiVoid devSystem() {
    printf("Dev Mode, Test worked\n");
}

// Debug Fungsi ==========================================================================================

debugFungsiInt runTest(char msg[], char type[], int param) {
    printf("\n\n\n");
    printf(HYEL "Fungsi dijalankan: " HBLU "%s\n" CRESET, __func__);
    if (type != NULL) {
        if (type == RUN_FAILED)
        {
            printf(HYEL "Run Result: " CRESET);
            printf(HRED "%s" CRESET, type);
            if (param != 0) printf( HYEL "  Parameter: " HRED "%d" CRESET, param);
            printf("\n");
            printf(HYEL "Message: " CRESET);
            printf(URED "%s" CRESET, msg);
            return 1;
        } else if (type == RUN_SUCCESS)
        {
            printf(HYEL "Run Result: " CRESET);
            printf(HGRN "%s" CRESET, type);
            printf("\n");
            printf(HYEL "Message: " CRESET);
            printf("%s", msg);
            return 0;
        }
    }
    return 0;
}