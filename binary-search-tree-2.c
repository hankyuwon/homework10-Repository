#include <stdio.h>
#include <stdlib.h>

typedef struct node { // Node 구조체 포인터 생성
    int key;
    struct node *left;
    struct node *right;
}Node;

#define MAX_STACK_SIZE 20
Node* stack[MAX_STACK_SIZE];
int top=-1;

Node* pop();
void push(Node* aNode);

#define MAX_QUEUE_SIZE 20
Node* queue[MAX_QUEUE_SIZE];
int front= -1;
int rear= -1;

Node* deQueue();
void enQueue(Node* aNode);

int initializeBST(Node** h);

void recursiveInorder(Node* ptr);
void iterativeInorder(Node* ptr);
void levelOrder(Node* ptr);
int insert(Node* head, int key);
int deleteNode(Node* head, int key);
int freeBST(Node* head);

void printStack();

int main()
{
    char command;
    int key;
    Node* head = NULL;

    printf("-----------[2019037002] [hankyuwon]--------------\n");
    do{
        printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

        printf("Command =");
        scanf(" %c", &command);

        switch(command){
            case'z':case'Z':
            initializeBST(&head);
            break;
            case'q':case'Q':
            freeBST(head);
            break;
            case'i':case'I':
            printf("Your key =");
            scanf("%d",&key);
            insert(head,key);
            break;
            case'd':case'D':
            printf("Your key =");
            scanf("%d", &key);
            deleteNode(head,key);
            break;
            case'r':case'R':
            recursiveInorder(head->left);
            break;
            case't':case'T':
            iterativeInorder(head->left);
            break;
            case'l':case'L':
            levelOrder(head->left);
            break;
            case'p':case'P':
            printStack();
            break;
            default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
        }
    }while(command!='q' && command !='Q');

    return 1;
}

int initializeBST(Node** h) // 이진탐색트리 생성을 위해 헤드노더를 생성하는 함수
{
    if(*h !=NULL)// 헤드노더가 NULL이 아닐 경우
    freeBST(*h); // head에 연결된 이진탐색트리 메모리 해제
    
    *h=(Node*)malloc(sizeof(Node));
    (*h)->left=NULL;
    (*h)->right=*h;
    (*h)->key=-9999;

    top=-1;

    front=rear=-1;

    return 1;
}

void recursiveInorder(Node* ptr) // 트리 중위순회 재귀 함수
{
    if(ptr){
        recursiveInorder(ptr->left); // 트리의 왼쪽 자식노드로 이동
        printf(" [%d]", ptr->key); // 출력
        recursiveInorder(ptr->right); // 트리의 오른쪽 자식노드로 이동
    }
}

void iterativeInorder(Node* node) // 트리 중위순회 반복문 이용 함수
// 레벨 1 노드부터 차례대로 Stack에 push (node 가 NULL이 아닐때 까지) -> Stack[ .... ] (여기서 top은 트리의 맨 왼쪽 아래 노드)
// -> 맨 왼쪽 아래 노드 pop(), 출력, 오른쪽 자식노드로 이동
// 오른쪽 자식노드는 NULL 이므로 for문(push) 진행하지 않고 바로 pop, 출력 .....
{
    for(;;)
    {
        for(;node;node=node->left)
        {
            push(node);
        }

        node=pop();

        if(!node) break;

        printf(" [%d] ", node->key);
        node=node->right;
    }
}

void levelOrder(Node* ptr) // 트리 레벨 순회 출력 함수
// 원형 큐에 레벨 1 노드 삽입 -> deQueue 함수를 통해 원형 큐에서 레벨 1 노드 꺼냄 -> 레벨 1 노드 출력,레벨 1 노드의 왼쪽 자식노드 , 오른쪽 자식노드 순으로 enQueue()
// -> 레벨 1 노드의 왼쪽 자식노드 꺼냄 -> 출력, 레벨 1노드의 왼쪽 자식노드, 오른쪽 자식노드 순으로 enQueue() -> 레벨 1 노드의 오른쪽 자식노드 꺼냄 ....
{
    if(!ptr) return;

    enQueue(ptr);

    for(;;)
    {
        ptr=deQueue();

        if(ptr){ // if(ptr != NULL) 과 동일
            printf(" [%d] ", ptr->key);

            if(ptr->left)
            enQueue(ptr->left);
            if(ptr->right)
            enQueue(ptr->right);
        }
        else
        break;
    }
}

