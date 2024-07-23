#ifndef AABB_INCLUDED_H
#define AABB_INCLUDED_H

#include "math3d.h"      // Includes mathematical utilities and types (e.g., Vector3f)
#include "intersectData.h" // Includes definitions for intersection data between objects

/**
 * The AABB class represents an Axis Aligned Bounding Box (AABB).
 * An AABB is used for collision detection and physics simulations as a simple
 * bounding volume that aligns with the coordinate axes.
 */
class AABB
{
public:
    /** 
     * Constructs an AABB with specified minimum and maximum extents.
     * 
     * @param minExtents The corner of the AABB with the smallest coordinates.
     * @param maxExtents The corner of the AABB with the largest coordinates.
     */
    AABB(const Vector3f& minExtents, const Vector3f& maxExtents) :
        m_minExtents(minExtents),
        m_maxExtents(maxExtents) {}

    /**
     * Computes whether this AABB intersects with another AABB.
     *
     * @param other The AABB to test for intersection with this AABB.
     * @return An IntersectData object containing information about the intersection.
     */
    IntersectData IntersectAABB(const AABB& other) const;

    /** Getter for the minimum extents of the AABB */
    inline const Vector3f& GetMinExtents() const { return m_minExtents; }

    /** Getter for the maximum extents of the AABB */
    inline const Vector3f& GetMaxExtents() const { return m_maxExtents; }

private:
    /** The corner of the AABB with the smallest coordinates (minimum extent) */
    const Vector3f m_minExtents;

    /** The corner of the AABB with the largest coordinates (maximum extent) */
    const Vector3f m_maxExtents;
};

#endif // AABB_INCLUDED_H
