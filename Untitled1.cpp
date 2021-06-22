#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct Node{
	char goatId[10];
	char goatName[50];
	char goatColor[20];
	int goatWeight;
	int goatAge;
	int height;
	Node* left;
	Node* right;
};

Node* createNode(char goatId[10],char goatName[50], char goatColor[20], int goatWeight, int goatAge){
	Node* newNode = (Node*)malloc(sizeof(Node));
	strcpy(newNode->goatId,goatId);
	strcpy(newNode->goatName,goatName);
	strcpy(newNode->goatColor,goatColor);
	newNode->goatWeight = goatWeight;
	newNode->goatAge = goatAge;
	newNode->height = 1;
	newNode->left = newNode->right = NULL;
	return newNode;
}

int max(int a, int b){
	// ternary
	// if (a > b) return a
	// else return b
	return a > b ? a : b;
}

int getHeight(Node* root){
	if(!root) return 0;
	return root->height;
	// 1. root nya ada -> langsung return root->height
	// 2. root nya NULL -> jangan return root->height, tapi 0;
}

int getBalanceFactor(Node* root){
	// height anak kiri - height anak kanan 
	return getHeight(root->left) - getHeight(root->right);
}

void updateHeight(Node* root){
	// height = max(height anak kiri, height anak kanan) + 1 -> diri sendiri
	root->height = max(getHeight(root->left), getHeight(root->right)) + 1;		
}

Node* rotateRight(Node* root){
	Node* child = root->left;
	Node* gchild = child->right;
	
	child->right = root;
	root->left = gchild;
	
	updateHeight(root);
	updateHeight(child);
	
	return child;
}

Node* rotateLeft(Node* root){
	Node* child = root->right;
	Node* gchild = child->left;
	
	child->left = root;
	root->right = gchild;
	
	updateHeight(root);
	updateHeight(child);
	
	return child;
}

Node* rebalance(Node* root){
	// balance factor
	int bf = getBalanceFactor(root);
	
	if(bf < -1){
		// kanan lebih berat
		if(getBalanceFactor(root->right) > 0){
			// root -> kanan -> kiri 
			// rotate right si childnya
			root->right = rotateRight(root->right);
		}
		// rotate left si rootnya
		root = rotateLeft(root);
	}else if(bf > 1){
		// kiri lebih berat
		if(getBalanceFactor(root->left) < 0){
			// root -> kiri -> kanan
			// rotate left si childnya
			root->left = rotateLeft(root->left);
		}
		// rotate right si rootnya
		root = rotateRight(root);
	}
	return root;
}

Node* push(Node* root,char goatId[10],char goatName[50], char goatColor[20], int goatWeight, int goatAge){
	if(!root) return createNode(goatId,goatName,goatColor,goatWeight,goatAge);
	if(strcmp(goatId, root->goatId) < 0){
		root->left = push(root->left,goatId,goatName,goatColor,goatWeight,goatAge);
	}else if(strcmp(goatId, root->goatId) > 0){
		root->right = push(root->right,goatId,goatName,goatColor,goatWeight,goatAge);
	}
	updateHeight(root);
	return rebalance(root);
}

Node* searchGoat(Node* root, char goatId[10]){
	if(!root) return NULL;
	
	if(strcmp(goatId, root->goatId) < 0) // name < root
		return searchGoat(root->left, goatId);
	else if(strcmp(goatId, root->goatId) > 0) // name > root
		return searchGoat(root->right, goatId);
	else return root;
}

bool nameIsValid(Node* root, char goatId[5]){
	char arr[5];
	if(strlen(goatId) < 5){
		printf("GOAT ID MUST CONSIST OF 5 DIGITS\n\n");
		return false;
	}
	for(int i=0;i<strlen(goatId);i++){
		if(!isdigit(goatId[i])){
			printf("GOAT ID MUST CONSIST OF NUMBERS ONLY\n\n");
			return false;
		}
	}
	return true;
}

