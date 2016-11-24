#!/usr/bin/env bash

find ./logs/ > .tmp
mkdir html
mkdir html/logs

echo "<head>
    <title>Report</title>
</head>
<body>
" > report.html

while read file
do
    DEST="./html/$file.html"
    ./intepretor -i "$file" -o "$DEST"
    echo "<a href=\"$DEST\">$file</a>" >> report.html
done < .tmp

echo '</body>' >> report.html

cp report.html /home/public/

rm .tmp