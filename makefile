all: server_givespeercred client_requestspeercred

server_givespeercred: server_givespeercred.c
	gcc -std=c11 -o server_givespeercred server_givespeercred.c

client_requestspeercred: client_requestspeercred.c
	gcc -std=c11 -o client_requestspeercred client_requestspeercred.c

clean:
	- rm server_givespeercred
	- rm client_requestspeercred
