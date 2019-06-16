#!/bin/bash

cd /build/esp-idf
git checkout --track origin/$1
git reset --recurse --hard HEAD
git pull -p
git submodule sync
git submodule update --recursive
git clean -fdx
git status

TESTDIR=/build/test
PROJECTDIR=/build/project

rm -rf ${TESTDIR}
cp -a ${PROJECTDIR}/test/main ${TESTDIR}
cd ${TESTDIR}

mkdir components
ln -s ${PROJECTDIR} components/loopp

cd ${TESTDIR}

cat >> sdkconfig.default <<EOF
CONFIG_MQTT_USER=""
CONFIG_MQTT_PASSWORD=""
CONFIG_MQTT_TOPIC_PREFIX="esp"
CONFIG_MQTT_CLIENTID_PREFIX="beaconscanner"
CONFIG_MQTT_TLS=y
CONFIG_CA_CERTIFICATE=y
CONFIG_CLIENT_CERTIFICATES=y
CONFIG_EMBEDDED_CERTIFICATES=y
CONFIG_DEFAULT_BLE_SCANNER=y
CONFIG_ESPTOOLPY_FLASHSIZE_4MB=y
CONFIG_CXX_EXCEPTIONS=y
CONFIG_DISABLE_GCC8_WARNINGS=y
EOF

export PATH=$PATH:/build/$2/xtensa-esp32-elf/bin:$IDF_PATH/tools

case "$3" in
    cmake)
        idf.py build
        ;;
    make)
        make defconfig
        make all
        ;;
    "*")
        ;;
esac
