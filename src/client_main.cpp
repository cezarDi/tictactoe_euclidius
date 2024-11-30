#include "client.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <config_file>" << '\n';
        return 1;
    }
    //Client client("configs/config_client.toml");
    Client client(argv[1]);

    return 0;
}
