#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define max_s 256       // Max Number of samples


double complex get_w(int n, int k) ;           // Get Wn^k
void dft(int n, double complex *x ) ;          // Get the n-points DFT
void output(int n, double complex *y) ;        // Show Points, Magnitudes

int main()
{
    while (1)
    {
        printf("Please input integer number which is a power of 2 :\n") ;
        int n;    // Number of samples

        //----------------   TAKING the n input ---------------------------
        char t ;    // this variable will only be used to handle scanf()
        while(1)
        {

            if(scanf("%d%c", &n, &t) != 2 || t != '\n' || ceil(log2(n)) != floor(log2(n)))
            {
                printf("Invalid number, Please input integer number which is a power of 2 :\n") ;
                do
                {t = getchar();}        // Get invalid chars in the buffer
                while (!isdigit(t));
                ungetc(t, stdin);       // Remove them
            }
            else {break ;}
        }
        //-------------------------------------------------------------------

        printf("Please input %d integer numbers which represent the samples :", n) ;
        double complex *x ;                              // The array of entered samples
        x = malloc(sizeof(double complex) * max_s) ;     // Pre-allocated array
        //----------------  TAKING every sample input  --------------------------------------
        int i=0 ;
        for(i=0; i<n; i++)      // Taking n samples
        {
            int input ;         // Correct input
            char t ;            // Only for handling scanf()
            printf("\nx(%d)= ", i) ;
            while(1)
            {
                if(scanf("%d%c", &input, &t) != 2 || t != '\n')
                {
                    printf("Invalid sample, Please enter a valid value of x(%d) :\n", i) ;
                    do
                    {t = getchar();}        // Get invalid chars in the buffer
                    while (!isdigit(t));
                    ungetc(t, stdin);       // Remove them
                }
                else {break ;}
            }

            x[i] = input ;    // Store the correct input
        }
        //---------------------------------------------------------------------------------------

        dft(n, x);          // Get the n-points DFT and store it in X
        output(n, x);       // Output the Points, Phase, Magnitude

        memset(x, 0, sizeof(double complex)* n);   // Delete the memory before proceeding to the next operation
    }
    return 0;
}

void dft(int n, double complex *x)
{

    if (n!=2)
    {
        double complex *xe ;        // Will hold the even samples
        double complex *xo ;        // Will hold the odd samples
        xe = malloc(sizeof(double complex) * max_s / 2) ;
        xo = malloc(sizeof(double complex) * max_s / 2) ;


        int i ;
        for(i=0; i< n/2; i++)
        {
            xe[i] = x[2*i] ;        // Get the even samples
            xo[i] = x[(2*i) + 1] ;  // Get the odd samples
        }

        dft(n/2, xe);               // Get n/2-points DFT for the even side and store it in xe
        dft(n/2, xo);               // Get n/2-points DFT for the odd side and store it in xo

        for (i=0; i<n/2; i++ )    0,1,2,3
        {
            x[i] = xe[i] + get_w(n, i) * xo[i] ;               // x[i] = xe[i] + Wn^k * xe[i]   ==> first half
            x[i+ n/2] = xe[i] + get_w(n, i + n/2) * xo[i] ;    //   ==> second half
        }
        memset(xe, 0, sizeof(double complex)* max_s / 2);       // Resetting Memory
        memset(xo, 0, sizeof(double complex)* max_s / 2);

    }
    else // n=2
    {
        double complex a = x[0]+ x[1];
        double complex b = x[0]- x[1];      // For the 2-points DFT :
        x[0] = a;                           // x[0] = xe[0] + xo[1]
        x[1] = b;                           // x[1] = xe[0] - xo[1]
    }

}


double complex get_w(int n, int k)
{
    return cexp(-I * 2.0 * 22.0 * (double)k / 7.0 / (double)n) ;
}

void output(int n, double complex *y)
{
    int i ;
    // Points
    printf("\nPoints :\t");
    printf("{") ;
    for(i=0; i<n; i++)
    {
        if (cabs(y[i]) < 0.02 ) {printf(" 0,");}     // Print 0 if the magnitude ~= 0
        else
        {
            if (creal(y[i]) > 0.02 || creal(y[i]) < -0.02 ) {printf(" %.2f", creal(y[i]));}
            if (cimag(y[i]) > 0.02 || cimag(y[i]) < -0.02) {printf(" %+.2f J", cimag(y[i]));}
            if (i != n-1) {printf(" , ") ;}
        }

    }
    printf(" }\n") ;

    // Magnitudes
    printf("Magnitudes :\t");
    printf("{") ;
    for(i=0; i<n; i++)
    {
        printf(" %.2f", cabs(y[i]));
        if (i != n-1) {printf(" , ") ;}
    }
    printf(" }\n") ;

    // Phase
    printf("Phases :\t");
    printf("{") ;
    for(i=0; i<n; i++)
    {
        printf(" %.1f", ceil(carg(y[i])* 180.0 *7.0 /22.0) );
        if (i != n-1) {printf(" , ") ;}
    }
    printf(" }\n\n") ;
}


