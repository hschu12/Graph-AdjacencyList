CC=g++
CFLAGS= -std=c++14 -O2

make: graph/TestDirectedNoProp.cpp graph/TestBidirectionalNoProp.cpp graph/TestTopoSort.cpp \
	graph/TestBidirectionalProps.cpp graph/TestDirectedProps.cpp graph/TestAddVertexFAILNoProp.cpp \
	graph/TestAddSameEdgeFAIL.cpp graph/TestAddVertexFAILProps.cpp graph/TestAddEdgeSameVertexFAIL.cpp \
	graph/TestAddEdgeLargeVertexFAIL.cpp
	$(CC) $(CFLAGS) graph/TestDirectedNoProp.cpp -o testDirectedNoProp
	$(CC) $(CFLAGS) graph/TestBidirectionalNoProp.cpp -o testBidirectionalNoProp
	$(CC) $(CFLAGS) graph/TestTopoSort.cpp -o testTopoSort
	$(CC) $(CFLAGS) graph/TestBidirectionalProps.cpp -o testBidirectionalProps
	$(CC) $(CFLAGS) graph/TestDirectedProps.cpp -o testDirectedProps
	$(CC) $(CFLAGS) graph/TestAddVertexFAILNoProp.cpp -o testAddVertexFAILNoProp
	$(CC) $(CFLAGS) graph/TestAddSameEdgeFAIL.cpp -o testAddSameEdgeFAIL
	$(CC) $(CFLAGS) graph/TestAddVertexFAILProps.cpp -o testAddVertexFAILProps
	$(CC) $(CFLAGS) graph/TestAddEdgeSameVertexFAIL.cpp -o testAddEdgeSameVertexFAIL
	$(CC) $(CFLAGS) graph/TestAddEdgeLargeVertexFAIL.cpp -o testAddEdgeLargeVertexFAIL

clean: 
	rm testDirectedNoProp
	rm testBidirectionalNoProp
	rm testTopoSort
	rm testBidirectionalProps
	rm testDirectedProps
	rm testAddVertexFAILNoProp
	rm testAddSameEdgeFAIL
	rm testAddVertexFAILProps
	rm testAddEdgeSameVertexFAIL
	rm testAddEdgeLargeVertexFAIL