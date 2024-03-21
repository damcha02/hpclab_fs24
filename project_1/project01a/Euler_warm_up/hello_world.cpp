#include <iostream>
#include <unistd.h>
#include <limits.h>

int main() {
    char hostname[HOST_NAME_MAX];
    gethostname(hostname, HOST_NAME_MAX);

    std::cout << "Hello, World! Running on host: " << hostname << std::endl;
    return 0;
}

