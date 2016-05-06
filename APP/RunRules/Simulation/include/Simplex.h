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
/*---------------------------- Interface ReadRows ----------------------------*/
/*----------------------------------------------------------------------------*/




/**
 * \brief Basic static function for the interface 'ReadRows'.
 * 
 * \param [in] param_count Interface Parameter "count".
 * \param [in] param_rowlen Interface Parameter "rowlen".
 * \param [in] param_start Interface Parameter "start".
 * \param [out] outstream_rows_fromlmem The stream should be of size ((param_count * param_rowlen) * 4) bytes.
 */
void Simplex_ReadRows(
	uint32_t param_count,
	uint32_t param_rowlen,
	uint32_t param_start,
	float *outstream_rows_fromlmem);

/**
 * \brief Basic static non-blocking function for the interface 'ReadRows'.
 * 
 * Schedule to run on an engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 * 
 * 
 * \param [in] param_count Interface Parameter "count".
 * \param [in] param_rowlen Interface Parameter "rowlen".
 * \param [in] param_start Interface Parameter "start".
 * \param [out] outstream_rows_fromlmem The stream should be of size ((param_count * param_rowlen) * 4) bytes.
 * \return A handle on the execution status, or NULL in case of error.
 */
max_run_t *Simplex_ReadRows_nonblock(
	uint32_t param_count,
	uint32_t param_rowlen,
	uint32_t param_start,
	float *outstream_rows_fromlmem);

/**
 * \brief Advanced static interface, structure for the engine interface 'ReadRows'
 * 
 */
typedef struct { 
	uint32_t param_count; /**<  [in] Interface Parameter "count". */
	uint32_t param_rowlen; /**<  [in] Interface Parameter "rowlen". */
	uint32_t param_start; /**<  [in] Interface Parameter "start". */
	float *outstream_rows_fromlmem; /**<  [out] The stream should be of size ((param_count * param_rowlen) * 4) bytes. */
} Simplex_ReadRows_actions_t;

/**
 * \brief Advanced static function for the interface 'ReadRows'.
 * 
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in,out] interface_actions Actions to be executed.
 */
void Simplex_ReadRows_run(
	max_engine_t *engine,
	Simplex_ReadRows_actions_t *interface_actions);

/**
 * \brief Advanced static non-blocking function for the interface 'ReadRows'.
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
max_run_t *Simplex_ReadRows_run_nonblock(
	max_engine_t *engine,
	Simplex_ReadRows_actions_t *interface_actions);

/**
 * \brief Group run advanced static function for the interface 'ReadRows'.
 * 
 * \param [in] group Group to use.
 * \param [in,out] interface_actions Actions to run.
 *
 * Run the actions on the first device available in the group.
 */
void Simplex_ReadRows_run_group(max_group_t *group, Simplex_ReadRows_actions_t *interface_actions);

/**
 * \brief Group run advanced static non-blocking function for the interface 'ReadRows'.
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
max_run_t *Simplex_ReadRows_run_group_nonblock(max_group_t *group, Simplex_ReadRows_actions_t *interface_actions);

/**
 * \brief Array run advanced static function for the interface 'ReadRows'.
 * 
 * \param [in] engarray The array of devices to use.
 * \param [in,out] interface_actions The array of actions to run.
 *
 * Run the array of actions on the array of engines.  The length of interface_actions
 * must match the size of engarray.
 */
void Simplex_ReadRows_run_array(max_engarray_t *engarray, Simplex_ReadRows_actions_t *interface_actions[]);

/**
 * \brief Array run advanced static non-blocking function for the interface 'ReadRows'.
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
max_run_t *Simplex_ReadRows_run_array_nonblock(max_engarray_t *engarray, Simplex_ReadRows_actions_t *interface_actions[]);

/**
 * \brief Converts a static-interface action struct into a dynamic-interface max_actions_t struct.
 *
 * Note that this is an internal utility function used by other functions in the static interface.
 *
 * \param [in] maxfile The maxfile to use.
 * \param [in] interface_actions The interface-specific actions to run.
 * \return The dynamic-interface actions to run, or NULL in case of error.
 */
max_actions_t* Simplex_ReadRows_convert(max_file_t *maxfile, Simplex_ReadRows_actions_t *interface_actions);



/*----------------------------------------------------------------------------*/
/*--------------------------- Interface WriteRows ----------------------------*/
/*----------------------------------------------------------------------------*/




/**
 * \brief Basic static function for the interface 'WriteRows'.
 * 
 * \param [in] param_count Interface Parameter "count".
 * \param [in] param_rowlen Interface Parameter "rowlen".
 * \param [in] param_start Interface Parameter "start".
 * \param [in] instream_rows_tolmem The stream should be of size ((param_count * param_rowlen) * 4) bytes.
 */
