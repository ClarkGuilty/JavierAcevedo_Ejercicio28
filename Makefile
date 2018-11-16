all:
	mpicc integra.c -o integra.x
	mpirun -np 4 ./integra.x 1000000
