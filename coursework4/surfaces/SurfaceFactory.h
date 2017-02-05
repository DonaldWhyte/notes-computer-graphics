#ifndef SURFACE_FACTORY_H
#define SURFACE_FACTORY_H

#include "../util/Vector3.h"
#include "../util/Geometry.h"
#include "Surface.h"

/* Factory class which can generate a variety of different surfaces. */
class SurfaceFactory
{

public:
    SurfaceFactory(bool showPoints = false, bool showLines = false,
        bool generateRandomColours = false);
	Surface* createCylinder(float height, float radius, int numSegments);
	Surface* createCone(float height, float radius, int numSegments);
	Surface* createBox(float width, float height, float length);
	Surface* createSphere(float radius, int numRings, int numQuadsPerRing);

private:
    Surface* generateSurface(const VertexList& verts, const TriangleList& tris);

    TexCoord computeSphereTexCoord(const Vector3& posOnSphere);
    // Default parameters to set to generated surfaces
    bool showPoints;
    bool showLines;    
    bool generateRandomColours;

};

#endif
