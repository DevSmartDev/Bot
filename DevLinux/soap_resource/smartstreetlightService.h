/*
 * =====================================================================================
 *
 *	Filename:  smartstreetlightService.h
 *
 *	Description:
 *
 *	Version:  1.0
 *	Created:  09/08/2016 13:30:00 PM
 *	Revision:  none
 *	Compiler:  g++
 *
 *	Author:  Software Department, software@icdrec.edu.vn
 *	Company:  ICDREC VIETNAM
 *
 * =====================================================================================
 */

//gsoap ns1 service name:       smartstreetlightService
//gsoap ns1 service type:       MyType
//gsoap ns1 service port:       http://localhost:8080/axis2/services/SplServices
//gsoap ns1 service namespace:  urn:wsdl.icdrec.edu.vn

#include <list>

/* ==================== Demo operation =================== */
struct _ns1__MyFirstException
{
	char* text 1;
};
struct _ns1__MySecondException
{
	int number 1;
};
//gsoap ns1 service method-fault: myOperation _ns1__MyFirstException
//gsoap ns1 service method-fault: myOperation _ns1__MySecondException
int ns1__myOperation
(
	char * myInput,
	struct ns1__myOperationResponse { char *myOutput; } *
);
/* ======================================================= */

/* ==================== Demo operation =================== */
struct _ns1__OperationException
{
	char* errString;
};
//gsoap ns1 service method-fault: loginOperation _ns1__OperationException
int ns1__loginOperation
(
    char*       login_username,
    char*       login_password,
    struct ns1__loginOperationResponse
    {
        int result_login;
        int id_login;
    } *
);
/* ======================================================= */

struct _ns1__DcuData
{
	char *	name;
	char *  address;
}

struct _ns1__DculistData
{
	 std::list<ns1_DcuData> mylist;
}

int ns1__getDCUList
(
    struct ns1__getDCUListResponse
    {
	ns1_DculistData dcu_list;
    } *
);
