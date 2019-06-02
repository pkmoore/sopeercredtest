all: server_givespeercred client_requestspeercred server_requestspeercred client_givespeercred

server_givespeercred: server_givespeercred.c
	gcc -std=c11 -o server_givespeercred server_givespeercred.c

client_requestspeercred: client_requestspeercred.c
	gcc -std=c11 -o client_requestspeercred client_requestspeercred.c

server_requestspeercred: server_requestspeercred.c
	gcc -std=c11 -o server_requestspeercred server_requestspeercred.c

client_givespeercred: client_givespeercred.c
	gcc -std=c11 -o client_givespeercred client_givespeercred.c

clean:
	- rm server_givespeercred
	- rm client_requestspeercred
	- rm server_requestspeercred
	- rm client_givespeercred
