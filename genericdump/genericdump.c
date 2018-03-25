#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define COLUMN_SIZE 16
#define MAX_LABEL   80

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
  FILE* settings = NULL;
  size_t infile_bytes_read = 0;
  size_t infile_offset = 0;
  short bytes_to_read = 0;
  char label[MAX_LABEL] = { 0 };
  unsigned char infile_bytes[COLUMN_SIZE] = {};

  // TODO: Handle cmdline error
  if (argc != 3)
    exit(1);

  infile = fopen(argv[1], "rb");
  // TODO: write err msg
  if (!infile)
    exit(2);

  settings = fopen(argv[2], "rb");
  // TODO: write err msg
  if (!settings) {
    fclose(infile);
    exit(2);
  }

  while (fscanf(settings, "%hd", &bytes_to_read) == 1) {
    if (bytes_to_read > COLUMN_SIZE) {
      break;
    }

    if (fgets(label, MAX_LABEL, settings) != label)  {
      break;
    }

    infile_bytes_read = fread(infile_bytes, 1, bytes_to_read, infile);
    if (infile_bytes_read != bytes_to_read) {
      break;
    }

    printf("(%02d)%s", bytes_to_read, label);
    hexdump(infile_bytes, infile_bytes_read, infile_offset);
    // putchar('\n');

    infile_offset += infile_bytes_read;
  }

  fclose(infile);
  fclose(settings);

  return 0;
}
