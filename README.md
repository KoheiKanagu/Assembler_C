##概要
* アセンブリ言語をバイナリに変換するプログラム
* 変換されたバイナリは、.mifをテキストで開いてコピペすると便利
* レジュメの機械命令語16bitを順守
* 某大学3回生の某実験のお役立ちツール
* Objective-Cバージョンはこちら[Assembler_Objective-C](https://github.com/KoheiKanagu/Assembler_Objective-C)


##注意点
* `//`でコメントアウトが可能
* 日本語のコメントはオーバーフローする場合があるので**非推奨**
* 改行は無視される
* 入力終了には`EOF`か`-1`


##実装命令
* ST
* LD
* ADD
* LI
* B
* BNZ
* CMP
* MLT
* BZ
* NOP

###オリジナル命令
* ADDI
* ROOT