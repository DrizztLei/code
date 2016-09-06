# /etc/skel/.bash_profile

# This file is sourced by bash for login shells.  The following line
# runs your .bashrc and is recommended by the bash info pages.
#if [[ -f ~/.bashrc ]] ; then
#	. ~/.bashrc
#fi
export LANG=en_US.UTF-8
export PATH="/usr/bin/:/usr/sbin/:/bin/:/sbin/:/usr/local/bin/:~/bin/:~/enviroment/iot-sol/:~/work/bin/:"
#export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/opt/cuda/lib64"
export LD_LIBRARY_PATH="/opt/cuda/lib64:/opt/cuda/lib64:/opt/cuda/lib64:~/enviroment/HKVision/lib/:~/enviroment/HKVision/lib/HCNetSDKCom/:"
export CUDA_HOME=/opt/cuda
export XIM="fcitx"
export XIM_PROGRAM="fcitx"
export XMODIFIERS="@im=fcitx"
export GTK_IM_MODULE="fcitx"
export QT_IM_MODULE="fcitx"
PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/lib/pkgconfig/
export PATH="${PATH}${LD_LIBRARY_PATH}"
