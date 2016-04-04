 (setq prelude-theme nil)
;===========================================================
;;键绑定
;;===========================================================

;;============================================================
;;必备扩展
;;============================================================
;;-----------------redo
(global-set-key [f1] 'manual-entry)
(global-set-key [f2] 'info )

;;f3为查找字符串,f4关闭当前缓冲区
(global-set-key [f3] 'grep-find)

(global-set-key [f4] 'kill-this-buffer)

;;.emacs中设一个speedbar的快捷键
;(global-set-key [(f12)] 'speedbar-get-focus)
;;ctrl-f4,激活,ecb
;(global-set-key [C-f4] 'ecb-activate)


;;F5显示/隐藏工具栏 方便调试
(global-set-key [f5] 'tool-bar-mode)
;;ctrl-F5显示/隐藏菜单栏 ;; M-x menu-bar-open
(global-set-key [C-f5] 'menu-bar-mode)

(global-set-key [f6] 'gdb)
;;  C-f7, 设置编译命令; f7, 保存所有文件然后编译当前窗口文件
(defun du-onekey-compile ()
    "Save buffers and start compile"
      (interactive)
        (save-some-buffers t)
	  (switch-to-buffer-other-window "*compilation*")
	    (compile compile-command))
(setq-default compile-command "make ")
(global-set-key [M-f7] 'compile)
(global-set-key [f7] 'du-onekey-compile)
;;目的是开一个shell的小buffer，用于更方便地测试程序(也就是运行程序了)，>我经常会用到。
;;f8就是另开一个buffer然后打开shell，C-f8则是在当前的buffer打开shell,shift+f8清空eshell
(defun open-eshell-other-buffer ()
    "Open eshell in other buffer"
      (interactive)
        (split-window-vertically)
	  (eshell))
(defun my-eshell-clear-buffer ()
    "Eshell clear buffer."
      (interactive)
        (let ((eshell-buffer-maximum-lines 0))
	      (eshell-truncate-buffer)))
(global-set-key [(f8)] 'open-eshell-other-buffer)
;(global-set-key [C-f8] 'eshell)
(global-set-key [S-f8] 'my-eshell-clear-buffer)

;;设置[C-f9]为调用dired命令
;(global-set-key [C-f9] 'dired)
(global-set-key [f9] 'other-window);f9在其他窗口之间旋转
