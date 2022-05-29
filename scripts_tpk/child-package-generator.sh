PROJECT_DIR="$(cd "$(dirname $0)" && pwd)"
BUILD_TC_TYPE=$1
MOD_NAME=$2
BUILD_DEVICE_TYPE=$3
CHILD_PKG_COUNT=$4

TAG_SPEC=$1
PREFIX="native"
PREFIX_PKG_NAME="native"
TAG_SPEC_PKG_NAME=$1
if [ $BUILD_TC_TYPE = "utc" ]; then
	 TAG_SPEC="tests"
	 PREFIX="core"
fi

TIZEN____="tizen_native_6.5"
TCT_PKG="tct-$MOD_NAME-$PREFIX_PKG_NAME-$TAG_SPEC_PKG_NAME"
TCT_PKG_NAME="tct-$MOD_NAME-$PREFIX_PKG_NAME-$TAG_SPEC_PKG_NAME-6.5.zip"
ZIP_PKG_DIR="/opt/tct/$TIZEN____/packages/$BUILD_DEVICE_TYPE"
PKG_INFO="_pkg_info.xml"
PKG_INFO_FILE_LOC="/opt/tct/$TIZEN____/packages/pkg_infos/$BUILD_DEVICE_TYPE$PKG_INFO"
PKG_INFO_FILE="$BUILD_DEVICE_TYPE$PKG_INFO"

PKG_NAME="$PREFIX-$MOD_NAME-$TAG_SPEC"

CHILD_DIR="child-package-generator"

if [ $CHILD_PKG_COUNT -lt 1 ]; then
	echo "------ Invalid (Child Count = $CHILD_PKG_COUNT) specified"
	exit 1
fi


#copy and unzip zip packages from 'ZIP_PKG_DIR' to 'child-package-generator' directory
rm -rf $CHILD_DIR
mkdir -p $CHILD_DIR
cp $ZIP_PKG_DIR/$TCT_PKG_NAME $CHILD_DIR/
cd $CHILD_DIR
unzip $TCT_PKG_NAME > /dev/null 2>&1;

#copy zip packages from 'ZIP_PKG_DIR' to child-package-generator directory
TEST_XML_FILE=tests.xml
LINE_COUNT=0
while read LINE
do
	LINE_COUNT=$((LINE_COUNT+1))
done < opt/$TCT_PKG/$TEST_XML_FILE

if [ $LINE_COUNT -lt 8 ]; then
	cd $PROJECT_DIR/..
	rm -rf $CHILD_DIR
	echo "------ tests.xml file found invalid; Total Number of lines is only $LINE_COUNT"
	exit 1
fi

TC_CURRENT_LINE_COUNT=0
TOTAL_LINES=$LINE_COUNT
TOTAL_TC_LINES=$((LINE_COUNT-8))
TOTAL_TC_COUNT=$((TOTAL_TC_LINES/5))
CHILD_TC_COUNT=$((TOTAL_TC_COUNT/CHILD_PKG_COUNT))
CHILD_TOTAL_TC_LINES=$((CHILD_TC_COUNT*5))
CHILD_PKG_INDEX=0

END_LINE_1=$((TOTAL_LINES-1))
END_LINE_2=$((TOTAL_LINES-2))
#generate child tests.xml
echo "------ Generating tests.xml file for child packages"
LINE_COUNT=0
while read LINE
do
	LINE_COUNT=$((LINE_COUNT+1))
	if [ $LINE_COUNT = 1 ]; then
		START_LINE_1=$LINE
		continue
	elif [ $LINE_COUNT = 2 ]; then
		START_LINE_2=$LINE
		continue
	elif [ $LINE_COUNT = 3 ]; then
		START_LINE_3=$LINE
		continue
	elif [ $LINE_COUNT = 4 ]; then
		START_LINE_4=$LINE
		continue
	elif [ $LINE_COUNT = 5 ]; then
		START_LINE_5=$LINE
		continue
	fi
	TC_CURRENT_LINE_COUNT=$((TC_CURRENT_LINE_COUNT+1))
	index_range=$((TC_CURRENT_LINE_COUNT%CHILD_TOTAL_TC_LINES))
	if [ $index_range = 1 ]; then
		if [ $CHILD_PKG_INDEX -lt $CHILD_PKG_COUNT ]; then
			CHILD_PKG_INDEX=$((CHILD_PKG_INDEX+1))
			echo $START_LINE_1 >> $TEST_XML_FILE\_$CHILD_PKG_INDEX
			echo $START_LINE_2 >> $TEST_XML_FILE\_$CHILD_PKG_INDEX
			echo $START_LINE_3 >> $TEST_XML_FILE\_$CHILD_PKG_INDEX
			echo $START_LINE_4 >> $TEST_XML_FILE\_$CHILD_PKG_INDEX
			echo $START_LINE_5 >> $TEST_XML_FILE\_$CHILD_PKG_INDEX
		fi
	fi

	if [ $LINE_COUNT = $TOTAL_LINES ] || [ $LINE_COUNT = $END_LINE_1 ] || [ $LINE_COUNT = $END_LINE_2 ]; then
		CURRENT_LOOP_COUNT=1
		while [ true ];
		do
			if [ $CURRENT_LOOP_COUNT -gt $CHILD_PKG_COUNT  ]; then
				break
			fi
			echo $LINE >> $TEST_XML_FILE\_$CURRENT_LOOP_COUNT
			CURRENT_LOOP_COUNT=$((CURRENT_LOOP_COUNT+1))
		done		
	else
		echo $LINE >> $TEST_XML_FILE\_$CHILD_PKG_INDEX
	fi

