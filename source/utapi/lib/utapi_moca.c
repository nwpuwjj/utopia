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
 * Copyright (c) 2008-2009 Cisco Systems, Inc. All rights reserved.
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utctx/utctx.h>
#include <utctx/utctx_api.h>
#include "utapi.h"
#include "utapi_util.h"
#include "utapi_wlan.h"
#include "DM_TR181.h"


int Utopia_GetMocaIntf_Static(void *str_handle)
{
    Obj_Device_MoCA_Interface_i_static *deviceMocaIntfStatic = NULL;
    char buf[BUF_SZ] = {'\0'};

    if (str_handle == NULL) {
	sprintf(ulog_msg, "%s: Invalid Input Parameter", __FUNCTION__);
	ulog_error(ULOG_CONFIG, UL_UTAPI, ulog_msg);
        return ERR_INVALID_ARGS;
    }
    deviceMocaIntfStatic = (Obj_Device_MoCA_Interface_i_static *)str_handle;

    sprintf(buf, "mocacfg %s > %s", "moca0", MOCACFG_FILE_NAME);
    system(buf);
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "mocacfg %s >> %s", "-g moca0 moca", MOCACFG_FILE_NAME);
    system(buf);
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "mocacfg %s >> %s", "-g moca0 mac", MOCACFG_FILE_NAME);
    system(buf);
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "mocacfg %s >> %s", "-g moca0 phy", MOCACFG_FILE_NAME);
    system(buf);

    if(Utopia_Get_TR181_Device_MoCA_Interface_i_Static(deviceMocaIntfStatic) != SUCCESS){
	sprintf(ulog_msg, "%s: Error in MoCA_Intf_GET !!!", __FUNCTION__);
	ulog_error(ULOG_CONFIG, UL_UTAPI, ulog_msg);
        return ERR_ITEM_NOT_FOUND;
    }
        
    return UT_SUCCESS;
}

int Utopia_GetMocaIntf_Dyn(void *str_handle)
{
    Obj_Device_MoCA_Interface_i_dyn *deviceMocaIntfDyn = NULL;
    char buf[BUF_SZ];
    
    if (str_handle == NULL) {
	sprintf(ulog_msg, "%s: Invalid Input Parameter", __FUNCTION__);
	ulog_error(ULOG_CONFIG, UL_UTAPI, ulog_msg);
        return ERR_INVALID_ARGS;
    }
    deviceMocaIntfDyn = (Obj_Device_MoCA_Interface_i_dyn*)str_handle;

    sprintf(buf, "mocacfg %s > %s", "moca0", MOCACFG_FILE_NAME);
    system(buf);
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "mocacfg %s >> %s", "-g moca0 moca", MOCACFG_FILE_NAME);
    system(buf);
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "mocacfg %s >> %s", "-g moca0 mac", MOCACFG_FILE_NAME);
    system(buf);
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "mocacfg %s >> %s", "-g moca0 phy", MOCACFG_FILE_NAME);
    system(buf);

    if(Utopia_Get_TR181_Device_MoCA_Interface_i_Dyn(deviceMocaIntfDyn) != SUCCESS){
	sprintf(ulog_msg, "%s: Error in MoCA_Intf_GET !!!", __FUNCTION__);
	ulog_error(ULOG_CONFIG, UL_UTAPI, ulog_msg);
        return ERR_ITEM_NOT_FOUND;
    }
        
    return UT_SUCCESS;
}

