#include <stdio.h>
#include <math.h>
/* Period parameters */
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

static unsigned long mt[N]; /* the array for the state vector  */
static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */

/* initializes mt[N] with a seed */
void init_genrand(unsigned long s)
{
    mt[0]= s & 0xffffffffUL;
    for (mti=1; mti<N; mti++) {
        mt[mti] =
	    (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti);
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
/* slight change for C++, 2004/2/26 */
void init_by_array(unsigned long init_key[], int key_length)
{
    int i, j, k;
    init_genrand(19650218UL);
    i=1; j=0;
    k = (N>key_length ? N : key_length);
    for (; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1664525UL))
          + init_key[j] + j; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++; j++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
        if (j>=key_length) j=0;
    }
    for (k=N-1; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1566083941UL))
          - i; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
    }

    mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */
}

/* generates a random number on [0,0xffffffff]-interval */
unsigned long genrand_int32(void)
{
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= N) { /* generate N words at one time */
        int kk;

        if (mti == N+1)   /* if init_genrand() has not been called, */
            init_genrand(5489UL); /* a default initial seed is used */

        for (kk=0;kk<N-M;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<N-1;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
        mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti = 0;
    }

    y = mt[mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

/* generates a random number on [0,0x7fffffff]-interval */
long genrand_int31(void)
{
    return (long)(genrand_int32()>>1);
}

/* generates a random number on [0,1]-real-interval */
double genrand_real1(void)
{
    return genrand_int32()*(1.0/4294967295.0);
    /* divided by 2^32-1 */
}

/* generates a random number on [0,1)-real-interval */
double genrand_real2(void)
{
    return genrand_int32()*(1.0/4294967296.0);
    /* divided by 2^32 */
}

/* generates a random number on (0,1)-real-interval */
double genrand_real3(void)
{
    return (((double)genrand_int32()) + 0.5)*(1.0/4294967296.0);
    /* divided by 2^32 */
}

/* generates a random number on [0,1) with 53-bit resolution*/
double genrand_res53(void)
{
    unsigned long a=genrand_int32()>>5, b=genrand_int32()>>6;
    return(a*67108864.0+b)*(1.0/9007199254740992.0);
}
/* These real versions are due to Isaku Wada, 2002/01/09 added */


double negExp(double Mean){
    double Y=genrand_real1();
    double X=log(1-Y);
    return ((-Mean)*X);
    
}

int main(void)
{
    double arr1[1000]; //An arry for 1'000 drawings
    double arr2[1000000]; //An arry for 1'000'000 drawings
    double sum1=0; // Is a variable which we need to calculate the avarage for 1'000 drawings
    double sum2=0; // Is a variable which we need to calculate the avarage for 1'000'000 drawings
    double avg1; //Is a variable wich will calculate the avarage for 1'000 drawings
    double avg2; //Is a variable wich will calculate the avarage for 1'000'000 drawings
    for(int i=0;i<1000;i++){
    arr1[i]=negExp(11);
}
    for(int i=0;i<1000000;i++){
    arr2[i]=negExp(11);
}
    for(int i=0;i<1000;i++){
        sum1+=arr1[i];
    }
    for(int i=0;i<1000000;i++){
        sum2+=arr2[i];
    }
    avg1=sum1/1000;
    avg2=sum2/1000000;
    printf("Average obtained after drawing 1'000 is: %f\n", avg1);
    printf("Average obtained after drawing 1'000'000 is: %f\n", avg2);
    
    int testBin[22]; // An arry which test the frequency of numbers between 0 and 1, between 1 and 2,… and between 20 and 21
    for (int i=0;i<22;i++){
        testBin[i]=0;
    }
    for(int i=0;i<1000;i++){
        int BIN=((int) negExp(11)); // A variable which takes the value of fonction negExp and generates only inteeger values
        testBin[BIN]++;
    }
    printf("\n============  Distribution for 1000 drawings  =============\n");
    for(int i=0;i<22;i++){
        printf("%d  ",testBin[i]);
    }
    printf("\n===========  Distribution for 1000000 drawings  ===========\n");
    for(int i=0;i<1000000;i++){
        int BIN=((int) negExp(11));
        testBin[BIN]++;
    }
    for(int i=0;i<22;i++){
        printf("%d  ",testBin[i]);
    }
    
    return 0;
    
}