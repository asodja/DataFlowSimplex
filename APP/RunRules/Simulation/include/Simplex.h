/**\file */
#ifndef SLIC_DECLARATIONS_Simplex_H
#define SLIC_DECLARATIONS_Simplex_H
#include "MaxSLiCInterface.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define Simplex_FMEM_DEPTH (10240)
#define Simplex_STREAM_FREQUENCY (150)
#define Simplex_LMEM_FREQUENCY ("MAX3_333")
#define Simplex_VECTOR_DEPTH (24)
#define Simplex_PCIE_ALIGNMENT (16)


/*----------------------------------------------------------------------------*/
/*--------------------------- Interface writeLMem ----------------------------*/
/*----------------------------------------------------------------------------*/




/**
 * \brief Basic static function for the interface 'writeLMem'.
 * 
 * \param [in] param_address Interface Parameter "address".
 * \param [in] param_count Interface Parameter "count".
 * \param [in] instream_tolmem The stream should be of size (param_count * 4) bytes.
 */
void Simplex_writeLMem(
	uint32_t param_address,
	uint32_t param_count,
	const float *instream_tolmem);

/**
 * \brief Basic static non-blocking function for the interface 'writeLMem'.
 * 
 * Schedule to run on an engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 * 
 * 
 * \param [in] param_address Interface Parameter "address".
 * \param [in] param_count Interface Parameter "count".
 * \param [in] instream_tolmem The stream should be of size (param_count * 4) bytes.
 * \return A handle on the execution status, or NULL in case of error.
 */
max_run_t *Simplex_writeLMem_nonblock(
	uint32_t param_address,
	uint32_t param_count,
	const float *instream_tolmem);

/**
 * \brief Advanced static interface, structure for the engine interface 'writeLMem'
 * 
 */
typedef struct { 
	uint32_t param_address; /**<  [in] Interface Parameter "address". */
	uint32_t param_count; /**<  [in] Interface Parameter "count". */
	const float *instream_tolmem; /**<  [in] The stream should be of size (param_count * 4) bytes. */
} Simplex_writeLMem_actions_t;

/**
 * \brief Advanced static function for the interface 'writeLMem'.
 * 
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in,out] interface_actions Actions to be executed.
 */
void Simplex_writeLMem_run(
	max_engine_t *engine,
	Simplex_writeLMem_actions_t *interface_actions);

/**
 * \brief Advanced static non-blocking function for the interface 'writeLMem'.
 *
 * Schedule the actions to run on the engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * 
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in] interface_actions Actions to be executed.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *Simplex_writeLMem_run_nonblock(
	max_engine_t *engine,
	Simplex_writeLMem_actions_t *interface_actions);

/**
 * \brief Group run advanced static function for the interface 'writeLMem'.
 * 
 * \param [in] group Group to use.
 * \param [in,out] interface_actions Actions to run.
 *
 * Run the actions on the first device available in the group.
 */
void Simplex_writeLMem_run_group(max_group_t *group, Simplex_writeLMem_actions_t *interface_actions);

/**
 * \brief Group run advanced static non-blocking function for the interface 'writeLMem'.
 * 
 *
 * Schedule the actions to run on the first device available in the group and return immediately.
 * The status of the run must be checked with ::max_wait. 
 * Note that use of ::max_nowait is prohibited with non-blocking running on groups:
 * see the ::max_run_group_nonblock documentation for more explanation.
 *
 * \param [in] group Group to use.
 * \param [in] interface_actions Actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *Simplex_writeLMem_run_group_nonblock(max_group_t *group, Simplex_writeLMem_actions_t *interface_actions);

/**
 * \brief Array run advanced static function for the interface 'writeLMem'.
 * 
 * \param [in] engarray The array of devices to use.
 * \param [in,out] interface_actions The array of actions to run.
 *
 * Run the array of actions on the array of engines.  The length of interface_actions
 * must match the size of engarray.
 */
void Simplex_writeLMem_run_array(max_engarray_t *engarray, Simplex_writeLMem_actions_t *interface_actions[]);

