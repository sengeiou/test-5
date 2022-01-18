#!/bin/bash

SCRIPT_PATH=`dirname $(readlink -f $0)`

echo ""
echo "python $SCRIPT_PATH/make_msg_header.py"
python $SCRIPT_PATH/make_msg_header.py

echo ""
echo "python $SCRIPT_PATH/find_differences.py $SCRIPT_PATH/../include/private/tizen_error_private.h $SCRIPT_PATH/tizen_error_private.h"
python $SCRIPT_PATH/find_differences.py $SCRIPT_PATH/../include/private/tizen_error_private.h $SCRIPT_PATH/tizen_error_private.h

echo ""
echo "mv $SCRIPT_PATH/tizen_error_private.h $SCRIPT_PATH/../include/private/tizen_error_private.h"
mv $SCRIPT_PATH/tizen_error_private.h $SCRIPT_PATH/../include/private/tizen_error_private.h