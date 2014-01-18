
#include "searchTool.h"

int HashFunction(char letter){
    int tablePosition;
    if(letter >= 48 && letter <= 57){     //first char of token is 0-9
        tablePosition = letter - 48;
    }
    if(letter >= 97 && letter <= 122){    //first char of token is a-z
        tablePosition = letter - 87;
    }
    return tablePosition;
}

char *Concat(char *string, char letter){    //concatenate character to end of a string
    char *str = string;
    char let = letter;
    size_t len = strlen(str);
    char *result = (char*) malloc((len + 2) * sizeof(char));
    strcpy(result, str);
    result[len] = let;
    return result;
}

//traverses the tree to find the given tokens files. If the token doesn't exist, returns NULL.
file_node *search_tree(TreeNode *root, char *token){
    file_node *fileList = (file_node*)malloc(sizeof(file_node));
    TreeNode *ptr = root;
    int i;
    char c;
    int index;
    for(i=0; i<strlen(token); i++){
        c = token[i];
        index = HashFunction(c);
        if(ptr->children[index] == NULL){
            return NULL;
        }
        ptr = ptr->children[index];
    }
    if(ptr->is_word == true){
        fileList = ptr->fileList;
        return fileList;
    }
    return NULL;
}

/* Updates the list of files that contain terms searched by the user. If the file is not in the
 * list of saved files yet, it is added. Otherwise, the frequency of that file is just incremented.
 */
file_node *update_files(file_node *savedFront, file_node *tokenList){
    file_node *ptr1 = NULL;
    file_node *ptr2 = savedFront;
    file_node *frontHold = NULL;    //saves the front of the saved file list so it can be returned
    file_node *new;
    if(savedFront == NULL){
        for(ptr1 = tokenList; ptr1 != NULL; ptr1 = ptr1->nextFN){
            new = malloc(sizeof(file_node));
            new->file = ptr1->file;
            new->freq = 1;
            new->nextFN = NULL;
            if(ptr2 == NULL){
                ptr2 = new;
                frontHold = ptr2;
            } else {
                ptr2->nextFN = new;
                ptr2 = ptr2->nextFN;
            }
        }
        savedFront = frontHold;
    } else {    //saved list already has files in it
        for(ptr1 = tokenList; ptr1 != NULL; ptr1 = ptr1->nextFN){
            for(ptr2 = savedFront; ptr2 != NULL; ptr2 = ptr2->nextFN){
                if(!strcmp(ptr1->file, ptr2->file)){
                    ptr2->freq++;
                    break;
                }
                if(ptr2->nextFN == NULL){   //file not in list and is added to the end of the saved file LL
                    new = malloc(sizeof(file_node));
                    new->file = ptr1->file;
                    new->freq = 1;
                    new->nextFN = NULL;
                    ptr2->nextFN = new;
                    break;
                }
            }
        }
    }
    return savedFront;
}

void print_so(file_node *front){
    file_node *curr;
    for(curr = front; curr != NULL; curr = curr->nextFN){
        if(curr == front){
            printf("\nFiles containing one or more of the searched terms:\n");
        }
        printf("%s\n", curr->file);
    }
    if(front == NULL){
        printf("\nNone of the listed terms were contained in any file.\n");
    }
}

void print_sa(file_node *front, int count){
    file_node *curr;
    bool boolean = false;
    for(curr = front; curr != NULL; curr = curr->nextFN){
        if(boolean == false && curr->freq == count){
            printf("\nFiles containing one or more of the searched terms:\n");
            boolean = true;
        }
        if(boolean == true && curr->freq == count){
            printf("%s\n", curr->file);
        }
    }
    if(front == NULL || boolean == false){
        printf("\nNone of the files contain all of the searched terms.\n");
    }
}

void destroy_savedList(file_node *front){
    file_node *temp;
    file_node *next;
    for(temp = front; temp != NULL; temp = next){
        next = temp->nextFN;
        temp->file = NULL;
        temp->freq = 0;
        free(temp);
    }
}

