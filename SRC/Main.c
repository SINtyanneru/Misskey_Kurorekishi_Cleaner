#include <stdio.h>

#include "HTTP.h"
#include "JSON.h"

int main(){
	HTTPS_REQUEST();

	JSON_PARSE("{\"name\": \"John\", \"age\": 30, \"city\": \"New York\"}");

	return 0;
}