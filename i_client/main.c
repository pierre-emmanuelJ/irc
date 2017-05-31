#include <unistd.h>

int main(void)
{
    return write(1, "Hello world!\n", 13);
}
