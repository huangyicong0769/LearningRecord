#include <stdio.h>
#include <math.h>

int main(void)
{   
      int count = 0, number;
      scanf ("%d", &number);
      int t_number = number;
      if(t_number < 0) {
            t_number = -t_number; 
      }   
      while(t_number != 0){       
          count++;
          t_number = t_number / 10;
      };
      printf("%d\n", count);
}
