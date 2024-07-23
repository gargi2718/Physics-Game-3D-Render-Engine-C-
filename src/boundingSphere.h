#ifndef BOUNDING_SPHERE_INCLUDED_H
#define BOUNDING_SPHERE_INCLUDED_H

#include "math3d.h"      // Includes mathematical utilities and types (e.g., Vector3f)
#include "intersectData.h" // Includes definitions for intersection data between objects

/**
 * The BoundingSphere class represents a sphere that can be used as a collider
 * in a physics engine. It provides functionality to determine intersections
 * with other spheres.
 */
class BoundingSphere
{
public:
    /** 
     * Constructs a BoundingSphere with a specified center and radius.
     * 
     * @param center The center point of the sphere.
     * @param radius The distance from the center to any point on the sphere's surface.
     */
    BoundingSphere(const Vector3f& center, float radius) :
        m_center(center),
        m_radius(radius) {}

    /**
     * Determines if this BoundingSphere intersects with another BoundingSphere.
     *
     * @param other The BoundingSphere to test for intersection with this sphere.
     * @return An IntersectData object containing information about the intersection.
     */
    IntersectData IntersectBoundingSphere(const BoundingSphere& other) const;

    /** Getter for the center point of the sphere */
    inline const Vector3f& GetCenter() const { return m_center; }

    /** Getter for the radius of the sphere */
    inline float GetRadius() const { return m_radius; }

private:
    /** The center point of the sphere in 3D space */
    const Vector3f m_center;

    /** The radius of the sphere, which is the distance from the center to the surface */
    const float m_radius;
};

#endif // BOUNDING_SPHERE_INCLUDED_H
