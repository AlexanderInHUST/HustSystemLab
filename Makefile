CXX		=	gcc
LOCK_S	= 	lock_operation.c
OBJ1	=	expr3
OBJ2	= 	read_buf
OBJ3	= 	write_buf

all:
	$(CXX) $(LOCK_S) $(OBJ1).c -o $(OBJ1)
	$(CXX) $(LOCK_S) $(OBJ2).c -o $(OBJ2)
	$(CXX) $(LOCK_S) $(OBJ3).c -o $(OBJ3)

clean:
	rm -rf $(OBJ1) $(OBJ2) $(OBJ3)
