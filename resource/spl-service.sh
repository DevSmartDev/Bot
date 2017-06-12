#!/bin/bash
#
# /etc/rc.d/init.d/spl-service
#      This shell script takes care of starting and stopping
#               (the Smart Street Light Server)
#
#
ICDREC_D_HOST=`hostname -a`
DIR_INSTALL="/opt/icdrec"
SPL_FOLDER="ic-spl"
BIN_DIR="$DIR_INSTALL/$SPL_FOLDER/bin"
LIB_DIR="$DIR_INSTALL/$SPL_FOLDER/lib"
SPL_SERVICE_NAME="$SPL_FOLDER"
OPTIONS="> /dev/null &"
KILL="kill `ps -ef | grep -v grep | grep $SPL_SERVICE_NAME | awk '{print $2}'`"
HARD_KILL="kill -9  `ps -ef | grep -v grep | grep $SPL_SERVICE_NAME | awk '{print $2}'`"

start() {
        echo -n "Starting $SPL_SERVICE_NAME..."
	status
	if [ $? -eq 0 ]; then
		echo "$SPL_SERVICE_NAME allready running with pid: $(ps -ef | grep -v grep | grep $SPL_SERVICE_NAME | awk '{print $2}')"
        else
                #cd $BIN_DIR
		export JAVA_HOME=$(readlink -f /usr/bin/java | sed "s:bin/java::")
		export AXIS2_HOME=$DIR_INSTALL/$SPL_FOLDER
		. $BIN_DIR/setenv.sh
		echo java $JAVA_OPTS -classpath "$AXIS2_CLASSPATH" \
    			-Djava.endorsed.dirs="$AXIS2_HOME/lib/endorsed":"$JAVA_HOME/jre/lib/endorsed":"$JAVA_HOME/lib/endorsed" \
    			org.apache.axis2.transport.SimpleAxis2Server \
    			-repo "$AXIS2_HOME"/repository -conf "$AXIS2_HOME"/conf/axis2.xml  
		java $JAVA_OPTS -classpath "$AXIS2_CLASSPATH" \
    			-Djava.endorsed.dirs="$AXIS2_HOME/lib/endorsed":"$JAVA_HOME/jre/lib/endorsed":"$JAVA_HOME/lib/endorsed" \
    			org.apache.axis2.transport.SimpleAxis2Server \
    			-repo "$AXIS2_HOME"/repository -conf "$AXIS2_HOME"/conf/axis2.xml   &
                RETVAL=$?
                return $RETVAL
        fi
	return 0
}

stop() {
        echo -n "Shutting down $SPL_SERVICE_NAME"
        status
	if [ $? -eq 0 ]; then
		echo "..."
				echo echo  "aaaa : $KILL"
		$KILL
		echo  "end"
	else
		echo ": $SPL_SERVICE_NAME not running"
	fi

	for i in {0..30}
	do
		status
		if [ $? -eq 0  ]; then
			echo "$SPL_SERVICE_NAME allready running"
			sleep 1
		else
			break
		fi
	done
	status
	if [ $? -eq 0 ]; then
		echo "$SPL_SERVICE_NAME not yet exit: hard kill"
		#killall -9 $SPL_SERVICE_NAME
		$HARD_KILL
        fi
        #rm -f /var/lock/subsys/$SPL_SERVICE_NAME
        return 0
}
#0: allready running
#1: not running
#
status(){	
	ps -ef | grep -v grep | grep $SPL_SERVICE_NAME > /dev/null
	RETVAL=$?
	return $RETVAL
}
# this function call by crontab example: /etc/ini.d/... recovery
recovery(){
	status
	if [ $? -eq 1 ]; then
		start
	fi	
	return 0	
}

case "$1" in
	start)
		start
		;;
	stop)
		stop
		;;
	status)
		status
		;;
	restart)
		stop
		start
	;;
	recovery)
		recovery
	;;
	*)
		echo "Usage:  {start|stop|status|restart|recovery}"
		exit 1
		;;
esac
exit $?
