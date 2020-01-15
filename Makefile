CC=gcc
CFLAGS=`PKG_CONFIG_PATH="/usr/local/opt/postgresql@9.6/lib/pkgconfig" pkg-config --cflags libpq`
LIBS=`PKG_CONFIG_PATH="/usr/local/opt/postgresql@9.6/lib/pkgconfig" pkg-config --libs libpq`
SOURCE=main.c
EXE=pgtest

all:
	$(CC) $(CFLAGS) $(LIBS) $(SOURCE) -o $(EXE)

clean:
	rm -f $(EXE)
