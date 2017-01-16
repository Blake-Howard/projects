#lang racket
;(require "a1-student-tests.rkt")
;(test-file #:file-name "a1.rkt")

(define test
  (lambda (x y)
    (cond
      [(equal? x y) 'PASSED]
      [else
       'FAILED])))

(define countdown
  (lambda(x)
    (cond
      [(zero? x) 0]
      [else
        (cons x (countdown (sub1 x)))])))

;(test (countdown 5) '(5 4 3 2 1 . 0))

(define insertR
  (lambda (x y lst)
    (cond
      [(empty? lst) lst]
      [(eqv? (car lst) x) (cons (car lst) (cons y (insertR x y (cdr lst))))]
      [else
       (cons (car lst) (insertR x y (cdr lst)))])))

;(test (insertR 'x 'y '(x z z x y x)) '(x y z z x y y x y))

(define remv-1st
  (lambda (x lst)
    (cond
      [(empty? (cdr lst)) lst]
      [(eqv? (car lst) x) (cdr lst)]
      [else
       (cons (car lst) (remv-1st x (cdr lst)))])))

;(test (remv-1st 'x '(x y z x)) '(y z x))

(define count-?s
  (lambda (lst)
      (cond
        [(null? lst) 0]
        [(eqv? '? (car lst)) (+ 1 (count-?s (cdr lst)))]
        [else
         (count-?s (cdr lst))])))

;(test (count-?s '(? y z ? ?)) 3)

(define filter
  (lambda (x lst)
    (cond
      [(null? lst) lst]
      [(x (car lst)) (cons (car lst) (filter x (cdr lst)))]
      [else
       (filter x (cdr lst))])))

;(test (filter even? '(1 2 3 4 5 6)) '(2 4 6))

(define zip
  (lambda (lst1 lst2)
    (cond
      [(empty? lst1) lst1]
      [(empty? lst2) lst2]
      [else
       (cons (cons (car lst1) (car lst2)) (zip (cdr lst1) (cdr lst2)))])))

;(test (zip '(1 2 3) '(a b c)) '((1 . a) (2 . b) (3 . c)))

(define map
  (lambda (pro lst)
    (cond
      [(null? lst) lst]
      [else
       (cons (pro (car lst)) (map pro (cdr lst)))])))

;(test (map add1 '(1 2 3 4)) '(2 3 4 5))

(define append
  (lambda (lst1 lst2)
    (cond
      [(null? lst2) lst2]
      [(null? lst1) (cons (car lst2) (append lst1 (cdr lst2)))]
      [else
       (cons (car lst1) (append (cdr lst1) lst2))])))

;(test (append '(a b c) '(1 2 3)) '(a b c 1 2 3))

;(define reverse
 ; (lambda (lst)
  ;  (define reverse2
   ;   (lambda (x lst)
    ;    (cond
     ;;     [(null? lst) (cons x lst)(cons (car lst) (reverse2 x (cdr lst)))]
       ;   [else
           
    

;(test (reverse '(a 3 x)) '(x 3 a))

(define fact
  (lambda (x)
    (cond
      [(zero? x) 1]
      [else
       (* x (fact (sub1 x)))])))

;(test (fact 5) 120)

(define member-?*
  (lambda (lst)
    (cond
      [(null? lst
        
