.PHONY: testASM

fourth: 4_grade.c
	gcc 4_grade.c -o fourth

fifth: 5_grade.c
	gcc 5_grade.c -o fifth

sixth: 6_grade.c
	gcc 6_grade.c -o sixth

seventh: 7_grade.c
	gcc 7_grade.c -o seventh

eigth: 8_grade/8_grade_first.c 8_grade/8_grade_second.c
	gcc 8_grade/8_grade_first.c -o eigth_first
	gcc 8_grade/8_grade_second.c -o eigth_second

delete_fifo:
	rm read.fifo write.fifo

test_fourth: fourth
	./fourth Tests/Test8.txt Tests/Test8_output.txt
	./fourth Tests/Test2.txt Tests/Test2_output.txt
	./fourth Tests/Test3.txt Tests/Test3_output.txt
	./fourth Tests/Test4.txt Tests/Test4_output.txt
	./fourth Tests/Test5.txt Tests/Test5_output.txt
	./fourth Tests/Test6.txt Tests/Test6_output.txt
	./fourth Tests/Test7.txt Tests/Test7_output.txt
	./fourth Tests/Test1.txt Tests/Test1_output.txt
	rm fourth

test_fifth: fifth
	./fifth Tests/Test8.txt Tests/Test8_output.txt
	./fifth Tests/Test2.txt Tests/Test2_output.txt
	./fifth Tests/Test3.txt Tests/Test3_output.txt
	./fifth Tests/Test4.txt Tests/Test4_output.txt
	./fifth Tests/Test5.txt Tests/Test5_output.txt
	./fifth Tests/Test6.txt Tests/Test6_output.txt
	./fifth Tests/Test7.txt Tests/Test7_output.txt
	./fifth Tests/Test1.txt Tests/Test1_output.txt
	rm read.fifo write.fifo fifth

test_sixth: sixth
	./sixth Tests/Test8.txt Tests/Test8_output.txt
	./sixth Tests/Test2.txt Tests/Test2_output.txt
	./sixth Tests/Test3.txt Tests/Test3_output.txt
	./sixth Tests/Test4.txt Tests/Test4_output.txt
	./sixth Tests/Test5.txt Tests/Test5_output.txt
	./sixth Tests/Test6.txt Tests/Test6_output.txt
	./sixth Tests/Test7.txt Tests/Test7_output.txt
	./sixth Tests/Test1.txt Tests/Test1_output.txt
	rm sixth

test_seventh: seventh
	./seventh Tests/Test8.txt Tests/Test8_output.txt
	./seventh Tests/Test2.txt Tests/Test2_output.txt
	./seventh Tests/Test3.txt Tests/Test3_output.txt
	./seventh Tests/Test4.txt Tests/Test4_output.txt
	./seventh Tests/Test5.txt Tests/Test5_output.txt
	./seventh Tests/Test6.txt Tests/Test6_output.txt
	./seventh Tests/Test7.txt Tests/Test7_output.txt
	./seventh Tests/Test1.txt Tests/Test1_output.txt
	rm read.fifo write.fifo seventh

