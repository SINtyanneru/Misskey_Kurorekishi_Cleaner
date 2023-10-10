#include <stdio.h>
#include "LIB/parson/parson.h"

#include "JSON.h"

int JSON_PARSE(){
	// JSON文字列
	const char *json_string = "{ \"name\": \"John\", \"age\": 30, \"city\": \"New York\" }";

	// JSONオブジェクトの作成
	JSON_Value *root_value = json_parse_string(json_string);
	if (json_value_get_type(root_value) != JSONObject) {
		fprintf(stderr, "Error: Root element is not an object.\n");
		return 1;
	}

	// JSONオブジェクトから値を取得
	JSON_Object *root_object = json_value_get_object(root_value);
	const char *name = json_object_get_string(root_object, "name");
	double age = json_object_get_number(root_object, "age");
	const char *city = json_object_get_string(root_object, "city");

	// 取得した値を表示
	printf("Name: %s\n", name);
	printf("Age: %.0f\n", age);
	printf("City: %s\n", city);

	// JSON_Valueの解放
	json_value_free(root_value);

	return 0;
}