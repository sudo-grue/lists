CFLAGS+=-Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline \
-std=c11 -Wall -Wextra
ARFLAGS = Urv
OBJDIR=StudentLibrary

.default: libStudent.a

libStudent.a: $(OBJDIR)/libStudent.a(Cllist/Cllist.o Llist/Llist.o Dllist/Dllist.o)


.PHONY: test

test: LDLIBS += -lStudent
test: Tests/testAll
	./$^


solution: LDLIBS += -lSolutions
solution: Tests/testAll
	./$^


clean:
	@$(RM) -r Tests/*.o Tests/testAll $(OBJDIR)/libStudent.a

TESTOBJS = $(subst .c,.o,$(wildcard Tests/test*.c))

Tests/testAll: $(TESTOBJS)
Tests/testAll: CFLAGS += -I. -g
Tests/testAll: LDLIBS += -lcunit
Tests/testAll: LDFLAGS += -LSolutionLibrary -LStudentLibrary



