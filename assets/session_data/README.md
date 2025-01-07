# Directory untuk menyimpan data sesi dimana setiap operasi user akan direkam seperti:
    -Log-in, log-out;
    -Lokasi user;
    -Request order user;
    -Data penerbangan;
    -Tagihan;
    -Tiket yang terdaftar.

# Dokumentasi:
## userlog_data.txt
    (CATATAN: Tidak boleh ada whitespace/spasi di antara delimiter ":")
    isLoggedin:(boolean) // Check jika user logged in
    LOGGED_USER:(string) // Nama dari user yang logged in
    LOGGED_PASS:(string) // Password dari user yang logged in
    LOGGED_USID:(integer)// USER ID(berupa integer dimulai dari 0)
    SESSION_COU:(string) // Lokasi negara yang sekarang ditempati user
    SESSION_CTY:(string) // Lokasi kota spesifik dalam negara

## domestik.txt
    Negara:[Kota[0]:Harga,Kota[1]:Harga,Kota[2]:Harga,Kota[3]:Harga]

## internasional.txt
    Negara:[Kota[0]:Harga,Kota[1]:Harga]