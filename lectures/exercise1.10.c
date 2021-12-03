#include <stdio.h>

#define PI 3.141592653589793

int main(void)
{
   double radius;

   printf("Dette program udregner arealet af en cirkel.\n\n");

   printf("Radius af cirkel:   ");
   scanf("%lf", &radius);

   printf("\nAreal = PI * radius * radius\n");
   printf("     = %.2f * %.2f * %.2f\n", PI, radius, radius);
   printf("     = %.5f\n", PI * radius * radius );

   return 0;
}