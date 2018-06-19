#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

typedef struct Point2D {
    int x;
    int y;
} Point2D;

typedef struct Point3D {
    int x;
    int y;
    int z;
} Point3D;

Point2D point2d(int x, int y);
Point3D point3d(int x, int y, int z);

#endif // POINT_H_INCLUDED
