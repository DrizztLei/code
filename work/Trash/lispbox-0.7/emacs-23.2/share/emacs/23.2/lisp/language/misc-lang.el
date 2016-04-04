;;; misc-lang.el --- support for miscellaneous languages (characters) -*- no-byte-compile: t -*-

;; Copyright (C) 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002, 2003, 2004,
;;   2005, 2006, 2007, 2008, 2009, 2010
;;   National Institute of Advanced Industrial Science and Technology (AIST)
;;   Registration Number H14PRO021

;; Keywords: multilingual, character set, coding system

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

;;; Code:

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; IPA (International Phonetic Alphabet)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(set-language-info-alist
 "IPA" '((charset . (ipa))
	 (coding-priority utf-8)
	 (coding-system utf-8)
	 (input-method . "ipa")
	 (nonascii-translation . ipa)
	 (documentation . "\
IPA is International Phonetic Alphabet for English, French, German
and Italian.")))

;; This is for Arabic.  But, as we still don't have Arabic language
;; support, we at least define a coding system here.

(define-coding-system 'iso-8859-6
  "ISO-8859-6 based encoding (MIME:ISO-8859-6)."
  :coding-type 'charset
  :mnemonic ?6
  :charset-list '(iso-8859-6)
  :mime-charset 'iso-8859-6)

(define-coding-system 'windows-1256
  "windows-1256 (Arabic) encoding (MIME: WINDOWS-1256)"
  :coding-type 'charset
  :mnemonic ?A
  :charset-list '(windows-1256)
  :mime-charset 'windows-1256)
(define-coding-system-alias 'cp1256 'windows-1256)

(provide 'misc-lang)

;; arch-tag: 6953585c-1a1a-4c09-be82-a2518afb6074
;;; misc-lang.el ends here
