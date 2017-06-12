#!/bin/bash

HERE=$(pwd)
SRC_DIR="$HERE/../src/"
GSOAP_DIR="$HERE/../../resource/gsoap-2.8.7/gsoap"

generation()
{
	wsdl2h -o smartstreetlightService.h smartstreetlightService.wsdl && \
	soapcpp2 smartstreetlightService.h
}

generation_copy()
{
	soapcpp2 smartstreetlightService.h &&
	echo "cp smartstreetlightService.nsmap soapC.cpp soapClient.cpp soapH.h  soapStub.h $SRC_DIR" &&
	cp smartstreetlightService.nsmap soapC.cpp soapClient.cpp soapH.h  soapStub.h $SRC_DIR &&
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
