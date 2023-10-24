#include <iostream>
#include <wiringPiI2C.h>
#include <wiringPiSPI.h>
#include <wiringPi.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

int main() {
    int fd = wiringPiI2CSetup(0x76); // Initialize BME280 sensor
    if (fd < 0) {
        std::cerr << "Error initializing BME280 sensor." << std::endl;
        return 1;
    }

    int spi_fd = wiringPiSPISetup(0, 500000); // Initialize SPI for Wi-Fi module
    if (spi_fd == -1) {
        std::cerr << "Error initializing SPI for Wi-Fi module." << std::endl;
        return 1;
    }

    while (true) {
        float temperature = 0;
        float humidity = 0;
        float pressure = 0;

        // Read temperature, humidity, and pressure data from the BME280 sensor
        
        // Create a JSON payload with sensor data
        std::string json_payload = "{\"temperature\":" + std::to_string(temperature)
            + ",\"humidity\":" + std::to_string(humidity)
            + ",\"pressure\":" + std::to_string(pressure) + "}";
            
        // Send the JSON payload to a remote server via Wi-Fi
        std::string server_address = "your_server_address";
        int server_port = 80;
        struct sockaddr_in server_info;
        int server_socket;
        server_socket = socket(AF_INET, SOCK_STREAM, 0);
        server_info.sin_family = AF_INET;
        server_info.sin_port = htons(server_port);
        server_info.sin_addr.s_addr = inet_addr(server_address.c_str());
        connect(server_socket, (struct sockaddr *)&server_info, sizeof(server_info));
        send(server_socket, json_payload.c_str(), strlen(json_payload.c_str()), 0);
        close(server_socket);

        std::this_thread::sleep_for(std::chrono::minutes(10)); // Send data every 10 minutes
    }

    return 0;
}
