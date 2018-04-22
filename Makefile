OBJS 	= main.o search.o
SOURCE	= main.c search.c
HEADER  = search.h hash.h oracle.h
OUT  	= invoke-oracle
CC	= gcc
FLAGS   = -g -c 
# -g option enables debugging mode 
# -c flag generates object code for separate files

all: $(OBJS)
	$(CC) -g $(OBJS) -L . -loracle -lhash -static -o $(OUT) 

# create/compile the individual files >>separately<< 
main.o: main.c
	$(CC) $(FLAGS) main.c

tree.o: search.c
	$(CC) $(FLAGS) search.c


# clean house
clean:
	rm -f $(OBJS) $(OUT)

# do a bit of accounting
count:
	wc $(SOURCE) $(HEADER)
