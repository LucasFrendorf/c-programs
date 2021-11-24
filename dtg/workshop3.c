/* Name: Lucas Mørk Frendorf */
/* Group: B201 */
/* Ran using: gcc workshop3.c -ansi -Wall -pedantic && ./a.out && rm a.out */
/* Ran on: Linux [x86_64] */
#include <stdio.h>
#include <stdlib.h>

/* Symbolic constants */
/* int L[10] = {5, 3, 8, 1, 6, 10, 7, 2, 4, 9}; */
int L[8] = {5, 3, 8, 1, 6, 10, 7, 2};
int T[10];

/* Prototypes */
void Merge(int l, int m, int r);
void MergeSort(int l, int r);

int main() { 
   int i, size = (sizeof(L)/sizeof(int))-1;

   printf(" Our array: \n");
   
   for(i = 0; i <= size; i++)
      printf(" %d", L[i]);

   printf("\n\n");

   MergeSort(0, size);

   printf(" Sorted: \n");
   
   for(i = 0; i <= size; i++)
      printf(" %d", L[i]);

   return EXIT_SUCCESS;
}

void MergeSort(int l, int r) {
   int m;
   
   if(l < r) {
      m = (r+l) / 2;

      MergeSort(l, m);
      MergeSort(m+1, r);

      Merge(l, m, r);
   } else { 
      return;
   }   
}

void Merge(int l, int m, int r) {
   int l1 = l, l2 = m+1, i;

   /* Loop until left and right side reaches middel */
   for(i = l; l1 <= m && l2 <= r; i++) {
      /* Compares the 2 values */
      if(L[l1] <= L[l2])
         T[i] = L[l1++];
      else
         T[i] = L[l2++];
   }
   
   /* When we end with a single number (on left side of middle) move it into the array */
   while(l1 <= m)
      T[i++] = L[l1++];

   /* When we end with a single number (on right side of middle) move it into the array */
   while(l2 <= r)
      T[i++] = L[l2++];

   /* Moves our temp array to our real array */
   for(i = l; i <= r; i++)
      L[i] = T[i];
}