#!/bin/bash
#echo "const gchar *ifast_gui = \"$(cat $1 | sed '{:q;N;s/\n/ /g;t q}' | sed 's/\"/\\\"/g') \";" > $2
echo "static const gchar *$1 = \"$(cat $2 | sed ':a;N;$!ba;s/\n/\\\n/g' | sed 's/\"/\\\"/g') \";" > $3