int Utopia_GetMocaIntf_Cfg(UtopiaContext *pCtx, void *str_handle)
{
    Obj_Device_MoCA_Interface_i_cfg *deviceMocaIntfCfg = NULL;
    int iVal = -1;
    char buf[64] = {'\0'};
    
    if (!pCtx || !str_handle) {
	sprintf(ulog_msg, "%s: Invalid Input Parameter", __FUNCTION__);
	ulog_error(ULOG_CONFIG, UL_UTAPI, ulog_msg);
        return ERR_INVALID_ARGS;
    }
    deviceMocaIntfCfg = (Obj_Device_MoCA_Interface_i_cfg*)str_handle;

    Utopia_GetInt(pCtx, UtopiaValue_Moca_Enable, &iVal);
    deviceMocaIntfCfg->Enable = (iVal == 0)? FALSE : TRUE ;

    Utopia_GetInt(pCtx, UtopiaValue_Moca_PreferredNC, &iVal);
    deviceMocaIntfCfg->PreferredNC = (iVal == 0)? FALSE : TRUE ;

    if(Utopia_GetInt(pCtx, UtopiaValue_Moca_PrivEnabledSet, &iVal) != 0)
        deviceMocaIntfCfg->PrivacyEnabledSetting = FALSE;   /*default value */
    else
        deviceMocaIntfCfg->PrivacyEnabledSetting = (iVal == 0)? FALSE : TRUE ;

    Utopia_Get(pCtx, UtopiaValue_Moca_Alias, &deviceMocaIntfCfg->Alias, UTOPIA_TR181_PARAM_SIZE);
    
    Utopia_Get(pCtx, UtopiaValue_Moca_FreqCurMaskSet, buf, sizeof(buf));
    buf[strlen(buf)] = '\0';
    getHex(buf, deviceMocaIntfCfg->FreqCurrentMaskSetting, HEX_SZ);

    if(Utopia_Get(pCtx, UtopiaValue_Moca_KeyPassPhrase, &deviceMocaIntfCfg->KeyPassphrase, KEYPASS_SZ) == 0)
        memset(deviceMocaIntfCfg->KeyPassphrase, 0, KEYPASS_SZ);    /*default value */
    if(Utopia_GetInt(pCtx, UtopiaValue_Moca_TxPowerLimit, (int*)&deviceMocaIntfCfg->TxPowerLimit) != 0)
        deviceMocaIntfCfg->TxPowerLimit = 36;       /*default value */
    if(Utopia_GetInt(pCtx, UtopiaValue_Moca_PwrCntlPhyTarget, (int*)&deviceMocaIntfCfg->PowerCntlPhyTarget) != 0)
        deviceMocaIntfCfg->PowerCntlPhyTarget = 236; /*default value */
    if(Utopia_GetInt(pCtx, UtopiaValue_Moca_BeaconPwrLimit, (int*)&deviceMocaIntfCfg->BeaconPowerLimit) != 0)
        deviceMocaIntfCfg->BeaconPowerLimit = 0;  /*default value */

    return UT_SUCCESS;
}

