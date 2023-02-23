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

//����
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

//�����
typedef struct Polygon
{
	int32 vertexCount;  //��������
	Vect vertexes[4];  //��������

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

//����
typedef struct Rectangle
{
	float left, right, top, bottom;
} Rectangle;

//���ι�����
static inline Rectangle rectMake(float left, float right, float top, float bottom)
{
	Rectangle r = {left, right, top, bottom};
	return r;
}

//����������
static inline Vect vectMake(float x, float y)
{
	Vect v(x, y);
	return v;
}

//�������
static inline float vectDot(Vect v1, Vect v2)
{
	return v1.x*v2.x + v1.y*v2.y;
}

//��������
static inline Vect vectSub(Vect v1, Vect v2)
{
	return vectMake(v1.x - v2.x, v1.y - v2.y);
}

//��������
static inline float vectLength(Vect v)
{
	return sqrt(v.x*v.x + v.y*v.y);
}


//�����Ĵ�ֱ����
static inline Vect vectPerp(Vect v)
{
	return vectMake(-v.y, v.x);
}

//��������ƽ��
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


//��������ͶӰ�þ���

static inline float intervalDistance(float minA, float maxA, float minB, float maxB)
{
	return (minA < minB) ? (minB - maxA) : (minA - maxB);
}

/*
* �������������Ƿ���ײ����ײ����true������ײ����false
* ����������͹����Σ�������α����ֳɶ��͹����λ�������
*/
bool polygonCollision(Polygon a, Polygon b)
{
	Vect edge, axis;
	float minA = 0, maxA = 0, minB = 0, maxB = 0;

	for (int32 i = 0, j=a.vertexCount-1; i < a.vertexCount + b.vertexCount; j=i, i++)
	{
		//ͨ������ȡ��ÿ����
		if (i < a.vertexCount)
		{
			edge = vectSub(a.vertexes[i], a.vertexes[j]);
		}
		else
		{
			edge = vectSub(b.vertexes[i-a.vertexCount], b.vertexes[j-a.vertexCount]);
		}

		axis = vectPerp(edge); //�����Ĵ�ֱ����

		//�ԱߵĴ���Ϊ���������ͶӰ��ȡ��ͶӰ�߶�[min, max]
		projectPolygon(axis, a, &minA, &maxA);
		projectPolygon(axis, b, &minB, &maxB);

		//�������ͶӰ�ľ��룬�����ͶӰû���غϲ��֣���ô�����ж������������û����ײ
		if (intervalDistance(minA, maxA, minB, maxB) > 0)
		{
			return false;
		}
	}


	return true;
}

//Բ��
typedef struct Circle
{
	Vect  o; // Բ������
	float r; //�뾶

	Circle(Vect v, float radii)
	{
		o = v;
		r = radii;
	}
} Circle;

/*
 * ����Բ��circle��������axis�ϵ�ͶӰ���õ���Сֵmin�����ֵmax
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

		//�ԱߵĴ���Ϊ���������ͶӰ��ȡ��ͶӰ�߶�[min, max]
		projectPolygon(axis, p, &minP, &maxP);
		projectCircle(axis, c, &minC, &maxC);

		//printf("%.2f\n", intervalDistance(minP, maxP, minC, maxC));

		//�������ͶӰ�ľ��룬�����ͶӰû���غϲ��֣���ô�����ж�������ͼ��û����ײ
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