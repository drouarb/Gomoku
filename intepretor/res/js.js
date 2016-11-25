/**
 * Created by greg on 21/11/2016.
 */

var c = document.getElementById("myCanvas");
var c_pattern = document.getElementById("patternCanvas");
var ctx = c.getContext("2d");
var ctx_pattern = c_pattern.getContext("2d");
var toto = 1;
var log = document.getElementById("log");


const numbershift = 37;


function put(ctx, x, y, color) {
//    ctx.rect(,  - 20, 40, 40);
    ctx.lineWidth = 1;
    ctx.strokeStyle = '#000000';
    ctx.fillStyle = color;
    ctx.borderStyle = color;
    ctx.beginPath();
    ctx.arc(x * numbershift, y * numbershift, 15, 0, 2 * Math.PI);
    ctx.fill();
    ctx.stroke();
    ctx.fillStyle = 'black';
}

function e(ctx) {
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

    ctx.fill();
    log.innerHTML = "";
    var r = "";
    for (var i = 0; i < game[toto].log.length; ++i) {
        r += game[toto].log[i] + "<br>";
    }
    log.innerHTML = r;
    return;
}

function fill(ctx) {
    for (var y = 0; y < 19; y++) {
        for (var x = 0; x < 19; x++) {
            if (game[toto].map[y][x] != 0) {
                put(ctx, x, y, (game[toto].map[y][x] == 1 ? 'black' : 'white'));
            }
        }
    }
}

function fillPattern(ctx) {

    var c = false;

    if (toto == 0) {
        return;
    }

    if (toto > 0) {
        toto--;
        c = true;
    }

    function getPos(startPos) {
        var y = parseInt(startPos / 21 - 1);
        var x = parseInt(startPos % 21 + 1);
        return {y: y, x: x};
    }

    function getNextPos(current, dir) {
        if (dir < 0) {
            throw "problem dir = " + dir;
        }
        switch (dir) {
            case 1:
                return {y: current.y, x: current.x + 1};
            case 21:
                return {y: current.y + 1, x: current.x};
            case 20:
                return {y: current.y + 1, x: current.x - 1};
            case 22:
                return {y: current.y + 1, x: current.x + 1};
        }
        if (dir < 0) {
            throw "problem dir = " + dir;
        }
    }


    function generatePos(pattern) {
        var res = [];
        var pos = getPos(pattern.startPos);
        for (var i = 0; i < pattern.length; ++i) {
            var c = pattern.line.charAt(i);
            var color;
            if (c == '0') {
                color = 'red'
            }
            if (c == '1') {
                color = 'black';
            }
            if (c == '2') {
                color = 'white';
            }
            res.push({x: pos.x, y: pos.y, color: color});
            pos = getNextPos(pos, pattern.dir);
        }
        console.log(res);
        return res;
    }

    var turn = game[toto].patterns;

    for (var i = 0; i < turn.length - 1; ++i) {
        ctx.strokeStyle = '#000000';
        console.log("pattern[" + i + "] : ", turn[i]);
        var res = generatePos(turn[i]);
        for (var j = 0; j < res.length; ++j) {
            ctx.strokeStyle = '#000000';
            put(ctx, res[j].x, res[j].y, res[j].color);
        }
        ctx.moveTo(res[0].x * (710 /19) - 3, res[0].y * (710 /19) - 3);
        ctx.lineTo(res[res.length - 1].x * (710 /19) - 3, res[res.length - 1].y * (710 /19) - 3);
        ctx.lineWidth = 3;
        //ctx.strokeStyle = '#ff0000';
        ctx.stroke();
        ctx.lineWidth = 1;
        ctx.strokeStyle = '#000000';
    }
    ctx.lineWidth = 1;
    ctx.strokeStyle = '#000000';

    if (c) {
        toto++;
    }

}

function load() {
    e(ctx);
    fill(ctx);
    e(ctx_pattern);
    fillPattern(ctx_pattern);
}

load();
