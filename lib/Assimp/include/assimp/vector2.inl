
/** @file  aiVector2D.inl
 *  @brief Inline implementation of aiVector2t<TReal> operators
 */
#ifndef AI_VECTOR2D_INL_INC
#define AI_VECTOR2D_INL_INC

#ifdef __cplusplus
#include "vector2.h"

// ------------------------------------------------------------------------------------------------
template <typename TReal>
template <typename TOther>
aiVector2t<TReal>::operator aiVector2t<TOther> () const {
	return aiVector2t<TOther>(static_cast<TOther>(x),static_cast<TOther>(y));
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
void aiVector2t<TReal>::Set( TReal pX, TReal pY) { 
	x = pX; y = pY;
}

// ------------------------------------------------------------------------------------------------
template <typename TReal>
TReal aiVector2t<TReal>::SquareLength() const {
	return x*x + y*y; 
}

// ------------------------------------------------------------------------------------------------
template <typename TReal>
TReal aiVector2t<TReal>::Length() const {
	return ::sqrt( SquareLength());
}

// ------------------------------------------------------------------------------------------------
template <typename TReal>
aiVector2t<TReal>& aiVector2t<TReal>::Normalize() { 
	*this /= Length(); 
	return *this;
}

// ------------------------------------------------------------------------------------------------
template <typename TReal>
const aiVector2t<TReal>& aiVector2t<TReal>::operator += (const aiVector2t& o) {
	x += o.x; y += o.y;  
	return *this; 
}

// ------------------------------------------------------------------------------------------------
template <typename TReal>
const aiVector2t<TReal>& aiVector2t<TReal>::operator -= (const aiVector2t& o) {
	x -= o.x; y -= o.y;  
	return *this; 
}

// ------------------------------------------------------------------------------------------------
template <typename TReal>
const aiVector2t<TReal>& aiVector2t<TReal>::operator *= (TReal f) { 
	x *= f; y *= f;  
	return *this; 
}

// ------------------------------------------------------------------------------------------------
template <typename TReal>
const aiVector2t<TReal>& aiVector2t<TReal>::operator /= (TReal f) {
	x /= f; y /= f;  
	return *this; 
}

// ------------------------------------------------------------------------------------------------
template <typename TReal>
TReal aiVector2t<TReal>::operator[](unsigned int i) const {
	return *(&x + i);
}

// ------------------------------------------------------------------------------------------------
template <typename TReal>
TReal& aiVector2t<TReal>::operator[](unsigned int i) {
	return *(&x + i);
}

// ------------------------------------------------------------------------------------------------
template <typename TReal>
bool aiVector2t<TReal>::operator== (const aiVector2t& other) const {
	return x == other.x && y == other.y;
}

// ------------------------------------------------------------------------------------------------
template <typename TReal>
bool aiVector2t<TReal>::operator!= (const aiVector2t& other) const {
	return x != other.x || y != other.y;
}

// ------------------------------------------------------------------------------------------------
template <typename TReal>
aiVector2t<TReal>& aiVector2t<TReal>::operator= (TReal f)	{
	x = y = f;
	return *this;
}

// ------------------------------------------------------------------------------------------------
template <typename TReal>
const aiVector2t<TReal> aiVector2t<TReal>::SymMul(const aiVector2t& o) {
	return aiVector2t(x*o.x,y*o.y);
}


// ------------------------------------------------------------------------------------------------
// symmetric addition
template <typename TReal>
inline aiVector2t<TReal> operator + (const aiVector2t<TReal>& v1, const aiVector2t<TReal>& v2)
{
	return aiVector2t<TReal>( v1.x + v2.x, v1.y + v2.y);
}

// ------------------------------------------------------------------------------------------------
// symmetric subtraction
template <typename TReal>
inline aiVector2t<TReal> operator - (const aiVector2t<TReal>& v1, const aiVector2t<TReal>& v2)
{
	return aiVector2t<TReal>( v1.x - v2.x, v1.y - v2.y);
}

// ------------------------------------------------------------------------------------------------
// scalar product
template <typename TReal>
inline TReal operator * (const aiVector2t<TReal>& v1, const aiVector2t<TReal>& v2)
{
	return v1.x*v2.x + v1.y*v2.y;
}

// ------------------------------------------------------------------------------------------------
// scalar multiplication
template <typename TReal>
inline aiVector2t<TReal> operator * ( TReal f, const aiVector2t<TReal>& v)
{
	return aiVector2t<TReal>( f*v.x, f*v.y);
}

// ------------------------------------------------------------------------------------------------
// and the other way around
template <typename TReal>
inline aiVector2t<TReal> operator * ( const aiVector2t<TReal>& v, TReal f)
{
	return aiVector2t<TReal>( f*v.x, f*v.y);
}

// ------------------------------------------------------------------------------------------------
// scalar division
template <typename TReal>
inline aiVector2t<TReal> operator / ( const aiVector2t<TReal>& v, TReal f)
{

	return v * (1/f);
}

// ------------------------------------------------------------------------------------------------
// vector division
template <typename TReal>
inline aiVector2t<TReal> operator / ( const aiVector2t<TReal>& v, const aiVector2t<TReal>& v2)
{
	return aiVector2t<TReal>(v.x / v2.x,v.y / v2.y);
}

// ------------------------------------------------------------------------------------------------
// vector negation
template <typename TReal>
inline aiVector2t<TReal> operator - ( const aiVector2t<TReal>& v)
{
	return aiVector2t<TReal>( -v.x, -v.y);
}

#endif 
#endif
