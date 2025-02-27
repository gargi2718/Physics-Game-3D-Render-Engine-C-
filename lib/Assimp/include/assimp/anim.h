/** @file anim.h
 *  @brief Defines the data structures in which the imported animations
 *  are returned.
 */
#ifndef AI_ANIM_H_INC
#define AI_ANIM_H_INC

#include "types.h"
#include "quaternion.h"

#ifdef __cplusplus
extern "C" {
#endif

// ---------------------------------------------------------------------------
/** A time-value pair specifying a certain 3D vector for the given time. */
struct aiVectorKey
{
	/** The time of this key */
	double mTime;     
	
	/** The value of this key */
	C_STRUCT aiVector3D mValue; 

#ifdef __cplusplus

	//! Default constructor
	aiVectorKey(){}

	//! Construction from a given time and key value
	aiVectorKey(double time, const aiVector3D& value)
		:	mTime	(time)
		,	mValue	(value)
	{}


	typedef aiVector3D elem_type;

	// Comparison operators. For use with std::find();
	bool operator == (const aiVectorKey& o) const {
		return o.mValue == this->mValue;
	}
	bool operator != (const aiVectorKey& o) const {
		return o.mValue != this->mValue;
	}

	// Relational operators. For use with std::sort();
	bool operator < (const aiVectorKey& o) const {
		return mTime < o.mTime;
	}
	bool operator > (const aiVectorKey& o) const {
		return mTime > o.mTime;
	}
#endif
};

// ---------------------------------------------------------------------------
/** A time-value pair specifying a rotation for the given time. 
 *  Rotations are expressed with quaternions. */
struct aiQuatKey
{
	/** The time of this key */
	double mTime;     

	/** The value of this key */
	C_STRUCT aiQuaternion mValue; 

#ifdef __cplusplus
	aiQuatKey(){
	}

	/** Construction from a given time and key value */
	aiQuatKey(double time, const aiQuaternion& value)
		:	mTime	(time)
		,	mValue	(value)
	{}

	typedef aiQuaternion elem_type;

	// Comparison operators. For use with std::find();
	bool operator == (const aiQuatKey& o) const {
		return o.mValue == this->mValue;
	}
	bool operator != (const aiQuatKey& o) const {
		return o.mValue != this->mValue;
	}

	// Relational operators. For use with std::sort();
	bool operator < (const aiQuatKey& o) const {
		return mTime < o.mTime;
	}
	bool operator > (const aiQuatKey& o) const {
		return mTime > o.mTime;
	}
#endif
};

// ---------------------------------------------------------------------------
/** Binds a anim mesh to a specific point in time. */
struct aiMeshKey 
{
	/** The time of this key */
	double mTime;

	/** Index into the aiMesh::mAnimMeshes array of the 
	 *  mesh coresponding to the #aiMeshAnim hosting this
	 *  key frame. The referenced anim mesh is evaluated
	 *  according to the rules defined in the docs for #aiAnimMesh.*/
	unsigned int mValue;

#ifdef __cplusplus

	aiMeshKey() {
	}

	/** Construction from a given time and key value */
	aiMeshKey(double time, const unsigned int value)
		:	mTime	(time)
		,	mValue	(value)
	{}

	typedef unsigned int elem_type;

	// Comparison operators. For use with std::find();
	bool operator == (const aiMeshKey& o) const {
		return o.mValue == this->mValue;
	}
	bool operator != (const aiMeshKey& o) const {
		return o.mValue != this->mValue;
	}

	// Relational operators. For use with std::sort();
	bool operator < (const aiMeshKey& o) const {
		return mTime < o.mTime;
	}
	bool operator > (const aiMeshKey& o) const {
		return mTime > o.mTime;
	}

#endif
};

// ---------------------------------------------------------------------------
/** Defines how an animation channel behaves outside the defined time
 *  range. This corresponds to aiNodeAnim::mPreState and 
 *  aiNodeAnim::mPostState.*/
enum aiAnimBehaviour
{
	/** The value from the default node transformation is taken*/
	aiAnimBehaviour_DEFAULT  = 0x0,  

	/** The nearest key value is used without interpolation */
	aiAnimBehaviour_CONSTANT = 0x1,

	/** The value of the nearest two keys is linearly
	 *  extrapolated for the current time value.*/
	aiAnimBehaviour_LINEAR   = 0x2,

	/** The animation is repeated.
	 *
	 *  If the animation key go from n to m and the current
	 *  time is t, use the value at (t-n) % (|m-n|).*/
	aiAnimBehaviour_REPEAT   = 0x3,



	/** This value is not used, it is just here to force the
	 *  the compiler to map this enum to a 32 Bit integer  */
#ifndef SWIG
	_aiAnimBehaviour_Force32Bit = 0x8fffffff
#endif
};

// ---------------------------------------------------------------------------
/** Describes the animation of a single node. The name specifies the 
 *  bone/node which is affected by this animation channel. The keyframes
 *  are given in three separate series of values, one each for position, 
 *  rotation and scaling. The transformation matrix computed from these
 *  values replaces the node's original transformation matrix at a
 *  specific time.
 *  This means all keys are absolute and not relative to the bone default pose.
 *  The order in which the transformations are applied is
 *  - as usual - scaling, rotation, translation.
 *
 *  @note All keys are returned in their correct, chronological order.
 *  Duplicate keys don't pass the validation step. Most likely there
 *  will be no negative time values, but they are not forbidden also ( so 
 *  implementations need to cope with them! ) */
struct aiNodeAnim
{
	/** The name of the node affected by this animation. The node 
	 *  must exist and it must be unique.*/
	C_STRUCT aiString mNodeName;

	/** The number of position keys */
	unsigned int mNumPositionKeys;

	/** The position keys of this animation channel. Positions are 
	 * specified as 3D vector. The array is mNumPositionKeys in size.
	 *
	 * If there are position keys, there will also be at least one
	 * scaling and one rotation key.*/
	C_STRUCT aiVectorKey* mPositionKeys;

	/** The number of rotation keys */
	unsigned int mNumRotationKeys;

	/** The rotation keys of this animation channel. Rotations are 
	 *  given as quaternions,  which are 4D vectors. The array is 
	 *  mNumRotationKeys in size.
	 *
	 * If there are rotation keys, there will also be at least one
	 * scaling and one position key. */
	C_STRUCT aiQuatKey* mRotationKeys;


	/** The number of scaling keys */
	unsigned int mNumScalingKeys;

	/** The scaling keys of this animation channel. Scalings are 
	 *  specified as 3D vector. The array is mNumScalingKeys in size.
	 *
	 * If there are scaling keys, there will also be at least one
	 * position and one rotation key.*/
	C_STRUCT aiVectorKey* mScalingKeys;


	/** Defines how the animation behaves before the first
	 *  key is encountered.
	 *
	 *  The default value is aiAnimBehaviour_DEFAULT (the original
	 *  transformation matrix of the affected node is used).*/
	C_ENUM aiAnimBehaviour mPreState;

	/** Defines how the animation behaves after the last 
	 *  key was processed.
	 *
	 *  The default value is aiAnimBehaviour_DEFAULT (the original
	 *  transformation matrix of the affected node is taken).*/
	C_ENUM aiAnimBehaviour mPostState;

#ifdef __cplusplus
	aiNodeAnim()
	{
		mNumPositionKeys = 0; mPositionKeys = NULL; 
		mNumRotationKeys = 0; mRotationKeys = NULL; 
		mNumScalingKeys  = 0; mScalingKeys  = NULL; 

		mPreState = mPostState = aiAnimBehaviour_DEFAULT;
	}

	~aiNodeAnim()
	{
		delete [] mPositionKeys;
		delete [] mRotationKeys;
		delete [] mScalingKeys;
	}
#endif // __cplusplus
};

// ---------------------------------------------------------------------------
/** Describes vertex-based animations for a single mesh or a group of
 *  meshes. Meshes carry the animation data for each frame in their
 *  aiMesh::mAnimMeshes array. The purpose of aiMeshAnim is to 
 *  define keyframes linking each mesh attachment to a particular
 *  point in time. */
struct aiMeshAnim
{
	/** Name of the mesh to be animated. An empty string is not allowed,
	 *  animated meshes need to be named (not necessarily uniquely,
	 *  the name can basically serve as wildcard to select a group
	 *  of meshes with similar animation setup)*/
	C_STRUCT aiString mName;

	/** Size of the #mKeys array. Must be 1, at least. */
	unsigned int mNumKeys;

	/** Key frames of the animation. May not be NULL. */
	C_STRUCT aiMeshKey* mKeys;

#ifdef __cplusplus

	aiMeshAnim()
		: mNumKeys()
		, mKeys()
	{}

	~aiMeshAnim()
	{
		delete[] mKeys;
	}

#endif
};

// ---------------------------------------------------------------------------
/** An animation consists of keyframe data for a number of nodes. For 
 *  each node affected by the animation a separate series of data is given.*/
struct aiAnimation
{
	/** The name of the animation. If the modeling package this data was 
	 *  exported from does support only a single animation channel, this 
	 *  name is usually empty (length is zero). */
	C_STRUCT aiString mName;

	/** Duration of the animation in ticks.  */
	double mDuration;

	/** Ticks per second. 0 if not specified in the imported file */
	double mTicksPerSecond;

	/** The number of bone animation channels. Each channel affects
	 *  a single node. */
	unsigned int mNumChannels;

	/** The node animation channels. Each channel affects a single node. 
	 *  The array is mNumChannels in size. */
	C_STRUCT aiNodeAnim** mChannels;


	/** The number of mesh animation channels. Each channel affects
	 *  a single mesh and defines vertex-based animation. */
	unsigned int mNumMeshChannels;

	/** The mesh animation channels. Each channel affects a single mesh. 
	 *  The array is mNumMeshChannels in size. */
	C_STRUCT aiMeshAnim** mMeshChannels;

#ifdef __cplusplus
	aiAnimation()
		: mDuration(-1.)
		, mTicksPerSecond()
		, mNumChannels()
		, mChannels()
		, mNumMeshChannels()
		, mMeshChannels()
	{
	}

	~aiAnimation()
	{
		// DO NOT REMOVE THIS ADDITIONAL CHECK
		if (mNumChannels && mChannels)	{
			for( unsigned int a = 0; a < mNumChannels; a++) {
				delete mChannels[a];
			}

		delete [] mChannels;
		}
		if (mNumMeshChannels && mMeshChannels)	{
			for( unsigned int a = 0; a < mNumMeshChannels; a++) {
				delete mMeshChannels[a];
			}

		delete [] mMeshChannels;
		}
	}
#endif // __cplusplus
};

#ifdef __cplusplus
}