/**
 * \brief Array run advanced static non-blocking function for the interface 'writeLMem'.
 * 
 *
 * Schedule to run the array of actions on the array of engines, and return immediately.
 * The length of interface_actions must match the size of engarray.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * \param [in] engarray The array of devices to use.
 * \param [in] interface_actions The array of actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *Simplex_writeLMem_run_array_nonblock(max_engarray_t *engarray, Simplex_writeLMem_actions_t *interface_actions[]);

/**
 * \brief Converts a static-interface action struct into a dynamic-interface max_actions_t struct.
 *
 * Note that this is an internal utility function used by other functions in the static interface.
 *
 * \param [in] maxfile The maxfile to use.
 * \param [in] interface_actions The interface-specific actions to run.
 * \return The dynamic-interface actions to run, or NULL in case of error.
 */
max_actions_t* Simplex_writeLMem_convert(max_file_t *maxfile, Simplex_writeLMem_actions_t *interface_actions);



/*----------------------------------------------------------------------------*/
/*---------------------------- Interface readLMem ----------------------------*/
/*----------------------------------------------------------------------------*/




/**
 * \brief Basic static function for the interface 'readLMem'.
 * 
 * \param [in] param_address Interface Parameter "address".
 * \param [in] param_count Interface Parameter "count".
 * \param [out] outstream_fromlmem The stream should be of size (param_count * 4) bytes.
 */
void Simplex_readLMem(
	uint32_t param_address,
	uint32_t param_count,
	float *outstream_fromlmem);

/**
 * \brief Basic static non-blocking function for the interface 'readLMem'.
 * 
 * Schedule to run on an engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 * 
 * 
 * \param [in] param_address Interface Parameter "address".
 * \param [in] param_count Interface Parameter "count".
 * \param [out] outstream_fromlmem The stream should be of size (param_count * 4) bytes.
 * \return A handle on the execution status, or NULL in case of error.
 */
max_run_t *Simplex_readLMem_nonblock(
	uint32_t param_address,
	uint32_t param_count,
	float *outstream_fromlmem);

/**
 * \brief Advanced static interface, structure for the engine interface 'readLMem'
 * 
 */
typedef struct { 
	uint32_t param_address; /**<  [in] Interface Parameter "address". */
	uint32_t param_count; /**<  [in] Interface Parameter "count". */
	float *outstream_fromlmem; /**<  [out] The stream should be of size (param_count * 4) bytes. */
} Simplex_readLMem_actions_t;

/**
 * \brief Advanced static function for the interface 'readLMem'.
 * 
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in,out] interface_actions Actions to be executed.
 */
void Simplex_readLMem_run(
	max_engine_t *engine,
	Simplex_readLMem_actions_t *interface_actions);

/**
 * \brief Advanced static non-blocking function for the interface 'readLMem'.
 *
 * Schedule the actions to run on the engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * 
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in] interface_actions Actions to be executed.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *Simplex_readLMem_run_nonblock(
	max_engine_t *engine,
	Simplex_readLMem_actions_t *interface_actions);

/**
 * \brief Group run advanced static function for the interface 'readLMem'.
 * 
 * \param [in] group Group to use.
 * \param [in,out] interface_actions Actions to run.
 *
 * Run the actions on the first device available in the group.
 */
void Simplex_readLMem_run_group(max_group_t *group, Simplex_readLMem_actions_t *interface_actions);

/**
 * \brief Group run advanced static non-blocking function for the interface 'readLMem'.
 * 
 *
 * Schedule the actions to run on the first device available in the group and return immediately.
 * The status of the run must be checked with ::max_wait. 
 * Note that use of ::max_nowait is prohibited with non-blocking running on groups:
 * see the ::max_run_group_nonblock documentation for more explanation.
 *
 * \param [in] group Group to use.
 * \param [in] interface_actions Actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *Simplex_readLMem_run_group_nonblock(max_group_t *group, Simplex_readLMem_actions_t *interface_actions);

/**
 * \brief Array run advanced static function for the interface 'readLMem'.
 * 
 * \param [in] engarray The array of devices to use.
 * \param [in,out] interface_actions The array of actions to run.
 *
 * Run the array of actions on the array of engines.  The length of interface_actions
 * must match the size of engarray.
 */
void Simplex_readLMem_run_array(max_engarray_t *engarray, Simplex_readLMem_actions_t *interface_actions[]);

