CPPFLAGS = -std=c++20 -Wall -Wshadow -g -DLOCAL
run: $(R); time ./$(R)
%.in: $(R); time ./$(R) < $@
%.asan: %.cpp; $(CXX) $(CPPFLAGS) $< -o $@ -fsanitize=address,undefined