bool checkunique(Node* root, char goatId[5]){
	for (int i = 0; i < strlen(goatId) - 1; i++) {
        for (int j = i + 1; j < strlen(goatId); j++) {
            if (goatId[i] == goatId[j]) {
            	printf("\n");
                return true;
            }
        }
    }
    printf("GOAT ID MUST UNIQUE!\n\n");
    return false;
}

Node* insertGoat(Node* root){
	char goatId[5];
	char goatName[30];
	char goatColor[15];
	int goatWeight;
	int goatAge;
	char confirmation;
	do{
		printf("Insert goat's id [5 digits number] : ");
		scanf("%[^\n]",goatId);
		getchar();
	}while(!nameIsValid(root,goatId) || !checkunique(root,goatId));
	do{
		printf("Insert goat's name [2 chars or more] : ");
		scanf("%[^\n]",goatName);
		getchar();
		if(strlen(goatName) < 2){
			puts("GOAT NAME MUST CONSISTS OF 2 CHARACTERS OR MORE!\n");
		}
	}while(strlen(goatName) < 2);
	printf("\n");
	do{
		printf("Insert goat's color [WHITE|BLACK|BROWN] : ");
		scanf("%[^\n]",goatColor);
		getchar();
		if(strcmpi(goatColor,"WHITE")!=0 && strcmpi(goatColor,"BLACK")!=0 && strcmpi(goatColor,"BROWN")!=0){
			puts("GOAT'S COLOR CAN ONLY BE WHITE / BLACK / BROWN\n");
		}
	}while(strcmpi(goatColor,"WHITE")!=0 && strcmpi(goatColor,"BLACK")!=0 && strcmpi(goatColor,"BROWN")!=0);
	printf("\n");
	do{
		printf("Insert goat's weight in KG [2-150] : ");
		scanf("%d",&goatWeight);
		getchar();
		if(goatWeight < 2 || goatWeight > 150){
			puts("GOAT'S WEIGHT MUST BE BETWEEN 2 AND 150 (INCLUSIVELY)\n");
		}
	}while(goatWeight < 2 || goatWeight > 150);
	printf("\n");
	do{
		printf("Insert goat's age in month(s) [0-60] : ");
		scanf("%d",&goatAge);
		getchar();
		if(goatAge < 0 || goatAge > 60){
			puts("GOAT'S AGE MUST BE BETWEEN 0 AND 60 (INCLUSIVELY)\n");
		}
	}while(goatAge < 0 || goatAge > 60);
	printf("\n");
	do{
		printf("ARE YOU SURE YOU WANT TO ADD %s PRODUCT? [Y|N] > ",goatName);
		scanf("%c",&confirmation);
		printf("\n");
		getchar();
	}while(confirmation != 'Y' && confirmation != 'N');
	if(confirmation == 'Y'){
		printf("SUCCESS ADD!\n");
		root = push(root, goatId, goatName, goatColor, goatWeight, goatAge);
	}
	return root;
}

void inorder(Node* root){
	if(!root) return;
	inorder(root->left);
	printf("\n");
	printf("===============================\n");
	printf("Goat's ID	: %s\n",root->goatId);
	printf("Goat's Name	: %s\n",root->goatName);
	printf("Goat's Color	: %s\n",root->goatColor);
	printf("Goat's Weight	: %d KG\n",root->goatWeight);
	printf("Goat's Age	: %d Months\n",root->goatAge);
	printf("===============================\n");
	printf("\n");
	inorder(root->right);
}

void preorder(Node* root){
	if(!root) return;
	printf("\n");
	printf("===============================\n");
	printf("Goat's ID	: %s\n",root->goatId);
	printf("Goat's Name	: %s\n",root->goatName);
	printf("Goat's Color	: %s\n",root->goatColor);
	printf("Goat's Weight	: %d KG\n",root->goatWeight);
	printf("Goat's Age	: %d Months\n",root->goatAge);
	printf("===============================\n");
	printf("\n");
	preorder(root->left);
	preorder(root->right);
}

