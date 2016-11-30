#!/usr/bin/env bash

RED="http://jenkins.navispeed.eu/static/0a3e7491/images/16x16/red.png"
BLUE="http://jenkins.navispeed.eu/static/0a3e7491/images/16x16/blue.png"

find ./logs/ | sort > .tmp
mkdir html
mkdir html/logs

echo "<head>
    <title>Report</title>
</head>
<body>

<h1>All builds</h1>

" > report.html

FAIL=0
SUCCESS=0

while read file
do
    DEST="./html/$file.html"
    ./intepretor.out -i "$file" -o "$DEST"
    filename=$(echo $file | cut -d '/' -f 3)

    if [ "$(cat $DEST | grep Error)" = "" ]
    then
       echo '<img src="'$BLUE'" alt="Succès > Sortie de console" tooltip="Succès > Sortie de console" style="width: 16px; height: 16px; " class="icon-blue icon-sm" title="Succès > Sortie de console">' >> report.html
           SUCCESS=$(($SUCCESS+1))
    else
       echo '<img src="'$RED'" alt="Succès > Sortie de console" tooltip="Succès > Sortie de console" style="width: 16px; height: 16px; " class="icon-blue icon-sm" title="Succès > Sortie de console">' >> report.html
       FAIL=$(($FAIL+1))
    fi

    echo "<a href=\"$DEST\">$filename</a><br>" >> report.html
done < .tmp

echo '</body>' >> report.html

cp report.html /home/public/

rm .tmp