#!/bin/bash
#---------------------------------------------------------------------------------
# Source and Install directories
#---------------------------------------------------------------------------------

#prefix=$(pwd)/ming32 # installation directory
#---------------------------------------------------------------------------------
# set the target and compiler flags
#---------------------------------------------------------------------------------
target=vn8
CXXFLAGS=""
CFLAGS=""
export DEBUG_FLAGS=''
CONF_FLAGS=""
SERVER=icdrec@192.168.52.10:/home/icdrec/ftp/toolchain-compiler/spl_app
FULL_PKG_NAME=
#---------------------------------------------------------------------------------
# Build and install binutils
#---------------------------------------------------------------------------------
config_spl()
{
	if [ "$OS_TYPE" = "win" ]; then

		if [ "$DIR_PACKAGE" == "NA" ]; then
			echo "error: non setup package dir for SmartStreetLight for win"
			exit 1
		fi
		if [ "$IS_RELEASE" = "NA" ]; then
			FOLDER="$(pwd)/build_win_package_debug"
		else
			FOLDER="$(pwd)/build_win_package_release"
		fi
		if [ "$DIR_INSTALL" = "NA" ]; then 
			DIR_INSTALL="$FOLDER/SmartStreetLight"
				
		else
			DIR_INSTALL="$DIR_INSTALL/SmartStreetLight"
		fi
		
			
		CONF_FLAGS="
				--prefix=$DIR_INSTALL \
				--host=i586-mingw32msvc \
				--build=i686-linux-gnu"

	else

		if [ "$OS_TYPE" = "NA" ]; then
			OS_TYPE=$(expr substr "$(lsb_release -i)" 17 33)
		fi
		if [ $IS_MAKE -eq $TRUE ]; then 
			FOLDER=build_$OS_TYPE
		else
			if [ "$IS_RELEASE" = "NA" ]; then
				FOLDER=build_${OS_TYPE}_package_debug
			else
				FOLDER=build_${OS_TYPE}_package_release
			fi	
		fi	
		if [ "$DIR_INSTALL" = "NA" ]; then 
			DIR_INSTALL=/usr/local
		fi
		CONF_FLAGS="--prefix=$DIR_INSTALL"
	fi

}
TYPE_PACK_OP="-D"
make_spl()
{
	
	mkdir -p $FOLDER && cd $FOLDER
	if [ ! -f Makefile ]; then
		echo ../configure $CONF_FLAGS 

		if [ "$IS_RELEASE" = "NA" ]; then
			export  CXXFLAGS="$CXXFLAGS"
			export  CFLAGS="$CFLAGS"
		else
			export  CXXFLAGS="$CXXFLAGS $IS_RELEASE"
			export  CFLAGS="$CFLAGS $IS_RELEASE"
		fi
		../configure $CONF_FLAGS 
	fi
	make V=s && $SUDO make install
}
create_install_sh()
{
	mkdir -p $FOLDER
	F_INSTALL=$FOLDER"/install.sh"
	rm -rf ${F_INSTALL}
	echo "make install" > "${F_INSTALL}"
	chmod +x ${FOLDER}/install.sh
}
package_spl()
{
	echo mkdir -p $FOLDER 
	mkdir -p $FOLDER && cd $FOLDER
	if [ ! -f Makefile ]; then
		echo ../configure $CONF_FLAGS && 
		if [ "$IS_RELEASE" = "NA" ]; then
			export  CFLAGS="$CFLAGS"
			export  CXXFLAGS="$CXXFLAGS"

		else
			export  CXXFLAGS="$CXXFLAGS $IS_RELEASE"
			export  CFLAGS="$CFLAGS $IS_RELEASE"
		fi

		../configure $CONF_FLAGS 
	fi
	if [ "$OS_TYPE" = "win" ]; then
		which makensis
		if [ $? -ne 0 ]; then
			echo "NSIS not found"
			echo "goto ftp://192.168.52.10/soft-os/soft/NSIS/nsis_installer.tar download nsis_installer"
			exit 1
		fi

		make && make install && \
		echo cp -rf $(pwd)/../../package/depend-package-win/* $DIR_INSTALL && \
		cp -rf $(pwd)/../../package/depend-package-win/* $DIR_INSTALL && \
		cp -rf $(pwd)/../../resource/spl_nsis/* $DIR_INSTALL/.. && \
		makensis setup.nsi
	else
		if [ "$OS_TYPE" != "Debian" ]; then
			TYPE_PACK_OP="-R"	
		fi
		ARCH=$(uname -m)
		if [ "$ARCH" = "i686" ]; then
			ARCH="i386"
		elif [ "$ARCH" = "x86_64" ]; then
			ARCH="amd64"
		fi
		FULL_PKG_NAME=${PACKAGE_NAME}_${PACKAGE_VERSION}-${PACKAGE_RELEASE}_${ARCH}
		make V=s && 
		echo sudo checkinstall $TYPE_PACK_OP --docdir=../doc-pak/ \
					-y --install=no --fstrans=no \
					--exclude=/selinux \
					--reset-uids=yes \
					--pkgname=$PACKAGE_NAME  \
					--pkgrelease=$(git log --pretty=format:\'\' | wc -l) \
					--pkgarch=$ARCH \
					--maintainer="SmartStreetLight <icdrec.edu.vn>" \
					--pakdir=$DIR_PACKAGE --backup=no \
					--requires="gtk+-3.0 glib-2.0 " &&
		sudo checkinstall $TYPE_PACK_OP --docdir=../doc-pak/ \
					-y --install=no --fstrans=no \
					--exclude=/selinux \
					--reset-uids=yes \
					--pkgname=$PACKAGE_NAME  \
					--pkgversion=$PACKAGE_VERSION  \
					--pkgrelease=$PACKAGE_RELEASE \
					--pkgarch=$ARCH \
					--maintainer="SmartStreetLight <icdrec.edu.vn>" \
					--pakdir=$DIR_PACKAGE --backup=no -D $(pwd)/install.sh \
					--requires="gtk+-3.0 glib-2.0 " &&
		sudo alien -k -r ${FULL_PKG_NAME}.deb &&
		cd - || exit 1
	fi
}

help1()
{
	echo "Usage: $0 [OPTION]"
	echo "OPTIONS:"
	echo "  -w32    		: build SmartStreetLight for windows 32bit"
	echo "  -m              	: make and install SmartStreetLight"
        echo "  -p              	: package SmartStreetLight"
        echo "  -r              	: package SmartStreetLight with disable debug"
        echo "  -push              	: push package SmartStreetLight to FTP server"
	echo "  -s      		: build SmartStreetLight with static libmpc/libmpfr/libgmp"
	echo "  -d <dir>     		: dir install of SmartStreetLight"
	echo "  -pkg_name <name>	: set name of package of SmartStreetLight"
	echo "  -su     		: install SmartStreetLight with sudo"
	exit 1
}
push_server()
{
	if [ "$OS_TYPE" = "win" ]; then
		echo push spl_setup.exe to ICDREC server with link $SERVER. &&
		echo sshpass -p 'soft-123456' scp spl_setup.exe $SERVER/spl_setup.exe &&
		sshpass -p 'soft-123456' scp spl_setup.exe $SERVER/spl_setup.exe
		if [ $? != 0 ]; then
			echo "Error: push spl client package to ICDREC server"
			exit 1
		fi
	else
		echo push ${FULL_PKG_NAME}.deb to ICDREC server with link $SERVER. &&
		echo sshpass -p 'soft-123456' scp $FOLDER/${FULL_PKG_NAME}.deb $SERVER/${FULL_PKG_NAME}.deb &&
		sshpass -p 'soft-123456' scp $FOLDER/${FULL_PKG_NAME}.deb $SERVER/${FULL_PKG_NAME}.deb &&
		echo push ${FULL_PKG_NAME}.rpm to ICDREC server with link $SERVER. &&
		sshpass -p 'soft-123456' scp $FOLDER/${FULL_PKG_NAME}.rpm $SERVER/${FULL_PKG_NAME}.rpm 
		if [ $? != 0 ]; then
			echo "Error: push spl client package to ICDREC server"
			exit 1
		fi
	fi
	echo Push spl client successful.
}
FALSE=0
TRUE=1
OS_TYPE="NA"
ENABLE_STATIC=""
DIR_INSTALL="NA"
DIR_PACKAGE=""
PACKAGE_NAME=spl-client
PACKAGE_VERSION="0.0.1"
PACKAGE_RELEASE=$(git log --pretty=format:\'\' | wc -l)
IS_MAKE=$FALSE
IS_PACKAGE=$FALSE
IS_PUSH=$FALSE
IS_RELEASE="NA"
SUDO=""
for PARAM in $1 $2 $3 $4 $5 $6 $7 $8 $9 ${10} ${11} ${12}
do
	case $PRE_PAR in
		-d) 	DIR_INSTALL=$PARAM
			PRE_PAR=""
			continue;;
		-pkg_name)	
			PACKAGE_NAME=$PARAM
			PRE_PAR=""
			continue;;
		-pkg_version)	
			PACKAGE_VERSION=$PARAM
			echo PACKAGE_VERSION=$PACKAGE_VERSION
			PRE_PAR=""
			continue;;
		-pkg_release)	
			PACKAGE_RELEASE=$PARAM
			PRE_PAR=""
			continue;;

		*);;
	esac
	case $PARAM in
		-w32)	OS_TYPE="win";;
		-su) 	SUDO="sudo";;
		-r) 	IS_RELEASE="-D__RELEASE__";;
		-d) 	;;
		-m)     IS_MAKE=$TRUE;;
                -p)     IS_PACKAGE=$TRUE;;
                -push)  IS_PUSH=$TRUE;;
		-pkg_name) ;;
		-pkg_version) ;;	
		-pkg_release) ;;	
		*) 	help1;;
	esac
	PRE_PAR=$PARAM
done
IS_DO=$FALSE
config_spl
create_install_sh
if [ $IS_MAKE -eq $TRUE ]; then
	IS_DO=$TRUE
	make_spl 
elif [ $IS_PACKAGE -eq $TRUE ]; then
	IS_DO=$TRUE
	package_spl 
fi
if [ $IS_PUSH -eq $TRUE ]; then
	IS_DO=$TRUE
	push_server
fi
if [ $IS_DO -eq $FALSE ]; then
	help1
fi