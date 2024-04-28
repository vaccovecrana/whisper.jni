compile:
	cc \
		-I/home/jjzazuet/Applications/zulu17.42.21-ca-crac-jdk17.0.7-linux_x64/include \
		-I/home/jjzazuet/Applications/zulu17.42.21-ca-crac-jdk17.0.7-linux_x64/include/linux \
		-Wall -fPIC -c -o whisperjni.o whisperjni.c
	cc -std=c11 -fPIC -lstdc++ -shared -o libwhisperjni.so ggml.o ggml-alloc.o ggml-backend.o ggml-quants.o whisper.o whisperjni.o

clean:
	rm -rfv whisperjni.o libwhisperjni.so
