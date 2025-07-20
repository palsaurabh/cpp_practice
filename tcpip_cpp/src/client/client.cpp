#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>

class TCPClient {
    public:
    bool connectToServer() {
	sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd_ < 0) {
	    perror("Socket creation failed");
	    return false;
	}

	sockaddr_in server_addr{};
	server_addr.sin_family = AF_INET;
	inet_pton(AF_INET, server_ip_.c_str(), &server_addr.sin_addr);
	server_addr.sin_port = htons(port_);

	if (connect(sockfd_, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
	    perror("Connection failed");
	    return false;
	}

	std::cout << "Connected to server at " << server_ip_ << ":" << port_ << "\n";
	return true;
    }

    void sendMessage(const std::string& message) {
	send(sockfd_, message.c_str(), message.size(), 0);
    }

    ~TCPClient() {
	if (sockfd_ >= 0) {
	    close(sockfd_);
	}
    }
    private:
	TCPClient(const std::string& server_ip, int port) : server_ip_(server_ip), port_(port) {}

    int sockfd_ = -1;
    std::string server_ip_;
    int port_;
};