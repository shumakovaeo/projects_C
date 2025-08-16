#!/bin/bash
echo 'log file_name'
read file

count=$(wc -l "$file")

echo '1: '"$count"

exit 0