void postorder(Node* root){
	if(!root) return;
	postorder(root->left);
	postorder(root->right);
	printf("\n");
	printf("===============================\n");
	printf("Goat's ID	: %s\n",root->goatId);
	printf("Goat's Name	: %s\n",root->goatName);
	printf("Goat's Color	: %s\n",root->goatColor);
	printf("Goat's Weight	: %d KG\n",root->goatWeight);
	printf("Goat's Age	: %d Months\n",root->goatAge);
	printf("===============================\n");
	printf("\n");
}

void seeAllProduct(Node* root){
	if(!root){
		puts("YOU DON'T HAVE ANY GOAT");
		getchar();
		return;
	}
	int choose = 0;
	do{
		puts("How do you want to see all product?");
		puts("1. In order");
		puts("2. Pre order");
		puts("3. Post order");
		printf(">> ");
		scanf("%d",&choose);
		getchar();
		switch(choose){
			case 1:
				inorder(root);
				getchar();
				break;
			case 2:
				preorder(root);
				getchar();
				break;
			case 3:
				postorder(root);
				getchar();
				break;
		}
	}while(choose < 1 || choose > 3);
}

Node* findPredecessor(Node* root){
	root = root->left; // ke kiri 1x
	while(root->right){ // ke kanan sampe mentok
		root = root->right;
	}
	return root;
}

Node* pop(Node* root, char goatId[10]){
	if(!root) return NULL;
	
	if(strcmp(goatId, root->goatId) < 0){
		root->left = pop(root->left, goatId);
	}else if(strcmp(goatId, root->goatId) > 0){
		root->right = pop(root->right, goatId);
	}else{
		// ketemu
		if(root->left && root->right){
			root = NULL;
			free(root);
			return NULL;
		}else if(!root->left){
			// anak kanan
			Node* child = root->right;
			root = NULL;
			free(root);
			return child;
		}else if(!root->right){
			// anak kiri
			Node* child = root->left;
			root = NULL;
			free(root);
			return child;
		}else{
			// 2 anak
			Node* pre = findPredecessor(root);
			strcpy(root->goatId,pre->goatId);
			strcpy(root->goatName, pre->goatName);
			strcpy(root->goatColor, pre->goatColor);
			root->goatWeight = pre->goatWeight;
			root->goatAge = pre->goatAge;
			
			root->left = pop(root->left, pre->goatId);
		}
	}
	updateHeight(root);
	
	return rebalance(root);
}

Node* removeProduct(Node* root){
	if(!root){
		puts("YOU DON'T HAVE ANY GOAT!");
		return NULL;
	}
	char goatId[10];
	Node* found = NULL;
	
	seeAllProduct(root);
	
	do{
		printf("ENTER GOAT ID TO BE REMOVED! > ");
		scanf("%[^\n]",goatId);
		found = searchGoat(root, goatId);
		if(!found){
			printf("ID IS INVALID!\n");
			getchar();
		}else{
			printf("SUCCESS REMOVE PRODUCT");
			getchar();
			pop(root, goatId);
		}
	}while(!found);
}

Node* removeAllProduct(Node* root){
	char confirmation;
	if(!root){
		puts("No Data!");
		return NULL;
	}
	do{
		printf("ARE YOU SURE WANT TO REMOVE ALL GOAT? [Y|N] > ");
		scanf("%c",&confirmation);
		getchar();
	}while(confirmation != 'Y' && confirmation != 'N');
	if(confirmation == 'Y'){
		while(root){
			root = pop(root, root->goatId);
		}
		printf("SUCCESS REMOVE ALL GOAT!");
	}
	return root;	
}

int main(){
	int choose = 0;
	Node* root = NULL;
	do{
		system("cls");
		puts("Mbek Farm\n");
		puts("1. Insert New Goat");
		puts("2. Remove a goat");
		puts("3. Sell all goat");
		puts("4. Remove all goat");
		puts("5. Exit");
		printf(" >> ");
		scanf("%d",&choose);
		getchar();
		switch(choose){
			case 1 :
				root = insertGoat(root);
				getchar();
				break;
			case 2 :
				root = removeProduct(root);
				getchar();
				break;
			case 3 :
				seeAllProduct(root);
				break;
			case 4 :
				root = removeAllProduct(root);
				getchar();
				break;
		}
	}while(choose!=5);
	return 0;
}
