;;; hebrew.el --- support for Hebrew -*- coding: iso-2022-7bit; no-byte-compile: t -*-

;; Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010
;;   Free Software Foundation, Inc.
;; Copyright (C) 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002, 2003, 2004,
;;   2005, 2006, 2007, 2008, 2009, 2010
;;   National Institute of Advanced Industrial Science and Technology (AIST)
;;   Registration Number H14PRO021

;; Copyright (C) 2003
;;   National Institute of Advanced Industrial Science and Technology (AIST)
;;   Registration Number H13PRO009

;; Keywords: multilingual, Hebrew

;; This file is part of GNU Emacs.

;; GNU Emacs is free software: you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation, either version 3 of the License, or
;; (at your option) any later version.

;; GNU Emacs is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; You should have received a copy of the GNU General Public License
;; along with GNU Emacs.  If not, see <http://www.gnu.org/licenses/>.

;;; Commentary:

;; For Hebrew, the character set ISO8859-8 is supported.
;; See http://www.ecma.ch/ecma1/STAND/ECMA-121.HTM.
;; Windows-1255 is also supported.

;;; Code:

(define-coding-system 'hebrew-iso-8bit
  "ISO 2022 based 8-bit encoding for Hebrew (MIME:ISO-8859-8)."
  :coding-type 'charset
  :mnemonic ?8
  :charset-list '(iso-8859-8)
  :mime-charset 'iso-8859-8)

(define-coding-system-alias 'iso-8859-8 'hebrew-iso-8bit)

;; These are for Explicit and Implicit directionality information, as
;; defined in RFC 1556.  We don't yet support directional information
;; in bidi languages, so these aliases are a lie, especially as far as
;; iso-8859-8-e is concerned.  FIXME.
(define-coding-system-alias 'iso-8859-8-e 'hebrew-iso-8bit)
(define-coding-system-alias 'iso-8859-8-i 'hebrew-iso-8bit)

(set-language-info-alist
 "Hebrew" '((charset iso-8859-8)
	    (coding-priority hebrew-iso-8bit)
	    (coding-system hebrew-iso-8bit windows-1255 cp862)
	    (nonascii-translation . iso-8859-8)
	    (input-method . "hebrew")
	    (unibyte-display . hebrew-iso-8bit)
	    (sample-text . "Hebrew	,Hylem(B")
	    (documentation . "Right-to-left writing is not yet supported.")))

(set-language-info-alist
 "Windows-1255" '((coding-priority windows-1255)
		  (coding-system windows-1255)
		  (documentation . "\
Support for Windows-1255 encoding, e.g. for Yiddish.
Right-to-left writing is not yet supported.")))

(define-coding-system 'windows-1255
  "windows-1255 (Hebrew) encoding (MIME: WINDOWS-1255)"
  :coding-type 'charset
  :mnemonic ?h
  :charset-list '(windows-1255)
  :mime-charset 'windows-1255)
(define-coding-system-alias 'cp1255 'windows-1255)

(define-coding-system 'cp862
  "DOS codepage 862 (Hebrew)"
  :coding-type 'charset
  :mnemonic ?D
  :charset-list '(cp862)
  :mime-charset 'cp862)
(define-coding-system-alias 'ibm862 'cp862)

(provide 'hebrew)

;; arch-tag: 3ca04f32-3f1e-498e-af46-8267498ba5d9
;;; hebrew.el ends here
