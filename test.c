#include "includes/minishell.h"

int main() {
    printf("Ctrl+\\ を押してSIGQUITシグナルを送信し、コアダンプを生成します。\n");
    printf("プログラムを終了するには、Ctrl+Cを使用してください。\n");
    ft_putstr_fd(M_PROMPT, 1);
    // 無限ループでプログラムを実行し続ける
    while (1) {
        sleep(1); // 1秒間隔でループを継続
    }

    return 0;
}

