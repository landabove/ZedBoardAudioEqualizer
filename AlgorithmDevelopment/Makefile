CC=gcc
CFLAGS=-I. -I./kiss_fft130 -I./kiss_fft130/tools -lsndfile -ggdb
DEPS = kiss_fft.h audioTestbench.h frequencyScaling.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

equalizer: audioTestbench.o frequencyScaling.o kiss_fft.o
	gcc -o equalizer audioTestbench.o frequencyScaling.o kiss_fft.o -I. -Ikiss_fft130 -lsndfile -lm -ggdb
