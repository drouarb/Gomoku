#!/usr/bin/env bash

find ./logs/ > .tmp
mkdir html
mkdir html/logs

echo "<head>
    <title>Report</title>
</head>
<body>

<h1>Build failed</h1>

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