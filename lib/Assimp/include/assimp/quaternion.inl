/** @file  aiQuaterniont.inl
 *  @brief Inline implementation of aiQuaterniont<TReal> operators
 */
#ifndef AI_QUATERNION_INL_INC
#define AI_QUATERNION_INL_INC

#ifdef __cplusplus
#include "quaternion.h"

// ---------------------------------------------------------------------------
template<typename TReal>
bool aiQuaterniont<TReal>::operator== (const aiQuaterniont& o) const
{
	return x == o.x && y == o.y && z == o.z && w == o.w;
}

// ---------------------------------------------------------------------------
template<typename TReal>
bool aiQuaterniont<TReal>::operator!= (const aiQuaterniont& o) const
{
	return !(*this == o);
}



// ---------------------------------------------------------------------------
// Constructs a quaternion from a rotation matrix
template<typename TReal>
inline aiQuaterniont<TReal>::aiQuaterniont( const aiMatrix3x3t<TReal> &pRotMatrix)
{
	TReal t = 1 + pRotMatrix.a1 + pRotMatrix.b2 + pRotMatrix.c3;

	// large enough
	if( t > static_cast<TReal>(0.001))
	{
		TReal s = sqrt( t) * static_cast<TReal>(2.0);
		x = (pRotMatrix.c2 - pRotMatrix.b3) / s;
		y = (pRotMatrix.a3 - pRotMatrix.c1) / s;
		z = (pRotMatrix.b1 - pRotMatrix.a2) / s;
		w = static_cast<TReal>(0.25) * s;
	} // else we have to check several cases
	else if( pRotMatrix.a1 > pRotMatrix.b2 && pRotMatrix.a1 > pRotMatrix.c3 )  
	{	
		// Column 0: 
		TReal s = sqrt( static_cast<TReal>(1.0) + pRotMatrix.a1 - pRotMatrix.b2 - pRotMatrix.c3) * static_cast<TReal>(2.0);
		x = static_cast<TReal>(0.25) * s;
		y = (pRotMatrix.b1 + pRotMatrix.a2) / s;
		z = (pRotMatrix.a3 + pRotMatrix.c1) / s;
		w = (pRotMatrix.c2 - pRotMatrix.b3) / s;
	} 
	else if( pRotMatrix.b2 > pRotMatrix.c3) 
	{ 
		// Column 1: 
		TReal s = sqrt( static_cast<TReal>(1.0) + pRotMatrix.b2 - pRotMatrix.a1 - pRotMatrix.c3) * static_cast<TReal>(2.0);
		x = (pRotMatrix.b1 + pRotMatrix.a2) / s;
		y = static_cast<TReal>(0.25) * s;
		z = (pRotMatrix.c2 + pRotMatrix.b3) / s;
		w = (pRotMatrix.a3 - pRotMatrix.c1) / s;
	} else 
	{ 
		// Column 2:
		TReal s = sqrt( static_cast<TReal>(1.0) + pRotMatrix.c3 - pRotMatrix.a1 - pRotMatrix.b2) * static_cast<TReal>(2.0);
		x = (pRotMatrix.a3 + pRotMatrix.c1) / s;
		y = (pRotMatrix.c2 + pRotMatrix.b3) / s;
		z = static_cast<TReal>(0.25) * s;
		w = (pRotMatrix.b1 - pRotMatrix.a2) / s;
	}
}

// ---------------------------------------------------------------------------
// Construction from euler angles
template<typename TReal>
inline aiQuaterniont<TReal>::aiQuaterniont( TReal fPitch, TReal fYaw, TReal fRoll )
{
	const TReal fSinPitch(sin(fPitch*static_cast<TReal>(0.5)));
	const TReal fCosPitch(cos(fPitch*static_cast<TReal>(0.5)));
	const TReal fSinYaw(sin(fYaw*static_cast<TReal>(0.5)));
	const TReal fCosYaw(cos(fYaw*static_cast<TReal>(0.5)));
	const TReal fSinRoll(sin(fRoll*static_cast<TReal>(0.5)));
	const TReal fCosRoll(cos(fRoll*static_cast<TReal>(0.5)));
	const TReal fCosPitchCosYaw(fCosPitch*fCosYaw);
	const TReal fSinPitchSinYaw(fSinPitch*fSinYaw);
	x = fSinRoll * fCosPitchCosYaw     - fCosRoll * fSinPitchSinYaw;
	y = fCosRoll * fSinPitch * fCosYaw + fSinRoll * fCosPitch * fSinYaw;
	z = fCosRoll * fCosPitch * fSinYaw - fSinRoll * fSinPitch * fCosYaw;
	w = fCosRoll * fCosPitchCosYaw     + fSinRoll * fSinPitchSinYaw;
}

