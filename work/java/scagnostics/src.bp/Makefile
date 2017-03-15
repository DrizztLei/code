JAVAC=javac
JAR=jar
JAVADOC=javadoc
JDKVER=1.5
JFLAGS=-source $(JDKVER) -target $(JDKVER)
JAPIURL=http://java.sun.com/j2se/1.4.2/docs/api

DOCSDIR=javaDoc

SRC=scagnostics/BinnedData.java scagnostics/Binner.java scagnostics/Cluster.java scagnostics/Edge.java scagnostics/Main.java scagnostics/Node.java scagnostics/Scagnostics.java scagnostics/Sorts.java scagnostics/Triangle.java

all: scagnostics.jar

scagnostics.jar: $(SRC)
	$(JAVAC) -d . $(JFLAGS) $(SRC)
	$(JAR) fc $@ scagnostics

docs: $(SRC)
	rm -rf $(DOCSDIR)
	mkdir $(DOCSDIR)
	$(JAVADOC) -d $(DOCSDIR) -author -version -breakiterator -link $(JAPIURL) $(SRC)

install: scagnostics.jar
	-mkdir -p ../inst/java
	cp scagnostics.jar ../inst/java/scagnostics.jar

clean:
	rm -rf scagnostics/*.class scagnostics.jar $(DOCSDIR)
