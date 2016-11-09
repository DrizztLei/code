(defun myserver()
	(start (make-instance 'easy-acceptor :port 8080))
	(define-easy-handler (greet :uri "/hello")()
		(format nil "<html><body><h1>HELLO LISP SERVER !</h1></body></html>")))
