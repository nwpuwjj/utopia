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

#pragma once

// actual_client_dom.h - [Generated by hdkcli_cpp]

// Non-generated client code.
#include "hdk_cli_cpp.h"

// Underlying schema module.
#include "actual_client_dom_mod.h"


namespace HDK
{
    ///
    /// \fn InitializeClient
    ///      Initialize the HDK client library.  This should be called once per application instance.
    ///      Each call to InitializeClient should be matched by a call to UninitializeClient.
    ///      \retval true if initialization was successful, false if not.
    ///
    bool InitializeClient() throw();

    ///
    /// \fn UninitializeClient
    ///      Cleanup the HDK client library.  This should be called if true was returned from InitializeClient
    ///      When the caller is done using the HDK client library.
    ///
    void UninitializeClient() throw();


    namespace Cisco_HNAP
    {
        ///
        /// \enum ActionResult
        ///      <a>http://cisco.com/HNAP/ActionResult</a>
        ///
        enum ActionResult
        {
            ActionResult_Unknown = ACTUAL_CLIENT_DOM_MOD_Enum_ActionResult__UNKNOWN__ /*<! Unknown value */,
            ActionResult_OK = ACTUAL_CLIENT_DOM_MOD_Enum_ActionResult_OK /*!< OK */,
            ActionResult_ERROR = ACTUAL_CLIENT_DOM_MOD_Enum_ActionResult_ERROR /*!< ERROR */
        }; // enum ActionResult

    } // namespace Cisco_HNAP

    namespace Cisco_HNAP_Sub
    {
        ///
        /// \enum ActionSubResult
        ///      <a>http://cisco.com/HNAP/Sub/ActionSubResult</a>
        ///
        enum ActionSubResult
        {
            ActionSubResult_Unknown = ACTUAL_CLIENT_DOM_MOD_Enum_Sub_ActionSubResult__UNKNOWN__ /*<! Unknown value */,
            ActionSubResult_OK = ACTUAL_CLIENT_DOM_MOD_Enum_Sub_ActionSubResult_OK /*!< OK */,
            ActionSubResult_ERROR = ACTUAL_CLIENT_DOM_MOD_Enum_Sub_ActionSubResult_ERROR /*!< ERROR */
        }; // enum ActionSubResult

    } // namespace Cisco_HNAP_Sub

    namespace Cisco
    {
        ///
        /// \enum ActionExtResult
        ///      <a>http://cisco.com/HNAPExt/ActionExtResult</a>
        ///
        enum ActionExtResult
        {
            ActionExtResult_Unknown = ACTUAL_CLIENT_DOM_MOD_Enum_Cisco_ActionExtResult__UNKNOWN__ /*<! Unknown value */,
            ActionExtResult_OK = ACTUAL_CLIENT_DOM_MOD_Enum_Cisco_ActionExtResult_OK /*!< OK */,
            ActionExtResult_ERROR = ACTUAL_CLIENT_DOM_MOD_Enum_Cisco_ActionExtResult_ERROR /*!< ERROR */
        }; // enum ActionExtResult

    } // namespace Cisco

    namespace Cisco_Sub
    {
        ///
        /// \enum ActionExtSubResult
        ///      <a>http://cisco.com/HNAPExt/Sub/ActionExtSubResult</a>
        ///
        enum ActionExtSubResult
        {
            ActionExtSubResult_Unknown = ACTUAL_CLIENT_DOM_MOD_Enum_Cisco_Sub_ActionExtSubResult__UNKNOWN__ /*<! Unknown value */,
            ActionExtSubResult_OK = ACTUAL_CLIENT_DOM_MOD_Enum_Cisco_Sub_ActionExtSubResult_OK /*!< OK */,
            ActionExtSubResult_ERROR = ACTUAL_CLIENT_DOM_MOD_Enum_Cisco_Sub_ActionExtSubResult_ERROR /*!< ERROR */
        }; // enum ActionExtSubResult

    } // namespace Cisco_Sub

