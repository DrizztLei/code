;;设定行距
(setq default-line-spaceing 4)
;;页宽
(setq default-fill-column 60)
;;缺省模式 text-mode
;;(setq default-major-mode 'text-mode)
;;设置删除记录
(setq kill-ring-max 200)



;以空行结束
;;(setq require-final-newline t)
;;开启语法高亮。
(global-font-lock-mode 1)
;;高亮显示区域选择
(transient-mark-mode t)
;;页面平滑滚动,scroll-margin 3 靠近屏幕边沿3行开始滚动，正好可以看到上下文
;;(setq scroll-margin 3 scroll-consrvatively 10000)
;;高亮显示成对括号
(show-paren-mode t)
(setq show-paren-style 'parentheses)
;;鼠标指针避光标
(mouse-avoidance-mode 'animate)




;;=======================================================================
;;回显区
;;=======================================================================
;;闪屏报警
(setq visible-bell t)
;;使用y or n提问
(fset 'yes-or-no-p 'y-or-n-p)
;;锁定行高
(setq resize-mini-windows nil)
;;递归minibuffer
(setq enable-recursive-minibuffers t)
;;当使用M-x COMMAND后，过1秒显示该COMMAND绑定的键
(setq suggest-key-bindings-1)   ;;默认？


;;======================================================================
;;编辑器的设定
;;======================================================================
;;不产生备份文件
(setq make-backup-files nil)
;;不生成临时文件
(setq-default make-backup-files nil)
;;只渲染当前屏幕语法高亮，加快显示速度
(setq lazy-lock-defer-on-scrolling t)
;;(setq font-lock-support-mode 'lazy-lock-mode)
(setq font-lock-maximum-decoration t)
;;将错误信息显示在回显区
(condition-case err
		        (progn
			            (require 'xxx))
			  (error
			       (message "Can't load xxx-mode %s" (cdr err))))
;;使用X剪贴板
(setq x-select-enable-clipboard t)
;;设定剪贴板的内容格式 适应Firefox
(set-clipboard-coding-system 'ctext)



(setq default-directory "~/work/")




;;===============================================================
;;外观设置
;;===============================================================
;; 去掉滚动条
(set-scroll-bar-mode nil)
;;关闭开启画面
(setq inhibit-startup-message t)
;;禁用工具栏
(tool-bar-mode nil)
;;禁用菜单栏
;;(menu-bar-mode nil)



;;===============================================================
;;其他设置
;;===============================================================

;;-------------ibuffer,查看bufer
(require 'ibuffer)
(global-set-key ( kbd "C-x C-b")' ibuffer)

;;自动重载更改的文件
(global-auto-revert-mode 1)
;;custome的风格改为单一的树状风格
(setq custom-buffer-style 'brackets)


(ido-mode t)

(setq sentence-end "\\([。！？]\\|……\\|[.?!][]\"')}]*\\($\\|[ \t]\\)\\)[ \t\n]*")
(setq sentence-end-double-space nil)

;;可以递归的使用 minibuffer
(setq enable-recursive-minibuffers t)

;;防止页面滚动时跳动， scroll-margin 3 可以在靠近屏幕边沿3行时就开始滚动，可以很好的看到上下文
(setq scroll-margin 3  scroll-conservatively 10000)

;;设置缺省主模式是text，,并进入auto-fill次模式.而不是基本模式fundamental-mode
(setq default-major-mode 'text-mode)
(add-hook 'text-mode-hook 'turn-on-auto-fill)


;;允许emacs和外部其他程序的粘贴
(setq x-select-enable-clipboard t)

;;使用鼠标中键可以粘贴
(setq mouse-yank-at-point t)

;; 自动的在文件末增加一新行
(setq require-final-newline t)


;;Non-nil if Transient-Mark mode is enabled.
(setq-default transient-mark-mode t)

