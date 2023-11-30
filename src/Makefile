CXX							= g++
CXXFLAGS				= -std=c++17 -Wall -Wextra -Werror -fsanitize=address,undefined -I .
LDFLAGS					= -lgtest_main -lgtest -lpthread 
VALGRIND_FLAGS	= --log-file="valgrind.txt" --track-origins=yes --trace-children=yes --leak-check=full --leak-resolution=med
GCOVFLAGS 			= -fprofile-arcs -ftest-coverage

SRC_DIR 				= containers/
SRC_TEST_DIR		= tests/

SRC_LIB					= $(wildcard $(SRC_DIR)*.h) *.h
SRC_TEST				= $(wildcard $(SRC_TEST_DIR)*.cc)


all: clean test

test:
	$(CXX) $(CXXFLAGS) $(SRC_TEST) -o test $(LDFLAGS)
	./test

rebuild: clean all

gcovr_report: clean
	$(CXX) $(CXXFLAGS) $(SRC_TEST) -o test $(LDFLAGS) $(GCOVFLAGS)
	./test
	mkdir gcovr/
	gcovr --html-details gcovr/report.details.html
	rm -rf ./*.gc*
	open gcovr/report.details.html

clean:
	@rm -rf test
	@rm -rf gcovr
	@rm -rf report
	@rm -rf *.info
	@rm -rf ./*.gc*
	@rm -rf *.txt
	@rm -rf *.dSYM

fmt:
	@clang-format -i --style=Google $(SRC_LIB)
	
stylecheck:
	@clang-format -n --style=Google $(SRC_LIB)
	@cpplint --filter=-legal/copyright,-build/header_guard,-runtime/references $(SRC_LIB)

