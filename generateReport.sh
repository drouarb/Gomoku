#!/usr/bin/env bash

find ./logs/ | sort > .tmp
mkdir html
mkdir html/logs

echo "<head>
    <title>Report</title>
</head>
<body>

<h1>All builds</h1>

" > report.html

while read file
do
    DEST="./html/$file.html"
    ./intepretor.out -i "$file" -o "$DEST"
    echo "<a href=\"$DEST\">$file</a><br>" >> report.html
done < .tmp

echo '</body>' >> report.html

cp report.html /home/public/

rm .tmp