# Pthreads Programming
## Problem Statement
+ Suppose we toss darts randomly at a square dartboard, whose bullseye is at the origin, and
whose sides are two feet in length. Suppose also that there is a circle inscribed in the square
dartboard. The radius of the circle is one foot, and its area is π square feet. If the points that
are hit by the darts are uniformly distributed (and we always hit the square), then the number
of darts that hit inside the circle should approximately satisfy the equation<pre>number of tosses in circle / total number of tosses = π / 4</pre>since the ratio of the area of the circle to the area of the square is π/4.
This is called a “Monte Carlo” method, since it uses randomness (the dart tosses).   
+ Write a Pthreads program that uses a Monte Carlo method to estimate π. The main thread should
read in the total number of tosses and print the estimate.

## Usage
+ compile <pre>gcc -pthread -std=gnu99 -O2 -s pi.c -o pi</pre>
+ run <pre>./pi <core #> <tosses #></pre>


## Other
+ If you're interested in the efficiency with different core number, you can run the program using <pre>time ./pi <core #> <tosses #></pre> and compare the wallclock time.
