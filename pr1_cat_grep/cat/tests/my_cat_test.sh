#!/bin/bash

SUCCESS=0
FAIL=0

TEST_FILE_1="tests/bytes.txt"
TEST_FILE_2="tests/bytes.txt tests/test_case_cat.txt"


test() {
  local test_params="$1"
  echo "TEST: $test_params"
  ./s21_cat $test_params >s21_cat.txt
  cat $test_params >cat.txt
  if diff -q s21_cat.txt cat.txt >/dev/null; then
    ((SUCCESS++))
  else
    echo "$test_params" 
    ((FAIL++))
  fi
  rm -f cat.txt s21_cat.txt
}

for var in -b -e -E -n -s -t -T -v --number-nonblank --number --squeeze-blank; do
  TEST1="$var $TEST_FILE_1"
  test "$TEST1"
done

for var in -b -e -E -n -s -t -T -v --number-nonblank --number --squeeze-blank; do
  TEST2="$var $TEST_FILE_2"
  test "$TEST2"
done


echo "Успех: $SUCCESS"
echo "Провал: $FAIL"

exit "$FAIL"