#include <iostream>
#include <iomanip>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <vector>
#include <fstream>

void saveDataToFile(const std::vector<char>& data) {
    std::ofstream file("ProcessMemoryOutput.txt");
    if (!file) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return;
    }
    for (char c : data) {
        file << c;
    }
    file.close();
    std::cout << "Data saved to file successfully." << std::endl;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <process_id> <memory_address> <data_size>" << std::endl;
        return -1;
    }

    std::string process_id{argv[1]};
    auto memory_address = std::stoull(argv[2], nullptr, 16);
    auto data_size = std::stoull(argv[3]);
    auto mem_file = "/proc/" + process_id + "/mem";

    int file_descriptor = open(mem_file.c_str(), O_RDONLY);
    if (file_descriptor == -1) {
        std::cerr << "Error opening memory file: " << strerror(errno) << std::endl;
        return -2;
    }

    off_t seek_result = lseek(file_descriptor, (off_t)memory_address, SEEK_SET);
    if (seek_result == (off_t)-1) {
        std::cerr << "Error seeking in memory file: " << strerror(errno) << std::endl;
        close(file_descriptor);
        return -3;
    }

    std::vector<char> mem_buffer(data_size);
    ssize_t read_result = read(file_descriptor, mem_buffer.data(), mem_buffer.size());
    if (read_result == -1) {
        std::cerr << "Error reading memory file: " << strerror(errno) << std::endl;
        close(file_descriptor);
        return -4;
    }

    saveDataToFile(mem_buffer);

    return 0;
}
