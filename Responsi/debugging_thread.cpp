#include <iostream>      // Header untuk operasi I/O
#include <thread>        // Header untuk kelas thread
#include <unistd.h>      // Header untuk fungsi sleep

void threadFunction() {
    sleep(1);            // Thread tidur selama 1 detik
    printf("hello\n");   // Mencetak "hello" setelah tidur
}

int main() {
    // Membuat thread baru untuk menjalankan fungsi threadFunction
    std::thread t(threadFunction); // Thread `t` menjalankan fungsi `threadFunction`, Membuat objek thread t yang memulai eksekusi fungsi threadFunction secara paralel.
    
    // Menunggu thread `t` selesai sebelum melanjutkan eksekusi di main
    t.join();            // Memastikan thread selesai sebelum keluar dari `main`
    /*Tanpa t.join(), thread utama dapat keluar lebih cepat dari thread t, yang di mana menyebabkan semua thread yang berjalan berhenti secara paksa,
    bahkan jika mereka belum menyelesaikan pekerjaannya. Dalam kasus ini, pesan "hello" mungkin saja tidak sempat dicetak karena threadFunction tidak selesai
    dengan t.join, thread utama akan berhenti sejenak menunggu thread t menyelesaikan pekerjaannya*/
    return 0;            // Keluar dari program setelah thread selesai
}
