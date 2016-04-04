(defun make-cd (a b c d)
		 (list :Title a :Artist b :Rating c :Ripped d))

(defvar *db* nil)

(defun add-record (cd)
  (push cd *db*))

(defun dump-db()
  (format t "~{~{~a: ~10t~a~%~}~%}" *db*))

(defun prompt-read (prompt)
  (format *query-io* "~a: " prompt)
  (force-output *query-io* )
  (read-line *query-io*))

(defun prompt-for-cd ()
  (make-cd
   (prompt-read "Title")
   (prompt-read "Artist")
   (or (parse-integer(prompt-read "Rating") :junk-allowed t) 0)
   (y-or-n-p "Ripped [y/n] : " )))

(defun add-cds()
  (loop (add-record (prompt-for-cd))
	 (if (not (y-or-n-p "Another ? [y/n] : ")) (return ))))

;;This is for saving the dababase .
(defun save-db (filename)
  (with-open-file (out filename
					   :direction :output
					   :if-exists :supersede)
	(with-standard-io-syntax
	  (print *db* out))))

;;This is load the database .
(defun load-db (filename)
  (with-open-file (in filename)
	(with-standard-io-syntax
	  (setf *db* (read in)))))

(remove-if-not #'evenp '(1 2 3 4 5 6 7 8 9 10))

										;or we can do it .
(remove-if-not #'(lambda (x) (= 0 (mod x 2))) '(1 2 3 4 5 6 7 8 9 10))

;;So , we can write as next .

(remove-if-not
 #'(lambda (cd) (equal (getf cd :artist) "Dixie Chicks")) *db*)
((:TITLE "Home" :ARTIST 
