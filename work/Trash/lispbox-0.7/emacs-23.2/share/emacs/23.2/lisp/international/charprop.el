;; Copyright (C) 1991-2009 Unicode, Inc.
;; This file was generated from the Unicode data file at
;; http://www.unicode.org/Public/UNIDATA/UnicodeData.txt.
;; See lisp/international/README for the copyright and permission notice.

;; FILE: uni-name.el
(define-char-code-property 'name "uni-name.el"
  "Unicode character name.
Property value is a string.")
;; FILE: uni-category.el
(define-char-code-property 'general-category "uni-category.el"
  "Unicode general category.
Property value is one of the following symbols:
  Lu, Ll, Lt, Lm, Lo, Mn, Mc, Me, Nd, Nl, No, Pc, Pd, Ps, Pe, Pi, Pf, Po,
  Sm, Sc, Sk, So, Zs, Zl, Zp, Cc, Cf, Cs, Co, Cn")
;; FILE: uni-combining.el
(define-char-code-property 'canonical-combining-class "uni-combining.el"
  "Unicode canonical combining class.
Property value is an integer.")
;; FILE: uni-bidi.el
(define-char-code-property 'bidi-class "uni-bidi.el"
  "Unicode bidi class.
Property value is one of the following symbols:
  L, LRE, LRO, R, AL, RLE, RLO, PDF, EN, ES, ET,
  AN, CS, NSM, BN, B, S, WS, ON")
;; FILE: uni-decomposition.el
(define-char-code-property 'decomposition "uni-decomposition.el"
  "Unicode decomposition mapping.
Property value is a list of characters.  The first element may be
one of these symbols representing compatibility formatting tag:
  font, noBreak, initial, medial, final, isolated, circle, super,
  sub, vertical, wide, narrow, small, square, fraction, compat")
;; FILE: uni-decimal.el
(define-char-code-property 'decimal-digit-value "uni-decimal.el"
  "Unicode numeric value (decimal digit).
Property value is an integer.")
;; FILE: uni-digit.el
(define-char-code-property 'digit-value "uni-digit.el"
  "Unicode numeric value (digit).
Property value is an integer.")
;; FILE: uni-numeric.el
(define-char-code-property 'numeric-value "uni-numeric.el"
  "Unicode numeric value (numeric).
Property value is an integer or a floating point.")
;; FILE: uni-mirrored.el
(define-char-code-property 'mirrored "uni-mirrored.el"
  "Unicode bidi mirrored flag.
Property value is a symbol `Y' or `N'.")
;; FILE: uni-old-name.el
(define-char-code-property 'old-name "uni-old-name.el"
  "Unicode old names as published in Unicode 1.0.
Property value is a string.")
;; FILE: uni-comment.el
(define-char-code-property 'iso-10646-comment "uni-comment.el"
  "Unicode ISO 10646 comment.
Property value is a string.")
;; FILE: uni-uppercase.el
(define-char-code-property 'uppercase "uni-uppercase.el"
  "Unicode simple uppercase mapping.
Property value is a character.")
;; FILE: uni-lowercase.el
(define-char-code-property 'lowercase "uni-lowercase.el"
  "Unicode simple lowercase mapping.
Property value is a character.")
;; FILE: uni-titlecase.el
(define-char-code-property 'titlecase "uni-titlecase.el"
  "Unicode simple titlecase mapping.
Property value is a character.")
;; Local Variables:
;; coding: utf-8
;; no-byte-compile: t
;; End:

;; charprop.el ends here
