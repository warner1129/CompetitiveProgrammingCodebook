set -e
g++ -O3 a.cpp -o a
g++ -O3 ac.cpp -o c
g++ -O3 gen.cpp -o g

for ((i=0;;i++))
do
	echo "case $i"
    ./g > inp
	time ./a < inp > wa.out
    time ./c < inp > ac.out
    diff ac.out wa.out || break
done