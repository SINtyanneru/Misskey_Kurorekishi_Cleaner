#include <stdio.h>
#include <jansson.h>

#include "JSON.h"

json_t* JSON_PARSE(char *TEXT){
	json_t *ROOT;
	json_error_t ERR;

	ROOT = json_loads(TEXT, 0, &ERR);

	if (ROOT) {
		return ROOT;
	} else {
		fprintf(stderr, "Error parsing JSON: %s\n", ERR.text);
		return NULL;
	}
}

/*
const char *name, *city;
int age;
json_unpack(ROOT, "{s:s, s:i, s:s}", "name", &name, "age", &age, "city", &city);
printf("Name: %s\nAge: %d\nCity: %s\n", name, age, city);
json_decref(ROOT);
*/