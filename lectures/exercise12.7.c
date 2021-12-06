/* Name: Lucas Mørk Frendorf */
/* Group: B201 */
/* Ran using: gcc exercise12.7.c -ansi -Wall -pedantic && ./a.out && rm a.out */
/* Ran on: Linux [x86_64] */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Symbolic constants */
struct tree_node{
  int key;
  struct tree_node *leftp, *rightp;
};

typedef struct tree_node tree_node;

/* Prototypes */
tree_node *make_tree(int key, tree_node *left, tree_node *right);
void assert_allocation_success(void *alloc_pointer);
tree_node *insert_in_binary_search_tree(tree_node *tree_ptr, int e);
void print_tree(tree_node *tree_ptr);
void print_tree_helper(tree_node *tree_ptr, int level);
int tree_height(tree_node *tree_ptr);

int main(void) {
  tree_node *tree4 = NULL;
  tree4 = insert_in_binary_search_tree(tree4, 6);
  tree4 = insert_in_binary_search_tree(tree4, 2);
  tree4 = insert_in_binary_search_tree(tree4, 1);
  tree4 = insert_in_binary_search_tree(tree4, 4);
  tree4 = insert_in_binary_search_tree(tree4, 3);
  tree4 = insert_in_binary_search_tree(tree4, 5);
  tree4 = insert_in_binary_search_tree(tree4, 7);
  tree4 = insert_in_binary_search_tree(tree4, 9);
  tree4 = insert_in_binary_search_tree(tree4, 8);

  /* printf("tree4:\n");
  print_tree(tree4); */

  tree_height(tree4);

  exit(EXIT_FAILURE);
}


tree_node *make_tree(int key, tree_node *left, tree_node *right){
  tree_node *the_tree = malloc(sizeof(tree_node));
  assert_allocation_success(the_tree);
  the_tree->key = key; 
  the_tree->leftp = left; 
  the_tree->rightp = right; 
  return the_tree;
} 

void assert_allocation_success(void *alloc_pointer){
  if (alloc_pointer == NULL){
    printf("Allocation problems. Your program stops.");
    exit(EXIT_FAILURE);
  }
}

/* Insert the element e i the binary search tree, designated by tree_ptr. 
   Drop the insertion if e is already in the tree. 
   Return the tree  in terms of a pointer to its root node. */
tree_node *insert_in_binary_search_tree(tree_node *tree_ptr, int e){
  if (tree_ptr == NULL){
    /* Make a small tree rooted with e and empty subtrees */
    /* This branch is never reached via recursion */
    tree_node *the_tree = make_tree(e, NULL, NULL);
    return the_tree;
  }
  else if (e == tree_ptr->key){
    /* Do nothing */
    return tree_ptr;
  }
  else if (e < tree_ptr->key && tree_ptr->leftp == NULL){
    tree_node *the_tree = make_tree(e, NULL, NULL);
    tree_ptr->leftp = the_tree;
    return tree_ptr;         
  }
  else if (e < tree_ptr->key){
    insert_in_binary_search_tree(tree_ptr->leftp, e);
    return tree_ptr;
  }
  else if (e > tree_ptr->key && tree_ptr->rightp == NULL){
    tree_node *the_tree = make_tree(e, NULL, NULL);
    tree_ptr->rightp = the_tree;
    return tree_ptr;         
  }
  else { /* e > tree_ptr->key) */
    insert_in_binary_search_tree(tree_ptr->rightp, e);
    return tree_ptr;
  }
}

void print_tree(tree_node *tree_ptr){
  print_tree_helper(tree_ptr, 0);
}    

/* print the tree designated by tree_ptr as horizotally, as an indented text, on standard output.
   Empty subtrees are printed as "." if tree_ptr is passsed as NULL */
void print_tree_helper(tree_node *tree_ptr, int level){
  int i; 

  /* print indented root */
  for(i = 0; i < level; ++i) 
    printf("   ");
  if (tree_ptr == NULL)
    printf(".\n");  /* Missing part */
  else
    printf("%d\n", tree_ptr->key);

  if(tree_ptr != NULL){
    /* print branches */
    if (tree_ptr->leftp == NULL && tree_ptr->rightp == NULL){
      /* print nothing */
    }
    else if (tree_ptr->leftp != NULL && tree_ptr->rightp == NULL){
      print_tree_helper(tree_ptr->leftp, level+1);
      print_tree_helper(NULL, level+1);
    }   
    else if (tree_ptr->leftp == NULL && tree_ptr->rightp != NULL){
      print_tree_helper(NULL, level+1);
      print_tree_helper(tree_ptr->rightp, level+1);
    }
    else {  
      print_tree_helper(tree_ptr->leftp, level+1);
      print_tree_helper(tree_ptr->rightp, level+1);
    }
  }
}


/* Opgave */
int tree_height(tree_node *tree_ptr){
    int i, height = 0;
    printf("test\n");
    /* print_tree(tree_ptr); */

    for (i = 0; i < sizeof(tree_ptr); i++)
    {
        printf("%d\n", tree_ptr->key);
    }

    height++;

    if ()
    

  return 0;
}