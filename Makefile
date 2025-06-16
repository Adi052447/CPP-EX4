#adi.gamzu@gmail.com
# =========================================
# קומפיילר ואופציות בסיס
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -g

# קבצי הפלט
EXEC      = main.out
TEST_EXEC = test.out

# יעד ברירת מחדל – בניית התכנית הראשית
default: $(EXEC)

# ----------  בנייה  ----------
$(EXEC): main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(TEST_EXEC): tests.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# ----------  הרצות  ----------
test: $(TEST_EXEC)
	./$(TEST_EXEC)

Main: $(EXEC)
	./$(EXEC)

valgrind: $(EXEC) $(TEST_EXEC)
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TEST_EXEC)

# ----------  ניקוי  ----------
clean:
	rm -f $(EXEC) $(TEST_EXEC)
	rm -rf *.dSYM

.PHONY: default test clean valgrind Main
