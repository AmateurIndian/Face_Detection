#!/bin/bash

if [ -e prof_sequential.txt ]
then
    	rm Yusuf_Syed.output
	rm prof_sequential.txt
	rm prof_omp.txt
fi

touch prof_sequential.txt
touch prof_omp.txt
./compile.sh
echo
echo -ne "Executing serial code " 
echo "SEQUENTIAL PART" >> Yusuf_Syed.output
for i in 1 2 5 7 10; 
do
	echo -ne "="
	echo >> Yusuf_Syed.output
	echo "Results for k = ${i}" >> Yusuf_Syed.output
	./lbp_seq ${i} >> Yusuf_Syed.output
	echo >> prof_sequential.txt
	echo "Results for k = ${i}" >> prof_sequential.txt
	echo -ne "="
	gprof -b lbp_seq gmon.out >> prof_sequential.txt
done
echo ">Serial Execution Completed"
echo
echo -ne "Executing parallel code "
echo "=========================" >> Yusuf_Syed.output
echo "=========================" >> Yusuf_Syed.output
echo >> Yusuf_Syed.output
echo "PARALLEL PART" >> Yusuf_Syed.output
echo "NB: Value of k set to 10 for all runs" >> Yusuf_Syed.output
for i in 1 2 4 6 8 16;
do
	echo -ne "="
	echo >> Yusuf_Syed.output
	echo "Results for thread count = ${i}" >> Yusuf_Syed.output
	OMP_NUM_THREADS=${i} ./lbp_omp 10 >> Yusuf_Syed.output
	echo >> prof_omp.txt
	echo "Results for thread count = ${i}" >> prof_omp.txt
	echo -ne "="
	gprof -b lbp_omp gmon.out >> prof_omp.txt
done
echo ">Parallel Execution Completed"
