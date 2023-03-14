.PHONY: testASM

fourth: 4_grade.c
	gcc 4_grade.c -o main
fifth: 5_grade.c
	gcc 5_grade.c -o main

ReadWriteFile: main_with_parts/complete
	./main_with_parts/complete file InOutputFiles/input.txt  InOutputFiles/output.txt
	./main_with_parts/complete file InOutputFiles/input_sec.txt  InOutputFiles/output_sec.txt

test: main
	./main Tests/Test8.txt Tests/Test8_output.txt
	./main Tests/Test2.txt Tests/Test2_output.txt
	./main Tests/Test3.txt Tests/Test3_output.txt
	./main Tests/Test4.txt Tests/Test4_output.txt
	./main Tests/Test5.txt Tests/Test5_output.txt
	./main Tests/Test6.txt Tests/Test6_output.txt
	./main Tests/Test7.txt Tests/Test7_output.txt
	./main Tests/Test1.txt Tests/Test1_output.txt

testCfile: main_with_parts/complete
	./test.sh main_with_parts/complete Tests/Test1.txt Tests/Test1_output.txt
	./test.sh main_with_parts/complete Tests/Test2.txt Tests/Test2_output.txt
	./test.sh main_with_parts/complete Tests/Test3.txt Tests/Test3_output.txt
	./test.sh main_with_parts/complete Tests/Test4.txt Tests/Test4_output.txt
	./test.sh main_with_parts/complete Tests/Test5.txt Tests/Test5_output.txt
	./test.sh main_with_parts/complete Tests/Test6.txt Tests/Test6_output.txt
	./test.sh main_with_parts/complete Tests/Test7.txt Tests/Test7_output.txt
	./test.sh main_with_parts/complete Tests/Test8.txt Tests/Test8_output.txt

testAsm: main_without_optimize/main_without_Optimize
	./test.sh main_without_optimize/main_without_Optimize Tests/Test1.txt Tests/Test1_output.txt
	./test.sh main_without_optimize/main_without_Optimize Tests/Test2.txt Tests/Test2_output.txt
	./test.sh main_without_optimize/main_without_Optimize Tests/Test3.txt Tests/Test3_output.txt
	./test.sh main_without_optimize/main_without_Optimize Tests/Test4.txt Tests/Test4_output.txt
	./test.sh main_without_optimize/main_without_Optimize Tests/Test5.txt Tests/Test5_output.txt
	./test.sh main_without_optimize/main_without_Optimize Tests/Test6.txt Tests/Test6_output.txt
	./test.sh main_without_optimize/main_without_Optimize Tests/Test7.txt Tests/Test7_output.txt
	./test.sh main_without_optimize/main_without_Optimize Tests/Test8.txt Tests/Test8_output.txt