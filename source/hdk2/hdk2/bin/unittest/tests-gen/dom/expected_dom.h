/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2015 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

/**********************************************************************
   Copyright [2014] [Cisco Systems, Inc.]
 
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
 
       http://www.apache.org/licenses/LICENSE-2.0
 
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
**********************************************************************/

/*
 * Copyright (c) 2008-2010 Cisco Systems, Inc. All rights reserved.
 *
 * Cisco Systems, Inc. retains all right, title and interest (including all
 * intellectual property rights) in and to this computer program, which is
 * protected by applicable intellectual property laws.  Unless you have obtained
 * a separate written license from Cisco Systems, Inc., you are not authorized
 * to utilize all or a part of this computer program for any purpose (including
 * reproduction, distribution, modification, and compilation into object code),
 * and you must immediately destroy or return to Cisco Systems, Inc. all copies
 * of this computer program.  If you are licensed by Cisco Systems, Inc., your
 * rights to utilize this computer program are limited by the terms of that
 * license.  To obtain a license, please contact Cisco Systems, Inc.
 *
 * This computer program contains trade secrets owned by Cisco Systems, Inc.
 * and, unless unauthorized by Cisco Systems, Inc. in writing, you agree to
 * maintain the confidentiality of this computer program and related information
 * and to not disclose this computer program and related information to any
 * other person or entity.
 *
 * THIS COMPUTER PROGRAM IS PROVIDED AS IS WITHOUT ANY WARRANTIES, AND CISCO
 * SYSTEMS, INC. EXPRESSLY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED,
 * INCLUDING THE WARRANTIES OF MERCHANTIBILITY, FITNESS FOR A PARTICULAR
 * PURPOSE, TITLE, AND NONINFRINGEMENT.
 */

#ifndef __ACTUAL_DOM_H__
#define __ACTUAL_DOM_H__

#include "hdk_mod.h"


/*
 * Macro to control public exports
 */

#ifdef __cplusplus
#  define ACTUAL_DOM_EXPORT_PREFIX extern "C"
#else
#  define ACTUAL_DOM_EXPORT_PREFIX extern
#endif
#ifdef HDK_MOD_STATIC
#  define ACTUAL_DOM_EXPORT ACTUAL_DOM_EXPORT_PREFIX
#else /* ndef HDK_MOD_STATIC */
#  ifdef _MSC_VER
#    ifdef ACTUAL_DOM_BUILD
#      define ACTUAL_DOM_EXPORT ACTUAL_DOM_EXPORT_PREFIX __declspec(dllexport)
#    else
#      define ACTUAL_DOM_EXPORT ACTUAL_DOM_EXPORT_PREFIX __declspec(dllimport)
#    endif
#  else /* ndef _MSC_VER */
#    ifdef ACTUAL_DOM_BUILD
#      define ACTUAL_DOM_EXPORT ACTUAL_DOM_EXPORT_PREFIX __attribute__ ((visibility("default")))
#    else
#      define ACTUAL_DOM_EXPORT ACTUAL_DOM_EXPORT_PREFIX
#    endif
#  endif /*def _MSC_VER */
#endif /* def HDK_MOD_STATIC */


/*
 * Elements
 */

typedef enum _ACTUAL_DOM_Element
{
    ACTUAL_DOM_Element_Cisco_CiscoStruct = 0,
    ACTUAL_DOM_Element_Cisco_CiscoStructToo = 1,
    ACTUAL_DOM_Element_Cisco_a = 2,
    ACTUAL_DOM_Element_Cisco_b = 3,
    ACTUAL_DOM_Element_Cisco_c = 4,
    ACTUAL_DOM_Element_Cisco_d = 5,
    ACTUAL_DOM_Element_Cisco_e = 6,
    ACTUAL_DOM_Element_Cisco_s = 7
} ACTUAL_DOM_Element;


/*
 * DOM Schemas
 */

ACTUAL_DOM_EXPORT const HDK_XML_Schema* ACTUAL_DOM_Schema_Cisco_CiscoStruct();
ACTUAL_DOM_EXPORT const HDK_XML_Schema* ACTUAL_DOM_Schema_Cisco_CiscoStructToo();

#endif /* __ACTUAL_DOM_H__ */