int Utopia_SetMocaIntf_Cfg(UtopiaContext *pCtx, void *str_handle)
{
    Obj_Device_MoCA_Interface_i_cfg *deviceMocaIntfCfg = NULL;
    int iVal = -1;
    char buf[64] = {'\0'};
    char cmd[64] = {'\0'};
    char key_val[64] = {'\0'};
    
    if (!pCtx || !str_handle) {
	sprintf(ulog_msg, "%s: Invalid Input Parameter", __FUNCTION__);
	ulog_error(ULOG_CONFIG, UL_UTAPI, ulog_msg);
        return ERR_INVALID_ARGS;
    }
    deviceMocaIntfCfg = (Obj_Device_MoCA_Interface_i_cfg*)str_handle;

    iVal = (deviceMocaIntfCfg->Enable == FALSE)? 0:1;
    if(iVal == 1){
        system("mocacfg moca up");
	Utopia_Set(pCtx, UtopiaValue_Moca_Enable, "up");
    }else{
	system("mocacfg moca down");
	Utopia_Set(pCtx, UtopiaValue_Moca_Enable, "down");
    }

    memset(cmd, 0, sizeof(cmd));
    memset(buf, 0, sizeof(buf));
    if(deviceMocaIntfCfg->PreferredNC == FALSE)
        strcpy(buf, "slave");
    else
        strcpy(buf, "master");
    Utopia_Set(pCtx, UtopiaValue_Moca_PreferredNC, buf);
    sprintf(cmd, "mocacfg -s moca nc %s", buf);
    system(cmd);

    memset(cmd, 0, sizeof(cmd));
    memset(buf, 0, sizeof(buf));
    if(deviceMocaIntfCfg->PrivacyEnabledSetting == FALSE)
        strcpy(buf, "disable");
    else
        strcpy(buf, "enable");
    Utopia_Set(pCtx, UtopiaValue_Moca_PrivEnabledSet, buf);
    sprintf(cmd, "mocacfg -s moca privacy %s", buf);
    system(cmd);

    Utopia_Set(pCtx, UtopiaValue_Moca_Alias, deviceMocaIntfCfg->Alias);

    memset(cmd, 0, sizeof(cmd));
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%02X%02X%02X%02X%02X%02X%02X%02X", 
                 deviceMocaIntfCfg->FreqCurrentMaskSetting[0],
		 deviceMocaIntfCfg->FreqCurrentMaskSetting[1],
		 deviceMocaIntfCfg->FreqCurrentMaskSetting[2],
		 deviceMocaIntfCfg->FreqCurrentMaskSetting[3],
		 deviceMocaIntfCfg->FreqCurrentMaskSetting[4],
		 deviceMocaIntfCfg->FreqCurrentMaskSetting[5],
		 deviceMocaIntfCfg->FreqCurrentMaskSetting[6],
		 deviceMocaIntfCfg->FreqCurrentMaskSetting[7]
	   );
    buf[16] = '\0';
    Utopia_Set(pCtx, UtopiaValue_Moca_FreqCurMaskSet, buf);
    Utopia_RawSet(pCtx, NULL, "FreqMode", "manual");
    system("mocacfg -s moca fmode manual");
    sprintf(cmd, "mocacfg -s moca fplan 0x%s", buf);
    system(cmd);

    memset(cmd, 0, sizeof(cmd));
    Utopia_Set(pCtx, UtopiaValue_Moca_KeyPassPhrase, deviceMocaIntfCfg->KeyPassphrase);
    sprintf(cmd, "mocacfg -s moca ppassword %s", deviceMocaIntfCfg->KeyPassphrase);
    system(cmd);
 
    memset(cmd, 0, sizeof(cmd));
    Utopia_SetInt(pCtx, UtopiaValue_Moca_TxPowerLimit, deviceMocaIntfCfg->TxPowerLimit); 
    sprintf(key_val, "%d", deviceMocaIntfCfg->TxPowerLimit);
    sprintf(cmd, "mocacfg -s moca maxtxpower %s", key_val);
    system(cmd);

    memset(cmd, 0, sizeof(cmd));
    memset(key_val, 0, sizeof(key_val));
    Utopia_SetInt(pCtx, UtopiaValue_Moca_PwrCntlPhyTarget, deviceMocaIntfCfg->PowerCntlPhyTarget);
    sprintf(key_val, "%d", deviceMocaIntfCfg->PowerCntlPhyTarget);
    sprintf(cmd, "mocacfg -s moca phyrate %s", key_val);
    system(cmd);

    memset(cmd, 0, sizeof(cmd));
    memset(key_val, 0, sizeof(key_val));
    Utopia_SetInt(pCtx, UtopiaValue_Moca_BeaconPwrLimit, deviceMocaIntfCfg->BeaconPowerLimit);
    sprintf(key_val, "%d", deviceMocaIntfCfg->BeaconPowerLimit);
    sprintf(cmd, "mocacfg -s moca bbackoff %s", key_val);
    system(cmd);

    return UT_SUCCESS;
}

int Utopia_GetMocaIntf_AssociateDevice(void *str_handle, int count)
{
    Obj_Device_MoCA_Interface_i_AssociatedDevice_i *mocaIntfAssociatedevice = NULL;
    char buf[BUF_SZ] = {'\0'};

    if (str_handle == NULL) {
        sprintf(ulog_msg, "%s: Invalid Input Parameter", __FUNCTION__);
        ulog_error(ULOG_CONFIG, UL_UTAPI, ulog_msg);
        return ERR_INVALID_ARGS;
    }
    mocaIntfAssociatedevice = (Obj_Device_MoCA_Interface_i_AssociatedDevice_i *)str_handle;

    sprintf(buf, "mocacfg %s > %s", " moca0", MOCACFG_FILE_NAME);
    system(buf);
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "mocacfg %s >> %s", "-g moca0 moca", MOCACFG_FILE_NAME);
    system(buf);
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "mocacfg %s >> %s", "-g moca0 mac", MOCACFG_FILE_NAME);
    system(buf);
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "mocacfg %s >> %s", "-g moca0 phy", MOCACFG_FILE_NAME);
    system(buf);

    if(Utopia_Get_TR181_Device_MoCA_Interface_i_AssociateDevice(mocaIntfAssociatedevice, count) != SUCCESS){
        sprintf(ulog_msg, "%s: Error in MoCA_Intf_AssociateDevice_GET !!!", __FUNCTION__);
        ulog_error(ULOG_CONFIG, UL_UTAPI, ulog_msg);
        return ERR_ITEM_NOT_FOUND;
    }

    return UT_SUCCESS;
}