/**
 * \brief Array run advanced static non-blocking function for the interface 'readLMem'.
 * 
 *
 * Schedule to run the array of actions on the array of engines, and return immediately.
 * The length of interface_actions must match the size of engarray.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * \param [in] engarray The array of devices to use.
 * \param [in] interface_actions The array of actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *Simplex_readLMem_run_array_nonblock(max_engarray_t *engarray, Simplex_readLMem_actions_t *interface_actions[]);

/**
 * \brief Converts a static-interface action struct into a dynamic-interface max_actions_t struct.
 *
 * Note that this is an internal utility function used by other functions in the static interface.
 *
 * \param [in] maxfile The maxfile to use.
 * \param [in] interface_actions The interface-specific actions to run.
 * \return The dynamic-interface actions to run, or NULL in case of error.
 */
max_actions_t* Simplex_readLMem_convert(max_file_t *maxfile, Simplex_readLMem_actions_t *interface_actions);



/*----------------------------------------------------------------------------*/
/*---------------------------- Interface default -----------------------------*/
/*----------------------------------------------------------------------------*/



/**
 * \brief Auxiliary function to evaluate expression for "MaxKernel.loopLength".
 */
int Simplex_get_MaxKernel_loopLength( void );


/**
 * \brief Basic static function for the interface 'default'.
 * 
 * \param [in] param_col Interface Parameter "col".
 * \param [in] param_m Interface Parameter "m".
 * \param [in] param_n Interface Parameter "n".
 * \param [in] param_pivot Interface Parameter "pivot".
 * \param [in] param_row Interface Parameter "row".
 * \param [out] outscalar_MaxKernel_maxcol_out Output scalar parameter "MaxKernel.maxcol_out".
 * \param [in] instream_pivcol The stream should be of size (param_m * 4) bytes.
 * \param [in] instream_pivrow The stream should be of size (param_n * 4) bytes.
 * \param [out] outstream_c_out The stream should be of size (param_n * 4) bytes.
 * \param [out] outstream_pivcol_out The stream should be of size (param_m * 4) bytes.
 * \param [out] outstream_ratio_out The stream should be of size (param_m * 4) bytes.
 */
void Simplex(
	uint32_t param_col,
	uint32_t param_m,
	uint32_t param_n,
	float param_pivot,
	uint32_t param_row,
	uint64_t *outscalar_MaxKernel_maxcol_out,
	const float *instream_pivcol,
	const float *instream_pivrow,
	float *outstream_c_out,
	float *outstream_pivcol_out,
	float *outstream_ratio_out);

/**
 * \brief Basic static non-blocking function for the interface 'default'.
 * 
 * Schedule to run on an engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 * 
 * 
 * \param [in] param_col Interface Parameter "col".
 * \param [in] param_m Interface Parameter "m".
 * \param [in] param_n Interface Parameter "n".
 * \param [in] param_pivot Interface Parameter "pivot".
 * \param [in] param_row Interface Parameter "row".
 * \param [out] outscalar_MaxKernel_maxcol_out Output scalar parameter "MaxKernel.maxcol_out".
 * \param [in] instream_pivcol The stream should be of size (param_m * 4) bytes.
 * \param [in] instream_pivrow The stream should be of size (param_n * 4) bytes.
 * \param [out] outstream_c_out The stream should be of size (param_n * 4) bytes.
 * \param [out] outstream_pivcol_out The stream should be of size (param_m * 4) bytes.
 * \param [out] outstream_ratio_out The stream should be of size (param_m * 4) bytes.
 * \return A handle on the execution status, or NULL in case of error.
 */
max_run_t *Simplex_nonblock(
	uint32_t param_col,
	uint32_t param_m,
	uint32_t param_n,
	float param_pivot,
	uint32_t param_row,
	uint64_t *outscalar_MaxKernel_maxcol_out,
	const float *instream_pivcol,
	const float *instream_pivrow,
	float *outstream_c_out,
	float *outstream_pivcol_out,
	float *outstream_ratio_out);

/**
 * \brief Advanced static interface, structure for the engine interface 'default'
 * 
 */
