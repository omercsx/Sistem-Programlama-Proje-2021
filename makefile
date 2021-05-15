app:derle temizle

derle:
	gcc -I ./include/ -o ./lib/string_islem.o -c ./src/string_islem.c -w
	gcc -I ./libfdr/ -o ./lib/fields.o -c ./libfdr/fields.c -w
	gcc -I ./libfdr/ -o ./lib/jrb.o -c ./libfdr/jrb.c -w
	gcc -I ./libfdr/ -o ./lib/jval.o -c ./libfdr/jval.c -w

	gcc -I ./include/ -o ./kripto ./lib/string_islem.o ./lib/fields.o ./lib/jrb.o ./lib/jval.o ./src/kripto.c -w

temizle:
	clear