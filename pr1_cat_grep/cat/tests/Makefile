SHELL := /bin/bash

FILE=t1.txt test_1_cat.txt test_2_cat.txt

test:
	-diff <(./../s21_cat $(FILE)) <(cat $(FILE))
	-diff <(./../s21_cat -e $(FILE)) <(cat -e $(FILE))
	-diff <(./../s21_cat -t $(FILE)) <(cat -t $(FILE))
	-diff <(./../s21_cat -s $(FILE)) <(cat -s $(FILE))
	-diff <(./../s21_cat --squeeze-blank $(FILE)) <(cat --squeeze-blank $(FILE))
	-diff <(./../s21_cat -n $(FILE)) <(cat -n $(FILE))
	-diff <(./../s21_cat --number $(FILE)) <(cat --number $(FILE))
	-diff <(./../s21_cat -b $(FILE)) <(cat -b $(FILE))
	-diff <(./../s21_cat --number-nonblank $(FILE)) <(cat -b $(FILE))
	-diff <(./../s21_cat -etsnb $(FILE)) <(cat -etsnb $(FILE))
	-diff <(./../s21_cat -v $(FILE)) <(cat -v $(FILE))