typedef struct { 
	uint32_t param_col; /**<  [in] Interface Parameter "col". */
	uint32_t param_m; /**<  [in] Interface Parameter "m". */
	uint32_t param_n; /**<  [in] Interface Parameter "n". */
	float param_pivot; /**<  [in] Interface Parameter "pivot". */
	uint32_t param_row; /**<  [in] Interface Parameter "row". */
	uint64_t *outscalar_MaxKernel_maxcol_out; /**<  [out] Output scalar parameter "MaxKernel.maxcol_out". */
	const float *instream_pivcol; /**<  [in] The stream should be of size (param_m * 4) bytes. */
	const float *instream_pivrow; /**<  [in] The stream should be of size (param_n * 4) bytes. */
	float *outstream_c_out; /**<  [out] The stream should be of size (param_n * 4) bytes. */
	float *outstream_pivcol_out; /**<  [out] The stream should be of size (param_m * 4) bytes. */
	float *outstream_ratio_out; /**<  [out] The stream should be of size (param_m * 4) bytes. */
} Simplex_actions_t;

/**
 * \brief Advanced static function for the interface 'default'.
 * 
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in,out] interface_actions Actions to be executed.
 */
void Simplex_run(
	max_engine_t *engine,
	Simplex_actions_t *interface_actions);

/**
 * \brief Advanced static non-blocking function for the interface 'default'.
 *
 * Schedule the actions to run on the engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * 
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in] interface_actions Actions to be executed.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *Simplex_run_nonblock(
	max_engine_t *engine,
	Simplex_actions_t *interface_actions);

/**
 * \brief Group run advanced static function for the interface 'default'.
 * 
 * \param [in] group Group to use.
 * \param [in,out] interface_actions Actions to run.
 *
 * Run the actions on the first device available in the group.
 */
void Simplex_run_group(max_group_t *group, Simplex_actions_t *interface_actions);

/**
 * \brief Group run advanced static non-blocking function for the interface 'default'.
 * 
 *
 * Schedule the actions to run on the first device available in the group and return immediately.
 * The status of the run must be checked with ::max_wait. 
 * Note that use of ::max_nowait is prohibited with non-blocking running on groups:
 * see the ::max_run_group_nonblock documentation for more explanation.
 *
 * \param [in] group Group to use.
 * \param [in] interface_actions Actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *Simplex_run_group_nonblock(max_group_t *group, Simplex_actions_t *interface_actions);

/**
 * \brief Array run advanced static function for the interface 'default'.
 * 
 * \param [in] engarray The array of devices to use.
 * \param [in,out] interface_actions The array of actions to run.
 *
 * Run the array of actions on the array of engines.  The length of interface_actions
 * must match the size of engarray.
 */
void Simplex_run_array(max_engarray_t *engarray, Simplex_actions_t *interface_actions[]);

/**
 * \brief Array run advanced static non-blocking function for the interface 'default'.
 * 
 *
 * Schedule to run the array of actions on the array of engines, and return immediately.
 * The length of interface_actions must match the size of engarray.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * \param [in] engarray The array of devices to use.
 * \param [in] interface_actions The array of actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *Simplex_run_array_nonblock(max_engarray_t *engarray, Simplex_actions_t *interface_actions[]);

/**
 * \brief Converts a static-interface action struct into a dynamic-interface max_actions_t struct.
 *
 * Note that this is an internal utility function used by other functions in the static interface.
 *
 * \param [in] maxfile The maxfile to use.
 * \param [in] interface_actions The interface-specific actions to run.
 * \return The dynamic-interface actions to run, or NULL in case of error.
 */
max_actions_t* Simplex_convert(max_file_t *maxfile, Simplex_actions_t *interface_actions);

/**
 * \brief Initialise a maxfile.
 */
max_file_t* Simplex_init(void);

/* Error handling functions */
int Simplex_has_errors(void);
const char* Simplex_get_errors(void);
void Simplex_clear_errors(void);
/* Free statically allocated maxfile data */
void Simplex_free(void);
/* returns: -1 = error running command; 0 = no error reported */
int Simplex_simulator_start(void);
/* returns: -1 = error running command; 0 = no error reported */
int Simplex_simulator_stop(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* SLIC_DECLARATIONS_Simplex_H */