int insert(Node* head, int key) // 입력값을 key로 갖는 노드 생성
{
    Node* newNode=(Node*)malloc(sizeof(Node)); // Node 메모리 동적 할당
    newNode->key=key;
    newNode->left=NULL;
    newNode->right=NULL;

    if(head->left==NULL){ // 트리가 비어있는 경우
        head->left=newNode;
        return 1;
    }

    Node* ptr = head->left; // 트리의 레벨 1 에 해당하는 노드를 ptr로 생각

    Node* parentNode=NULL;

    while(ptr!=NULL){ // ptr이 NULL이 될 때 까지 자식노드를 타고 이동
        if(ptr->key==key) return 1; // key값(입력값)을 갖고있는 Node가 존재하면 just return

        parentNode=ptr; // ptr이 NULL이 되었을 때 부모노드로 돌아가지 못하므로 기록하기 위해 parentNode에 ptr을 계속 대입해줌

        if(ptr->key<key) // 입력받은 key가 ptr의 key값 보다 크면 오른쪽 자식노드이므로 오른쪽으로 이동
        ptr=ptr->right;
        else
        ptr=ptr->left;
    }

    if(parentNode->key>key) // parentNode의 key값이 입력받은 key값 보다 크면 왼쪽 아래 자식노드 생성
    parentNode->left=newNode;
    else // 그렇지 않은 경우 오른쪽 아래 자식노드 생성
    parentNode->right=newNode;
    return 1;
}

int deleteNode(Node* head, int key)
{
    if(head==NULL){
        printf("\n nothing to delete!!\n");
        return -1;
    }

    if(head->left==NULL){
        printf("\n Nothing to delete!!\n");
        return -1;
    }

    Node* root = head ->left; // root를 트리의 레벨 1 노드로 생각

    Node* parent = NULL;
    Node* ptr = root;

    while((ptr!=NULL)&&(ptr->key!=key)){ // ptr 이 NULL이 되거나, ptr의 key값이 입력값이면 while문 종료
        if(ptr->key!=key){ // ptr의 key값이 입력값이 아니면
            parent=ptr; // parent에 ptr을 넣어주는 이유는 ptr이 계속해서 이동하는데, 이전으로 돌아갈 방법이 없기 때문이다.
            if(ptr->key>key) // key값 비교를 통해 계속해서 이동
            ptr=ptr->left; // ptr의 key값이 입력값보다 크면 왼쪽 자식노드로 이동
            else
            ptr=ptr->right; // ptr의 key값이 입력값보다 작으면 오른쪽 자식노드로 이동
        }
    }

    if(ptr==NULL) // key값을 찾기 위해 ptr을 이동시키는데 찾는 key값을 갖고있는 node가 존재하지 않는다면 ptr은 NULL까지 이동하게된다.
    {
        printf("No node for key [%d]\n", key);
        return -1;
    }
//case 1: the node which has to be removed is a leaf node
    if(ptr->left==NULL && ptr->right==NULL) // ptr의 자식노드가 없을때
    {
        if(parent!=NULL) // parent가 NULL 이 아닐때, 즉 ptr은 트리의 레벨 1 노드가 아닐때
        {
            if(parent->left==ptr) // ptr이 parent의 왼쪽 자식 노드일 때
            parent->left=NULL; // parent->left 를 ptr에서 NULL로 바꿔줌
            else
            parent->right=NULL; // ptr이 parent의 오른쪽 자식 노드일 때 parent->right = NULL
        }

        else // parent == NULL 일때, 처음 parent를 선언할 때 NULL로 선언했음. 지금 parent가 NULL일 때는 위의 while문이 한번도 돌아가지 않았을때,
        // 즉 ptr이 트리의 레벨 1 노드일때이다.
        {
            head->left=NULL;
        }

        free(ptr); // ptr 메모리 해제. 여기서 ptr은 입력 key값을 key로 갖고있는 노드
        return 1;
    }

//case 2: if the node to be deleted has one child
    if((ptr->left==NULL || ptr->right ==NULL)) // ptr의 왼쪽 자식노드가 없거나 오른쪽 자식노드가 없을 때(왼쪽 자식노드와 오른쪽 자식노드가 둘다 없을때는 위에서 이미 걸러짐.
    // 따라서 둘중 하나만 없을때만 이 if문에 걸림)
    {
        Node* child; // child 노드 생성
        if(ptr->left!=NULL) // ptr의 왼쪽 자식노드가 있을 때
        child=ptr->left; // child를 ptr의 왼쪽 자식노드로 생각
        else
        child=ptr->right; // ptr의 오른쪽 자식노드가 없을 때, child를 ptr의 오른쪽 자식노드로 생각
        
        if(parent!=NULL) // parent가 NULL이 아닐때, 즉 ptr은 트리의 레벨 1 노드가 아닐때
        {
            if(parent->left=ptr) // parent의 왼쪽 자식 노드가 ptr일 때
            parent->left=child; // parent의 왼쪽 자식 노드를 ptr의 자식 노드인 chlid로 선언(parent->ptr->child에서 중간에 ptr을 끊음. parent->child)
            else
            parent->right=child;
        }
        
        else // ptr이 트리의 레벨 1 노드일 때
        {
            root=child; // head->left가 child가 됨. child가 즉 트리의 레벨 1 노드가 됨
        }

        free(ptr); // ptr(ptr->key값으로 입력key값을 갖고있는 노드) 메모리 해제
        return 1;
    }


//case 3: the node(ptr) has two children
    Node* candidate; // 삭제할 노드의 자리에 들어올 후계자 노드
    parent = ptr;
    
    candidate = ptr->right; // 후계자 노드를 찾는 방법에는 두가지 방법이 있다.
    // 왼쪽 자식 노드 중 가장 큰 노드 , 오른쪽 자식 노드 중 가장 작은 노드 두개 중 하나가 오면 된다.
    // 이 방법은 오른쪽 자식 노드 중 가장 작은 노드를 찾는 방법이다.
    // candidate는 ptr(삭제할 노드)의 오른쪽 자식노드, 즉 ptr보다 큼

    while(candidate->left !=NULL) // 계속해서 왼쪽 자식노드로 이동. ptr보다 큰 값중 가장 작은 값 찾기
    {
        parent=candidate;
        candidate=candidate->left;
    }

    if(parent->right==candidate) // 후계자 노드가 ptr의 바로 오른쪽 자식노드일 때
    parent->right=candidate->right; // 즉, parent의 오른쪽 자식노드에 candidate 가있고,
    // candidate는 자식노드가 없을 때 parent->right= NULL 대입, parent-> key에 candidate-> key 대입
    // 사실상 삭제하는 노드는 ptr이 아닌 candidate이다. ptr에 들어올 candidate 값을 찾은 뒤
    // ptr과 candidate의 연결 link를 NULL로 바꾼 뒤, candidate의 key값을 ptr의 key값에 대입,
    // 이후 candidate 메모리 해제 이다.

    else
    parent->left=candidate->right; // 후계자 노드가 ptr의 바로 오른쪽 자식노드가 아닐 때, 즉 바로 오른쪽 자식 노드에서 왼쪽 자식 노드로 n번의 이동이 있을 때
    // parent 의 왼쪽 자식노드가 후계자 노드. 연결을 끊고 값을 ptr에 넣어준뒤 후계자 노드는 삭제
    // 따라서 parent -> left는 NULL 대입
    ptr->key=candidate->key; // ptr -> key 값에 candidate -> key값 대입

    free(candidate); // candidate 노드 메모리 해제
    return 1;
}

