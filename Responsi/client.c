#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_fd; // File descriptor untuk client
    struct sockaddr_in server_addr; // Struktur alamat server
    char buffer[1024] = {0}; // Buffer untuk menerima pesan

    // Langkah 1: Membuat socket
    client_fd = socket(AF_INET, SOCK_STREAM, 0); // Membuat socket dengan IPv4 dan protokol TCP
    if (client_fd < 0) {
        perror("Error membuat socket"); // Tampilkan pesan error jika gagal
        return 1;
    }

    // Langkah 2: Tentukan alamat server
    server_addr.sin_family = AF_INET; // IPv4
    server_addr.sin_port = htons(8080); // Port 8080
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Alamat localhost (127.0.0.1)

    // Langkah 3: Terhubung ke server
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error koneksi ke server"); // Tampilkan pesan error jika gagal
        close(client_fd); // Tutup socket
        return 1;
    }

    // Langkah 4: Terima pesan dari server
    read(client_fd, buffer, sizeof(buffer)); // Baca pesan dari server
    printf("Diterima dari server: %s\n", buffer); // Cetak pesan ke konsol

    // Langkah 5: Tutup koneksi
    close(client_fd); // Tutup socket

    return 0; // Program selesai
}
