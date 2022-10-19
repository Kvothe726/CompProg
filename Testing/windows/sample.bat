g++ a.cpp -o a

@echo off
for /l %%x in (1, 1, 1000) do (
    echo %%x
    gen %%x > input.in
    a < input.in > output.out 
)

echo all tests passed
:End