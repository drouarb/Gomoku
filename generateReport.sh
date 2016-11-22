#!/usr/bin/env bash

find ./logs/ > .tmp
mkdir html

echo "<head>
    <title>Report</title>
</head>
<body>
" > report.html

while read line
do
    DEST="./html/$file.html"
    ./interpretor -i "$file" -o "$DEST"
    echo "<a src=\"$DEST\"></a>" >> .report.html
done < .tmp

echo '</body>' > .report.html

rm .tmp