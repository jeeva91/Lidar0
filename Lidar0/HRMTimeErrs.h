/****************************************************************************
 Copyright (c) 2008,       SensL Technologies LTD.      All Rights Reserved.
*****************************************************************************

   File          : HRMTimeErrs.h

   Author        : Steve Buckley

   Date          : 05-07-2008

   Function      : HRMTime error code definitions.

   Update        : 18-08-2008 
   By            : Steve Buckley
   Reason        : Add TIMEOUT error.
   				   All changes indicated by (2.01)         

****************************************************************************/

#define	 HRM_OK              (HRM_STATUS)0    /* No error                  */
#define  HRM_ERROR           (HRM_STATUS)1    /* Function error            */

#define  HRM_NO_LICENSE      (HRM_STATUS)2    /* License error             */
#define  HRM_OPEN_USB        (HRM_STATUS)3    /* Couldn't open USB module  */
#define  HRM_CLOSE_USB       (HRM_STATUS)4    /* Couldn't close USB module */
#define  HRM_INV_HANDLE      (HRM_STATUS)5    /* Invalid HANDLE            */
#define  HRM_RAW_FILE        (HRM_STATUS)6    /* Could not open RAW file   */
#define  HRM_OUTPUT_FILE     (HRM_STATUS)7    /* Could not open O/P file   */
#define  HRM_INV_PARAMETER   (HRM_STATUS)8    /* Invalid function param    */
#define  HRM_WRITE_COMMAND   (HRM_STATUS)9    /* Error writing command     */
#define  HRM_READ_COMMAND    (HRM_STATUS)10   /* Error reading command     */
#define  HRM_READ_DATA       (HRM_STATUS)11   /* Error reading data block  */
#define  HRM_FIFO_OVERFLOW   (HRM_STATUS)12   /* FIFO has overflowed       */
#define  HRM_BUFFER_FULL     (HRM_STATUS)13   /* Memory buffer full        */
#define  HRM_TIMEOUT         (HRM_STATUS)14   /* Timeout error             */
#define  HRM_NO_MODULE_FOUND (HRM_STATUS)15   /* Could not find module     */

#define  HRM_NO_CHANGE       (HRM_STATUS)9999 /* No change to error value  */
