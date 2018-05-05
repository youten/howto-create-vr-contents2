#@# VRコンテンツのつくりかた2 技術書典3
#@# （）かっこは全角統一する。
#@# ユーザ入力は""ダブルクォーテーション、メニュー表示文字列は「」かぎかっこにでくくる。

= Daydreamを使う

この章では、Daydreamの使い方について紹介します。
セットアップから始まり、Google Playとの連携具合や、開発する際に便利なデバッグ設定について記載します。

== Daydreamのセットアップ

=== 初期セットアップ

//image[daydream-setup-01][Daydreamのセットアップ][scale=0.90]

DaydreamのアイコンからDaydreamアプリを立ち上げます。
まずはVRモードではない通常の2DのUIで、初期セットアップウィザードが始まります。
Daydreamのアプリも通常のアプリと同様のGoogle Playで公開されており、そこからダウンロードする仕組みになっていますので、Googleアカウントを選択します（@<img>{daydream-setup-01}-左）。

Daydream対応ヘッドセットを持っている場合のみ続行できます（@<img>{daydream-setup-01}-中）。
ただし、抜け道があり、Daydream Viewを持っていなくとも、Bluetooth経由で別のAndroidデバイスをDaydreamコントローラエミュレータとして使うことができます。
これについては後述します。

//image[daydream-entry-screen][VRモードに移行する際に表示されるエントリー画面][scale=0.75]

Daydreamコントローラのペアリングを行った後（@<img>{daydream-setup-01}-右）、エントリー画面（@<img>{daydream-entry-screen}）を経て、ここ以降はVRモードでのチュートリアルが始まります。

=== チュートリアルとホーム画面

//image[daydream-tutorial][チュートリアル画面][scale=1.00]

きちんとバンドがしまっていて、首をふってもヘッドセットがずれたりしないかの確認に始まり（@<img>{daydream-tutorial}-左上）、コントローラの使い方を順番に教えてくれます@<fn>{tutorial-tofu}。

とくにこのDaydreamボタン（旧：ホームボタン）の長押しによる中心のリセット（@<img>{daydream-tutorial}-左下）は重要操作なので覚えておきましょう。

//footnote[tutorial-tofu][2017年10月15日現在、手元の環境では一部の文字が豆腐になっており、見事に読めませんでした。日本語が正常に表示されている画面もあり、詳細は不明です。]

//image[daydream-home][Daydreamのホーム画面][scale=1.00]

チュートリアルが終わると、Daydreamのホーム画面が表示されます（@<img>{daydream-home}）。

ピックアップアプリや動画が上段に、中段には最近使ったアプリが並びます。
下段は左から、アプリ「Playストア」、インストール済みアプリ一覧の「ライブラリ」、Chromecastでアプリ画面を写す「キャスト」、「設定」です。

セットアップが終わると、どのアプリを試せばいいのか迷うのですが、まずは「Googleストリートビュー」をオススメします。
次に、徐々にVR空間での使い勝手がよくなってきた「YouTube」で360度・3D（ステレオで立体的に見える）動画を閲覧しましょう。
もしあなたがTHETAユーザで、全天球の画像をそれなりに保有してあるのであれば、「Googleフォト」も大変オススメです。

ゲームなどのダイナミックなコンテンツもいいのですが、現状はこれだ！というキラータイトルが定まっていないように思えます。
まずは写真・動画系のアプリでDaydreamの操作に慣れたあとでゆっくり探して見てください。

=={daydream-developer-settings} デベロッパー向け設定とVR Entry Flow

この節では、Daydreamのデベロッパー向けの設定を用いて、不要な操作を省略したり、Daydream ViewがなくともDaydreamアプリの利用や開発を可能にする方法を紹介します。
ユーザにトラブルなくDaydreamを利用してもらうための特別なフローである「VR Entry Flow」の他、様々な仕組みがあって、特別な設定や操作の上に可能となります。

=== VR Entry Flow

Daydreamには、コントローラのペアリングや、必要な権限の設定を、ヘッドセットをかぶる前にチェックの上、必要な操作をユーザに促すVR Entry Flow@<fn>{vr-entry-flow}という作業フローが定義されています。

