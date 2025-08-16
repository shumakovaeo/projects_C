#!/bin/bash
echo 'file_name fro change'
read file
echo 'string_old'
read str1
echo 'string_new'
read str2

#if [ $file -eq "" ] || [ $str1 -eq "" ] || [ $str -eq "" ];
#then
#    echo "no string"
#    exit 0
#else
#    echo "+"
#fi

#if [ !-f $file ]; then echo "no file" exit 0 fi


t=$(stat --format="%z" "$file")
s=$(stat --format="%s" "$file")
#t=$(date -r "$file" +"%Y-%m-%d %H:%M")
#n=$(stat --format="%n" "$file")

#sh=$(sha256sum -t "$file")
sh=$(shasum -a 256 "$file")

echo 'src/'"$file"' - '"$s"' - '"$t"' - '"$sh"' - sha256' >> files.log


echo 'done'
exit 0
