#include "aabb.h"

// This method calculates the intersection data between this  Axis Aligned bounding Box(AABB) and another AABB.
IntersectData AABB::IntersectAABB(const AABB& other) const
{
    // The distance between the AABBs on the X, Y, and Z axes.
    // Computed twice because there are two possible valid distances,
    // depending on the relative locations of the AABBs.
	/*
	These lines calculate the distances between the current AABB (this) and the other AABB on the X, Y, and Z axes.
	distances1 calculates the distances from the minimum extents of the other AABB to the maximum extents of this AABB.
	distances2 calculates the distances from the minimum extents of this AABB to the maximum extents of the other AABB.
	*/
    Vector3f distances1 = other.GetMinExtents() - m_maxExtents;
    Vector3f distances2 = m_minExtents - other.GetMaxExtents();

    // The correct distances will be whichever distance is larger for each axis.
    Vector3f distances = Vector3f(distances1.Max(distances2));

    // Find the maximum distance from the distances vector.
    float maxDistance = distances.Max();
    
    // If there is any distance between the two AABBs, then maxDistance will
    // be greater than or equal to 0. If maxDistance is greater than or equal to 0,
    // it means the AABBs are not intersecting.
    //
    // Therefore, if the AABBs are intersecting, maxDistance must be less than 0.
    return IntersectData(maxDistance < 0, maxDistance);
}
