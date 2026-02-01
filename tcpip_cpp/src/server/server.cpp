#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <optional>
#include <memory>
#include <stdexcept>
#include <thread>

constexpr int PORT = 8080;

struct client_details {
    int client_fd{-1};
    sockaddr_in client_address;

    ~client_details() {
        if (client_fd != -1)
            close(client_fd);
    }
};

class PracticeTCPServer {
public:
    static PracticeTCPServer* create(int port) {
        if (server_ != nullptr)
            return server_.get();

        server_ = std::unique_ptr<PracticeTCPServer>(new PracticeTCPServer(port));

        if (!server_->create_socket()) {
            throw std::runtime_error("Create socket failed");
        }

        if (!server_->bind_socket(port)) {
            throw std::runtime_error("Binding socket failed");
        }

        if (!server_->start_listening()) {
            throw std::runtime_error("Listening failed");
        }

        return server_.get();
    }

    static PracticeTCPServer* instance() {
        return server_.get();
    }

    std::optional<client_details> accept_client() {
        client_details details;
        socklen_t len = sizeof(sockaddr_in);
        if ((details.client_fd = accept(server_fd_, (sockaddr*)&details.client_address, &len)) < 0) {
            return std::nullopt;
        } else {
            return details;
        }
    }

    void read_data(const client_details* details, char* buffer, const int len) {
        if (read(details->client_fd, buffer, len) < 0) {
            std::cout << "No data\n";
        } else {
            std::cout << "Client says: " << buffer << "\n";
        }
    }

    void send_data(const client_details* details) {
        std::string_view response = "Hello from server!";
        send(details->client_fd, response.data(), response.size(), 0);
    }

    ~PracticeTCPServer() {
        if (server_fd_ != -1) {
            close(server_fd_);
        }
    }

    PracticeTCPServer(PracticeTCPServer& copy) = delete;
    PracticeTCPServer& operator=(const PracticeTCPServer& copy) = delete;

private:
    bool create_socket() {
        server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
        return server_fd_ >= 0;
    }

    bool bind_socket(int port) {
        sockaddr_in address{};
        address.sin_family = AF_INET;
        address.sin_port = htons(port);
        address.sin_addr.s_addr = INADDR_ANY;

        return bind(server_fd_, (sockaddr*)&address, sizeof(address)) >= 0;
    }

    bool start_listening() {
        return listen(server_fd_, 10) >= 0;
    }

    PracticeTCPServer(int port) : port_(port) {}

    static std::unique_ptr<PracticeTCPServer> server_;
    int server_fd_ = -1;
    int port_;
};

// Static member initialization
std::unique_ptr<PracticeTCPServer> PracticeTCPServer::server_{nullptr};


int main() {
    try {
        auto* server = PracticeTCPServer::create(PORT);
        int client_no = 0;
        while(1){
            auto client = server->accept_client();
            client_no++;
            if (client.has_value()) {
                std::thread client_thread([details = std::move(*client), server, client_no](){
                    char buffer[1024] = {0};
                    server->read_data(&(details), buffer, sizeof(buffer));
                    server->send_data(&(details));
                    std::cout<<"client_no :"<<client_no<<"\n";
                });
                client_thread.detach();
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << "\n";
    }

    return 0;
}
