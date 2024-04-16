# minishell
## 大まかなフローチャート
### signalの処理 
### lexer 
#### envの情報を持ってくる   
#### 一個shlvのレベルを一つ上げて、ユーザーの環境から外す  

### parser 
#### 入力のトークン化
#### ctrl+C
#### ctrl+D
#### ctrl+/
#### histryに処理を加える

### expander 
#### pipeの実装

### executor 
#### 普通のshellからコマンドを呼び出す
#### echo with option -n
#### cd
#### pwd
#### export
#### unset
#### env
#### exit