    namespace Purenetworks_HNAP
    {
        ///
        /// \enum ActionLegacy2Result
        ///      <a>http://purenetworks.com/HNAP/ActionLegacy2Result</a>
        ///
        enum ActionLegacy2Result
        {
            ActionLegacy2Result_Unknown = ACTUAL_CLIENT_DOM_MOD_Enum_Purenetworks_HNAP_ActionLegacy2Result__UNKNOWN__ /*<! Unknown value */,
            ActionLegacy2Result_OK = ACTUAL_CLIENT_DOM_MOD_Enum_Purenetworks_HNAP_ActionLegacy2Result_OK /*!< OK */,
            ActionLegacy2Result_ERROR = ACTUAL_CLIENT_DOM_MOD_Enum_Purenetworks_HNAP_ActionLegacy2Result_ERROR /*!< ERROR */
        }; // enum ActionLegacy2Result

    } // namespace Purenetworks_HNAP

    namespace Purenetworks_HNAP_Sub
    {
        ///
        /// \enum ActionLegacy2SubResult
        ///      <a>http://purenetworks.com/HNAP/Sub/ActionLegacy2SubResult</a>
        ///
        enum ActionLegacy2SubResult
        {
            ActionLegacy2SubResult_Unknown = ACTUAL_CLIENT_DOM_MOD_Enum_PN_Sub_ActionLegacy2SubResult__UNKNOWN__ /*<! Unknown value */,
            ActionLegacy2SubResult_OK = ACTUAL_CLIENT_DOM_MOD_Enum_PN_Sub_ActionLegacy2SubResult_OK /*!< OK */,
            ActionLegacy2SubResult_ERROR = ACTUAL_CLIENT_DOM_MOD_Enum_PN_Sub_ActionLegacy2SubResult_ERROR /*!< ERROR */
        }; // enum ActionLegacy2SubResult

    } // namespace Purenetworks_HNAP_Sub

    namespace Purenetworks_HNAP1
    {
        ///
        /// \enum ActionLegacyResult
        ///      <a>http://purenetworks.com/HNAP1/ActionLegacyResult</a>
        ///
        enum ActionLegacyResult
        {
            ActionLegacyResult_Unknown = ACTUAL_CLIENT_DOM_MOD_Enum_PN_ActionLegacyResult__UNKNOWN__ /*<! Unknown value */,
            ActionLegacyResult_OK = ACTUAL_CLIENT_DOM_MOD_Enum_PN_ActionLegacyResult_OK /*!< OK */,
            ActionLegacyResult_ERROR = ACTUAL_CLIENT_DOM_MOD_Enum_PN_ActionLegacyResult_ERROR /*!< ERROR */
        }; // enum ActionLegacyResult

    } // namespace Purenetworks_HNAP1

    namespace Purenetworks_HNAP1_Sub
    {
        ///
        /// \enum ActionSubLegacyResult
        ///      <a>http://purenetworks.com/HNAP1/Sub/ActionSubLegacyResult</a>
        ///
        enum ActionSubLegacyResult
        {
            ActionSubLegacyResult_Unknown = ACTUAL_CLIENT_DOM_MOD_Enum_Purenetworks_HNAP1_Sub_ActionSubLegacyResult__UNKNOWN__ /*<! Unknown value */,
            ActionSubLegacyResult_OK = ACTUAL_CLIENT_DOM_MOD_Enum_Purenetworks_HNAP1_Sub_ActionSubLegacyResult_OK /*!< OK */,
            ActionSubLegacyResult_ERROR = ACTUAL_CLIENT_DOM_MOD_Enum_Purenetworks_HNAP1_Sub_ActionSubLegacyResult_ERROR /*!< ERROR */
        }; // enum ActionSubLegacyResult

    } // namespace Purenetworks_HNAP1_Sub

    namespace Purenetworks
    {
        ///
        /// \enum ActionLegacyExtResult
        ///      <a>http://purenetworks.com/HNAPExt/ActionLegacyExtResult</a>
        ///
        enum ActionLegacyExtResult
        {
            ActionLegacyExtResult_Unknown = ACTUAL_CLIENT_DOM_MOD_Enum_Purenetworks_ActionLegacyExtResult__UNKNOWN__ /*<! Unknown value */,
            ActionLegacyExtResult_OK = ACTUAL_CLIENT_DOM_MOD_Enum_Purenetworks_ActionLegacyExtResult_OK /*!< OK */,
            ActionLegacyExtResult_ERROR = ACTUAL_CLIENT_DOM_MOD_Enum_Purenetworks_ActionLegacyExtResult_ERROR /*!< ERROR */
        }; // enum ActionLegacyExtResult

    } // namespace Purenetworks

