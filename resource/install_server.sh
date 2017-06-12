#!/bin/bash
PARAM=$1
INSTALL_SERVER="install_server"
UNINSTALL_SERVER="uninstall_server"
SETUP_CRONTAB="install_service"
REMOVE_CRONTAB="remove_service"
INSTALL_MYSQLC="install_mysql_c"
UNINSTALL="uninstall"
CMD=" "
LOGFILE="/dev/null 2>&1"

#param Server
NAME_SERVER="SPL Server"
DATABASE_SERVER="SmartStreetLight"
DIR_SERVICE_SERVER="."

#param is used in function build
SERVICE="spl-service.sh"
USER_MYSQL="software"
PASS_MYSQL="softwareicdrec"
DIR_INSTALL="/opt/icdrec"
SPL_FOLDER="ic-spl"
MINUTES=1
DIR_INSTALL_SERVICE="/etc/init.d"
DIR_DATABASE="."
DATABASE_SERVER_INSTALL=SmartStreetLight_struct.sql
MONITOR_SYSTEM="xuongmay/modules/monitoring_system/monitoring_system.module"

REQUIRED_VER_JAVA=1.7.0
REQUIRED_VER_JAVA_NO=`echo $REQUIRED_VER_JAVA | awk '{ print substr($1, 1, 3); }' | sed -e 's;\.;0;g'`
REQUIRED_VER_MYSQL=5.1.0
REQUIRED_VER_MYSQL_NO=`echo $REQUIRED_VER_MYSQL | awk '{ print substr($1, 1, 3); }' | sed -e 's;\.;0;g'`
uninstall_server(){
        #echo uninstall server
        if test -f $DIR_INSTALL_SERVICE/$SERVICE; then
                checkMysqlRoot
		$DIR_INSTALL_SERVICE/$SERVICE stop
                checkDatabase
		setupCrontab uninstall $DIR_INSTALL_SERVICE/$SERVICE
                rm -rf $DIR_INSTALL/$SPL_FOLDER
                echo "Uninstall Smart Street Light Server successfully"
        else
                echo "Smart Street Light Server has removed, already"
        fi
}
 
