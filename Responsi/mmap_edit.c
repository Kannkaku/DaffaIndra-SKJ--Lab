#include <stdio.h>      // Header untuk fungsi I/O
#include <fcntl.h>      // Header untuk operasi file
#include <sys/mman.h>   // Header untuk fungsi memory mapping
#include <sys/stat.h>   // Header untuk operasi terkait file stat
#include <unistd.h>     // Header untuk fungsi-fungsi sistem POSIX

int main() {
    const char *filename = "hello.txt"; // Nama file yang akan dimodifikasi
    int fd;                             // File descriptor untuk file
    struct stat file_stat;              // Struktur untuk menyimpan informasi file
    char *mapped_file;                  // Pointer ke file yang telah di-memory map
    size_t file_size;                   // Variabel untuk ukuran file

    // Langkah 1: Buka file untuk membaca dan menulis
    fd = open(filename, O_RDWR);        // Membuka file dengan akses baca-tulis
    if (fd == -1) {                     // Jika terjadi error saat membuka file
        perror("Error membuka file");   // Cetak pesan error
        return 1;                       // Keluar dengan kode error
    }

    // Langkah 2: Dapatkan ukuran file
    if (fstat(fd, &file_stat) == -1) {  // Mendapatkan informasi tentang file
        perror("Error mendapatkan ukuran file"); // Cetak pesan error jika gagal
        close(fd);                      // Tutup file sebelum keluar
        return 1;                       // Keluar dengan kode error
    }
    file_size = file_stat.st_size;      // Mengambil ukuran file dari struktur file_stat

    // Langkah 3: Memory-map file
    mapped_file = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_file == MAP_FAILED) {    // Jika memory mapping gagal
        perror("Error mapping file");  // Cetak pesan error
        close(fd);                      // Tutup file sebelum keluar
        return 1;                       // Keluar dengan kode error
    }

    // Langkah 4: Modifikasi isi file
    mapped_file[0] = 'J';               // Mengubah karakter pertama menjadi 'J'

    // Langkah 5: Sinkronisasi perubahan dan pembersihan
    if (msync(mapped_file, file_size, MS_SYNC) == -1) { // Sinkronisasi perubahan ke disk
        perror("Error mensinkronisasi perubahan"); // Cetak pesan error jika gagal
    }
    if (munmap(mapped_file, file_size) == -1) {    // Membebaskan memory mapping
        perror("Error unmapping file");           // Cetak pesan error jika gagal
    }
    close(fd);                                    // Tutup file setelah selesai

    return 0; // Program selesai tanpa error
}
