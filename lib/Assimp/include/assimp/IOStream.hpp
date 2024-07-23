/** @file IOStream.h
 *  @brief File I/O wrappers for C++. 
 */

#ifndef AI_IOSTREAM_H_INC
#define AI_IOSTREAM_H_INC

#include "types.h"

#ifndef __cplusplus
#	error This header requires C++ to be used. aiFileIO.h is the \
	corresponding C interface.
#endif

namespace Assimp	{

// ----------------------------------------------------------------------------------
/** @brief CPP-API: Class to handle file I/O for C++
 *
 *  Derive an own implementation from this interface to provide custom IO handling
 *  to the Importer. If you implement this interface, be sure to also provide an
 *  implementation for IOSystem that creates instances of your custom IO class.
*/
class ASSIMP_API IOStream : public Intern::AllocateFromAssimpHeap
{
protected:
	/** Constructor protected, use IOSystem::Open() to create an instance. */
	IOStream(void);

public:
	// -------------------------------------------------------------------
	/** @brief Destructor. Deleting the object closes the underlying file, 
	 * alternatively you may use IOSystem::Close() to release the file. 
	 */
	virtual ~IOStream();

	// -------------------------------------------------------------------
	/** @brief Read from the file
	 *
	 * See fread() for more details
	 * This fails for write-only files */
    virtual size_t Read(void* pvBuffer, 
		size_t pSize, 
		size_t pCount) = 0;

	// -------------------------------------------------------------------
	/** @brief Write to the file
	*
	* See fwrite() for more details
	* This fails for read-only files */
    virtual size_t Write(const void* pvBuffer, 
		size_t pSize,
		size_t pCount) = 0;

	// -------------------------------------------------------------------
	/** @brief Set the read/write cursor of the file
	 *
	 * Note that the offset is _negative_ for aiOrigin_END.
	 * See fseek() for more details */
	virtual aiReturn Seek(size_t pOffset,
		aiOrigin pOrigin) = 0;

	// -------------------------------------------------------------------
	/** @brief Get the current position of the read/write cursor
	 *
	 * See ftell() for more details */
    virtual size_t Tell() const = 0;

	// -------------------------------------------------------------------
	/**	@brief Returns filesize
	 *	Returns the filesize. */
	virtual size_t FileSize() const = 0;

	// -------------------------------------------------------------------
	/**	@brief Flush the contents of the file buffer (for writers) 
	 *	See fflush() for more details.
	 */
	virtual void Flush() = 0;
}; //! class IOStream

// ----------------------------------------------------------------------------------
inline IOStream::IOStream()
{
	// empty
}

// ----------------------------------------------------------------------------------
inline IOStream::~IOStream()
{
	// empty
}
// ----------------------------------------------------------------------------------
} //!namespace Assimp

#endif //!!AI_IOSTREAM_H_INC