install_server(){
	#echo install server
	check_mysql
        if [ $? -ne 0 ]; then
                exit 1
        fi
        check_java
        if [ $? -ne 0 ]; then
                exit 1
        fi
	# check root user of MySQL
	checkMysqlRoot
	# setup database local
	checkDatabase
	if [ $? -eq 0 ]; then
		echo "Please setup password for Admin"
		BOOL=0
		until [ $BOOL = 1 ]; do
			read -s -p "password: "  PASSADMIN
			echo ""
			read -s -p "verify password: "  PASSADMIN_VCS
			echo ""
			if [ "$PASSADMIN" != "$PASSADMIN_VCS" ]; then
				read -p "Invalid password. You want setup password admin again.(y/n)"  YES_NO
				if [ "$YES_NO" = "y" ]; then
					echo ""
				else
					exit 1
				fi
			else 
				BOOL=1
			fi
		done

		echo "Create database $DATABASE_SERVER"	
		#echo "	$MYSQL_ROOT -e \"CREATE DATABASE $DATABASE_SERVER CHARACTER SET utf8 COLLATE utf8_general_ci\""
		$MYSQL_ROOT -e "CREATE DATABASE $DATABASE_SERVER CHARACTER SET utf8 COLLATE utf8_general_ci"
		echo "$MYSQL_ROOT $DATABASE_SERVER < $DIR_DATABASE/$DATABASE_SERVER_INSTALL"	
		$MYSQL_ROOT $DATABASE_SERVER < $DIR_DATABASE/$DATABASE_SERVER_INSTALL
		$MYSQL_ROOT -e "GRANT ALL PRIVILEGES ON $DATABASE_SERVER.* TO '$USER_MYSQL'@'localhost' IDENTIFIED BY '$PASS_MYSQL' WITH GRANT OPTION"
		$MYSQL_ROOT -e "INSERT INTO $DATABASE_SERVER.UserTable (UserAccount, UserPasswd,UserPrivileges, UserPhone, UserEmail,UserConfig) VALUES (\"admin\",\"$PASSADMIN\",268435455,\"\",\"\", 0)"
	else
		echo $DATABASE_SERVER database exists
	fi

	# setup services	
	#echo "cp -rf $DIR_SERVICE_SERVER/$SERVICE $DIR_INSTALL_SERVICE"
	mkdir -p $DIR_INSTALL	
	mkdir -p $DIR_INSTALL/$SPL_FOLDER	
	cp -rf ./* $DIR_INSTALL/$SPL_FOLDER
	cp -rf $DIR_SERVICE_SERVER/$SERVICE $DIR_INSTALL_SERVICE
	if [ $? = 1 ]; then
		exit 0
	fi

	chmod +x $DIR_INSTALL_SERVICE/$SERVICE
	setupCrontab install $DIR_INSTALL_SERVICE/$SERVICE
	$DIR_INSTALL_SERVICE/$SERVICE start
	echo "Finish install $NAME_SERVER software."
}
setupCrontab(){
        #echo 1:$1 --- 2:$2
        if [ "$1" = "install" ]; then
                # install local
                #echo "your new lines here" >> temp-crontab
                # MIN HOUR DAYOFMONTH MONTH DAYOFWEEK COMMAND
                #echo "crontab -l | grep $DIR_INSTALL_SERVICE/$SERVICE"
                crontab -l | grep $2 > /dev/null 2>&1
                if [ $? = 1 ]; then
                        echo "Create $2 in crontab"
                        crontab -l > temp-crontab
                        #echo " echo */$MINUTES * * * * $DIR_INSTALL_SERVICE/$SERVICE recovery >> temp-crontab"
                        echo "*/$MINUTES * * * * $2 recovery" >> temp-crontab
                        crontab temp-crontab
                        if [ $? -eq 1 ]; then
                                echo "  Error: create $2 in crontab"
                        fi
                        rm temp-crontab
                        echo "Restart service"
                        #echo "$DIR_INSTALL_SERVICE/$SERVICE start"
                        $2 start  > /dev/null 2>&1
                        echo "Finish setup crontab for $2."
                else
                        echo "$2 was already created in crontab"
                fi
        else
        	# rm local in crontab 
        	crontab -l | grep $2  > /dev/null 2>&1  
        	if [ $? = 0 ]; then
                    #echo "sed -i \"/$SERVICE/d\" temp-crontab"
                     echo delete local service in crontab
			TMP=$(echo $2 | sed -e "s/\//\\\\\//g") &&
			crontab -l > temp-crontab &&
                        sed -i "/$TMP/d" temp-crontab && crontab temp-crontab &&
			rm temp-crontab

                        if [ $? -eq 1 ]; then
                                echo "Error: delete local service for local"
                        else
           			$2 stop  > /dev/null 2>&1
			fi
                else
			echo "$2 was already delete"
        	fi
        fi
}

