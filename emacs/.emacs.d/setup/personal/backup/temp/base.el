;;=======================================================================
;;Author:chen yang (陈杨)
;;Date:2011-10-7
;;Update Date:2011-10-7
;;=======================================================================

;;设置字体大小，默认是Monospace
;;(set-default-font "8x16")
;;(set-default-font "10x20")
;;(set-default-font "9x15")
;;(set-default-font "文泉驿等宽微米黑")
;;(set-default-font "-unknown-Mono-normal-normal-*-15-*-*-*-m-0-iso10646-1")  ;;感觉还可以


;;======================================================================
;;状态栏
;;======================================================================
;;显示时间
;;(display-time)
(display-time-mode 1);;启用时间显示设置，在minibuffer上面的那个杠上
(setq display-time-24hr-format t);;时间使用24小时制
(setq display-time-day-and-date t);;时间显示包括日期和具体时间
;;(setq display-time-use-mail-icon t);;时间栏旁边启用邮件设置
;;(setq display-time-interval 10);;时间的变化频率，单位多少来着？


;;显示列号
(setq column-number-mode t)
;;没列左边显示行号,按f3显示/隐藏行号
(put 'scroll-left 'disabled nil)     ;允许屏幕左移
(put 'scroll-right 'disabled nil)    ;允许屏幕右移
(put 'set-goal-column 'disabled nil)
(put 'narrow-to-region 'disabled nil) 
(put 'upcase-region 'disabled nil)
(put 'downcase-region 'disabled nil)
(put 'LaTeX-hide-environment 'disabled nil)

