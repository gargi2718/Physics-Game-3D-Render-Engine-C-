
/** @file aiMatrix4x4t<TReal>.inl
 *  @brief Inline implementation of the 4x4 matrix operators
 */
#ifndef AI_MATRIX4x4_INL_INC
#define AI_MATRIX4x4_INL_INC

#ifdef __cplusplus

#include "matrix4x4.h"
#include "matrix3x3.h"
#include "quaternion.h"

#include <algorithm>
#include <limits>
#include <math.h>

// ----------------------------------------------------------------------------------------
template <typename TReal>
aiMatrix4x4t<TReal> ::aiMatrix4x4t () :	
	a1(1.0f), a2(), a3(), a4(), 
	b1(), b2(1.0f), b3(), b4(), 
	c1(), c2(), c3(1.0f), c4(),
	d1(), d2(), d3(), d4(1.0f)
{

}

// ----------------------------------------------------------------------------------------
template <typename TReal>
aiMatrix4x4t<TReal> ::aiMatrix4x4t (TReal _a1, TReal _a2, TReal _a3, TReal _a4,
			  TReal _b1, TReal _b2, TReal _b3, TReal _b4,
			  TReal _c1, TReal _c2, TReal _c3, TReal _c4,
			  TReal _d1, TReal _d2, TReal _d3, TReal _d4) :	
	a1(_a1), a2(_a2), a3(_a3), a4(_a4),  
	b1(_b1), b2(_b2), b3(_b3), b4(_b4), 
	c1(_c1), c2(_c2), c3(_c3), c4(_c4),
	d1(_d1), d2(_d2), d3(_d3), d4(_d4)
{
	
}

// ------------------------------------------------------------------------------------------------
template <typename TReal>
template <typename TOther>
aiMatrix4x4t<TReal>::operator aiMatrix4x4t<TOther> () const
{
	return aiMatrix4x4t<TOther>(static_cast<TOther>(a1),static_cast<TOther>(a2),static_cast<TOther>(a3),static_cast<TOther>(a4),
		static_cast<TOther>(b1),static_cast<TOther>(b2),static_cast<TOther>(b3),static_cast<TOther>(b4),
		static_cast<TOther>(c1),static_cast<TOther>(c2),static_cast<TOther>(c3),static_cast<TOther>(c4),
		static_cast<TOther>(d1),static_cast<TOther>(d2),static_cast<TOther>(d3),static_cast<TOther>(d4));
}


// ----------------------------------------------------------------------------------------
template <typename TReal>
inline aiMatrix4x4t<TReal>::aiMatrix4x4t (const aiMatrix3x3t<TReal>& m)
{
	a1 = m.a1; a2 = m.a2; a3 = m.a3; a4 = static_cast<TReal>(0.0);
	b1 = m.b1; b2 = m.b2; b3 = m.b3; b4 = static_cast<TReal>(0.0);
	c1 = m.c1; c2 = m.c2; c3 = m.c3; c4 = static_cast<TReal>(0.0);
	d1 = static_cast<TReal>(0.0); d2 = static_cast<TReal>(0.0); d3 = static_cast<TReal>(0.0); d4 = static_cast<TReal>(1.0);
}

// ----------------------------------------------------------------------------------------
template <typename TReal>
inline aiMatrix4x4t<TReal>& aiMatrix4x4t<TReal>::operator *= (const aiMatrix4x4t<TReal>& m)
{
	*this = aiMatrix4x4t<TReal>(
		m.a1 * a1 + m.b1 * a2 + m.c1 * a3 + m.d1 * a4,
		m.a2 * a1 + m.b2 * a2 + m.c2 * a3 + m.d2 * a4,
		m.a3 * a1 + m.b3 * a2 + m.c3 * a3 + m.d3 * a4,
		m.a4 * a1 + m.b4 * a2 + m.c4 * a3 + m.d4 * a4,
		m.a1 * b1 + m.b1 * b2 + m.c1 * b3 + m.d1 * b4,
		m.a2 * b1 + m.b2 * b2 + m.c2 * b3 + m.d2 * b4,
		m.a3 * b1 + m.b3 * b2 + m.c3 * b3 + m.d3 * b4,
		m.a4 * b1 + m.b4 * b2 + m.c4 * b3 + m.d4 * b4,
		m.a1 * c1 + m.b1 * c2 + m.c1 * c3 + m.d1 * c4,
		m.a2 * c1 + m.b2 * c2 + m.c2 * c3 + m.d2 * c4,
		m.a3 * c1 + m.b3 * c2 + m.c3 * c3 + m.d3 * c4,
		m.a4 * c1 + m.b4 * c2 + m.c4 * c3 + m.d4 * c4,
		m.a1 * d1 + m.b1 * d2 + m.c1 * d3 + m.d1 * d4,
		m.a2 * d1 + m.b2 * d2 + m.c2 * d3 + m.d2 * d4,
		m.a3 * d1 + m.b3 * d2 + m.c3 * d3 + m.d3 * d4,
		m.a4 * d1 + m.b4 * d2 + m.c4 * d3 + m.d4 * d4);
	return *this;
}

