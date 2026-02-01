#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <optional>
#include <memory>
#include <stdexcept>
#include <thread>

struct server_details {
    int server_fd{-1};
    sockaddr_in server_address;
    ~server_details() {
        if (server_fd != -1)
            close(server_fd);
    }
};
class NetworkingClient {
	public:
	virtual ~NetworkingClient(){}
	virtual void send_data_to_server(std::string_view str) = 0;
	private:
	virtual int connect_to_server() = 0;

};

class TCPClient : public NetworkingClient
{
public:
	TCPClient(server_details details):server_details_(details){
		if(create_client_socket())
			throw std::runtime_error("client socket creation failed.\n");
		if(connect_to_server())		
			throw std::runtime_error("Connection to server failed.\n");
	}

	static server_details fill_server_details(std::string_view address, int port_no){
		server_details details;
		inet_pton(AF_INET, address.data(), &(details.server_address.sin_addr));
		details.server_address.sin_port = htons(port_no);
		details.server_address.sin_family = AF_INET;
		return details;
	}

	void send_data_to_server(std::string_view str) override{
		if(send(clientSocket_, str.data(), str.length(),0) > 0)
			std::cout<<"data was sent\n";
	}

private:

	int connect_to_server() override{
		int status = EXIT_SUCCESS;
		if(connect(clientSocket_, (sockaddr*)(&server_details_.server_address), sizeof(server_details_.server_address)) < 0)
			status = EXIT_FAILURE;
		return status;
	}

	int create_client_socket(){
		int status = EXIT_SUCCESS;
		clientSocket_ = socket(AF_INET, SOCK_STREAM, 0);
		if (clientSocket_ < 0){
			status = EXIT_FAILURE;
			std::cerr<<"client socket creation failed: ";
		}
		return status;
	}

	int clientSocket_;
	server_details server_details_;
};


int main() {
    try {
		server_details details = TCPClient::fill_server_details("127.0.0.1", 8080);
		TCPClient client = TCPClient(details);
		client.send_data_to_server("Hello");
	} catch (const std::exception& e) {
        std::cerr << "Client error: " << e.what() << "\n";
    }

    return 0;
}
