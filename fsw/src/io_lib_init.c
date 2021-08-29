/*************************************************************************
* File: io_lib_init.c
**
** Copyright 2017 United States Government as represented by the Administrator
** of the National Aeronautics and Space Administration.  No copyright is
** claimed in the United States under Title 17, U.S. Code.
** All Other Rights Reserved.
**
*************************************************************************/

/*************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"
#include "cfe_evs.h"
#include "cfe_evs_extern_typedefs.h"
#include "io_lib.h"

#include "tmtf.h"
#include "tm_sync.h"
#include "tc_sync.h"

/*************************************************************************
** Macro Definitions
*************************************************************************/
IO_LIB_LibData_t    g_IO_LIB_LibData;


/*************************************************************************
** Protocol Library Init Functions
*************************************************************************/
extern int32 TMTF_LibInit(void);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* CFS Library Initialization Routine                              */
/* cFE requires that a library have an initialization routine      */ 
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 IO_LibInit(void)
{
    CFE_Status_t iStatus = CFE_SUCCESS;

    /* Perform any library initializations */
    // iStatus = TMTF_LibInit();
    // iStatus |= TM_SYNC_LibInit(); 
    // iStatus |= TC_SYNC_LibInit(); 

    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("IO_Lib Init failed.\n");
    }


    CFE_PSP_MemSet((void*) g_IO_LIB_LibData.EventTbl, 0x00, sizeof(g_IO_LIB_LibData.EventTbl));

    g_IO_LIB_LibData.EventTbl[0].EventID = IO_LIB_RESERVED_EID;
    g_IO_LIB_LibData.EventTbl[1].EventID = IO_LIB_INF_EID;
    g_IO_LIB_LibData.EventTbl[2].EventID = IO_LIB_ERR_EID;
    g_IO_LIB_LibData.EventTbl[3].EventID = IO_LIB_FORMAT_INF_EID;
    g_IO_LIB_LibData.EventTbl[4].EventID = IO_LIB_SERVICE_INF_EID;
    g_IO_LIB_LibData.EventTbl[5].EventID = IO_LIB_FORMAT_ERR_EID;

    g_IO_LIB_LibData.EventTbl[ 6].EventID = IO_LIB_SERVICE_ERR_EID;
    g_IO_LIB_LibData.EventTbl[ 7].EventID = IO_LIB_TRANS_UDP_EID;
    g_IO_LIB_LibData.EventTbl[ 8].EventID = IO_LIB_TRANS_RS422_EID;
    g_IO_LIB_LibData.EventTbl[ 9].EventID = IO_LIB_TRANS_SELECT_EID;
    g_IO_LIB_LibData.EventTbl[10].EventID = IO_LIB_COP1_EID;
    g_IO_LIB_LibData.EventTbl[11].EventID = IO_LIB_TM_SDLP_EID;
    
    /* Register the table with CFE */
    iStatus = CFE_EVS_Register(g_IO_LIB_LibData.EventTbl, IO_LIB_EVT_CNT, CFE_EVS_EventFilter_BINARY);
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("IO Lib: Failed to register with EVS (0x%08X)\n", iStatus);
        switch (iStatus) {
            case CFE_SUCCESS: // Sucessful execution.
                CFE_ES_WriteToSysLog("IO Lib: CFE_SUCCESS\n");
                break;
            case CFE_EVS_APP_FILTER_OVERLOAD: // Application Filter Overload.
                CFE_ES_WriteToSysLog("IO Lib: CFE_EVS_APP_FILTER_OVERLOAD\n");
                break;
            case CFE_EVS_UNKNOWN_FILTER: // Unknown Filter.
                CFE_ES_WriteToSysLog("IO Lib: CFE_EVS_UNKNOWN_FILTER\n");
                break;
            case CFE_EVS_APP_ILLEGAL_APP_ID: // Illegal Application ID. 
                CFE_ES_WriteToSysLog("IO Lib: CFE_EVS_APP_ILLEGAL_APP_ID\n");
                break;
            default:
                CFE_ES_WriteToSysLog("IO Lib: UNKOWN ERROR\n");
                break;
        }
    }
    else
    {
        CFE_ES_WriteToSysLog("IO Lib Initialized.  Version %d.%d.%d.%d\n",
                IO_LIB_MAJOR_VERSION,
                IO_LIB_MINOR_VERSION, 
                IO_LIB_REVISION, 
                IO_LIB_MISSION_REV);
    }

    return iStatus;

}/* End CFS_LibInit */
