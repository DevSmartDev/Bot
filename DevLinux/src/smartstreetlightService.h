/*
 * =====================================================================================
 *
 *	Filename:  smartstreetlightService.h
 *
 *	Description:  
 *
 *	Version:  1.0
 *	Created:  08/25/2016 03:01:40 PM
 *	Revision:  none
 *	Compiler:  gcc
 *
 *	Author:  Nghi Hoang (), nghi.hoangminhthe@icdrec.edu.vn
 *	Company:  ICDREC
 *
 * =====================================================================================
 */
//gsoap ns1 service name:       smartstreetlightService
//gsoap ns1 service type:       MyType 
//gsoap ns1 service port:       http://localhost:8080/axis2/services/SplServices
//gsoap ns1 service namespace:  urn:wsdl.icdrec.edu.vn

struct _ns1__MyFirstException {
	char* text 1;
};
struct _ns1__MySecondException {
	int number 1;
};

//gsoap ns1 service method-fault: myOperation _ns1__MyFirstException
//gsoap ns1 service method-fault: myOperation _ns1__MySecondException
int ns1__myOperation(
	char * myInput,
	struct ns1__myOperationResponse { char *myOutput; } *
	);