void Simplex_WriteRows(
	uint32_t param_count,
	uint32_t param_rowlen,
	uint32_t param_start,
	const float *instream_rows_tolmem);

/**
 * \brief Basic static non-blocking function for the interface 'WriteRows'.
 * 
 * Schedule to run on an engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 * 
 * 
 * \param [in] param_count Interface Parameter "count".
 * \param [in] param_rowlen Interface Parameter "rowlen".
 * \param [in] param_start Interface Parameter "start".
 * \param [in] instream_rows_tolmem The stream should be of size ((param_count * param_rowlen) * 4) bytes.
 * \return A handle on the execution status, or NULL in case of error.
 */
max_run_t *Simplex_WriteRows_nonblock(
	uint32_t param_count,
	uint32_t param_rowlen,
	uint32_t param_start,
	const float *instream_rows_tolmem);

/**
 * \brief Advanced static interface, structure for the engine interface 'WriteRows'
 * 
 */
typedef struct { 
	uint32_t param_count; /**<  [in] Interface Parameter "count". */
	uint32_t param_rowlen; /**<  [in] Interface Parameter "rowlen". */
	uint32_t param_start; /**<  [in] Interface Parameter "start". */
	const float *instream_rows_tolmem; /**<  [in] The stream should be of size ((param_count * param_rowlen) * 4) bytes. */
} Simplex_WriteRows_actions_t;

/**
 * \brief Advanced static function for the interface 'WriteRows'.
 * 
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in,out] interface_actions Actions to be executed.
 */
void Simplex_WriteRows_run(
	max_engine_t *engine,
	Simplex_WriteRows_actions_t *interface_actions);

/**
 * \brief Advanced static non-blocking function for the interface 'WriteRows'.
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
max_run_t *Simplex_WriteRows_run_nonblock(
	max_engine_t *engine,
	Simplex_WriteRows_actions_t *interface_actions);

/**
 * \brief Group run advanced static function for the interface 'WriteRows'.
 * 
 * \param [in] group Group to use.
 * \param [in,out] interface_actions Actions to run.
 *
 * Run the actions on the first device available in the group.
 */
void Simplex_WriteRows_run_group(max_group_t *group, Simplex_WriteRows_actions_t *interface_actions);

/**
 * \brief Group run advanced static non-blocking function for the interface 'WriteRows'.
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
max_run_t *Simplex_WriteRows_run_group_nonblock(max_group_t *group, Simplex_WriteRows_actions_t *interface_actions);

/**
 * \brief Array run advanced static function for the interface 'WriteRows'.
 * 
 * \param [in] engarray The array of devices to use.
 * \param [in,out] interface_actions The array of actions to run.
 *
 * Run the array of actions on the array of engines.  The length of interface_actions
 * must match the size of engarray.
 */
void Simplex_WriteRows_run_array(max_engarray_t *engarray, Simplex_WriteRows_actions_t *interface_actions[]);

/**
 * \brief Array run advanced static non-blocking function for the interface 'WriteRows'.
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
max_run_t *Simplex_WriteRows_run_array_nonblock(max_engarray_t *engarray, Simplex_WriteRows_actions_t *interface_actions[]);

/**
 * \brief Converts a static-interface action struct into a dynamic-interface max_actions_t struct.
 *
 * Note that this is an internal utility function used by other functions in the static interface.
 *
 * \param [in] maxfile The maxfile to use.
 * \param [in] interface_actions The interface-specific actions to run.
 * \return The dynamic-interface actions to run, or NULL in case of error.
 */
max_actions_t* Simplex_WriteRows_convert(max_file_t *maxfile, Simplex_WriteRows_actions_t *interface_actions);



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
 * \param [in] instream_pivot_col The stream should be of size (param_m * 4) bytes.
 * \param [in] instream_pivot_row The stream should be of size (param_n * 4) bytes.
 * \param [out] outstream_cost The stream should be of size (param_n * 4) bytes.
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
	const float *instream_pivot_col,
	const float *instream_pivot_row,
	float *outstream_cost,
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
 * \param [in] instream_pivot_col The stream should be of size (param_m * 4) bytes.
 * \param [in] instream_pivot_row The stream should be of size (param_n * 4) bytes.
 * \param [out] outstream_cost The stream should be of size (param_n * 4) bytes.
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
	const float *instream_pivot_col,
	const float *instream_pivot_row,
	float *outstream_cost,
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
	const float *instream_pivot_col; /**<  [in] The stream should be of size (param_m * 4) bytes. */
	const float *instream_pivot_row; /**<  [in] The stream should be of size (param_n * 4) bytes. */
	float *outstream_cost; /**<  [out] The stream should be of size (param_n * 4) bytes. */
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

