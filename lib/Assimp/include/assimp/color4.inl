/** @file  aiColor4D.inl
 *  @brief Inline implementation of aiColor4t<TReal> operators
 */
#ifndef AI_COLOR4D_INL_INC
#define AI_COLOR4D_INL_INC

#ifdef __cplusplus
#include "color4.h"

// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE const aiColor4t<TReal>& aiColor4t<TReal>::operator += (const aiColor4t<TReal>& o) {
	r += o.r; g += o.g; b += o.b; a += o.a; 
	return *this; 
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE const aiColor4t<TReal>& aiColor4t<TReal>::operator -= (const aiColor4t<TReal>& o) {
	r -= o.r; g -= o.g; b -= o.b; a -= o.a; 
	return *this;
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE const aiColor4t<TReal>& aiColor4t<TReal>::operator *= (TReal f) {
	r *= f; g *= f; b *= f; a *= f; 
	return *this; 
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE const aiColor4t<TReal>& aiColor4t<TReal>::operator /= (TReal f) {
	r /= f; g /= f; b /= f; a /= f; 
	return *this; 
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE TReal aiColor4t<TReal>::operator[](unsigned int i) const {
	return *(&r + i);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE TReal& aiColor4t<TReal>::operator[](unsigned int i) {
	return *(&r + i);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE bool aiColor4t<TReal>::operator== (const aiColor4t<TReal>& other) const {
	return r == other.r && g == other.g && b == other.b && a == other.a;
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE bool aiColor4t<TReal>::operator!= (const aiColor4t<TReal>& other) const {
	return r != other.r || g != other.g || b != other.b || a != other.a;
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE aiColor4t<TReal> operator + (const aiColor4t<TReal>& v1, const aiColor4t<TReal>& v2)	{
	return aiColor4t<TReal>( v1.r + v2.r, v1.g + v2.g, v1.b + v2.b, v1.a + v2.a);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE aiColor4t<TReal> operator - (const aiColor4t<TReal>& v1, const aiColor4t<TReal>& v2)	{
	return aiColor4t<TReal>( v1.r - v2.r, v1.g - v2.g, v1.b - v2.b, v1.a - v2.a);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE aiColor4t<TReal> operator * (const aiColor4t<TReal>& v1, const aiColor4t<TReal>& v2)	{
	return aiColor4t<TReal>( v1.r * v2.r, v1.g * v2.g, v1.b * v2.b, v1.a * v2.a);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE aiColor4t<TReal> operator / (const aiColor4t<TReal>& v1, const aiColor4t<TReal>& v2)	{
	return aiColor4t<TReal>( v1.r / v2.r, v1.g / v2.g, v1.b / v2.b, v1.a / v2.a);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE aiColor4t<TReal> operator * ( TReal f, const aiColor4t<TReal>& v)	{
	return aiColor4t<TReal>( f*v.r, f*v.g, f*v.b, f*v.a);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE  aiColor4t<TReal> operator * ( const aiColor4t<TReal>& v, TReal f)	{
	return aiColor4t<TReal>( f*v.r, f*v.g, f*v.b, f*v.a);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE  aiColor4t<TReal> operator / ( const aiColor4t<TReal>& v, TReal f)	{
	return v * (1/f);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE  aiColor4t<TReal> operator / ( TReal f,const aiColor4t<TReal>& v)	{
	return aiColor4t<TReal>(f,f,f,f)/v;
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE  aiColor4t<TReal> operator + ( const aiColor4t<TReal>& v, TReal f)	{
	return aiColor4t<TReal>( f+v.r, f+v.g, f+v.b, f+v.a);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE  aiColor4t<TReal> operator - ( const aiColor4t<TReal>& v, TReal f)	{
	return aiColor4t<TReal>( v.r-f, v.g-f, v.b-f, v.a-f);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE  aiColor4t<TReal> operator + ( TReal f, const aiColor4t<TReal>& v)	{
	return aiColor4t<TReal>( f+v.r, f+v.g, f+v.b, f+v.a);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
AI_FORCE_INLINE  aiColor4t<TReal> operator - ( TReal f, const aiColor4t<TReal>& v)	{
	return aiColor4t<TReal>( f-v.r, f-v.g, f-v.b, f-v.a);
}

// ------------------------------------------------------------------------------------------------
template <typename TReal>
inline bool aiColor4t<TReal> :: IsBlack() const	{
	// The alpha component doesn't care here. black is black.
	static const TReal epsilon = 10e-3f;
	return fabs( r ) < epsilon && fabs( g ) < epsilon && fabs( b ) < epsilon;
}

#endif // __cplusplus
#endif // AI_VECTOR3D_INL_INC
