set -e
# g++ -O3 -DLOCAL -fsanitize=address,undefined -std=c++20 A.cpp -o a
g++ -O3 -DLOCAL -std=c++20 A.cpp -o a
g++ -O3 -DLOCAL -std=c++20 ac.cpp -o c

for ((i = 0; ; i++)); do
	echo "case $i"
	python3 gen.py > inp
	time ./a < inp > wa.out
	time ./c < inp > ac.out 
    diff ac.out wa.out || break
done