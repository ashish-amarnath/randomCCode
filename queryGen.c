#include <stdio.h>
#include <assert.h>

void generate_query() {
	FILE *fp = fopen("globalTxnIds.txt", "r");
	assert(fp != NULL);
	char txnId[25] = { 0 };

	fprintf (stdout,
			"{ \n  \"query\": { \n    \"bool\": { \n      \"must\": [],  \n      \"must_not\": [], \n      \"should\": [\n");
	while (fscanf(fp, "%s", txnId) != EOF) {
		fprintf(stdout, "        {\"term\": {\"tran.salesCollectHeader.globalTransactionID\": \"%s\"}},\n", txnId);
	}
	fprintf (stdout, "      ]\n    }\n  },\n  \"size\":40\n}\n");
}


int main () {
	generate_query();
}
