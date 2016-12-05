//
// Created by drouar_b on 11/25/16.
//

#ifndef GOMOKU_STOPWATCH_HH
#define GOMOKU_STOPWATCH_HH

# include <sys/time.h>
# include <time.h>

class Stopwatch {
public:
    Stopwatch();
    ~Stopwatch();

    void set();
    long elapsedMs();
    long elapsedUs();

private:
    struct timeval startTime;
};

#endif //GOMOKU_STOPWATCH_HH
