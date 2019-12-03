g++ a.cpp -o a
g++ brute.cpp -o brute
g++ gen.cpp -o gen

for((i = 1; ; ++i)); do
    echo $i
    ./gen $i > intx
    # ./a < int > out1
    # ./brute < int > out2
    # diff -w out1 out2 || break
    diff -w <(./a < intx) <(./brute < intx) || break
done
