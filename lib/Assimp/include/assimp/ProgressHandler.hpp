/** @file ProgressHandler.h
 *  @brief Abstract base class 'ProgressHandler'.
 */
#ifndef INCLUDED_AI_PROGRESSHANDLER_H
#define INCLUDED_AI_PROGRESSHANDLER_H
#include "types.h"
namespace Assimp	{

// ------------------------------------------------------------------------------------
/** @brief CPP-API: Abstract interface for custom progress report receivers.
 *
 *  Each #Importer instance maintains its own #ProgressHandler. The default 
 *  implementation provided by Assimp doesn't do anything at all. */
class ASSIMP_API ProgressHandler 
	: public Intern::AllocateFromAssimpHeap	{
protected:
	/** @brief	Default constructor	*/
	ProgressHandler () {
	}
public:
	/** @brief	Virtual destructor	*/
	virtual ~ProgressHandler () {
	}

	// -------------------------------------------------------------------
	/** @brief Progress callback.
	 *  @param percentage An estimate of the current loading progress,
	 *    in percent. Or -1.f if such an estimate is not available.
	 *
	 *  There are restriction on what you may do from within your 
	 *  implementation of this method: no exceptions may be thrown and no
	 *  non-const #Importer methods may be called. It is 
	 *  not generally possible to predict the number of callbacks 
	 *  fired during a single import.
	 *
	 *  @return Return false to abort loading at the next possible
	 *   occasion (loaders and Assimp are generally allowed to perform
	 *   all needed cleanup tasks prior to returning control to the
	 *   caller). If the loading is aborted, #Importer::ReadFile()
	 *   returns always NULL.
	 *
	 *  @note Currently, percentage is always -1.f because there is 
	 *   no reliable way to compute it.
	 *   */
	virtual bool Update(float percentage = -1.f) = 0;



}; // !class ProgressHandler 
// ------------------------------------------------------------------------------------
} // Namespace Assimp

#endif
