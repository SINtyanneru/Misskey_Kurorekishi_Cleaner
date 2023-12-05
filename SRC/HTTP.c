#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "HTTP.h"

// データの受信時に呼ばれるコールバック関数
size_t write_callback(void *contents, size_t size, size_t nmemb, char **output) {
	size_t realsize = size * nmemb;

	// 受信したデータをoutputにコピー
	*output = realloc(*output, realsize + 1);
	if (*output == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return 0;
	}

	memcpy(*output, contents, realsize);
	(*output)[realsize] = '\0';  // 文字列の終端を設定

	return realsize;
}

int HTTPS_REQUEST(){
	CURL *curl;
	CURLcode res;

	// cURLの初期化
	curl_global_init(CURL_GLOBAL_DEFAULT);

	// cURLハンドルの作成
	curl = curl_easy_init();
	if (curl) {
		// URLの設定
		curl_easy_setopt(curl, CURLOPT_URL, "https://ussr.rumiserver.com/api/users/show");

		// HTTPSリクエストを許可
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

		struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers, "Content-Type: application/json; charset=UTF-8");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		// POSTデータの設定
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		const char *post_data = "{\"username\":\"TestMan\",\"host\":null,\"i\":\"r1OMhQz0o1UVSqrr\"}";
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);

		// データを格納するための変数
		char *response_data = NULL;

		// データの受信時に呼ばれるコールバック関数の設定
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

		// リクエストの実行
		res = curl_easy_perform(curl);

		// エラーチェック
		if (res != CURLE_OK) {
			fprintf(stderr, "cURL failed: %s\n", curl_easy_strerror(res));
		} else {
			// 受信したデータを表示
			printf("Response:\n%s\n", response_data);
		}

		// データを格納する変数の解放
		free(response_data);

		// cURLハンドルのクリーンアップ
		curl_easy_cleanup(curl);
	}

	// cURLのクリーンアップ
	curl_global_cleanup();

	return 0;
}