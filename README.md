# 正N角形の描画(HandyGrafic)

プログラム内容
正N角形を作図します(Nは２以上の有理数です）


起動後の操作
最初にNの数字を決定する画面が表示されます。
キーボードの数字または.を押すことで入力することができます。（例 4 , 3.25)
DELETEキーを押すと数字を打ち直すことができます。
ENTERキーを入力すると数字が確定し、次の画面へ進みます。
次の画面では入力した正N角形が表示されます。
ここで、ENTERキーを入力すると正N角形を回転することができます。
（回転させる前に円を表示させるかのキー入力が求められます、画面の指示に従って入力してください。）

問題点
数字によって画面が動かなくなる、座標がおかしくなり円上を飛び出す（？）。
動かなくなる数の例　2.7
座標がおかしくなる例　3.01



正N角形作図の方法
正多角形の頂点は円周上の点に存在することを利用する。
例　正三角形の場合120°ずつ回転させそれぞれに点を打ち結ぶ。

点の回転に使用した式
http://www.geisya.or.jp/~mwm48961/kou2/linear_image3.html

