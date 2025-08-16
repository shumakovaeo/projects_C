#include<stdio.h>
#include<math.h>

int main(void)
{
    double x;
    if ((scanf("%lf", &x) == 1) && (x > 0))
    { 
        double y, t = 1 / 3;
    
        y = 7e-3 * pow(x,4.0) + ((22.8 * pow(x, t) - 1e3) * x + 3) / (x * x / 2)  - x * pow((10.0 + x),(2.0/x)) - 1.01;
        printf("%.1f", y);
        
    }   
    
    else
    {
        printf("n/a");
    }
    
    return 0;
}