// ----------------------------------------------------------------------------------------
template <typename TReal>
inline aiMatrix4x4t<TReal> aiMatrix4x4t<TReal>::operator* (const aiMatrix4x4t<TReal>& m) const
{
	aiMatrix4x4t<TReal> temp( *this);
	temp *= m;
	return temp;
}


// ----------------------------------------------------------------------------------------
template <typename TReal>
inline aiMatrix4x4t<TReal>& aiMatrix4x4t<TReal>::Transpose()
{
	// (TReal&) don't remove, GCC complains cause of packed fields
	std::swap( (TReal&)b1, (TReal&)a2);
	std::swap( (TReal&)c1, (TReal&)a3);
	std::swap( (TReal&)c2, (TReal&)b3);
	std::swap( (TReal&)d1, (TReal&)a4);
	std::swap( (TReal&)d2, (TReal&)b4);
	std::swap( (TReal&)d3, (TReal&)c4);
	return *this;
}


// ----------------------------------------------------------------------------------------
template <typename TReal>
inline TReal aiMatrix4x4t<TReal>::Determinant() const
{
	return a1*b2*c3*d4 - a1*b2*c4*d3 + a1*b3*c4*d2 - a1*b3*c2*d4 
		+ a1*b4*c2*d3 - a1*b4*c3*d2 - a2*b3*c4*d1 + a2*b3*c1*d4 
		- a2*b4*c1*d3 + a2*b4*c3*d1 - a2*b1*c3*d4 + a2*b1*c4*d3 
		+ a3*b4*c1*d2 - a3*b4*c2*d1 + a3*b1*c2*d4 - a3*b1*c4*d2 
		+ a3*b2*c4*d1 - a3*b2*c1*d4 - a4*b1*c2*d3 + a4*b1*c3*d2
		- a4*b2*c3*d1 + a4*b2*c1*d3 - a4*b3*c1*d2 + a4*b3*c2*d1;
}

