
#include "searchTool.h"

int main(int argc, char *argv[]){
    
    FILE *index;
    index = fopen(argv[1], "r");
    if(index == NULL){
        fprintf(stderr, "ERROR: given inverted index file does not exist\nf");
        return 1;
    }
    TreeNode *root = build_tree(index);
    char input[1000];
    char *token;
    char *hold = NULL;
    char *seps = " \n";
    fputs("Please enter one of the following:\n\t\"sa <terms>\", for a list of files with all of the listed terms\n\t\"so <terms>\", for a list of files containing one or more of the terms\n\t\"q\" to quit\n", stdout);
    fgets(input, sizeof(input), stdin);
    file_node *temp = NULL;
    int count = 0;
    while (strcmp(input, "q\n")){
        file_node *savedFront = NULL;
        token = strtok_r(input, seps, &hold);
        //printf("token: %s\n", token);
        
        // checks to see which type of search the user wants to perform
        if(token != NULL && !strcmp(token, "sa")){
            token = strtok_r(NULL, seps, &hold);
            // loops through the terms searched by the user
            while(token){
                temp = search_tree(root, token);    //gets the files associated with the given token
                if(temp != NULL){
                    savedFront = update_files(savedFront, temp);
                }
                count++;
                token = strtok_r(NULL, seps, &hold);
            }
            print_sa(savedFront, count);
        }
        else if(token != NULL && !strcmp(token, "so")){
            token = strtok_r(NULL, seps, &hold);
            // loops through the terms searched by the user
            while(token){
                temp = search_tree(root, token);
                if(temp != NULL){
                    savedFront = update_files(savedFront, temp);
                }
                token = strtok_r(NULL, seps, &hold);
            }
            print_so(savedFront);
        }
        else {
            fprintf(stderr, "ERROR: incorrect input format\n");
            return 1;
        }
        
        //starts loop again
        fputs("\nPlease enter one of the following:\n\t\"sa <terms>\", for a list of files with all of the listed terms\n\t\"so <terms>\", for a list of files containing one or more of the terms\n\t\"q\" to quit\n", stdout);
        fgets(input, sizeof(input), stdin);
        destroy_savedList(savedFront);
        count = 0;
    }
    printf("Quiting program......\n");
    destroy_treenode(root);
    return 0;
}
