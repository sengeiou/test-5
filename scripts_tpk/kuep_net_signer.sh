#! /bin/bash

# This script signs a file for kUEP via network.
#
# 1. Append meta tags which contains version and level for SecureContainer to original file.
# 2. Calculate sha256 value from the modified file.
# 3. Encode the sha256 value with ASN1.
# 4. Send the value to HSM HardServer then get a signature.
# 5. Append the signature to modified file.
#
# Lee Chang Woo(jason77.lee@samsung.com) - VD Security

usage()
{
        echo 'Usage : kuep_net_signer.sh -s -year 2019 -t [lua|js|elf] -verbose file_to_sign'
        exit
}

FILE_TYPE="elf"
YEAR=""
TZ_MVER=""
UEP_LEVEL="3"

function get_uep_info()
{
        # echo -n "##UEP53"
        # echo -n -e '\x0a\x23\x23\x55\x45\x50\x35\x33'
        CMT_TAG="##"
        if [ "$FILE_TYPE" = "lua" ];then CMT_TAG="--" ; fi
        if [ "$FILE_TYPE" = "js" ];then CMT_TAG="//" ; fi

        ((YNUM=${YEAR}-2014))

        # dprint "YNUM:"$YNUM
        echo -n -e '\x0a'$CMT_TAG"UEP"$YNUM$UEP_LEVEL

        #dprint "UEP_INFO:"$UEP_INFO
}


VERBOSE=0

function dprint()
{
        if [ "$VERBOSE" -eq 1 ]; then echo $* ; fi
}

# Intermediate files
TEMP_FILE=""
SIG_FILE=""
OUT_FILE=""
ASN_CONF_FILE=""
ASN_HASH_FILE=""

function clean_files()
{
        # remove intermediate files
        rm -f $TEMP_FILE $SIG_FILE $OUT_FILE $ASN_CONF_FILE $ASN_HASH_FILE
}

function check_err_exit()
{
        if [ $? -ne 0 ]; then echo $1; clean_files; exit $? ; fi
}


if [ "$#" -le 3 ]
then
        usage
fi

while [ "$1" != "" ]; do
case $1 in
                -s ) SIGN=1
                        ;;
                -tizen_major_ver ) shift
                                TZ_MVER=$1
            		;;
                -year ) shift
                                YEAR=$1
                        ;;
                -l ) shift
                                UEP_LEVEL=$1
                        ;;
                -t ) shift
                                FILE_TYPE=$1
				FILE_TYPE=`echo "${FILE_TYPE}" | tr '[A-Z]' '[a-z]'` # (convering upper to lower charactor)
                                #FILE_TYPE=`echo "${FILE_TYPE,,}"` #can use after bash4 version(converting uppper to lower charactor)
				
                        ;;
                -verbose ) VERBOSE=1
                                ;;
                * ) IN_FILE=$1
                        break
                        ;;
        esac
        shift
done

if [ "$SIGN" = "" ]
then
    usage
fi
if [ "$YEAR" = "" ] && [ "$TZ_MVER" = "" ]
then
    usage
fi
if [ "$IN_FILE" = "" ]
then
    usage
fi

dprint "SIGN:"$SIGN", YEAR="$YEAR", TZ_MVER="$TZ_MVER", TYPE="$FILE_TYPE", LEVEL:"$UEP_LEVEL", IN_FILE:"$IN_FILE

# If tizen_major_ver is given, the YEAR argument should be ignored. 
if [ "$TZ_MVER" != "" ]
then
    ((YEAR=${TZ_MVER}+2014))
fi
dprint "YEAR by TZ_MVER:"$YEAR


## Copy input file to temp file
TEMP_FILE=$(mktemp)
dprint "TEMP_FILE:"$TEMP_FILE


cp $IN_FILE $TEMP_FILE
check_err_exit "Failed to copy input file to temp file"



## Append uep info to input file
UEP_INFO=`get_uep_info`
dprint "UEP_INFO:"$UEP_INFO
echo -n "$UEP_INFO" >> $TEMP_FILE
# if [ "$VERBOSE" -eq 1 ]; then echo "TEMP_FILE:";xxd -s -100 $TEMP_FILE ; fi


## Make config file for ASN1 encoding with sha256 hash
ASN_CONF_FILE=$(mktemp)
cat >$ASN_CONF_FILE <<EOF
asn1 = SEQUENCE:digest_info_and_digest

[digest_info_and_digest]
dinfo = SEQUENCE:digest_info
digest = FORMAT:HEX,OCT:`openssl dgst -sha256 $TEMP_FILE |cut -f 2 -d ' '`

[digest_info]
algid = OID:2.16.840.1.101.3.4.2.1
params = NULL

EOF

if [ "$VERBOSE" -eq 1 ]; then echo "ASN1_CONF($ASN_CONF_FILE):";cat $ASN_CONF_FILE ; fi

# Encode hash value with ASN1
ASN_HASH_FILE=$(mktemp)
openssl asn1parse -i -genconf $ASN_CONF_FILE -out $ASN_HASH_FILE
check_err_exit "Failed to encode hash with asn1"
if [ "$VERBOSE" -eq 1 ]; then echo "ASN_HASH($ASN_HASH_FILE):";xxd $ASN_HASH_FILE ; fi

## Request a base64 encoded signature from HSM HardServer.
SIG_FILE=$(mktemp)
dprint "SIG_FILE:"$SIG_FILE

curl -m 240 -w %{http_code} -f -F "file=@$ASN_HASH_FILE" -F "file_name=$IN_FILE" -F "year=$YEAR" -o "$SIG_FILE" http://10.40.68.214/signKUEPhash.do
# curl -m 240 -w %{http_code} -f -F "file_name=$IN_FILE" -F "year=$YEAR" -F "hash=$HASH" http://10.40.68.214/signKUEPhash.do
check_err_exit "Failed to curl"
echo ""
if [ "$VERBOSE" -eq 1 ]; then echo "signature:"; xxd $SIG_FILE ; fi

# Append a signautre
OUT_FILE=$(mktemp)
cat $TEMP_FILE $SIG_FILE > $OUT_FILE
check_err_exit "Failed to merge file"
# if [ "$VERBOSE" -eq 1 ]; then echo "signed_file($OUT_FILE)"; xxd -s -600 $OUT_FILE ; fi

# Copy attribute of original file to signed file.
chmod --reference $IN_FILE $OUT_FILE
# check_err_exit "Failed to copy attributes of the file"


# Move signed file into path of original file.
rm -f $IN_FILE
check_err_exit "Failed to remove original file"

mv $OUT_FILE $IN_FILE
check_err_exit "Failed to move signed file to original file"

clean_files

echo "Signing is done successfully."

exit 0