void freeNode(Node* ptr) // ptr과 ptr의 자식 노드들 메모리 해제 함수
{
    if(ptr){
        freeNode(ptr->left); // 재귀함수 호출로 ptr의 왼쪽 자식 노드 모두 메모리 해제
        freeNode(ptr->right); // 재귀함수 호출로 ptr의 오른쪽 자식 노드 모두 메모리 해제
        free(ptr); // ptr 메모리 해제
    }
}

int freeBST(Node* head) // Binary Search Tree 전체 메모리 해제 함수
{
    if(head->left == head) // 이진 트리가 비어있을 때
    {
        free(head); // head만 메모리 해제
        return 1;
    }

    Node *p =head->left;

    freeNode(p); // head 다음 노드를 p라 하면, freeNode(p)를 통하여 메모리 해제

    free(head); // head 메모리 해제
    return 1;
}

Node* pop() // stack에서 pop을 구현하는 함수
{
    if (top < 0)return NULL;
    return stack[top--];
}

void push(Node* aNode) // stack에서 push를 구현하는 함수
{
    stack[++top]=aNode;
}

void printStack() // stack에 저장된 값을 출력
{
    int i=0;
    printf("--- stack ---\n");
    while(i<=top)
    {
        printf("stack[%d] = %d\n", i, stack[i]->key);
    }
}

Node* deQueue() // Queue에서 첫번째 값을 return하는 함수
{
    if(front==rear){ // Queue가 empty인 상태
        return NULL;
    }

    front=(front+1)%MAX_QUEUE_SIZE; // front값을 증가
    return queue[front]; // 현재 Queue의 첫번째 값 return
}

void enQueue(Node* aNode) // Queue에서 값을 추가하는 함수
{
    rear=(rear+1)%MAX_QUEUE_SIZE;
    if(front==rear){ // Queue가 FUll 인 상태
        return;
    }

    queue[rear]=aNode; // Queue가 Full 이 아니면, 노드 삽입
}