// some C++ utilities for inter- and extrapolation
namespace Assimp {

// ---------------------------------------------------------------------------
/** @brief CPP-API: Utility class to simplify interpolations of various data types.
 *
 *  The type of interpolation is choosen automatically depending on the
 *  types of the arguments. */
template <typename T>
struct Interpolator		
{	
	// ------------------------------------------------------------------
	/** @brief Get the result of the interpolation between a,b.
	 *
	 *  The interpolation algorithm depends on the type of the operands.
	 *  aiQuaternion's and aiQuatKey's SLERP, the rest does a simple
	 *  linear interpolation. */
	void operator () (T& out,const T& a, const T& b, float d) const {
		out = a + (b-a)*d;
	}
}; // ! Interpolator <T>

//! @cond Never

template <>
struct Interpolator	<aiQuaternion>	{	
	void operator () (aiQuaternion& out,const aiQuaternion& a, 
		const aiQuaternion& b, float d) const
	{
		aiQuaternion::Interpolate(out,a,b,d);
	}
}; // ! Interpolator <aiQuaternion>

template <>
struct Interpolator	<unsigned int>	{	
	void operator () (unsigned int& out,unsigned int a, 
		unsigned int b, float d) const
	{
		out = d>0.5f ? b : a;
	}
}; // ! Interpolator <aiQuaternion>

template <>
struct Interpolator	 <aiVectorKey>	{	
	void operator () (aiVector3D& out,const aiVectorKey& a,
		const aiVectorKey& b, float d) const	
	{
		Interpolator<aiVector3D> ipl;
		ipl(out,a.mValue,b.mValue,d);
	}
}; // ! Interpolator <aiVectorKey>

template <>
struct Interpolator <aiQuatKey>		{
	void operator () (aiQuaternion& out, const aiQuatKey a,
		const aiQuatKey& b, float d) const
	{
		Interpolator<aiQuaternion> ipl;
		ipl(out,a.mValue,b.mValue,d);
	}
}; // ! Interpolator <aiQuatKey>

template <>
struct Interpolator <aiMeshKey>		{
	void operator () (unsigned int& out, const aiMeshKey a,
		const aiMeshKey& b, float d) const
	{
		Interpolator<unsigned int> ipl;
		ipl(out,a.mValue,b.mValue,d);
	}
}; // ! Interpolator <aiQuatKey>

//! @endcond
} //  ! end namespace Assimp



#endif // __cplusplus
#endif // AI_ANIM_H_INC
