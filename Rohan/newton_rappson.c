#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>


// Function to compute f(x)
double f(double x,double coeff) {
    return (log(x)-log(1-x)+log(10.0)+0.1962-(2*coeff*x));
}

// Function to compute f'(x)
double fprime(double x,double coeff) {
    return ((1/x)+(1/(1-x))-(2*coeff));
}

double newton_raphson(double x,double sigma){

  double tolerance = 1e-6;
  int max_iter = 25000;
  int iter;

  // Iterate until maximum number of iterations is reached or solution is found
  for (iter = 1; iter <= max_iter; iter++) {
     if(x<=0 || x>=1){
        return -9999;
    }
    // Compute function and derivative at current value of x
    double f_val = f(x,sigma);
    double fprime_val = fprime(x,sigma);
    
    // printf("%0.f\t%0.6f",f_val,fprime_val);

    // Check if solution is found or if derivative is zero
    if (fabs(f_val) < tolerance) {
      break;
    } else if (fprime_val == 0.0) {
      printf("Error: derivative is zero\n");
      return 1;
    }

    // Update x using Newton-Raphson formula
    x = x - f_val/fprime_val;
   
  }

  // Print result
//   printf("Solution: %0.9f\n", x);

  return x;
}

int main(void) {

// Declare variables
double tolerance,sigma;
int max_iter, iter;

double delta_l = 0.0;
double avg_l = 0.0;
double x = 0.6;
double result;

  int i,j;

  FILE *fp;

  // Open the file for writing
  fp = fopen("output.dat", "w");

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
            result = newton_raphson(x,sigma);
            if (result!=-9999) {
            fprintf(fp, "%0.6f\t%0.6f\t%0.6f\t%0.9f\n", avg_l,delta_l,sigma,result);
            }
            delta_l = delta_l+0.025;
            // count++;
            // if(count == 2){
            //     exit(0);
          }

    avg_l = avg_l+0.05;
    delta_l = 0.0;
}    
    

fclose(fp);


}
