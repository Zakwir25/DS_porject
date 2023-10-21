#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node{
	int iso;
	int size;
	char name[40];
	char type[10];
	char nikon[20];
	char strSpeed[10];
	char lensa[10];
	char loc[50];
	char putihabu[4];
	
	
	struct node *left;
	struct node *right;
};

struct node *createNewNode(struct node *root,char name[], char type[], char nikon[]
,char strSpeed[],int iso,char lensa[],char putihabu[],char loc[], int size){
	struct node *newNode = (struct node*)malloc(sizeof(struct node));
	
		newNode->size = size;
	newNode->iso = iso;
	newNode->left = NULL;
	newNode->right = NULL;
		
	strcpy(newNode->name, name);
	strcpy(newNode->nikon, nikon);
	strcpy(newNode->strSpeed, strSpeed);
	strcpy(newNode->lensa, lensa);
	strcpy(newNode->putihabu, putihabu);
	strcpy(newNode->loc, loc);
	strcpy(newNode->type, type);

	
	return newNode;
}

struct node* minvalnode(struct node* node){
    struct node* current = node;
 
    while (current && current->left != NULL)
        current = current->left;
 
    return current;
}

struct node * insert(struct node *root,char name[], char type[], char nikon[],  char strSpeed[],int iso,char lensa[],char putihabu[],char loc[], int size){
	if(root == NULL){
		return createNewNode(root, name, type,  nikon, strSpeed, iso, lensa, putihabu, loc, size);
	}
	else if(size < root->size){
		root->left = insert(root->left, name, type,  nikon, strSpeed, iso, lensa, putihabu, loc, size);
	}
	else if(size >= root->size){
		root->right = insert(root->right, name, type,  nikon, strSpeed, iso, lensa, putihabu, loc, size);
	}
	return root;
}

//display
void inOrder(struct node *root){ 
	if(root == NULL){
		return;
	}
	else{
		inOrder(root->left);
		printf("%s.%s, %d KB - %s\nnikon: %s, Shutter Speed: %s, ISO: %d, Aperture: %s, Grayscale: %s \n", root->name, root->type, root->size, root->loc, 
		root->nikon, root->strSpeed, root->iso, root->lensa, root->putihabu);
		inOrder(root->right);
	}
}


struct node* deletenode(struct node* root, char name[]){
	if(root == NULL) {
		return;
 	} 
	else if(strcmp(root->name, name) != 0){
  		root->left = deletenode(root->left, name);
 		root->right = deletenode(root->right, name);
 	} 
	else if(strcmp(root->name, name) == 0) {
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }
 
        struct node* temp = minvalnode(root->right);
 
        root = temp;
 
        root->right = deletenode(root->right, temp->name);
     	return root;
 	}
}

struct node* searchname(struct node* root, char name[]){
	if(root == NULL) {
		return;
 	} 
	else if(strcmp(root->name, name) != 0){
  		root->left = searchname(root->left, name);
 		root->right = searchname(root->right, name);
 	} 
	else if(strcmp(root->name, name) == 0) {
  		printf("\n%s.%s, %d KB - %s\nnikon: %s, Shutter Speed: %s, ISO: %d, Aperture: %s, Grayscale: %s \n", root->name, root->type, root->size, root->loc, 
		        root->nikon, root->strSpeed, root->iso, root->lensa, root->putihabu);
 	return root;
	 }
}

int main(){
	
	
	struct node* root = NULL;
	char name[100];
	char nikon[100];
	char type[5];
	char strSpeed[100];
	int iso;
	char lensa[100];
	char putihabu[100];
	char loc[100];
	int size;
	int i;
	FILE *fp;
	fp=fopen("imagesize.txt","r");

	i=0;
	while(!feof(fp)){
		fscanf(fp,"%[^.].%[^#]#%[^#]#%[^#]#%d#%[^#]#%[^#]#%[^#]#%d\n",name, type, nikon, strSpeed, &iso, lensa, putihabu, loc, &size);
		root = insert(root, name,type, nikon, strSpeed, iso, lensa, putihabu, loc, size);
		i++;
	}

	fclose(fp);
	printf("Deleting foto_60.bmp...\n");
	deletenode(root, "foto_39");
	printf("Searching for foto_69.jpg...\n");
	searchname(root, "foto_65");
	printf("Displaying list image:\n\n");
	inOrder(root);
	
	
	return 0;
}
