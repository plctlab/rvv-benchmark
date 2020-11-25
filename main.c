#include <stdbool.h>
#include <stdio.h>

char *strcpy(char *d, const char *s);
char *strncpy(char *d, const char *s, size_t n);
void *vvaddint32(size_t n, const int *x, const int *y, int *z);
void *memcpy(void *dest, const void *src, size_t n);
size_t strlen(const char *str);
void *saxpy(size_t n, const float a, const float *x, float *y);
void *sgemm_nn(size_t n, size_t m, size_t p, const float *a, size_t lda,
               const float *b, size_t ldb, float *c, size_t ldc);

void test_strcpy() {
  #define N 9
  char *src = "ABCDEFGH";
  char dst[N] = "abcdefgh";

  printf(">>> Testing strcpy.s...\n");
  printf(">>> src = %s, dst = %s\n", src, dst);
  strcpy(dst, src);
  printf(">>> after calling strcpy(dst, src):\n");
  printf(">>> src = %s, dst = %s\n", src, dst);

  /* Check result. */
  bool status = true;
  for (int i = 0; i < N; ++i) {
    if (dst[i] != src[i]) {
      status = false;
      break;
    }
  }
  printf(">>> %s\n\n", status ? "Pass!" : "Failed!");
  #undef N
}

void test_strncpy() {
  #define N 3
  char *src = "ABCDEFGH";
  char dst[] = "abcdefgh";

  printf(">>> Testing strncpy.s...\n");
  printf(">>> src = %s, dst = %s\n", src, dst);
  strncpy(dst, src, N);
  printf(">>> after calling strncpy(dst, src, %d):\n", N);
  printf(">>> src = %s, dst = %s\n", src, dst);

  /* Check result. */
  bool status = true;
  for (int i = 0; i < N; ++i) {
    if (dst[i] != src[i]) {
      status = false;
      break;
    }
  }
  printf(">>> %s\n\n", status ? "Pass!" : "Failed!");
  #undef N
}

void test_vvaddint32() {
  #define N 5
  const int x[N]= { 1, 2, 3, 4, 5};
  const int y[N]= { 1, 1, 1, 1, 1};
  int z[N];

  printf(">>> Testing vvaddint32.s...\n");
  printf(">>> x = ");
  for (int i = 0; i < N; i++)
    printf("%d, ", x[i]);
  printf("\n");

  printf(">>> y = ");
  for (int i = 0; i < N; i++)
    printf("%d, ", y[i]);
  printf("\n");

  vvaddint32(N, x, y, z);

  printf(">>> after calling vvaddint32(%d, x, y, z):\n", N);
  printf(">>> z = ");
  for (int i = 0; i < N; i++)
    printf("%d, ", z[i]);
  printf("\n");

  /* Check result. */
  bool status = true;
  for (int i = 0; i < N; ++i) {
    if (z[i] != x[i] + y[i]) {
      status = false;
      break;
    }
  }
  printf(">>> %s\n\n", status ? "Pass!" : "Failed!");
  #undef N
}

void test_memcpy_strlen() {
  char *src = "Hello World!";
  char dst[20];
  size_t len = strlen(src) + 1;

  printf(">>> Testing memcpy.s and strlen.s...\n");
  printf(">>> src = %s\n", src);
  printf(">>> after calling memcpy(dst, src, %zu)\n", len);
  memcpy(dst, src, len);
  printf(">>> dst = %s\n", dst);

  /* Check result. */
  bool status = true;
  for (int i = 0; i < len; ++i) {
    if (dst[i] != src[i]) {
      status = false;
      break;
    }
  }
  printf(">>> %s\n\n", status ? "Pass!" : "Failed!");
}

void test_saxpy() {
  #define N 7
  const float x[N] = {7, 7, 7, 7, 7, 7, 7};
        float y[N] = {1, 1, 1, 1, 1, 1, 1};
  const float z[N] = {15, 15, 15, 15, 15, 15, 15};
  const float a = 2;

  printf(">>> Testing saxpy.s...\n");
  printf(">>> x = ");
  for (int i = 0; i < N; i++)
    printf("%f, ", x[i]);
  printf("\n");

  printf(">>> y = ");
  for (int i = 0; i < N; i++)
    printf("%f, ", y[i]);
  printf("\n");

  printf(">>> a = %f\n", a);

  printf(">>> after calling saxpy(%d, a, x, y)\n", N);
  saxpy(N, a, x, y);

  printf(">>> y = ");
  for (int i = 0; i < N; i++)
    printf("%f, ", y[i]);
  printf("\n");

  /* Check result. */
  bool status = true;
  for (int i = 0; i < N; ++i) {
    if (y[i] != z[i]) {
      status = false;
      break;
    }
  }
  printf(">>> %s\n\n", status ? "Pass!" : "Failed!");
  #undef N
}

void test_sgemm_nn() {
  #define N 16
  #define M 16
  #define K 4
  const float a[M][K] = {
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  };
  const float b[K][N] = {
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  };
  float c[M][N] = {0};

  printf(">>> Testing sgemm.S...\n");
  sgemm_nn(N, M, K, (float*)a, 1, (float*)b, 1, (float*)c, 1);

  /* TODO: Check result. */
  bool status = true;
  // for (int i = 0; i < M; ++i) {
  //   for (int j = 0; j < N; ++j) {
  //     printf("%f, ", c[i][j]);
  //   }
  //   printf("\n");
  // }
  printf(">>> %s\n\n", status ? "Pass!" : "Failed!");
  #undef N
}

int main(void)
{
  printf("\nRunning rvv-benchmark...\n");
  test_strcpy();
  test_strncpy();
  test_vvaddint32();
  test_memcpy_strlen();
  test_saxpy();
  test_sgemm_nn();
}
