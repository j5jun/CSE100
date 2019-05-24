/*
 * ActorNode.h
 * Author: John Jun
 * Date:   5/29/2018
 *
 * The ActorNode class represents a node that contains the following information
 * (1) Actor Name
 * (2) 
 */

#ifndef ACTORNODE_H
#define ACTORNODE_H

#include <iostream>

// Maybe include some data structures here

using namespace std;

class ActorNode {
    public:
        string actorName;
        
        //Keeps track of whether or not the node has been visited
        bool isVisited;

        //constructor that creates a new ActorNode
        ActorNode(string actorName);

        //the previous actorNode before reaching the current node
        ActorNode* previous;

        //Actor
        ActorEdge* edge;

        /** You can modify this method definition as you wish
         *
         * Load the graph from a tab-delimited file of actor->movie relationships.
         *
         * in_filename - input filename
         * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
         *
         * return true if file was loaded sucessfully, false otherwise
         */
        bool operator<(const ActorNode& other);
};


#endif // ACTORNODE_H