// ---------------------------------------------------------------------------
// Returns a matrix representation of the quaternion
template<typename TReal>
inline aiMatrix3x3t<TReal> aiQuaterniont<TReal>::GetMatrix() const
{
	aiMatrix3x3t<TReal> resMatrix;
	resMatrix.a1 = static_cast<TReal>(1.0) - static_cast<TReal>(2.0) * (y * y + z * z);
	resMatrix.a2 = static_cast<TReal>(2.0) * (x * y - z * w);
	resMatrix.a3 = static_cast<TReal>(2.0) * (x * z + y * w);
	resMatrix.b1 = static_cast<TReal>(2.0) * (x * y + z * w);
	resMatrix.b2 = static_cast<TReal>(1.0) - static_cast<TReal>(2.0) * (x * x + z * z);
	resMatrix.b3 = static_cast<TReal>(2.0) * (y * z - x * w);
	resMatrix.c1 = static_cast<TReal>(2.0) * (x * z - y * w);
	resMatrix.c2 = static_cast<TReal>(2.0) * (y * z + x * w);
	resMatrix.c3 = static_cast<TReal>(1.0) - static_cast<TReal>(2.0) * (x * x + y * y);

	return resMatrix;
}

// ---------------------------------------------------------------------------
// Construction from an axis-angle pair
template<typename TReal>
inline aiQuaterniont<TReal>::aiQuaterniont( aiVector3t<TReal> axis, TReal angle)
{
	axis.Normalize();

	const TReal sin_a = sin( angle / 2 );
	const TReal cos_a = cos( angle / 2 );
	x    = axis.x * sin_a;
	y    = axis.y * sin_a;
	z    = axis.z * sin_a;
	w    = cos_a;
}
// ---------------------------------------------------------------------------
// Construction from am existing, normalized quaternion
template<typename TReal>
inline aiQuaterniont<TReal>::aiQuaterniont( aiVector3t<TReal> normalized)
{
	x = normalized.x;
	y = normalized.y;
	z = normalized.z;

	const TReal t = static_cast<TReal>(1.0) - (x*x) - (y*y) - (z*z);

	if (t < static_cast<TReal>(0.0)) {
		w = static_cast<TReal>(0.0);
	}
	else w = sqrt (t);
}

// ---------------------------------------------------------------------------
// Performs a spherical interpolation between two quaternions 
// Implementation adopted from the gmtl project. All others I found on the net fail in some cases.
// Congrats, gmtl!
template<typename TReal>
inline void aiQuaterniont<TReal>::Interpolate( aiQuaterniont& pOut, const aiQuaterniont& pStart, const aiQuaterniont& pEnd, TReal pFactor)
{
	// calc cosine theta
	TReal cosom = pStart.x * pEnd.x + pStart.y * pEnd.y + pStart.z * pEnd.z + pStart.w * pEnd.w;

	// adjust signs (if necessary)
	aiQuaterniont end = pEnd;
	if( cosom < static_cast<TReal>(0.0))
	{
		cosom = -cosom;
		end.x = -end.x;   // Reverse all signs
		end.y = -end.y;
		end.z = -end.z;
		end.w = -end.w;
	} 

	// Calculate coefficients
	TReal sclp, sclq;
	if( (static_cast<TReal>(1.0) - cosom) > static_cast<TReal>(0.0001)) // 0.0001 -> some epsillon
	{
		// Standard case (slerp)
		TReal omega, sinom;
		omega = acos( cosom); // extract theta from dot product's cos theta
		sinom = sin( omega);
		sclp  = sin( (static_cast<TReal>(1.0) - pFactor) * omega) / sinom;
		sclq  = sin( pFactor * omega) / sinom;
	} else
	{
		// Very close, do linear interp (because it's faster)
		sclp = static_cast<TReal>(1.0) - pFactor;
		sclq = pFactor;
	}

	pOut.x = sclp * pStart.x + sclq * end.x;
	pOut.y = sclp * pStart.y + sclq * end.y;
	pOut.z = sclp * pStart.z + sclq * end.z;
	pOut.w = sclp * pStart.w + sclq * end.w;
}

// ---------------------------------------------------------------------------
template<typename TReal>
inline aiQuaterniont<TReal>& aiQuaterniont<TReal>::Normalize()
{
	// compute the magnitude and divide through it
	const TReal mag = sqrt(x*x + y*y + z*z + w*w);
	if (mag)
	{
		const TReal invMag = static_cast<TReal>(1.0)/mag;
		x *= invMag;
		y *= invMag;
		z *= invMag;
		w *= invMag;
	}
	return *this;
}

// ---------------------------------------------------------------------------
template<typename TReal>
inline aiQuaterniont<TReal> aiQuaterniont<TReal>::operator* (const aiQuaterniont& t) const
{
	return aiQuaterniont(w*t.w - x*t.x - y*t.y - z*t.z,
		w*t.x + x*t.w + y*t.z - z*t.y,
		w*t.y + y*t.w + z*t.x - x*t.z,
		w*t.z + z*t.w + x*t.y - y*t.x);
}

// ---------------------------------------------------------------------------
template<typename TReal>
inline aiQuaterniont<TReal>& aiQuaterniont<TReal>::Conjugate ()
{
	x = -x;
	y = -y;
	z = -z;
	return *this;
}

// ---------------------------------------------------------------------------
template<typename TReal>
inline aiVector3t<TReal> aiQuaterniont<TReal>::Rotate (const aiVector3t<TReal>& v)
{
	aiQuaterniont q2(0.f,v.x,v.y,v.z), q = *this, qinv = q;
	q.Conjugate();

	q = q*q2*qinv;
	return aiVector3t<TReal>(q.x,q.y,q.z);

}

#endif
#endif