VRアプリの起動時など、非VRの状態からVRモードに遷移する際に、以下のフローに従います。

 1. 設定済みでなければ、コントローラをペアリングします
 2. 必要があれば、コントローラのファームウェアをアップデートします
 3. 必要があれば、Google VR Servicesを有効にして、必要な権限を設定します
 4. BluetoothやNFCの他、必要な設定がONになっていなければ設定画面を呼び出します
 5. 実施していなければ、Daydreamヘッドセットの設定を行います
 6. ガイド（@<img>{daydream-entry-screen}）を表示し、スマートフォンをヘッドセットに挿入します
 7. コントローラと接続し、ヘッドセットとコントローラの向きを初期化、キャリブレートします

これらのフローはGoogle VR Servicesによって自動的にハンドリングされ、通常アプリ開発者はこの流れを気にする必要はありません。
ただし、ホームアプリのランチャーや、タスク一覧からあなたのVRアプリを立ち上げた際に、Androidライフサイクルに沿って起動したあなたのVR Activityは、VR Entry Flowによって割り込まれ、中断されます。
Daydreamアプリに限定された話ではなくAndroidアプリとして当然の話ではありますが、あなたのアプリがいつ中断されても問題がないように作っておく必要があります。

//footnote[vr-entry-flow][VR Entry Flow | Google VR | Google Developers @<href>{https://developers.google.com/vr/daydream/guides/vr-entry}]

=== デベロッパー向けの設定

Daydreamには、デベロッパー向けのデバッグ設定があります。
このうち、「VR Entry Flowをスキップする設定」と「Bluetooth経由でのコントローラのエミュレータを使う設定」の2つが大変重要ですので覚えておいてください。
前者はコントローラを操作する必要がないアプリの利用時や機能の開発時に便利です。
また、この2つの設定を組み合わせると、Daydream Viewを持っていなくともDaydreamアプリの利用や開発を行うことが可能になります。

デベロッパー向けの設定については公式サイトの「The Controller Emulator@<fn>{controller-emulator}」のページに記載されていますが、手順のみがシンプルに掲載されており、少しわかりづらいです。
もう少し噛み砕いて手順を確認していきましょう。

前節のDaydreamの初期セットアップの最後、コントローラのペア設定画面（@<img>{daydream-setup-01}-右）まで進めると、実は初期セットアップとしてはコントローラの設定を残して完了しているため、Daydreamアプリを終了して、再度起動すると設定が完了したかのようにホーム画面が表示されます。

//image[daydream-developer-settings-01][デベロッパー向け設定の有効化][scale=1.00]

ホーム画面の左上のハンバーガーメニュー（≡）から設定画面（@<img>{daydream-developer-settings-01}-左）を呼び出し、「ビルド バージョン」を7回タップすると（@<img>{daydream-developer-settings-01}-中）、「デベロッパー向けの設定」隠しメニューが表示されるようになります（@<img>{daydream-developer-settings-01}-右）。

//image[daydream-developer-settings-02][デベロッパー向けの設定][scale=1.00]

ここまで、Daydream Viewとコントローラを使わないまま、セットアップを続けています。
実際にアプリを起動した際にコントローラとのペアリングを要求されるのを回避するために、デベロッパー向けの設定中の、「Skip VR entry screens」を有効にしておきましょう（@<img>{daydream-developer-settings-02}）。

//footnote[controller-emulator][The Controller Emulator | Google VR | Google Developers @<href>{https://developers.google.com/vr/daydream/controller-emulator}]

=== Daydreamコントローラエミュレータ

//image[daydream-controller-emulator-setup][コントローラエミュレータのセットアップ][scale=1.00]

続けて、コントローラエミュレータのセットアップを行い、動かしてみましょう。

==== エミュレータアプリは別Androidデバイスで

Daydreamコントローラのエミュレータは、専用のAndroidアプリが公開されています。
Daydream母艦となるAndroidデバイスとは別のAndroidデバイスを用意してください。
Android 4.4 KitKat以降であれば動作します。
Daydream-ready phoneがもう1台必要というわけではありません。

