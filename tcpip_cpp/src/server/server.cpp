// tcp_server.cpp
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <optional>
#include <memory>

constexpr int PORT = 8080;

struct client_details{
    int client_fd{-1};
    sockaddr_in client_address;
    ~client_details(){
        if(client_fd != -1)
            close(client_fd);
    }
};


class PracticeTCPServer {
public:
    static PracticeTCPServer* create(int port) {
        if(server_ != nullptr)
            return server_.get();
        else
        {
            server_ = std::shared_ptr<PracticeTCPServer>(new PracticeTCPServer(port));  
            if(!server_->create_socket())
            {
                throw::std::runtime_error("Create socket failed\n");
            }
            if(!server_->bind_socket(port))
            {
                throw::std::runtime_error("Binding socket failed\n");
            }
            if(!server_->start_listening())
            {
                throw::std::runtime_error("Listening failed\n");
            }
            return server_.get();
        }
    }

    std::optional<client_details> accept_client(){
        client_details details;
        socklen_t len = sizeof(sockaddr_in);
        if((details.client_fd = accept(server_fd_, (sockaddr*)&details.client_address, &len)) < 0){
            return std::nullopt;
        }
        else{
            return std::move(details);
        }
    }

    void read_data(const client_details *details, char *buffer, const int len) {
        if(read(details->client_fd, buffer, len) < 0)
        {
            std::cout << "No data\n";
        }
        else{
            std::cout << "Client says: " << buffer << "\n";
        }
    }

    void send_data(const client_details *details){
        std::string_view response = "Hello from server!";
        send(details->client_fd, response.data(), response.size(), 0);
    }

    ~PracticeTCPServer() {
        if (server_ != nullptr) {
            close(server_->server_fd_);
            // delete server_;
        }
    }

    PracticeTCPServer(PracticeTCPServer& copy) = delete;
    PracticeTCPServer& operator=(const PracticeTCPServer& copy) = delete;
private:
    bool create_socket(){
        if((server_fd_ = socket(AF_INET, SOCK_STREAM, 0)) < 0){
            return false;
        }
        else{
            return true;
        }
    }

    bool bind_socket(int port){
        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_port = htons(port);
        address.sin_addr.s_addr = INADDR_ANY;

        if(bind(server_fd_, (sockaddr*)&address, sizeof(address)) < 0)
        {
            return false;
        }
        else{
            return true;
        }
    }

    bool start_listening(){
        if(listen(server_fd_, 10) < 0)
        {
            return false;
        }
        else{
            return true;
        }
    }

    PracticeTCPServer(int port) : port_(port) {}
    static std::shared_ptr<PracticeTCPServer> server_;
    int server_fd_ = -1;
    int port_;
};

std::shared_ptr<PracticeTCPServer> PracticeTCPServer::server_{nullptr};
// PracticeTCPServer *PracticeTCPServer::server_{nullptr};

int main() {
    try{
        PracticeTCPServer* server = PracticeTCPServer::create(PORT);   
        auto details = server->accept_client();
    }
    catch (const std::runtime_error &e)
    {
        std::cerr<<"Caught a runtime exception: "<<e.what()<<"\n";
    }
    return 0;
}
