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
