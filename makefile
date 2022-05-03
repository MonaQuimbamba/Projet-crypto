EXECS=pivotGauss
GCC?=gcc

all: ${EXECS}

pivotGauss: pivotGauss.c
	${GCC} -o pivotGauss -Wall pivotGauss.c -lm


clean:
	rm -f ${EXECS}
