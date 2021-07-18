g++ brute.cpp -o brute
g++ gen.cpp -o gen

for((i = 1; i<=50 ; ++i)); do
    #echo $i
    ./gen $i > intx
    ./brute < intx
done