/**
 * Created by greg on 21/11/2016.
 */

var c = document.getElementById("myCanvas");
var ctx = c.getContext("2d");
var toto = 7;


const numbershift = 45;


function put(x, y, color) {
//    ctx.rect(,  - 20, 40, 40);
    ctx.fillStyle = color;
    ctx.borderStyle = color;
    ctx.beginPath();
    ctx.arc(x * numbershift, y * numbershift, 20, 0, 2 * Math.PI);
    ctx.fill();
    ctx.stroke();
    ctx.fillStyle = 'black';
}

function e() {
    ctx.clearRect(0, 0, 2000, 2000);

    for (var j = 0; j < 19; ++j) {
        ctx.moveTo(j * numbershift, 0);
        ctx.lineTo(j * numbershift, 1900);
        ctx.stroke();
    }

    for (var j = 0; j < 19; ++j) {
        ctx.moveTo(0, j * numbershift);
        ctx.lineTo(1900, j * numbershift);
        ctx.stroke();
    }
    for (var y = 0; y < 19; y++) {
        for (var x = 0; x < 19; x++) {
            if (game[toto].map[y][x] != 0) {
                put(x, y, (game[toto].map[y][x] == 1 ? 'black' : 'white'));
            }
        }
    }
    ctx.fill();
    return;
}

e();
