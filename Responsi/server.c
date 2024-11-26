#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, client_fd; // File descriptor untuk server dan client
    struct sockaddr_in server_addr, client_addr; // Struktur alamat untuk server dan client
    socklen_t client_len = sizeof(client_addr); // Ukuran alamat client
    char *message = "Hello, Client!"; // Pesan yang dikirim ke client

    // Langkah 1: Membuat socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0); // Membuat socket dengan IPv4 dan protokol TCP
    if (server_fd < 0) {
        perror("Error membuat socket"); // Tampilkan pesan error jika gagal
        return 1;
    }

    // Langkah 2: Bind socket ke port 8080
    server_addr.sin_family = AF_INET; // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY; // Mendengarkan pada semua interface
    server_addr.sin_port = htons(8080); // Port 8080, diubah ke network byte order
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error bind socket"); // Tampilkan pesan error jika gagal
        close(server_fd); // Tutup socket
        return 1;
    }

    // Langkah 3: Listen untuk koneksi masuk
    if (listen(server_fd, 5) < 0) { // Maksimum 5 koneksi antrian
        perror("Error listen koneksi"); // Tampilkan pesan error jika gagal
        close(server_fd); // Tutup socket
        return 1;
    }
    printf("Server mendengarkan di port 8080...\n");

    // Langkah 4: Terima koneksi
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len); // Menerima koneksi dari client
    if (client_fd < 0) {
        perror("Error menerima koneksi"); // Tampilkan pesan error jika gagal
        close(server_fd); // Tutup socket
        return 1;
    }

    // Langkah 5: Kirim pesan ke client
    write(client_fd, message, strlen(message)); // Kirim pesan ke client melalui socket client_fd

    // Langkah 6: Tutup koneksi
    close(client_fd); // Tutup koneksi client
    close(server_fd); // Tutup socket server

    return 0; // Program selesai
}
