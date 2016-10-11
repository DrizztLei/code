# /etc/skel/.bashrc
#
# This file is sourced by all *interactive* bash shells on startup,
# including some apparently interactive shells such as scp and rcp
# that can't tolerate any output.  So make sure this doesn't display
# anything or bad things will happen !


# Test for an interactive shell.  There is no need to set anything
# past this point for scp and rcp, and it's important to refrain from
# outputting anything in those cases.
if [[ $- != *i* ]] ; then
	# Shell is non-interactive.  Be done now!
	return
fi


# Put your fun stuff here.
#export GTK_IM_MODULE=fcitx
#export QT_IM_MODULE=fcitx
#export XMODIFIERS="@im=fcitx"

#[ -s "$NVM_DIR/nvm.sh" ] && . "$NVM_DIR/nvm.sh"  # This loads nvm

source ~/.bash_profile

#source /opt/poky-edison/1.6/environment-setup-core2-32-poky-linux

