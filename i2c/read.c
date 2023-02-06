/*

  read.c
  Eric Klavins

  gcc read.c -li2c -o read

  Example usage:
  sudo ./read 0x12

*/

#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
#include <unistd.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Derived from https://stackoverflow.com/questions/111928
void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
        printf(" ");
    }
}

// Derived from https://docs.kernel.org/i2c/dev-interface.html
int main(int argc, char * argv[]) {

  int file;
  char filename[20] = "/dev/i2c-1";

  file = open(filename, O_RDWR);
  assert(file >= 0);

  int addr = 0x4a;
  assert (ioctl(file, I2C_SLAVE, addr) >= 0);

  __s32 res;
  __u8 reg = strtol(argv[1], NULL, 16);

  res = i2c_smbus_read_byte_data(file, reg);
  printf("Register 0x%.2x, ", reg);
  printBits(1, &res);
  printf("\n");

  return 0;

}