CC = gcc
CFLAGS = -ansi -Wall -pedantic
OBJS = assembler.o preproc.o first_pass.o second_pass.o util.o lexer.o table.o code_conversion.o handle_text.o Errors.o
HEADERS = globals.h preproc.h first_pass.h second_pass.h util.h lexer.h table.h code_conversion.h handle_text.h Errors.h data_strct.h

assembler: $(OBJS)
	$(CC) $(CFLAGS) -o assembler $(OBJS)

assembler.o: assembler.c $(HEADERS)
	$(CC) $(CFLAGS) -c assembler.c

preproc.o: preproc.c preproc.h util.h globals.h
	$(CC) $(CFLAGS) -c preproc.c

first_pass.o: first_pass.c first_pass.h table.h lexer.h handle_text.h globals.h Errors.h
	$(CC) $(CFLAGS) -c first_pass.c

second_pass.o: second_pass.c second_pass.h table.h lexer.h handle_text.h globals.h Errors.h code_conversion.h util.h
	$(CC) $(CFLAGS) -c second_pass.c

util.o: util.c util.h globals.h
	$(CC) $(CFLAGS) -c util.c

lexer.o: lexer.c lexer.h globals.h
	$(CC) $(CFLAGS) -c lexer.c

table.o: table.c table.h globals.h util.h
	$(CC) $(CFLAGS) -c table.c

code_conversion.o: code_conversion.c code_conversion.h lexer.h
	$(CC) $(CFLAGS) -c code_conversion.c

handle_text.o: handle_text.c handle_text.h
	$(CC) $(CFLAGS) -c handle_text.c

Errors.o: Errors.c Errors.h globals.h
	$(CC) $(CFLAGS) -c Errors.c

clean:
	rm -f *.o assembler *.ob *.ent *.ext *.am