    namespace Purenetworks_Sub
    {
        ///
        /// \enum ActionLegacyExtSubResult
        ///      <a>http://purenetworks.com/HNAPExt/Sub/ActionLegacyExtSubResult</a>
        ///
        enum ActionLegacyExtSubResult
        {
            ActionLegacyExtSubResult_Unknown = ACTUAL_CLIENT_DOM_MOD_Enum_Purenetworks_Sub_ActionLegacyExtSubResult__UNKNOWN__ /*<! Unknown value */,
            ActionLegacyExtSubResult_OK = ACTUAL_CLIENT_DOM_MOD_Enum_Purenetworks_Sub_ActionLegacyExtSubResult_OK /*!< OK */,
            ActionLegacyExtSubResult_ERROR = ACTUAL_CLIENT_DOM_MOD_Enum_Purenetworks_Sub_ActionLegacyExtSubResult_ERROR /*!< ERROR */
        }; // enum ActionLegacyExtSubResult

    } // namespace Purenetworks_Sub

    namespace Cisco_HNAP
    {
        ///
        /// \brief Action
        ///      <a>http://cisco.com/HNAP/Action</a>
        ///
        class ActionStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            ActionStruct() throw();

            ///
            /// \brief Get the Member value.
            ///
            HDK_XML_Int get_Member() const throw();

            ///
            /// \brief Set the Member value.
            ///
            void set_Member(HDK_XML_Int value) throw();

        }; // class ActionStruct : public Struct

        ///
        /// \brief ActionResponse
        ///      <a>http://cisco.com/HNAP/ActionResponse</a>
        ///
        class ActionResponseStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            ActionResponseStruct() throw();

