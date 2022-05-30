
helpusage() {
	echo "Usage note: sudo ./tc_info <mode> <build_type> <module_name> <profile>"
	echo "<mode> = name|count"
	echo "<build_type> = itc|ctc|utc"
	echo "<profile> = mobile|wearable. <profile> is optional and if not used then it will give total count/name of different test cases from all profile."
	echo ""
	exit 1
}

if [ -z $3 ]; then
	helpusage
fi

MODE=$1
if [ "$MODE" != "name" ] && [ "$MODE" != "count" ]; then
	helpusage
fi

BUILD_TYPE=$2
MODULE_NAME=$3
PROJECT_DIR="$(cd "$(dirname $0)" && pwd)"
FINAL_TC_COUNT=0

if [ "$BUILD_TYPE" != "itc" ] && [ "$BUILD_TYPE" != "utc" ] && [ "$BUILD_TYPE" != "ctc" ]; then
	helpusage
fi

TAG="native"
if [ "$BUILD_TYPE" = "utc" ]; then
	TAG="core"
fi


if [ "$4" != "" ]; then
	PROFILE=$4
	if [ ! -d src/$BUILD_TYPE/$MODULE_NAME ]; then
		echo "[ERROR] 'src/$BUILD_TYPE/$MODULE_NAME' DOES NOT EXIST"
		exit 1
	fi

	if [ -e src/$BUILD_TYPE/$MODULE_NAME/tct-$MODULE_NAME-$TAG\_$PROFILE.h ]; then
		AUTO_PROFILE_LIST=$(cd $PROJECT_DIR; python scripts_tpk/retriever.py -f src/$BUILD_TYPE/$MODULE_NAME $BUILD_TYPE $PROFILE $MODULE_NAME )
		if [ "$MODE" = "count" ]; then
			#calculate count
			for TC1 in $AUTO_PROFILE_LIST
			do
				FINAL_TC_COUNT=$((FINAL_TC_COUNT+1))
			done
			echo "$FINAL_TC_COUNT"
			exit 0
		fi

		if [ "$MODE" = "name" ]; then
			#extract name
			echo ""
			for TC1 in $AUTO_PROFILE_LIST
			do
				echo $TC1 | sed 's/,.*//'
			done
			echo ""
			exit 0
		fi
	else
		echo "[ERROR] tct header file for $PROFILE DOES NOT EXIST at 'src/$BUILD_TYPE/$MODULE_NAME'"
		exit 1
	fi
fi


if [ -d src/$BUILD_TYPE/$MODULE_NAME ]; then
	if [ -e src/$BUILD_TYPE/$MODULE_NAME/tct-$MODULE_NAME-$TAG\_mobile.h ]; then
		AUTO_MOB_LIST=$(cd $PROJECT_DIR; python scripts_tpk/retriever.py -f src/$BUILD_TYPE/$MODULE_NAME $BUILD_TYPE mobile $MODULE_NAME )
	fi

	if [ -e src/$BUILD_TYPE/$MODULE_NAME/tct-$MODULE_NAME-$TAG\_wearable.h ]; then
		AUTO_WEAR_LIST=$(cd $PROJECT_DIR; python scripts_tpk/retriever.py -f src/$BUILD_TYPE/$MODULE_NAME $BUILD_TYPE wearable $MODULE_NAME )
	fi

	if [ -e src/$BUILD_TYPE/$MODULE_NAME/tct-$MODULE_NAME-$TAG\_tv.h ]; then
		AUTO_TV_LIST=$(cd $PROJECT_DIR; python scripts_tpk/retriever.py -f src/$BUILD_TYPE/$MODULE_NAME $BUILD_TYPE tv $MODULE_NAME )
	fi

	AUTO_LIST=$AUTO_MOB_LIST;

	#for wearable
	for TC1 in $AUTO_WEAR_LIST
	do
		FOUND=0
		for TC2 in $AUTO_LIST
		do
			if [ "$TC1" = "$TC2" ]; then
				FOUND=1
				break
			fi
		done
		if [ $FOUND = 0 ]; then
			AUTO_LIST=`echo $AUTO_LIST"\n"$TC1`
		fi
	done

        for TC1 in $AUTO_TV_LIST
        do
                FOUND=0
                for TC2 in $AUTO_LIST
                do
                        if [ "$TC1" = "$TC2" ]; then
                                FOUND=1
                                break
                        fi
                done
                if [ $FOUND = 0 ]; then
                        AUTO_LIST=`echo $AUTO_LIST"\n"$TC1`
                fi
        done

	if [ "$MODE" = "count" ]; then
		#calculate count
		for TC1 in $AUTO_LIST
		do
			FINAL_TC_COUNT=$((FINAL_TC_COUNT+1))
		done
		echo "$FINAL_TC_COUNT"
		exit 0
	fi

	if [ "$MODE" = "name" ]; then
		#extract name
		for TC1 in $AUTO_LIST
		do
			echo $TC1 | sed 's/,.*//'
		done
		exit 0
	fi

else
	echo ""
	echo "[ERROR] 'src/$BUILD_TYPE/$MODULE_NAME' DOES NOT EXIST"
	echo ""
	exit 1
fi
