#include "boundingSphere.h"

IntersectData BoundingSphere::IntersectBoundingSphere(const BoundingSphere& other) const
{
    // The radius of a sphere is the distance from any point on the sphere
    // to its center. By adding the radii of two spheres together, we get
    // the distance between the centers of the spheres if they were just touching.
    float radiusDistance = m_radius + other.GetRadius();
    
    // Compute the distance between the centers of the two spheres.
    // GetCenter() returns the center position of the sphere.
    // Subtracting the centers of the two spheres gives the vector between them,
    // and Length() computes the magnitude of this vector, which is the distance.
    float centerDistance = (other.GetCenter() - m_center).Length();

    // The distance between the centers of the spheres when they are touching
    // is given by radiusDistance. To get the actual distance between the
    // surfaces of the two spheres, subtract radiusDistance from centerDistance.
    float distance = centerDistance - radiusDistance;

    // Spheres intersect if the distance between their surfaces is less than 0.
    // If distance is less than 0, the spheres are intersecting.
    // Return an IntersectData object with a boolean indicating intersection status
    // and the calculated distance between the spheres.
    return IntersectData(distance < 0, distance);
}
