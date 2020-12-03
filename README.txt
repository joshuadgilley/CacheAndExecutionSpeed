This is my implementation of the Graph ADT. Note that I have a separate document in this zip called Learning_Outcomes.pdf where I describe some of the issues that I ran into in trying to put this together.

This read me is simply to tell you how to run this program. 

You can use one of the following commands where the first argument is the number of the nodes you wish to use. This must be either 10, 100, 1000, or 10,000 but as you get up to 10,000 you start to run into some issue which I go over in Learning_Outcomes.pdf.

The second argument is to specify if you want the graph to be built as bipartite or not. If you want the graph to be bipartite then pass the flag “-bipartite” and if not then don’t pass anything. 

Some examples of how to run the program. 

1.) Navigate to the root folder where “Graph.java” is. 

2.) Run one of the following commands
	java Graph.java 10 
	java Graph.java 10 -bipartite
	java Graph.java 100
	java Graph.java 100 -bipartite
	java Graph.java 1000 
	java Graph.java 1000 -bipartite

Again when you start to get up to 10,000 and 100,000 you start to run into issues in calculate the strongly connected components for (0.80*N choose 2) edges.
