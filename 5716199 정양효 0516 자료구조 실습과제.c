#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct listNode {
    element data;
    struct listNode* link;
} ListNode;

ListNode* insert_first(ListNode* h, int value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = h;
    h = p;
    return h;
}

ListNode* insert(ListNode* head, ListNode* pre, element value) {
    if (pre == NULL) {
        printf("Error: pre is NULL\n");
        return head;
    }
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    if (p == NULL) {
        printf("Memory allocation error\n");
        return head;
    }
    p->data = value;
    p->link = pre->link;
    pre->link = p;
    return head;
}

void print_list(ListNode* h) {
    while (h != NULL) {
        printf("%d->", h->data);
        h = h->link;
    }
    printf("NULL\n");
}

ListNode* delete_first(ListNode* head) {
    if (head == NULL)
        return NULL;
    ListNode* remove = head;
    head = remove->link;
    free(remove);
    return head;
}

ListNode* delete(ListNode* h, ListNode* pre) {
    if (pre == NULL || pre->link == NULL) {
        printf("Error\n");
        return h;
    }
    ListNode* remove = pre->link;
    pre->link = remove->link;
    free(remove);
    return h;
}

int main() {
    ListNode* head = NULL;
    element input;
    int choice, pos;
    int insert_count = 0, delete_count = 0;

    while (1) {
        printf("\n메뉴:\n");
        printf("1. 숫자를 위치에 삽입\n");
        printf("2. 위치에서 숫자 삭제\n");
        printf("3. 리스트 출력\n");
        printf("0. 프로그램 종료\n");
        printf("선택하세요: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("삽입할 숫자를 입력하세요: ");
            scanf("%d", &input);
            printf("추가할 위치를 입력하세요: ");
            scanf("%d", &pos);
            insert_count = 0;

            if (pos == 0) {
                head = insert_first(head, input);
            }
            else {
                ListNode* temp = head;
                for (int i = 0; i < pos - 1; i++) {
                    if (temp == NULL) {
                        printf("잘못된 위치입니다.\n");
                        break;
                    }
                    temp = temp->link;
                    insert_count++;
                }
                if (temp != NULL) {
                    head = insert(head, temp, input);
                    insert_count++;
                }
            }
            printf("삽입시 이동한 링크 수: %d\n", insert_count);
            print_list(head);
            break;
        case 2:
            if (head == NULL) {
                printf("리스트가 비어있습니다.\n");
            }
            else {
                printf("삭제할 위치를 입력하세요: ");
                scanf("%d", &pos);
                delete_count = 0;

                if (pos == 0) {
                    head = delete_first(head);
                }
                else {
                    ListNode* temp = head;
                    for (int i = 0; i < pos - 1; i++) {
                        if (temp == NULL || temp->link == NULL) {
                            printf("잘못된 위치입니다.\n");
                            break;
                        }
                        temp = temp->link;
                        delete_count++;
                    }
                    if (temp != NULL && temp->link != NULL) {
                        head = delete(head, temp);
                        delete_count++;
                    }
                }
            }
            printf("삭제시 이동한 링크 수: %d\n", delete_count);
            print_list(head);
            break;
        case 3:
            print_list(head);
            break;
        case 0:
            printf("프로그램 종료\n");
            return 0;
        default:
            printf("유효하지 않은 선택입니다.\n");
        }
    }
}
