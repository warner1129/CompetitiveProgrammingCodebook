CPPFLAGS = -std=c++20 -Wall -Wshadow -g -DLOCAL
run:  $(R); time ./$(R)
%.in: $(R); time ./$(R) < $@
%.asan: %.cpp; $(CXX) $(CPPFLAGS) $< -o $@ -fsanitize=address,undefined
%.o2:   %.cpp; $(CXX) $(CPPFLAGS) $< -o $@ -O2 -ULOCAL
save: $(R); cp $(R).cpp s/$(R)-$(shell date +%T).cpp
