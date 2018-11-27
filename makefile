ECHO= @echo
RM= rm
COMP= g++
EDL= g++
CPPFLAGS= -D MAP -ansi -pedantic -Wall -std=c++11 
EDLFLAGS=
RMFLAGS= -f
INT=Test.h Grille.h
REAL= $(INT:.h=.cpp)
OBJ=$(REAL:.cpp=.o)
LIBS=
INCPATH=
LIBPATH=
EFFACE=clean
EXE=Demineur
DATE=22.10
AUTHOR=Felix
YEAR=2018
EMAIL=felix.fonteneau@insa-lyon.fr

.PHONY: $(EFFACE)

$(EXE) : $(OBJ)
	$(ECHO) "Edition de liens de <$(EXE)>"
	$(EDL) -o $(EXE) $(OBJ) $(LIBS)

Grille.o : Grille.cpp Grille.h
	$(ECHO) "Compilation de <Grille.cpp>"
	$(COMP) $(CPPFLAGS) $(INCPATH) -c Grille.cpp

Test.o : Test.cpp Test.h
	$(ECHO) "Compilation de <Test.cpp>"
	$(COMP) $(CPPFLAGS) $(INCPATH) -c Test.cpp

$(EFFACE) :
	$(ECHO) "Suppression des fichiers"
	$(RM) $(RMFLAGS) $(OBJ) $(EXE) core