            ///
            /// \brief Get the ActionResult value.
            ///
            enum ActionResult get_ActionResult() const throw();

        }; // class ActionResponseStruct : public Struct

    } // namespace Cisco_HNAP

    namespace Cisco_HNAP_Sub
    {
        ///
        /// \brief ActionSub
        ///      <a>http://cisco.com/HNAP/Sub/ActionSub</a>
        ///
        class ActionSubStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            ActionSubStruct() throw();

            ///
            /// \brief Get the MemberSub value.
            ///
            HDK_XML_Int get_MemberSub() const throw();

            ///
            /// \brief Set the MemberSub value.
            ///
            void set_MemberSub(HDK_XML_Int value) throw();

        }; // class ActionSubStruct : public Struct

        ///
        /// \brief ActionSubResponse
        ///      <a>http://cisco.com/HNAP/Sub/ActionSubResponse</a>
        ///
        class ActionSubResponseStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            ActionSubResponseStruct() throw();

            ///
            /// \brief Get the ActionSubResult value.
            ///
            enum ActionSubResult get_ActionSubResult() const throw();

        }; // class ActionSubResponseStruct : public Struct

    } // namespace Cisco_HNAP_Sub

    namespace Cisco
    {
        ///
        /// \brief ActionExt
        ///      <a>http://cisco.com/HNAPExt/ActionExt</a>
        ///
        class ActionExtStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            ActionExtStruct() throw();

            ///
            /// \brief Get the MemberExt value.
            ///
            HDK_XML_Int get_MemberExt() const throw();

            ///
            /// \brief Set the MemberExt value.
            ///
            void set_MemberExt(HDK_XML_Int value) throw();

        }; // class ActionExtStruct : public Struct

        ///
        /// \brief ActionExtResponse
        ///      <a>http://cisco.com/HNAPExt/ActionExtResponse</a>
        ///
        class ActionExtResponseStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            ActionExtResponseStruct() throw();

            ///
            /// \brief Get the ActionExtResult value.
            ///
            enum ActionExtResult get_ActionExtResult() const throw();

        }; // class ActionExtResponseStruct : public Struct

    } // namespace Cisco

    namespace Cisco_Sub
    {
        ///
        /// \brief ActionExtSub
        ///      <a>http://cisco.com/HNAPExt/Sub/ActionExtSub</a>
        ///
        class ActionExtSubStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            ActionExtSubStruct() throw();

            ///
            /// \brief Get the MemberExtSub value.
            ///
            HDK_XML_Int get_MemberExtSub() const throw();

            ///
            /// \brief Set the MemberExtSub value.
            ///
            void set_MemberExtSub(HDK_XML_Int value) throw();

        }; // class ActionExtSubStruct : public Struct

        ///
        /// \brief ActionExtSubResponse
        ///      <a>http://cisco.com/HNAPExt/Sub/ActionExtSubResponse</a>
        ///
        class ActionExtSubResponseStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            ActionExtSubResponseStruct() throw();

            ///
            /// \brief Get the ActionExtSubResult value.
            ///
            enum ActionExtSubResult get_ActionExtSubResult() const throw();

        }; // class ActionExtSubResponseStruct : public Struct

    } // namespace Cisco_Sub

    namespace Purenetworks_HNAP
    {
        ///
        /// \brief ActionLegacy2
        ///      <a>http://purenetworks.com/HNAP/ActionLegacy2</a>
        ///
        class ActionLegacy2Struct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            ActionLegacy2Struct() throw();

            ///
            /// \brief Get the MemberLegacy2 value.
            ///
            HDK_XML_Int get_MemberLegacy2() const throw();

            ///
            /// \brief Set the MemberLegacy2 value.
            ///
            void set_MemberLegacy2(HDK_XML_Int value) throw();

        }; // class ActionLegacy2Struct : public Struct

        ///
        /// \brief ActionLegacy2Response
        ///      <a>http://purenetworks.com/HNAP/ActionLegacy2Response</a>
        ///
        class ActionLegacy2ResponseStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            ActionLegacy2ResponseStruct() throw();

            ///
            /// \brief Get the ActionLegacy2Result value.
            ///
            enum ActionLegacy2Result get_ActionLegacy2Result() const throw();

        }; // class ActionLegacy2ResponseStruct : public Struct

    } // namespace Purenetworks_HNAP

    namespace Purenetworks_HNAP_Sub
    {
        ///
        /// \brief ActionLegacy2Sub
        ///      <a>http://purenetworks.com/HNAP/Sub/ActionLegacy2Sub</a>
        ///
        class ActionLegacy2SubStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            ActionLegacy2SubStruct() throw();

            ///
            /// \brief Get the MemberLegacy2Sub value.
            ///
            HDK_XML_Int get_MemberLegacy2Sub() const throw();

            ///
            /// \brief Set the MemberLegacy2Sub value.
            ///
            void set_MemberLegacy2Sub(HDK_XML_Int value) throw();

        }; // class ActionLegacy2SubStruct : public Struct

        ///
        /// \brief ActionLegacy2SubResponse
        ///      <a>http://purenetworks.com/HNAP/Sub/ActionLegacy2SubResponse</a>
        ///
        class ActionLegacy2SubResponseStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            ActionLegacy2SubResponseStruct() throw();

            ///
            /// \brief Get the ActionLegacy2SubResult value.
            ///
            enum ActionLegacy2SubResult get_ActionLegacy2SubResult() const throw();

        }; // class ActionLegacy2SubResponseStruct : public Struct

    } // namespace Purenetworks_HNAP_Sub

    namespace Purenetworks_HNAP1
    {
        ///
        /// \brief ActionLegacy
        ///      <a>http://purenetworks.com/HNAP1/ActionLegacy</a>
        ///
        class ActionLegacyStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            ActionLegacyStruct() throw();

            ///
            /// \brief Get the MemberLegacy value.
            ///
            HDK_XML_Int get_MemberLegacy() const throw();

            ///
            /// \brief Set the MemberLegacy value.
            ///
            void set_MemberLegacy(HDK_XML_Int value) throw();

        }; // class ActionLegacyStruct : public Struct

        ///
        /// \brief ActionLegacyResponse
        ///      <a>http://purenetworks.com/HNAP1/ActionLegacyResponse</a>
        ///
        class ActionLegacyResponseStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            ActionLegacyResponseStruct() throw();

            ///
            /// \brief Get the ActionLegacyResult value.
            ///
            enum ActionLegacyResult get_ActionLegacyResult() const throw();

        }; // class ActionLegacyResponseStruct : public Struct

    } // namespace Purenetworks_HNAP1

    namespace Purenetworks_HNAP1_Sub
    {
        ///
        /// \brief ActionSubLegacy
        ///      <a>http://purenetworks.com/HNAP1/Sub/ActionSubLegacy</a>
        ///
        class ActionSubLegacyStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            ActionSubLegacyStruct() throw();

            ///
            /// \brief Get the MemberLegacySub value.
            ///
            HDK_XML_Int get_MemberLegacySub() const throw();

            ///
            /// \brief Set the MemberLegacySub value.
            ///
            void set_MemberLegacySub(HDK_XML_Int value) throw();

        }; // class ActionSubLegacyStruct : public Struct

        ///
        /// \brief ActionSubLegacyResponse
        ///      <a>http://purenetworks.com/HNAP1/Sub/ActionSubLegacyResponse</a>
        ///
        class ActionSubLegacyResponseStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            ActionSubLegacyResponseStruct() throw();

            ///
            /// \brief Get the ActionSubLegacyResult value.
            ///
            enum ActionSubLegacyResult get_ActionSubLegacyResult() const throw();

        }; // class ActionSubLegacyResponseStruct : public Struct

    } // namespace Purenetworks_HNAP1_Sub

    namespace Purenetworks
    {
        ///
        /// \brief ActionLegacyExt
        ///      <a>http://purenetworks.com/HNAPExt/ActionLegacyExt</a>
        ///
        class ActionLegacyExtStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            ActionLegacyExtStruct() throw();

            ///
            /// \brief Get the MemberLegacyExt value.
            ///
            HDK_XML_Int get_MemberLegacyExt() const throw();

            ///
            /// \brief Set the MemberLegacyExt value.
            ///
            void set_MemberLegacyExt(HDK_XML_Int value) throw();

        }; // class ActionLegacyExtStruct : public Struct

        ///
        /// \brief ActionLegacyExtResponse
        ///      <a>http://purenetworks.com/HNAPExt/ActionLegacyExtResponse</a>
        ///
        class ActionLegacyExtResponseStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            ActionLegacyExtResponseStruct() throw();

            ///
            /// \brief Get the ActionLegacyExtResult value.
            ///
            enum ActionLegacyExtResult get_ActionLegacyExtResult() const throw();

        }; // class ActionLegacyExtResponseStruct : public Struct

    } // namespace Purenetworks

    namespace Purenetworks_Sub
    {
        ///
        /// \brief ActionLegacyExtSub
        ///      <a>http://purenetworks.com/HNAPExt/Sub/ActionLegacyExtSub</a>
        ///
        class ActionLegacyExtSubStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            ActionLegacyExtSubStruct() throw();

            ///
            /// \brief Get the MemberLegacyExtSub value.
            ///
            HDK_XML_Int get_MemberLegacyExtSub() const throw();

            ///
            /// \brief Set the MemberLegacyExtSub value.
            ///
            void set_MemberLegacyExtSub(HDK_XML_Int value) throw();

        }; // class ActionLegacyExtSubStruct : public Struct

        ///
        /// \brief ActionLegacyExtSubResponse
        ///      <a>http://purenetworks.com/HNAPExt/Sub/ActionLegacyExtSubResponse</a>
        ///
        class ActionLegacyExtSubResponseStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            ActionLegacyExtSubResponseStruct() throw();

            ///
            /// \brief Get the ActionLegacyExtSubResult value.
            ///
            enum ActionLegacyExtSubResult get_ActionLegacyExtSubResult() const throw();

        }; // class ActionLegacyExtSubResponseStruct : public Struct

    } // namespace Purenetworks_Sub

    namespace Cisco_HNAP
    {
        ///
        /// \brief SOAP method URI for action Action
        ///
#define Action_URI (HDK_MOD_GetMethod(ACTUAL_CLIENT_DOM_MOD_Module(), ACTUAL_CLIENT_DOM_MOD_MethodEnum_Action)->pszSOAPAction)

        ///
        /// \brief Call the Action method on a given device.
        ///     <a>http://cisco.com/HNAP/Action</a>
        ///     This method uses HTTP method POST and location '/HNAP1'
        ///
        ///     Possible result values:
        ///          - #ActionResult_OK
        ///          - #ActionResult_ERROR
        ///     \arg pTarget The target on which to call this method.
        ///     \arg input The input argument data to the Action HNAP method.
        ///     \arg[optional] result The HNAP result of the Action HNAP method.
        ///     \arg timeoutSecs An optional timeout, in seconds, to use for the HNAP call.
        ///     \retval The result of the HNAP method call.
        ///
        HDK::ClientError Action
        (
            HDK::ITarget* pTarget,
            const ActionStruct & input,
            enum ActionResult* presult = NULL,
            unsigned int timeoutSecs = 0
        ) throw();

    } // namespace Cisco_HNAP

    namespace Cisco_HNAP_Sub
    {
        ///
        /// \brief SOAP method URI for action ActionSub
        ///
#define Sub_ActionSub_URI (HDK_MOD_GetMethod(ACTUAL_CLIENT_DOM_MOD_Module(), ACTUAL_CLIENT_DOM_MOD_MethodEnum_Sub_ActionSub)->pszSOAPAction)

        ///
        /// \brief Call the ActionSub method on a given device.
        ///     <a>http://cisco.com/HNAP/Sub/ActionSub</a>
        ///     This method uses HTTP method POST and location '/HNAP1'
        ///
        ///     Possible result values:
        ///          - #ActionSubResult_OK
        ///          - #ActionSubResult_ERROR
        ///     \arg pTarget The target on which to call this method.
        ///     \arg input The input argument data to the ActionSub HNAP method.
        ///     \arg[optional] result The HNAP result of the ActionSub HNAP method.
        ///     \arg timeoutSecs An optional timeout, in seconds, to use for the HNAP call.
        ///     \retval The result of the HNAP method call.
        ///
        HDK::ClientError ActionSub
        (
            HDK::ITarget* pTarget,
            const ActionSubStruct & input,
            enum ActionSubResult* presult = NULL,
            unsigned int timeoutSecs = 0
        ) throw();

    } // namespace Cisco_HNAP_Sub

    namespace Cisco
    {
        ///
        /// \brief SOAP method URI for action ActionExt
        ///
#define Cisco_ActionExt_URI (HDK_MOD_GetMethod(ACTUAL_CLIENT_DOM_MOD_Module(), ACTUAL_CLIENT_DOM_MOD_MethodEnum_Cisco_ActionExt)->pszSOAPAction)

        ///
        /// \brief Call the ActionExt method on a given device.
        ///     <a>http://cisco.com/HNAPExt/ActionExt</a>
        ///     This method uses HTTP method POST and location '/HNAP1'
        ///
        ///     Possible result values:
        ///          - #ActionExtResult_OK
        ///          - #ActionExtResult_ERROR
        ///     \arg pTarget The target on which to call this method.
        ///     \arg input The input argument data to the ActionExt HNAP method.
        ///     \arg[optional] result The HNAP result of the ActionExt HNAP method.
        ///     \arg timeoutSecs An optional timeout, in seconds, to use for the HNAP call.
        ///     \retval The result of the HNAP method call.
        ///
        HDK::ClientError ActionExt
        (
            HDK::ITarget* pTarget,
            const ActionExtStruct & input,
            enum ActionExtResult* presult = NULL,
            unsigned int timeoutSecs = 0
        ) throw();

    } // namespace Cisco

    namespace Cisco_Sub
    {
        ///
        /// \brief SOAP method URI for action ActionExtSub
        ///
#define Cisco_Sub_ActionExtSub_URI (HDK_MOD_GetMethod(ACTUAL_CLIENT_DOM_MOD_Module(), ACTUAL_CLIENT_DOM_MOD_MethodEnum_Cisco_Sub_ActionExtSub)->pszSOAPAction)

        ///
        /// \brief Call the ActionExtSub method on a given device.
        ///     <a>http://cisco.com/HNAPExt/Sub/ActionExtSub</a>
        ///     This method uses HTTP method POST and location '/HNAP1'
        ///
        ///     Possible result values:
        ///          - #ActionExtSubResult_OK
        ///          - #ActionExtSubResult_ERROR
        ///     \arg pTarget The target on which to call this method.
        ///     \arg input The input argument data to the ActionExtSub HNAP method.
        ///     \arg[optional] result The HNAP result of the ActionExtSub HNAP method.
        ///     \arg timeoutSecs An optional timeout, in seconds, to use for the HNAP call.
        ///     \retval The result of the HNAP method call.
        ///
        HDK::ClientError ActionExtSub
        (
            HDK::ITarget* pTarget,
            const ActionExtSubStruct & input,
            enum ActionExtSubResult* presult = NULL,
            unsigned int timeoutSecs = 0
        ) throw();

    } // namespace Cisco_Sub

    namespace Purenetworks_HNAP
    {
        ///
        /// \brief SOAP method URI for action ActionLegacy2
        ///
#define Purenetworks_HNAP_ActionLegacy2_URI (HDK_MOD_GetMethod(ACTUAL_CLIENT_DOM_MOD_Module(), ACTUAL_CLIENT_DOM_MOD_MethodEnum_Purenetworks_HNAP_ActionLegacy2)->pszSOAPAction)

        ///
        /// \brief Call the ActionLegacy2 method on a given device.
        ///     <a>http://purenetworks.com/HNAP/ActionLegacy2</a>
        ///     This method uses HTTP method POST and location '/HNAP1'
        ///
        ///     Possible result values:
        ///          - #ActionLegacy2Result_OK
        ///          - #ActionLegacy2Result_ERROR
        ///     \arg pTarget The target on which to call this method.
        ///     \arg input The input argument data to the ActionLegacy2 HNAP method.
        ///     \arg[optional] result The HNAP result of the ActionLegacy2 HNAP method.
        ///     \arg timeoutSecs An optional timeout, in seconds, to use for the HNAP call.
        ///     \retval The result of the HNAP method call.
        ///
        HDK::ClientError ActionLegacy2
        (
            HDK::ITarget* pTarget,
            const ActionLegacy2Struct & input,
            enum ActionLegacy2Result* presult = NULL,
            unsigned int timeoutSecs = 0
        ) throw();

    } // namespace Purenetworks_HNAP

    namespace Purenetworks_HNAP_Sub
    {
        ///
        /// \brief SOAP method URI for action ActionLegacy2Sub
        ///
#define PN_Sub_ActionLegacy2Sub_URI (HDK_MOD_GetMethod(ACTUAL_CLIENT_DOM_MOD_Module(), ACTUAL_CLIENT_DOM_MOD_MethodEnum_PN_Sub_ActionLegacy2Sub)->pszSOAPAction)

        ///
        /// \brief Call the ActionLegacy2Sub method on a given device.
        ///     <a>http://purenetworks.com/HNAP/Sub/ActionLegacy2Sub</a>
        ///     This method uses HTTP method POST and location '/HNAP1'
        ///
        ///     Possible result values:
        ///          - #ActionLegacy2SubResult_OK
        ///          - #ActionLegacy2SubResult_ERROR
        ///     \arg pTarget The target on which to call this method.
        ///     \arg input The input argument data to the ActionLegacy2Sub HNAP method.
        ///     \arg[optional] result The HNAP result of the ActionLegacy2Sub HNAP method.
        ///     \arg timeoutSecs An optional timeout, in seconds, to use for the HNAP call.
        ///     \retval The result of the HNAP method call.
        ///
        HDK::ClientError ActionLegacy2Sub
        (
            HDK::ITarget* pTarget,
            const ActionLegacy2SubStruct & input,
            enum ActionLegacy2SubResult* presult = NULL,
            unsigned int timeoutSecs = 0
        ) throw();

    } // namespace Purenetworks_HNAP_Sub

    namespace Purenetworks_HNAP1
    {
        ///
        /// \brief SOAP method URI for action ActionLegacy
        ///
#define PN_ActionLegacy_URI (HDK_MOD_GetMethod(ACTUAL_CLIENT_DOM_MOD_Module(), ACTUAL_CLIENT_DOM_MOD_MethodEnum_PN_ActionLegacy)->pszSOAPAction)

        ///
        /// \brief Call the ActionLegacy method on a given device.
        ///     <a>http://purenetworks.com/HNAP1/ActionLegacy</a>
        ///     This method uses HTTP method POST and location '/HNAP1'
        ///
        ///     Possible result values:
        ///          - #ActionLegacyResult_OK
        ///          - #ActionLegacyResult_ERROR
        ///     \arg pTarget The target on which to call this method.
        ///     \arg input The input argument data to the ActionLegacy HNAP method.
        ///     \arg[optional] result The HNAP result of the ActionLegacy HNAP method.
        ///     \arg timeoutSecs An optional timeout, in seconds, to use for the HNAP call.
        ///     \retval The result of the HNAP method call.
        ///
        HDK::ClientError ActionLegacy
        (
            HDK::ITarget* pTarget,
            const ActionLegacyStruct & input,
            enum ActionLegacyResult* presult = NULL,
            unsigned int timeoutSecs = 0
        ) throw();

    } // namespace Purenetworks_HNAP1

    namespace Purenetworks_HNAP1_Sub
    {
        ///
        /// \brief SOAP method URI for action ActionSubLegacy
        ///
#define Purenetworks_HNAP1_Sub_ActionSubLegacy_URI (HDK_MOD_GetMethod(ACTUAL_CLIENT_DOM_MOD_Module(), ACTUAL_CLIENT_DOM_MOD_MethodEnum_Purenetworks_HNAP1_Sub_ActionSubLegacy)->pszSOAPAction)

        ///
        /// \brief Call the ActionSubLegacy method on a given device.
        ///     <a>http://purenetworks.com/HNAP1/Sub/ActionSubLegacy</a>
        ///     This method uses HTTP method POST and location '/HNAP1'
        ///
        ///     Possible result values:
        ///          - #ActionSubLegacyResult_OK
        ///          - #ActionSubLegacyResult_ERROR
        ///     \arg pTarget The target on which to call this method.
        ///     \arg input The input argument data to the ActionSubLegacy HNAP method.
        ///     \arg[optional] result The HNAP result of the ActionSubLegacy HNAP method.
        ///     \arg timeoutSecs An optional timeout, in seconds, to use for the HNAP call.
        ///     \retval The result of the HNAP method call.
        ///
        HDK::ClientError ActionSubLegacy
        (
            HDK::ITarget* pTarget,
            const ActionSubLegacyStruct & input,
            enum ActionSubLegacyResult* presult = NULL,
            unsigned int timeoutSecs = 0
        ) throw();

    } // namespace Purenetworks_HNAP1_Sub

    namespace Purenetworks
    {
        ///
        /// \brief SOAP method URI for action ActionLegacyExt
        ///
#define Purenetworks_ActionLegacyExt_URI (HDK_MOD_GetMethod(ACTUAL_CLIENT_DOM_MOD_Module(), ACTUAL_CLIENT_DOM_MOD_MethodEnum_Purenetworks_ActionLegacyExt)->pszSOAPAction)

        ///
        /// \brief Call the ActionLegacyExt method on a given device.
        ///     <a>http://purenetworks.com/HNAPExt/ActionLegacyExt</a>
        ///     This method uses HTTP method POST and location '/HNAP1'
        ///
        ///     Possible result values:
        ///          - #ActionLegacyExtResult_OK
        ///          - #ActionLegacyExtResult_ERROR
        ///     \arg pTarget The target on which to call this method.
        ///     \arg input The input argument data to the ActionLegacyExt HNAP method.
        ///     \arg[optional] result The HNAP result of the ActionLegacyExt HNAP method.
        ///     \arg timeoutSecs An optional timeout, in seconds, to use for the HNAP call.
        ///     \retval The result of the HNAP method call.
        ///
        HDK::ClientError ActionLegacyExt
        (
            HDK::ITarget* pTarget,
            const ActionLegacyExtStruct & input,
            enum ActionLegacyExtResult* presult = NULL,
            unsigned int timeoutSecs = 0
        ) throw();

    } // namespace Purenetworks

    namespace Purenetworks_Sub
    {
        ///
        /// \brief SOAP method URI for action ActionLegacyExtSub
        ///
#define Purenetworks_Sub_ActionLegacyExtSub_URI (HDK_MOD_GetMethod(ACTUAL_CLIENT_DOM_MOD_Module(), ACTUAL_CLIENT_DOM_MOD_MethodEnum_Purenetworks_Sub_ActionLegacyExtSub)->pszSOAPAction)

        ///
        /// \brief Call the ActionLegacyExtSub method on a given device.
        ///     <a>http://purenetworks.com/HNAPExt/Sub/ActionLegacyExtSub</a>
        ///     This method uses HTTP method POST and location '/HNAP1'
        ///
        ///     Possible result values:
        ///          - #ActionLegacyExtSubResult_OK
        ///          - #ActionLegacyExtSubResult_ERROR
        ///     \arg pTarget The target on which to call this method.
        ///     \arg input The input argument data to the ActionLegacyExtSub HNAP method.
        ///     \arg[optional] result The HNAP result of the ActionLegacyExtSub HNAP method.
        ///     \arg timeoutSecs An optional timeout, in seconds, to use for the HNAP call.
        ///     \retval The result of the HNAP method call.
        ///
        HDK::ClientError ActionLegacyExtSub
        (
            HDK::ITarget* pTarget,
            const ActionLegacyExtSubStruct & input,
            enum ActionLegacyExtSubResult* presult = NULL,
            unsigned int timeoutSecs = 0
        ) throw();

    } // namespace Purenetworks_Sub
} // namespace HDK
