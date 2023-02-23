#include <iostream> 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double x = 1;
    double y = 1;
    double angle = atan2(y, x);
    double angle2 = atan2(-y, -x);
    double angle3 = atan(1);
    double angle4 = atan(-1);
    //double angle2 = atan(y,x);
    printf("angle(1,1) = %f, angle(-1,-1)=%f\n", angle*180/M_PI,angle2*180/M_PI);
    printf("angle(1) = %f, angle(-1)=%f\n", angle3*180/M_PI,angle4*180/M_PI);
    return 0;
}