done < opt/$TCT_PKG/$TEST_XML_FILE

#generate new pkg_info.xml
echo "------ Generating new pkg_info file for '$BUILD_DEVICE_TYPE' profile"
cp $PKG_INFO_FILE_LOC ./
LINE_COUNT=0
if [ $BUILD_TC_TYPE = "itc" ]; then
	 category="IntegrationTestCases"
elif [ $BUILD_TC_TYPE = "ctc" ]; then
	 category="ComplianceTestCases"
else
	category="UnitTestCases"
fi
END_XML_LINE="</ns3:testplan>"
DELIMIT="_"
while read LINE
do
	LINE_COUNT=$((LINE_COUNT+1))
	if echo "$LINE" | grep -q "$END_XML_LINE"; then
		CURRENT_LOOP_COUNT=1
		while [ true ];
		do
			if [ $CURRENT_LOOP_COUNT -gt $CHILD_PKG_COUNT  ]; then
				break
			fi
			tc_count=$CHILD_TC_COUNT
			if [ $CURRENT_LOOP_COUNT = $CHILD_PKG_COUNT ]; then
				used_index=$((CURRENT_LOOP_COUNT-1))
				used_tc_count=$((CHILD_TC_COUNT*used_index))
				tc_count=$((TOTAL_TC_COUNT-used_tc_count))
			fi
			PKG_INFO_1="<suite name=\"tct-$MOD_NAME-$PREFIX_PKG_NAME-$TAG_SPEC_PKG_NAME$DELIMIT$CURRENT_LOOP_COUNT\" category=\" $category \">"
			PKG_INFO_2="    <auto_tcn>$tc_count</auto_tcn>"
			PKG_INFO_3="    <manual_tcn>0</manual_tcn>"
			PKG_INFO_4="    <total_tcn>$tc_count</total_tcn>"
			PKG_INFO_5="    <pkg_name>$BUILD_DEVICE_TYPE/tct-$MOD_NAME-$PREFIX_PKG_NAME-$TAG_SPEC_PKG_NAME$DELIMIT$CURRENT_LOOP_COUNT-6.5.zip</pkg_name>"
			PKG_INFO_6="  </suite>"
			echo $PKG_INFO_1 >> $PKG_INFO_FILE\_NEW
			echo $PKG_INFO_2 >> $PKG_INFO_FILE\_NEW
			echo $PKG_INFO_3 >> $PKG_INFO_FILE\_NEW
			echo $PKG_INFO_4 >> $PKG_INFO_FILE\_NEW
			echo $PKG_INFO_5 >> $PKG_INFO_FILE\_NEW
			echo $PKG_INFO_6 >> $PKG_INFO_FILE\_NEW
			CURRENT_LOOP_COUNT=$((CURRENT_LOOP_COUNT+1))
		done	
	fi
	echo "$LINE" >> $PKG_INFO_FILE\_NEW
done < $PKG_INFO_FILE

#create multiple child zip packages
echo "------ Updating inst.sh and Creating zip for child packages"
rm -rf child_packages
mkdir -p child_packages
cd child_packages
CURRENT_LOOP_COUNT=1
while [ true ];
do
	if [ $CURRENT_LOOP_COUNT -gt $CHILD_PKG_COUNT  ]; then
		break
	fi
	mkdir -p child_packages_$CURRENT_LOOP_COUNT
	cd child_packages_$CURRENT_LOOP_COUNT	
	mkdir -p opt
	mkdir -p opt/tct-$MOD_NAME-$PREFIX_PKG_NAME-$TAG_SPEC_PKG_NAME\_$CURRENT_LOOP_COUNT
	cp -rf ../../opt/$TCT_PKG/* ./opt/tct-$MOD_NAME-$PREFIX_PKG_NAME-$TAG_SPEC_PKG_NAME\_$CURRENT_LOOP_COUNT/
	rm ./opt/tct-$MOD_NAME-$PREFIX_PKG_NAME-$TAG_SPEC_PKG_NAME\_$CURRENT_LOOP_COUNT/tests.xml
	cp ../../$TEST_XML_FILE\_$CURRENT_LOOP_COUNT ./opt/tct-$MOD_NAME-$PREFIX_PKG_NAME-$TAG_SPEC_PKG_NAME\_$CURRENT_LOOP_COUNT/$TEST_XML_FILE

	zip -r tct-$MOD_NAME-$PREFIX_PKG_NAME-$TAG_SPEC_PKG_NAME\_$CURRENT_LOOP_COUNT-6.5.zip opt > /dev/null 2>&1;
	cp tct-$MOD_NAME-$PREFIX_PKG_NAME-$TAG_SPEC_PKG_NAME\_$CURRENT_LOOP_COUNT-6.5.zip $ZIP_PKG_DIR/
	cd ..

	CURRENT_LOOP_COUNT=$((CURRENT_LOOP_COUNT+1))
done

cd ..
cp $PKG_INFO_FILE\_NEW $PKG_INFO_FILE_LOC
cd $PROJECT_DIR/..
rm -rf $CHILD_DIR
echo "------ Copying child zip packages to '$ZIP_PKG_DIR'"
echo "------ Updating pkg_info file for '$BUILD_DEVICE_TYPE' profile to '$PKG_INFO_FILE_LOC'"
echo "------ Child Packages Generation Finished Successfully"
