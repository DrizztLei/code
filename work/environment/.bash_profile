# /etc/skel/.bash_profile

# This file is sourced by bash for login shells.  The following line
# runs your .bashrc and is recommended by the bash info pages.
#if [[ -f ~/.bashrc ]] ; then
#	. ~/.bashrc
#fi
export NLS_LANG=AMERICAN_AMERICA.UTF8
export LANG=en_US.UTF-8
export PATH="/usr/bin/:/usr/sbin/:/bin/:/sbin/:/usr/local/bin/:/opt/cuda/bin/:~/bin/:/opt/VirtualBox/:~/environment/Bazel/bazel/output/:/opt/bin/:~/environment/iot-sol/:~/work/bin/:~/Android/Sdk/platform-tools/:"
#export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/opt/cuda/lib64"
#export ARCHDIR="/home/elvis/environment/mips/mips-x86.linux-xgcc/"
export ARCHDIR="~/environment/mips/mips/bin/"
export LD_LIBRARY_PATH="/opt/cuda/lib64:/opt/cuda/lib64:/opt/cuda/lib64:~/environment/HKVision/lib/:~/environment/HKVision/lib/HCNetSDKCom/:~/environment/lib/:"
export CUDA_HOME=/opt/cuda
export XIM="fcitx"
export XIM_PROGRAM="fcitx"
export XMODIFIERS="@im=fcitx"
export GTK_IM_MODULE="fcitx"
export QT_IM_MODULE="fcitx"
export JAVA_HOME="/usr/lib/jvm/java-8-openjdk/bin"
PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/lib/pkgconfig/
export VOREEN="~/environment/VoreenVE/voreen-src-3.0.1-unix/bin/"
export PATH="${PATH}${LD_LIBRARY_PATH}${VOREEN}"
export QT_SELECT="qt4"
