#!/bin/bash

HERE=$(pwd)
SRC_DIR="$HERE/../src/"
GSOAP_DIR="$HERE/../../resource/gsoap-2.8.7/gsoap"

generation()
{
	wsdl2h -o botService.h botService.wsdl && \
	soapcpp2 botService.h
}

generation_copy()
{
	soapcpp2 botService.h &&
	echo "cp botService.nsmap soapC.cpp soapClient.cpp soapH.h  soapStub.h $SRC_DIR" &&
	cp botService.nsmap soapC.cpp soapClient.cpp soapH.h  soapStub.h $SRC_DIR &&
	echo "cp $GSOAP_DIR/stdsoap2.h $GSOAP_DIR/stdsoap2.cpp $SRC_DIR" &&
	cp $GSOAP_DIR/stdsoap2.h $GSOAP_DIR/stdsoap2.cpp $SRC_DIR	
}


if [ "$1" == "clean" ]; then
	rm -rf *.xml *nsmap soap* *.xsd
else
	if [ "$1" == "gen" ]; then
		generation
	else
		generation_copy
	fi
fi
