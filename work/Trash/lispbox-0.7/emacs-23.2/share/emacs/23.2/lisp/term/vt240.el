;; -*- no-byte-compile: t -*-
;; For our purposes we can treat the vt200 and vt100 almost alike.
;; Most differences are handled by the termcap entry.
(defun terminal-init-vt240 ()
  "Terminal initialization function for vt240."
  (tty-run-terminal-initialization (selected-frame) "vt100")
  ;; Make F11 an escape key.
  (define-key input-decode-map "\e[23~" [f11]) ;Probably redundant.
  (define-key local-function-key-map [f11] [?\e]))

;; arch-tag: d9f88e9c-02dc-49ff-871c-a415f08e4eb7
;;; vt240.el ends here
