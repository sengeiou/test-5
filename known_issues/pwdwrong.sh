#!/bin/bash

env | grep -i dbus > tmp.txt;
cat tmp.txt | cut -f 2-3 -d "=" > dbus.txt;
rm tmp.txt;

if [ ! -f ~/tizen-studio/tools/certificate-encryptor/.secret ]; then
    touch ~/tizen-studio/tools/certificate-encryptor/.secret
    echo ".secret file generated"
fi

cat dbus.txt > ~/tizen-studio/tools/certificate-encryptor/.secret
rm dbus.txt;

echo "Write dbus information to .secret file"
echo "Done"