==== Bluetoothのペアリング設定

まず、2台のBluetooth設定を開いて、ペアリングを行います（@<img>{daydream-controller-emulator-setup}-左）。
この際、エミュレータ側のデバイス名を区別がつきやすい名前に変えておくとわかりやすいです。

次に、Daydreamのデベロッパー向け設定の「controller emulator device」を選択し、ペアリング設定を行ったデバイスを選択します（@<img>{daydream-controller-emulator-setup}-中）。

前述の公式サイト@<fn>{controller-emulator}から、「Controller Emulator」のapkをダウンロードし、インストールします@<fn>{apk-install}。
このアプリは、Bluetooth経由の他、WiFiやUSBケーブル経由でUnityやUnreal Engineなどのエディタ上でのコントローラ操作のエミュレートにも使えます。

==== コントローラエミュレータを試す

セットアップが完了したら、実際に動かしてみましょう。
Daydreamアプリを立ち上げ、右下のVRゴーグルアイコンをタップします。
「Skip VR entry screens」設定が有効になっていると、本物のコントローラのペアリングも、Daydreamボタンの押下も要求されません。

二眼ステレオのVRモードになったら、もう一台のAndroidで「Controller Emulator」アプリを起動します。
エミュレータアプリの表示が「Connected（Bluetooth）」になったら、正常に動作しています。
うまくいかない際には、Bluetoothの設定や、アプリの起動順番に気をつけつつ、何度かやり直してみてください。
アプリUI上にも説明文言が表示されていますが、タッチパネル部のクリックのエミュレートには、アプリ上でのダブルタップで対応しています。

==== Daydream Viewがなくとも

ここまでの手順で、Daydream Viewがなくとも、Daydream-ready phoneまたはその設定が可能なAndroidデバイスがあればDaydreamの世界をちょっと覗いてみたり、Daydreamアプリ開発を試してみることができるようになります。
ただし、あくまでお試しで。
Daydreamの真の力はきちんとした環境でぜひ体験してください。

//footnote[apk-install][インストール手順は省略します。AndroidのSDKが導入済みであれば「adb install」を、一般ユーザは「提供元不明のアプリのインストール」を試してみてください。]

== Daydream View互換機BOBOVR Z5を試す

//image[bobovr-z5-photo][BOBOVR Z5 Daydarem Edition][scale=1.00]

=== Daydream View互換機とは

前章で述べた通り、Daydream ViewのヘッドユニットはCardboardと同等のもので、コントローラはBLEで（比較的）シンプルな情報を送信しているだけです。
このため、ハックの上、クローンが作れるということです。

=== BOBOVR Z5

Cardboard向けVRゴーグルや、独自のVRのプラットフォームを展開しているBOBOVRから、BOBOVR Z5@<fn>{bobovr-z5}というDaydream View互換機が登場しました（@<img>{bobovr-z5-photo}）。
$59でAliExpress経由で購入しましたが、今はAmazon@<fn>{bobovr-z5-amazon}でも取り扱いがある模様です。

=== ヘッドユニットのレンズまわりに難あり

Daydreamのコントローラ部は問題なく動作しました。タッチパネル部の形状の違いから操作感が違うのですが、許容範囲だと思います。

ただし、公式サイトにも書かれていますが、旧型のDaydream Viewの視野角である90度を120度に広げたヘッドユニット部の独自拡張がよろしくなく、端が歪んで見えます。
首を振ると顕著に感じられ、気持ち悪く感じます。

結論としては、Daydream互換機として動作はしましたが、格別安いというわけでもなく、決してオススメはできない機種です。
日本特有の例のアレの話もありますし、おとなしく新型のDaydream Viewを購入してください。

//footnote[bobovr-z5][BOBOVR Z5 @<href>{http://www.bobovr.com/product/bobovrz5/}]
//footnote[bobovr-z5-amazon][Amazon.co.jp： BOBOVR Z5 Daydream View VRゴーグル @<href>{https://www.amazon.co.jp/dp/B071GYQR8V}]
