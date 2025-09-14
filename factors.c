#include <gmp.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void factors(mpz_ptr n) {
  size_t counter = 0;
  mpz_ptr a, b = NULL;
  mpz_t b1, b2, rn, tmp;
  mpz_inits(b1, b2, rn, tmp, NULL);
  mpz_sqrt(rn, n);
  if (!mpz_perfect_square_p(n)) {
    mpz_add_ui(rn, rn, 1);
  }
  mpz_set_ui(b1, 2);
  mpz_set(b2, rn);
  for (; counter <= 100; counter++) {
    mpz_mod(tmp, n, b1);
    if (mpz_cmp_ui(tmp, 0) == 0) {
      mpz_div(tmp, n, b1);
      a = tmp;
      b = b1;
      break;
    }
    mpz_mod(tmp, n, b2);
    if (mpz_cmp_ui(tmp, 0) == 0) {
      mpz_div(tmp, n, b2);
      b = tmp;
      a = b2;
      break;
    }
    mpz_add_ui(b1, b1, 1);
    mpz_add_ui(b2, b2, 1);
  }
  printf("%lu=%lu*%lu\n", mpz_get_ui(n), mpz_get_ui(a), mpz_get_ui(b));
  mpz_clears(b1, b2, rn, tmp);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    return EXIT_FAILURE;
  }
  char *filename = argv[1];
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }
  char *line = NULL;
  size_t size = 0;
  mpz_t n;
  mpz_init(n);
  while (getline(&line, &size, file) != -1) {
    mpz_set_str(n, line, 10);
    factors(n);
  }
  mpz_clear(n);
  free(line);
  fclose(file);
  return EXIT_SUCCESS;
}
