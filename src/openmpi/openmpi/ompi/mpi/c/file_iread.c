/*
 * Copyright (c) 2004-2005 The Trustees of Indiana University and Indiana
 *                         University Research and Technology
 *                         Corporation.  All rights reserved.
 * Copyright (c) 2004-2005 The University of Tennessee and The University
 *                         of Tennessee Research Foundation.  All rights
 *                         reserved.
 * Copyright (c) 2004-2005 High Performance Computing Center Stuttgart, 
 *                         University of Stuttgart.  All rights reserved.
 * Copyright (c) 2004-2005 The Regents of the University of California.
 *                         All rights reserved.
 * $COPYRIGHT$
 * 
 * Additional copyrights may follow
 * 
 * $HEADER$
 */

#include "ompi_config.h"

#include "ompi/mpi/c/bindings.h"
#include "ompi/datatype/datatype.h"
#include "ompi/file/file.h"
#include "ompi/mca/io/io.h"
#include "ompi/mca/io/base/io_base_request.h"

#if OMPI_HAVE_WEAK_SYMBOLS && OMPI_PROFILING_DEFINES
#pragma weak MPI_File_iread = PMPI_File_iread
#endif

#if OMPI_PROFILING_DEFINES
#include "ompi/mpi/c/profile/defines.h"
#endif

static const char FUNC_NAME[] = "MPI_File_iread";


int MPI_File_iread(MPI_File fh, void *buf, int count, 
                   MPI_Datatype datatype, MPI_Request *request)
{
    int rc;
    mca_io_base_request_t *io_request;

    if (MPI_PARAM_CHECK) {
        rc = MPI_SUCCESS;
        OMPI_ERR_INIT_FINALIZE(FUNC_NAME);
        if (ompi_file_invalid(fh)) {
            fh = MPI_FILE_NULL;
            rc = MPI_ERR_FILE;
        } else if (count < 0) {
            rc = MPI_ERR_COUNT;
        } else {
           OMPI_CHECK_DATATYPE_FOR_RECV(rc, datatype, count);
        }
        OMPI_ERRHANDLER_CHECK(rc, fh, rc, FUNC_NAME);
    }

    /* Get a request */

    if (OMPI_SUCCESS != mca_io_base_request_alloc(fh, &io_request)) {
        return OMPI_ERRHANDLER_INVOKE(fh, MPI_ERR_NO_MEM, FUNC_NAME);
    }
    *request = (ompi_request_t*) io_request;

    /* Call the back-end io component function */

    switch (fh->f_io_version) {
    case MCA_IO_BASE_V_1_0_0:
        rc = fh->f_io_selected_module.v1_0_0.
            io_module_file_iread(fh, buf, count, datatype, io_request);
        break;

    default:
        rc = MPI_ERR_INTERN;
        break;
    }

    /* All done */
    
    OMPI_ERRHANDLER_RETURN(rc, fh, rc, FUNC_NAME);
}
