/*
*  SeparatingAxisTheorem.h
*  CollisionDetect
*
*  Created by George on 12/24/09.
*  Copyright 2009 __MyCompanyName__. All rights reserved.
*
*/

#include <stdio.h>
#include <stdio.h>
#include <math.h>
//#include <CoreGraphics/CoreGraphics.h>

typedef int int32;

//向量
typedef struct Vect
{
	float x,y;
	Vect()
	{}
	Vect(int32 Cx, int32 Cy)
	{
		x = Cx;
		y = Cy;
	}
} Vect;

//多边形
typedef struct Polygon
{
	int32 vertexCount;  //顶点数量
	Vect vertexes[4];  //顶点数组

	Polygon()
	{
		vertexCount = 4;
	}
	Polygon(Vect v1, Vect v2, Vect v3, Vect v4)
	{
		vertexCount = 4;
		vertexes[0] = v1;
		vertexes[1] = v2;
		vertexes[2] = v3;
		vertexes[3] = v4;
	}

} Polygon;

//矩形
typedef struct Rectangle
{
	float left, right, top, bottom;
} Rectangle;

//矩形构造器
static inline Rectangle rectMake(float left, float right, float top, float bottom)
{
	Rectangle r = {left, right, top, bottom};
	return r;
}

//向量构造器
static inline Vect vectMake(float x, float y)
{
	Vect v(x, y);
	return v;
}

//向量点乘
static inline float vectDot(Vect v1, Vect v2)
{
	return v1.x*v2.x + v1.y*v2.y;
}

//向量减法
static inline Vect vectSub(Vect v1, Vect v2)
{
	return vectMake(v1.x - v2.x, v1.y - v2.y);
}

//向量长度
static inline float vectLength(Vect v)
{
	return sqrt(v.x*v.x + v.y*v.y);
}


//向量的垂直向量
static inline Vect vectPerp(Vect v)
{
	return vectMake(-v.y, v.x);
}

//两点距离的平方
static inline float disSquare(Vect p1, Vect p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

static inline void projectPolygon(Vect axis, Polygon polygon, float* min, float* max)
{
	float d = vectDot(axis, polygon.vertexes[0]);
	*min = d;
	*max = d;
	for (int32 i = 0; i < polygon.vertexCount; i++)
	{
		d = vectDot(axis, polygon.vertexes[i]);
		if (d < *min)
		{
			*min = d;
		}
		else
		{
			if (d > *max)
			{
				*max = d;
			}
		}
	}
}


//计算两个投影得距离

static inline float intervalDistance(float minA, float maxA, float minB, float maxB)
{
	return (minA < minB) ? (minB - maxA) : (minA - maxB);
}

/*
* 检测两个多边形是否碰撞，碰撞返回true，不碰撞返回false
* 必须是两个凸多边形，凹多边形必须拆分成多个凸多边形或三角形
*/
bool polygonCollision(Polygon a, Polygon b)
{
	Vect edge, axis;
	float minA = 0, maxA = 0, minB = 0, maxB = 0;

	for (int32 i = 0, j=a.vertexCount-1; i < a.vertexCount + b.vertexCount; j=i, i++)
	{
		//通过顶点取得每个边
		if (i < a.vertexCount)
		{
			edge = vectSub(a.vertexes[i], a.vertexes[j]);
		}
		else
		{
			edge = vectSub(b.vertexes[i-a.vertexCount], b.vertexes[j-a.vertexCount]);
		}

		axis = vectPerp(edge); //向量的垂直向量

		//以边的垂线为坐标轴进行投影，取得投影线段[min, max]
		projectPolygon(axis, a, &minA, &maxA);
		projectPolygon(axis, b, &minB, &maxB);

		//检查两个投影的距离，如果两投影没有重合部分，那么可以判定这两个多边形没有碰撞
		if (intervalDistance(minA, maxA, minB, maxB) > 0)
		{
			return false;
		}
	}


	return true;
}

//圆形
typedef struct Circle
{
	Vect  o; // 圆心坐标
	float r; //半径

	Circle(Vect v, float radii)
	{
		o = v;
		r = radii;
	}
} Circle;

/*
 * 计算圆形circle在坐标轴axis上得投影，得到最小值min和最大值max
 */
static inline void projectCircle(Vect axis, Circle circle, float* min, float* max)
{
	float d = vectDot(axis, circle.o);
	float axisLength = vectLength(axis);
	*min = d - (circle.r * axisLength);
	*max = d + (circle.r * axisLength);
}


bool polygonCircleCollision(Polygon p, Circle c)
{
	Vect edge, axis;
	float minP = 0, maxP = 0, minC = 0, maxC = 0;

	for(int i = 0, j=p.vertexCount-1; i < p.vertexCount; j=i, i++)
	{
		edge = vectSub(p.vertexes[i], p.vertexes[j]);
		axis = vectPerp(edge); // perpendicular to edge     

		//以边的垂线为坐标轴进行投影，取得投影线段[min, max]
		projectPolygon(axis, p, &minP, &maxP);
		projectCircle(axis, c, &minC, &maxC);

		//printf("%.2f\n", intervalDistance(minP, maxP, minC, maxC));

		//检查两个投影的距离，如果两投影没有重合部分，那么可以判定这两个图形没有碰撞
		if (intervalDistance(minP, maxP, minC, maxC) > 0)
		{
			return false;
		}
	}

	for(int i = 0; i < p.vertexCount; i++)
	{
		axis = vectSub(c.o, p.vertexes[i]);

		projectPolygon(axis, p, &minP, &maxP);
		projectCircle(axis, c, &minC, &maxC);

		//printf("%.2f\n", intervalDistance(minP, maxP, minC, maxC));

		if (intervalDistance(minP, maxP, minC, maxC) > 0)
		{
			return false;
		}
	}

	return true;
}

bool circleCollision(Circle c1, Circle c2)
{
	float dis = (c1.o.x - c2.o.x) * (c1.o.x - c2.o.x) +  (c1.o.y - c2.o.y) * (c1.o.y - c2.o.y);
	if (dis > (c1.r + c2.r) * (c1.r + c2.r))
	{
		return false;
	}
	else
	{
		return true;
	}
}

int main()
{
	Polygon p1( Vect(0,1), Vect(0,0), Vect(2,1), Vect(2,0) );
	Circle c1(Vect(3,1), 0.4);
	
	bool is_collision = polygonCircleCollision(p1, c1);

	Circle c2(Vect(1,1), 0.4);
	
	bool cc_collision = circleCollision(c1, c2);

	return 0;
}