.PHONY: testASM

fourth: 4_grade.c
	gcc 4_grade.c -o fourth

fifth: 5_grade.c
	gcc 5_grade.c -o fifth


test_fourth: fourth
	./fourth Tests/Test8.txt Tests/Test8_output.txt
	./fourth Tests/Test2.txt Tests/Test2_output.txt
	./fourth Tests/Test3.txt Tests/Test3_output.txt
	./fourth Tests/Test4.txt Tests/Test4_output.txt
	./fourth Tests/Test5.txt Tests/Test5_output.txt
	./fourth Tests/Test6.txt Tests/Test6_output.txt
	./fourth Tests/Test7.txt Tests/Test7_output.txt
	./fourth Tests/Test1.txt Tests/Test1_output.txt

test_fifth: fifth
	./fifth Tests/Test8.txt Tests/Test8_output.txt
	./fifth Tests/Test2.txt Tests/Test2_output.txt
	./fifth Tests/Test3.txt Tests/Test3_output.txt
	./fifth Tests/Test4.txt Tests/Test4_output.txt
	./fifth Tests/Test5.txt Tests/Test5_output.txt
	./fifth Tests/Test6.txt Tests/Test6_output.txt
	./fifth Tests/Test7.txt Tests/Test7_output.txt
	./fifth Tests/Test1.txt Tests/Test1_output.txt
	rm read.fifo write.fifo 