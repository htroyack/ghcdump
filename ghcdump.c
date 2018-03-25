#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define COLUMN_SIZE 16

void print_hex_bytes(const unsigned char* bytes, unsigned short bytes_count) {
  int i = 0;

  for (i = 0; i < bytes_count; i++) {
    printf("%02X ", bytes[i]);
    if (i == 7)
      putchar(' ');
  }

  // leave the blanks
  while (i++ < 16) {
    printf("   ");
    if (i == 8)
      putchar(' ');
  }
}

void print_chars(const unsigned char* bytes, unsigned short bytes_count) {
  int i = 0;

  for (i = 0; i < bytes_count; i++) {
    putchar(isprint(bytes[i])? bytes[i] : '.');
  }

  while (i++ < 16)
    putchar(' ');
}

// TODO: what if the offset exceds unsigned int range...
void hexdump(const unsigned char* bytes, unsigned short bytes_count,
  unsigned offset) {
  printf("%08X  ", offset);

  print_hex_bytes(bytes, bytes_count);

  printf(" |");
  print_chars(bytes, bytes_count);
  printf("|\n");
}

int main(int argc, char* argv[]) {
  FILE* infile = NULL;
  size_t bytes_read = 0;
  size_t offset = 0;
  unsigned char bytes[COLUMN_SIZE] = {};

  // TODO: Handle cmdline error
  if (argc != 2)
    exit(1);

  infile = fopen(argv[1], "rb");
  // TODO: write err msg
  if (!infile)
    exit(2);

  do {
    bytes_read = fread(bytes, 1, COLUMN_SIZE, infile);
    hexdump(bytes, bytes_read, offset);
    offset += bytes_read;
  } while (bytes_read > 0);

  fclose(infile);

  return 0;
}