// ----------------------------------------------------------------------------------------
template <typename TReal>
inline aiMatrix4x4t<TReal>& aiMatrix4x4t<TReal>::Inverse()
{
	// Compute the reciprocal determinant
	const TReal det = Determinant();
	if(det == static_cast<TReal>(0.0)) 
	{
		// Matrix not invertible. Setting all elements to nan is not really
		// correct in a mathematical sense but it is easy to debug for the
		// programmer.
		const TReal nan = std::numeric_limits<TReal>::quiet_NaN();
		*this = aiMatrix4x4t<TReal>(
			nan,nan,nan,nan,
			nan,nan,nan,nan,
			nan,nan,nan,nan,
			nan,nan,nan,nan);

		return *this;
	}

	const TReal invdet = static_cast<TReal>(1.0) / det;

	aiMatrix4x4t<TReal> res;
	res.a1 = invdet  * (b2 * (c3 * d4 - c4 * d3) + b3 * (c4 * d2 - c2 * d4) + b4 * (c2 * d3 - c3 * d2));
	res.a2 = -invdet * (a2 * (c3 * d4 - c4 * d3) + a3 * (c4 * d2 - c2 * d4) + a4 * (c2 * d3 - c3 * d2));
	res.a3 = invdet  * (a2 * (b3 * d4 - b4 * d3) + a3 * (b4 * d2 - b2 * d4) + a4 * (b2 * d3 - b3 * d2));
	res.a4 = -invdet * (a2 * (b3 * c4 - b4 * c3) + a3 * (b4 * c2 - b2 * c4) + a4 * (b2 * c3 - b3 * c2));
	res.b1 = -invdet * (b1 * (c3 * d4 - c4 * d3) + b3 * (c4 * d1 - c1 * d4) + b4 * (c1 * d3 - c3 * d1));
	res.b2 = invdet  * (a1 * (c3 * d4 - c4 * d3) + a3 * (c4 * d1 - c1 * d4) + a4 * (c1 * d3 - c3 * d1));
	res.b3 = -invdet * (a1 * (b3 * d4 - b4 * d3) + a3 * (b4 * d1 - b1 * d4) + a4 * (b1 * d3 - b3 * d1));
	res.b4 = invdet  * (a1 * (b3 * c4 - b4 * c3) + a3 * (b4 * c1 - b1 * c4) + a4 * (b1 * c3 - b3 * c1));
	res.c1 = invdet  * (b1 * (c2 * d4 - c4 * d2) + b2 * (c4 * d1 - c1 * d4) + b4 * (c1 * d2 - c2 * d1));
	res.c2 = -invdet * (a1 * (c2 * d4 - c4 * d2) + a2 * (c4 * d1 - c1 * d4) + a4 * (c1 * d2 - c2 * d1));
	res.c3 = invdet  * (a1 * (b2 * d4 - b4 * d2) + a2 * (b4 * d1 - b1 * d4) + a4 * (b1 * d2 - b2 * d1));
	res.c4 = -invdet * (a1 * (b2 * c4 - b4 * c2) + a2 * (b4 * c1 - b1 * c4) + a4 * (b1 * c2 - b2 * c1));
	res.d1 = -invdet * (b1 * (c2 * d3 - c3 * d2) + b2 * (c3 * d1 - c1 * d3) + b3 * (c1 * d2 - c2 * d1));
	res.d2 = invdet  * (a1 * (c2 * d3 - c3 * d2) + a2 * (c3 * d1 - c1 * d3) + a3 * (c1 * d2 - c2 * d1));
	res.d3 = -invdet * (a1 * (b2 * d3 - b3 * d2) + a2 * (b3 * d1 - b1 * d3) + a3 * (b1 * d2 - b2 * d1));
	res.d4 = invdet  * (a1 * (b2 * c3 - b3 * c2) + a2 * (b3 * c1 - b1 * c3) + a3 * (b1 * c2 - b2 * c1)); 
	*this = res;

	return *this;
}

// ----------------------------------------------------------------------------------------
template <typename TReal>
inline TReal* aiMatrix4x4t<TReal>::operator[](unsigned int p_iIndex)
{
	// XXX this is UB. Has been for years. The fact that it works now does not make it better.
	return &this->a1 + p_iIndex * 4;
}

// ----------------------------------------------------------------------------------------
template <typename TReal>
inline const TReal* aiMatrix4x4t<TReal>::operator[](unsigned int p_iIndex) const
{
	// XXX same
	return &this->a1 + p_iIndex * 4;
}

// ----------------------------------------------------------------------------------------
template <typename TReal>
inline bool aiMatrix4x4t<TReal>::operator== (const aiMatrix4x4t<TReal> m) const
{
	return (a1 == m.a1 && a2 == m.a2 && a3 == m.a3 && a4 == m.a4 &&
			b1 == m.b1 && b2 == m.b2 && b3 == m.b3 && b4 == m.b4 &&
			c1 == m.c1 && c2 == m.c2 && c3 == m.c3 && c4 == m.c4 &&
			d1 == m.d1 && d2 == m.d2 && d3 == m.d3 && d4 == m.d4);
}

// ----------------------------------------------------------------------------------------
template <typename TReal>
inline bool aiMatrix4x4t<TReal>::operator!= (const aiMatrix4x4t<TReal> m) const
{
	return !(*this == m);
}

// ----------------------------------------------------------------------------------------
template <typename TReal>
inline void aiMatrix4x4t<TReal>::Decompose (aiVector3t<TReal>& scaling, aiQuaterniont<TReal>& rotation,
	aiVector3t<TReal>& position) const
{
	const aiMatrix4x4t<TReal>& _this = *this;

	// extract translation
	position.x = _this[0][3];
	position.y = _this[1][3];
	position.z = _this[2][3];

	// extract the rows of the matrix
	aiVector3t<TReal> vRows[3] = {
		aiVector3t<TReal>(_this[0][0],_this[1][0],_this[2][0]),
		aiVector3t<TReal>(_this[0][1],_this[1][1],_this[2][1]),
		aiVector3t<TReal>(_this[0][2],_this[1][2],_this[2][2])
	};

	// extract the scaling factors
	scaling.x = vRows[0].Length();
	scaling.y = vRows[1].Length();
	scaling.z = vRows[2].Length();

	// and the sign of the scaling
	if (Determinant() < 0) {
		scaling.x = -scaling.x;
		scaling.y = -scaling.y;
		scaling.z = -scaling.z;
	}

	// and remove all scaling from the matrix
	if(scaling.x)
	{
		vRows[0] /= scaling.x;
	}
	if(scaling.y)
	{
		vRows[1] /= scaling.y;
	}
	if(scaling.z)
	{
		vRows[2] /= scaling.z;
	}

	// build a 3x3 rotation matrix
	aiMatrix3x3t<TReal> m(vRows[0].x,vRows[1].x,vRows[2].x,
		vRows[0].y,vRows[1].y,vRows[2].y,
		vRows[0].z,vRows[1].z,vRows[2].z);

	// and generate the rotation quaternion from it
	rotation = aiQuaterniont<TReal>(m);
}

