#include<stdio.h>

char *strcpy(char *d, const char *s);
char *strncpy(char *d, const char *s, size_t n);
void *vvaddint32(size_t n, const int *x, const int *y, int *z);
void *memcpy(void* dest, const void* src, size_t n);
size_t strlen(const char* str);
void *saxpy(size_t n, const float a, const float* x, float* y);
void *sgemm_nn(size_t n, size_t m, size_t p, const float* a, size_t lda, const float* b, size_t ldb, float* c, size_t ldc);

int main(void){

	printf("\033[1m\033[45;33m rvv-benchmark \033[0m\n");
        
	//--------------------------//
	const char srcstr[] = "ABCDEFGH";
              char dststr[] = "abcdefgh";
		
        printf("//strcpy.s ----------------------// \n");
      	strcpy(dststr, srcstr);
	printf(" srcstr[] = ABCDEFGH, dststr[] = abcdefgh, after calling strcpy.s     \n ");
	printf("dststr[] = ");
	printf("%s \n", dststr);
        printf("//strcpy.s Pass ----------------------// \n\n");	

        //---------------------------//
	printf("//strncpy.s---------------------// \n");
	const char srcnstr[] = "ABCDEFGH";
              char dstnstr[] = "abcdefgh";
	strncpy(dstnstr, srcnstr, 3);
	printf(" srcnstr[] = ABCDEFGH, dstnstr[] = abcdefgh, n=3,  after calling strcpy.s     \n ");
        printf("dstnstr[] = ");
	printf("%s \n", dstnstr);
        printf("//strncpy.s Pass ----------------------// \n\n");

        //---------------------------//
       	printf("//vvaddint32.s---------------------// \n");
	size_t n=5;
        const int x[5]= { 1, 2, 3, 4, 5};
	const int y[5]= { 1, 1, 1, 1, 1};
              int z[5];
        vvaddint32(n, x, y, z);
	for(int i=0; i<n; i++)
	printf("%d, ", z[i]);
	printf("\n");
        printf("//vvaddint32.s Pass---------------------// \n\n");

        //---------------------------//
       	printf("//memcpy.s and strlen.s---------// \n");
        char* src="hellowilliam";
	char dest[20];
	size_t m= strlen(src)+1;
	memcpy(dest, src, m);
	printf("%s \n", dest);
        printf("//memcpy.s and strlen.s Pass---------// \n\n");

        //---------------------------//
       	printf("//saxpy.s---------------------// \n");
        const float xx[7] = {7, 7, 7, 7, 7, 7, 7};
              float yy[7] = {1, 1, 1, 1, 1, 1, 1};
	const float a=2;
	size_t p=7;
	saxpy(p, a, xx, yy);
	for(int i=0; i<p; i++)
        printf("%f, ", yy[i]);
        printf("\n");
        printf("//saxpy.s Pass---------------------// \n\n");
       
        //---------------------------//
	printf("//sgemm.S---------------------// \n");
        unsigned int n1 = 16;
        unsigned int m1 = 16;
        unsigned int k1 = 2;

        const float a1[16][2] = {0.7, 1.6, 0.1, 0.2, 1.1, 1.2, 1.1, 0.0, 
		                0.3, 0.1, 0.1, 0.7, 0.2, 0.2, 0.5, 2.1,
			       	0.1, 0.1, 1.0, 0.0, 0.0, 0.8, 0.2, 1.3,
			       	0.7, 1.6, 0.6, 0.8, 1.2, 1.5, 1.4, 0.3,};

        const float b1[2][16] = {1.7, 0.1, 0.3, 0.7, 0.3, 0.5, 0.9, 1.1,
                                2.2, 0.6, 1.7, 0.4, 1.1, 1.4, 1.2, 1.8,
                                2.1, 1.4, 0.9, 1.2, 0.8, 0.6, 0.4, 1.2,
                                0.7, 0.2, 0.7, 0.8, 0.1, 1.0, 0.2, 0.1};

	float c1[16][16] = { 0 };
 
        size_t lda = 1;
        size_t ldb = 1;
        size_t ldc = 1;

        sgemm_nn(n1, m1, k1, &a1[0][0], lda, &b1[0][0], ldb, &c1[0][0], ldc);
        printf("//sgemm.S Pass---------------------// \n\n");

	return 0;
}
