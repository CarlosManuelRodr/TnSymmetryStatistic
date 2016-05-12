VERSION=10.0
MLINKDIR = /opt/Mathematica/SystemFiles/Links/MathLink/DeveloperKit/Linux-x86-64
SYS = Linux-x86-64
CADDSDIR = ${MLINKDIR}/CompilerAdditions
DEFINES = MATHEMATICA
EXTRA_CFLAGS=-m64 -D ${DEFINES}

INCDIR = ${CADDSDIR}
LIBDIR = ${CADDSDIR}
OBJDIR = obj
BINDIR = bin

MPREP = ${CADDSDIR}/mprep
RM = rm

CC = /usr/bin/cc
CXX = /usr/bin/c++

clean: 
	@echo "##########################"
	@echo "#                        #"
	@echo "#      Cleaning up       #"
	@echo "#                        #"
	@echo "##########################"
	@echo ""
	@rm -rf $(OBJDIR) $(BINDIR)
	

# Mathematica

before_mathematica: 
	@echo ""
	@echo "###########################################"
	@echo "#                                         #"
	@echo "# Building TnStatistic (for Mathematica)  #"
	@echo "#                                         #"
	@echo "###########################################"
	@echo ""
	@test -d $(BINDIR) || mkdir -p $(BINDIR)
	@test -d $(OBJDIR) || mkdir -p $(OBJDIR)

after_mathematica: 
	@echo ""
	@echo "#############################"
	@echo "#                           #"
	@echo "#            Done.          #"
	@echo "#                           #"
	@echo "#############################"
	@echo ""

mathematica : before_mathematica $(BINDIR)/TnStatisticMathLink after_mathematica

$(BINDIR)/TnStatisticMathLink : $(OBJDIR)/mathlinktm.o $(OBJDIR)/mathlink.o $(OBJDIR)/TnStatistic.o
	${CXX} ${EXTRA_CFLAGS} -I${INCDIR} $(OBJDIR)/mathlinktm.o $(OBJDIR)/mathlink.o $(OBJDIR)/TnStatistic.o -L${LIBDIR} -lML64i4 -lm -lpthread -lrt -lstdc++ -ldl -luuid -o $@
	
$(OBJDIR)/mathlinktm.o : $(OBJDIR)/mathlinktm.cpp
	${CXX} -c ${EXTRA_CFLAGS} -I${INCDIR} $(OBJDIR)/mathlinktm.cpp -o $@
	
$(OBJDIR)/mathlink.o: mathlink.cpp
	$(CXX) -c $(EXTRA_CFLAGS) -I${INCDIR} mathlink.cpp -o $(OBJDIR)/mathlink.o

$(OBJDIR)/TnStatistic.o: ../common/TnStatistic.cpp
	$(CXX) -c $(EXTRA_CFLAGS) -I${INCDIR} ../common/TnStatistic.cpp -o $(OBJDIR)/TnStatistic.o
	

$(OBJDIR)/mathlinktm.cpp : mathlink.tm
	${MPREP} $? -o $@
	
	
.DEFAULT_GOAL := mathematica

.PHONY: before_cli after_cli