// ----------------------------------------------------------------------------------------
template <typename TReal>
inline void aiMatrix4x4t<TReal>::DecomposeNoScaling (aiQuaterniont<TReal>& rotation,
	aiVector3t<TReal>& position) const
{
	const aiMatrix4x4t<TReal>& _this = *this;

	// extract translation
	position.x = _this[0][3];
	position.y = _this[1][3];
	position.z = _this[2][3];

	// extract rotation
	rotation = aiQuaterniont<TReal>((aiMatrix3x3t<TReal>)_this);
}

// ----------------------------------------------------------------------------------------
template <typename TReal>
inline aiMatrix4x4t<TReal>& aiMatrix4x4t<TReal>::FromEulerAnglesXYZ(const aiVector3t<TReal>& blubb)
{
	return FromEulerAnglesXYZ(blubb.x,blubb.y,blubb.z);
}

// ----------------------------------------------------------------------------------------
template <typename TReal>
inline aiMatrix4x4t<TReal>& aiMatrix4x4t<TReal>::FromEulerAnglesXYZ(TReal x, TReal y, TReal z)
{
	aiMatrix4x4t<TReal>& _this = *this;

	TReal cr = cos( x );
	TReal sr = sin( x );
	TReal cp = cos( y );
	TReal sp = sin( y );
	TReal cy = cos( z );
	TReal sy = sin( z );

	_this.a1 = cp*cy ;
	_this.a2 = cp*sy;
	_this.a3 = -sp ;

	TReal srsp = sr*sp;
	TReal crsp = cr*sp;

	_this.b1 = srsp*cy-cr*sy ;
	_this.b2 = srsp*sy+cr*cy ;
	_this.b3 = sr*cp ;

	_this.c1 =  crsp*cy+sr*sy ;
	_this.c2 =  crsp*sy-sr*cy ;
	_this.c3 = cr*cp ;

	return *this;
}

// ----------------------------------------------------------------------------------------
template <typename TReal>
inline bool aiMatrix4x4t<TReal>::IsIdentity() const
{
	// Use a small epsilon to solve floating-point inaccuracies
	const static TReal epsilon = 10e-3f;

	return (a2 <= epsilon && a2 >= -epsilon &&
			a3 <= epsilon && a3 >= -epsilon &&
			a4 <= epsilon && a4 >= -epsilon &&
			b1 <= epsilon && b1 >= -epsilon &&
			b3 <= epsilon && b3 >= -epsilon &&
			b4 <= epsilon && b4 >= -epsilon &&
			c1 <= epsilon && c1 >= -epsilon &&
			c2 <= epsilon && c2 >= -epsilon &&
			c4 <= epsilon && c4 >= -epsilon &&
			d1 <= epsilon && d1 >= -epsilon &&
			d2 <= epsilon && d2 >= -epsilon &&
			d3 <= epsilon && d3 >= -epsilon &&
			a1 <= 1.f+epsilon && a1 >= 1.f-epsilon && 
			b2 <= 1.f+epsilon && b2 >= 1.f-epsilon && 
			c3 <= 1.f+epsilon && c3 >= 1.f-epsilon && 
			d4 <= 1.f+epsilon && d4 >= 1.f-epsilon);
}

// ----------------------------------------------------------------------------------------
template <typename TReal>
inline aiMatrix4x4t<TReal>& aiMatrix4x4t<TReal>::RotationX(TReal a, aiMatrix4x4t<TReal>& out)
{
	/*
	     |  1  0       0       0 |
     M = |  0  cos(A) -sin(A)  0 |
         |  0  sin(A)  cos(A)  0 |
         |  0  0       0       1 |	*/
	out = aiMatrix4x4t<TReal>();
	out.b2 = out.c3 = cos(a);
	out.b3 = -(out.c2 = sin(a));
	return out;
}

