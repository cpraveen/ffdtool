#ifndef _DECL_H_
#define _DECL_H_

#include "type.h"
#include "mesh.h"
#include "ffd.h"

#define min(a,b)  ( (a) < (b) ? (a) : (b) )
#define max(a,b)  ( (a) > (b) ? (a) : (b) )

void ReadMesh(MESH*);
void WriteMesh(MESH*);
void ReadFFD(FFD*);
void WriteFFDBox(FFD*);
void CheckFFDBox(FFD_BOX*);
void ReadFFDVar(FFD*);
REAL** RealArray2(UINT, UINT);
void DelRealArray2(UINT nx, REAL**);
REAL*** RealArray3(UINT, UINT, UINT);
void CountFFDVar(FFD*);
void DeformMesh(MESH*, FFD*);
UINT IsInside(REAL, REAL, REAL, FFD_BOX*, UINT*, UINT*, UINT*);
void MinMaxRangeFFD(FFD_BOX*);
void FFDCoord(REAL, REAL, REAL, FFD_BOX*, UINT, UINT, UINT, REAL*);
void rootFun(REAL, REAL, REAL, REAL*, REAL*, REAL*, REAL*, REAL*);
void rootFunJac(REAL*, REAL*, REAL*, REAL*, REAL**);
void Gaussj(double **a, int n, double *b);

void Bezier3D(SHAPE_PARAM *var, REAL *t, REAL *dr);
void NodeMove(FFD *ffd, REAL *t, REAL *dr);
REAL decas(UINT degree, REAL coeff[], REAL t);

#endif
