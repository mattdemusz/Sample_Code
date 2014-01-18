
#ifndef search_search_h
#define search_search_h

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>

//true false boolean
typedef enum {false, true} bool;

/* Tree node is an array of length 36, each poistion representing 0-9
 * or a-z. Each position also has a pointer to its child tree node.
 */
struct TreeNode{
    char c;
    struct TreeNode *parent;
    struct TreeNode **children;
    bool is_word;
    struct file_node *fileList;
};
typedef struct TreeNode TreeNode;

/* node structure to hold the file path name a token exists in and its
 * frequency in that file along with a pointer to the next file_node
 */
struct file_node{
    const char *file;
    int freq;
    struct file_node *nextFN;
};
typedef struct file_node file_node;


/* Concat takes a string and a character as parameters and adds the character
 * to the end of the string and returns the resulting string
 */
char *Concat(char *string, char letter);

/* HashFunction is a function that takes in a char from a token and returns
 * an int so that char can be mapped in the prefix tree
 */
int HashFunction(char letter);


//**********prefix tree functions**********
void destroy_treenode(TreeNode *node);
TreeNode *create_treenode(char c, TreeNode *parent);
TreeNode *add_token(TreeNode *root,char *token, file_node *fileFront);
TreeNode *build_tree(FILE *index);
file_node *search_tree(TreeNode *root, char *token);
file_node *update_files(file_node *savedFront, file_node *temp);
void print_so(file_node *front);
void print_sa(file_node *front, int count);
void destroy_savedList(file_node *front);



#endif
