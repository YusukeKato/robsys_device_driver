# 対戦型LEDゲーム

LEDとスイッチを使ったゲームを作成しました。

スイッチの入力は```/sys/class/gpio/```からです。



概要
---
・二人プレイ（一人でも可）

・卓球のラリーのようなタイミングゲーム



必要な物
---
・Raspberry Pi 3

・ブレッドボード

・LED × 17

・スイッチ × 2 （今回はジャンパ線で代用しました）

・ジャンパ線

・抵抗



ルール
---
・自分の側にLEDの光がやってきたら、タイミングよくスイッチを押します。

・上手くいくとLEDの光を返せます。

・失敗すると負けです。（ゲーム終了時、勝った側のLEDが点滅します。）

・LEDの光はだんだんと早くなります。

・スイッチをずっとONにしていても返せないようにしています。



導入方法
---
```
git clone https://github.com/YusukeKato/robsys_device_driver.git
cd robsys_device_driver
make
make install
./led_game.sh
```



動画
---
https://youtu.be/2ITisuJ2QFc
