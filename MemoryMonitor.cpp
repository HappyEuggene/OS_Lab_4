#include <unistd.h>
#include <iostream>
#include <fstream>
#include <new>

void writeDataToFile(const char* data) {
    std::ofstream file("MemoryMonitorData.txt");
    if (!file) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return;
    }
    file << data;
    file.close();
    std::cout << "Data written to file successfully." << std::endl;
}

int main() {
    const char* message = new (std::nothrow) char[31]{"OS Lab is the best of the best"};
    if (!message) {
        std::cerr << "Failed to allocate memory." << std::endl;
        return 1;
    }

    std::cout << "Process ID: " << getpid()
              << "\nMessage address: " << static_cast<const void*>(message)
              << "\nMessage length: " << sizeof("OS Lab is the best of the best\n") << std::endl;

    writeDataToFile(message);

    std::cin.get();

    delete[] message;
    return 0;
}
