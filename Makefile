

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

ninth: 9_grade/9_grade_first.c 9_grade/9_grade_second.c
	gcc 9_grade/9_grade_first.c -o ninth_first
	gcc 9_grade/9_grade_second.c -o ninth_second

delete_fifo:
	rm read.fifo write.fifo

delete_eigth:
	rm eigth_first eigth_second

delete_ninth:
	rm ninth_first ninth_second

test_fourth: fourth
	./test.sh fourth Tests/Test8.txt Tests/Test8_output.txt
	./test.sh fourth Tests/Test2.txt Tests/Test2_output.txt
	./test.sh fourth Tests/Test3.txt Tests/Test3_output.txt
	./test.sh fourth Tests/Test4.txt Tests/Test4_output.txt
	./test.sh fourth Tests/Test5.txt Tests/Test5_output.txt
	./test.sh fourth Tests/Test6.txt Tests/Test6_output.txt
	./test.sh fourth Tests/Test7.txt Tests/Test7_output.txt
	./test.sh fourth Tests/Test1.txt Tests/Test1_output.txt
	rm fourth

test_fifth: fifth
	./test.sh fifth Tests/Test8.txt Tests/Test8_output.txt
	./test.sh fifth Tests/Test2.txt Tests/Test2_output.txt
	./test.sh fifth Tests/Test3.txt Tests/Test3_output.txt
	./test.sh fifth Tests/Test4.txt Tests/Test4_output.txt
	./test.sh fifth Tests/Test5.txt Tests/Test5_output.txt
	./test.sh fifth Tests/Test6.txt Tests/Test6_output.txt
	./test.sh fifth Tests/Test7.txt Tests/Test7_output.txt
	./test.sh fifth Tests/Test1.txt Tests/Test1_output.txt
	rm read.fifo write.fifo fifth

test_sixth: sixth
	./test.sh sixth Tests/Test1.txt Tests/Test1_output.txt
	./test.sh sixth Tests/Test8.txt Tests/Test8_output.txt
	./test.sh sixth Tests/Test2.txt Tests/Test2_output.txt
	./test.sh sixth Tests/Test3.txt Tests/Test3_output.txt
	./test.sh sixth Tests/Test4.txt Tests/Test4_output.txt
	./test.sh sixth Tests/Test5.txt Tests/Test5_output.txt
	./test.sh sixth Tests/Test6.txt Tests/Test6_output.txt
	./test.sh sixth Tests/Test7.txt Tests/Test7_output.txt
	rm sixth

test_seventh: seventh
	./test.sh seventh Tests/Test8.txt Tests/Test8_output.txt
	./test.sh seventh Tests/Test2.txt Tests/Test2_output.txt
	./test.sh seventh Tests/Test3.txt Tests/Test3_output.txt
	./test.sh seventh Tests/Test4.txt Tests/Test4_output.txt
	./test.sh seventh Tests/Test5.txt Tests/Test5_output.txt
	./test.sh seventh Tests/Test6.txt Tests/Test6_output.txt
	./test.sh seventh Tests/Test7.txt Tests/Test7_output.txt
	./test.sh seventh Tests/Test1.txt Tests/Test1_output.txt
	rm read.fifo write.fifo seventh

