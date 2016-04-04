#!/bin/sh
JVMINCLUDE=/usr/lib/jvm/java-openjdk/include
CFLAGS="-m32 -I${JVMINCLUDE}/linux";export CFLAGS
rm -rf usr
h-to-ffi.sh ${JVMINCLUDE}/jni.h
