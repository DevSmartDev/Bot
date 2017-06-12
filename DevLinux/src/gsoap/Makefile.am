bin_PROGRAMS = gsoap

RESOURCE_DIR=$(srcdir)/../../../resource
WSDL_GSOAP_DIR = $(RESOURCE_DIR)/gsoap-2.8
WSDL2H=${WSDL_GSOAP_DIR}/gsoap/bin/linux386/wsdl2h
SOAPCPP2=${WSDL_GSOAP_DIR}/gsoap/bin/linux386/soapcpp2

gsoap_SOURCES =	$(srcdir)/../../../WebServices/src/botService.wsdl
gsoap$(EXEEXT): $(srcdir)/botService.h

$(srcdir)/botService.h: $(srcdir)/../../../WebServices/src/botService.wsdl
	mkdir -p $(srcdir)/gsoap
	cp -f $(WSDL_GSOAP_DIR)/gsoap/stdsoap2.h $(srcdir)/stdsoap2.h
	cp -f $(WSDL_GSOAP_DIR)/gsoap/stdsoap2.cpp $(srcdir)/stdsoap2.cpp
	$(WSDL2H) -o $(srcdir)/botService.h -s $< -I${WSDL_GSOAP_DIR}
	$(SOAPCPP2) $@ -x -L -2 -C -d$(srcdir) -I${WSDL_GSOAP_DIR}/gsoap/import/

clean:
	rm -f $(srcdir)/botService.h 	
