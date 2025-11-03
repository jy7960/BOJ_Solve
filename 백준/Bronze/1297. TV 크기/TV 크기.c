#include <stdio.h>
#include <math.h>

int main()
{
    double a, b, c;
    scanf("%lf %lf %lf",&a,&b,&c);
    double tmp = sqrt((a*a)/(b*b+c*c));

    printf("%d %d", (int)floor(b*tmp), (int)floor(c*tmp));
    return 0;
}