/*! @file Var.h
	@brief %IPhreeqc VARIANT Documentation
*/
// Var.h

#ifndef __VAR_H_INC
#define __VAR_H_INC

#if defined(_WINDLL)
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

/*! \brief Enumeration used to determine the type of data stored in a VAR.
*/
typedef enum {
	TT_EMPTY  = 0,  /*!< VAR contains no data */
	TT_ERROR  = 1,  /*!< vresult is valid */
	TT_LONG   = 2,  /*!< lVal is valid */
	TT_DOUBLE = 3,  /*!< dVal is valid */
	TT_STRING = 4   /*!< sVal is valid */
} VAR_TYPE;

/*! \brief Enumeration used to return error codes.
*/
typedef enum {
	VR_OK            =  0,  /*!< Success */
	VR_OUTOFMEMORY   = -1,  /*!< Failure, Out of memory */
	VR_BADVARTYPE    = -2,  /*!< Failure, Invalid VAR type */
	VR_INVALIDARG    = -3,  /*!< Failure, Invalid argument */
	VR_INVALIDROW    = -4,  /*!< Failure, Invalid row */
	VR_INVALIDCOL    = -5   /*!< Failure, Invalid column */
} VRESULT;

/*! \brief Datatype used to store SELECTED_OUTPUT values.
*/
typedef struct {
	VAR_TYPE type;         /*!< holds datatype of <code>VAR</code>          */
	union {
		long    lVal;      /*!< valid when <code>(type == TT_LONG)</code>   */
		double  dVal;      /*!< valid when <code>(type == TT_DOUBLE)</code> */
		char*   sVal;      /*!< valid when <code>(type == TT_STRING)</code> */
		VRESULT vresult;   /*!< valid when <code>(type == TT_ERROR)</code>  */
	};
} VAR;


#if defined(__cplusplus)
extern "C" {
#endif

/** Initializes a VAR.
 *  @param pvar Pointer to the VAR that will be initialized.
 */
DLL_EXPORT void VarInit(VAR* pvar);

/** Clears a VAR.
 *  @param pvar Pointer to the VAR that will be freed and initialized.
 *  @retval VR_OK Success.
 *  @retval VR_BADVARTYPE The \c VAR was invalid (probably uninitialized).
 */
DLL_EXPORT VRESULT VarClear(VAR* pvar);

/** Frees the destination VAR and makes a copy of the source VAR.
 *  @param pvarDest Pointer to the VAR to receive the copy.
 *  @param pvarSrc Pointer to the VAR to be copied.
 *  @retval VR_OK Success.
 *  @retval VR_BADVARTYPE The source and/or the destination are invalid (usually uninitialized).
 *  @retval VR_OUTOFMEMORY Memory could not be allocated for the copy.
 *  @return The return value is one of the following.
 */
DLL_EXPORT VRESULT VarCopy(VAR* pvarDest, const VAR* pvarSrc);


/** Allocates a new string for use in a VAR and copies the passed string into it.
 *  @param pSrc Pointer to the VAR that will be initialized.
 *  @return A pointer to the string on success NULL otherwise.
 */
DLL_EXPORT char* VarAllocString(const char* pSrc);

/** Frees a string allocated using VarAllocString.
 *  @param pSrc Pointer to the string to be freed.
 */
DLL_EXPORT void VarFreeString(char* pSrc);

#if defined(__cplusplus)
}
#endif

#if defined(__cplusplus)

#include <ostream> // std::ostream

inline std::ostream& operator<< (std::ostream &os, const VAR_TYPE& vt)
{
	switch(vt)
	{
	case TT_EMPTY:
		os << "TT_EMPTY";
		break;
	case TT_ERROR:
		os << "TT_ERROR";
		break;
	case TT_LONG:
		os << "TT_LONG";
		break;
	case TT_DOUBLE:
		os << "TT_DOUBLE";
		break;
	case TT_STRING:
		os << "TT_STRING";
		break;
	default:
		os << (int)vt;
		break;
	}
	return os;
}

inline std::ostream& operator<< (std::ostream &os, const VRESULT& vr)
{
	switch(vr)
	{
	case VR_OK:
		os << "VR_OK";
		break;
	case VR_OUTOFMEMORY:
		os << "VR_OUTOFMEMORY";
		break;
	case VR_BADVARTYPE:
		os << "VR_BADVARTYPE";
		break;
	case VR_INVALIDARG:
		os << "VR_INVALIDARG";
		break;
	case VR_INVALIDROW:
		os << "VR_INVALIDROW";
		break;
	case VR_INVALIDCOL:
		os << "VR_INVALIDCOL";
		break;
	default:
		os << (int)vr;
		break;
	}
	return os;
}
#endif /* __cplusplus */

#endif /* __VAR_H_INC */
