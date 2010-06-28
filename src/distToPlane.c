// Find distance of point "p" from plane
// Plane is defined by: "normal" is perpendicular to plane
//                      "point" lies on the plane
#include <math.h>
#include "decl.h"

REAL distToPlane(REAL *normal, REAL *point, REAL *p){
   REAL dist;

   dist = fabs( normal[0]*(p[0] - point[0]) +
                normal[1]*(p[1] - point[1]) +
                normal[2]*(p[2] - point[2]) );
   dist = dist/sqrt(normal[0]*normal[0] + normal[1]*normal[1] +
                    normal[2]*normal[2]);
   return dist;
}
