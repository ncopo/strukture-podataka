#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH (50)
#define MAX_DATE_LENGTH (11)
#define FILE_NOT_OPEN (-1)
#define FAILED_MEMORY_ALLOCATION (NULL)


typedef struct _article* articlePosition;
typedef struct _article {
	char name[MAX_LENGTH];
	int quantity;
	int price;
	articlePosition next;
}article;

typedef struct _receipt* receiptPosition;
typedef struct _receipt {
	char receiptDate[MAX_DATE_LENGTH];
	article articleHead;
	receiptPosition next;

}receipt;


int loadReceipts(receiptPosition receiptHead);
receiptPosition createReceipt(char* receiptName);
articlePosition createArticle(char* articleName, int articleQuantity, int articlePrice);
int addArticleSorted(articlePosition articleHead, articlePosition newArticleNode);
int addReceiptSorted(receiptPosition receiptHead, receiptPosition newReceiptNode);
int compareDates(char* date1, char* date2);
int mergeReceipts(receiptPosition newReceiptNode, receiptPosition currentReceiptInList);
int findArticlesInTimeFrame(receiptPosition receiptHead, char* wantedArticleName, char* dateFrom, char* dateTo);
int printArticlesInTimeFrame(receiptPosition firstReceipt, receiptPosition lastReceipt, char* wantedArticleName);
int printReceiptsAndArticles(receiptPosition receiptHead);
int freeArticle(articlePosition articleHead);
int freeReceipt(receiptPosition receiptHead);


int main() {
	receipt receiptHead = { {0},{{0},0,0,NULL},NULL };
	char dateFrom[MAX_LENGTH] = { '\0' };
	char dateTo[MAX_LENGTH] = { '\0' };
	char articleName[MAX_LENGTH] = { '\0' };

	loadReceipts(&receiptHead);

	printf("\nReceipts and articles:\n");
	printReceiptsAndArticles(&receiptHead);


	printf("\nEnter the name of the article and the time period in the format 'article YYYY-MM-DD YYYY-MM-DD' to find out the total quantity and price of that article: ");
	scanf("%s %s %s", articleName, dateFrom, dateTo);

	findArticlesInTimeFrame(&receiptHead, articleName, dateFrom, dateTo);

	freeReceipt(&receiptHead);

	return EXIT_SUCCESS;
}

int loadReceipts(receiptPosition receiptHead) {
    FILE* file = fopen("racuni.txt", "r");
    char receiptName[MAX_LENGTH] = { '\0' };
    receiptPosition newReceiptNode = NULL;

    if (!file) {
        printf("Error opening file: racuni.txt\n");
        return FILE_NOT_OPEN;
    }

    while (fscanf(file, "%s", receiptName) == 1) {
        newReceiptNode = createReceipt(receiptName);
        if (newReceiptNode)
            addReceiptSorted(receiptHead, newReceiptNode);
    }

    fclose(file);
    return EXIT_SUCCESS;
}


receiptPosition createReceipt(char* receiptName) {
    FILE* file = fopen(receiptName, "r");
    char receiptDate[MAX_DATE_LENGTH] = { '\0' };
    char articleName[MAX_LENGTH] = { '\0' };
    int articleQuantity = 0, articlePrice = 0;

    receiptPosition newReceiptNode = malloc(sizeof(receipt));
    if (!newReceiptNode) {
        printf("Memory allocation failed for receipt\n");
        return FAILED_MEMORY_ALLOCATION;
    }

    if (!file) {
        printf("Error opening file: %s\n", receiptName);
        free(newReceiptNode);
        return NULL;
    }

    fscanf(file, "%s", receiptDate);
    strcpy(newReceiptNode->receiptDate, receiptDate);
    newReceiptNode->next = NULL;
    newReceiptNode->articleHead.next = NULL;

    while (fscanf(file, "%s %d %d", articleName, &articleQuantity, &articlePrice) == 3) {
        articlePosition newArticleNode = createArticle(articleName, articleQuantity, articlePrice);
        if (newArticleNode)
            addArticleSorted(&newReceiptNode->articleHead, newArticleNode);
    }

    fclose(file);
    return newReceiptNode;
}


articlePosition createArticle(char* articleName, int articleQuantity, int articlePrice) {
    articlePosition newArticleNode = malloc(sizeof(article));
    if (!newArticleNode) {
        printf("Memory allocation failed for article\n");
        return FAILED_MEMORY_ALLOCATION;
    }

    strcpy(newArticleNode->name, articleName);
    newArticleNode->quantity = articleQuantity;
    newArticleNode->price = articlePrice;
    newArticleNode->next = NULL;

    return newArticleNode;
}


int addArticleSorted(articlePosition articleHead, articlePosition newArticleNode) {
    articlePosition current = articleHead;

    while (current->next != NULL && strcmp(newArticleNode->name, current->next->name) > 0)
        current = current->next;

    if (current->next != NULL && strcmp(newArticleNode->name, current->next->name) == 0) {
        current->next->quantity += newArticleNode->quantity;
        current->next->price += newArticleNode->price * newArticleNode->quantity;
        free(newArticleNode);
    } else {
        newArticleNode->next = current->next;
        current->next = newArticleNode;
    }
    return EXIT_SUCCESS;
}


int compareDates(char* date1, char* date2) {
    int y1, m1, d1, y2, m2, d2;
    sscanf(date1, "%d-%d-%d", &y1, &m1, &d1);
    sscanf(date2, "%d-%d-%d", &y2, &m2, &d2);

    if (y1 != y2) return (y1 > y2) ? 1 : -1;
    if (m1 != m2) return (m1 > m2) ? 1 : -1;
    return (d1 > d2) ? 1 : (d1 < d2 ? -1 : 0);
}


int mergeReceipts(receiptPosition newReceiptNode, receiptPosition currentReceiptInList) {
    articlePosition current = &newReceiptNode->articleHead;
    while (current->next != NULL) {
        addArticleSorted(&currentReceiptInList->articleHead, createArticle(current->next->name, current->next->quantity, current->next->price));
        current = current->next;
    }
    return EXIT_SUCCESS;
}


int printReceiptsAndArticles(receiptPosition receiptHead) {
    receiptPosition currentReceipt = receiptHead->next;
    while (currentReceipt) {
        printf("Receipt Date: %s\n", currentReceipt->receiptDate);
        articlePosition currentArticle = currentReceipt->articleHead.next;
        while (currentArticle) {
            printf("  Article: %s, Quantity: %d, Price: %d EUR\n", currentArticle->name, currentArticle->quantity, currentArticle->price);
            currentArticle = currentArticle->next;
        }
        printf("\n");
        currentReceipt = currentReceipt->next;
    }
    return EXIT_SUCCESS;
}


int freeArticle(articlePosition articleHead) {
    articlePosition temp;
    while (articleHead->next) {
        temp = articleHead->next;
        articleHead->next = temp->next;
        free(temp);
    }
    return EXIT_SUCCESS;
}


int freeReceipt(receiptPosition receiptHead) {
    receiptPosition temp;
    while (receiptHead->next) {
        temp = receiptHead->next;
        freeArticle(&temp->articleHead);
        receiptHead->next = temp->next;
        free(temp);
    }
    return EXIT_SUCCESS;
}
