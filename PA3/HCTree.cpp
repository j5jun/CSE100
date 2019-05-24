#include "HCTree.h"
#include "HCNode.h"
#include "BitOutputStream.h"
#include "BitInputStream.h"
#include <iostream>
#include <stack>

using namespace std;

    /** Use the Huffman algorithm to build a Huffman coding trie.
     *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
     *  the frequency of occurrence of byte i in the message.
     *  POSTCONDITION:  root points to the root of the trie,
     *  and leaves[i] points to the leaf node containing byte i.
     */
    void HCTree::build(const vector<int>& freqs){
    	//create a priority queue
    	priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pqueue;

    	for(int i = 0; i < freqs.size(); i++){
            //add characters that occur at least once to the queue
    		if(freqs[i] != 0){
    			HCNode* temp = new HCNode(freqs[i], i);
    			leaves[i] = temp;
   				pqueue.push(leaves[i]);
    		}
    	}

        //handling empty file : set the root to null pointer
        if(pqueue.size() < 1){
            root = nullptr;
            return;
        }

    	while(pqueue.size() > 1){
            // retrieve the first node that contains the least frequency
    		HCNode* first = pqueue.top();
    		pqueue.pop();
            // retrieve the second node that contains the next least frequency
    		HCNode* second = pqueue.top();
    		pqueue.pop();

            // create a parent node for the two child nodes
            /* Parent Node Information:
             * count : the sum of the counts of the two child nodes
             * symbol : the symbol of the node with lower frequency; if the frequencies
                        are the same, the symbol is updated to the one with lower ASCII value. 
             */
    		HCNode* parent = new HCNode((first->count + second->count), first->symbol);

            //assign the parent node to each of the child nodes
  			first->p = parent;
  			second->p = parent;

            //assign the child nodes to the parent node
  			parent->c0 = first;
  			parent->c1 = second;

            //insert the parent node to the queue.
  			pqueue.push(parent);
    	}

        //if there is a single node in the queue, make the node the root node of the tree.
    	if(pqueue.size() == 1){
    		HCNode* last = pqueue.top();
            root = last;
    	}
    }

    void HCTree::build( BitInputStream& bin, ifstream& in){
        stack<HCNode*>* nodestack2;
        root = new HCNode(0, 0);
        nodestack2->push(root);

        while( !nodestack2.empty() ){
            int bit = bin.readBit();
            HCNode* curr = nodestack2.top();
            nodestack2.pop();

            if(bit == 0){
                curr->c0 = new HCNode(0, 0);
                curr->c1 = new HCNode(0, 0);

                nodestack2.push(curr->c0);
                nodestack2.push(curr->c1);
            }
            else{
                curr->symbol = bin.readByte();
            }
        }
        return;
    }

    /** Write to the given BitOutputStream
     *  the sequence of bits coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    void HCTree::encode(byte symbol, BitOutputStream& out) const{
        //empty tree
        if(leaves[(int)symbol] == nullptr){
            return;
        }

        stack<unsigned int> s;
        HCNode* n = leaves[(int)symbol];
        while(n->p){
            if(n->p->c0 == n){
                //add 0 to the encoding sequence
                s.push(0);
            }
            else if(n->p->c1 == n){
                //add 1 to the encoding sequence
                s.push(1);
            }
            //update the current node to the parent node
            n = n->p;
        }

        while(!s.empty()){
            out.writeBit(s.top());
            s.pop();
        }
    }

    /** Return symbol coded in the next sequence of bits from the stream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    int HCTree::decode(BitInputStream& in) const{
        if(root == nullptr) return -1;

        HCNode* curr = root;

        while(curr->c0 != nullptr && curr->c1 != nullptr){
            unsigned int num = in.readBit();
            cout << num << endl;
            if(num == 0)
            {
                curr = curr->c0;
            }   
            else{
                curr = curr->c1;
            }
        }
        return curr->symbol;
    }

    void HCTree::encode_header( int totalnum, int uniquenum, BitOutputStream& bout, ostream& out){
        cout << "Encoding Tree Start" << endl;
        out.put('0'+totalnum);
        out << endl;
        out.put('0'+uniquenum);
        out << endl;

        stack<HCNode*>* nodestack = new stack<HCNode*>;
        nodestack->push(root);

        if(uniquenum == 1){
            HCNode* currNode = nodestack->top();
            bout.writeByte(currNode->symbol);
            delete nodestack;
            return;
        }

        while(nodestack->size() > 0){
            HCNode* currNode = nodestack->top();
            nodestack->pop();

            if(currNode == nullptr){
                continue;
            }

            //if the current node is an internal node, write bit 0.
            if(currNode->c0 != nullptr && currNode->c1 != nullptr){
                bout.writeBit(0);
            }
            //if the current node is a leaf node, write bit 1 and the character
            else{
                bout.writeBit(1);
                bout.writeByte(currNode->symbol);
            }

            nodestack->push(currNode->c1);
            nodestack->push(currNode->c0);
        }

        delete nodestack;
        return;
    }

    //Destructor for HCTree. Uses the helper function "deleteAll"
    HCTree::~HCTree(){
        deleteAll(root);
    }

    /* Helper function for the HCTree destructor. Recursively deletes
     * all the nodes in the tree.
     */
    void HCTree::deleteAll(HCNode* root){
        if(!root){
            return;
        }
        deleteAll(root->c0);
        deleteAll(root->c1);

        delete root;
    }