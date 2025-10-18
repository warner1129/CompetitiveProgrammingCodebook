CPPFLAGS=-std=c++20 -Wall -Wshadow -g -DLOCAL
run: $(R) # set noet ai; retab!
	time ./$(R)
%.in: $(R)
	time ./$(R) < $@
%.asan: %.cpp
	$(CXX) $(CPPFLAGS) $< -o $@ -fsanitize=address 
