#!/bin/bash
if [ "${0:0:2}" = "./" ]; then
    export LISPBOX_HOME=`pwd`
else
    export LISPBOX_HOME=`dirname $0`
fi
export SBCL_HOME=${LISPBOX_HOME}/sbcl-1.0.42/lib/sbcl
export EMACSDATA=${LISPBOX_HOME}/emacs-23.2/share/emacs/23.2/etc/
export EMACSDOC=${LISPBOX_HOME}/emacs-23.2/share/emacs/23.2/etc/
export EMACSLOADPATH=${LISPBOX_HOME}/emacs-23.2/share/emacs/23.2/site-lisp:\
${LISPBOX_HOME}/emacs-23.2/share/emacs/site-lisp:\
${LISPBOX_HOME}/emacs-23.2/share/emacs/23.2/leim:\
${LISPBOX_HOME}/emacs-23.2/share/emacs/23.2/lisp:\
${LISPBOX_HOME}/emacs-23.2/share/emacs/23.2/lisp/toolbar:\
${LISPBOX_HOME}/emacs-23.2/share/emacs/23.2/lisp/textmodes:\
${LISPBOX_HOME}/emacs-23.2/share/emacs/23.2/lisp/progmodes:\
${LISPBOX_HOME}/emacs-23.2/share/emacs/23.2/lisp/play:\
${LISPBOX_HOME}/emacs-23.2/share/emacs/23.2/lisp/obsolete:\
${LISPBOX_HOME}/emacs-23.2/share/emacs/23.2/lisp/net:\
${LISPBOX_HOME}/emacs-23.2/share/emacs/23.2/lisp/mail:\
${LISPBOX_HOME}/emacs-23.2/share/emacs/23.2/lisp/language:\
${LISPBOX_HOME}/emacs-23.2/share/emacs/23.2/lisp/international:\
${LISPBOX_HOME}/emacs-23.2/share/emacs/23.2/lisp/gnus:\
${LISPBOX_HOME}/emacs-23.2/share/emacs/23.2/lisp/eshell:\
${LISPBOX_HOME}/emacs-23.2/share/emacs/23.2/lisp/emulation:\
${LISPBOX_HOME}/emacs-23.2/share/emacs/23.2/lisp/emacs-lisp:\
${LISPBOX_HOME}/emacs-23.2/share/emacs/23.2/lisp/calendar


PATH=$PATH:${LISPBOX_HOME}/libexec/emacs/23.2/i686-pc-linux-gnu
exec ${LISPBOX_HOME}/emacs-23.2/bin/emacs --no-init-file --no-site-file --eval='(progn (load "lispbox") (slime))'