checkMysqlRoot(){
	echo "check MySQL's root user"
	BOOL=0
	mysql -u root -e "quit" > /dev/null 2>&1

	if [ $? = 1 ]; then
		until [ $BOOL = 1 ]; do
			read -s -p "Please enter MySQL's root password: "  PASSWORD
			echo ""
               		mysql -u root -p$PASSWORD -e "quit"
			if [ $? = 0 ]; then
				MYSQL_ROOT="mysql -u root -p$PASSWORD"		
				MYSQLDUMP_ROOT="mysqldump -u root -p$PASSWORD"		
				let BOOL=1
			else 
				echo ""
				echo invalid password, try again, please.
			fi;
		done
	else
		MYSQL_ROOT="mysql -u root"		
		MYSQLDUMP_ROOT="mysqldump -u root"
	fi
}
check_mysql(){
        echo -n "checking mysql ..."
        MYSQL_EXE=$(which mysql)
        if [ $MYSQL_EXE ];
        then
                $MYSQL_EXE --version > tmp.ver 
                VERSION=`cat tmp.ver | grep -o "[0-9].[0-9].[0-9][0-9]"`
		rm tmp.ver
		VERSION_NO=`echo $VERSION | awk '{ print substr($1, 1, 3); }' | sed -e 's;\.;0;g'`
                if [ $VERSION_NO ]; then
			if [ $VERSION_NO -ge $REQUIRED_VER_MYSQL_NO ]; then
				echo "yes"
				#echo version:$VERSION, version require: $REQUIRED_VERSION
				return  0
                        else
				echo "no"
                                echo "Error: required mysql (version >= $REQUIRED_VER_MYSQL) but version of mysql is $VERSION." 
                        fi
                else
                                echo "Error: required mysql (version >= $REQUIRED_VER_MYSQL) but version of mysql is $VERSION." 
                fi
        else
                echo "no"
                echo "Error: not found mysql. Please, install mysql (version >= $REQUIRED_VER_MYSQL)." 
        fi
        return 1
}


check_java(){
        echo -n "checking java ..."
        JAVA_EXE=$(which java)
        if [ $JAVA_EXE ];
        then
                $JAVA_EXE -version 2> tmp.ver 1> /dev/null
                VERSION=`cat tmp.ver | grep "version" | awk '{ print substr($3, 2, length($3)-2); }'`
		rm tmp.ver
                VERSION_NO=`echo $VERSION | awk '{ print substr($1, 1, 3); }' | sed -e 's;\.;0;g'`
                if [ $VERSION_NO ]; then
			if [ $VERSION_NO -ge $REQUIRED_VER_JAVA_NO ]; then
				echo "yes"
				#echo version:$VERSION, version require: $REQUIRED_VERSION
				return  0
                        else
				echo "no"
                                echo "Error: required java (version >= $REQUIRED_VER_JAVA) but version of java > $VERSION." 
                        fi
                else
                                echo "Error: required java (version >= $REQUIRED_VER_JAVA) but version of java > $VERSION." 
                fi
        else
                echo "no"
                echo "Error: not found java. Please, install java (version >= $REQUIRED_VER_JAVA)." 
        fi
        return 1
}
checkDatabase (){
	echo $MYSQL_ROOT -e "use $DATABASE_SERVER" > /dev/null 2>&1
	$MYSQL_ROOT -e "use $DATABASE_SERVER" > /dev/null 2>&1
	if [ $? -eq 0 ]; then
        	BOOL=0
                until [ $BOOL = 1 ]; do
                	read -p " $DATABASE_SERVER database exists, Do you want to drop $DATABASE_SERVER database?(y/n)"  ANSWER
			if [ $? -ne 0 ]; then
				exit 1
			fi
                        echo ""
			if [ "$ANSWER" = "y" ]; then
				BOOL=1
			fi
			if [ "$ANSWER" = "n" ]; then
                                BOOL=1
                        fi
                done
		if [ "$ANSWER" = "y" ]; then
			#echo $MYSQL_ROOT -e "drop database $DATABASE_SERVER" > /dev/null 2>&1
			$MYSQL_ROOT -e "drop database $DATABASE_SERVER" > /dev/null 2>&1
			return 0
		else
			return 1
		fi
		
	fi
	return 0

}

buildLinuxHelp()
{
echo "Usage: install.sh [OPTION]... "
echo "OPTION: "
echo "	$INSTALL_SERVER			Install Smart Street Light Server"
echo "	$UNINSTALL_SERVER		Uninstall Smart Street Server"
echo ""
}


case $PARAM in
        $INSTALL_SERVER)
		MODE="install";
		install_server;;
	$UNINSTALL_SERVER)
		MODE="uninstall";
		NAME_SERVER=$NAME_SERVER;
		uninstall_server;;

	$SETUP_CRONTAB)
		MODE="install";
		setupCrontab;;
	$REMOVE_CRONTAB)
		MODE="uninstall";
		setupCrontab;;
	*)	buildLinuxHelp;;
esac
