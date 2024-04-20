<<<<<<< HEAD
# minishell
=======
# Mini Shell
>>>>>>> etakaham-dev
## 大まかなフローチャート
### signalの処理 
### lexer 
#### envの情報を持ってくる   
#### 一個shlvのレベルを一つ上げて、ユーザーの環境から外す  

<<<<<<< HEAD
### parser 
=======
### parser
>>>>>>> etakaham-dev
#### 入力のトークン化
#### ctrl+C
#### ctrl+D
#### ctrl+/
#### histryに処理を加える

<<<<<<< HEAD
### expander 
=======
### expander
>>>>>>> etakaham-dev
#### pipeの実装

### executor 
#### 普通のshellからコマンドを呼び出す
#### echo with option -n
#### cd
#### pwd
#### export
#### unset
#### env
<<<<<<< HEAD
#### exit
=======
#### exit

## 入力値に対する処理
### 記録する構造体
#### tokens
charの二重ポインタ  
基本的に'command', 'option', 'arguments'が入る  
#### types
tokensの文字列が何なのかを記録する  
enumで'command', 'option', 'arguments'の三つのtypeを作り、それぞれなにに含まれるのかを記録する  
#### command
tokensの1つ目の文字列がなんのコマンドなのかを示す  
enumで'echo', 'cd', 'pwd', 'export', 'unset', 'env', 'exit', 'others'のなんなのかを記録する  

### 処理手順
1. char pointerで取得する
2. 入力行に''が含まれているかの確認
    1. あれば3に飛ぶ
    2. なければ に飛ぶ
3. ''が閉じているかの確認
    1. 閉じていなければ4に飛ぶ
    2. 閉じていれば に飛ぶ
4. 入力パラメーター
>>>>>>> etakaham-dev
