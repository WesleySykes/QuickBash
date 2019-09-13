srun: qbash.c
	gcc `pkg-config --cflags gtk+-3.0` qbash.c `pkg-config --libs gtk+-3.0` -o qbash

clean:
	rm qbash
