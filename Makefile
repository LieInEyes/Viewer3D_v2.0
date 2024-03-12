WASH=rm -rf *css *.html .clang-format man_ru *.tgz build build_test Testing ../MyViewer

OS=$(shell uname)
ifeq ($(OS), Linux)
	LEAKS=CK_FORK=no valgrind --leak-check=full --track-origins=yes -s build_test/test_model
else
	LEAKS=CK_FORK=no leaks --atExit -- build/test_model
endif

all: clean uninstall gcov_report install


install: uninstall build
	mkdir -p $(HOME)/Desktop/Viewer_v2_0
ifeq ($(OS), Linux)
	mv build/3DViewer_v2_0 $(HOME)/Desktop/Viewer_v2_0/
else
	mv build/3DViewer_v2_0.app $(HOME)/Desktop/Viewer_v2_0/
endif

uninstall:
	rm -rf $(HOME)/Desktop/Viewer_v2_0/

build:
	mkdir build
	cd build; cmake ..
	cmake --build build --target 3DViewer_v2_0


test: build_test
	cd build_test; ctest ..

build_test:
	mkdir build_test
	cd build_test; cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS_DEBUG="-g -fprofile-arcs -ftest-coverage"
	cmake --build build_test --target test_model

gcov_report: test
	gcovr -r .. --html --html-details -e="main.cc" -e="common" -e="front" -e="controller" -e="../build_test" -e="backend/common.*" -e="backend/model_settings.*" -o gcov_report.html
	open gcov_report.html


dvi:
	makeinfo --html --no-warn --no-validate --force src/man_ru.texi


dist:
	rm -rf MyViewer
	mkdir MyViewer
	cp -r src/* MyViewer
	tar -czvf ./MyViewer.tar.tgz MyViewer
	rm -rf MyViewer/


check_clang_format: backend/* controller/* front/*.h front/*.cc src/tests/test.cc main.cc
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n $^

clang_reformat: backend/* controller/* front/*.h front/*.cc src/tests/test.cc main.cc
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i $^


check_leaks:
	$(LEAKS)

check_cppcheck: backend/* controller/* front/*.h front/*.cc src/main/main.cc
	cppcheck --language=c++ --std=c++17 --enable=all --suppress=missingInclude --suppress=unusedStructMember --suppress=unusedFunction $^

clean:
	$(WASH)
