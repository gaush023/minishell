#include "../playground.h"

int main(void) {
    char *input;

    // ユーザーにプロンプトを表示して入力を読み取る
    while ((input = readline("Enter command (or 'exit' to quit): ")) != NULL) {
        // 'exit'が入力されたらループを抜ける
        if (strcmp(input, "exit") == 0) {
            free(input);
            break;
        }

        // 入力を履歴に追加
        if (input && *input) {
            add_history(input);
        }

        // 入力内容を表示
        printf("You entered: %s\n", input);
        free(input);
    }

    // 履歴をクリア
    printf("Clearing history...\n");
    clear_history();

    printf("History cleared. Exiting.\n");
    return 0;
}
