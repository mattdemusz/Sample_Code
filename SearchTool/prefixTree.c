
#include "searchTool.h"


TreeNode *create_treenode(char c, TreeNode *parent){
    TreeNode *node = malloc(sizeof(TreeNode));
    node->c = c;
    node->parent = parent;
    node->children = malloc(36*sizeof(TreeNode));
    node->is_word = false;
    node->fileList = NULL;
    return node;
}


void destroy_treenode(TreeNode *node){
    if(node==NULL){
        return;
    }
    int i;
    for(i=0; i<36; i++){
        if(node->children[i] != NULL){
            if(node->children[i]->fileList != NULL){
                destroy_savedList(node->children[i]->fileList);
            }
        }
        destroy_treenode(node->children[i]);
    }
    free(node->children);
    free(node);
    return;
}

TreeNode *build_tree(FILE *index){
    char *string = "";
    char c;
    c = getc(index);
    while(c != EOF){
        string = Concat(string, c);
        c = getc(index);
    }
    //printf("%s", string);
    char *token;
    char *hold = NULL;
    char *seps = " \n";
    TreeNode *root = create_treenode(' ', NULL);
    file_node *fileFront = NULL;
    file_node *ptr = NULL;
    char *word;
    token = strtok_r(string, seps, &hold);
    
    /* Parses the string and checks each token to make sure its information thats to go
     * into the prefix tree, and not a tag thats used for formatting.
     */
    while (token){
        if(strcmp(token, "<list>") && strcmp(token, "</list>")){
            //printf("token: %s\n", token);
            word = token;
            while(token = strtok_r(NULL, seps, &hold), strcmp(token, "</list>")){
                if(fileFront == NULL){
                    fileFront = malloc(sizeof(file_node));
                    fileFront->file = token;
                    //printf("File is:%s--", token);
                    token = strtok_r(NULL, seps, &hold);
                    fileFront->freq = 0;
                    //printf("Frequency is:%s\n", token);
                    ptr = fileFront;
                } else {
                    file_node *new = malloc(sizeof(file_node));
                    new->file = token;
                    //printf("File is:%s--", token);
                    token = strtok_r(NULL, seps, &hold);
                    fileFront->freq = 0;
                    //printf("Frequency is:%s\n", token);
                    ptr->nextFN = new;
                    ptr = ptr->nextFN;
                }
            }
            root = add_token(root, word, fileFront);
            fileFront = NULL;
        } else {
            token = strtok_r(NULL, seps, &hold);
        }
    }
    return root;
}


TreeNode *add_token(TreeNode *root, char *token, file_node *fileFront){
    TreeNode *ptr = root;
    int character;
    int converted;
    size_t size = strlen(token);
    int i;
    for(i = 0; i < size; i++){
        character = token[i];
        converted = HashFunction(character);
        if(ptr->children[converted] == NULL){
            ptr->children[converted] = create_treenode(character, ptr);
        }
        //printf("%s / %c / %d\n", token, character, converted);
        ptr = ptr->children[converted];
    }
    ptr->is_word = true;
    ptr->fileList = fileFront;
    return root;
}