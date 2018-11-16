mpicc integra.c -o integra.x -lm
touch rta.txt && rm rta.txt
for N in 2 3 4 5 6 7 8
do
	satan=$((10**$N))
	mpirun -np 8 ./integra.x $satan > sol
	echo $N > potencias
	paste -d' ' potencias sol >> rta.txt
#Decidí no guardar muchos archivos porque simplemente no es necesario.
done
cat rta.txt
rm potencias sol integra.x

