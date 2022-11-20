#ifndef RAY_H
#define RAY_H

#include "Elements.h"
#include "Object.h"
#include "Packages.h"

#include <math.h>
#include <stdio.h>

#include "nv_algebra.h"
#include "nv_math.h"

class Ray
{
  public:
    Point pos;
    Point dir;

    Ray(int x, int y);
    Ray(Object* from, Object* to);
    Ray();
    static int intersectSphere(Ray ray, float sphereScale, Point spherePosition, Point* I);
    static int intersectBox(Ray ray, Point min, Point max, Point* hit);
    static int intersectTriangle(Ray ray, vector<Vertex> triangle, Point* I, Point* coords);
    static int intersectRectangle(Ray ray, vector<Vertex> rectangle, Point* I, Point* coords);
    static void intersectPlaneNoBounds(Point a,
                                       Point b,
                                       Point planeNormal,
                                       Point planePosition,
                                       Point* hit);

    virtual ~Ray();
};

#endif
