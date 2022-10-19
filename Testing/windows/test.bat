g++ a.cpp -o a
g++ brute.cpp -o brute
g++ gen.cpp -o gen

@echo off
for /l %%x in (1, 1, 1000) do (
    echo %%x
    gen %%x > input.in
    a < input.in > output.out 
    brute < input.in > output2.out
    fc output.out output2.out > diagnostics || exit /b
)

echo all tests passed
