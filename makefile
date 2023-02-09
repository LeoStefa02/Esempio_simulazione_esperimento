LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

main: main.cpp ./FunzioniUtili/funzioni.h EspLambdaSodio.h
	g++ main.cpp EspLambdaSodio.cpp -o main ${LIBS} ${INCS} -I/home/leonardo/anaconda3/envs/dev/include/