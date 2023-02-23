#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Point_vts{
	double x;
	double y;
};

void getWayPoint(std::vector<Point_vts> &referenceLine)
{
	ifstream myfile("/home/erma/learn-python/jupyter_planning_visualization/testee_way_point.txt");
	if(!myfile){  
        cout << "Unable to open myfile"; 
        exit(1); // terminate with error  	
    }  
    else
    {
		char str[64] = {0};

        while (!myfile.eof())
        {
            Point_vts aPoint;
            myfile.getline (str, 64); //读取一行数据
            double a = 0.0, b = 0.0;
            sscanf(str, "%lf %lf", &a, &b);
            aPoint.x = a;
            aPoint.y = b;
            // printf("aPoint.x = %f, aPoint.y = %f", aPoint.x, aPoint.y);
			referenceLine.push_back(aPoint);
        }
        // double da = 0.0;
        // double db = 0.0;
        // Point_vts aPoint;
        // while(myfile >>  da >> db)
        // {
        //     aPoint.x  = da;
        //     aPoint.y = db;
        //     referenceLine.push_back(aPoint);
        // }
    }
}

int main()
{
    std::string str("784514.07 3352802.07");
    float f1 = 0.0;
    float f2 = 0.0;
    sscanf(str.data(), "%f %f", &f1, &f2);
    printf("f1 = %f, f2 = %f\n", f1, f2);

    double d1 = 0.0;
    double  d2 = 0.0;
    int  i11= 0;
    int  i22 = 0;
    sscanf("1.0 2.0", "%f %f", &d1, &d2);
    sscanf("1 2", "%d %d", &i11, &i22);
    printf("d1 = %f, d2 =%f\n", d1, d2);



    double num1 = 0.0;
    double num2 = 0.0;
    sscanf(str.data(), "%f %f", &num1, &num2);
    printf("num1 = %f, num2= %f\n", num1, num2);
    vector<Point_vts> wayLine;
    getWayPoint(wayLine);
    printf("the wayLine.size = %d\n", wayLine.size());
    for(int i = 0; i < 5; ++i)
    {
        printf("the wayLine.x = %f, y = %f\n", wayLine[i].x, wayLine[i].y);
    }

    return 0;
}