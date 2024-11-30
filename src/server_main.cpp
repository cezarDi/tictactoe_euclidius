#include "server.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <config_file>" << '\n';
        return 1;
    }
    //Server server("configs/config_server.toml");
    Server server(argv[1]);
    return 0;
}
