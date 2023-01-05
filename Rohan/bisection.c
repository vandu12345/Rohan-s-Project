#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>



// Function to compute f(x)
double f(double x,double coeff) {
    return (log(x)-log(1-x)+log(10.0)+0.1962-(2*coeff*x));
}

double bisection(double sigma) {
  double fa,fc;
  double fb,c;
  double tolerance = 1e-6;
  double a = tolerance;
  double b = 1-tolerance; 
  fa = f(a,sigma);
  fb = f(b,sigma);

  while (fabs(b - a) > tolerance) {
    c = (a + b) / 2;
    fc = f(c,sigma);

    if (fa * fc < 0) {
      b = c;
      fb = fc;
    } else {
      a = c;
      fa = fc;
    }
  }

  return c;
}

int main(void) {

// Declare variables
double tolerance,sigma;
int max_iter, iter;

double delta_l = 0.0;
double avg_l = 0.0;
double result;

  int i,j;

  FILE *fp;

  // Open the file for writing
  fp = fopen("spinglass_bisection.dat", "w");

    if (fp == NULL) {
    printf("Error: Could not open file\n");
    return 1;
  }

 int count = 0;

  for(i=0; i<100; i++) 
  {
        for(j=0; j<100; j++) 
        {
            sigma = (avg_l-(pow(delta_l,2)/2.0));
            result = bisection(sigma);
            fprintf(fp, "%0.6f\t%0.6f\t%0.6f\t%0.9f\n", avg_l,delta_l,sigma,result);
            delta_l = delta_l+0.025;
        }

    avg_l = avg_l+0.05;
    delta_l = 0.0;
}    
    

fclose(fp);


}
