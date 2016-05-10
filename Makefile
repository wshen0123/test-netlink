EXE=test_netlink_userspace
SRC=test_netlink_userspace.c
OBJ=$(SRC:.c=.o)

.PHONY: clean

all: $(SRC) $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $@

.c.o:
	$(CC) $< -o $@

clean:
	$(RM) $(OBJ) $(EXE)
