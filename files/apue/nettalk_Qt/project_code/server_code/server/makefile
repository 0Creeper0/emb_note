LDFLAGS+=-lsqlite3

regserver:regserver.c
	gcc -o $@ $^ $(LDFLAGS)

loginserver:loginserver.c
	gcc -o $@ $^ $(LDFLAGS)

chatserver:chatserver.c
	gcc -o $@ $^ $(LDFLAGS)

clean:
	rm regserver loginserver chatserver
