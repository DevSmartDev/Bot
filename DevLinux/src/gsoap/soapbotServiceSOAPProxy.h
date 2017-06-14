/* soapbotServiceSOAPProxy.h
   Generated by gSOAP 2.8.7 from ../../../src/gsoap/botService.h

Copyright(C) 2000-2011, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
1) GPL or 2) Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#ifndef soapbotServiceSOAPProxy_H
#define soapbotServiceSOAPProxy_H
#include "soapH.h"
class botServiceSOAP
{   public:
	/// Runtime engine context allocated in constructor
	struct soap *soap;
	/// Endpoint URL of service 'botServiceSOAP' (change as needed)
	const char *endpoint;
	/// Constructor allocates soap engine context, sets default endpoint URL, and sets namespace mapping table
	botServiceSOAP()
	{ soap = soap_new(); endpoint = "http://localhost:8080/axis2/services/botServices"; if (soap && !soap->namespaces) { static const struct Namespace namespaces[] = 
{
	{"SOAP-ENV", "http://www.w3.org/2003/05/soap-envelope", "http://schemas.xmlsoap.org/soap/envelope/", NULL},
	{"SOAP-ENC", "http://www.w3.org/2003/05/soap-encoding", "http://schemas.xmlsoap.org/soap/encoding/", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns1", "urn:wsdl.icdrec.edu.vn", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
	soap->namespaces = namespaces; } };
	/// Destructor frees deserialized data and soap engine context
	virtual ~botServiceSOAP() { if (soap) { soap_destroy(soap); soap_end(soap); soap_free(soap); } };
	/// Invoke 'LoginOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__LoginOperation(_ns1__LoginOperation *ns1__LoginOperation, _ns1__LoginOperationResponse *ns1__LoginOperationResponse) { return soap ? soap_call___ns1__LoginOperation(soap, endpoint, NULL, ns1__LoginOperation, ns1__LoginOperationResponse) : SOAP_EOM; };
	/// Invoke 'LoginPcOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__LoginPcOperation(_ns1__LoginPcOperation *ns1__LoginPcOperation, _ns1__LoginPcOperationResponse *ns1__LoginPcOperationResponse) { return soap ? soap_call___ns1__LoginPcOperation(soap, endpoint, NULL, ns1__LoginPcOperation, ns1__LoginPcOperationResponse) : SOAP_EOM; };
	/// Invoke 'LogoutOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__LogoutOperation(_ns1__LogoutOperation *ns1__LogoutOperation, _ns1__LogoutOperationResponse *ns1__LogoutOperationResponse) { return soap ? soap_call___ns1__LogoutOperation(soap, endpoint, NULL, ns1__LogoutOperation, ns1__LogoutOperationResponse) : SOAP_EOM; };
	/// Invoke 'getDcuListOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__getDcuListOperation(_ns1__getDcuListOperation *ns1__getDcuListOperation, _ns1__getDcuListOperationResponse *ns1__getDcuListOperationResponse) { return soap ? soap_call___ns1__getDcuListOperation(soap, endpoint, NULL, ns1__getDcuListOperation, ns1__getDcuListOperationResponse) : SOAP_EOM; };
	/// Invoke 'getLcuListOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__getLcuListOperation(_ns1__getLcuListOperation *ns1__getLcuListOperation, _ns1__getLcuListOperationResponse *ns1__getLcuListOperationResponse) { return soap ? soap_call___ns1__getLcuListOperation(soap, endpoint, NULL, ns1__getLcuListOperation, ns1__getLcuListOperationResponse) : SOAP_EOM; };
	/// Invoke 'updateRuntimeForUserOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__updateRuntimeForUserOperation(_ns1__updateRuntimeForUserOperation *ns1__updateRuntimeForUserOperation, _ns1__updateRuntimeForUserOperationResponse *ns1__updateRuntimeForUserOperationResponse) { return soap ? soap_call___ns1__updateRuntimeForUserOperation(soap, endpoint, NULL, ns1__updateRuntimeForUserOperation, ns1__updateRuntimeForUserOperationResponse) : SOAP_EOM; };
	/// Invoke 'getLineListOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__getLineListOperation(_ns1__getLineListOperation *ns1__getLineListOperation, _ns1__getLineListOperationResponse *ns1__getLineListOperationResponse) { return soap ? soap_call___ns1__getLineListOperation(soap, endpoint, NULL, ns1__getLineListOperation, ns1__getLineListOperationResponse) : SOAP_EOM; };
	/// Invoke 'addDcuOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__addDcuOperation(_ns1__addDcuOperation *ns1__addDcuOperation, _ns1__addDcuOperationResponse *ns1__addDcuOperationResponse) { return soap ? soap_call___ns1__addDcuOperation(soap, endpoint, NULL, ns1__addDcuOperation, ns1__addDcuOperationResponse) : SOAP_EOM; };
	/// Invoke 'removeDcuOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__removeDcuOperation(_ns1__removeDcuOperation *ns1__removeDcuOperation, _ns1__removeDcuOperationResponse *ns1__removeDcuOperationResponse) { return soap ? soap_call___ns1__removeDcuOperation(soap, endpoint, NULL, ns1__removeDcuOperation, ns1__removeDcuOperationResponse) : SOAP_EOM; };
	/// Invoke 'editDcuOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__editDcuOperation(_ns1__editDcuOperation *ns1__editDcuOperation, _ns1__editDcuOperationResponse *ns1__editDcuOperationResponse) { return soap ? soap_call___ns1__editDcuOperation(soap, endpoint, NULL, ns1__editDcuOperation, ns1__editDcuOperationResponse) : SOAP_EOM; };
	/// Invoke 'addLcuOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__addLcuOperation(_ns1__addLcuOperation *ns1__addLcuOperation, _ns1__addLcuOperationResponse *ns1__addLcuOperationResponse) { return soap ? soap_call___ns1__addLcuOperation(soap, endpoint, NULL, ns1__addLcuOperation, ns1__addLcuOperationResponse) : SOAP_EOM; };
	/// Invoke 'removeLcuOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__removeLcuOperation(_ns1__removeLcuOperation *ns1__removeLcuOperation, _ns1__removeLcuOperationResponse *ns1__removeLcuOperationResponse) { return soap ? soap_call___ns1__removeLcuOperation(soap, endpoint, NULL, ns1__removeLcuOperation, ns1__removeLcuOperationResponse) : SOAP_EOM; };
	/// Invoke 'editLcuOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__editLcuOperation(_ns1__editLcuOperation *ns1__editLcuOperation, _ns1__editLcuOperationResponse *ns1__editLcuOperationResponse) { return soap ? soap_call___ns1__editLcuOperation(soap, endpoint, NULL, ns1__editLcuOperation, ns1__editLcuOperationResponse) : SOAP_EOM; };
	/// Invoke 'addLineOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__addLineOperation(_ns1__addLineOperation *ns1__addLineOperation, _ns1__addLineOperationResponse *ns1__addLineOperationResponse) { return soap ? soap_call___ns1__addLineOperation(soap, endpoint, NULL, ns1__addLineOperation, ns1__addLineOperationResponse) : SOAP_EOM; };
	/// Invoke 'removeLineOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__removeLineOperation(_ns1__removeLineOperation *ns1__removeLineOperation, _ns1__removeLineOperationResponse *ns1__removeLineOperationResponse) { return soap ? soap_call___ns1__removeLineOperation(soap, endpoint, NULL, ns1__removeLineOperation, ns1__removeLineOperationResponse) : SOAP_EOM; };
	/// Invoke 'editLineOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__editLineOperation(_ns1__editLineOperation *ns1__editLineOperation, _ns1__editLineOperationResponse *ns1__editLineOperationResponse) { return soap ? soap_call___ns1__editLineOperation(soap, endpoint, NULL, ns1__editLineOperation, ns1__editLineOperationResponse) : SOAP_EOM; };
	/// Invoke 'addProgramOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__addProgramOperation(_ns1__addProgramOperation *ns1__addProgramOperation, _ns1__addProgramOperationResponse *ns1__addProgramOperationResponse) { return soap ? soap_call___ns1__addProgramOperation(soap, endpoint, NULL, ns1__addProgramOperation, ns1__addProgramOperationResponse) : SOAP_EOM; };
	/// Invoke 'removeProgramOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__removeProgramOperation(_ns1__removeProgramOperation *ns1__removeProgramOperation, _ns1__removeProgramOperationResponse *ns1__removeProgramOperationResponse) { return soap ? soap_call___ns1__removeProgramOperation(soap, endpoint, NULL, ns1__removeProgramOperation, ns1__removeProgramOperationResponse) : SOAP_EOM; };
	/// Invoke 'controlLcuOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__controlLcuOperation(_ns1__controlLcuOperation *ns1__controlLcuOperation, _ns1__controlLcuOperationResponse *ns1__controlLcuOperationResponse) { return soap ? soap_call___ns1__controlLcuOperation(soap, endpoint, NULL, ns1__controlLcuOperation, ns1__controlLcuOperationResponse) : SOAP_EOM; };
	/// Invoke 'controlLineOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__controlLineOperation(_ns1__controlLineOperation *ns1__controlLineOperation, _ns1__controlLineOperationResponse *ns1__controlLineOperationResponse) { return soap ? soap_call___ns1__controlLineOperation(soap, endpoint, NULL, ns1__controlLineOperation, ns1__controlLineOperationResponse) : SOAP_EOM; };
	/// Invoke 'setProgramDcuOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__setProgramDcuOperation(_ns1__setProgramDcuOperation *ns1__setProgramDcuOperation, _ns1__setProgramDcuOperationResponse *ns1__setProgramDcuOperationResponse) { return soap ? soap_call___ns1__setProgramDcuOperation(soap, endpoint, NULL, ns1__setProgramDcuOperation, ns1__setProgramDcuOperationResponse) : SOAP_EOM; };
	/// Invoke 'getEventLogOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__getEventLogOperation(_ns1__getEventLogOperation *ns1__getEventLogOperation, _ns1__getEventLogOperationResponse *ns1__getEventLogOperationResponse) { return soap ? soap_call___ns1__getEventLogOperation(soap, endpoint, NULL, ns1__getEventLogOperation, ns1__getEventLogOperationResponse) : SOAP_EOM; };
	/// Invoke 'updateReadEventLogOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__updateReadEventLogOperation(_ns1__updateReadEventLogOperation *ns1__updateReadEventLogOperation, _ns1__updateReadEventLogOperationResponse *ns1__updateReadEventLogOperationResponse) { return soap ? soap_call___ns1__updateReadEventLogOperation(soap, endpoint, NULL, ns1__updateReadEventLogOperation, ns1__updateReadEventLogOperationResponse) : SOAP_EOM; };
	/// Invoke 'deleteEventLogOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__deleteEventLogOperation(_ns1__deleteEventLogOperation *ns1__deleteEventLogOperation, _ns1__deleteEventLogOperationResponse *ns1__deleteEventLogOperationResponse) { return soap ? soap_call___ns1__deleteEventLogOperation(soap, endpoint, NULL, ns1__deleteEventLogOperation, ns1__deleteEventLogOperationResponse) : SOAP_EOM; };
	/// Invoke 'getUserLogOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__getUserLogOperation(_ns1__getUserLogOperation *ns1__getUserLogOperation, _ns1__getUserLogOperationResponse *ns1__getUserLogOperationResponse) { return soap ? soap_call___ns1__getUserLogOperation(soap, endpoint, NULL, ns1__getUserLogOperation, ns1__getUserLogOperationResponse) : SOAP_EOM; };
	/// Invoke 'deleteUserLogOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__deleteUserLogOperation(_ns1__deleteUserLogOperation *ns1__deleteUserLogOperation, _ns1__deleteUserLogOperationResponse *ns1__deleteUserLogOperationResponse) { return soap ? soap_call___ns1__deleteUserLogOperation(soap, endpoint, NULL, ns1__deleteUserLogOperation, ns1__deleteUserLogOperationResponse) : SOAP_EOM; };
	/// Invoke 'getAllZoneOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__getAllZoneOperation(_ns1__getAllZoneOperation *ns1__getAllZoneOperation, _ns1__getAllZoneOperationResponse *ns1__getAllZoneOperationResponse) { return soap ? soap_call___ns1__getAllZoneOperation(soap, endpoint, NULL, ns1__getAllZoneOperation, ns1__getAllZoneOperationResponse) : SOAP_EOM; };
	/// Invoke 'getAllZoneForUserOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__getAllZoneForUserOperation(_ns1__getAllZoneForUserOperation *ns1__getAllZoneForUserOperation, _ns1__getAllZoneForUserOperationResponse *ns1__getAllZoneForUserOperationResponse) { return soap ? soap_call___ns1__getAllZoneForUserOperation(soap, endpoint, NULL, ns1__getAllZoneForUserOperation, ns1__getAllZoneForUserOperationResponse) : SOAP_EOM; };
	/// Invoke 'SetDcuToZoneOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__SetDcuToZoneOperation(_ns1__SetDcuToZoneOperation *ns1__SetDcuToZoneOperation, _ns1__SetDcuToZoneOperationResponse *ns1__SetDcuToZoneOperationResponse) { return soap ? soap_call___ns1__SetDcuToZoneOperation(soap, endpoint, NULL, ns1__SetDcuToZoneOperation, ns1__SetDcuToZoneOperationResponse) : SOAP_EOM; };
	/// Invoke 'addZoneOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__addZoneOperation(_ns1__addZoneOperation *ns1__addZoneOperation, _ns1__addZoneOperationResponse *ns1__addZoneOperationResponse) { return soap ? soap_call___ns1__addZoneOperation(soap, endpoint, NULL, ns1__addZoneOperation, ns1__addZoneOperationResponse) : SOAP_EOM; };
	/// Invoke 'editZoneOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__editZoneOperation(_ns1__editZoneOperation *ns1__editZoneOperation, _ns1__editZoneOperationResponse *ns1__editZoneOperationResponse) { return soap ? soap_call___ns1__editZoneOperation(soap, endpoint, NULL, ns1__editZoneOperation, ns1__editZoneOperationResponse) : SOAP_EOM; };
	/// Invoke 'removeZoneOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__removeZoneOperation(_ns1__removeZoneOperation *ns1__removeZoneOperation, _ns1__removeZoneOperationResponse *ns1__removeZoneOperationResponse) { return soap ? soap_call___ns1__removeZoneOperation(soap, endpoint, NULL, ns1__removeZoneOperation, ns1__removeZoneOperationResponse) : SOAP_EOM; };
	/// Invoke 'getAllUserOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__getAllUserOperation(_ns1__getAllUserOperation *ns1__getAllUserOperation, _ns1__getAllUserOperationResponse *ns1__getAllUserOperationResponse) { return soap ? soap_call___ns1__getAllUserOperation(soap, endpoint, NULL, ns1__getAllUserOperation, ns1__getAllUserOperationResponse) : SOAP_EOM; };
	/// Invoke 'addUserOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__addUserOperation(_ns1__addUserOperation *ns1__addUserOperation, _ns1__addUserOperationResponse *ns1__addUserOperationResponse) { return soap ? soap_call___ns1__addUserOperation(soap, endpoint, NULL, ns1__addUserOperation, ns1__addUserOperationResponse) : SOAP_EOM; };
	/// Invoke 'editUserOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__editUserOperation(_ns1__editUserOperation *ns1__editUserOperation, _ns1__editUserOperationResponse *ns1__editUserOperationResponse) { return soap ? soap_call___ns1__editUserOperation(soap, endpoint, NULL, ns1__editUserOperation, ns1__editUserOperationResponse) : SOAP_EOM; };
	/// Invoke 'removeUserOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__removeUserOperation(_ns1__removeUserOperation *ns1__removeUserOperation, _ns1__removeUserOperationResponse *ns1__removeUserOperationResponse) { return soap ? soap_call___ns1__removeUserOperation(soap, endpoint, NULL, ns1__removeUserOperation, ns1__removeUserOperationResponse) : SOAP_EOM; };
	/// Invoke 'editUserByUserOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__editUserByUserOperation(_ns1__editUserByUserOperation *ns1__editUserByUserOperation, _ns1__editUserByUserOperationResponse *ns1__editUserByUserOperationResponse) { return soap ? soap_call___ns1__editUserByUserOperation(soap, endpoint, NULL, ns1__editUserByUserOperation, ns1__editUserByUserOperationResponse) : SOAP_EOM; };
	/// Invoke 'getProgramOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__getProgramOperation(_ns1__getProgramOperation *ns1__getProgramOperation, _ns1__getProgramOperationResponse *ns1__getProgramOperationResponse) { return soap ? soap_call___ns1__getProgramOperation(soap, endpoint, NULL, ns1__getProgramOperation, ns1__getProgramOperationResponse) : SOAP_EOM; };
	/// Invoke 'editProgramOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__editProgramOperation(_ns1__editProgramOperation *ns1__editProgramOperation, _ns1__editProgramOperationResponse *ns1__editProgramOperationResponse) { return soap ? soap_call___ns1__editProgramOperation(soap, endpoint, NULL, ns1__editProgramOperation, ns1__editProgramOperationResponse) : SOAP_EOM; };
	/// Invoke 'getDayScheduleOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__getDayScheduleOperation(_ns1__getDayScheduleOperation *ns1__getDayScheduleOperation, _ns1__getDayScheduleOperationResponse *ns1__getDayScheduleOperationResponse) { return soap ? soap_call___ns1__getDayScheduleOperation(soap, endpoint, NULL, ns1__getDayScheduleOperation, ns1__getDayScheduleOperationResponse) : SOAP_EOM; };
	/// Invoke 'editDayScheduleOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__editDayScheduleOperation(_ns1__editDayScheduleOperation *ns1__editDayScheduleOperation, _ns1__editDayScheduleOperationResponse *ns1__editDayScheduleOperationResponse) { return soap ? soap_call___ns1__editDayScheduleOperation(soap, endpoint, NULL, ns1__editDayScheduleOperation, ns1__editDayScheduleOperationResponse) : SOAP_EOM; };
	/// Invoke 'removeDayScheduleOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__removeDayScheduleOperation(_ns1__removeDayScheduleOperation *ns1__removeDayScheduleOperation, _ns1__removeDayScheduleOperationResponse *ns1__removeDayScheduleOperationResponse) { return soap ? soap_call___ns1__removeDayScheduleOperation(soap, endpoint, NULL, ns1__removeDayScheduleOperation, ns1__removeDayScheduleOperationResponse) : SOAP_EOM; };
	/// Invoke 'addDayScheduleOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__addDayScheduleOperation(_ns1__addDayScheduleOperation *ns1__addDayScheduleOperation, _ns1__addDayScheduleOperationResponse *ns1__addDayScheduleOperationResponse) { return soap ? soap_call___ns1__addDayScheduleOperation(soap, endpoint, NULL, ns1__addDayScheduleOperation, ns1__addDayScheduleOperationResponse) : SOAP_EOM; };
	/// Invoke 'getListScheduleOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__getListScheduleOperation(_ns1__getListScheduleOperation *ns1__getListScheduleOperation, _ns1__getListScheduleOperationResponse *ns1__getListScheduleOperationResponse) { return soap ? soap_call___ns1__getListScheduleOperation(soap, endpoint, NULL, ns1__getListScheduleOperation, ns1__getListScheduleOperationResponse) : SOAP_EOM; };
	/// Invoke 'addListScheduleOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__addListScheduleOperation(_ns1__addListScheduleOperation *ns1__addListScheduleOperation, _ns1__addListScheduleOperationResponse *ns1__addListScheduleOperationResponse) { return soap ? soap_call___ns1__addListScheduleOperation(soap, endpoint, NULL, ns1__addListScheduleOperation, ns1__addListScheduleOperationResponse) : SOAP_EOM; };
	/// Invoke 'editListScheduleOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__editListScheduleOperation(_ns1__editListScheduleOperation *ns1__editListScheduleOperation, _ns1__editListScheduleOperationResponse *ns1__editListScheduleOperationResponse) { return soap ? soap_call___ns1__editListScheduleOperation(soap, endpoint, NULL, ns1__editListScheduleOperation, ns1__editListScheduleOperationResponse) : SOAP_EOM; };
	/// Invoke 'removeListScheduleOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__removeListScheduleOperation(_ns1__removeListScheduleOperation *ns1__removeListScheduleOperation, _ns1__removeListScheduleOperationResponse *ns1__removeListScheduleOperationResponse) { return soap ? soap_call___ns1__removeListScheduleOperation(soap, endpoint, NULL, ns1__removeListScheduleOperation, ns1__removeListScheduleOperationResponse) : SOAP_EOM; };
	/// Invoke 'getScheduleOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__getScheduleOperation(_ns1__getScheduleOperation *ns1__getScheduleOperation, _ns1__getScheduleOperationResponse *ns1__getScheduleOperationResponse) { return soap ? soap_call___ns1__getScheduleOperation(soap, endpoint, NULL, ns1__getScheduleOperation, ns1__getScheduleOperationResponse) : SOAP_EOM; };
	/// Invoke 'addScheduleOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__addScheduleOperation(_ns1__addScheduleOperation *ns1__addScheduleOperation, _ns1__addScheduleOperationResponse *ns1__addScheduleOperationResponse) { return soap ? soap_call___ns1__addScheduleOperation(soap, endpoint, NULL, ns1__addScheduleOperation, ns1__addScheduleOperationResponse) : SOAP_EOM; };
	/// Invoke 'editScheduleOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__editScheduleOperation(_ns1__editScheduleOperation *ns1__editScheduleOperation, _ns1__editScheduleOperationResponse *ns1__editScheduleOperationResponse) { return soap ? soap_call___ns1__editScheduleOperation(soap, endpoint, NULL, ns1__editScheduleOperation, ns1__editScheduleOperationResponse) : SOAP_EOM; };
	/// Invoke 'removeScheduleOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__removeScheduleOperation(_ns1__removeScheduleOperation *ns1__removeScheduleOperation, _ns1__removeScheduleOperationResponse *ns1__removeScheduleOperationResponse) { return soap ? soap_call___ns1__removeScheduleOperation(soap, endpoint, NULL, ns1__removeScheduleOperation, ns1__removeScheduleOperationResponse) : SOAP_EOM; };
	/// Invoke 'getLcuLogOperation' of service 'botServiceSOAP' and return error code (or SOAP_OK)
	virtual int __ns1__getLcuLogOperation(_ns1__getLcuLogOperation *ns1__getLcuLogOperation, _ns1__getLcuLogOperationResponse *ns1__getLcuLogOperationResponse) { return soap ? soap_call___ns1__getLcuLogOperation(soap, endpoint, NULL, ns1__getLcuLogOperation, ns1__getLcuLogOperationResponse) : SOAP_EOM; };
};
#endif