// ----------------------------------------------------------------------------------------
template <typename TReal>
inline aiMatrix4x4t<TReal>& aiMatrix4x4t<TReal>::RotationY(TReal a, aiMatrix4x4t<TReal>& out)
{
	/*
	     |  cos(A)  0   sin(A)  0 |
     M = |  0       1   0       0 |
         | -sin(A)  0   cos(A)  0 |
         |  0       0   0       1 |
		*/
	out = aiMatrix4x4t<TReal>();
	out.a1 = out.c3 = cos(a);
	out.c1 = -(out.a3 = sin(a));
	return out;
}

// ----------------------------------------------------------------------------------------
template <typename TReal>
inline aiMatrix4x4t<TReal>& aiMatrix4x4t<TReal>::RotationZ(TReal a, aiMatrix4x4t<TReal>& out)
{
	/*
	     |  cos(A)  -sin(A)   0   0 |
     M = |  sin(A)   cos(A)   0   0 |
         |  0        0        1   0 |
         |  0        0        0   1 |	*/
	out = aiMatrix4x4t<TReal>();
	out.a1 = out.b2 = cos(a);
	out.a2 = -(out.b1 = sin(a));
	return out;
}

// ----------------------------------------------------------------------------------------
// Returns a rotation matrix for a rotation around an arbitrary axis.
template <typename TReal>
inline aiMatrix4x4t<TReal>& aiMatrix4x4t<TReal>::Rotation( TReal a, const aiVector3t<TReal>& axis, aiMatrix4x4t<TReal>& out)
{
  TReal c = cos( a), s = sin( a), t = 1 - c;
  TReal x = axis.x, y = axis.y, z = axis.z;

  // Many thanks to MathWorld and Wikipedia
  out.a1 = t*x*x + c;   out.a2 = t*x*y - s*z; out.a3 = t*x*z + s*y;
  out.b1 = t*x*y + s*z; out.b2 = t*y*y + c;   out.b3 = t*y*z - s*x;
  out.c1 = t*x*z - s*y; out.c2 = t*y*z + s*x; out.c3 = t*z*z + c;
  out.a4 = out.b4 = out.c4 = static_cast<TReal>(0.0);
  out.d1 = out.d2 = out.d3 = static_cast<TReal>(0.0);
  out.d4 = static_cast<TReal>(1.0);

  return out;
}

// ----------------------------------------------------------------------------------------
template <typename TReal>
inline aiMatrix4x4t<TReal>& aiMatrix4x4t<TReal>::Translation( const aiVector3t<TReal>& v, aiMatrix4x4t<TReal>& out)
{
	out = aiMatrix4x4t<TReal>();
	out.a4 = v.x;
	out.b4 = v.y;
	out.c4 = v.z;
	return out;
}

// ----------------------------------------------------------------------------------------
template <typename TReal>
inline aiMatrix4x4t<TReal>& aiMatrix4x4t<TReal>::Scaling( const aiVector3t<TReal>& v, aiMatrix4x4t<TReal>& out)
{
	out = aiMatrix4x4t<TReal>();
	out.a1 = v.x;
	out.b2 = v.y;
	out.c3 = v.z;
	return out;
}

// ----------------------------------------------------------------------------------------
/** A function for creating a rotation matrix that rotates a vector called
 * "from" into another vector called "to".
 * Input : from[3], to[3] which both must be *normalized* non-zero vectors
 * Output: mtx[3][3] -- a 3x3 matrix in colum-major form
 * Authors: Tomas M�ller, John Hughes
 *          "Efficiently Building a Matrix to Rotate One Vector to Another"
 *          Journal of Graphics Tools, 4(4):1-4, 1999
 */
// ----------------------------------------------------------------------------------------
template <typename TReal>
inline aiMatrix4x4t<TReal>& aiMatrix4x4t<TReal>::FromToMatrix(const aiVector3t<TReal>& from, 
	const aiVector3t<TReal>& to, aiMatrix4x4t<TReal>& mtx)
{	
	aiMatrix3x3t<TReal> m3;
	aiMatrix3x3t<TReal>::FromToMatrix(from,to,m3);
	mtx = aiMatrix4x4t<TReal>(m3);
	return mtx;
}

#endif // __cplusplus
#endif // AI_MATRIX4x4_INL_INC
